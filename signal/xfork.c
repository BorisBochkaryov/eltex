#include <stdio.h>
#include <signal.h>

/* программа для порождения группы процессов с общим родителем */
int main(){
	switch(fork()){
	case -1: printf("Error in fork()"); break;
	case 0: break; // дочерний 
	default:{ // родитель 
		switch(fork()){
		case -1: printf("Error in fork()"); break;
		case 0: break; // дочерний
		default:{ // родитель
			switch(fork()){
			case -1: printf("Error in fork()"); break;
			case 0: break; // дочерний
			default:{ // родитель
				if(fork() == -1)
					printf("Error in fork()");
			} break;
			}
		} break;
		}
	} break;
	}
	printf("My pid %d in group %d from parent %d\n",getpid(),getpgrp(),getppid());
	while(1) sleep(1);
	return 0;
}
