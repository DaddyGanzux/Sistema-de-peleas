#include <iostream>
#include <Locale>
#include <time.h>
#include <codecvt>
#include <string>
#include <thread>
#include <random>
#include <ctime>


int generarNumeroAleatorio(int min, int max) //Generador de números aleatorios.
{
    static std::mt19937 generador(static_cast<unsigned int>(std::time(0)));
    std::uniform_int_distribution<int> distribucion(min, max);
    return distribucion(generador);
}

class Personaje
{
public:
    std::string nombre;
    int salud;
    int ataque;
    int defensa;
    int zi;

    Personaje(std::string nombre, int salud, int ataque, int defensa)
        : nombre(nombre), salud(salud), ataque(ataque), defensa(defensa) {
    }

    void atacar(Personaje& enemigo)
    {
        int daño = std::max(0, ataque - enemigo.defensa);
        daño += generarNumeroAleatorio(0, 29);
        enemigo.salud -= daño;
        std::cout << nombre << " ataca a " << enemigo.nombre << " causando " << daño << " de daño." << std::endl;
        if (enemigo.salud < 0) enemigo.salud = 0;
    }

    // Para mostrar el estado
    void mostrarEstado() const {
        std::cout << nombre << " - Salud: " << salud << std::endl;
    }

    // Para verificar si está vivo
    bool estaVivo() const {
        return salud > 0;
    }
};

// Función principal del juego
void juegoRPG()
{
    setlocale(LC_ALL, "Spanish");
    char respuesta;
    std::string nombreJugador;
    std::string nombreEnemigo;

    std::cout << "Ingresa nombre de tu jugador\n";
    std::getline(std::cin, nombreJugador);

    std::cout << "Ingresa nombre de tu nemesis\n";
    std::getline(std::cin, nombreEnemigo);


    Personaje jugador(nombreJugador, 200, 20, 30);

    Personaje enemigo(nombreEnemigo, 270, -10, 10);

    while (jugador.estaVivo() && enemigo.estaVivo())
    {
        system("cls");

        std::cout << "Escoje un ataque: 1- Espadazo  2- Super ultra mega skibiditoilet parangacutirimicuaro oztion   3- Achazo\n";
        std::cin >> respuesta;

        jugador.atacar(enemigo);
        enemigo.mostrarEstado();
        if (!enemigo.estaVivo())
        {
            std::cout << "Hooray, you win CONGRATULATIONS!!!!!!!\n";
            break;
        }

        enemigo.atacar(jugador);
        jugador.mostrarEstado();
        if (!jugador.estaVivo())
        {
            std::cout << nombreJugador << " ha sido derrotado." << std::endl;
            break;
        }

        std::cin.ignore();

        std::cout << "Presione enter para continuar\n";
        std::cin.get();

    }
}

int main() {
    juegoRPG();
    return 0;
}