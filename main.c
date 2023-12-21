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

static int player_nr; //플레이어 수 

typedef struct player { //player(tag) 구조체 형태의 player_t 변수 선언  
        int energy;
        int position;
        char name[MAX_CHARNAME];
        int accumCredit;
        int flag_graduate; //졸업여부 
} player_t;

static player_t cur_player[MAX_PLAYER]; //player_t 구조체에서 energy, position, name, accumCreditm flag_graduate 변수들 배열로 묶는다. 

#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME]; // 나열되어 있는 배열 중 i번째 노드의 플레이어 이름과 위치, 에너지  
#endif

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player) 수강이력 
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
#endif

void printPlayerStatus(void) //print all player status at the beginning of each turn 플레이어들의 해당 턴이 모두 끝나고 새로운 턴이 돌아왔을 때 플레이어들의 상태 출력 
{
     int i;

     for (i=0;i<player_nr;i++) 
     {
         printf("%s : credit %i, energy %i, position %i\n", 
                      cur_player[i].name, //cur_player 배열 내 name 변수의 값을 출력한다. 
                      cur_player[i].accumCredit, //cur_player 배열 내 accumCredit 변수의 값을 출력한다.
                      cur_player[i].energy, //cur_player 배열 내 energy 변수의 값을 출력한다. 
                      cur_player[i].position); //cur_player 배열 내 position 변수의 값을 출력한다.
     }
}


void generatePlayers(int n, int initEnergy) //generate a new player, n명의 플레이어, initEnergy는 에너지 초기화. 
{
     int i;
     //n time loop
     for (i=0;i<n;i++) //플레이어가 n번 있다고 가정한다. 
     {
         //input name 플레이어 수는 시작시 입력 받으며, 각 플레이어의 이름을 입력받아서 활용될 수 있어야 함. 
         printf("Input player %i's name:", i); 
         scanf("%s", cur_player[i].name); //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 name 변수의 값을 출력한다. 
         fflush(stdin); //while 문 사용 시에 buffer 안에 잔재가 남아 이름으로 들어갈 수도 있다. 

         //set position 
         //player_position[i] = 0;
         cur_player[i].position = 0; //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 position 변수의 값을 출력한다. 
 
         //set energy 시작 시 플레이어는 현재 에너지가 집 노드의 보충 에너지로 초기화되어야 한다. 
          //player_energy[i] = initEnergy; 플레이어 별로 값이 있어야하므로 배열로 잡는다. 
         cur_player[i].energy = initEnergy; //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 initEnergy 변수의 값을 출력한다. 
         cur_player[i].accumCredit = 0; //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 accumCredit 변수의 값을 초기화한다.
         cur_player[i].flag_graduate = 0; //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 flag_graduate 변수의 값을 초기화한다. 
     }
}

void printGrades(int player){ //print grade history of the player Player 정보 출력 함수 구현 턴을 돌때마다 플레이어의 정보를 찍는 걸 printf를 이용해서 함수 작성 
                              //턴 시작 시 모든 플레이어의 상태 (위치, 실험 중 상태, 누적 학점, 현재 에너지) 출력해야. 
}

int rolldie(int player) // 주사위 굴리기 
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //입력된 순으로 플레이어가 돌아가면서 주사위를 던지고 이동한다. 
    fflush(stdin);

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1); //랜덤으로 주사위 눈 나온다. 
}

//action code when a player stays at a node
int ramdom() {
    return (rand() % 6) + 1;  // 1에서 6까지의 랜덤한 숫자 생성
}

void actionNode(int player)

