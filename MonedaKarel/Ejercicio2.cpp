#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

class Karel {
private:
    int x, y;                      // Posición del robot
    vector<vector<int>> mundo;     // Mundo representado por una matriz

public:
    // Constructor: inicializa el mundo con monedas aleatorias
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

    // Método para contar las monedas en la primera fila
    void contarMonedas() {
        int contador = 0; // Contador de monedas
        cout << "\nINICIO: Conteo de Monedas" << endl;

        // Recorre la primera fila y cuenta las monedas
        for (x = 0; x < mundo[0].size(); x++) {
            if (mundo[0][x] > 0) {
                contador += mundo[0][x];
                cout << "Monedas encontradas en posición (" << x << ", 0): " << mundo[0][x] << endl;
            }
        }

        // Depositar el total en la última celda de la fila
        mundo[0][mundo[0].size() - 1] = contador;
        cout << "\nTotal de monedas contadas: " << contador << endl;
        cout << "Depositando " << contador << " monedas en la última posición (" 
             << mundo[0].size() - 1 << ", 0)" << endl;
    }
};

int main() {
    Karel robot;
    robot.contarMonedas();
    return 0;
}
