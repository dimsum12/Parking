#include <unistd.h>
#include <sys/wait.h>

#include "Outils.h"


int main() {
	InitialiserApplication(XTERM);
	//sleep(10);
	pid_t noFils;
	if ( /* ( noFils = fork()) == 0 */ )
	{
		//Clavier();
	} else
	{
		//waitpid(noFils, NULL, 0);
		//TerminerApplication();
		//exit(0);

	}
    return 0;
}
