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

static int player_nr;

static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME]; // 나열되어 있는 배열 중 i번째 노드의 플레이어 이름과 위치, 에너지  

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

void generatePlayers(int n, int initEnergy) //generate a new player, n명의 플레이어, initEnergy는 에너지 초기화. 
{
     int i;
     //n time loop
     for (i=0;i<n;i++) //플레이어가 n번 있다고 가정한다. 
     {
         //input name
         printf("Input player %i's name:", i); 
         scanf("%s", player_name[i]);
         fflush(stdin); //while 문 사용 시에 buffer 안에 잔재가 남아 이름으로 들어갈 수도 있다. 

         //set position
         player_position[i] = 0;

         //set energy
         player_energy[i] = initEnergy; //플레이어 별로 값이 있어야하므로 배열로 잡는다. 
     }
}

void printGrades(int player){ //print grade history of the player Player 정보 출력 함수 구현 턴을 돌때마다 플레이어의 정보를 찍는 걸 printf를 이용해서 함수 작성 

}
void goForward(int player, int step) { //make player go "step" steps on the board (check if player is graduated) Player 이동 함수 구현, 다음 주 상어 게임을 하면 구현 가능 

}
int rolldie(int player) // 주사위 굴리기 
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
    char name[MAX_CHARNAME]; // main 함수 내 이름, 유형, 학점, 에너지 변수 선언 
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
    if ((fp = fopen(BOARDFILEPATH,"r")) == NULL) //fopen: 파일 이름을 통해 파일 열기, BOARDFILEPATH 파일  
    {
        printf("[ERROR] failed to open %s. This file should be in the same directory of SMMarble.exe.\n", BOARDFILEPATH);
        getchar(); //한 줄씩 데이터 가져오기
        return -1;
    }

    printf("Reading board component......\n");
    while ( fscanf(fp, "%s %i %i %i", name, &type, &credit, &energy) == 4 ) //fscanf로 네 가지 데이터를 읽어오기, fscanf 함수의 출력은 성공적으로 읽은 값의 개수와 같다. read a node parameter set
    {
        //store the parameter set
        smmObj_genNode(name, type, credit, energy); //main 함수에서 선언한 name, type, credit, energy를 매개변수 자리에 대입한다. 
        if (type == SMMNODE_TYPE_HOME)
           initEnergy = energy;
        board_nr++; // board_nr=0인 상태에서 시작. 
    }
    fclose(fp); //BOARDFILEPATH 파일을 닫는다.  
    printf("Total number of board nodes : %i\n", board_nr); // 네 가지 데이터를 성공적으로 읽은 횟수 16번 

    for (i = 0;i<board_nr;i++) // main 함수에서 선언한 변수i는 성공적으로 네 가지 데이터를 읽은 횟수만큼 더해지고 for문은 반복된다.  
         printf("node %i : %s, %i(%s), credit %i, energy %i\n", 
                     i, smmObj_getNodeName(i), 
                     smmObj_getNodeType(i), smmObj_getTypeName(smmObj_getNodeType(i)),
                     smmObj_getNodeCredit(i), smmObj_getNodeEnergy(i));
        //입력받은 변수 i 값의 노드 이름을 문자열로 출력, 노드 유형(번호)를 숫자로 출력,  숫자에 따른 lecture, restaurant 등을 문자열로 출력. 

    printf("(%s)", smmObj_getTypeName(SMMNODE_TYPE_LECTURE)); //lecture 강의 내에서 유형 이름 출력. 

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

    do
    {
        //input player number to player_nr
        printf("input player no.:");
        scanf("%d", &player_nr);
        fflush(stdin);
    }
    while (player_nr < 0 || player_nr >  MAX_PLAYER); //끝나는 조건을 반대로 걸어 반복시킨다. 
    //while 문은 조건에 부합하지 않으면 반복문 탈출, do-while 문은 조건 부합해야 탈출. MAX_PLAYER=100 main.c에 선언. 

    generatePlayers(player_nr, initEnergy); //i에 따른 player_energy[i]의 값에 따라 initEnergy 값 달라진다. 
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
