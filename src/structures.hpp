#ifndef STRUCTURES_HPP
#define STRUCTURES_HPP

#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <stdbool.h>
#include <time.h>
#include <unistd.h>
#include <stdint.h>
#include <array>
#include <iomanip>
#include <random>
#include <ctime>
#include <string.h>
#include <string>
#include <sstream>
#include <algorithm>
#include <fstream>
#include <iostream>

#include "ReadSignatures.hpp"
//É necessário declarar uma estrutura de dados contida na matriz para termos métricas de armazenamento e assim
//usar alocação dinâmica para criar e depois percorrer a matriz:

//Estrutura de dados dos elementos da matriz:

using namespace std;
struct LabyrinthCell
{
    short int Region;
};

struct BoolCell
{
    short int BoolCell;
};

struct Matrix
{
    short int n = SizeRecon();
    unsigned short int matrices = HowMuchMatrixes();
    LabyrinthCell *Labyrinth = (LabyrinthCell*) malloc(n*n*sizeof(LabyrinthCell));
};

struct BoolMatrix
{
    short int size = SizeRecon()-1;
    BoolCell *Bool2D = (BoolCell*) malloc(size*size*sizeof(BoolCell));
};

struct Coordinate 
{
    unsigned short int i, j;
    unsigned short int MatrixOfPosition = 0;
};

struct SignedCoordinate 
{
    short int i, j;
    short int MatrixOfPosition = 0;
};


struct TravelBackTotem
{
    Coordinate *Memory = (Coordinate*)malloc(4*sizeof(Coordinate));
};


/// @brief A estrutura abaixo representa um jogador que caminha pelos labirintos
/// @param Steps Número de passos realizados.
/// @param PossibleSteps Número de passos possíveis
/// @param KnownCoordinates Número de casas passíveis de serem percorridas que foram exploradas
/// @param UnknownCoordinates Número de casas passíveis de serem percorridas que não foram exploradas
/// @param Bag Soma total do valor dos valores de cada item.
/// @param ItemsGrasped Soma total de itens pegos.
/// @param Life Pontos de vida do jogador.
/// @param DangersFaced Casas que tiram 1 ponto de vida e foram exploradas
/// @param MatrixOfTheMomment Matriz onde o jogador se encontra no momento.
/// @param Roundabout Simboliza um artefato em formato de rotunda com espaços vazios, estes são preenchidos quando o jogador sai de uma matriz sem pegar itens.
/// @param WinCondition Simboliza um objeto que mata o jogador quando sua rotunda é preenchida.
/// @param DefeatCombo Conta os espaços preenchidos da rotunda.
/// @param TookA0Yet Simboliza um artefato que mostra se o jogador já pegou um item enquanto percorre uma matriz específica.
struct PlayerStatus
{
    //Passos dados:
    unsigned short int Steps = 0;

    //Passos possíveis
    unsigned short int PossibleStep = 0;

    //Representa quantas casas foram percorridas ao todo:
    short int KnownCoordinates = 0;

    //Representa quantas casas possíveis de serem exploradas não alcançadas:
    unsigned short int UnknownCoordinates = 0;

    //Soma total do valor dos itens:
    unsigned short int Bag = 0;

    //Soma da quantidade de itens agarrados:
    unsigned short int ItemsGrasped = 0;

    //Itens consumidos:
    unsigned short int ItensConsumed = 0;

    //Vida:
    unsigned short int Life = 10;

    //Perigos enfrentados:
    unsigned short int DangersFaced = 0;

    //Número do labirinto em que o jogador está no momento:
    unsigned short int MatrixOfTheMomment = 0;

    //Vetor que armazena as últimas posições percorridas em diferentes matrizes de valor de item 0
    SignedCoordinate *Roundabout = (SignedCoordinate*)malloc(HowMuchMatrixes()*sizeof(SignedCoordinate));

    //Condição de vitória, pode ser verdadeira ou não:
    bool WinCondition = true;

    //Combo da derrota que soma 1 valor quando a rotunda tem 1 espaço preenchido.
    unsigned short int DefeatCombo = 0;

