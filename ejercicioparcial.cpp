#include <cmath>
#include <iostream>
#include <limits>
#include <string>
#include <iomanip>

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

void corregirCoordenadas(
    PuntoTrayectoria &punto,
    float desplazamientoX,
    float desplazamientoY,
    float desplazamientoZ)
{
    punto.coordenadas[0] += desplazamientoX;
    punto.coordenadas[1] += desplazamientoY;
    punto.coordenadas[2] += desplazamientoZ;

    calcularDistancia(&punto);
    clasificarPunto(punto);

    std::cout << "\nPUNTO CORREGIDO\n";
    std::cout << "ID: " << punto.identificador << '\n';
    std::cout << "Nombre: " << punto.nombre << '\n';
    std::cout << "X: " << punto.coordenadas[0] << '\n';
    std::cout << "Y: " << punto.coordenadas[1] << '\n';
    std::cout << "Z: " << punto.coordenadas[2] << '\n';
    std::cout << "Distancia al origen: "
              << punto.distanciaOrigen << '\n';
    std::cout << "Clasificacion: "
              << punto.estadoSeguridad << '\n';
}

void generarInforme(PuntoTrayectoria puntos[], int cantidad)
{
    if (cantidad <= 0)
    {
        std::cout << "No hay puntos registrados.\n";
        return;
    }

    int cercanos = 0;
    int intermedios = 0;
    int lejanos = 0;
    int extremos = 0;
    double suma_distancias = 0;

    // Guardar el formato actual de la salida.
    const auto formato_anterior = std::cout.flags();
    const auto precision_anterior = std::cout.precision();

    std::cout << std::fixed << std::setprecision(2);
    std::cout << "\nINFORME DE TRAYECTORIA\n\n";

    std::cout << std::left
              << std::setw(15) << "ID"
              << std::setw(25) << "Nombre"
              << std::setw(12) << "X"
              << std::setw(12) << "Y"
              << std::setw(12) << "Z"
              << std::setw(15) << "Distancia"
              << "Clasificacion\n";

    std::cout << std::string(105, '-') << '\n';

    for (PuntoTrayectoria *p = puntos;
         p < puntos + cantidad;
         p++)
    {
        calcularDistancia(p);
        clasificarPunto(*p);

        std::cout << std::setw(15) << p->identificador
                  << std::setw(25) << p->nombre
                  << std::setw(12) << p->coordenadas[0]
                  << std::setw(12) << p->coordenadas[1]
                  << std::setw(12) << p->coordenadas[2]
                  << std::setw(15) << p->distanciaOrigen
                  << p->estadoSeguridad << '\n';

        suma_distancias += p->distanciaOrigen;

        if (p->estadoSeguridad == "CERCANO")
        {
            cercanos++;
        }
        else if (p->estadoSeguridad == "INTERMEDIO")
        {
            intermedios++;
        }
        else if (p->estadoSeguridad == "LEJANO")
        {
            lejanos++;
        }
        else if (p->estadoSeguridad == "EXTREMO")
        {
            extremos++;
        }
    }

    std::cout << "\nCercanos: " << cercanos << '\n';
    std::cout << "Intermedios: " << intermedios << '\n';
    std::cout << "Lejanos: " << lejanos << '\n';
    std::cout << "Extremos: " << extremos << '\n';
    std::cout << "Distancia promedio al origen: "
              << suma_distancias / cantidad << '\n';

    std::cout.flags(formato_anterior);
    std::cout.precision(precision_anterior);
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




int opcion = -1;

do
{
    std::cout << "\nMENU\n";
    std::cout << "1. Corregir coordenadas de un punto\n";
    std::cout << "2. Generar informe de trayectoria\n";
    std::cout << "0. Salir\n";
    std::cout << "Selecciona una opcion: ";

    if (!(std::cin >> opcion))
    {
        if (std::cin.eof())
        {
            return 0;
        }

        std::cin.clear();
        std::cin.ignore(
            std::numeric_limits<std::streamsize>::max(), '\n');

        std::cout << "Ingresa una opcion numerica.\n";
        continue;
    }

    switch (opcion)
    {
        case 1:
        {
            std::cout << "\nPUNTOS REGISTRADOS\n";

            for (int i = 0; i < cantidad; i++)
            {
                std::cout << i + 1 << ". "
                          << trayectoria[i].identificador << " - "
                          << trayectoria[i].nombre << '\n';
            }

            int seleccion = 0;

            std::cout << "Numero del punto que deseas corregir: ";

            if (!(std::cin >> seleccion))
            {
                if (std::cin.eof())
                {
                    return 0;
                }

                std::cin.clear();
                std::cin.ignore(
                    std::numeric_limits<std::streamsize>::max(), '\n');

                std::cout << "Entrada invalida.\n";
                break;
            }

            if (seleccion < 1 || seleccion > cantidad)
            {
                std::cout << "Ese punto no existe.\n";
                break;
            }

            float desplazamientos[3]{};
            const char ejes[3] = {'X', 'Y', 'Z'};

            for (int i = 0; i < 3; i++)
            {
                while (true)
                {
                    std::cout << "Desplazamiento en "
                              << ejes[i] << ": ";

                    if (std::cin >> desplazamientos[i])
                    {
                        break;
                    }

                    if (std::cin.eof())
                    {
                        return 0;
                    }

                    std::cin.clear();
                    std::cin.ignore(
                        std::numeric_limits<std::streamsize>::max(),
                        '\n');

                    std::cout << "Ingresa un numero valido.\n";
                }
            }

            corregirCoordenadas(
                trayectoria[seleccion - 1],
                desplazamientos[0],
                desplazamientos[1],
                desplazamientos[2]);

            break;
        }

        case 2:
        {
            generarInforme(trayectoria, cantidad);
            break;
        }

        case 0:
        {
            std::cout << "Programa finalizado.\n";
            break;
        }

        default:
        {
            std::cout << "Opcion invalida.\n";
            break;
        }
    }

} while (opcion != 0);

    return 0;
}