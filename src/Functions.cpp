
#include "structures.hpp"

using namespace std;

//================= Funções para funcionamento do programa =================

/// @brief GEra um número aleatório entre 2 valores
/// @param Higher Maior valor possível gerado
/// @param Lower Menor valor possível gerdao
/// @return Valor aleatório entre Higher e Lower
unsigned short int RandomGenerator(unsigned short int Higher, unsigned short int Lower)
{
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(Higher, Lower);
    return dis(gen);
}

bool VerifyPositionGenerated(Coordinate NowPosition, Coordinate NewPosition)
{
    if(abs(NowPosition.i - NewPosition.i)>1 || abs(NowPosition.j - NewPosition.j)>1)
        return true;
    
    else
        return false;

}

Coordinate CoordinateDefinition(unsigned short int size, Coordinate NowPosition,bool N,bool NW,bool W,bool SW, bool S , bool E, bool SE, bool NE)
{
    Coordinate Position;
    
    // cout<<"N:"<<N<<" ";
    // cout<<"NW:"<<N<<" ";
    // cout<<"W:"<<W<<" ";
    // cout<<"SW:"<<SW<<" ";
    // cout<<"S:"<<S<<" ";
    // cout<<"E:"<<E<<" ";
    // cout<<"SE:"<<SE<<" ";
    // cout<<"NE:"<<NE<<" ";
        

    //Criar um vetor com todas as casa adjascentes possíveis de caminhamento
    string PossibleCoordinatesStr[8] = {"N"," NW", "W", "SW", "S", "E", "SE", "NE"};
    int PossibleCoordinatesBool[8] = {N, NW, W, SW, S, E, SE, NE};  

    short int TrueCases[8] = {-1,-1,-1,-1,-1,-1,-1,-1};

    unsigned short int FalseCasesCounter, TrueCasesCounter = 0;


    for(unsigned short int i = 0; i < 8; i++)
    {
        
        if((PossibleCoordinatesBool[i]) == (true))
        {

            TrueCases[TrueCasesCounter] = i;
            cout<<PossibleCoordinatesStr[i]<<"\t";
            TrueCasesCounter+=1;
        }
        else
            FalseCasesCounter+=1;

        //cout<<PossibleCoordinatesStr[i]<<"@"<<PossibleCoordinatesBool[i]<<"\n";
    }

    //Criar um acesso aleatório de índice
    
    if(FalseCasesCounter==8)
    {
        Position.i = NowPosition.i;
        Position.j = NowPosition.j;
    }

    else
    {        
        unsigned short int Key = RandomGenerator(0,TrueCasesCounter-1);
        // cout<<Key;
        unsigned short int NextStepCoordinateIndex = TrueCases[Key];

        if(NextStepCoordinateIndex == 0)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i-1;
            Position.j = NowPosition.j;
        }
        else if(NextStepCoordinateIndex == 1)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i-1;
            Position.j = NowPosition.j-1;    
        }
        else if(NextStepCoordinateIndex == 2)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i;
            Position.j = NowPosition.j-1;
        }
        else if(NextStepCoordinateIndex == 3)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i+1;
            Position.j = NowPosition.j-1;
        }
        else if(NextStepCoordinateIndex == 4)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i+1;
            Position.j = NowPosition.j;
        }
        else if(NextStepCoordinateIndex == 5)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i;
            Position.j = NowPosition.j+1;    
        }
        else if(NextStepCoordinateIndex == 6)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i+1;
            Position.j = NowPosition.j+1;
        }
        else if(NextStepCoordinateIndex == 7)
        {
            // cout<<"Caminhei para -> \t"<<PossibleCoordinatesStr[NextStepCoordinateIndex];
            Position.i = NowPosition.i-1;
            Position.j = NowPosition.j+1;
        }

        else
        {
            cout<<"ESTOU PARADO E VOU MORRER!\n"<<NextStepCoordinateIndex<<"\n&&&\n\t\n\t";
            cout<<NextStepCoordinateIndex<<"\t"<<Key<<"\t"<<"\n";
            for(int i = 0;i<TrueCasesCounter;i++)
            {
                cout<<"\n";
                cout<<TrueCases[i]<<"$";
            }
        }

        // //TO DO:
        //     //Caso esteja cercado por paredes
        // //Assim que um dos índices desse vetor for escolhido validar se essa posição é válida ou não
        // //Se essa posição não for válida sortear outro índice para ser  acessado
    }

    return Position;
    
}

