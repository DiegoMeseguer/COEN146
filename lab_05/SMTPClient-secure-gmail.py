
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server
# the program runs the ping command, and emails the result using smtp.gmail.com

# NOTE: Do not forget to allow login from less secure apps in your gmail account. Otherwise gmail will complain about username and password.


import smtplib, ssl
import subprocess


port = 465  # For SSL

email_address = input("Please enter your email address: ")
password = input("Please enter your password: ")
receiver_email = input("Please enter receiver's email address: ")


# ping google.com and save the result
p = subprocess.Popen(['ping', '-c', '2', 'google.com'],stdout=subprocess.PIPE).stdout.read()
#p = check_output(['ping', '-c', '2', 'google.com'])


print('\nNow contacting the mail server...')
s = smtplib.SMTP_SSL('smtp.gmail.com', 465)
s.login(email_address, password)  


print('\nSending email...')


# text = p.as_string()

s.sendmail(email_address, receiver_email, p)

s.quit()



