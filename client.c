#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

#include "trim.h"
#include "check.h"
#include "ftpcommands.h"
#include "ftp_data.h"



//catch and disable function
//of signal SIGINT
//produced by CTRL+C
static volatile sig_atomic_t _;

static void sig_handler()
{

	printf("\b\b  \n");
	printf("ftp--> ");
	fflush(stdout);
}
//

int main(int argc, char *argv[])
{
	(void)_;

	//"disable CTRL+C signal aka SIGINT" function call
	signal(SIGINT, sig_handler);

	//char * variable for storing user input
	char *command;
	command = (char*)malloc(1000*sizeof(char));

	//create structure to store ftp status data
	create_server_status();
	
	while(1)
	{
		//user interface 
		//get string input from stdin
		printf("ftp--> ");
		fgets(command, 1000, stdin);

		//get rid of any before or after spaces
		trim(command);
		

		if(check_command(command)==-1)
		{
			break;
		}	

	}
	printf("Closing the client...\n");
	return 0;	
}
