
# Behnam Dezfouli
# CSEN, Santa Clara University

# This program implements a simple web server that serves html and jpg files

# Input arguments:
# argv[1]: Sever's port number


from socket import *  # Import socket module
import sys            # To terminate the program


if __name__ == "__main__":

    # check if port number is provided
    if len(sys.argv) != 2:
        print('Usage: python %s <PortNumber>' % (sys.argv[0]))
        sys.exit()

    portNumber = int(sys.argv[1])
    
    # Create socket
    serverSocket = socket(AF_INET, SOCK_STREAM)
    serverSocket.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
    
    # Bind socket to host and port
    serverSocket.bind(('localhost', portNumber))


    # Start to Listen
    serverSocket.listen(5)    
    # STUDENT WORK

    # Server should be up and running and listening to the incoming connections
    while True:
        print('The server is ready to respond to incoming requests...')

        (clientSocket, address) = serverSocket.accept()
        # STUDENT WORK

        request = clientSocket.recv(1024).decode()
        print(request)
        
        requestList = request.split()
        temp = requestList[1]
        file_extension = temp[temp.find('.') + 1:]        
        print(file_extension)

        try:

            # STUDENT WORK

            if (file_extension == 'html'):
                f = open("index.html", "r")
                message = f.read()
                # print(message)
                # response_headers = { 'Content-Type': 'text/html; encoding=utf8' }
                response = "HTTP/1.1 200 OK\nContent-Type: text/html; encoding=utf8\nContent-Length: 195\n\n";                      finalResponse = response + message
                # print(finalResponse)
                clientSocket.sendall(finalResponse.encode())
    
            elif (file_extension == 'jpg'):
                f = open("img.jpg", "rb")

                message = f.read()
                # myString = message.decode(encoding='utf8')
                # print(type(myString))
                # print(len(message))
                response = "HTTP/1.1 200 OK\nContent-Type: image/jpeg; encoding=utf8\nContent-Length: 329831\n\n";  
                # finalResponse = response + message
                clientSocket.sendall(response.encode())
                clientSocket.sendall(message)

                # response_headers = { 'Content-Type': 'image/jpeg; encoding=utf8' }
            else:
                print('Invalid file type, we only support html and jpg!')
                continue
            

        
            
            # STUDENT WORK


            
            
        #Raised when an I/O operation (such as a print statement, the built-in open() function or a method of a file object) fails for an I/O-related reason, e.g., "file not found" or "disk full"
        except IOError:
            print("404 Error")


# STUDENT WORK

