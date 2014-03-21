import pygame, sys
import serial
import time
from pygame.locals import *
import curses
 
white = (255, 255, 255)

ser = serial.Serial('/dev/tty.usbmodem1411', 115200)
 
pygame.init()
pygame.display.set_caption('Monster Truck')
size = [430, 480]
screen = pygame.display.set_mode(size)
clock = pygame.time.Clock()

#Carregar os incones
cima = pygame.image.load("/Users/pholanda/Dropbox/UFRN/2014.1/Robotica Experimental/Incones para interface/Cima.png")
baixo = pygame.image.load("/Users/pholanda/Dropbox/UFRN/2014.1/Robotica Experimental/Incones para interface/Baixo.png")
direita = pygame.image.load("/Users/pholanda/Dropbox/UFRN/2014.1/Robotica Experimental/Incones para interface/Direita.png")
esquerda = pygame.image.load("/Users/pholanda/Dropbox/UFRN/2014.1/Robotica Experimental/Incones para interface/Esquerda.png")
 
# by default the key repeat is disabled
# call set_repeat() to enable it
#pygame.key.set_repeat(50, 50)
 
while True:
    
    screen.fill(white)
    screen.blit(cima,(150,100))
    screen.blit(baixo,(150,250))
    screen.blit(direita,(240,175))
    screen.blit(esquerda,(65,175))
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            pygame.quit()
            sys.exit()
            ser.close()
        #Confere a tecla que foi pressionada
        if event.type == pygame.KEYDOWN:
            if event.key == pygame.K_LEFT:
                ser.write('L')
                screen.blit(esquerda,(30,175))
                #print ser.readline()
            if event.key == pygame.K_RIGHT:
                ser.write('R')
                screen.blit(direita,(280,175))
            if event.key == pygame.K_UP:
                ser.write('U')
                screen.blit(cima,(150,70))
            if event.key == pygame.K_DOWN:
                ser.write('D')
                screen.blit(baixo,(150,280))
            if event.key == pygame.K_ESCAPE:
                pygame.quit()
                sys.exit()
                ser.close()
        else:
            ser.write('S')
            print "Pareeiiiiiiii...."
 
    pygame.display.flip()
    clock.tick(10)