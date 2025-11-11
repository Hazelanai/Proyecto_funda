#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <windows.h> // para Sleep()

using namespace std;

struct Jugador {
    string nombre;
    char simbolo;
    int posicion = 0;
    int ganes = 0;
    int empates = 0;
    int perdidas = 0;
};


void menu();
void registrarJugadores(Jugador jugadores[], int &num);
void iniciarCarrera(Jugador jugadores[], int num);
void mostrarTablero(Jugador jugadores[], int num, int longitud);
void aplicarSerpientesEscaleras(Jugador &jugador);
void registrarResultados(Jugador jugadores[], int num);
void mostrarEstadisticas();

int main() {
    srand(time(nullptr)); 
    menu();
    return 0;
}

void menu() {
    Jugador jugadores[5];
    int num = 0;
    int opcion;

    do {
        cout << "\n===== MENU PRINCIPAL =====" << endl;
        cout << "1. Registrar jugadores" << endl;
        cout << "2. Iniciar carrera" << endl;
        cout << "3. Ver estadisticas" << endl;
        cout << "4. Salir" << endl;
        cout << "Seleccione una opcion: ";
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1:
                registrarJugadores(jugadores, num);
                break;
            case 2:
                if (num >= 2)
                    iniciarCarrera(jugadores, num);
                else
                    cout << "Debe registrar al menos 2 jugadores antes de iniciar.\n";
                break;
            case 3:
                mostrarEstadisticas();
                break;
            case 4:
                cout << "Saliendo del programa...\n";
                break;
            default:
                cout << "Opcion no valida.\n";
        }
    } while (opcion != 4);
}

void registrarJugadores(Jugador jugadores[], int &num) {
    do {
        cout << "\nIngrese la cantidad de participantes a registrar (2 a 5): ";
        cin >> num;
        if (num < 2 || num > 5)
            cout << "Debe ingresar un numero entre 2 y 5.\n";
    } while (num < 2 || num > 5);

    cin.ignore();

    cout << "\n=== Registro de participantes ===\n";
    for (int i = 0; i < num; i++) {
        cout << "Participante " << i + 1 << " de " << num << endl;
        cout << "Nombre: ";
        getline(cin, jugadores[i].nombre);
        jugadores[i].simbolo = toupper(jugadores[i].nombre[0]);
        jugadores[i].posicion = 0;
        jugadores[i].ganes = jugadores[i].empates = jugadores[i].perdidas = 0;
    }

    cout << "\nSe han registrado correctamente " << num << " participantes.\n";
}

void mostrarTablero(Jugador jugadores[], int num, int longitud) {
    cout << "\n-------------------------------- TABLERO --------------------------------\n";
    for (int i = 0; i < num; i++) {
        cout << setw(10) << jugadores[i].nombre << " ";
        for (int j = 0; j < longitud; j++) {
            if (j == jugadores[i].posicion)
                cout << jugadores[i].simbolo;
            else
                cout << ".";
        }
        cout << endl;
    }
    cout << "-------------------------------------------------------------------------\n";
}

void aplicarSerpientesEscaleras(Jugador &jugador) {
    switch (jugador.posicion) {
        case 5:
            cout << jugador.nombre << " sube por una escalera! (+3 posiciones)\n";
            jugador.posicion += 3;
            break;
        case 10:
            cout << jugador.nombre << " cae en una serpiente! (-4 posiciones)\n";
            jugador.posicion -= 4;
            if (jugador.posicion < 0) jugador.posicion = 0;
            break;
        case 15:
            cout << jugador.nombre << " sube por una escalera! (+5 posiciones)\n";
            jugador.posicion += 5;
            break;
        case 22:
            cout << jugador.nombre << " cae en una serpiente! (-6 posiciones)\n";
            jugador.posicion -= 6;
            if (jugador.posicion < 0) jugador.posicion = 0;
            break;
        default:
            break;
    }
}

void iniciarCarrera(Jugador jugadores[], int num) {
    const int META = 30;
    bool fin = false;

    cout << "\n===== COMIENZA LA CARRERA =====\n";

    while (!fin) {
        for (int i = 0; i < num; i++) {
            int dado = rand() % 6 + 1;
            jugadores[i].posicion += dado;
            cout << jugadores[i].nombre << " avanza " << dado << " pasos.\n";

            aplicarSerpientesEscaleras(jugadores[i]);
            if (jugadores[i].posicion >= META)
                fin = true;
        }

        mostrarTablero(jugadores, num, META);
        Sleep(800); // pausa para ver el avance
        cout << endl;
    }

    // Determinar ganadores
    int mayor = 0;
    for (int i = 0; i < num; i++)
        if (jugadores[i].posicion > mayor) mayor = jugadores[i].posicion;

    int ganadores = 0;
    for (int i = 0; i < num; i++) {
        if (jugadores[i].posicion >= mayor) {
            jugadores[i].ganes++;
            ganadores++;
        } else {
            jugadores[i].perdidas++;
        }
    }

    cout << "\n===== RESULTADOS =====\n";
    if (ganadores > 1)
        cout << "Empate entre los siguientes jugadores:\n";
    else
        cout << "Ganador:\n";

    for (int i = 0; i < num; i++)
        if (jugadores[i].posicion >= mayor)
            cout << "🏆 " << jugadores[i].nombre << endl;

    registrarResultados(jugadores, num);
}

void registrarResultados(Jugador jugadores[], int num) {
    ofstream archivo("resultados.txt", ios::app);
    if (!archivo) {
        cout << "Error al abrir el archivo de resultados.\n";
        return;
    }

    time_t ahora = time(nullptr);
    archivo << "\n===== Carrera del " << ctime(&ahora);
    for (int i = 0; i < num; i++) {
        archivo << jugadores[i].nombre
                << " (pos: " << jugadores[i].posicion << ")\n";
    }
    archivo << "--------------------------\n";
    archivo.close();

    cout << "\nResultados guardados en 'resultados.txt'\n";
}

void mostrarEstadisticas() {
    ifstream archivo("resultados.txt");
    if (!archivo) {
        cout << "No hay resultados guardados aún.\n";
        return;
    }

    cout << "\n===== HISTORIAL DE CARRERAS =====\n";
    string linea;
    while (getline(archivo, linea)) {
        cout << linea << endl;
    }
    archivo.close();
}
