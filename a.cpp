#include"Base.h"
#include"AC.h"
int main()
{
     ifstream in("./Pattern");
     Node *first=new Node;
     AC ac(in,first);
     ac.All_travese(first);
     int i;
    for(i=0;i<MAX;i++)
      {
          cout<<i<<":"<<Next[i]<<endl;
      }
   for(i=0;i<MAX;i++)
      {
          cout<<i<<":"<<Base[i]<<endl;
      }
     for(i=0;i<MAX;i++)
      {
          cout<<i<<":"<<Check[i]<<endl;
      }
   for(i=0;i<MAX;i++)
      {
          cout<<i<<":"<<Fail[i]<<endl;
      }


}
