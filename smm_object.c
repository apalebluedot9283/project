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
#define MAX_FEST        100 //NODE, FOOD, FEST 배열의 최대 범위 설정 

static char smmNodeName[SMMNODE_TYPE_MAX][MAX_CHARNAME] =
{
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

typedef enum smmObjGrade
{
    smmObjGrade_Ap = 0,
    smmObjGrade_A0,
    smmObjGrade_Am,
    smmObjGrade_Bp,
    smmObjGrade_B0,
    smmObjGrade_Bm,
    smmObjGrade_Cp,
    smmObjGrade_C0,
    smmObjGrade_Cm
} smmObjGrade_e;


//1. 구조체 형식 정의 main.c에게 구조체의 구조를 보이지 않게 코딩 
typedef struct smmObject 
{ //smmobject라는 구조체 내 여러 자료형의 변수들 정의내리고 smmObject_t라는 실체로 나타낸다.  
       char name[MAX_CHARNAME];
       smmObjType_e objType; 
       int type;
       int credit;
       int energy;
       smmObjGrade_e grade;
} smmObject_t;

typedef struct smmFood 
{ //smmFood라는 구조체 내 여러 자료형의 변수들 정의내리고 smmFood_t라는 실체로 나타낸다.  
       char name[MAX_CHARNAME];
       int energy;
} smmFood_t;

typedef struct smmFest 
{ //smmFest라는 구조체 내 여러 자료형의 변수들 정의내리고 smmFest_t라는 실체로 나타낸다.  
       char name[MAX_CHARNAME];
} smmFest_t;

/*2. 구조체 배열 변수 정의 
static smmObject_t smm_node[MAX_NODE]; //smmObject_t 구조체의 배열로 smm_node를 정의한다. 
static smmFood_t smm_food[MAX_FOOD]; //smmFood_t 구조체의 배열로 smm_food를 정의한다. 
static smmFest_t smm_fest[MAX_FEST]; //smmFest_t 구조체의 배열로 smm_fest를 정의한다. 

전역변수 배열로 정의한 각 요소들을 구조체의 배열로 관련 함수를 바꾼다. 

static int smmObj_noNode = 0;
static int smmObj_noFood=0;
static int smmObj_noFest=0; */

//3. 관련 함수 변경  
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
//Node 배열 출력하기 위한 배경 함수 
{
    smmObject_t* ptr;
//smmObj_noNode++; //void 함수 내에서는 noNode 값이 0에서 계속해서 상승, 번호가 15까지 내에서 Node 내 type과 credit, energy 출력. 
    ptr = (smmObject_t*)malloc(sizeof(smmObject_t));

    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return ptr;
}

void smmObj_genFood(char* name, int energy)
{   
    smmFood_t* ptr;
    
    ptr = (smmFood_t*)malloc(sizeof(smmFood_t));

    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return ptr;
}

void smmObj_genFest(char* name)
{
    smmFest_t* ptr;
     
    ptr = (smmFood_t*)malloc(sizeof(smmFood_t));

    strcpy(ptr->name, name);
    ptr->objType = objType;
    ptr->type = type;
    ptr->credit = credit;
    ptr->energy = energy;
    ptr->grade = grade;

    return ptr;
}

//3. 관련 함수 변경 (Node) 
char* smmObj_getNodeName(void* obj)
{
      smmObject_t* ptr = (smmObject_t*)obj;

      return ptr->name;
}

int smmObj_getNodeType(void* obj)
{
      smmObject_t* ptr = (smmObject_t*)obj;

      return ptr->type;}

int smmObj_getNodeEnergy(void* obj)
{
      smmObject_t* ptr = (smmObject_t*)obj;

      return ptr->energy;}

int smmObj_getNodeCredit(void* obj) // i번째 노드의 타입을 가져와 입력하면 문자열 출력되는 함수 코딩 
{
      smmObject_t* ptr = (smmObject_t*)obj;

      return ptr->credit;}
}

//3. 관련 함수 변경 (Food) 
char* smmObj_getFoodName(void* obj)
{
      smmFood_t* ptr = (smmFood_t*)obj;

      return ptr->name;}
}

int smmObj_getFoodEnergy(void* obj)
{
    smmFood_t* ptr = (smmFood_t*)obj;

    return ptr->energy;}
}

//3. 관련 함수 변경 (Fest) 
char* smmObj_getFestName(void* obj)
{
      smmFest_t* ptr = (smmFest_t*)obj;

      return ptr->name;}
}



