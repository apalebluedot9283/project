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

static int player_nr; //�÷��̾� �� 

typedef struct player { //player(tag) ����ü ������ player_t ���� ����  
        int energy;
        int position;
        char name[MAX_CHARNAME];
        int accumCredit;
        int flag_graduate; //�������� 
} player_t;

static player_t cur_player[MAX_PLAYER]; //player_t ����ü���� energy, position, name, accumCreditm flag_graduate ������ �迭�� ���´�. 

#if 0
static int player_energy[MAX_PLAYER];
static int player_position[MAX_PLAYER];
static char player_name[MAX_PLAYER][MAX_CHARNAME]; // �����Ǿ� �ִ� �迭 �� i��° ����� �÷��̾� �̸��� ��ġ, ������  
#endif

//function prototypes
#if 0
int isGraduated(void); //check if any player is graduated
//void generatePlayers(int n, int initEnergy); //generate a new player
float calcAverageGrade(int player); //calculate average grade of the player
smmGrade_e takeLecture(int player, char *lectureName, int credit); //take the lecture (insert a grade of the player) �����̷� 
void* findGrade(int player, char *lectureName); //find the grade from the player's grade history
#endif

void printPlayerStatus(void) //print all player status at the beginning of each turn �÷��̾���� �ش� ���� ��� ������ ���ο� ���� ���ƿ��� �� �÷��̾���� ���� ��� 
{
     int i;

     for (i=0;i<player_nr;i++) 
     {
         printf("%s : credit %i, energy %i, position %i\n", 
                      cur_player[i].name, //cur_player �迭 �� name ������ ���� ����Ѵ�. 
                      cur_player[i].accumCredit, //cur_player �迭 �� accumCredit ������ ���� ����Ѵ�.
                      cur_player[i].energy, //cur_player �迭 �� energy ������ ���� ����Ѵ�. 
                      cur_player[i].position); //cur_player �迭 �� position ������ ���� ����Ѵ�.
     }
}


void generatePlayers(int n, int initEnergy) //generate a new player, n���� �÷��̾�, initEnergy�� ������ �ʱ�ȭ. 
{
     int i;
     //n time loop
     for (i=0;i<n;i++) //�÷��̾ n�� �ִٰ� �����Ѵ�. 
     {
         //input name �÷��̾� ���� ���۽� �Է� ������, �� �÷��̾��� �̸��� �Է¹޾Ƽ� Ȱ��� �� �־�� ��. 
         printf("Input player %i's name:", i); 
         scanf("%s", cur_player[i].name); //player_t ����ü���� ���� ������ ������ cur_player �迭 �� name ������ ���� ����Ѵ�. 
         fflush(stdin); //while �� ��� �ÿ� buffer �ȿ� ���簡 ���� �̸����� �� ���� �ִ�. 

         //set position 
         //player_position[i] = 0;
         cur_player[i].position = 0; //player_t ����ü���� ���� ������ ������ cur_player �迭 �� position ������ ���� ����Ѵ�. 
 
         //set energy ���� �� �÷��̾�� ���� �������� �� ����� ���� �������� �ʱ�ȭ�Ǿ�� �Ѵ�. 
          //player_energy[i] = initEnergy; �÷��̾� ���� ���� �־���ϹǷ� �迭�� ��´�. 
         cur_player[i].energy = initEnergy; //player_t ����ü���� ���� ������ ������ cur_player �迭 �� initEnergy ������ ���� ����Ѵ�. 
         cur_player[i].accumCredit = 0; //player_t ����ü���� ���� ������ ������ cur_player �迭 �� accumCredit ������ ���� �ʱ�ȭ�Ѵ�.
         cur_player[i].flag_graduate = 0; //player_t ����ü���� ���� ������ ������ cur_player �迭 �� flag_graduate ������ ���� �ʱ�ȭ�Ѵ�. 
     }
}

void printGrades(int player){ //print grade history of the player Player ���� ��� �Լ� ���� ���� �������� �÷��̾��� ������ ��� �� printf�� �̿��ؼ� �Լ� �ۼ� 
                              //�� ���� �� ��� �÷��̾��� ���� (��ġ, ���� �� ����, ���� ����, ���� ������) ����ؾ�. 
}

