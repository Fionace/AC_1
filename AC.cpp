#include"AC.h"

AC::AC(ifstream in,Node *first)
{
   int i=0;
  while(in>>Patt[i])
     i++;
   patt_num=i;
  for(i=0;i<patt_num,i++)
   {  
      if(Patt[i].size>patt_maxlen)
          patt_maxlen=Patt[i].size;
   }
  first->state=0;
  first->Nextindex=0;
  PR="";
 
}

bool Trans_son(char *son)
{
    int len=strlen(son);
     int i=0;
    char *tem=New char[len];
      *tem=*son;
    for(i=1;i<len;i++)
      {
         for(int k=0;k<strlen(tem);k++)
        { if(*(son+i)==*(tem+k))
            break;
        else
           {*(tem+strlen(tem))=*(son+i);}
        }
      }
    Sort(tem,strlen(len));
    son=tem;
   return true;
}

bool Test_next(char *son ,int init)
{
    int len=strlen(son);
    int tem[len];
    tem[0]=init;
   for(int i=1;i<len;i++) 
      {
          tem[i]=tem[0]+(int)(*(son+i)-*son);
            if(Nextif[tem[i]]==false)
                continue;
             else
                break;
      }
  if(i==len)
    return true;
  else
    return false;
   
}

bool CreateTable(Node *curr_old,Node *curr,int init,char *a,char *ini)
{
    int i=int(*a)-int(*ini)+init;
    int z=0,y=0,x=0;
    Next[i]=curr->state;
    Base[curr_old->state]=Next[i]-curr_old->Nextindex-int(*a);
    Check[curr->state]=curr_old->state;
     int b=strlen(curr_old->PR)+1;
     char *tem=new char[b];
     strcpy(tem,curr_old->PR);
     strcat(tem,a);
     for(int k=0;k<patt_num;k++)
      {
         if(Patt[k].c_str==tem)
           {
              z=0;  
             while(Output[curr->state][z]!=0)
                 z++;
              Output[curr->state][z]=k;
                break;
           }
      }
      int f;
      f=Fail[Check[curr_old->state]];
      Fail[curr->state]=curr_old->Nextindex+Base[curr_old->state]+int(*a);
      if(Output[Fail[curr->state]][0]!=0)
         {
               z=0;
              while(Output[curr->state][z]!=0)
                 z++;
               y=0;
              while(Output[Fail[curr->state]][y]!=0)
                 y++;
            for(x=0;x<y;x++)
             { Output[curr->state][z]=Output[Fail[curr->state]][x]; 
                z++;
             }
          }
   return true;    
}

/*bool CreateSon(char *son,int sta,Node *curr_son)
{
    curr_son 
   
}*/

bool All_travese()
{
    
} 

