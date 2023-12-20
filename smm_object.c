//
//  smm_node.c Data encapsulation ������� ��� ������ �����ϴ� ��, ������ ������ ���μ� ���ߴ� ���α׷��� ���, main.c�� �����Ǵ� �Լ��θ� ������ ���� ���� 
//  SMMarble
//  smm_object.c ��ü (����ĭ-���, ����ī��, ����ī��, ���� �̷�  �� ����) ����ü ���� �� �м� 
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100
#define MAX_FOOD        100
#define MAX_FEST        100

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] = {
       "lecture",
       "restaurant",
       "laboratory",
       "home",
       "gotoLab",
       "foodChance",
       "festival"
};

char* smmObj_getTypeName(int type)
{
      return (char*)smmNodeName[type]; 
}

//1. ����ü ���� ����
typedef struct smmObject {
       char name[MAX_CHARNAME];
       int type;
       int credit;
       int energy;
} smmObject_t;

typedef struct smmFood_t {
       char name[MAX_CHARNAME];
       int energy;
} smmFood_t;

typedef struct smmFest {
       char name[MAX_CHARNAME];
} smmFest_t;

//2. ����ü �迭 ���� ���� 
smmObject_t smm_node[MAX_NODE];
smmObject_t smm_food[MAX_FOOD];
smmObject_t smm_fest[MAX_FEST];


#if 0

static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //�ش� ���ڿ� �迭 ����, ���ڿ��� ��ȯ�ϴ� API �Լ��� smm_object.c�� ���� 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];

#endif 

static int smmObj_noNode = 0;
static int smmObj_noFood=0;
static int smmObj_noFest=0;

//3. ���� �Լ� ����  
//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //Node �迭 ����ϱ� ���� ��� �Լ� 
{
    #if 0
    strcpy(smmObj_name[smmObj_noNode], name);
    smmObj_type[smmObj_noNode] = type;
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;
    #endif
    
    strcpy(smm_node[smmObj_noNode].name, name);
    smm_node[smmObj_noNode].type = type;
    smm_node[smmObj_noNode].credit = credit;
    smm_node[smmObj_noNode].energy = energy;


    smmObj_noNode++; //void �Լ� �������� noNode ���� 0���� ����ؼ� ���, ��ȣ�� 15���� ������ Node �� type�� credit, energy ���. 
}

void smmObj_genFood(char* name, int energy)
{
    #if 0 
    strcpy(smmObj_name[smmObj_noFood], name);
    smmObj_energy[smmObj_noFood] = energy;
    #endif
    
    strcpy(smm_food[smmObj_noFood].name, name);
    smm_food[smmObj_noFood].energy = energy;
    
    smmObj_noFood++; //void �Լ� �������� noFood ���� 0���� ����ؼ� ���, ��ȣ�� 13���� ������ Food �� energy ���. 
}

void smmObj_genFest(char* name)
{
    #if 0
    strcpy(smmObj_name[smmObj_noFest], name);
    #endif
    
    strcpy(smm_fest[smmObj_noFest].name, name);
    
    smmObj_noFest++; //void �Լ� �������� noFest ���� 0���� ����ؼ� ���, ��ȣ�� 4���� ������ Fest �� ���ڿ� ������ ���. 
}

//3. ���� �Լ� ���� 
char* smmObj_getNodeName(int node_nr)
{
    return smm_node[node_nr].name;
}
//3. ���� �Լ� ����
int smmObj_getNodeType(int node_nr)
{
    return smm_node[node_nr].type;
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}

int smmObj_getNodeCredit(int node_nr) // i��° ����� Ÿ���� ������ �Է��ϸ� ���ڿ� ��µǴ� �Լ� �ڵ� 
{
    
    return smm_node[node_nr].credit;
}

char* smmObj_getFoodName(int food_nr)
{
    return smm_food[food_nr].name;
}

int smmObj_getFoodEnergy(int food_nr)
{
    return smm_food[food_nr].energy;
}

char* smmObj_getFestName(int festival_nr)
{
    return smm_fest[festival_nr].name;
}



