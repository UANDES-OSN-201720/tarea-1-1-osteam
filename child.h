#include "functions.h"


void Exec_suc(int pid){
	
}

void talk_bank(int pid){
	
}

// Necesary params: sucursal
void* listen_bank(void* par){
	Params* var = (Params*)par;
	read(var->sucursal.pipein[0], var->sucursal.readbufersuc, sizeof(var->sucursal.readbufersuc));
	return NULL;
}
