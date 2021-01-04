#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <iostream>
#include <mutex>
#include <string>
#include <thread>
#include <unistd.h>

#include "Monitor.h"

using namespace std;

// Constructor del semáforo
Monitor::Monitor(int n) {

  N = n;
  contA1 = n;
  contA2 = n;
  pasaDerecha = true;
  contAutos = 0;
}

void Monitor::printDireccion(string direccion) {
  cout << "auto #" << contAutos << " " << direccion << "\n";
}

// Éste es el método que la hebra invoca en su espacio
void Monitor::PuntoEntrada(string direccion) {

  unique_lock<mutex> lck(m);

  // Distingue si la dirección es izquierda o derecha
  if (direccion == "derecha") {
    // mientras no esten pasando los que vienen por la derecha
    // estos esperaran hasta que se les avise o pasen 3 segundos.
    while (!pasaDerecha) {

      if (a1.wait_for(lck, 3000ms) == cv_status::timeout) {

        contA2 = N;
        pasaDerecha = true;
      }
    }

    // Se usan los contA para ver si ya se dejo pasar una cantidad N de autos
    contA1--;
    // El último auto ejecuta éste código
    if (contA1 == 0) {
      contA1 = N;
      pasaDerecha = false;
    }
    contAutos++;
  } else if (direccion == "izquierda") {
    // Similar a más arriba, pero esperan a que la derecha esté bloqueada
    while (pasaDerecha) {
      if (a2.wait_for(lck, 3000ms) == cv_status::timeout) {
        contA1 = N;
        pasaDerecha = false;
      }
    }
    contA2--;

    // El último auto de la izquierda entra aquí.
    if (contA2 == 0) {
      contA2 = N;
      pasaDerecha = true;
    }
    contAutos++;
  }
  // Imprime el resultado y se sale
  printDireccion(direccion);
  PuntoSalida();
}

// Cada auto ejecuta éste código cuando sale de la vía
void Monitor::PuntoSalida() {
  // Se notifica a solamente 1 auto de cada lado, estos
  // notificaran a los demas al volver a llamar este metodo.
  a1.notify_one();
  a2.notify_one();
}