    //Variável que mostra se um item de valor 0 já foi pego na matriz percorrida:
    bool TookA0Yet = false;
};


using namespace std;

void GenerateMatrix(Matrix *MatrixStructure);

void SetMatrixSignature(Matrix *MatrixStructure);

void SaveMatrix(Matrix MatrixStructure);

unsigned short int RandomGenerator(unsigned short int a, unsigned short int b);

string PathDefinerInitial(unsigned short int MatrixesReaded);

char * PathDefiner(unsigned short int MatrixesReaded);

void ClearFile(FILE *AimedFile, string Path, unsigned short int SizeOfMatrix, unsigned short int NumberOfMatrixes);

void FileUpdate(unsigned short int *MatrixesReaded , Matrix MatrixLabyrinth, string PathOutput, long int *writePointer);

void  Jogar(unsigned short int Size, unsigned short int NumOfMatrixes, unsigned short int *MatrixesReaded, string Path, bool *Over);

void IniciaJogo();

Coordinate CoordinateDefinition(unsigned short int size, Coordinate NowPosition, bool N, bool NW, bool W, bool SW, bool S , bool E, bool SE, bool NE);

Coordinate Spawn(unsigned short int size);

unsigned short int* RoadMapDefiner(vector<unsigned short int> Steps,unsigned short int HowManySteps);

void MapOfTheJourney(unsigned short int *iRoute,unsigned short int *jRoute,unsigned short int size, unsigned short int NumberOfSteps);

void RoadMapViewer(unsigned short int *iRoute,unsigned short int *jRoute, unsigned short int HowManySteps, LabyrinthCell *FinalMatrix,unsigned short int size, unsigned int *GlobalSum);

void JourneyMetrics(unsigned short int ReadedMatrixes, unsigned int GlobalSum);

void CreatingCoordinates(unsigned short int size,unsigned short int i,unsigned short int j, bool *N,bool *NW,bool *W,bool *SW, bool *S , bool *E, bool *SE, bool *NE, Matrix *MatrixLabyrinth);

Coordinate NextStep(unsigned short int size, Matrix *MatrixStructure, Coordinate NowPosition,bool N,bool NW,bool W,bool SW, bool S , bool E, bool SE, bool NE);

bool MatrixOnRoundabout(PlayerStatus *player);

void UpdatingPlayerRoundabout(PlayerStatus *player, Coordinate ActuallyPlace, unsigned short int ActuallyValue);

void PlayerAndLabyrinthUpdate(PlayerStatus *player, Coordinate ActuallyPlace, Matrix *MatrixStructure);

void LabyrinthStatusUpdate(Coordinate ActuallyPlace, Matrix *MatrixStructure);

void MatrixScanning(Matrix *MatrixLabyrinth);

void ResumeOfJourney(PlayerStatus Player);

bool PlayerIsDead(PlayerStatus PlayerOne);

bool GameOver(PlayerStatus PlayerOne, bool *Over, unsigned short int MatrixReaded);


//Gerar um arquivo com as matrizes de uso;
//Conseguir ler essas matrizes e passar por parâmetro para minha função


#endif


//referências:  https://youtu.be/Gp2m8ZuXoPg?t=1343 , 
//              https://github.com/mpiress/GenerateDataToMatrix/blob/main/src/mat.h

//Descoberta interessante: Não se pode dar malloc dentro de um struct, mas por quê?
//            tentativa: Pois a estrutura ainda não foi alocada na memória e malloc
//            requisita uma instrução de alocação de memória. Portanto não se pode espaço
//            de uma estrutura que ainda não tem seu tamanho de alocação pré-definido, acredito
//            que isso aconteça pelo fato de que é necessário ter uma estrutura completamente declada
//            para que ela seja depois disso alocada na memória.

//Proposta de Melhoria: Criar um jeito de ter um número aleatório no lugar de TAM sem ter problemas
// com alocação de memória, de forma que esse número esteja por exemplo pré-processado em um arquivo.

