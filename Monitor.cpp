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

Monitor::Monitor(int n) {

  N = n;
  contA1 = n;
  contA2 = n;
  pasaDerecha = true;
  pasando = false;
  contAutos = 0;
}

void Monitor::printDireccion(string direccion) {

  cout << "auto #" << contAutos << " " << direccion << "\n";
}

void Monitor::PuntoEntrada(string direccion) {

  unique_lock<mutex> lck(m);

  if (direccion == "derecha") {

    // esperando1++;

    // mientras no esten pasando los que vienen por la derecha
    // estos esperaran hasta que se les avise o pasen 3 segundos.
    while (!pasaDerecha) {

      if (a1.wait_for(lck, 3000ms) == cv_status::timeout) {

        contA2 = N;
        pasaDerecha = true;
      }
      // a1.wait(lck);
      // a1.wait_for(lck, 1000ms);
      // cout<<"esperando a la "<<direccion<<"\nesperando1 =
      // "<<esperando1<<"\nesperando2 ="<<esperando2<<"\n";
    }
    // contA1_mutex.lock();

    // Se usan los contA para ver si ya se dejo pasar una cantidad N de autos
    contA1--;
    // esperando1--;
    if (contA1 == 0) {

      contA1 = N;
      pasaDerecha = false;
    }
    contAutos++;
    // contA1_mutex.unlock();

    printDireccion(direccion);
    PuntoSalida();

  } else if (direccion == "izquierda") {

    // esperando2++;

    while (pasaDerecha) {

      if (a2.wait_for(lck, 3000ms) == cv_status::timeout) {

        contA1 = N;
        pasaDerecha = false;
      }
      // a2.wait(lck);
      // a2.wait_for(lck, 1000ms);
      // cout<<"esperando a la "<<direccion<<"\nesperando1 =
      // "<<esperando1<<"\nesperando2 ="<<esperando2<<"\n";
    }

    // contA2_mutex.lock();

    contA2--;
    // esperando2--;

    if (contA2 == 0) {

      contA2 = N;
      pasaDerecha = true;
    }
    contAutos++;
    // contA2_mutex.unlock();

    printDireccion(direccion);
    PuntoSalida();
  }
}

void Monitor::PuntoSalida() {

  // Se notifica a solamente 1 auto de cada lado, estos
  // notificaran a los demas al volver a llamar este metodo.
  a1.notify_one();
  a2.notify_one();

  /*
          if(pasaDerecha && (esperando1 == 0) && (esperando2 != 0)){

                  contA1 = N;
                  pasaDerecha = false;
                  a2.notify_one();


          }else if(!pasaDerecha && (esperando1 != 0) && (esperando2 == 0)){

                  contA2 = N;
                  pasaDerecha = true;
                  a1.notify_one();

          }else{

                  a1.notify_one();
                  a2.notify_one();

          }
  */
}
