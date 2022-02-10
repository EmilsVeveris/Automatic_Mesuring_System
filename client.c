#include <stdio.h> 
#include <time.h>
#include "socket.h"
#include "commands.h"
#include <signal.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>


static volatile int keepRunning = 1;

void intHandler(int dummy) {
    keepRunning = 0;
}
int main()
{
	signal(SIGINT, intHandler);

	setlocale(LC_NUMERIC, "French_Canada.1252");

 	time_t curtime;
	int sock;
	int server;
 	int plotter;   
	int port1 = 1234;
	int count = 0;
  	//char *ip1 = "10.0.4.163";
	char ip1 [255];
	//char *ip1 = "127.0.0.1";
	FILE *file;
	char buffer [255];
	time_t rawtime;
	char * dot;
	char * dot1;

	double Volts = 0;
	double Amps = 0;
	double Frequency = 0;
	double Torque = 0;
	double RPM = 0;
	int max = 0, min_v = 1;

	unsigned char a,b,c,d;
	printf("Ievadiet GPIB IP adresi\n");
    scanf("%hhu.%hhu.%hhu.%hhu", &a,&b,&c,&d);

    printf("Ievadita IP adrese %hhu.%hhu.%hhu.%hhu\n", a, b, c, d);
	sprintf(ip1,"%hhu.%hhu.%hhu.%hhu", a, b, c, d);

	client_prg(ip1, port1, &sock);

	time (&rawtime);
	sprintf(buffer,"%s.txt",ctime(&rawtime) );


	char *p = buffer;
	for (; *p; ++p)
	{
		if (*p == ' ')
			*p = '_';
	}



	printf("%s\n",buffer);
	file = fopen(buffer,"w");
	fprintf(file, "Laiks:HH:MM:SS\tNR:\tPretestība (Ω)\t\tSpriegums(V)\t\tStrāva(A)\t\t\tFrekvence(Hz)\t\t\tGriezes_Moments(N*m)\t\t\tApgrizieni(RPM)\n");

	init(sock);
	

	while(keepRunning)
	{
		char command [255];
		char *read = "R";
		char *exit = "E";
		double resistance = 0;
		int n = 10; 
		double delay = 0;
		int i = 0;

		printf("\nIevadiet Komandu: R - Datu lasīšana, E - Lai izietu no programmas :");
		scanf(" %s", &command);

			
		if (strcmp(command,read) == 0)
		{
			time_t now;
			struct tm *now_tm;
			int hour, min, sec;

			
			
			printf("\nIevadiet Pretestību (Ω):");
			scanf(" %lf", &resistance); 
			printf("\n");
			for( i = 0; i < n; i++)
			{
				now = time(NULL);
				now_tm = localtime(&now);

				hour = now_tm->tm_hour;
				min = now_tm->tm_min;
				sec = now_tm->tm_sec;
				
				printf("%d. Mērijums\n", i);
				measure(sock);


				Volts = get_double_from_char(Volt_Rez);
				Amps = get_double_from_char(Amper_Rez);
				Frequency = get_double_from_char(Frequency_Rez);
				Torque = get_double_from_char(Torque_Rez);
				RPM = get_double_from_char(RPM_Rez);
	
				Torque = (Torque/5);
				RPM = ((RPM/4)*60);

				fprintf(file, "Laiks:%02d:%02d:%02d\t%02d\t%8lf \t\t%11.3lf \t\t%11lf \t\t%10.2lf \t\t%9.3lf \t\t%9.3lf \n",hour,min,sec,count, resistance, Volts, Amps, Frequency, Torque, RPM);
				
				count++;
				
				
				printf("Volts = %lf\n", Volts);
				printf("Ampers = %lf\n", Amps);
				printf("Frequency = %lf\n", Frequency);
				printf("Torque mesurment = %lf\n", Torque);
				printf("Frequency for RPM mesurment = %lf\n", RPM);
				
				sleep(delay);
			}
			max = min_v + n;
			fprintf(file, "Laiks:%02d:%02d:%02d\t%02d\t=AVRAGE(C%d:C%d)\t\t=AVRAGE(E%d:E%d)\t\t=AVRAGE(G%d:G%d)\t\t=AVRAGE(I%d:I%d)\t\t=AVRAGE(K%d:K%d)\t\t=AVRAGE(M%d:M%d)\n",hour,min,sec,count, min_v, max, min_v, max, min_v, max, min_v, max, min_v, max, min_v, max);
			fprintf(file, "\n\n");
			printf("\nMērijumu_Beigas!\n\n");
			min_v = max + 3;
		}
		else if (strcmp(command,exit) == 0)
		{
			    
			close_socket(&sock);
			fclose(file);
			return 0;
		} 
		else 
		{
			printf("\nIevadīta nepareiza komanda\n");
		}
				
		

	}
    
	close_socket(&sock);
	fclose(file);
	return 1;
    
}
      
      
