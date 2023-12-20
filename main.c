//
//  main.c 플레이어 및 전반적인 게임 흐름 구현 
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



//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
void generatePlayers(int n, int initEnergy); //generate a new player
void printGrades(int player); //print grade history of the player
void goForward(int player, int step); //make player go "step" steps on the board (check if player is graduated)
void printPlayerStatus(void); //print all player status at the beginning of each turn
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player)
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
void printGrades(int player); //print all the grade history of the player
#endif




int rolldie(int player)
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
    char name[MAX_CHARNAME]; // 이름, 유형, 학점, 에너지 
    int type;
    int credit;
    int energy;
    int i;

    board_nr = 0;
    food_nr = 0;
    festival_nr = 0;

    srand(time(NULL));


    //1. import parameters ---------------------------------------------------------------------------------
    //1-1. boardConfig 
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL) //fopen: 파일 이름을 통해 파일 열기 
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar(); //한 줄씩 데이터 가져오기
        return -1;
    }

    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //fscanf로 네 가지 데이터를 읽어오기, fscanf 함수의 출력은 성공적으로 읽은 값의 개수와 같다. read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy);
        board_nr++;
    }
    fclose(fp);
    printf("Total number of board nodes : %i\n", board_nr);

    for (i = 0;i<board_nr;i++)
        printf("node %i: %s, %i, %i\n", i, smmObj_getNodeName(i), smmObj_getNodeType(i), smmObj_getNodeEnergy(i));

    //2. food card config 
    if ((fp = fopen(FOODFILEPATH,"r")) == NULL)
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", FOODFILEPATH);
        getchar(); //한 줄씩 데이터 가져오기
        return -1;
    }

    printf("\n\nReading food card component......\n");
    while ( fscanf(fp, "%s %i", name, &energy) == 2 ) //fscanf로 두 가지 데이터를 읽어오기, fscanf 함수의 출력은 성공적으로 읽은 값의 개수와 같다. read a food parameter set
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
        getchar(); //한 줄씩 데이터 가져오기
        return -1;
    }

    printf("\n\nReading festival card component......\n");
    while ( fscanf(fp, "%s", name) == 1 ) //fscanf로 두 가지 데이터를 읽어오기, fscanf 함수의 출력은 성공적으로 읽은 값의 개수와 같다. read a food parameter set
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
    /*
    do
    {
        //input player number to player_nr
    }
    while ();
    generatePlayers();
    */
#if 0
    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while () //is anybody graduated? 일단 무한 반복
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
