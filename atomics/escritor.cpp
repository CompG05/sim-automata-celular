#include "escritor.h"
void escritor::init(double t,...) {
char* FName;
va_list parameters;
va_start(parameters, t);
FName=va_arg(parameters, char*);
Sigma=0;
FOutput = PDFileOpen(FName, 'w');

std::string parametros[4];
std::ifstream archivo;
std::string nombre_archivo = "../atomics/vida/estado.txt";
archivo.open(nombre_archivo.data());

if (!archivo.is_open())
	std::cerr << "No se pudo abrir el archivo " << nombre_archivo << "\n";

for (int i = 0; i < 4; i++) {
	if (!getline(archivo, parametros[i])) {
		std::cerr << "Error al leer el archivo\n";
	}
}

tablero = parametros[0];
intervalo = atof(parametros[3].data());

archivo.close();
}
double escritor::ta(double t) {
return Sigma;
}
void escritor::dint(double t) {
char buf[1024];
sprintf(buf,"%g, %s\n",t, tablero.data());
PDFileWrite(FOutput,buf,strlen(buf));

Sigma = intervalo;
}
void escritor::dext(Event x, double t) {
double *value = (double *) x.value;
int id = (int) value[0];
tablero[id] = value[1] == 0 ? '0' : '1';
Sigma -= e;
}
Event escritor::lambda(double t) {
return Event(0,0);
}
void escritor::exit() {
PDFileClose(FOutput);
}
