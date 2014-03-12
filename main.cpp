#include <unistd.h>
#include <sys/wait.h>

#include "Outils.h"
#include "Clavier.h"
#include "Entree.h"


int main() {
	InitialiserApplication(XTERM);
	//sleep(10);
	pid_t noClavier, noEntree;


	if ( ( noClavier = fork()) == 0 )
	{
	    Clavier();
	}
	else if ( (noEntree = fork()) == 0)
	{
	    Entree();
	}
        else
	{
                Afficher(MESSAGE, "Test");
		waitpid(noClavier, NULL, 0);
		TerminerApplication();
		exit(0);

	}
    return 0;
}
