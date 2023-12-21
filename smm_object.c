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
#define MAX_FEST        100 //NODE, FOOD, FEST �迭�� �ִ� ���� ���� 

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


//1. ����ü ���� ���� main.c���� ����ü�� ������ ������ �ʰ� �ڵ� 
typedef struct smmObject 
{ //smmobject��� ����ü �� ���� �ڷ����� ������ ���ǳ����� smmObject_t��� ��ü�� ��Ÿ����.  
       char name[MAX_CHARNAME];
       smmObjType_e objType; 
       int type;
       int credit;
       int energy;
       smmObjGrade_e grade;
} smmObject_t;

typedef struct smmFood 
{ //smmFood��� ����ü �� ���� �ڷ����� ������ ���ǳ����� smmFood_t��� ��ü�� ��Ÿ����.  
       char name[MAX_CHARNAME];
       int energy;
} smmFood_t;

typedef struct smmFest 
{ //smmFest��� ����ü �� ���� �ڷ����� ������ ���ǳ����� smmFest_t��� ��ü�� ��Ÿ����.  
       char name[MAX_CHARNAME];
} smmFest_t;

/*2. ����ü �迭 ���� ���� 
static smmObject_t smm_node[MAX_NODE]; //smmObject_t ����ü�� �迭�� smm_node�� �����Ѵ�. 
static smmFood_t smm_food[MAX_FOOD]; //smmFood_t ����ü�� �迭�� smm_food�� �����Ѵ�. 
static smmFest_t smm_fest[MAX_FEST]; //smmFest_t ����ü�� �迭�� smm_fest�� �����Ѵ�. 

�������� �迭�� ������ �� ��ҵ��� ����ü�� �迭�� ���� �Լ��� �ٲ۴�. 

static int smmObj_noNode = 0;
static int smmObj_noFood=0;
static int smmObj_noFest=0; */

//3. ���� �Լ� ����  
//object generation
void* smmObj_genObject(char* name, smmObjType_e objType, int type, int credit, int energy, smmObjGrade_e grade)
//Node �迭 ����ϱ� ���� ��� �Լ� 
{
    smmObject_t* ptr;
//smmObj_noNode++; //void �Լ� �������� noNode ���� 0���� ����ؼ� ���, ��ȣ�� 15���� ������ Node �� type�� credit, energy ���. 
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

//3. ���� �Լ� ���� (Node) 
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

int smmObj_getNodeCredit(void* obj) // i��° ����� Ÿ���� ������ �Է��ϸ� ���ڿ� ��µǴ� �Լ� �ڵ� 
{
      smmObject_t* ptr = (smmObject_t*)obj;

      return ptr->credit;}
}

//3. ���� �Լ� ���� (Food) 
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

//3. ���� �Լ� ���� (Fest) 
char* smmObj_getFestName(void* obj)
{
      smmFest_t* ptr = (smmFest_t*)obj;

      return ptr->name;}
}



