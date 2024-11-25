#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

class Karel {
private:
    int x, y; // Posición de Karel
    vector<vector<int>> mundo; // Mundo con monedas
    int monedasRecolectadas;   // Total de monedas recolectadas

public:
    // Constructor
    Karel(int filas = 5, int cols = 5) 
        : x(0), y(0), 
          mundo(filas, vector<int>(cols, 0)), 
          monedasRecolectadas(0) 
    {
        // Inicializar monedas aleatorias en la primera fila
        srand(time(NULL)); // Semilla para números aleatorios
        for (int i = 0; i < cols; i++) {
            mundo[0][i] = rand() % 3; // Entre 0 y 2 monedas
            cout << "Monedas en posición (" << i << ", 0): " << mundo[0][i] << endl;
        }
    }

    // Método para recolectar monedas
    void recolectarMonedas() {
        cout << "\nINICIO: Recolección de Monedas\n" << endl;

        // Recolectar monedas en cada posición de la primera fila
        while (x < mundo[0].size()) {
            if (mundo[0][x] > 0) {
                cout << "Monedas encontradas en posición (" << x << ", 0): " << mundo[0][x] << endl;
                monedasRecolectadas += mundo[0][x]; // Sumar al total recolectado
                mundo[0][x] = 0; // Vaciar las monedas de esta posición
            }
            x++;
        }

        // Regresar al inicio
        regresarAlInicio();

        // Depositar monedas
        depositarMonedas();
    }

    // Método para regresar a la posición inicial
    void regresarAlInicio() {
        cout << "\nRegresando al inicio..." << endl;
        x = 0;
        cout << "Posición actual: (" << x << ", 0)" << endl;
    }

    // Método para depositar monedas en la posición inicial
    void depositarMonedas() {
        mundo[0][0] = monedasRecolectadas; // Almacenar monedas en la posición inicial
        cout << "Depositando " << monedasRecolectadas << " monedas en la posición inicial (0, 0)" << endl;
    }
};

int main() {
    // Crear instancia de Karel y recolectar monedas
    Karel robot;
    robot.recolectarMonedas();
    return 0;
}

