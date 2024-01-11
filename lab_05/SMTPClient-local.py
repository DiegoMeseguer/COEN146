
# Behnam Dezfouli
#  CSEN, Santa Clara University

# This program implements a simple smtp mail client to send an email to a local smtp server

# Note:
# Run a local smtp mail server using the following command before running this code:
# python -m smtpd -c DebuggingServer -n localhost:6000


from socket import *
import ssl


# Choose a mail server
mailserver = 'localhost'


# Create socket called clientSocket and establish a TCP connection with mailserver
clientSocket = socket(AF_INET, SOCK_STREAM)
clientSocket.connect((mailserver, 6000))


# Port number may change according to the mail server
# STUDENT WORK


recv = clientSocket.recv(1024).decode()
print(recv)
if recv[:3] != '220':
    print('220 reply not received from server.')


# Send HELO command along with the server address
heloCommand = 'HELO ' + mailserver + '\r\n'
clientSocket.send(heloCommand.encode())
recv1 = clientSocket.recv(1024).decode()
print("Message after HELO command:" + recv1)
if recv1[:3] != '250':
    print('250 reply not received from server.')



# Send MAIL FROM command and print server response
mail = 'MAIL FROM: <dmeseguersalas@scu.edu>\r\n'
clientSocket.send(mail.encode())
recv2 = clientSocket.recv(1024).decode()
print("Message after MAIL FROM command: " + recv2)
if recv2[:3] != '250':
	print('250 reply not received from server.')



# Send RCPT TO command and print server response
rcpt = 'RCPT TO: <dmeseguersalas@scu.edu>\r\n'
clientSocket.send(rcpt.encode())
recv3 = clientSocket.recv(1024).decode()
print("Message after RCPT TO command: " + recv3)
if recv3[:3] != '250':
	print('250 reply not received from server.')



# Send DATA command and print server response
data = 'DATA\r\n'
clientSocket.send(data.encode())
recv4 = clientSocket.recv(1024).decode()
print("Message after DATA command: " + recv4)
if recv4[:3] != '354':
	print('354 reply not received from server.')



# Send message data.
clientSocket.send('SUBJECT: Greeting To you!\r\n'.encode())
clientSocket.send('This is line 1\n'.encode())
clientSocket.send('This is line 2\n'.encode())
clientSocket.send('\r\n.\r\n'.encode())
recv5 = clientSocket.recv(1024).decode()
print("Message after SENDING DATA: " + recv5)
if recv5[:3] != '250':
	print('250 reply not received from server.')


# Message to send
# STUDENT WORK


# Message ends with a single period
# STUDENT WORK


# Send QUIT command and get server response
quitcommand = 'QUIT\r\n'
clientSocket.send(quitcommand.encode())
recv6 = clientSocket.recv(1024).decode()
print(recv6)
if recv6[:3] != '221':
	print('221 reply not received from server.')














