#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/signal.h>

/* Программа для примера буфиризации, объединения и сортировки сигналов */
/* Максимальное число сигналов, которые можно принять */
#define MAX_SENDED_SIGS 10
/* Массив, в который записываются номера принятых сигналов */
int rec_sig[MAX_SENDED_SIGS];
/* Следующий свободный для записи элемент в массиве */
unsigned int nfree_elem = 0;
/* Обработчик сигнала заносит номер принятого сигнала в массив */
void sighandler(int signo) {
	rec_sig[nfree_elem++] = signo;
	return;
}

int main(int argc, char * argv[]) {
	sigset_t mask;
	struct sigaction act;
	int i;

	memset(&act, 0, sizeof(act));
	sigemptyset(&mask);

	/* Добавляем в маску те сигналы, которые мы буде принимать */
	sigaddset(&mask, SIGUSR2);
	sigaddset(&mask, SIGHUP);
	sigaddset(&mask, SIGUSR1);

	/* Устанавливаем обработчик для наших сигналов */
	act.sa_handler = sighandler;
	act.sa_mask = mask;
	sigaction(SIGUSR2, &act, NULL);
	sigaction(SIGHUP, &act, NULL);
	sigaction(SIGUSR1, &act, NULL);

	/* Блокируем доставку наших сигналов, чтобы избежать их немедленной доставки */
	sigprocmask(SIG_BLOCK, &mask, NULL);

	/* Отправляем сигналы */
	raise(SIGUSR2);
	raise(SIGHUP);
	raise(SIGUSR2);
	raise(SIGHUP);
	raise(SIGUSR1);
	raise(SIGUSR1);

	/* Разблокируем сигналы – все сигналы приходят одновременно */
	sigprocmask(SIG_UNBLOCK, &mask, NULL);

	/* Выводим на экран список принятых сигналов в порядке их поступления */
	for(i = 0; i < nfree_elem; ++i) {
		if (rec_sig[i] == SIGUSR1) {
			printf("We get SIGUSR1\n");
		} else if (rec_sig[i] == SIGUSR2) {
			printf("We get SIGUSR2\n");
		} else if (rec_sig[i] == SIGHUP) {
			printf("We get SIGHUP\n");
		}
	}
	return 0;
}
