#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    // Representa el mundo con pared y puertas
    vector<vector<int>> mundo;
    // Monedas de Karel
    int monedas;
    // Posición actual de Karel
    int x, y;
    // Dirección de Karel (0: derecha, 1: izquierda)
    int direccion;

public:
    // Constructor: inicializa mundo con una puerta
    Karel() : x(0), y(0), direccion(0), monedas(5),
        mundo({
            // 0 libre, 1 pared, 2 marca puerta
            {1, 1, 2, 1, 1}
        }) {}

    // Verifica si el frente está libre
    bool frenteLibre() {
        // Mueve a la derecha
        if(direccion == 0 && x+1 < mundo[0].size()) {
            return mundo[y][x+1] == 0 || mundo[y][x+1] == 2;
        }
        // Mueve a la izquierda
        if(direccion == 1 && x-1 >= 0) {
            return mundo[y][x-1] == 0 || mundo[y][x-1] == 2;
        }
        return false;
    }

    // Método para mover a Karel
    void mover() {
        if(direccion == 0) {
            if(x+1 < mundo[0].size()) {
                x++;
                cout << "Moviendo a la derecha. Posición: ("
                     << x << "," << y << ")" << endl;
            }
        }
        else {
            if(x-1 >= 0) {
                x--;
                cout << "Moviendo a la izquierda. Posición: ("
                     << x << "," << y << ")" << endl;
            }
        }
    }

    // Método para colocar moneda
    void colocarMoneda() {
        if(monedas > 0 && mundo[y][x] == 2) {
            monedas--;
            cout << "Colocando moneda en puerta. Monedas restantes: "
                 << monedas << endl;
        }
    }

    // Método para encontrar puerta y marcarla
    void encontrarPuertaConMoneda() {
        cout << "Buscando puerta para marcar..." << endl;

        // Recorre hasta encontrar puerta
        while(!frenteLibre()) {
            mover();
        }

        // Coloca moneda en la puerta
        colocarMoneda();

        // Cruza la puerta
        mover();

        cout << "¡Puerta cruzada en posición ("
             << x << "," << y << ")!" << endl;
    }
};

int main() {
    Karel robot;
    robot.encontrarPuertaConMoneda();
    return 0;
}
