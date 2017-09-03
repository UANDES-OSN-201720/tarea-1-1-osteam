# tarea1-1
Tarea 1, parte 1

Nuestra tarea tiene 3 archivos importantes: main.c, fucntions.h y child.h
El archivo functions.h lo escribimos con tal de tener en un solo archivo, separado del main, 
todas las funciones respectivas al proceso del banco. Este tiene 2 structs, el primero suc, el 
cual tiene toda la informacion respectiva a cada sucursal, esto es, su ID, los pipes de entrada
y salida, arreglo de cuentas bancarias, la inicializacion del thread listen_thread que es el que
escucha al banco, etc. El segundo struct es params, el cual contiene los parametros ocupados en 
las funciones para los threads. Esto incluye un arreglo de sucursales, su tamaño, asi como tambien 
un identificador para el ID de una sucursal especifica, etc. 
El archivo functions.h tiene las siguientes funciones:
funcion Find_suc, cuya funcion es encontrar una sucursal.
funcion talk_suc, es la comunicacion entre el banco y la sucursal, donde el banco le manda a la sucursal
un mensaje a traves del pipe asociado
funcion init_suc, la cual inicializa la sucursal

Actualmente las funciones del archivo child.h no estan definidas. Además, las funciones que fueron definidas
en functions.h no estan implementadas en el main.