Coordinate Spawn(unsigned short int size, Matrix MatrixLabyrinth)
{

    Coordinate Position;
    bool CreatePosition = true;
    Position.i = RandomGenerator(1,size-1);
    Position.j = RandomGenerator(1,size-1);
    
    //(MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * Position.i + Position.j].Region == '#') || (Position.j==(size-1))
    while(CreatePosition)
    {

        short int a = (MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * Position.i + Position.j].Region);
        //OBS: mais caro comparar se é menor do que igual afinal existe instrução direta em Assembly para comparar se é diferente:
        if((MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * Position.i + Position.j].Region != -2) && (Position.j!=(size-1))) CreatePosition = false;

        else
        {
            Position.i = RandomGenerator(1,size-1);
            Position.j = RandomGenerator(1,size-1);
        }
    
    }
    cout<<"POSITION ===>"<<Position.i<<Position.j<<"(("<<((MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * Position.i + Position.j].Region == -2) || (Position.j==(size-1)))<<"))";
    cout<<"ELEMENTO:"<<MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * Position.i + Position.j].Region;

    return Position;
}

void CreatingCoordinates(unsigned short int size,unsigned short int i,unsigned short int j, bool *N,bool *NW,bool *W,bool *SW, bool *S , bool *E, bool *SE, bool *NE,Matrix *MyLabyrinth)
{
   

    //Passos verticais e horizontais para qualquer i e j:

    //Posso ir para cima se ao retroceder uma casa eu ainda for maior ou igual a 1:
    bool UpAllowed = ((i-1)>=1);

    //Posso ir para baixo se ao avançar uma casa eu ainda for menor ou igual ao tamanho da matriz:
    bool DownAllowed = ((i+1)<=(size-1));


    //Posso ir para a esquerda se ao retroceder uma casa eu aindo for maior ou igual a 1:
    bool LeftAllowed = ((j-1)>=1);

    //Posso ir para baixo se ao avançar uma casa eu ainda for menor ou igual ao tamanho da matriz:
    bool RightAllowed = ((j+1)<=(size-1));
    
    //Passos diagonais para qualquer i e j:
    bool DiagonallyLeftDown = (DownAllowed && LeftAllowed);
    bool DiagonallyLeftUp = (UpAllowed && LeftAllowed);
    bool DiagonallyRightDown = (DownAllowed && RightAllowed);
    bool DiagonallyRightUp = (UpAllowed && RightAllowed);

    //Se eu estiver adjascente a casa inicial e o próximo passo randomico for a parede que eu nasci eu finalizo o jogo

    *E = ( ( RightAllowed ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * i + (j+1)].Region==(-2)));
    
    *N = ( ( UpAllowed ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i-1) + j].Region==(-2)));
    
    *W = ( ( LeftAllowed ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * i + (j-1)].Region==(-2)));
    
    *S = ( ( DownAllowed ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i+1) + j].Region==(-2)));
    
    *SW = ( ( DiagonallyLeftDown ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i+1) + (j-1)].Region==(-2)));
    
    *SE = ( ( DiagonallyRightDown ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i+1) + (j+1)].Region==(-2)));    
    
    *NE = ( ( DiagonallyRightUp )  && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i-1) + (j+1)].Region==(-2)));
    
    *NW = ( ( DiagonallyLeftUp ) && !(MyLabyrinth->Labyrinth[MyLabyrinth->n * (i-1) + (j-1)].Region==(-2)));
    
}


// * * 16 
// * # 12 
// * 48 # 

// 12 * # 
// * * 1 
// 22 1 # 

