#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
/* Программа по обработке SIGUSER1 и SIGUSER2 c sigwait()*/
void sighandler(int signo) {
	if(signo == SIGUSR1){
		switch(fork()){
		case -1: printf("Error in fork!"); break;
		case 0: execlp("date","--date=now",NULL); 
		break;
		}
	} else if(signo == SIGUSR2){
		exit(0);
	}
}
int main(int argc, char * argv[]) {
	struct sigaction act;
	sigset_t mask;
	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);
	/* Добавляем в маску те сигналы, которые мы буде блокировать */
	sigaddset(&mask, SIGUSR1);
	sigaddset(&mask, SIGUSR2);
	/* Устанавливаем обработчик для наших сигналов */
	act.sa_handler = sighandler;
	act.sa_mask = mask;
	/* Какие сигналы будем принимать */
	sigaction(SIGUSR1, &act, NULL);
	sigaction(SIGUSR2, &act, NULL);	
	printf("Wait...%d\n",getpid());
	while(1){
		int signo = 0;
		sigwait(&mask,&signo);
		sighandler(signo);
	}
	return 0;
}
