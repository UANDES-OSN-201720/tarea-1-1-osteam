#include "functions.h"
#include <pthread.h>
#include <signal.h>

// Necesary params: sucursal
void* listen_bank(void* par){
	Params* var = (Params*)par;
	char* readbufer = calloc(STRING_SIZE, sizeof(char));
	while(true){
		read(var->pipein[0], &readbufer, sizeof(readbufer));
		if(strcmp(readbufer, "omaewa mo shindeiru") == 0){
			write(var->pipeout[1], "NANI!?", 6);
			kill(0, SIGTERM);
		}
	}
	return NULL;
}

void* write_bank(void* par){
	Params* var = (Params*)par;
	char* msg = "nada";
	while(true){
		write(var->pipeout[1], msg, sizeof(msg));
	}
	return NULL;
}

void talk_bank(int pid){
	
}

void Exec_suc(int* pipein, int* pipeout, void* par){
	pthread_t listen_thread;
	pthread_t write_thread;
	Params* var = (Params*)par;
	var->pipein = pipein;
	var->pipeout = pipeout;
	pthread_create(&listen_thread, NULL, &listen_bank, &var);
	pthread_join(listen_thread, NULL);
	pthread_create(&write_thread, NULL, &write_bank, &var);
}