//Não pegar o item no lugar que spwnar.
//Nunca Spawnar em parede (' # ').
//Nunca Spawnar no teleporte.
//



void DangerAlert(PlayerStatus *player)
{
    player->Life -= 1;
    player->DangersFaced += 1;
}

void BagAlert(PlayerStatus *player, Coordinate ActuallyPlace, Matrix *MatrixStructure, short int PositionValue)
{
    player->Bag+=PositionValue;
    player->ItemsGrasped+=1;
    MatrixStructure->Labyrinth[MatrixStructure->n * ActuallyPlace.i + ActuallyPlace.j].Region = 0;

    if((player->ItemsGrasped%4==0)&&(player->ItemsGrasped!=0) && (player->Life<10))
    {
        player->Life+=1;
        player->ItensConsumed+=1;
    }
}

/// @brief Limpa todos os valores que estão dentro da rotunda.
/// @param Roundabout Espaço onde matrizes percorridas sme captura de itens são gravadas.

void RestartRoundabout(SignedCoordinate *Roundabout)
{

    for(short int i=0;i<HowMuchMatrixes();i++)
    {
        Roundabout[i].i=(-1);
        Roundabout[i].j=(-1);
        Roundabout[i].MatrixOfPosition=-1;
    }
}

/// @brief Verifica se a matriz sendo percorrida no momento já foi adicionada na rotunda ou não.
/// @param Roundabout Espaço onde matrizes percorridas sem captura de itens são gravadas.
/// @param MatrixOfTheMomment Matriz onde o percurso está sendo realizado.
/// @return true se a matriz não está na rotunda e false se ela está na rotunda.
bool MatrixNotOnRoundabout(SignedCoordinate *Roundabout, unsigned short int MatrixOfTheMomment)
{
    bool OnRoundabout = false;

    for(short int i=0;i<HowMuchMatrixes();i++)
    {
        //Se a matriz não está no Roundabout
        if(MatrixOfTheMomment!=Roundabout[i].MatrixOfPosition) OnRoundabout = (OnRoundabout || true);
        else return false;
    }

    return OnRoundabout;
}

/// @brief Atualiza as variáveis relacionadas à um circuito onde o jogador não pega itens.
/// @param player Jogador com atributos de percorrimento do labirinto
/// @param ActuallyPlace Posição atual
/// @param ActuallyValue Valor da posição atual
void UpdatingPlayerRoundabout(PlayerStatus *player, Coordinate ActuallyPlace, unsigned short int ActuallyValue)
{
    short int i = player->Roundabout[0].i;
    short int j = player->Roundabout[0].j;
    short int M = player->Roundabout[0].MatrixOfPosition;

    //Se o jogador ainda não pegou 1 zero na matriz local
    if(player->TookA0Yet==false && ActuallyValue == 0 && (MatrixNotOnRoundabout(player->Roundabout, (player->MatrixOfTheMomment+1))))
    {       
        player->Roundabout[player->MatrixOfTheMomment-1].i = ActuallyPlace.i;
        player->Roundabout[player->MatrixOfTheMomment-1].j = ActuallyPlace.j;
        player->Roundabout[player->MatrixOfTheMomment-1].MatrixOfPosition = player->MatrixOfTheMomment;

        player->DefeatCombo+=1;
        cout<<"Combo da derrota está em:"<<player->DefeatCombo;
    }

    //Se a matriz que você se encontra é igual a primeira matriz onde capturou zeros:

    //Caso o jogador tenha pego 0 percorrendo todas as matrizes e pisar na posição inicial ele perde
    else if( (ActuallyValue<=0) && (player->DefeatCombo == HowMuchMatrixes()+1) && (player->Roundabout[0].MatrixOfPosition==player->MatrixOfTheMomment) )
    {       
        //Caso onde o jogador pisou na posição inicial realizando uma rotunda como trajeto:
        if( (ActuallyPlace.i == player->Roundabout[0].i) && (ActuallyPlace.j == player->Roundabout[0].j) )  player->WinCondition = false;
        else return;
    }

    //Caso ele pise em um * nada acontece
    else if(ActuallyValue==-1)  return;

    //Caso o jogador pegue um item a rotunda é esvaziada:
    else if(ActuallyValue>0 && player->TookA0Yet)  
    {
        RestartRoundabout(*&player->Roundabout);
        player->TookA0Yet = false;
        cout<<"AQUI O VETOR SERIA COMPLETAMENTE APAGADO!!";
        player->DefeatCombo = 0;
    }

    //Caso ainda não resolvido:
    else
    {
        return;
    }
}

