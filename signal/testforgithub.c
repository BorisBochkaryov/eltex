#include <stdio.h>
#include <stdlib.h>
#include <signal.h>

/* программа для задания обработчика сигнала через signal() */
void term_handler(int i){  // обработчик сигнала
	printf ("Пришёл сигнал %d\n",i);
}
int main() {
	signal(SIGINT, term_handler); // переопределение
	signal(SIGTERM, SIG_IGN); // игнорирование
	raise(SIGINT); // отправка сигнала самому себе
	printf("Мой pid %i\n", getpid());
	printf("Ожидаем...\n");
	while(1) sleep(1);
	return 0;
}
