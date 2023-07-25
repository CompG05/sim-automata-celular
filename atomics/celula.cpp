#include "celula.h"
void celula::init(double t,...) {
/* Inicialización de Célula */
// El id se obtiene desde el parámetro.
// La configuración inicial se obtiene desde el archivo: '../sim-automata-celular/estado.txt'.
// Del archivo se obtienen:
//		- El estado
//		- Las reglas
//    - El intervalo de tiempo

va_list parameters;
va_start(parameters, t);

// Abrir archivo
std::ifstream archivo;
std::string nombre_archivo = "../sim-automata-celular/estado.txt";

archivo.open(nombre_archivo.data());

if (!archivo.is_open()) {
	std::cerr << "No se pudo abrir el archivo " << nombre_archivo << "\n";
}


// Lectura de filas, columnas y el tablero
std::string buffer;
getline(archivo, buffer);
int filas = buffer[0] - '0';

getline(archivo, buffer);
int columnas = buffer[0] - '0';

std::string tablero = "";
for (int i = 0; i < filas; i++) {
	getline(archivo, buffer);
	tablero += buffer;
}


// Inicializar reglas
getline(archivo, buffer);
n_r_supervivencia = buffer.length();
for (int i = 0; i < n_r_supervivencia; i++)
	r_supervivencia[i] = buffer[i] - '0';

getline(archivo, buffer);
n_r_nacimiento = buffer.length();
for (int i = 0; i < n_r_nacimiento; i++)
	r_nacimiento[i] = buffer[i] - '0';


// Inicializar intervalo
getline(archivo, buffer);
intervalo = atof(buffer.data());

archivo.close();


// Inicializar atributos del estado
id = va_arg(parameters, double);
vecinos_vivos = 0;
estado = 0.0 + (tablero[(int)id] - '0'); // Obtener valor entero, sumarle 0.0 para convertir a double

// En la primera iteración se inicializa la variable vecinos_vivos como la cantidad de vecinos vivos
// Los que tienen estado inicial 'vivo' lo comunican a sus vecinos para que incrementen la variable
// Los que están muertos pasan a la siguiente acción sin comunicar
// Se usará: 0 para comunicar y producir salida, 1 para actualizar
if (estado == 0.0) {
	instante = 1; // Pasar a actualizar
	sigma = intervalo / 2;
} else {
	instante = 0;	// Pasar a comunicar
	sigma = 0;
}

vecindario_cambio = 1;
}
double celula::ta(double t) {
/* TA de la Célula */
// Retorna un valor double, el atributo sigma del estado.
return sigma;
}
void celula::dint(double t) {
/* Delta Interna de Célula */
// Función que determina el siguiente estado de la célula.

// Si el instante es Actualizar
if (instante == 1) {
		
		// Y el vecindario no cambió, entonces salteo el instante Comunicar
    if (!vecindario_cambio)
        sigma = intervalo;
    
    else {
        // Calcular nuevo estado
        double nuevo_estado;
        if (estado == 1) {
            int sobrevive = 0;
            for (int i = 0; i < n_r_supervivencia; i++) {
                if (r_supervivencia[i] == vecinos_vivos) {
                    sobrevive = 1;
                    break;
                }
            }
            nuevo_estado = sobrevive ? 1 : 0;
        } else {
            int nace = 0;
            for (int i = 0; i < n_r_nacimiento; i++) {
                if (r_nacimiento[i] == vecinos_vivos) {
                    nace = 1;
                    break;
                }
            }
            nuevo_estado = nace ? 1 : 0;
        }
        
				// Si el estado no cambió, salteo el instante Comunicar
        if (nuevo_estado == estado)
            sigma = intervalo;
        
				// Si el estado cambió  
        else {
            estado = nuevo_estado;			// Actualizo estado
            sigma = intervalo/2;				// El siguiente instante es Comunicar
            instante = 0;							
        }
    }

		vecindario_cambio = 0;
}

// Si el instante es Comunicar
else {
    sigma = intervalo/2;			// Solo se programa el siguiente Actualizar
    instante = 1;
}
}
void celula::dext(Event x, double t) {
/* Delta externa de la Célula */
// El evento de entrada se encuentra en la variable 'x'.
// donde:
//     'x.value' es el valor (puntero a void).
//							 El puntero contiene una dirección a un arreglo del tipo: [id, estado]
//     'x.port' es el número del puerto
//     'e' es el tiempo transcurrido desde la última transición.

// Asigna True la variable vecindario_cambio
vecindario_cambio = 1;

double *value = (double *) x.value;
double estado_vecino = value[1];

// Actualiza la variable vecindario_vivos
if (estado_vecino == 1) {
	vecinos_vivos++;
} 
else {
	vecinos_vivos--;
}

sigma = sigma - e;
}
Event celula::lambda(double t) {
/* Salida de la Célula */
// Esta función retorna un Evento:
//     Event(%&Valor%, %NroPuerto%)
// donde:
//     %&Valor% apunta a la variable que contiene el valor.
//     %NroPuerto% es el número del puerto (de 0 a n-1).

// Si el instante es Actualizar, entonces descartamos la salida haciendo uso del puerto 1.
if (instante==1) return Event(0, 1);

// Si el instante es Comunicar, enviamos por el puerto 0 la salida: [id, estado]
y[0]=id;
y[1]=estado;
return Event(y, 0);
}
void celula::exit() {

}