void PlayerAndLabyrinthUpdate(PlayerStatus *player, Coordinate ActuallyPlace, Matrix *MatrixStructure, unsigned short int NowMatrix)
{
    // (MatrixStructure->Labyrinth[MatrixStructure->n * ((ActuallyPlace.i)) + ((ActuallyPlace.j))].Region);
    short int PositionValue = (MatrixStructure->Labyrinth[MatrixStructure->n * ((ActuallyPlace.i)) + ((ActuallyPlace.j))].Region);

    player->Steps+=1;
    
    player->MatrixOfTheMomment = NowMatrix+1;

    UpdatingPlayerRoundabout(&*player, ActuallyPlace, PositionValue);

    //Se o jogar pisa no -1:
    if((PositionValue)==(-1)) DangerAlert(&*player);

    // Se o jogador pegar um zero:
    else if(PositionValue == 0)    player->TookA0Yet=true;
    
    //Se o jogador pegar um item:
    else if((PositionValue>0) && (PositionValue<=999))
    {
        BagAlert(&*player, ActuallyPlace, &*MatrixStructure, PositionValue);
    }

    else
    {
       cout<<"PAREDE!!";
    }
}

void MatrixScanning(Matrix *MatrixLabyrinth)
{
    for(int i=0;i<(MatrixLabyrinth->n-1);i++)
    {   
        cout<<"\n";
        for(int z=0;z<(MatrixLabyrinth->n-1);z++)
            cout<<MatrixLabyrinth->Labyrinth[MatrixLabyrinth->n * ((i)+1) + ((z) + 1)].Region<<"\t";
    }
}

void ResumeOfJourney(PlayerStatus Player, short int Cycles)
{
    cout<<"========================Resumo da Trilha=================================\n";
    cout<<"\n -> Itens pegos: "<<Player.ItemsGrasped<<"Itens. \n";
    cout<<"\n -> Total de casas exploradas: "<<Player.KnownCoordinates<<"\n";
    cout<<"\n -> Total de itens consumidos: "<<Player.ItensConsumed<<"\n";
    cout<<"\n -> Total de perigos enfrentados: "<<Player.DangersFaced<<"\n";
    cout<<"\n -> Número total de passos: "<<Player.Steps<<"\n\n";
    cout<<"\n -> Pontos de vida ao final da caminhada:"<<Player.Life<<"\n\n";
    cout<<"=========================================================================\n";
}


bool PlayerIsDead(PlayerStatus PlayerOne)
{
    if(PlayerOne.Life==0)
    {   
        return true;
    }

    else
    {
        return false;
    }
}

bool PlayerOnRoundabout(PlayerStatus PlayerOne)
{
    if(PlayerOne.WinCondition==false)
    {
        return true;
    }
    
    else
        return false;

}

bool GameOver(PlayerStatus PlayerOne, bool *Over, unsigned short int MatrixReaded)
{

    if(PlayerIsDead(PlayerOne) || PlayerOnRoundabout(PlayerOne)) return true;

    else return false;
}

/*"Voltando no Tempo":
    IDEA INTERESSANTE: Criar uma pilha onde caso meu personagem se encontre preso

    1 - Ele escolhe o último elemento de coordenadas da pilha como próximo passo
        1.2 -Não considerando a posição anterior como uma possível ele reavalia a trajetória.
        MÉTODO:
            Insere a posição ruim em uma lista de lugares para não se caminhar.

    2 - Se o próximo passo não está na lista de lugares péssimos ele entra lá.
    3 - Se está na lista de lugares péssimos ele se questiona se ainda da para caminhar.
        3.1 - Se ainda da para caminhar ele caminha
        3.2 - Se não ele finaliza o jogo.
*/

