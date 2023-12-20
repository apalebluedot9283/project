//
//  main.c �÷��̾� �� �������� ���� �帧 ���� 
//  SMMarble
//
//  Created by Juyeop Kim on 2023/11/05.
//

#include <time.h>
#include <string.h>
#include "smm_object.h"
#include "smm_database.h"
#include "smm_common.h"
#define BOARDFILEPATH "marbleBoardConfig.txt"
#define FOODFILEPATH "marbleFoodConfig.txt"
#define FESTFILEPATH "marbleFestivalConfig.txt"

//board configuration parameters
static int board_nr;
static int food_nr;
static int festival_nr;

static int player_nr;

static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME]; // �����Ǿ� �ִ� �迭 �� i��° ����� �÷��̾� �̸��� ��ġ, ������  

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif

void generatePlayers(int n, int initEnergy) //generate a new player, n���� �÷��̾�, initEnergy�� ������ �ʱ�ȭ. 
{
     int i;
     //n time loop
     for (i=0;i<n;i++) //�÷��̾ n�� �ִٰ� �����Ѵ�. 
     {
         //input name
         printf("Input player %i's name:", i); 
         scanf("%s", player_name[i]);
         fflush(stdin); //while �� ��� �ÿ� buffer �ȿ� ���簡 ���� �̸����� �� ���� �ִ�. 

         //set position
         player_position[i] = 0;

         //set energy
         player_energy[i] = initEnergy; //�÷��̾� ���� ���� �־���ϹǷ� �迭�� ��´�. 
     }
}

void printGrades(int player){ //print grade history of the player Player ���� ��� �Լ� ���� ���� �������� �÷��̾��� ������ ��� �� printf�� �̿��ؼ� �Լ� �ۼ� 

}
void goForward(int player, int step) { //make player go "step" steps on the board (check if player is graduated) Player �̵� �Լ� ����, ���� �� ��� ������ �ϸ� ���� ���� 

}
int rolldie(int player) // �ֻ��� ������ 
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar();
    fflush(stdin);

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1);
}

#if 0
//action code when a player stays at a node
void actionNode(int player)
{
    switch(type)
    {
        //case lecture:
        default:
            break;
    }
}
#endif



int main(int argc, const char * argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME]; // main �Լ� �� �̸�, ����, ����, ������ ���� ���� 
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;

    board_nr = 0; 
    food_nr = 0;
    festival_nr = 0;

    srand(time(NULL)); 


    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL) //fopen: ���� �̸��� ���� ���� ����, BOARDFILEPATH ����  
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar(); //�� �پ� ������ ��������
        return -1;
    }

    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //fscanf�� �� ���� �����͸� �о����, fscanf �Լ��� ����� ���������� ���� ���� ������ ����. read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy); //main �Լ����� ������ name, type, credit, energy�� �Ű����� �ڸ��� �����Ѵ�. 
        if (type == SMMNODE_TYPE_HOME)
           initEnergy = energy;
        board_nr++; // board_nr=0�� ���¿��� ����. 
    }
    fclose(fp); //BOARDFILEPATH ������ �ݴ´�.  
    printf("Total number of board nodes : %i\n", board_nr); // �� ���� �����͸� ���������� ���� Ƚ�� 16�� 

    for (i = 0;i<board_nr;i++) // main �Լ����� ������ ����i�� ���������� �� ���� �����͸� ���� Ƚ����ŭ �������� for���� �ݺ��ȴ�.  
         printf("node %i : %s, %i(%s), credit %i, energy %i\n", 
                     i, smmObj_getNodeName(i), 
                     smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),
                     smmObj_getNodeCredit(i), smmObj_getNodeEnergy(i));
        //�Է¹��� ���� i ���� ��� �̸��� ���ڿ��� ���, ��� ����(��ȣ)�� ���ڷ� ���,  ���ڿ� ���� lecture, restaurant ���� ���ڿ��� ���. 

    printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE)); //lecture ���� ������ ���� �̸� ���. 

    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        getchar(); //�� �پ� ������ ��������
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while ( fscanf(fp, "%s %i", name, &energy) == 2 ) //fscanf�� �� ���� �����͸� �о����, fscanf �Լ��� ����� ���������� ���� ���� ������ ����. read a food parameter set
    {
        //store the parameter set
        smmObj_genFood(name, energy);
        food_nr++;
    }
    fclose(fp);
    printf("Total number of food cards : %i\n", food_nr);
    
    for (i = 0;i<food_nr;i++)
        printf("%s %i\n", smmObj_getFoodName(i), smmObj_getFoodEnergy(i));

    //3. festival card config 
    if ((fp = fopen(FESTFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FESTFILEPATH);
        getchar(); //�� �پ� ������ ��������
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while ( fscanf(fp, "%s", name) == 1 ) //fscanf�� �� ���� �����͸� �о����, fscanf �Լ��� ����� ���������� ���� ���� ������ ����. read a food parameter set
    {
        //store the parameter set
        smmObj_genFest(name);
        festival_nr++;
    }
    fclose(fp);
    printf("Total number of festival cards : %i\n", festival_nr);
    
    for (i = 0;i<festival_nr;i++)
        printf("Fest %i : %s\n", i, smmObj_getFestName(i));


    //2. Player configuration ---------------------------------------------------------------------------------

    do
    {
        //input player number to player_nr
        printf("input player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while (player_nr < 0 || player_nr >  MAX_PLAYER); //������ ������ �ݴ�� �ɾ� �ݺ���Ų��. 
    //while ���� ���ǿ� �������� ������ �ݺ��� Ż��, do-while ���� ���� �����ؾ� Ż��. MAX_PLAYER=100 main.c�� ����. 

    generatePlayers(player_nr, initEnergy); //i�� ���� player_energy[i]�� ���� ���� initEnergy �� �޶�����. 
#if 0
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while () //is anybody graduated? �ϴ� ���� �ݺ�
    {
        int die_result;

        //4-1. initial printing
        //printPlayerStatus();

        //4-2. die rolling (if not in experiment)


        //4-3. go forward
        //goForward();

		//4-4. take action at the destination node of the board
        //actionNode();

        //4-5. next turn

    }
#endif

    system("PAUSE");
    return 0;
}
