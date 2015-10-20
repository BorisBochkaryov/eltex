#include <stdio.h>
#include <signal.h>
/* программа для отправки сигнала группе процессов */
int main(int argc, char* argv[]){
	int sig, gr;
	sscanf(argv[1],"%d",&sig);
	sscanf(argv[2],"%d",&gr);
	if(killpg(gr,sig) == -1)
		printf("Error in killpg()");
	return 0;
}
