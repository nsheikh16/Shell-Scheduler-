#include "tsh.h"
#include <sys/wait.h>

using namespace std;

void simple_shell::parse_command(char* cmd, char** cmdTokens) {
  // TODO: tokenize the command string into arguments
	int j = 0;
	cmd[strlen(cmd) - 1] = '\0';
	char *tok =strtok(cmd," ");

	while (tok != NULL){
		cout << tok;
		cmdTokens[j]=tok;
		j++;
		tok = strtok(NULL," ");
	}
	
	cmdTokens[j]=NULL;

}

void simple_shell::exec_command(char **argv)
{
  // TODO: fork a child process to execute the command.
  // parent process should wait for the child process to complete and reap it
	int rc =fork();

	if (rc < 0) {
		
		exit(1);
	}
	else if (rc == 0){ //child 
		execvp(argv[0],argv);
		
		exit(1);
	}
	else{
		
		int w = wait(NULL);
	}
}

bool simple_shell::isQuit(char *cmd){

	if(strcmp(cmd,"quit")==0){
		return true;
	}
	else{
		return false;
	}
  // TODO: check for the command "quit" that terminates the shell
}
