#include <iostream>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

using namespace std;


void imprimirMatriz(), titulo(), Instrucciones();
string UnJugador(), DosJugadores();
bool EsGanador(char);
char matrizDeJuego[3][3];

int main()
{
    system("color 0A");
    srand(time(NULL));
    //////Variables//////
    int opcion;
    string ganador;
    ////////Darle la bienvenida al usuario//////
    titulo();
    cout<<"\n\tBienvenido al juego de gato.\n";
    Sleep(1500);
    while (true)  //////Ciclo principal
    {
        do /////menu principal (modo de juego o salirse del programa)
        {
            titulo();
            cout<<"\n\tElija el modo de juego\n";
            cout<<"\n\t1.- Jugar en PvP.";
            cout<<"\n\t2.- Jugar Vs IA.";
            cout<<"\n\t3.- Instrucciones.";
            cout<<"\n\t4.- Salir del juego"; 
            cout<<"\n\n\tOpcion: ";
            cin>>opcion;
            //si la capturo mal, decirle que se equivoco antes de que se repita el menu
            if(opcion<1 || opcion>4) //esto se cumple si el usuario se equivoca
            {
                titulo();
                cout<<"\n\tOpcion invalida x.x"; //le decimos que se equivoco
                Sleep(1500);
            }
        }while(opcion<1 || opcion>4);
        ///Fin del menu principal
        ///Ejecucion de la opcion escogida
        switch (opcion)
        {
            case 1:
                ganador=DosJugadores();
                titulo();
                cout<<"\n\tHa ganado el jugador: " <<ganador <<"\n\n\t";
                system("pause");
                break;

            case 2:
                ganador=UnJugador();
                titulo();
                cout<<"\n\tHa ganado el jugador: " <<ganador <<"\n\n\t";
                system("pause");
                break;

            case 3:
                Instrucciones();
                break;

            default:
                titulo();
                cout<<"\n\tGracias por jugar!";
                Sleep(1500);
                exit(EXIT_SUCCESS);
        }
    }
}

