#include "functions.h"
#include <pthread.h>

// Necesary params: sucursal
void* listen_bank(void* par){
	Params* var = (Params*)par;
	while(true){
		read(var->sucursal.pipein[0], var->sucursal.readbufersuc, sizeof(var->sucursal.readbufersuc));
	}
	return NULL;
}


void talk_bank(int pid){
	
}

// Necesary params: suc_array, array_size, sucursal, sucid
void Exec_suc(void* par){
	Params* var = (Params*)par;
	Suc this_sucursal;
	for(int i = 0; i < var->array_size; i++){
		printf("%d, %d\n", var->suc_array[i].ID, var->sucid);
		if(var->suc_array[i].ID == var->sucid){
			printf("holiii\n");
			this_sucursal = var->suc_array[i];
			pthread_create(&var->suc_array[i].listen_thread, NULL, &listen_bank, &var->sucursal);
		}
	}
	while(true){
		if(strcmp(this_sucursal.readbufersuc, "omae wa mou shindeiru") == 0){
			printf("nani!");
			Delete_suc(par);
			 _exit(EXIT_SUCCESS);
		 }
	}
}
