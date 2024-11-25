#include <iostream>
#include <vector>
using namespace std;

class Karel {
private:
    int posX, posY;           // Posición actual
    int totalFilas, totalCols; // Dimensiones de la ciudad
    bool barridoDerecha;      // Dirección del barrido
    vector<vector<bool>> basuraRecolectada;

public:
    Karel(int filas = 5, int cols = 5) 
        : posX(0), posY(0),
          totalFilas(filas), totalCols(cols),
          barridoDerecha(true),
          basuraRecolectada(filas, vector<bool>(cols, false)) {}

    // Moverse a la siguiente casilla
    void avanzar() {
        cout << "MOVIMIENTO: ";
        if (barridoDerecha) {
            posX++;
            cout << "Moviendo a la derecha. Nueva posición: (" << posX << "," << posY << ")" << endl;
        } else {
            posX--;
            cout << "Moviendo a la izquierda. Nueva posición: (" << posX << "," << posY << ")" << endl;
        }
    }

    // Cambiar a la siguiente fila
    void siguienteFila() {
        posY++;
        barridoDerecha = !barridoDerecha;
        cout << "CAMBIO DE FILA: Subiendo a la fila " << posY
             << ". Dirección cambiada a "
             << (barridoDerecha ? "derecha" : "izquierda") << endl;
    }

    // Recoger basura si hay en la posición actual
    void recogerBasura() {
        basuraRecolectada[posY][posX] = true;
        cout << "RECOLECCIÓN: Basura recogida en posición (" << posX << "," << posY << ")" << endl;
    }

    // Patrullar toda la ciudad
    void patrullarCiudad() {
        cout << "INICIO DEL PATRULLAJE" << endl;
        while (posY < totalFilas) {
            cout << "\n--- FILA " << posY << " ---" << endl;
            while ((barridoDerecha && posX < totalCols - 1) ||
                   (!barridoDerecha && posX > 0)) {
                recogerBasura();
                avanzar();
            }
            // Mover a la siguiente fila si no es la última
            if (posY < totalFilas - 1) {
                siguienteFila();
            } else {
                break;
            }
        }
        regresarInicio();
    }

    // Regresar al punto de inicio (0, 0)
    void regresarInicio() {
        cout << "\nREGRESANDO AL INICIO" << endl;
        while (posY > 0) {
            cout << "Bajando a la fila " << posY - 1 << endl;
            posY--;
        }
        posX = 0;
        cout << "Posición final: (0,0)" << endl;
    }

    // Generar un reporte de las basuras recogidas
    void reportarBasuras() {
        int totalBasura = 0;
        cout << "\nREPORTE FINAL DE BASURAS:" << endl;
        for (int fila = 0; fila < totalFilas; fila++) {
            for (int col = 0; col < totalCols; col++) {
                if (basuraRecolectada[fila][col]) {
                    totalBasura++;
                    cout << "Basura recogida en (" << col << "," << fila << ")" << endl;
                }
            }
        }
        cout << "Total de basuras recogidas: " << totalBasura << endl;
    }
};

int main() {
    Karel robot;
    robot.patrullarCiudad();
    robot.reportarBasuras();
    return 0;
}
