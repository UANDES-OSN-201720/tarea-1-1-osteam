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

A la hora de trabajar con el comando init, tuvimos varios problemas en el camino, desde asignación de memoria con
malloc, hasta problemas con la creación de una segunda sucursal. Uno de los grandes problemas que tuvimos con esto
fue al momento de crear un segundo proceso hijo, donde nuestro programa se caía, pero solo el proceso padre, y los 
hijos, es decir, las sucursales, seguían en funcionamiento. Una vez solucionado esto, el nuevo problema al cual nos
enfrentamos fue respecto a las cuentas asociadas. Nos ocurrió que las cuentas, asi como también la cantidad de estas
de cada sucursal, se reescribían en la memoria de la primera sucursal. Es decir, la primera sucursal quedaba con una cantidad
determinada de clientes, mientras que las demás sucursales no tenían presencia de clientes. Decidimos, para ahorrar
mayores problemas, en lugar de usar un realloc para modificar el tamaño del arreglo, hicimos un arreglo de tamaño
fijo. Con esto solucionamos parcialmente el problema, dado que nuestro objetivo era intentar ocupar el realloc.

El comando quit termina todos los procesos activos, tanto el proceso padre, el cual es la oficina matriz, también llamado
banco, como los procesos hijos, los cuales serían cada una de las sucursales existentes.

El comando kill funciona de manera intuitiva. Es cosa de ingresar el comando, seguido del ID de la sucursal que se 
quiere terminar, y lo que logra el comando es eliminar la sucursal del array de sucursales, así como también matar
el proceso. Kill manda un mensaje desde el banco hasta una sucursal, entregándole la instrucción "die", lo que hace que este 
proceso se elimine por su cuenta, y no que un proceso externo lo elimine.

Al igual que kill, list tiene un funcionamiento bastante simple. Lo que hace es listar la lista de sucursales
que existen hasta ese momento, junto con las cuentas asociadas a cada una de esas sucursales.

  

##Actualmente las funciones del archivo child.h no estan definidas. Además, las funciones que fueron definidas
##en functions.h no están implementadas en el main.c
