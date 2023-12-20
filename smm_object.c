//
//  smm_node.c Data encapsulation 방식으로 노드 데이터 저장하는 곳, 데이터 원본을 감싸서 감추는 프로그래밍 방식, main.c에 제공되는 함수로만 데이터 접근 가능 
//  SMMarble
//  smm_object.c 객체 (보드칸-노드, 음식카드, 축제카드, 수강 이력  및 성적) 구조체 생성 및 분석 
//  Created by Juyeop Kim on 2023/11/05.
//

#include "smm_common.h"
#include "smm_object.h"
#include <string.h>

#define MAX_NODETYPE    7
#define MAX_GRADE       9
#define MAX_NODE        100


static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //해당 문자열 배열 생성, 문자열을 반환하는 API 함수를 smm_object.c에 구현 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];
static int smmObj_noNode=0;
static int smmObj_noFood=0;
static int smmObj_noFest=0;


//object generation
void smmObj_genNode(char* name, int type, int credit, int energy)
{
    strcpy(smmObj_name[smmObj_noNode], name);
    smmObj_type[smmObj_noNode] = type;
    smmObj_credit[smmObj_noNode] = credit;
    smmObj_energy[smmObj_noNode] = energy;

    smmObj_noNode++;
}

void smmObj_genFood(char* name, int energy)
{
    strcpy(smmObj_name[smmObj_noFood], name);
    smmObj_energy[smmObj_noFood] = energy;

    smmObj_noFood++;
}

void smmObj_genFest(char* name)
{
    strcpy(smmObj_name[smmObj_noFest], name);
    
    smmObj_noFest++;
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
char* smmObj_getNodeName(smmNode_e type)
{
    return smmNodeName[type];
}

char* smmObj_getGradeName(smmGrade_e grade)
{
    return smmGradeName[grade];
}
#endif
