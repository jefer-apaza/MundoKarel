#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    int x, y;
    vector<vector<int>> laberinto;
    enum Direccion { NORTE, ESTE, SUR, OESTE };
    Direccion orientacion;

public:
    // Constructor que inicializa el laberinto y la orientación
    Karel() : x(0), y(0), orientacion(ESTE),
        laberinto({
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1},
            {0, 0, 0, 0, 2}  // 2 representa la salida
        }) {}

    // Comprobar si hay un camino despejado a la derecha
    bool derechaDespejada() {
        switch (orientacion) {
            case NORTE: return x + 1 < laberinto[0].size() && laberinto[y][x + 1] != 1;
            case ESTE:  return y + 1 < laberinto.size() && laberinto[y + 1][x] != 1;
            case SUR:   return x - 1 >= 0 && laberinto[y][x - 1] != 1;
            case OESTE: return y - 1 >= 0 && laberinto[y - 1][x] != 1;
        }
        return false;
    }

    // Comprobar si hay un camino despejado al frente
    bool frenteLibre() {
        switch (orientacion) {
            case NORTE: return y - 1 >= 0 && laberinto[y - 1][x] != 1;
            case ESTE:  return x + 1 < laberinto[0].size() && laberinto[y][x + 1] != 1;
            case SUR:   return y + 1 < laberinto.size() && laberinto[y + 1][x] != 1;
            case OESTE: return x - 1 >= 0 && laberinto[y][x - 1] != 1;
        }
        return false;
    }

    // Girar a la derecha
    void girarDerecha() {
        orientacion = static_cast<Direccion>((orientacion + 1) % 4);
        cout << "Girando a la derecha. Nueva orientación: " << orientacionToString() << endl;
    }

    // Girar a la izquierda
    void girarIzquierda() {
        orientacion = static_cast<Direccion>((orientacion + 3) % 4);
        cout << "Girando a la izquierda. Nueva orientación: " << orientacionToString() << endl;
    }

    // Mover al frente
    void mover() {
        switch (orientacion) {
            case NORTE: y--; break;
            case ESTE:  x++; break;
            case SUR:   y++; break;
            case OESTE: x--; break;
        }
        cout << "Moviendo a posición (" << x << ", " << y << ")" << endl;
    }

    // Algoritmo para encontrar la salida
    void encontrarSalida() {
        cout << "Iniciando búsqueda desde posición (" << x << ", " << y << ")" << endl;
        while (laberinto[y][x] != 2) {  // 2 representa la salida
            if (derechaDespejada()) {
                girarDerecha();
                mover();
            } else if (frenteLibre()) {
                mover();
            } else {
                girarIzquierda();
            }
        }
        cout << "¡Salida encontrada en (" << x << ", " << y << ")!" << endl;
    }

    // Convertir orientación a string para imprimir
    string orientacionToString() {
        switch (orientacion) {
            case NORTE: return "NORTE";
            case ESTE:  return "ESTE";
            case SUR:   return "SUR";
            case OESTE: return "OESTE";
        }
        return "";
    }
};

int main() {
    Karel robot;
    robot.encontrarSalida();
    return 0;
}