string PathDefinerInitial(unsigned short int MatrixesReaded)
{
    string Path;

    if(MatrixesReaded<HowMuchMatrixes())   Path = "./dataset/input.data";
    
    else 
    {    
        Path = "./dataset/Output.data";
    }
    
    return Path;
}



void ClearFile(FILE *AimedFile, string Path, unsigned short int SizeOfMatrix, unsigned short int NumberOfMatrixes)
{
    AimedFile = fopen(Path.c_str(),"w");

    unsigned short int RangeOfClear = (NumberOfMatrixes+3)*(SizeOfMatrix*2); 

    for(int i=0;i<RangeOfClear;i++)
    {
        fprintf(AimedFile,"\0");
    }

    fclose(AimedFile);
}

void FileUpdate(unsigned short int MatrixesReaded, Matrix MatrixChanges, string Path, unsigned short int *counter, long int *Rewritings, unsigned short int SizeOfMatrixes, unsigned short int NumberOfMatrixes)
{
    

    //Se eu estou escrevendo na primeira linha eu escrevo
    //fprintf(Outs ,"%d %d %d \n", MatrixChanges.n-1, MatrixChanges.n-1, MatrixChanges.matrices);

    // ofstream Outs;
    FILE *Outs;
    if(*Rewritings == NumberOfMatrixes || *Rewritings==0)  
    {
        ClearFile(&*Outs,Path,SizeOfMatrixes,NumberOfMatrixes);
        Outs = fopen(Path.c_str(),"a+");
        fprintf(Outs ,"%d %d %d \n", MatrixChanges.n-1, MatrixChanges.n-1, MatrixChanges.matrices);
        fclose(Outs);
    }
    // Outs = fopen(Path.c_str(),"a+");
     
    if(Outs==NULL) printf("FILE COULD NOT BE OPENED");

    else
    {
        Outs = fopen(Path.c_str(),"a+");
    //Criar uma função ReadCheckpoint e WriteCheckpointe:
        //Nessas funções descarta ou utiliza a primeira linha
        //
        // Outs = fopen(Path.c_str(),"a+");
        // if(MatrixesReaded==1)   Outs<<MatrixChanges.n-1<<" "<<MatrixChanges.n-1<<" "<<MatrixChanges.matrices<<" "<<"\n";

        

        // if((MatrixesReaded%HowMuchMatrixes())==1)
        // {   
        //     fprintf(Outs ,"%d %d %d \n", MatrixChanges.n-1, MatrixChanges.n-1, MatrixChanges.matrices);
        // }
        
        for(int index1=1;index1<=MatrixChanges.n-1;index1++)
        {
            for(int index2=1;index2<=MatrixChanges.n-1;index2++)
            {
                fprintf(Outs, "%d ", MatrixChanges.Labyrinth[MatrixChanges.n * (index1) + (index2)].Region);
            }

            fprintf(Outs, "%c",'\n');
        }
        fprintf(Outs, "%c" ,'\n');
    }
    
    
    if(*counter>=1) cout<<"EU TENTEI ESCREVER 2 MATRIZES";

    fclose(Outs);
    *Rewritings+=1;

}



void NullingSteps(SignedCoordinate *elements)
{
    short int constant = HowMuchMatrixes()*SizeRecon()*SizeRecon();
    for(short int i=0;i<constant;i++)
    {
        elements->i = -1;
        elements->j = -1;
        elements->MatrixOfPosition = -1;
    }
}

bool SearchInSteps(Coordinate Position, SignedCoordinate *elements, short int MatrixesLocallyReaded)
{
    short int length = SizeRecon()*SizeRecon()*HowMuchMatrixes();
    for(short int x;x<length;x++)
    {
        if((elements[x].i == Position.i) && (elements[x].j == Position.j) && (elements[x].MatrixOfPosition==MatrixesLocallyReaded)) return false;
    }
    return true;
};