string UnJugador()
{
    //Aca van las variables//
    string jugadores[2];
    char simbolosJugadores[2];
    int opcion, jugadorActual=0;
    bool tiradaValida=false, matrizllena=false;
    int fila,columna;
    //inicializando la matriz
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            matrizDeJuego[i][j]=' ';
        }
    }
    //Obtencion de nombres//
    titulo();
    cout<<"\n\tEscribe tu nombre de jugador: ";
    cin>>jugadores[0];
    cout<<"\n\tEscribe el nombre de la IA: ";
    cin>>jugadores[1];
    do //menu de eleccion de simbolo
    {
        titulo();
        cout<<"\n\tEscoje:\n\n\t1.-Jugar con X\n\t2.-Jugar con O\n\n\topcion: ";
        cin>>opcion;
        if (opcion<1 || opcion>2)
        {
            titulo();
            cout<<"\n\tOpcion invalida, intentalo de nuevo...";
            Sleep(1500);
        }
    } while (opcion<1 || opcion>2);
    //Definiendo el simbolo del jugador y maquina
    opcion==1 ? simbolosJugadores[0]='X' : simbolosJugadores[0]='O';
    simbolosJugadores[0]=='X' ? simbolosJugadores[1]='O' : simbolosJugadores[1]='X';
    //Se completa el registro del jugador
    //Se inicia el juego (ciclo principal)
    while(true)
    {
        //se comprueba que la matriz no este llena
        matrizllena=true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //si se llega a encontrar alguna casilla vacia entonces la matriz no esta llena y se puede realizar el tiro
                if(matrizDeJuego[i][j]==' '){matrizllena=false;}
            }
        }
        if(matrizllena){return "empate";}
        //si no se ha llenado entonces el siguiente jugador procede a tirar
        switch (jugadorActual)
        {
            case 0:
                //menu de pedir datos para jugador 1
                do
                {
                    //impresion de matriz
                    imprimirMatriz();
                    //Se piden los datos de fila y columna para la tirada
                    tiradaValida=true;
                    cout<<"\n\tTurno de " <<jugadores[jugadorActual] <<"\n\n\tIndica la fila de la tirada: ";
                    cin>>fila;
                    cout<<"\n\tIndica la columna de la tirada: ";
                    cin>>columna;
                    //se comprueba que el tiro sea correcto
                    if((fila<1 || fila>3) || (columna<1 || columna>3) || (matrizDeJuego[fila-1][columna-1]!=' '))
                    {
                        tiradaValida=false;
                        titulo();
                        cout<<"\n\tLa tidada no es valida, intentalo de nuevo.";
                        Sleep(1500);
                    }
                } while (!tiradaValida);
                //Como el jugador hace tiradas de 1 a 3 y los indices van de 0 a 2 entonces a cada variable se le resta 1
                fila--; columna--;
                break;

            case 1:
                imprimirMatriz();
                cout<<"\n\tTurno de " <<jugadores[jugadorActual];
                Sleep(1500);
                cout<<"\n\n\t" <<jugadores[jugadorActual] <<" esta pensando la tirada...\n";
                Sleep(1500);
                do
                {
                    fila=rand()%3; //numero aleatorio para la fila que va del 0 al 2
                    columna=rand()%3; //numero aleatorio para la columna que va del 0 al 2
                    cout<<"\n\tTirada calculada por "<<jugadores[jugadorActual] <<": " <<fila+1 <<"," <<columna+1;
                    Sleep(1500);
                    matrizDeJuego[fila][columna]==' ' ? tiradaValida=true : tiradaValida=false;
                }while(!tiradaValida);
                break;
        
            default:
                titulo();
                cout<<"\n\n\tHa sucedido un error, favor de contactar al programador.";
                Sleep(1500);
                exit(EXIT_FAILURE);
            break;
        }
        //Se realiza el tiro
        matrizDeJuego[fila][columna]=simbolosJugadores[jugadorActual];
        imprimirMatriz();
        cout<<"\n\t" <<jugadores[jugadorActual] <<" realiza la tirada en la posicion: " <<fila+1 <<"," <<columna+1;
        Sleep(1500);
        //Se comprueba si el jugador actual ha ganado
        if(EsGanador(simbolosJugadores[jugadorActual])){return jugadores[jugadorActual];}
        //Si el jugador actual no ha ganado el turno para al siguiente jugador y se repite el programa
        jugadorActual==0 ? jugadorActual=1 : jugadorActual=0;
    }
    //Se termina el juego
}

string DosJugadores()
{
    //Aca van las variables//
    string jugadores[2];
    char simbolosJugadores[]={'X','O'};
    int opcion, jugadorActual=0;
    bool tiradaValida=false, matrizllena=false;
    int fila,columna;
    //inicializando la matriz
    for(int i=0; i<3; i++)
    {
        for(int j=0; j<3; j++)
        {
            matrizDeJuego[i][j]=' ';
        }
    }
    //Obtencion de nombres//
    titulo();
    cout<<"\n\tEscribe el nombre del jugador 1: ";
    cin>>jugadores[0];
    cout<<"\n\tEscribe el nombre del jugador 2: ";
    cin>>jugadores[1];
    //Se inicia el juego (ciclo principal)
    while(true)
    {
        //se comprueba que la matriz no este llena
        matrizllena=true;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                //si se llega a encontrar alguna casilla vacia entonces la matriz no esta llena y se puede realizar el tiro
                if(matrizDeJuego[i][j]==' '){matrizllena=false;}
            }
        }
        if(matrizllena){return "empate";}
        //si no se ha llenado entonces el siguiente jugador procede a tirar
        do
        {
            //impresion de matriz
            imprimirMatriz();
            //Se piden los datos de fila y columna para la tirada
            tiradaValida=true;
            cout<<"\n\tTurno de " <<jugadores[jugadorActual] <<".\n\n\tIndica la fila de la tirada: ";
            cin>>fila;
            cout<<"\n\tIndica la columna de la tirada: ";
            cin>>columna;
            //se comprueba que el tiro sea correcto
            if((fila<1 || fila>3) || (columna<1 || columna>3) || (matrizDeJuego[fila-1][columna-1]!=' '))
            {
                tiradaValida=false;
                titulo();
                cout<<"\n\tLa tidada no es valida, intentalo de nuevo.";
                Sleep(1500);
            }
        } while (!tiradaValida);
        //Se realiza el tiro
        matrizDeJuego[fila-1][columna-1]=simbolosJugadores[jugadorActual];
        imprimirMatriz();
        cout<<"\n\t" <<jugadores[jugadorActual] <<" realiza la tirada en la posicion: " <<fila <<"," <<columna;
        Sleep(1500);
        //Se comprueba si el jugador actual ha ganado
        if(EsGanador(simbolosJugadores[jugadorActual])){return jugadores[jugadorActual];}
        //Si el jugador actual no ha ganado el turno para al siguiente jugador
        jugadorActual==0 ? jugadorActual=1 : jugadorActual=0;
    }
}

