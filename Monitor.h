#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

class Monitor {

public:
  int N;
  int contAutos;
  int contA1;
  int contA2;
  bool pasaDerecha;
  bool pasando;
  condition_variable a1;
  condition_variable a2;
  mutex m;
  mutex contA1_mutex;
  mutex contA2_mutex;

public:
  Monitor(int n);
  void PuntoEntrada(string direccion);
  void PuntoSalida();
  void printDireccion(string direccion);
};