int rolldie(int player) // �ֻ��� ������ 
{
    char c;
    printf(" Press any key to roll a die (press g to see grade): ");
    c = getchar(); //�Էµ� ������ �÷��̾ ���ư��鼭 �ֻ����� ������ �̵��Ѵ�. 
    fflush(stdin);

#if 0
    if (c == 'g')
        printGrades(player);
#endif

    return (rand()%MAX_DIE + 1); //�������� �ֻ��� �� ���´�. 
}

//action code when a player stays at a node
int ramdom() {
    return (rand() % 6) + 1;  // 1���� 6������ ������ ���� ����
}

void actionNode(int player)

{
     int type = smmObj_getNodeType( cur_player[player].position ); //player_t ����ü���� ���� ������ ������ cur_player �迭 �� position ������ ���� ����Ѵ�. 
     cur_player[player].position %= 16;
     switch (type) {
        // ������ ���� ��忡���� ���ǹ��ϸ�, ���� ���� �� �÷��̾ ��� �Ǵ� ���� ����.
        // �� �÷��̾�� �ڽ��� �������� �����ϸ鼭 �����ϰ� ���������� ��� ���� ����(credit)�� ä��� ���� ���� ��ǥ�� �Ѵ�.
        // ���� �������� �ҿ信���� �̻� �ְ� ������ ���� ���� �����̸� ���� �����ϸ�, ���� Ȥ�� ����� ������ �� �ִ�.
        // �����ϸ� ������ A+, A0, A-, B+..... �� �ϳ��� �������� ���´�.
        case SMMNODE_TYPE_LECTURE:
            {
                // ���� �������� �ҿ信���� �̻��̰�, ������ ���� ���� �������� ���θ� Ȯ��
                if (cur_player[player].energy >= smmObj_getNodeEnergy(cur_player[player].position)) {
                    printf("Do you want to attend the lecture? (1: Attend, 2: Drop): ");
                    int choice;
                    scanf("%d", &choice);

                    if (choice == 1) {
                        // ���� ����
                        cur_player[player].accumCredit += smmObj_getNodeCredit(cur_player[player].position);
                        cur_player[player].energy -= smmObj_getNodeEnergy(cur_player[player].position);

                        // ���� �������� �����ϰ� ��� (A+, A0, A-, B+ ��)
                        char* grades[] = {"A+", "A0", "A-", "B+", "B0", "B-", "C+", "C0", "C-"};
                        int randomIndex = rand() % 9; // 0���� 8������ ���� �ε���
                        printf("You attended the lecture and received grade: %s\n", grades[randomIndex]);
                    } else if (choice == 2) {
                        // ��� ����
                        printf("You dropped the lecture.\n");
                    } else {
                        printf("Invalid choice. No action taken.\n");
                    }
                } else {
                    printf("Not enough energy to attend the lecture.\n");
                }
            }
            break;
        /*case restaurant: �������� ���� ���� Ȥ�� ����ǿ��� ���� �� �ҿ�ǰų� �Ĵ� Ȥ�� ������ �����ȴ�. 
        �Ĵ翡���� ���� ��������ŭ �÷��̾��� ���� �������� ��������. */
          case SMMNODE_TYPE_RESTAURANT:
              cur_player[player].energy += smmObj_getNodeEnergy( cur_player[player].position );
              break;
        /*case home: ù��° ��� (�Է� ������ ù��)�� �׻� ������ ���̸�, ������ ����� ������ ù��° ���� ����Ǵ� ������ �����ؾ� �Ѵ�.
        �������� ���� ������ ���� ��������ŭ ���� �������� ��������. */
          case SMMNODE_TYPE_HOME:
        // �ֻ����� ������ 0���� 15������ ��带 �̵��ϴ� ����
              cur_player[player].energy += smmObj_getNodeEnergy(cur_player[player].position);
              break;
        //case gotolab: ������ ���·� ��ȯ�Ǹ鼭 laboratory�� �̵��Ѵ�. 
        //�ֻ��� �� �������� criterion�� �������� �����Ѵ�. 
          case SMMNODE_TYPE_GOTOLAB:
              srand(time(NULL));  // ���� �߻��⸦ �ʱ�ȭ (���α׷��� ������ �� �� ���� ����)
              int criterion = ramdom();  // 1���� 6������ ������ ���ڸ� ����
              printf("Experimental success criterion: %d\n", criterion); // �ֻ����� ���� ���� ���� ���ذ��� �������� ����
              
              cur_player[player].position = SMMNODE_TYPE_LABORATORY; // Laboratory�� �̵�
              break;
          /*case laboratory: ������ ���¸� �ֻ����� ������ ������ ������ ���� ���� ���ذ� �̻��� ������ ������ ����ǰ�, �׷��� ������ �̵����� ���ϰ� ������ ���¿� �ӹ���.
        �ܼ��� laboratory ��忡 �ӹ����ٰ� ������ ���°� ���� ������, ���� ��忡 �ӹ����� ������ ���°� �ȴ�.
        ���� �õ����� �ҿ� ��������ŭ �ҿ��ϸ�, �̷� ���� �������� ������ �� �� �ִ�.*/
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

        //case foodchance: ����ī�带 ���� �������� ���� ��õ� ���� �������� ���� �������� ���Ѵ�. 
          case SMMNODE_TYPE_FOODCHANCE:
              srand(time(NULL));
              int foodIndex = rand() % food_nr; // �������� ���� ī�带 ����

              printf("You are at the FoodChance node. Selected Food: %s, Energy Bonus: %i\n",
              smmObj_getFoodName(foodIndex), smmObj_getFoodEnergy(foodIndex));

       //���õ� ���� ī���� �������� ���� �������� ���Ѵ�.
              cur_player[player].energy += smmObj_getFoodEnergy(foodIndex);

              break;
       //case festival: ����ī�带 ���� �������� ��� ��õ� �̼��� �����Ѵ�. 
          case SMMNODE_TYPE_FESTIVAL:
              srand(time(NULL));
              int festIndex = rand() % festival_nr; // �������� ���� ī�带 ����

              printf("You are at the Festival node. Mission: %s\n", smmObj_getFestName(festIndex));
              break;
 
        default:
            break;
    }
}

