//
//  Serial.h
//  Projeto PDI
//
//  Created by Pablo Holanda on 15/06/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//

#ifndef Projeto_PDI_Serial_h
#define Projeto_PDI_Serial_h

//
//  oximeter.h
//  ELA Home Care
//
//  Created by Pablo Holanda on 16/05/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//



#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>


#define USB_PORT "/dev/tty.usbmodem1411"
#define BAUDRATE_OUT B57600
#define BAUDRATE_IN B57600
#define BYTE_SIZE 1

void configureOximeter(struct termios *stdio, struct termios *tio, struct termios *old_stdio) {
    
	tcgetattr(STDOUT_FILENO, old_stdio);
    
	memset(stdio, 0, sizeof(stdio));
	stdio->c_iflag = 0;
	stdio->c_oflag = 0;
	stdio->c_cflag = 0;
	stdio->c_lflag = 0;
	stdio->c_cc[VMIN] = 1;
	stdio->c_cc[VTIME] = 0;
	tcsetattr(STDOUT_FILENO, TCSANOW, stdio);
	tcsetattr(STDOUT_FILENO, TCSAFLUSH, stdio);
	fcntl(STDIN_FILENO, F_SETFL, O_NONBLOCK);     // make the reads non-blocking
    
	memset(tio, 0, sizeof(tio));
	tio->c_iflag = 0;
	tio->c_oflag = 0;
	tio->c_cflag = CS8 | CREAD | CLOCAL; // 8n1, see termios.h for more information
	tio->c_lflag = 0;
	tio->c_cc[VMIN] = 1;
	tio->c_cc[VTIME] = 5;
    
}

void openUSB(int *tty_usb, struct termios *tio) {
    
	(*tty_usb) = open(USB_PORT, O_RDWR | O_NOCTTY | O_NDELAY);
    
	if ((*tty_usb) == -1) {
		printf("\nDispositivo USB não pode ser acessado");
		return;
	}
    
	cfsetospeed(tio, BAUDRATE_OUT); // 115200 baud
	cfsetispeed(tio, BAUDRATE_IN);  // 115200 baud
	tcsetattr((*tty_usb), TCSANOW, tio);
    
}




#endif
