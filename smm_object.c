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



static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //�ش� ���ڿ� �迭 ����, ���ڿ��� ��ȯ�ϴ� API �Լ��� smm_object.c�� ���� 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0;
static int smmObj_noFood=0;
static int smmObj_noFest=0;


//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //Node �迭 ����ϱ� ���� ��� �Լ� 
{
    strcpy(smmObj_name[smmObj_noNode], name);
    smmObj_type[smmObj_noNode] = type;
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;

    smmObj_noNode++; //void �Լ� �������� noNode ���� 0���� ����ؼ� ���, ��ȣ�� 15���� ������ Node �� type�� credit, energy ���. 
}

void smmObj_genFood(char* name, int energy)
{
    strcpy(smmObj_name[smmObj_noFood], name);
    smmObj_energy[smmObj_noFood] = energy;

    smmObj_noFood++; //void �Լ� �������� noFood ���� 0���� ����ؼ� ���, ��ȣ�� 13���� ������ Food �� energy ���. 
}

void smmObj_genFest(char* name)
{
    strcpy(smmObj_name[smmObj_noFest], name);
    
    smmObj_noFest++; //void �Լ� �������� noFest ���� 0���� ����ؼ� ���, ��ȣ�� 4���� ������ Fest �� ���ڿ� ������ ���. 
}

char* smmObj_getNodeName(int node_nr)
{
    return smmObj_name[node_nr];
}

int smmObj_getNodeType(int node_nr)
{
    return smmObj_type[node_nr];
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smmObj_energy[node_nr];
}

char* smmObj_getFoodName(int food_nr)
{
    return smmObj_name[food_nr];
}

int smmObj_getFoodEnergy(int food_nr)
{
    return smmObj_energy[food_nr];
}

char* smmObj_getFestName(int Fest_nr)
{
    return smmObj_name[Fest_nr];
}

//member retrieving


#if 0

//element to string
char* smmObj_getNodeName(smmNode_e type) // i��° ����� Ÿ���� ������ �Է��ϸ� ���ڿ� ��µǴ� �Լ� �ڵ� 
{
    
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}
#endif
