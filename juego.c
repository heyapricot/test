#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <windows.h>

int main()
{
    char tablero[10][10], tableroVisible[10][10], comando, celda, reiniciar;
    int jugadorX, jugadorY, tesorosRestantes, numTrampas, numTesoros, numPistas;
    int i, j, x, y, distancia, nuevaX, nuevaY, juegoTerminado, distTemp;
    HANDLE hConsole;

    reiniciar = 's';
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

    while (reiniciar == 's' || reiniciar == 'S')
    {
        srand(time(NULL));
        for (i = 0; i < 10; i++)
        {
            for (j = 0; j < 10; j++)
            {
                tablero[i][j] = ' ';
                tableroVisible[i][j] = ' ';
            }
        }

        system("cls");
        SetConsoleTextAttribute(hConsole, 11);
        printf("\n******************************************\n");
        printf("*  BIENVENIDO AL JUEGO DE BUSQUEDA DEL   *\n");
        printf("*               TESORO                   *\n");
        printf("******************************************\n\n");
        SetConsoleTextAttribute(hConsole, 7);

        printf("Configuracion inicial:\n");
        printf("Numero de trampas: ");
        scanf("%d", &numTrampas);
        printf("Numero de tesoros: ");
        scanf("%d", &numTesoros);
        printf("Numero de pistas: ");
        scanf("%d", &numPistas);

        jugadorX = rand() % 10;
        jugadorY = rand() % 10;

        tesorosRestantes = numTesoros;
        for (i = 0; i < numTesoros; i++)
        {
            do
            {
                x = rand() % 10;
                y = rand() % 10;
            }
            while ((x == jugadorX && y == jugadorY) || tablero[x][y] != ' ');
            tablero[x][y] = 'T';
        }

        for (i = 0; i < numTrampas; i++)
        {
            do
            {
                x = rand() % 10;
                y = rand() % 10;
            }
            while ((x == jugadorX && y == jugadorY) || tablero[x][y] != ' ');
            tablero[x][y] = 'X';
        }

        for (i = 0; i < numPistas; i++)
        {
            do
            {
                x = rand() % 10;
                y = rand() % 10;
            }
            while ((x == jugadorX && y == jugadorY) || tablero[x][y] != ' ');
            tablero[x][y] = '?';
        }

        juegoTerminado = 0;

        system("cls");
        SetConsoleTextAttribute(hConsole, 10);
        printf("\nInstrucciones:\n");
        printf("Movimientos: w=arriba, s=abajo, a=izquierda, d=derecha\n");
        printf("Objetivo: Encontrar los %d tesoros (T) evitando trampas (X)\n", numTesoros);
        printf("Pistas usadas se marcan con ? \n");
        printf("Tesoros restantes: %d\n", tesorosRestantes);
        printf("------------------------------------------\n");
        SetConsoleTextAttribute(hConsole, 7);
        system("pause");

        while (!juegoTerminado)
        {
            system("cls");

            SetConsoleTextAttribute(hConsole, 14);
            printf("\n   0 1 2 3 4 5 6 7 8 9\n");
            printf("  +-------------------+\n");

            for (i = 0; i < 10; i++)
            {
                printf("%d |", i);
                for (j = 0; j < 10; j++)
                {
                    if (i == jugadorX && j == jugadorY)
                    {
                        SetConsoleTextAttribute(hConsole, 9);
                        printf("P|");
                        SetConsoleTextAttribute(hConsole, 14);
                    }
                    else if (tableroVisible[i][j] == 'T')
                    {
                        SetConsoleTextAttribute(hConsole, 10);
                        printf("T|");
                        SetConsoleTextAttribute(hConsole, 14);
                    }
                    else if (tableroVisible[i][j] == '?')
                    {
                        SetConsoleTextAttribute(hConsole, 6);
                        printf("?|");
                        SetConsoleTextAttribute(hConsole, 14);
                    }
                    else if (tablero[i][j] == 'T' || tablero[i][j] == 'X' || tablero[i][j] == '?')
                    {
                        printf(" |");
                    }
                    else
                    {
                        printf("%c|", tablero[i][j]);
                    }
                }
                printf("\n");
                if (i < 9)
                {
                    printf("  |-------------------|\n");
                }
                else
                {
                    printf("  +-------------------+\n");
                }
            }
            SetConsoleTextAttribute(hConsole, 7);
            printf("\nTesoros restantes: %d\n", tesorosRestantes);

            printf("\nIngresa tu movimiento: ");
            scanf(" %c", &comando);

            nuevaX = jugadorX;
            nuevaY = jugadorY;

            if (comando == 'w')
            {
                nuevaX = nuevaX - 1;
            }
            else if (comando == 's')
            {
                nuevaX = nuevaX + 1;
            }
            else if (comando == 'a')
            {
                nuevaY = nuevaY - 1;
            }
            else if (comando == 'd')
            {
                nuevaY = nuevaY + 1;
            }

            if (nuevaX >= 0 && nuevaX < 10 && nuevaY >= 0 && nuevaY < 10)
            {
                jugadorX = nuevaX;
                jugadorY = nuevaY;
                celda = tablero[jugadorX][jugadorY];

                if (celda == 'X')
                {
                    system("cls");
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("\n******************************************\n");
                    printf("*             Game Over!                   *\n");
                    printf("*  Caiste en una trampa en [%d,%d]         *\n", jugadorX, jugadorY);
                    printf("*  Tesoros faltantes: %d                   *\n", tesorosRestantes);
                    printf("********************************************\n");
                    SetConsoleTextAttribute(hConsole, 7);
                    juegoTerminado = 1;
                    system("pause");
                }
                else if (celda == 'T')
                {
                    tesorosRestantes--;
                    tablero[jugadorX][jugadorY] = ' ';
                    tableroVisible[jugadorX][jugadorY] = 'T';

                    if (tesorosRestantes > 0)
                    {
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 10);
                        printf("\n Tesoro encontrado en [%d,%d]!\n", jugadorX, jugadorY);
                        printf("Tesoros restantes: %d\n", tesorosRestantes);
                        SetConsoleTextAttribute(hConsole, 7);
                        Sleep(2000);
                    }
                    else
                    {
                        system("cls");
                        SetConsoleTextAttribute(hConsole, 10);
                        printf("\n******************************************\n");
                        printf("*       FELICIDADES! GANASTE!          *\n");
                        printf("*  Encontraste todos los %d tesoros      *\n", numTesoros);
                        printf("******************************************\n");
                        SetConsoleTextAttribute(hConsole, 7);
                        juegoTerminado = 1;
                        system("pause");
                    }
                }
                else if (celda == '?')
                {
                    distancia = 20;
                    for (i = 0; i < 10; i++)
                    {
                        for (j = 0; j < 10; j++)
                        {
                            if (tablero[i][j] == 'T')
                            {
                                distTemp = abs(i - jugadorX) + abs(j - jugadorY);
                                if (distTemp < distancia)
                                {
                                    distancia = distTemp;
                                }
                            }
                        }
                    }

                    system("cls");
                    SetConsoleTextAttribute(hConsole, 6);
                    printf("\nPista: Tesoro mas cercano a %d celdas\n", distancia);
                    SetConsoleTextAttribute(hConsole, 7);
                    tablero[jugadorX][jugadorY] = ' ';
                    tableroVisible[jugadorX][jugadorY] = '?';
                    Sleep(2000);
                }
            }
            else
            {
                SetConsoleTextAttribute(hConsole, 12);
                printf("\nMovimiento no valido\n");
                SetConsoleTextAttribute(hConsole, 7);
                Sleep(1000);
            }
        }

        system("cls");
        SetConsoleTextAttribute(hConsole, 14);
        printf("\nTablero final:\n");
        printf("   0 1 2 3 4 5 6 7 8 9\n");
        printf("  +-------------------+\n");

        for (i = 0; i < 10; i++)
        {
            printf("%d |", i);
            for (j = 0; j < 10; j++)
            {
                if (i == jugadorX && j == jugadorY)
                {
                    SetConsoleTextAttribute(hConsole, 9);
                    printf("P|");
                    SetConsoleTextAttribute(hConsole, 14);
                }
                else if (tablero[i][j] == 'T' || tableroVisible[i][j] == 'T')
                {
                    SetConsoleTextAttribute(hConsole, 10);
                    printf("T|");
                    SetConsoleTextAttribute(hConsole, 14);
                }
                else if (tablero[i][j] == 'X')
                {
                    SetConsoleTextAttribute(hConsole, 12);
                    printf("X|");
                    SetConsoleTextAttribute(hConsole, 14);
                }
                else if (tablero[i][j] == '?' || tableroVisible[i][j] == '?')
                {
                    SetConsoleTextAttribute(hConsole, 6);
                    printf("?|");
                    SetConsoleTextAttribute(hConsole, 14);
                }
                else
                {
                    printf(" |");
                }
            }
            printf("\n");
            if (i < 9)
            {
                printf("  |-------------------|\n");
            }
            else
            {
                printf("  +-------------------+\n");
            }
        }
        SetConsoleTextAttribute(hConsole, 7);

        printf("\nJugar nuevamente? (s/n): ");
        scanf(" %c", &reiniciar);

        while (reiniciar != 's' && reiniciar != 'S' && reiniciar != 'n' && reiniciar != 'N')
        {
            printf("Ingresa 's' para si o 'n' para no: ");
            scanf(" %c", &reiniciar);
        }
    }

    system("cls");
    SetConsoleTextAttribute(hConsole, 11);
    printf("\n******************************************\n");
    printf("*        GRACIAS POR JUGAR!              *\n");
    printf("******************************************\n\n");
    SetConsoleTextAttribute(hConsole, 7);

    return 0;
}
