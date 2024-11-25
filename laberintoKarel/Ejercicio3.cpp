#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    int x, y, monedas;
    vector<vector<int>> laberinto;
    enum Direccion { NORTE, ESTE, SUR, OESTE };
    Direccion orientacion;

public:
    // Constructor
    Karel() : x(0), y(0), orientacion(ESTE), monedas(10),
        laberinto({
            {0, 0, 0, 0, 1},
            {1, 1, 0, 1, 1},
            {0, 0, 0, 0, 0},
            {1, 1, 0, 1, 1},
            {0, 0, 0, 0, 2}  // 2 representa salida
        }) {}

    // Convertir orientación a texto
    string orientacionToString() {
        switch (orientacion) {
            case NORTE: return "NORTE";
            case ESTE:  return "ESTE";
            case SUR:   return "SUR";
            case OESTE: return "OESTE";
        }
        return "";
    }

    // Verificar si hay más de dos caminos posibles desde la posición actual
    bool contarCaminos() {
        int caminos = 0;
        if (y - 1 >= 0 && laberinto[y - 1][x] != 1) caminos++; // Arriba
        if (y + 1 < laberinto.size() && laberinto[y + 1][x] != 1) caminos++; // Abajo
        if (x - 1 >= 0 && laberinto[y][x - 1] != 1) caminos++; // Izquierda
        if (x + 1 < laberinto[0].size() && laberinto[y][x + 1] != 1) caminos++; // Derecha
        return caminos > 2;
    }

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

    // Marcar intersección con una moneda
    void marcarInterseccion() {
        if (contarCaminos() && monedas > 0) {
            monedas--;
            cout << "Intersección marcada con moneda en (" << x << ", " << y << "). "
                 << "Monedas restantes: " << monedas << endl;
        } else if (contarCaminos() && monedas == 0) {
            cout << "No hay monedas disponibles para marcar intersección en (" << x << ", " << y << ")" << endl;
        }
    }

    // Encontrar la salida del laberinto
    void encontrarSalida() {
        cout << "Iniciando búsqueda desde posición (" << x << ", " << y << ")" << endl;

        while (laberinto[y][x] != 2) {  // 2 representa la salida
            marcarInterseccion();

            if (derechaDespejada()) {
                girarDerecha();
                mover();
            } else if (frenteLibre()) {
                mover();
            } else {
                girarDerecha(); // Cambia de dirección si no hay opciones disponibles
            }
        }

        cout << "¡Salida encontrada en (" << x << ", " << y << ")! "
             << "Monedas usadas: " << 10 - monedas << endl;
    }
};

int main() {
    Karel robot;
    robot.encontrarSalida();
    return 0;
}
