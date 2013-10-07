//
//  SerialConfig.h
//  Serial GPL
//
//  Created by Pablo Holanda on 27/09/13.
//  Copyright (c) 2013 Pablo Holanda. All rights reserved.
//

#ifndef __Serial_GPL__SerialConfig__
#define __Serial_GPL__SerialConfig__

#include <iostream>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <stdio.h>

#define USB_PORT "/dev/tty.usbmodem1421"
#define BAUDRATE_OUT B115200
#define BAUDRATE_IN B115200
#define BYTE_SIZE 4
#define SINC_TIME 4 

#define BUFSIZE 1024



void SerialConfig(struct termios *stdio, struct termios *tio, struct termios *old_stdio);

void openSerial(int *tty_usb, struct termios *tio);



#endif /* defined(__Serial_GPL__SerialConfig__) */
