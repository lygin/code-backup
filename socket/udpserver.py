from socket import *
serverPort=12000
serverSocket=socket(AF_INET,SOCK_DGRAM)
serverSocket.bind(('',serverPort))
print("ready!")
while True:
    msg, cliAddr = serverSocket.recvfrom(2048)
    modifyMsg = msg.decode().upper()
    serverSocket.sendto(modifyMsg.encode(), cliAddr)