#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    // Representa el mundo con la pared y puertas
    vector<vector<int>> mapa;
    // Posición actual de Karel
    int posX, posY;
    // Dirección de Karel (0: derecha, 1: izquierda)
    int orientacion;

public:
    // Constructor: inicializa el mundo con una pared y una puerta
    Karel() : posX(0), posY(0), orientacion(0),
        mapa({
            // 0 representa espacio libre
            // 1 representa pared
            {1, 1, 0, 1, 1}  // Pared con puerta en la posición 2
        }) {}

    // Método para verificar si el frente está libre
    bool frenteLibre() {
        // Si va a la derecha, verifica la siguiente columna
        if(orientacion == 0 && posX + 1 < mapa[0].size()) {
            return mapa[posY][posX + 1] == 0;
        }
        // Si va a la izquierda, verifica la columna anterior
        if(orientacion == 1 && posX - 1 >= 0) {
            return mapa[posY][posX - 1] == 0;
        }
        return false;
    }

    // Método para mover a Karel
    void mover() {
        // Mueve a la derecha
        if(orientacion == 0) {
            posX++;
            cout << "Moviendo a la derecha. Posición: ("
                 << posX << "," << posY << ")" << endl;
        }
        // Mueve a la izquierda
        else {
            posX--;
            cout << "Moviendo a la izquierda. Posición: ("
                 << posX << "," << posY << ")" << endl;
        }
    }

    // Método para cambiar dirección
    void cambiarDireccion() {
        orientacion = 1 - orientacion;
        cout << "Cambiando dirección. Nueva dirección: "
             << (orientacion == 0 ? "derecha" : "izquierda") << endl;
    }

    // Método para encontrar la puerta
    void encontrarPuerta() {
        cout << "Buscando puerta..." << endl;

        // Continúa hasta encontrar una casilla libre
        while(!frenteLibre()) {
            mover();
        }

        cout << "¡Puerta encontrada en posición ("
             << posX << "," << posY << ")!" << endl;
    }
};

int main() {
    Karel robot;
    robot.encontrarPuerta();
    return 0;
}
