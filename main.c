#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include "child.h"

// Cuenten con este codigo monolitico en una funcion
// main como punto de partida.
// Idealmente, el codigo del programa deberia estar
// adecuadamente modularizado en distintas funciones,
// e incluso en archivos separados, con dependencias
// distribuidas en headers. Pueden modificar el Makefile
// libremente para lograr esto.


int main(int argc, char** argv) {
	size_t bufsize = 512;
	char* commandBuf = malloc(sizeof(char)*bufsize);
	const int bankId = getpid() % 1000;
	Suc* suc_array = calloc(50, sizeof(Suc));
	int array_size = 0;
	Params* par = calloc(1, sizeof(Params));
	par->suc_array = suc_array;
	printf("Bienvenido a Banco '%d'\n", bankId);

	while (true) {
		printf(">>");
		getline(&commandBuf, &bufsize, stdin);

		// Manera de eliminar el \n leido por getline
		commandBuf[strlen(commandBuf)-1] = '\0';

		printf("Comando ingresado: '%s'\n", commandBuf);

		if (!strncmp("quit", commandBuf, strlen("quit"))) {
			break;
		}
		else if (!strncmp("init", commandBuf, strlen("init"))) {
			// OJO: Llamar a fork dentro de un ciclo
			// es potencialmente peligroso, dado que accidentalmente
			// pueden iniciarse procesos sin control.
			// Buscar en Google "fork bomb"
			
			int pipebnk2suc[2] = pipe(&pipebnk2suc);
			int pipesuc2bnk[2] = pipe(&pipesuc2bnk);
			static int N;
			char* n = &commandBuf[4];
			N = atoi(n);
			if(!N) N = 1000;
			
			pid_t sucid = fork()

			if (sucid > 0) {
				printf("%d hiya! 1\n", sucid);
				printf("Sucursal creada con ID '%d' y %d cuentas\n", sucid, N);
				
				array_size++;
				suc_array[array_size - 1] = Init_suc(sucid);
			}
			// Proceso de sucursal
			else if (!sucid) {
				int sucId = getpid() % 1000;
				printf("Hola, soy la sucursal '%d'\n", sucId);
				par->array_size = array_size;
				par->sucid = sucId;
				par->sucursal = Find_suc((void*)par);
				Exec_suc((void*)par);
				//usleep(1000000);
				// 100 milisegundos...
				/*int bytes = read(bankPipe[0], readbuffer, sizeof(readbuffer));
				printf("Soy la sucursal '%d' y me llego mensaje '%s' de '%d' bytes.\n",
				sucId, readbuffer, bytes);*/

				// Usar usleep para dormir una cantidad de microsegundos

				// Cerrar lado de lectura del pipe

				// Para terminar, el proceso hijo debe llamar a _exit,
				// debido a razones documentadas aqui:
				// https://goo.gl/Yxyuxb
				//_exit(EXIT_SUCCESS);
			}
			// error
			else {
				fprintf(stderr, "Error al crear proceso de sucursal!\n");
				return (EXIT_FAILURE);
			}
		}
		else if(!strncmp("list", commandBuf, strlen("list"))){
			for(int i = 0; i < array_size; i++){
				printf("%d, clients amount: %d:", suc_array[i].ID, suc_array[i].clients_amount);
				for(int j = 0; j < suc_array[i].clients_amount; j++){
					printf("%6d ",suc_array[i].accountid[j]);
				}
			printf("\n");
			}
		}
		else if(!strncmp("kill", commandBuf, strlen("kill"))){
			int id = atoi(&commandBuf[4]);
			if(!id){
				printf("El comando ''kill'' debe ser ingresado junto con un id valido.");
			}
			else{
				par->sucid = id;
				Suc dead_sucursal = Find_suc((void*)par);
				if (!dead_sucursal.ID) printf("El comando ''kill'' debe ser ingresado junto con un id valido: id no encontrado.");
				else{
					write(dead_sucursal.pipein[1], "die", 3);
				}
			}
		}
		else {
			fprintf(stderr, "Comando no reconocido.\n");
		}
		// Implementar a continuacion los otros comandos
	}

	printf("Terminando ejecucion limpiamente...\n");
	// Cerrar lado de escritura del pipe

	return(EXIT_SUCCESS);
}
