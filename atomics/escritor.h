//CPP:vida/escritor.cpp
#if !defined escritor_h
#define escritor_h

#include "simulator.h"
#include "event.h"
#include "stdarg.h"

#include "string"
#include "fstream"
#include "iostream"


class escritor: public Simulator { 
// Atributos del escritor
double Sigma;
long int FOutput;
std::string tablero;
double intervalo;


public:
	escritor(const char *n): Simulator(n) {};
	void init(double, ...);
	double ta(double t);
	void dint(double);
	void dext(Event , double );
	Event lambda(double);
	void exit();
};
#endif
