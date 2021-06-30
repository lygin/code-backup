from socket import *
serverPort=12000
serverSock=socket(AF_INET,SOCK_STREAM)
serverSock.bind(('',serverPort))
serverSock.listen(1)
print("ready to recv!")
while True:
    connectSock, cliAddr=serverSock.accept()
    msg=connectSock.recv(1024).decode()
    modiMsg=msg.upper()
    connectSock.send(modiMsg.encode())
    connectSock.close()