void AddStep(SignedCoordinate *elements, Coordinate NowPosition, short int MatrixesLocallyReaded, short int *counter)
{


    
    if(SearchInSteps(NowPosition, &*elements, MatrixesLocallyReaded))
    {
        elements[*counter].i = NowPosition.i;
        elements[*counter].j = NowPosition.j;
        elements[*counter].MatrixOfPosition = MatrixesLocallyReaded;
        *counter+=1;
    }
    else
        return;
}

void Jogar(unsigned short int Size, unsigned short int NumOfMatrixes, unsigned short int *MatrixesReaded, bool *Over, PlayerStatus *PlayerOne, short int *Cycle, short int *CounterELements, SignedCoordinate *elements)
{

    //Criando variáveis úteis:
    string Line,Path;
    char string_generic[1];
    char *CharPointer = string_generic;
    Matrix MatrixLabyrinth;
    MatrixLabyrinth.Labyrinth;
    unsigned short int MatrixLines = 0;
    unsigned short int MatrixColumns = 0;
    long int Rewrites = 0;
    int count = 1;
    Coordinate NowPosition;
    bool N, NW, W, SW, S, SE, E, NE;
    bool RoundAbout;
    unsigned short int MatrixesLocallyReaded = 0;
    

    //Definindo PATH:
    Path = PathDefinerInitial(*MatrixesReaded);


    //Abrindo o arquivo:
    ifstream File(Path);

    //Tirar o cout e usar *
    

    // Percorrendo arquivo linha por linha e armazenando em Line:
    while (getline(File, Line))
    {
        
        // Criando um pointeiro de char do tamanho da linha do arquivo:
        char *copy = new char[Line.length() + 1];

        // Passando os dados de Line para copy e selecionando os dados desejados:
        strcpy(copy, Line.c_str());
        CharPointer = strtok(copy, " \n \0");


        if (count >= 2)
        {
            
            //Ponto onde a leitura de uma matriz foi finalizada dentro do arquivo:
            if(MatrixLines==(Size-1))
            {    
                // if(*MatrixesReaded==4)
                // {
                //     MatrixScanning(&MatrixLabyrinth);
                //     exit(0);
                // }
                *MatrixesReaded;
                NowPosition = Spawn(Size,MatrixLabyrinth);
                AddStep(&*elements, NowPosition, MatrixesLocallyReaded,&*CounterELements);

                Coordinate LastPosition;
                

                MatrixScanning(&MatrixLabyrinth);
                // Consertar a soma

                //Função de caminhamento vem aqui:
                //MatrixScanning(&MatrixLabyrinth);                
                
                MatrixLines=0;
                MatrixColumns=0;

                while(NowPosition.j<(Size))
                {
                    


                    //Criar aqui uma Matriz booleana:
                     
                    //Função 1 Criar uma matriz booleana de tamanho Size com 0.

                    //Função 2 Dar match da posição atual na matriz booleana.
                        

                    //Verifiando para onde se pode andar:
                    CreatingCoordinates(Size, NowPosition.i, NowPosition.j, &N, &NW, &W, &SW, &S, &E, &SE, &NE, &MatrixLabyrinth);
                    //Gravando o último passo:
                    LastPosition.i = NowPosition.i;
                    LastPosition.j = NowPosition.j;

                    //Gerando o próximo passo:                
                    NowPosition = CoordinateDefinition(Size, NowPosition, N, NW, W, SW, S, E, SE, NE);
                    AddStep(&*elements, NowPosition, MatrixesLocallyReaded,&*CounterELements);


                    cout<<"\n\nHP:"<<PlayerOne->Life<<"  I'm on =>>=>>=>>"<<NowPosition.i<<"\t"<<NowPosition.j<<"\t"<<"Size:"<<Size<<"\t"<<"value:"<<MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * NowPosition.i + NowPosition.j].Region<<"\n";

                    //Verificando se o último passo é igual ao passo atual:
                    if(LastPosition.i == NowPosition.i && LastPosition.j == NowPosition.j)
                    {
                        cout<<"FIM DE JOGO ESTOU PRESO";
                        cout<<MatrixLines<<MatrixColumns;
                        break;
                    }

                 
                    //Atualizando a matriz mapa e os status do jogador:
                    PlayerAndLabyrinthUpdate(&*PlayerOne, NowPosition, &MatrixLabyrinth, MatrixesLocallyReaded);
                    *MatrixesReaded+=1;

                    //Teste de derrota:
                    *Over = GameOver(*PlayerOne, &*Over, *MatrixesReaded);

                    cout<<*Over;
                    
                    //Se perder:
                    if(*Over)
                    {
                        PlayerOne->KnownCoordinates = *CounterELements;
                        ResumeOfJourney(*PlayerOne, *Cycle);
                        cout<<"SHUTOWUT";
                        unsigned short int counter=0;
                        return;
                    }
                    
                    //Se teleportar:
                    else if(NowPosition.j == (Size-1)) 
                    {
                     
                        //Finalizar a matriz booleana
                            //Adicionar 1 das posições únicas ao contador de posições únicas do seu jogador
                        *Cycle+=1;
                        PlayerOne->TookA0Yet = false;
                        MatrixesLocallyReaded+=1;
                        unsigned short int counter=0;
                        FileUpdate(*MatrixesReaded ,MatrixLabyrinth, "./dataset/Output.data", &counter, &Rewrites, (Size-1), NumOfMatrixes);
                        MatrixScanning(&MatrixLabyrinth);
                        
                        break;
                        
                    }
                    

                }
            }
            
            else
            {
                MatrixColumns = 0;
                MatrixLines += 1;
            }
        }

        

        while (CharPointer != NULL && MatrixLines!=0)
        {
            
            /*
                Chega um momento onde o número de matrizes lidas é maior que NumOfMatrixes
                com isso o código começa a Translator = atoi('*') e Translator = atoi('#')
            */
            MatrixColumns += 1;
            
            
            
            int Translator;
            
            if((*CharPointer=='#') && (MatrixesLocallyReaded<NumOfMatrixes))
            {    
                Translator = -2;
            }
            else if((*CharPointer=='*') && (MatrixesLocallyReaded<NumOfMatrixes))
            {
                Translator = -1;
                PlayerOne->PossibleStep+=1;
            }
            else
            {
                Translator = atoi(CharPointer);
                PlayerOne->PossibleStep+=1;
            }
            MatrixLabyrinth.Labyrinth[MatrixLabyrinth.n * (MatrixLines) + (MatrixColumns)].Region = Translator;
            
            CharPointer = strtok(NULL, " \n \0");
        }
        count += 1;
        
    }

    *MatrixesReaded;
    cout<<"qlqr coisa"<<endl;
    MatrixScanning(&MatrixLabyrinth);

    
    if(MatrixesLocallyReaded==HowMuchMatrixes())
    {
        cout<<"Atualizando tudo!";
        getline(File, Line);
        cout<<"voltei pra ficar em: "<<Line<<"\n";
        File.close();
    }
}



void IniciaJogo()
{
    short int CounterElements = 0;
    SignedCoordinate elements[(HowMuchMatrixes()*SizeRecon()*SizeRecon())];
    NullingSteps(&*elements);
    unsigned short int MatrixesReaded = 0;
    short int CycleOfRead = 0;
    bool Over=false;
    PlayerStatus PlayerOne;
    RestartRoundabout(&*PlayerOne.Roundabout);

    //Escrever corretamente no arquivo para conseguir ler matrizes editadas
    while(!Over)
    {
        
        Jogar(SizeRecon(), HowMuchMatrixes(), &MatrixesReaded, &Over, &PlayerOne, &CycleOfRead, &CounterElements, &*elements);
    }

}

//Abre o arquivo de saída 1º vez = APAGA A PORRA TODA:
    //1ª Escrita
        //V