import socket
import pygame
import time
msgFromClient = "Hello UDP Server"
length = 400
graph = []
pygame.init()
screen = pygame.display.set_mode((length, 400))
done = False
bufferSize = 2048
UDP_IP = "192.168.0.32"
UDP_PORT = 4210
MESSAGE = "test"
print("UDP target IP:", UDP_IP)
print("UDP target port:", UDP_PORT)
print("message:", MESSAGE)
x = 0
t=0
sock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM) # UDP

sock.sendto(bytes(MESSAGE, "utf-8"), (UDP_IP, UDP_PORT))
msgFromServer = sock.recvfrom(bufferSize)

while not done:
    slope = msgFromServer[0]

    screen.fill((5, 5, 5))
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done = True
    msgFromServer = sock.recvfrom(bufferSize)
    if len(graph) >= length:
       graph.pop(0)
       graph.append(int(msgFromServer[0]))
    else:

       graph.append(int(msgFromServer[0]))

    for x in range(len(graph)-1):
        screen.set_at((x, (graph[x]+2)*100), (255, 255, 255, 255))
    if slope != msgFromServer[0]:
        t = time.clock()-x
        x = time.clock()
        print(t)
    pygame.display.flip()