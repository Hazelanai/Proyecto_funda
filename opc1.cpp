#include <iostream>
#include <cstdlib>   
#include <ctime>    
#include <fstream>  
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
    int n = 0; // Número de jugadores
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
                if (n > 0)
                    simularCarrera(jugadores, n);
                else
                    cout << "Primero registre jugadores" << endl;
                break;
            case 3:
                if (n > 0)
                    mostrarEstadisticas(jugadores, n);
                else
                    cout << "No hay jugadores registrados" << endl;
                break;
            case 4:
                if (n > 0)
                    mostrarTop3(jugadores, n);
                else
                    cout << "No hay jugadores registrados" << endl;
                break;
            case 5:
                if (n > 0)
                    guardarResultados(jugadores, n, ganadores, 3);
                else
                    cout << "No hay resultados para guardar" << endl;
                break;
            case 6:
                limpiarPantalla();
                break;
            case 7:
                cout << "Saliendo del programa" << endl;
                break;
            default:
                cout << "Opcion invalida, intente de nuevo" << endl;
        }
    } while (opcion != 0);

    return 0;
}

// Limpia pantalla (depende del sistema operativo)
void limpiarPantalla() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Registra jugadores y devuelve la cantidad
int registrarJugadores(Jugador jugadores[]) {
    int n;
    cout << "Ingrese el numero de jugadores (max 10): ";
    cin >> n;

    if (n < 1 || n > 10) {
        cout << "Numero invalido, debe ser entre 1 y 10." << endl;
        return 0;
    }

    for (int i = 0; i < n; i++) {
        cout << "Ingrese el nombre del jugador " << i + 1 << ": ";
        cin >> jugadores[i].nombre;
        jugadores[i].tiempo = 0;
        jugadores[i].posicion = 0;
    }

    cout << "Jugadores registrados correctamente!" << endl;
    return n;
}

// Simula carrera asignando tiempos aleatorios
void simularCarrera(Jugador jugadores[], int n) {
    srand(time(0)); // Inicializa semilla aleatoria

    for (int i = 0; i < n; i++) {
        jugadores[i].tiempo = 50 + rand() % 51; // Tiempo entre 50 y 100
    }

    // Ordenar por tiempo (menor tiempo = mejor lugar)
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (jugadores[j].tiempo < jugadores[i].tiempo) {
                swap(jugadores[i], jugadores[j]);
            }
        }
    }

    // Asignar posiciones
    for (int i = 0; i < n; i++) {
        jugadores[i].posicion = i + 1;
    }

    cout << "Carrera simulada con exito!" << endl;
}

// Muestra todos los jugadores con su tiempo y posición
void mostrarEstadisticas(Jugador jugadores[], int n) {
    cout << "\n--- ESTADISTICAS DE CARRERA ---" << endl;
    for (int i = 0; i < n; i++) {
        cout << jugadores[i].posicion << ". " << jugadores[i].nombre
             << " - Tiempo: " << jugadores[i].tiempo << "s" << endl;
    }
}

// Muestra los tres primeros
void mostrarTop3(Jugador jugadores[], int n) {
    cout << "\n--- TOP 3 GANADORES ---" << endl;
    for (int i = 0; i < n && i < 3; i++) {
        cout << i + 1 << ". " << jugadores[i].nombre
             << " (" << jugadores[i].tiempo << "s)" << endl;
    }
}

// Guarda resultados en archivo de texto
void guardarResultados(Jugador jugadores[], int n, int ganadores[], int totalGanadores) {
    ofstream archivo("resultados.txt");

    if (!archivo) {
        cout << "Error al crear el archivo!" << endl;
        return;
    }

    archivo << "RESULTADOS DE LA CARRERA\n";
    archivo << "-------------------------\n";
    for (int i = 0; i < n; i++) {
        archivo << jugadores[i].posicion << ". " << jugadores[i].nombre
                << " - " << jugadores[i].tiempo << "s\n";
    }

    archivo.close();
    cout << "Resultados guardados en 'resultados.txt'" << endl;
}
