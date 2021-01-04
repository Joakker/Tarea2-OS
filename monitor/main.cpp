#include <chrono>
#include <condition_variable>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <mutex>
#include <queue>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>

#include "Monitor.hpp"

using namespace std;

Monitor *M;

void mEntrada(string s) { M->PuntoEntrada(s); }

int main(int argc, char *argv[]) {

  // Guardia para notar el uso correcto del programa
  if (argc != 2) {
    cout << "uso: " << argv[0] << " N\n";
    return 1;
  }

  srand(time(NULL));

  // Convierte una string a int
  const int n = atoi(argv[1]);
  int r;
  string dir;

  int z = 5 * n;

  string v[z];

  cout << "\n----Autos que llegan----\n";
  // Genera z autos (hebras) con direcciones al azar
  for (int i = 0; i < z; i++) {

    r = rand() % 20 + 1;

    if (r > 10) {
      v[i] = "derecha";
    } else if (r <= 10) {
      v[i] = "izquierda";
    }
    // v[i] = "derecha";
    cout << "v[" << i << "] = " << v[i] << "\n";
  }
  cout << "\n----Autos que salen----\n";

  // Éste es el monitor que nos administrará las hebras
  M = new Monitor(n);

  // Aquí se mantienen las hebras generadas
  vector<thread> threads;

  // Se crean las hebras y se les pasa el metodo a ocupar.
  for (int i = 0; i < z; i++) {
    dir = v[i];
    threads.push_back(thread(mEntrada, dir));
  }

  // Une las hebras una por una.
  for (auto &thread : threads) {
    thread.join();
  }

  return 0;
}