{
     int type = smmObj_getNodeType( cur_player[player].position ); //player_t 구조체에서 여러 변수들 묶었던 cur_player 배열 내 position 변수의 값을 출력한다. 
     cur_player[player].position %= 16;
     switch (type) {
        // 학점은 강의 노드에서만 유의미하며, 강의 수강 후 플레이어가 얻게 되는 학점 수다.
        // 각 플레이어는 자신의 에너지를 관리하면서 적절하게 전공수업을 듣고 졸업 학점(credit)을 채우는 것을 최종 목표로 한다.
        // 현재 에너지가 소요에너지 이상 있고 이전에 듣지 않은 강의이면 수강 가능하며, 수강 혹은 드랍을 선택할 수 있다.
        // 수강하면 성적이 A+, A0, A-, B+..... 중 하나가 랜덤으로 나온다.
        case SMMNODE_TYPE_LECTURE:
            {
                // 현재 에너지가 소요에너지 이상이고, 이전에 듣지 않은 강의인지 여부를 확인
                if (cur_player[player].energy >= smmObj_getNodeEnergy(cur_player[player].position)) {
                    printf("Do you want to attend the lecture? (1: Attend, 2: Drop): ");
                    int choice;
                    scanf("%d", &choice);

                    if (choice == 1) {
                        // 수강 선택
                        cur_player[player].accumCredit += smmObj_getNodeCredit(cur_player[player].position);
                        cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);

                        // 성적 랜덤으로 결정하고 출력 (A+, A0, A-, B+ 등)
                        char* grades[] = {"A+", "A0", "A-", "B+", "B0", "B-", "C+", "C0", "C-"};
                        int randomIndex = rand() % 9; // 0부터 8까지의 랜덤 인덱스
                        printf("You attended the lecture and received grade: %s\n", grades[randomIndex]);
                    } else if (choice == 2) {
                        // 드랍 선택
                        printf("You dropped the lecture.\n");
                    } else {
                        printf("Invalid choice. No action taken.\n");
                    }
                } else {
                    printf("Not enough energy to attend the lecture.\n");
                }
            }
            break;
        /*case restaurant: 에너지는 강의 수강 혹은 실험실에의 실험 시 소요되거나 식당 혹은 집에서 충전된다. 
        식당에서는 보충 에너지만큼 플레이어의 현재 에너지가 더해진다. */
          case SMMNODE_TYPE_RESTAURANT:
              cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
              break;
        /*case home: 첫번째 노드 (입력 파일의 첫줄)은 항상 유형이 집이며, 마지막 노드의 다음은 첫번째 노드로 연결되는 구조로 구성해야 한다.
        지나가는 순간 지정된 보충 에너지만큼 현재 에너지에 더해진다. */
          case SMMNODE_TYPE_HOME:
        // 주사위를 굴려서 0에서 15까지의 노드를 이동하는 게임
              cur_player[player].energy += smmObj_getNodeEnergy(cur_player[player].position);
              break;
        //case gotolab: 실험중 상태로 전환되면서 laboratory로 이동한다. 
        //주사위 눈 범위에서 criterion을 랜덤으로 지정한다. 
          case SMMNODE_TYPE_GOTOLAB:
              srand(time(NULL));  // 난수 발생기를 초기화 (프로그램을 실행할 때 한 번만 수행)
              int criterion = ramdom();  // 1에서 6까지의 랜덤한 숫자를 생성
              printf("Experimental success criterion: %d\n", criterion); // 주사위를 굴려 실험 성공 기준값을 랜덤으로 설정
              
              cur_player[player].position = SMMNODE_TYPE_LABORATORY; // Laboratory로 이동
              break;
          /*case laboratory: 실험중 상태면 주사위를 굴려서 사전에 지정된 실험 성공 기준값 이상이 나오면 실험이 종료되고, 그렇지 않으면 이동하지 못하고 실험중 상태에 머문다.
        단순히 laboratory 노드에 머무른다고 실험중 상태가 되지 않으며, 실험 노드에 머물러야 실험중 상태가 된다.
        실험 시도마다 소요 에너지만큼 소요하며, 이로 인해 에너지가 음수가 될 수 있다.*/
          case SMMNODE_TYPE_LABORATORY:
              cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);
              srand(time(NULL));
              int result = ramdom();

              if (result >= criterion) {
                  printf("Congratulation, you can escape.\n");
              } else {
                  printf("You failed, try next time.\n");
                  return;
              }
              break;

        //case foodchance: 음식카드를 한장 랜덤으로 고르고 명시된 보충 에너지를 현재 에너지에 더한다. 
          case SMMNODE_TYPE_FOODCHANCE:
              srand(time(NULL));
              int foodIndex = rand() % food_nr; // 랜덤으로 음식 카드를 선택

              printf("You are at the FoodChance node. Selected Food: %s, Energy Bonus: %i\n",
              smmObj_getFoodName(foodIndex), smmObj_getFoodEnergy(foodIndex));

       //선택된 음식 카드의 에너지를 현재 에너지에 더한다.
              cur_player[player].energy += smmObj_getFoodEnergy(foodIndex);

              break;
       //case festival: 축제카드를 한장 랜덤으로 골라서 명시된 미션을 수행한다. 
          case SMMNODE_TYPE_FESTIVAL:
              srand(time(NULL));
              int festIndex = rand() % festival_nr; // 랜덤으로 축제 카드를 선택

              printf("You are at the Festival node. Mission: %s\n", smmObj_getFestName(festIndex));
              break;
 
        default:
            break;
    }
}

