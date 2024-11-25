#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Karel {
private:
    int x, y;
    vector<vector<int>> mundo;

public:
    // Constructor: inicializa el mundo con monedas desordenadas
    Karel(int filas = 5, int cols = 5) 
        : x(0), y(0), 
          mundo(filas, vector<int>(cols, 0)) {
        srand(time(NULL)); // Semilla para números aleatorios
        cout << "MONEDAS INICIALES EN EL MUNDO:" << endl;
        for (int i = 0; i < cols; i++) {
            mundo[0][i] = rand() % 3; // Generar 0-2 monedas en cada celda de la primera fila
            cout << "Posición (" << i << ", 0): " << mundo[0][i] << " monedas" << endl;
        }
    }

    // Método para ordenar las monedas en la primera fila
    void ordenarMonedas() {
        cout << "\nINICIO: Ordenación de Monedas" << endl;

        // Mostrar estado inicial
        cout << "Estado inicial de monedas: ";
        for (int coins : mundo[0]) {
            cout << coins << " ";
        }
        cout << endl;

        // Recolectar todas las monedas en un contenedor temporal
        int totalMonedas = 0;
        for (int i = 0; i < mundo[0].size(); i++) {
            totalMonedas += mundo[0][i];
            mundo[0][i] = 0; // Vaciar todas las celdas
        }

        // Distribuir las monedas ordenadas desde la izquierda
        for (int i = 0; i < totalMonedas; i++) {
            mundo[0][i] = 1;
        }

        // Mostrar estado final
        cout << "\nEstado final de monedas: ";
        for (int coins : mundo[0]) {
            cout << coins << " ";
        }
        cout << endl;
    }
};

int main() {
    Karel robot;
    robot.ordenarMonedas();
    return 0;
}
