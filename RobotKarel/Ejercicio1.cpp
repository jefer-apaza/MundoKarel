#include <iostream>
using namespace std;

class Karel {
private:
    int posX, posY; // Posición actual de Karel
    int dir;        // 0: Norte, 1: Este, 2: Sur, 3: Oeste

public:
    Karel() : posX(0), posY(0), dir(1) {} // Constructor por defecto

    // Girar 90 grados hacia la izquierda
    void girarIzquierda() {
        dir = (dir + 1) % 4;
        mostrarEstado("Girando a la izquierda");
    }

    // Avanzar una casilla en la dirección actual
    void avanzar() {
        switch(dir) {
            case 0: posY++; break;  // Norte
            case 1: posX++; break;  // Este
            case 2: posY--; break;  // Sur
            case 3: posX--; break;  // Oeste
        }
        mostrarEstado("Avanzando");
    }

    // Comprobar si el camino está libre al frente
    bool caminoLibre() const {
        switch(dir) {
            case 0: return posY < 4;  // Norte
            case 1: return posX < 4;  // Este
            case 2: return posY > 0;  // Sur
            case 3: return posX > 0;  // Oeste
        }
        return false;
    }

    // Mostrar el estado actual de Karel
    void mostrarEstado(const string& accion) const {
        static const string direcciones[] = {"Norte", "Este", "Sur", "Oeste"};
        cout << accion << " - Posición: (" << posX << ", " << posY << ") Dirección: " 
             << direcciones[dir] << endl;
    }

    // Recorrer el perímetro del cuadrado 5x5
    void recorrerPerimetro() {
        cout << "Iniciando recorrido del perímetro" << endl;
        do {
            // Moverse mientras no haya pared
            while(caminoLibre()) {
                avanzar();
            }
            // Girar a la izquierda si encuentra una pared
            girarIzquierda();
        } while(!(posX == 0 && posY == 0));

        cout << "Recorrido completado" << endl;
    }
};

int main() {
    Karel robot;
    robot.recorrerPerimetro();
    return 0;
}
