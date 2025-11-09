#include <iostream>
#include <cstdlib>
#include <ctime>
#include <string>
#include <thread>
#include <chrono>
#include <fstream>
using namespace std;

struct Jugador {
    string nombre;
    char simbolo;
    int ganes = 0;
    int empates = 0;
    int perdidas = 0;
};

void limpiarPantalla();
int registrarJugadores(Jugador jugadores[]);
void simularCarrera(Jugador jugadores[], int n);
void mostrarEstadisticas(Jugador jugadores[], int n);
void mostrarTop3(Jugador jugadores[], int n);
void guardarResultados(Jugador jugadores[], int n, int ganadores[], int totalGanadores);


int main() {
    srand(time(0));
    Jugador jugadores[5];
    int cantidadJugadores = 0;
    int opcion;

    do {
        cout << "|---------Menu de Opciones---------|" << endl;
        cout << "| 1. Registrar a los participantes |" << endl;
        cout << "| 2. Iniciar carrera               |" << endl;
        cout << "| 3. Ver estadisticas              |" << endl;
        cout << "| 4. Ver top 3 jugadores           |" << endl;
        cout << "| 5. Salir                         |" << endl;
        cout << "------------------------------------" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                limpiarPantalla();
                cantidadJugadores = registrarJugadores(jugadores);
                break;

            case 2:
                limpiarPantalla();
                if (cantidadJugadores < 2) {
                    cout << "Debe registrar al menos 2 jugadores primero \n";
                } else {
                    simularCarrera(jugadores, cantidadJugadores);
                }
                break;

            case 3:
                limpiarPantalla();
                if (cantidadJugadores == 0)
                    cout << "No hay datos registrados.\n";
                else
                    mostrarEstadisticas(jugadores, cantidadJugadores);
                break;

            case 4:
                limpiarPantalla();
                if (cantidadJugadores == 0)
                    cout << "No hay jugadores registrados \n";
                else
                    mostrarTop3(jugadores, cantidadJugadores);
                break;

            case 0:
                limpiarPantalla();
                cout << "Saliendo del juego \n";
                break;

            default:
                limpiarPantalla();
                cout << "Opcion invalida, intente de nuevo \n";
        }

        if (opcion != 5) {
            cout << "\nPresione Enter para continuar ";
            cin.ignore();
            cin.get();
            limpiarPantalla();
        }

    } while (opcion != 0);

    return 0;
}
