/************ 	Elif Ilaria Yurtseven Programming Project #1 
				I pledge that I did not receive any help for this project 
				*************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h> //for the LS command
#define MAXTOKS 100 //Maximum number of tokens allowed in tokens array

struct name {
  char **tok; 
  int count;
  int status;
};

int read_name(struct name* input, char **envp)
{
	enum status_value { NORMAL, EOF_OR_ERROR, TOO_MANY_TOKENS };

	input -> tok = malloc(MAXTOKS* sizeof(char *));
	char *buffer = NULL;
  	size_t buffsize = 0;
  	size_t chars;

	chars = getline(&buffer, &buffsize, stdin);
	
	int N = 0;
	int N0 = 0;
	int i;
	int j;
	
	for (i = 0; i < chars; i++)
	{
		if (isspace(buffer[i]) || buffer[i] == '\0')
		{
			if(N != 0) //Check if there is a token to allocate
			{
				if (i == '\0')
					N++;
				if(N0 >= MAXTOKS)
				{
					input -> status == TOO_MANY_TOKENS; //Error in case tokens are more than MAXTOKS
					break;
				}
				input -> tok[N0] = malloc((N+1) * sizeof(char));

				for(j = 0; j < N; j++) //loop to copy the tokens
				{
					char cc;
					if(i == '\0')
						cc = buffer[i-N+j+1];
					else
						cc = buffer[i-N+j];
					input -> tok[N0][j] = cc;
				}
				input -> tok[N0][N] = 0;
				N0++;
			}
			N = 0; //skip all spaces
			continue;
		}
		N++;
	}
	input -> count = N0;
	input -> tok[N0+1] = NULL;

	if(chars == -1)
	{
		if (input -> tok[0][0] == -1)
		{
			input -> status = EOF_OR_ERROR; //Check if there is an error in inputting
			printf("There was an error.\n");
		}

	}
	else if (N0 >= MAXTOKS)
	{
		input -> status = EOF_OR_ERROR; //Check if there are too many tokens
		printf("You have entered too many tokens.\n");
	}
	else {
	    input -> status = NORMAL; //If the input was without an error, you can do the following:

	    /*EXTRA FEATURES*/
	    /****Change directory*****/
	    //If you input 'chdir' and then the directory you would like to change to the shell will take you to that directory
	    if(strcmp(input -> tok[0], "chdir") == 0){
	   		chdir(input -> tok[1]); //The shell will take you to the second token tht you have entered please make sure this token is the FULL PATH to the directory you desire to go to
	   //example of FULL PATH : /home/users/yurtse1/OS/pp1
	   	}
	   	/*****LIST FILES IN DIRECTORY*****/
	   	else if (strcmp(input -> tok[0], "ls") == 0){ //if you wish to list all the files in your directory, you can type 'ls' in the shell and that is what you will get
	   		DIR *directory;
    		struct dirent *dir;
    		directory = opendir(".");
    		if (directory)
    		{
        		while ((dir = readdir(directory)) != NULL)
        		{
            		printf("%s\n", dir->d_name);
        		}
        		closedir(directory);
    		}
	    }
	    else if (strcmp(input -> tok[0], "exit") == 0){ //if you wish to exit from the shell, you shal type 'exit'
	    	_exit(0);
	    }
	    /*END OF EXTRA FEATURES*/


	int ret;
	int ret_val;
	/*printf("I am the PARENT.  My pid is %d\n", */getpid();//);

//Forking command for the parent
	if((ret = fork()) < 0) //if forking failes, error message will appear
		{
			printf("fork() FAILED");
			perror("forkeg");
			_exit(1);
		}

	if (ret != 0) { //if forking was successful the child will proceed to do the execve()
    	/*printf("I am the PARENT.  My pid is %d, and fork() returned %d.\n",*/
	   	getpid();//, ret);
	   	wait();


    /* NOTE: parent should ordinarily wait(), to collect child's exit status */
  	} else {
    	/*printf("I am the CHILD.  My pid is %d, and fork() returned %d.\n",*/
	   	getpid();//, ret);
	
	   	if ((ret_val = execve(input -> tok[0], input -> tok, envp)) == -1){ //if child failes at exevce error message will be shown
	   		printf("Could not execute command.");
	   	}
    	_exit(1);
  	}
  	/*printf("I am the PARENT.  My pid is %d, and I'm signing off.\n",*/ getpid();//);


	}
}

  int main(int argc, char **argv, char **envp)
  {
  	int x = 1;
    struct name buffer;
    while (1){
    	read_name(&buffer, envp);
    }
  }