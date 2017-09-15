#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

const unsigned int STRING_SIZE = 80;

typedef struct{
	int ID;
	int pipein[2];
	int pipeout[2];
	char* readbuferbnk;
} Suc;

typedef struct{
	int sucid;
	int array_size;
	int clients;
	Suc* suc_array;
	Suc sucursal;
	char* msg;
}Params;

// Allocates memory for the structure and all it's components.
Suc* Init_suc(int id){
	Suc* sucursal = calloc(50, sizeof(Suc));
	sucursal->ID = id;
	sucursal->readbuferbnk = malloc(sizeof(char) * STRING_SIZE);
	Suc
}

// Deallocates the memory for the specific sucursal.
void Delete_suc(Suc** sucursal){
	free((*sucursal->readbuferbnk));
	free(*sucursal);
	*sucursal = NULL;
}

Suc Find_suc(int suc_id, Suc* suc_array, int array_size){
	for(int i = 0; i < array_size; i++){
		if(suc_array[i].ID == sucid){
			return suc_array[i];
		}
	}
	return NULL;
}

// Necesary params: sucursal, msg
 Talk_suc(int sucid, char* msg){
	Params* var = (Params*)par;
	write(var->sucursal.pipein[1], var->msg, strlen(var->msg)+1);
	return NULL;
}







