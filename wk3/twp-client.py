#!/usr/bin/python

import os
import mimetypes
import getpass
import smtplib
import subprocess
import argparse
from smtplib import SMTPAuthenticationError
from email.mime.multipart import MIMEMultipart
from email import encoders
from email.message import Message
from email.mime.audio import MIMEAudio
from email.mime.base import MIMEBase
from email.mime.image import MIMEImage
from email.mime.text import MIMEText

# twp-client.py
#
# author: Kendrick Cline
#         kdecline@gmail.com
#         01/26/2016
#
# This script serves to be a hands free client
# program which creates a default RSA Key for
# students if they don't exist, then e-mails their
# public key to the appropriate server for registration

#####
# Argument Parser
#####
parser = argparse.ArgumentParser(description = 'Client program for the Trenary Workflow Project to be used by students to initialize their \
        machines')
parser.add_argument('-v', '--verbose', action='store_true', help='enable more logging')
parser.add_argument('--dest-email', action='store', help='override default destination email')
args = vars(parser.parse_args())

#####
# Variables
#####
MAX_PASSWORD_ATTEMPTS = 3
class_emails = {
    'a' : 'trenarycs223@gmail.com',
    'b' : 'trenarycs224@gmail.com'
#    'c' : 'carrcs595@gmail.com'
}
rsa_key_path = os.path.expanduser('~/.ssh/id_rsa')
rsa_pub_key_path = os.path.expanduser('~/.ssh/id_rsa.pub')
ssh_keygen_cmd = "ssh-keygen -b 2048 -t rsa -f {0} -q -N \"\"".format(rsa_key_path)

#####
# Functions
#####
def debug(msg):
    if args['verbose']:
        print '[DEBUG]: {0}'.format(msg)

#####
# Begin Script
#####
emailto = args['dest_email']
if emailto is None:
    class_arg = raw_input('2230(a) or 3240(b)?: ')
    emailto = class_emails.get(class_arg, None)
    if emailto is None:
        print 'Invalid option, please enter a or b'
        exit(1)
debug('set target email to {0}'.format(emailto))

emailfrom = raw_input('Enter your wmich email: ')
username = raw_input('Enter your Bronco NET ID: ')

#####
# Validate username and password
#
# Invalidate the smtp session after we validate the user session
# leaving a connection open during work would be a bad idea
#####
ct = 0
while True:
    if ct == MAX_PASSWORD_ATTEMPTS:
        print 'Authentication failed'
        server.quit()
        exit(1)

    password = getpass.getpass('Enter your wmich password: ')
    server = smtplib.SMTP("smtp.wmich.edu:587")
    server.starttls()

    try:
        server.login(username,password)
    except SMTPAuthenticationError:
        print 'Incorrect username/password combination, please try again.\
                Attempt {0} of {1}.'.format(ct+1, MAX_PASSWORD_ATTEMPTS)
        ct = ct + 1
        server.quit()
        continue
    server.quit()
    break

debug('successfully validated credentials for user {0}'.format(username))
print 'Working...'

#####
# If there is no default RSA Key, generate one for them
#####
if not os.path.isfile(rsa_key_path) and \
        not os.path.isfile(rsa_pub_key_path):
    debug('default RSA Key does not exist, creating one at {0}'.format(rsa_key_path))
    debug('running command {0}'.format(ssh_keygen_cmd))
    p = subprocess.Popen(ssh_keygen_cmd, shell=True)
    p.wait()

#####
# Create the message mime-type and attach the RSA Key to it
#####
msg = MIMEMultipart()
msg['From'] = emailfrom
msg['To'] = emailto
msg['Subject'] = '[KEYS]'

debug('opening and checking file type of {0}'.format(rsa_pub_key_path))
ctype, encoding = mimetypes.guess_type(rsa_pub_key_path)
if ctype is None or encoding is not None:
    ctype = "application/octet-stream"
maintype, subtype = ctype.split("/", 1)

# check for pub file type
fp = open(rsa_pub_key_path)
# Note: we should handle calculating the charset
attachment = MIMEText(fp.read(), _subtype=subtype)
fp.close()

attachment.add_header('Content-Disposition', 'attachment', filename='id_rsa.pub')
msg.attach(attachment)

#####
# Create smtp session and send the email
#####
debug('creating smtp TLS connection to smtp.wmich.edu')
server = smtplib.SMTP("smtp.wmich.edu:587")
server.starttls()
debug('logging in with student credentials')
server.login(username,password)
debug('sending mail')
server.sendmail(emailfrom, emailto, msg.as_string())
server.quit()
debug('successfully sent mail')

print 'Success!'
