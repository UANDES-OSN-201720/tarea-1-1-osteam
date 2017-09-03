# tarea1-1
Tarea 1, parte 1

Nuestra tarea tiene 3 archivos importantes: main.c, fucntions.h y child.h
El archivo functions.h lo escribimos con tal de tener en un solo archivo, separado del main, 
todas las funciones respectivas al proceso del banco. Este tiene 2 structs, el primero suc, el 
cual tiene toda la información respectiva a cada sucursal, esto es, su ID, los pipes de entrada
y salida, arreglo de cuentas bancarias, la inicialización del thread listen_thread que es el que
escucha al banco, etc. El segundo struct es params, el cual contiene los parametros ocupados en 
las funciones para los threads. Esto incluye un arreglo de sucursales, su tamaño, asi como también 
un identificador para el ID de una sucursal específica, etc. 
El archivo functions.h tiene las siguientes funciones:
función Find_suc(), cuya función es encontrar una sucursal.
función Talk_suc(), es la comunicación entre el banco y la sucursal, donde el banco le manda a la sucursal
un mensaje a través del pipe asociado
función Init_suc(), la cual inicializa la sucursal

La función Init_suc() se implementa a la hora de inicializar la sucursal en el main.c. Se inicializa cuando el
usuario ingresa en la consola el comando "init". Esto crea una nueva sucursal, con sus atributos respectivos.
Cabe notar que el usuario puede inicializar una sucursal con una cantidad definida de cuentas. En caso de que 
el usuario no ingrese esta cantidad, por defecto se le entregarán 1000 cuentas a dicha sucursal.

##Actualmente las funciones del archivo child.h no estan definidas. Además, las funciones que fueron definidas
##en functions.h no están implementadas en el main.c
