

#include "ReadSignatures.hpp"

using namespace std;

/// @brief Lê a primeira linha do arquivo input.data e retorna uma variável que representa o tamanho das matrizes contidas nesse arquivo
/// @return O tamanho das matrizes à serem lidas
unsigned short int SizeRecon()
{
    unsigned short int ArrayArea = 0;
    FILE *LocalPointer;
    LocalPointer = fopen("./dataset/input.data", "r");
    fscanf(LocalPointer, "%hu", &ArrayArea);
    fclose(LocalPointer);
    return (ArrayArea+1);
}

unsigned int HowMuchMatrixes()
{
    int size;
    string strNumberOfMatrixes;
    string FirstLine;
    FILE *LocalPointer;
    LocalPointer = fopen("./dataset/input.data", "r");
    char l2[100];
    FirstLine = fgets(l2,100,LocalPointer);
    fclose(LocalPointer);

    
    if(FirstLine.at(FirstLine.length()-3)==' ')// Número de matrizes < 10:
    {
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-2);
    }
    else if(FirstLine.at(FirstLine.length()-4)==' ')//Número de matrizes <100:
    {
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-3);
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-2);
    }
    else if(FirstLine.at(FirstLine.length()-5)==' ')//Número de matrizes <1000:
    {
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-4);
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-3);
        strNumberOfMatrixes+=FirstLine.at(FirstLine.length()-2);
    }

    // char AuxChar = (char)strNumberOfMatrixes;

    std::string::size_type sz;
    unsigned int NumberOfMatrixes = std::stoi(strNumberOfMatrixes,&sz);
    
    return NumberOfMatrixes;
}