#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

using namespace std;

// Clase semáforo que administrará qué autos pasan por la vía y cuándo
class Monitor {

public:
  int N;            // Número total de autos
  int contAutos;    // Contador para cuántos autos han pasado
  int contA1;       // Contador para autos de la derecha
  int contA2;       // Contador para autos de la izquierda
  bool pasaDerecha; // Variable de estado que determina qué lado pasa
                    //    (derecha -> true, izquierda -> false)
  condition_variable a1;  // Variable de condición para autos de la derecha
  condition_variable a2;  // Variable de condición para autos de la izquierda
  mutex m;

public:
  Monitor(int n);
  void PuntoEntrada(string direccion);
  void PuntoSalida();
  void printDireccion(string direccion);
};
