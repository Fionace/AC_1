#ifndef AC_H
#define AC_H

#include<iostream>
#include<string>
#include<string.h>
#include<fstream>
#include"Base.h"

//const int MAX=255;
using namespace std;

const int MAX=255;
/*typedef struct
{
   
}SonStruct;*/

typedef struct 
{
   int state;//状态值
   int Nextindex;//next表下标
   char *PR; //前缀
   char *son;//存放所有可能子状态字符
   
}Node;

class AC
{
   public:
     int Next[MAX];
    static const int id=0;//指示接着的子状态的状态序
     bool  Nextif[MAX];
     int Nextne;//指示下一个部分子状态的初始位置
     int Base[MAX];
     int Check[MAX];
     int Fail[MAX];
     int Output[MAX][MAX];//状态值.模式串索引
     string Patt[MAX];
     int patt_num;
     int patt_maxlen;
  AC(ifstream in,Node *first);
  bool All_travese();
  bool Test_next(char *son);
  bool Trans_son(char *son);
  bool CreateTable(Node *curr_old,Node *curr,int init,char *a,char *ini);
     
};

#endif //AC_H
