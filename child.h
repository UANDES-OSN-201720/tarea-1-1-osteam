#include "functions.h"
#include <pthread.h>
#include <signal.h>

// Necesary params: sucursal
void* listen_bank(void* par){
	Params* var = (Params*)par;
	char* readbufer = calloc(STRING_SIZE, sizeof(char));
	while(true){
		read(var->pipein[0], &readbufer, sizeof(var->msg));
		if(strcmp(readbufer, "die") == 0){
			write(var->pipeout[1], "I died", 6);
			Delete_suc(par);
			kill(0, SIGTERM);
		}
	}
	return NULL;
}


void talk_bank(int pid){
	
}

void Exec_suc(int* pipein, int* pipeout, void* par){
	pthread_t listen_thread;
	Params* var = (Params*)par;
	var->pipein = pipein;
	var->pipeout = pipeout;
	pthread_create(&listen_thread, NULL, &listen_bank, &var);
}


