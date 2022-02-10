#include "commands.h"


	char VOLTmeter_addr[] = "++addr 1\n";
	char Ampermeter_addr[] = "++addr 2\n";
	char Frequency_addr[] = "++addr 3\n";
	char Tourque_addr[] = "++addr 4\n";
	char RPM_addr[] = "++addr 5\n";


short init(int sock)
{

	char init_VOLTmeter[] = "VAC; range 3\n";
	char init_Ampermeter[] = "AAC; range 3\n";
	char init_Frequency[] = "FREQ; range 3\n";
	char init_Tourque[] = "VDC; range 3\n";
	char init_RPM[] = "FREQ; range 3\n";



    //Init first multimeter as a voltmeter(AC)
	send(sock, VOLTmeter_addr, sizeof(VOLTmeter_addr)-1, 0); 
  	send(sock, init_VOLTmeter, sizeof(init_VOLTmeter)-1, 0); 

    //Init second multimeter as a ampermeter
	send(sock, Ampermeter_addr, sizeof(Ampermeter_addr)-1, 0); 
  	send(sock, init_Ampermeter, sizeof(init_Ampermeter)-1, 0); 

    //Init third multimeter for frequency
	send(sock, Frequency_addr, sizeof(Frequency_addr)-1, 0); 
  	send(sock, init_Frequency, sizeof(init_Frequency)-1, 0); 
	
	//Init fourth multimeter as a voltmeter(DC)
	send(sock, Tourque_addr, sizeof(Tourque_addr)-1, 0); 
  	send(sock, init_Tourque, sizeof(init_Tourque)-1, 0); 

    //Init fifth multimeter for frequency to measure rpm 
	send(sock, RPM_addr, sizeof(RPM_addr)-1, 0); 
  	send(sock, init_RPM, sizeof(init_RPM)-1, 0); 
	 
     
    
    return 0;
}
short measure(int sock)
{
	
	




// Do stuff  here




	char read[] = "val?\n";


    struct timeval start, stop;
	double secs = 0;

	gettimeofday(&start, NULL);

  	send(sock, VOLTmeter_addr, sizeof(VOLTmeter_addr)-1, 0); 
	sleep(0.001);
  	send(sock, read, sizeof(read)-1, 0);
	recv(sock, Volt_Rez, sizeof(Volt_Rez)-1, 0);

	gettimeofday(&stop, NULL);
	secs = (double)(stop.tv_usec - start.tv_usec) / 1000000 + (double)(stop.tv_sec - start.tv_sec);
	printf("time taken %f\n",secs);

    //Amper measurment
	send(sock, Ampermeter_addr, sizeof(Ampermeter_addr)-1, 0);
	sleep(0.001);
    send(sock, read, sizeof(read)-1, 0);
	recv(sock, Amper_Rez, sizeof(Amper_Rez)-1, 0);

	//Frequency mesurment
  	send(sock, Frequency_addr, sizeof(Frequency_addr)-1, 0); 
	sleep(0.001);
  	send(sock, read, sizeof(read)-1, 0);
	recv(sock, Frequency_Rez, sizeof(Frequency_Rez)-1, 0);
	
	
	//Voltmeter for torque
	send(sock, Tourque_addr, sizeof(Tourque_addr)-1, 0); 
	sleep(0.001);
  	send(sock, read, sizeof(read)-1, 0);
	recv(sock, Torque_Rez, sizeof(Torque_Rez)-1, 0);
	
	
	//Frequency for RPM
	send(sock, RPM_addr, sizeof(RPM_addr)-1, 0); 
	sleep(0.001);
  	send(sock, read, sizeof(read)-1, 0);
	recv(sock, RPM_Rez, sizeof(RPM_Rez)-1, 0);
	

	

	printf("Volts = %s", Volt_Rez);
	printf("Ampers = %s", Amper_Rez);
	printf("Frequency = %s", Frequency_Rez);
	printf("Torque mesurment = %s", Torque_Rez);
	printf("Frequency for RPM mesurment = %s", RPM_Rez);


    	
    	
    
    return 0;
}

double get_double_from_char(char string[255])
{
	
	char temp[255];
	char temp2[255];
	int i = 0;
	int i2 = 0;

	double number = 0, powerr = 0;
	// Finding all number before E
	while (string[i] != 'E')
	{
		
			temp[i] = string[i];
			i++;
		
	}
	// Finding all Numberrs after E
	i++;
	while(string[i] != '\0')
	{
		temp2[i2] = string[i];
		i++;
		i2++;
	}
	
	//Changing from char to double
	number = atof(temp);
	powerr = atof(temp2);	
	
	
	// calculating end result

	
	number = number * (pow (10, powerr));
	

	return number;
	
}
    
    

