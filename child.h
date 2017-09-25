#include "functions.h"
#include <pthread.h>
#include <signal.h>

char* kill_command = "omaewa mo shindeiru";
char* dump_command = "respaldo transacciones";
char* accs_command ="respaldo saldos";
char* errs_command = "respaldo errores";
char* columns; //Para los comandos dump, marca los nombres de las columnas
char* filename; //Nombre del archivo que se va a guardar al ocupar un comando dump

// Necesary params: sucursal
void* listen_bank(void* par){
	Params* var = (Params*)par;
	char* readbufer = calloc(STRING_SIZE, sizeof(char));
	while(true){
		read(var->pipein[0], &readbufer, sizeof(readbufer));
		if(strcmp(readbufer, kill_command) == 0){
			write(var->pipeout[1], "NANI!?", 6);
			kill(0, SIGTERM);
		}
		else if(strcmp(readbufer, dump_command) == 0){
			write(var->pipeout[1], "creando respaldo", 6);
			columns = "tipo de transaccion, medio de origen, cuenta de origen, cuenta de destino";
			sprintf(filename, "dump_%d", var->sucid);
			create_csv(filename, columns, /*int *trans,*/ 4, 6);//aun hay que hacer las tablas que se le pasan 4 y 6 numeros de prueba

		}
		else if(strcmp(readbufer, accs_command) == 0){
			write(var->pipeout[1], "creando respaldo", 6);
			columns = "numero de cuenta, saldo";
			sprintf(filename, "dump_accs_%d", var->sucid);
			create_csv(filename, columns, /*int *trans,*/ 2, 6);//aun hay que hacer las tablas que se le pasan 4 y 6 numeros de prueba

		}
		else if(strcmp(readbufer, errs_command) == 0){
			write(var->pipeout[1], "creando respaldo", 6);
			columns = "tipo de error, numero de cuenta, saldo previo, monto a retirar";
			sprintf(filename, "dump_errs_%d", var->sucid);
			create_csv(filename, columns, /*int *trans,*/ 4, 6);//aun hay que hacer las tablas que se le pasan 4 y 6 numeros de prueba

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


