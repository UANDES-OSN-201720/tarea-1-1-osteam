#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

const unsigned int STRING_SIZE = 80;

typedef struct{
	int ID;
	int* pipein;
	int* pipeout;
	char* readbuferbnk;
} Suc;

typedef struct{
	int sucid;
	int array_size;
	int clients;
	int* pipein;
	int* pipeout;
	Suc** suc_array;
	Suc* sucursal;
	char* msg;
}Params;

// Allocates memory for the structure and all it's components.
Suc* Init_suc(int id, int* pipein, int* pipeout){
	Suc* sucursal = calloc(50, sizeof(Suc));
	sucursal->ID = id;
	sucursal->readbuferbnk = malloc(sizeof(char) * STRING_SIZE);
	sucursal->pipein = pipein;
	sucursal->pipeout = pipeout;
	return sucursal;
}

// Deallocates the memory for the specific sucursal.
void Delete_suc(Suc** sucursal){
	free((*sucursal)->readbuferbnk);
	free(*sucursal);
	*sucursal = NULL;
}

Suc Find_suc(int suc_id, Suc* suc_array, int array_size){
	for(int i = 0; i < array_size; i++){
		if(suc_array[i].ID == suc_id){
			return suc_array[i];			
		}
	}
	Suc sucursal;
	sucursal.ID =0;
	return sucursal;
}

// Necesary params: sucursal, msg
void Talk_suc(int sucid, char* msg, Suc* array, int array_size){
	Suc sucursal = Find_suc(sucid, array, array_size);
	write(sucursal.pipein[1], msg, strlen(msg)+1);
}

void* Listen_suc(void* par){
	Params* var = (Params*)par;
	char* bufer;
	printf("holaa\n");
	while(true){
		for(int i = 0; i < var->array_size; i++){
			if(&var->suc_array[i] != NULL){
				bufer = var->suc_array[i]->readbuferbnk;
				read(var->suc_array[i]->pipein[0], bufer, sizeof(bufer));
				if(strcmp(bufer, "NANI!?") == 0){ 
					Delete_suc(&var->sucursal);
				}
			}
		}
	}
	return NULL;
}


void create_csv(char *filename, char* columns, /*int *trans,*/ int cols, int rows){//estado de prueba
	printf("\n Creando respaldo...");
	FILE *dump;
	filename = strcat(filename, ".csv");
	dump = fopen(filename, "w+");
	fprintf(dump, "%s", columns);
	for (int i = 0; i< rows; i++){
		fprintf(dump, "\n");
		for (int j = 0; j < cols; j++){
			//fprintf(dump,"%d, ", *(trans+i*rows+j));
		}
	}
	if (strcmp(columns, "tipo de transaccion, medio de origen, cuenta de origen, cuenta de destino")){
		fprintf (dump, "\n Tipos de transacciones\n 1: Deposito\n 2: Retiro");
	}
	else if (strcmp(columns, "tipo de error, numero de cuenta, saldo previo, monto a retirar")){
		fprintf (dump, "\n Tipos de errores\n 1: Falta de saldo\n 2: Numero de cuenta invalido");
	}
	fclose(dump);
	printf("\n Respaldo creado con nombre %s", filename);
}








