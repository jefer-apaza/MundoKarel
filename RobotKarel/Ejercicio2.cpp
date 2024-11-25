#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    int posX, posY;   // Posición actual
    int direccion;    // 0: Norte, 1: Este, 2: Sur, 3: Oeste
    vector<vector<bool>> mapaVisitados;  // Registro de celdas visitadas

public:
    Karel(int tamano = 5) 
        : posX(0), posY(0), direccion(1),
          mapaVisitados(tamano, vector<bool>(tamano, false)) {
        mapaVisitados[posX][posY] = true;
    }

    // Girar hacia la derecha
    void girarDerecha() {
        direccion = (direccion - 1 + 4) % 4;
        mostrarEstado("Girando a la derecha");
    }

    // Girar hacia la izquierda
    void girarIzquierda() {
        direccion = (direccion + 1) % 4;
        mostrarEstado("Girando a la izquierda");
    }

    // Avanzar una casilla
    void avanzar() {
        switch(direccion) {
            case 0: posY++; break;  // Norte
            case 1: posX++; break;  // Este
            case 2: posY--; break;  // Sur
            case 3: posX--; break;  // Oeste
        }
        mapaVisitados[posX][posY] = true;
        mostrarEstado("Avanzando");
    }

    // Mostrar el estado actual de Karel
    void mostrarEstado(const string& accion) const {
        static const string direcciones[] = {"Norte", "Este", "Sur", "Oeste"};
        cout << accion << " - Posición: (" << posX << ", " << posY << ") Dirección: " 
             << direcciones[direccion] << endl;
    }

    // Comprobar si hay camino al frente
    bool caminoLibre() const {
        switch(direccion) {
            case 0: return posY < 4;  // Norte
            case 1: return posX < 4;  // Este
            case 2: return posY > 0;  // Sur
            case 3: return posX > 0;  // Oeste
        }
        return false;
    }

    // Buscar la salida del laberinto
    void buscarSalida() {
        cout << "Iniciando búsqueda de salida" << endl;
        while(!esSalida()) {
            // Intentar girar a la derecha y avanzar
            girarDerecha();
            if(caminoLibre() && !casillaVisitada()) {
                avanzar();
            }
            // Avanzar si el camino está despejado
            else if(caminoLibre()) {
                avanzar();
            }
            // Retroceder si no hay camino
            else {
                cout << "Sin camino, retrocediendo" << endl;
                girarIzquierda();
                girarIzquierda();
            }

            // Mostrar el estado del mapa de visitados
            mostrarMapaVisitados();
        }
        cout << "¡Salida encontrada!" << endl;
    }

    // Comprobar si la posición actual es una salida
    bool esSalida() const {
        return (posX == 4 || posY == 4);
    }

    // Comprobar si la casilla al frente ya fue visitada
    bool casillaVisitada() const {
        int nuevaX = posX, nuevaY = posY;
        switch(direccion) {
            case 0: nuevaY++; break;
            case 1: nuevaX++; break;
            case 2: nuevaY--; break;
            case 3: nuevaX--; break;
        }
        return mapaVisitados[nuevaX][nuevaY];
    }

    // Mostrar el mapa de celdas visitadas
    void mostrarMapaVisitados() const {
        cout << "Mapa de celdas visitadas:" << endl;
        for(int i = 0; i < mapaVisitados.size(); i++) {
            for(int j = 0; j < mapaVisitados[i].size(); j++) {
                cout << (mapaVisitados[j][i] ? "X " : "O ");
            }
            cout << endl;
        }
        cout << "-------------------" << endl;
    }
};

int main() {
    Karel robot;
    robot.buscarSalida();
    return 0;
}
