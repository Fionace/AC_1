#include"Base.h"
#include"AC.h"
int main()
{
     ifstream in("./Pattern");
     Node *first=new Node;
     AC ac(in,first);
     cout<<"AC is created!"<<endl;
     ac.All_travese(first);
     int i;
    for(i=0;i<30;i++)
      {
          cout<<i<<":"<<ac.Next[i]<<endl;
      }
   for(i=0;i<30;i++)
      {
          cout<<i<<":"<<ac.Base[i]<<endl;
      }
     for(i=0;i<30;i++)
      {
          cout<<i<<":"<<ac.Check[i]<<endl;
      }
   for(i=0;i<30;i++)
      {
          cout<<i<<":"<<ac.Fail[i]<<endl;
      }


}
