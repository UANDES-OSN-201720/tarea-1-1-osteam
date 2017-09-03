#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>


typedef struct{
	int ID;
	int pipein[2];
	int pipeout[2];
	pthread_t listen_thread;
} suc;

typedef struct{
	int sucid;
	int array_size;
	suc* suc_array;
	suc sucursal;
	char* msg;
}Params;

suc Find_suc(void* par/* suc* suc_array, int size_suc_array, int sucid */){
	Params* var = (Params*)par;
	for(int i = 0; i < var->array_size; i++){
		if(var->suc_array[i].ID == var->sucid){
			return var->suc_array[i];
		}
	}
	suc sucursal;
	sucursal.ID = 0;
	return sucursal;
}

void Talk_suc(void* par/*suc sucursal, char* msg*/){
	Params* var = (Params*)par;
	write(var->sucursal.pipein[1], var->msg, strlen(var->msg)+1);
}

void Init_suc(void* par/*suc* suc_array, int size_suc_array*/){
	Params* var = (Params*)par;
	var->suc_array = realloc(var->suc_array, var->array_size);
}
