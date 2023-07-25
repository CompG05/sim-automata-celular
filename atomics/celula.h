//CPP:vida/celula.cpp
#if !defined celula_h
#define celula_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"
#include "fstream"
#include "iostream"


class celula: public Simulator { 
// Declare the state,
// output variables
// and parameters
double id;
double estado;
int instante;
int vecindario_cambio;
int vecinos_vivos;
double sigma;

double intervalo;
int r_supervivencia[8];
int n_r_supervivencia;
int r_nacimiento[8];
int n_r_nacimiento;

double y[2];

public:
	celula(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