void goForward(int player, int step) //make player go "step" steps on the board (check if player is graduated)
                                     //Player �̵� �Լ� ����, ���� �� ��� ������ �ϸ� ���� ���� 
{
     cur_player[player].position += step; //player_t ����ü �� ������ ������� cur_player �迭���� position ������ step ���� ���Ѵ�. 
     
     // ���� ��ġ�� 15�� �Ѿ�� �ٽ� 0���� �ǵ�����.
    cur_player[player].position %= 16;

     printf("%s go to node %i (name: %s)\n", 
                cur_player[player].name, cur_player[player].position,
                smmObj_getNodeName(cur_player[player].position));
                //player_t ����ü �� ������ ������� cur_player �迭���� name ������ position ����, �츮�� ó�� ��� �̸��� ����Ѵ�.  
}

int main(int argc, const char * argv[]) {

    FILE* fp;
    char name[MAX_CHARNAME]; // main �Լ� �� �̸�, ����, ����, ������ ���� ���� 
    int type;
    int credit;
    int energy;
    int i;
    int initEnergy;
    int turn=0; //turn ���� ���� �� �ʱ�ȭ 

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

    //3. SM Marble game starts ---------------------------------------------------------------------------------
    while (1) //is anybody graduated? �ϴ� ���� �ݺ���Ų��. �ѹ��� �ݺ����� �� �÷��̾ ���� ���� ����. 
    {
        int die_result;

        //4-1. initial printing 
        printPlayerStatus(); 

        //4-2. die rolling (if not in experiment) �ֻ����� ���� �̵� 
        die_result = rolldie(turn); 


        //4-3. go forward
        goForward(turn, die_result); 

		//4-4. take action at the destination node of the board
		//���� ����� �Բ� ������ �÷��̾ ������ ������ �̸�, ����, ������ ���� ����ؾ�.
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
                       "A+"); // ���⼭ ������ ������ �ƴ� A+�� ����
            }
        }

        // Break out of the loop
        break;
    }


    } /*���� ���� ����: �÷��̾� �� �Ѹ��� GRADUATE_CREDIT �̻��� ���� �̼��ϰ� ������ �̵��ϸ� ������ ��� �����.
      GRADUATE_CREDIT = 30, MAX_DIE = 6 */

    system("PAUSE");
    return 0;
   
}
