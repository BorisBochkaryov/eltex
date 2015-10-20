#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>
void sighandler(int signo) {
	printf("ok");
}
/* Программа для блокирования сигналов SIGINT и SIGTERM */
int main(int argc, char * argv[]) {
	struct sigaction act;
	sigset_t mask;
	/* Добавляем в маску те сигналы, которые мы буде блокировать */
	sigaddset(&mask, SIGINT);
	sigaddset(&mask, SIGTERM);
	/* Устанавливаем обработчик для наших сигналов */
	act.sa_handler = sighandler;
	act.sa_mask = mask;
	/* Какие сигналы будем принимать */
	sigaction(SIGINT, &act, NULL);
	sigaction(SIGTERM, &act, NULL);
	/* Блокируем доставку сигналов */
	sigprocmask(SIG_BLOCK, &mask, NULL);

	printf("Wait...%d\n",getpid());
	while(1) sleep(1);
	return 0;
}
