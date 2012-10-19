#include"Base.h"

void swap(char *a,int i,int j)
{
    char temp;
    temp=*(a+i);
    *(a+i)=*(a+j);
    *(a+j)=temp;
} 
void Sort(char *a,int len)
{
    for(int i=0;i<len;i++)
      {
          for(int j=len-2;j>=i;j--)
             {
                 if(*(a+j)>*(a+j+1))
                    swap (a,j,j+1);
             }
      }
    
}

/*int main()
 {
    char b[]={'c','d','a','b','f','e','h'};
    char *a=b;
    cout<<strlen(b)<<endl;
    Sort(a,strlen(b));
   for(int i=0;i<strlen(b);i++)
       cout<<*(a+i)<<endl;
    return 0;
 } */ 
