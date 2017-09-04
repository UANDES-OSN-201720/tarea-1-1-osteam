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

En el archivo child.h existen las siguientes funciones:
función Listen_bank(), la cual lee lo que hay en el pipe que va desde el banco hasta la sucursal.
función Exec_suc(), que crea el thread de la sucursal asociada. Además de esto, ejecuta todas las acciones que la 
sucursal lea a través del pipe de entrada, el cual es el que va desde el banco hasta la sucursal, como por ejemplo 
el comando "kill".
función Talk_bank(), que le escribe al banco a través del pipe que va desde la sucursal hasta el banco.

Debido a la gran cantidad de complicaciones que tuvimos durante el desarrollo de la tarea, más específicamente con respecto
al manejo de las sucursales, no nos dio el tiempo para terminar todo lo que debía ser desarrollado. Dentro de los aspectos que 
no pudimos lograr fueron, por ejemplo, las transacciones bancarias de las sucursales, sean estas depósitos de dinero o 
retiro de dinero. Tampoco logramos completar la comunicación desde la sucursal hasta el banco, dejando la función Talk_bank() en 
blanco. Tampoco desarrollamos los comandos dump, que son los que guardan un archivo .SCV, lo que nos deja con mucho trabajo para 
lo que es la segunda parte de esta primera tarea. Por último, el comando kill creemos que fue hecho de manera correcta, es decir, 
la sucursal efectivamente lee el mensaje a través del pipe, y logra terminar el proceso, pero no logramos eliminarlo 
del array de sucursales.
