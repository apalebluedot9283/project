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

//1. 구조체 형식 정의
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

//2. 구조체 배열 변수 정의 
smmObject_t smm_node[MAX_NODE];
smmObject_t smm_food[MAX_FOOD];
smmObject_t smm_fest[MAX_FEST];


#if 0

static char smmObj_name[MAX_NODE][MAX_CHARNAME]; //해당 문자열 배열 생성, 문자열을 반환하는 API 함수를 smm_object.c에 구현 
static int smmObj_type[MAX_NODE];
static int smmObj_credit[MAX_NODE];
static int smmObj_energy[MAX_NODE];

#endif 

static int smmObj_noNode = 0;
static int smmObj_noFood=0;
static int smmObj_noFest=0;

//3. 관련 함수 변경  
//object generation
void smmObj_genNode(char* name, int type, int credit, int energy) //Node 배열 출력하기 위한 배경 함수 
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


    smmObj_noNode++; //void 함수 내에서는 noNode 값이 0에서 계속해서 상승, 번호가 15까지 내에서 Node 내 type과 credit, energy 출력. 
}

void smmObj_genFood(char* name, int energy)
{
    #if 0 
    strcpy(smmObj_name[smmObj_noFood], name);
    smmObj_energy[smmObj_noFood] = energy;
    #endif
    
    strcpy(smm_food[smmObj_noFood].name, name);
    smm_food[smmObj_noFood].energy = energy;
    
    smmObj_noFood++; //void 함수 내에서는 noFood 값이 0에서 계속해서 상승, 번호가 13까지 내에서 Food 내 energy 출력. 
}

void smmObj_genFest(char* name)
{
    #if 0
    strcpy(smmObj_name[smmObj_noFest], name);
    #endif
    
    strcpy(smm_fest[smmObj_noFest].name, name);
    
    smmObj_noFest++; //void 함수 내에서는 noFest 값이 0에서 계속해서 상승, 번호가 4까지 내에서 Fest 내 문자열 순차적 출력. 
}

//3. 관련 함수 변경 
char* smmObj_getNodeName(int node_nr)
{
    return smm_node[node_nr].name;
}
//3. 관련 함수 변경
int smmObj_getNodeType(int node_nr)
{
    return smm_node[node_nr].type;
}

int smmObj_getNodeEnergy(int node_nr)
{
    return smm_node[node_nr].energy;
}

int smmObj_getNodeCredit(int node_nr) // i번째 노드의 타입을 가져와 입력하면 문자열 출력되는 함수 코딩 
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



