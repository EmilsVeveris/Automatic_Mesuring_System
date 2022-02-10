#ifndef COMMANDS_H
#define COMMANDS_H

#include <stdio.h>
#include <stdlib.h>

#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <math.h> 


#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
char Volt_Rez[20];
char Amper_Rez[20];
char Frequency_Rez[20];
char Torque_Rez[20];
char RPM_Rez[20];

short measure(int sock);
double get_double_from_char();

#endif
