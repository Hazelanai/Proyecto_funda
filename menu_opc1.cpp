#include <iostream>
using namespace std;

struct Jugador {
    string nombre;
    int tiempo;
    int posicion;
};

void limpiarPantalla();
int registrarJugadores(Jugador jugadores[]);
void simularCarrera(Jugador jugadores[], int n);
void mostrarEstadisticas(Jugador jugadores[], int n);
void mostrarTop3(Jugador jugadores[], int n);
void guardarResultados(Jugador jugadores[], int n, int ganadores[], int totalGanadores);

int main() {
    Jugador jugadores[10];  
    int n;                
    int ganadores[3];     

    int opcion;
    do {
        cout << "----- MENU DE CARRERA -----" << endl;
        cout << "| 1. Registrar jugadores  |" << endl;
        cout << "| 2. Iniciar carrera      |" << endl;
        cout << "| 3. Mostrar estadisticas |" << endl;
        cout << "| 4. Mostrar top 3        |" << endl;
        cout << "| 5. Guardar resultados   |" << endl;
        cout << "| 6. Limpiar pantalla     |" << endl;
        cout << "| 7. Salir                |" << endl;
        cout << "---------------------------" << endl;
        cin >> opcion;

        switch (opcion) {
            case 1:
                n = registrarJugadores(jugadores);  
                break;
            case 2:
                simularCarrera(jugadores, n);       
                break;
            case 3:
                mostrarEstadisticas(jugadores, n); 
                break;
            case 4:
                mostrarTop3(jugadores, n);       
                break;
            case 5:
                guardarResultados(jugadores, n, ganadores, 3); 
                break;
            case 6:
                limpiarPantalla();                 
                break;
            case 7:
                cout << "Saliendo del programa" << endl;
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo" << endl;
        }

    } while (opcion != 0);

    return 0;
}