void imprimirMatriz()
{
    titulo();
    cout<<"\n\t  1  2  3";
    for(int i=0; i<3; i++)
    {
        cout<<"\n\t" <<(i+1) <<"[" <<matrizDeJuego[i][0] <<"][" <<matrizDeJuego[i][1] <<"][" <<matrizDeJuego[i][2] <<"]";
    }
    cout<<endl;
}

void titulo()
{
    system("cls");
    cout<<"\n";
    cout<<"\n\t************************";
    cout<<"\n\t*                      *";
    cout<<"\n\t*    Juego del Gato    *";
    cout<<"\n\t*                      *";
    cout<<"\n\t************************";
    cout<<"\n";
}

void Instrucciones()
{
    titulo();
    cout<<"\n\tInstrucciones:\n";
    cout<<"\n\tSi escoges el modo de un jugador entonces se te va";
    cout<<"\n\ta pedir un nombre de jugador y otro nombre para la";
    cout<<"\n\tIA. Despues, independientemente de si escoges el modo";
    cout<<"\n\tun jugador o dos jugadores, la forma de tirar es";
    cout<<"\n\tpor turnos, donde a los jugadores se les va a pedir";
    cout<<"\n\tla fila (vertical) y la columna (horizontal)";
    cout<<"\n\tdonde se desea realizar el tiro.\n";
    cout<<"\n\tEjemplo:\n";
    cout<<"\n\tIndica la fila de la tirada: 3";
    cout<<"\n\tIndica la columna de la tirada: 2\n";
    cout<<"\n\tTirada realizada en las coordenadas 3,2:\n";
    cout<<"\n\t  1  2  3";
    cout<<"\n\t1[ ][ ][ ]";
    cout<<"\n\t2[ ][ ][ ]";
    cout<<"\n\t3[ ][X][ ]";
    cout<<"\n\n\t";
    system("pause");
}

bool EsGanador(char caracter)
{
    int contadorHorizontal=0,contadorVertical=0;
    //Para filas y columnas
    for (int i = 0; i < 3; i++)
    {
        //Se reinician contadores por cada fila/columna
        contadorHorizontal=0;
        contadorVertical=0;
        for (int j = 0; j < 3; j++)
        {
            if(matrizDeJuego[i][j]==caracter){contadorHorizontal++;} //horizontales
            if(matrizDeJuego[j][i]==caracter){contadorVertical++;} //horizontales
        }
        //se comprueba si se ha llenado alguna fila/columna
        if((contadorHorizontal==3) || (contadorVertical==3)){return true;}
    }
    //Para las diagonales (reusamos contadores ya declarados)
    contadorHorizontal=0;
    contadorVertical=0;
    for (int i = 0; i < 3; i++)
    {
        if(matrizDeJuego[i][i]==caracter){contadorHorizontal++;}
        if(matrizDeJuego[i][2-i]==caracter){contadorVertical++;}
    }
    if((contadorHorizontal==3) || (contadorVertical==3)){return true;}
    return false;
}