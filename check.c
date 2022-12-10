#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"
#include "ftpcommands.h"
#include "trim.h"

int check_command(char *com)
{
	char **args = split_to_array(com, " ");

	toUP(*args);

	if (!strcmp(*args,"OPEN"))
	{
		if(ftp_open(args))
		{
			ftp_syst();
		}
	}
	else if (!strcmp(*args, "LS"))
	{
		ftp_ls(args);
	}
	else if (!strcmp(*args, "RETR"))
	{
		ftp_retr(args);
	}
	else if (!strcmp(*args, "QUIT"))
	{
		if(ftp_quit())
		{
			return -1;
		}
	}
	else if (!strcmp(*args, "STOR"))
	{
		ftp_stor();
	}
	else if (!strcmp(*args, "PWD"))
	{
		ftp_pwd();
	}
	else if (!strcmp(*args, "DELE"))
	{
		ftp_dele();
	}
	else if (!strcmp(*args, "RMD"))
	{
		ftp_rmd();
	}
	else if (!strcmp(*args, "CWD"))
	{
		ftp_cwd();
	}
	else if (!strcmp(*args, "CDUP"))
	{
		ftp_cdup();
	}
	else if (!strcmp(*args, "MKD"))
	{
		ftp_mkd();
	}
	else if (!strcmp(*args, "HELP"))
	{
		ftp_help();
	}
	else
	{
		printf("Unknown command\nTry HELP\n");
	}
	return 0;
}
//

//
//check for rightness of the ip here for IPv4
//four integer numbers delimited by a dot
//each number ranges between [0, 255]
//param_check index 1
int check_ip(char* ip)
{
	char** args;
	args = split_to_array(ip, ".");

	int sets = is_occupied(args);

	if (sets<4) return 0; 

	//check if is number in range
	for (int i=0; i<4; i++)
	{
		int num = conv_to_num(args[i]);
		if (num<0 || num>255) 
		{
			return 0;
		}
	}
	return 1;
}
//

//Check for port if written correctrly
//an integer number in the range of
//[0, 2^16-1]
//param_check index 2
int check_port(char* port)
{
	int res = conv_to_num(port);
	if (res<0 || res>65535) return 0;
	return res;	
}
//

//Get the list of the files in local current working directory
//compare with the one given as the command parameter
//param_check index 3
int check_local_filename(char* filename)
{
	return 0;
}
//


//some tools function maybe move in 
//different files latter
void toUP(char* comd)
{
	for (int i=0; i<strlen(comd); i++)
	{
		*(comd+i) = toupper(*(comd+i));
	}
}

int is_occupied(char **args)
{
	for (int i=0; i<4; i++)
	{
		if (!strcmp(*(args+i),"")) return i;
	}
	return 4;
}

int conv_to_num(char* str)
{
	//return the converted number
	//if no more that 5 character lenght
	//-1 otherwise
	if (strlen(str)>5) return -1;

	for (int i=0; i<strlen(str); i++)
	{
		if (!isdigit(str[i]))
		{
			return -1;
		}	
	}
	return atoi(str);
}

char**  split_to_array(char* inputstr, const char *ch)
{
	char *token;
	int count=0;
	char** args;
	args = (char**)malloc(sizeof(char*)*4);
	char* str = malloc(sizeof(char)*50);
	strcpy(str, inputstr);
	
	for (int i=0; i<4; i++)
	{
		*(args+i) = malloc(100*sizeof(char));
	}

	token = strtok(str, ch);
	
	while( token != NULL && count<4)
	{
		*(args+count++) = trim(token);
		token = strtok(NULL, ch);	
	}

	return args;
}
