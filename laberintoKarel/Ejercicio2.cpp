#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    int x, y, monedasRecolectadas;
    vector<vector<int>> laberinto;
    enum Direccion { NORTE, ESTE, SUR, OESTE };
    Direccion orientacion;

public:
    // Constructor: inicializa el laberinto, posición inicial y orientación
    Karel() : x(0), y(0), orientacion(ESTE), monedasRecolectadas(0),
        laberinto({
            {0, 3, 0, 0, 1},
            {1, 1, 0, 1, 1},
            {0, 0, 3, 0, 0},
            {1, 1, 0, 1, 3},
            {0, 0, 0, 0, 2}  // 2 = salida, 3 = moneda
        }) {}

    // Verificar si la celda a la derecha está despejada
    bool derechaDespejada() {
        switch (orientacion) {
            case NORTE: return x + 1 < laberinto[0].size() && laberinto[y][x + 1] != 1;
            case ESTE:  return y + 1 < laberinto.size() && laberinto[y + 1][x] != 1;
            case SUR:   return x - 1 >= 0 && laberinto[y][x - 1] != 1;
            case OESTE: return y - 1 >= 0 && laberinto[y - 1][x] != 1;
        }
        return false;
    }

    // Verificar si la celda al frente está despejada
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

    // Recoger moneda en la posición actual
    void recogerMoneda() {
        if (laberinto[y][x] == 3) {
            monedasRecolectadas++;
            laberinto[y][x] = 0; // Marcar la celda como vacía
            cout << "¡Moneda recolectada! Total: " << monedasRecolectadas << endl;
        }
    }

    // Buscar la salida mientras se recolectan monedas
    void encontrarSalida() {
        cout << "Iniciando búsqueda desde posición (" << x << ", " << y << ")" << endl;

        while (laberinto[y][x] != 2) {  // 2 representa la salida
            recogerMoneda();

            if (derechaDespejada()) {
                girarDerecha();
                mover();
            } else if (frenteLibre()) {
                mover();
            } else {
                girarIzquierda();
            }
        }

        cout << "¡Salida encontrada en (" << x << ", " << y << ")! Monedas recolectadas: " << monedasRecolectadas << endl;
    }

    // Convertir orientación a texto legible
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
