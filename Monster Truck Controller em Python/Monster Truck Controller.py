import pygame, sys
import serial
import time
from pygame.locals import *
import curses
 
white = (255, 255, 255)

#Cria um objeto com a configuracao da porta serial
#ser = serial.Serial('/dev/tty.usbmodem1411', 115200)
ser = serial.Serial('/dev/tty.HC-06-DevB', 9600)
 
pygame.init()
pygame.display.set_caption('Monster Truck') #Nome da janela do programa
size = [430, 480] #Tamanho da janela do programa
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
    
    screen.fill(white) #Preeche a tela com branco
    screen.blit(cima,(150,100)) #Insere o incone na tela na posicao determinada (x,y)
    screen.blit(baixo,(150,250))
    screen.blit(direita,(240,175))
    screen.blit(esquerda,(65,175))
    
    for event in pygame.event.get():
        if event.type == pygame.QUIT: #Se fechar a janela no botao X
            pygame.quit()
            sys.exit()
            ser.close()
        #Confere a tecla que foi pressionada
        if event.type == pygame.KEYDOWN: #Detecta quando a tecla e pressionada K_1
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
            if event.key == pygame.K_1:
                ser.write('1')
            if event.key == pygame.K_2:
                ser.write('2')
            if event.key == pygame.K_3:
                ser.write('3')
            if event.key == pygame.K_4:
                ser.write('4')
            if event.key == pygame.K_5:
                ser.write('5')
            if event.key == pygame.K_6:
                ser.write('6')
            if event.key == pygame.K_7:
                ser.write('7')
            if event.key == pygame.K_8:
                ser.write('8')
        else:
            ser.write('S')
 
    pygame.display.flip()
    clock.tick(10)