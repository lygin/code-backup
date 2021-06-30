from socket import *
serverName='127.0.0.1'
serverPort=12000
cliSocket=socket(AF_INET, SOCK_DGRAM)
msg=input('input msg:')
cliSocket.sendto(msg.encode(),(serverName,serverPort))
rtnMsg, serverAddr=cliSocket.recvfrom(2048)
print(rtnMsg.decode())
cliSocket.close()