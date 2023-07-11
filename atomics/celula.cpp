#include "celula.h"
void celula::init(double t,...) {
va_list parameters;
va_start(parameters, t);

std::ifstream archivo;
std::string nombre_archivo = "../sim-automata-celular/estado.txt";

archivo.open(nombre_archivo.data());

if (!archivo.is_open()) {
	std::cerr << "No se pudo abrir el archivo " << nombre_archivo << "\n";
}

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
estado = 0.0 + (tablero[(int)id] - '0'); // Obtener valor entero, sumarle 0.0 para convertir a double
vecindario_cambio = 1;
instante = 0;	// 0 para comunicar y producir salida, 1 para actualizar
vecinos_vivos = 0;
sigma = 0;
es_primera_iter = 1;
}
double celula::ta(double t) {
//This function returns a double.
return sigma;
}
void celula::dint(double t) {
if (instante == 1) {
    if (es_primera_iter)
        es_primera_iter = 0;
    
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
        
        if (nuevo_estado == estado)
            sigma = intervalo;
        
        else {
            estado = nuevo_estado;
            sigma = intervalo/2;
            instante = 0;
        }
    }

		vecindario_cambio = 0;
}

else {
    sigma = intervalo/2;
    instante = 1;
}
}
void celula::dext(Event x, double t) {
//The input event is in the 'x' variable.
//where:
//     'x.value' is the value (pointer to void)
//     'x.port' is the port number
//     'e' is the time elapsed since last transition

vecindario_cambio = 1;
double *value = (double *) x.value;
double estado_vecino = value[1];

if (estado_vecino == 1) {
	vecinos_vivos++;
} 
else if (!es_primera_iter) {
	vecinos_vivos--;
}

sigma = sigma - e;
}
Event celula::lambda(double t) {
//This function returns an Event:
//     Event(%&Value%, %NroPort%)
//where:
//     %&Value% points to the variable which contains the value.
//     %NroPort% is the port number (from 0 to n-1)


if (instante==1) return Event(0, 1);

y[0]=id;
y[1]=estado;
return Event(y, 0);
}
void celula::exit() {
//Code executed at the end of the simulation.

}