void goForward(int player, int step) //make player go "step" steps on the board (check if player is graduated)
                                     //Player 이동 함수 구현, 다음 주 상어 게임을 하면 구현 가능 
{
     cur_player[player].position += step; //player_t 구조체 내 변수를 묶어놓은 cur_player 배열에서 position 변수에 step 값을 더한다. 
     
     // 만약 위치가 15를 넘어가면 다시 0으로 되돌린다.
    cur_player[player].position %= 16;

     printf("%s go to node %i (name: %s)\n", 
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(cur_player[player].position));
                //player_t 구조체 내 변수를 묶어놓은 cur_player 배열에서 name 변수와 position 변수, 우리집 처럼 노드 이름을 출력한다.  
}

int main(int argc, const char * argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME]; // main 함수 내 이름, 유형, 학점, 에너지 변수 선언 
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn=0; //turn 변수 선언 및 초기화 

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

    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated? 일단 무한 반복시킨다. 한번의 반복에서 한 플레이어가 한턴 동작 수행. 
    {
        int die_result;

        //4-1. initial printing 
        printPlayerStatus(); 

        //4-2. die rolling (if not in experiment) 주사위에 따라 이동 
        die_result = rolldie(turn); 


        //4-3. go forward
        goForward(turn, die_result); 

		//4-4. take action at the destination node of the board
		//게임 종료와 함께 졸업한 플레이어가 수강한 강의의 이름, 학점, 성적을 각각 출력해야.
        actionNode(turn);

        //4-5. next turn
        turn = (turn + 1)%player_nr;
        
        // Check if any player has accumulated enough credits to graduate
        if (cur_player[turn].accumCredit >= GRADUATE_CREDIT) {
        printf("%s has graduated!\n", cur_player[turn].name);
        
        int i;
        
        // Print the details of the courses taken
        for (i = 0; i < board_nr; i++) {
            if (smmObj_getNodeType(i) == SMMNODE_TYPE_LECTURE) {
                printf("Course: %s, Credit: %d, Grade: %s\n",
                       smmObj_getNodeName(i),
                       smmObj_getNodeCredit(i),
                       "A+"); // 여기서 성적은 랜덤이 아닌 A+로 가정
            }
        }

        // Break out of the loop
        break;
    }


    } /*게임 종료 조건: 플레이어 중 한명이 GRADUATE_CREDIT 이상의 학점 이수하고 집으로 이동하면 게임이 즉시 종료됨.
      GRADUATE_CREDIT = 30, MAX_DIE = 6 */

    system("PAUSE");
    return 0;
   
}
