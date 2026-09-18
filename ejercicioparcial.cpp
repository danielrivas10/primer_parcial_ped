#include <iostream>

/*
Un laboratorio de robótica está realizando pruebas con un robot autónomo que debe desplazarse dentro de una zona de investigación.
Durante una prueba, el robot registra diferentes puntos de su trayectoria.
Cada punto contiene una posición en los ejes X, Y y Z, además de información
relacionada con el movimiento realizado en ese punto.
El programa deberá almacenar los puntos de trayectoria, procesarlos matemáticamente
y determinar aspectos como la distancia recorrida, el punto más alejado del origen y posibles cambios en la trayectoria.
El objetivo es utilizar estructuras, arreglos, funciones, referencias y punteros
para construir un pequeño sistema de análisis de trayectoria.
El programa trabajará con un máximo de 10 puntos.
*/

struct PuntoTrayectoria
{
    std::string identificador;
    std::string nombre;
    std::string coordenadas[3];
    float distanciaOrigen;
    float factorUtilizacion;
    std::string estadoSeguridad;
};

void registrarPunto(PuntoTrayectoria &punto)
{

    std::cout << "Identificador: ";
    std::getline(std::cin >> std::ws, punto.identificador);

    std::cout << "Nombre: ";
    std::getline(std::cin, punto.nombre);

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Coordenadas " << i + 1 << ": ";
        std::cin >> punto.coordenadas[i];
    }
}

float calcularDistancia(PuntoTrayectoria *punto)
{
    float raiz = 0;

    std::cout << "Su distancia al origen es: " << std::endl;
    for (int i = 0; i < 3; i++)
    {

        (*punto).coordenadas[i];
    }
}

void clasificarPunto(PuntoTrayectoria &punto)
{

    if (punto.distanciaOrigen <= 5)
    {
        punto.estadoSeguridad = "CERCANO";
    }
    else if (punto.distanciaOrigen <= 10)
    {
        punto.estadoSeguridad = "INTERMEDIO";
    }
    else if (punto.distanciaOrigen <= 20)
    {
        punto.estadoSeguridad = "LEJANO";
    }
    else
    {
        punto.estadoSeguridad = "EXTREMO";
    }
}

PuntoTrayectoria *obtenerPuntoMasAlejado(PuntoTrayectoria puntos[], int cantidad)
{

    PuntoTrayectoria *critico = &puntos[0];

    for (int i = 1; i < cantidad; i++)
    {
        if (puntos[i].distanciaOrigen >
            (*critico).distanciaOrigen) // Es este el mayor de todos?
        {
            critico = &puntos[i]; // Entonces esta es la mayor distancia
        }
    }

    return critico;
}

int main()
{
    const int MAX_ELEMENTOS = 10;

    PuntoTrayectoria trayectoria[MAX_ELEMENTOS]{};
    int cantidad = 0;
    while (true)
    {
        std::cout << "Cuantos elementos deseas registrar? (1 a 10): ";

        if (std::cin >> cantidad)
        {
            if (cantidad >= 1 && cantidad <= MAX_ELEMENTOS)
            {
                break;
            }
        }
        else
        {

            std::cin.clear();
        }

        std::cout << "Cantidad invalida. Intenta nuevamente.\n";
    }

    std::cout << "Se registrara " << cantidad
              << " puntos." << std::endl;

    //------------------------------------------------------------------------------

    for (int i = 0; i < cantidad; i++)
    {

        registrarPunto(trayectoria[i]);
    }
    //--------------------------------------------------------------------------

    for (PuntoTrayectoria *p = trayectoria; p < trayectoria + cantidad; p++) // Avanza el puntero una estructura Elemento completa, para apuntar a la siguiente.
    {
        float factor = calcularDistancia(p);
        float calcularDistancia(PuntoTrayectoria * punto);
    }

    //-------------------------------------------------------

    PuntoTrayectoria *encontrado = obtenerPuntoMasAlejado(trayectoria, cantidad);

    std::cout << "\nELEMENTO MAS ALEJADO\n";

    std::cout << "ID: "
              << (*encontrado).identificador << std::endl;

    std::cout << "Nombre: "
              << (*encontrado).nombre << std::endl;

    for (int i = 0; i < 3; i++)
    {
        std::cout << "Coordenadas " << i + 1 << ": "
                  << (*encontrado).coordenadas[i] << std::endl;
    }

    std::cout << "Estado de seguridad: "
              << (*encontrado).estadoSeguridad << std::endl;

    //--------------------------------------------------------

    



    return 0;
}