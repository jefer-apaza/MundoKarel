#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    // Representa el mundo con múltiples puertas
    vector<vector<int>> mapa;
    // Posición actual de Karel
    int posX, posY;
    // Dirección de Karel (0: derecha, 1: izquierda)
    int orientacion;

public:
    // Constructor: inicializa el mapa con múltiples puertas
    Karel() : posX(0), posY(0), orientacion(0),
        mapa({
            // 0 libre, 1 pared
            {1, 0, 1, 0, 1, 0, 1}
        }) {}

    // Verifica si el frente está libre
    bool frenteLibre() {
        // Mueve a la derecha
        if(orientacion == 0 && posX + 1 < mapa[0].size()) {
            return mapa[posY][posX + 1] == 0;
        }
        // Mueve a la izquierda
        if(orientacion == 1 && posX - 1 >= 0) {
            return mapa[posY][posX - 1] == 0;
        }
        return false;
    }

    // Método para mover a Karel
    void mover() {
        if(orientacion == 0) {
            posX++;
            cout << "Moviendo a la derecha. Posición: ("
                 << posX << "," << posY << ")" << endl;
        }
        else {
            posX--;
            cout << "Moviendo a la izquierda. Posición: ("
                 << posX << "," << posY << ")" << endl;
        }
    }

    // Cambia dirección de Karel
    void cambiarDireccion() {
        orientacion = 1 - orientacion;
        cout << "Cambiando dirección. Nueva dirección: "
             << (orientacion == 0 ? "derecha" : "izquierda") << endl;
    }

    // Método para cruzar múltiples puertas
    void cruzarPuertas() {
        cout << "Cruzando puertas..." << endl;

        // Recorre todas las posiciones
        while(posX < mapa[0].size() - 1) {
            // Si encuentra puerta, la cruza
            if(frenteLibre()) {
                mover();
                cout << "Cruzando puerta en posición ("
                     << posX << "," << posY << ")" << endl;
            }
            else {
                // Si hay pared, avanza
                mover();
            }
        }

        cout << "Llegada al final del pasillo en posición ("
             << posX << "," << posY << ")" << endl;
    }
};

int main() {
    Karel robot;
    robot.cruzarPuertas();
    return 0;
}
