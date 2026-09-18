#include <cmath>
#include <iostream>
#include <limits>
#include <string>

struct PuntoTrayectoria
{
    std::string identificador;
    std::string nombre;
    float coordenadas[3]{};
    float distanciaOrigen = 0;
    std::string estadoSeguridad;
};

void registrarPunto(PuntoTrayectoria &punto)
{
    std::cout << "Identificador: ";
    std::getline(std::cin >> std::ws, punto.identificador);

    std::cout << "Nombre: ";
    std::getline(std::cin, punto.nombre);

    const char ejes[3] = {'X', 'Y', 'Z'};

    for (int i = 0; i < 3; i++)
    {
        while (true)
        {
            std::cout << "Coordenada " << ejes[i] << ": ";

            if (std::cin >> punto.coordenadas[i])
            {
                break;
            }

            if (std::cin.eof())
            {
                return;
            }

            std::cin.clear();
            std::cin.ignore(
                std::numeric_limits<std::streamsize>::max(), '\n');

            std::cout << "Entrada invalida. Ingresa un numero.\n";
        }
    }
}

float calcularDistancia(PuntoTrayectoria *punto)
{
    float x = punto->coordenadas[0];
    float y = punto->coordenadas[1];
    float z = punto->coordenadas[2];

    punto->distanciaOrigen = std::sqrt(x * x + y * y + z * z);

    return punto->distanciaOrigen;
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

PuntoTrayectoria *obtenerPuntoMasAlejado(
    PuntoTrayectoria puntos[], int cantidad)
{
    if (cantidad <= 0)
    {
        return nullptr;
    }

    PuntoTrayectoria *mas_alejado = puntos;

    for (PuntoTrayectoria *actual = puntos + 1;
         actual < puntos + cantidad;
         actual++)
    {
        if (actual->distanciaOrigen > mas_alejado->distanciaOrigen)
        {
            mas_alejado = actual;
        }
    }

    return mas_alejado;
}

int main()
{
    const int kMaxElementos = 10;

    PuntoTrayectoria trayectoria[kMaxElementos]{};
    int cantidad = 0;

    while (true)
    {
        std::cout << "Cuantos puntos deseas registrar? (1 a 10): ";

        if (std::cin >> cantidad)
        {
            if (cantidad >= 1 && cantidad <= kMaxElementos)
            {
                break;
            }
        }
        else
        {
            if (std::cin.eof())
            {
                return 0;
            }

            std::cin.clear();
        }

        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Cantidad invalida. Intenta nuevamente.\n";
    }

    std::cout << "\nSe registraran " << cantidad << " puntos.\n";

    // Registrar los puntos mediante la funcion.
    for (int i = 0; i < cantidad; i++)
    {
        std::cout << "\nPUNTO " << i + 1 << '\n';
        registrarPunto(trayectoria[i]);

        if (!std::cin)
        {
            return 0;
        }
    }

    // Recorrer el arreglo utilizando punteros.
    for (PuntoTrayectoria *p = trayectoria;
         p < trayectoria + cantidad;
         p++)
    {
        calcularDistancia(p);
        clasificarPunto(*p);
    }

    // Mostrar la distancia y clasificacion de cada punto.
    std::cout << "\nRESULTADOS\n";

    for (PuntoTrayectoria *p = trayectoria;
         p < trayectoria + cantidad;
         p++)
    {
        std::cout << "\nID: " << p->identificador << '\n';
        std::cout << "Nombre: " << p->nombre << '\n';
        std::cout << "Distancia al origen: "
                  << p->distanciaOrigen << '\n';
        std::cout << "Clasificacion: "
                  << p->estadoSeguridad << '\n';
    }

    PuntoTrayectoria *encontrado =
        obtenerPuntoMasAlejado(trayectoria, cantidad);

    if (encontrado != nullptr)
    {
        std::cout << "\nPUNTO MAS ALEJADO\n";
        std::cout << "ID: " << encontrado->identificador << '\n';
        std::cout << "Nombre: " << encontrado->nombre << '\n';

        std::cout << "X: " << encontrado->coordenadas[0] << '\n';
        std::cout << "Y: " << encontrado->coordenadas[1] << '\n';
        std::cout << "Z: " << encontrado->coordenadas[2] << '\n';

        std::cout << "Distancia al origen: "
                  << encontrado->distanciaOrigen << '\n';

        std::cout << "Clasificacion: "
                  << encontrado->estadoSeguridad << '\n';
    }

    return 0;
}