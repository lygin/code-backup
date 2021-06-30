from socket import *
serverName='127.0.0.1'
serverPort=12000
cliSock=socket(AF_INET,SOCK_STREAM)
cliSock.connect((serverName,serverPort))
msg=input("input msg:")
cliSock.send(msg.encode())
rtn=cliSock.recv(1024)
print('From Server:', rtn.decode())
cliSock.close()