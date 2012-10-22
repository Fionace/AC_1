#include"AC.h"


AC::AC(ifstream &in,Node *first)
{
	int i=0;
	while(in>>Patt[i])
		i++;
	patt_num=i;
	patt_maxlen=0;//一定要初始化为一个最小值
	for(i=0;i<patt_num;i++)
	{  
		if(Patt[i].size()>patt_maxlen)
			patt_maxlen=Patt[i].size();
	}
	first->state=0;
	first->Nextindex=0;
	first->PR="";
	Nextif[MAX]={0};
	Nextne=0;//指示下一个部分子状态的初始位置
	Base[MAX]={10000};
	Check[MAX]={0};
	Fail[MAX]={0};
	Output[MAX][MAX]={0};//状态

}


int AC::id=0;
bool AC::Trans_son(char *son)
{
	int len=strlen(son);
	int i=0;
	char *tem=new char[len];
	//*tem=*son;
	strcpy(tem,son);
	for(i=1;i<len;i++)
	{
		for(int k=0;k<strlen(tem);k++)
		{ if(*(son+i)==*(tem+k))
			break;
			else
			{*(tem+strlen(tem))=*(son+i);}
		}
	}
	Sort(tem,strlen(tem));
	delete son;
	son=tem;
	return true;
}

bool AC::Test_next(char *son ,int init)
{
	int len=strlen(son);
	int tem[len];
	tem[0]=init;
	int i;
	for(i=1;i<len;i++) 
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

bool AC::CreateTable(Node *curr_old,Node *curr,int init,char *a,char *ini)
{
	int i=int(*a)-int(*ini)+init;
	curr->Nextindex=i;
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
		if(Patt[k].c_str()==tem)
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

bool AC::AttainSon(Node *curr)
{
	int num=strlen(curr->PR);
	for(int i=0;i<patt_num;i++)
	{
		if(Patt[i].size()>num)
		{strcat(curr->son,&Patt[i][num]);
			cout<<curr->son<<endl;
		}
	}
	return true;

}

/*bool Travese(Node *first,int id)
  {
  int i;
  Node *cur;
  Node *fat=New Node;

  cur=first;
  cur->son=new Node[patt_num];//调用AttainSon之前需要给son分配空间
  AttainSon(cur);

  char *son=New char[strlen[cur->son]];
  strcpy(son,sur->son);
  Trans_son(son);
  sonnum=strlen(son);
  fat=cur;
  Node *Son=new Node[sonnum];
  for(int k=0;k<sonnum;k++)  //为子状态建立新结点，并为状态值和前缀赋值
  { Son->state=id+1;
  id++;//id指示当前最后的状态值数值
  Son_PR=new char[strlen(fat->PR)+1];
  strcpy(Son->PR,fat->PR);
  strcat(Son->PR,son+k);
  }
  int init=Nextne;
  while(!Test_next(son,init))
  init++;
  for(k=0;k<sonnum;k++)  //构造表并且为子结点的Nextindex赋值
  {
  if(!CreateTable(fat,Son+k,init,son+k,son))
  { 
  cout<<"FAULT IN CreateTable! "<<endl;
  return false;
  }
  }

 *for(k=0;k<sonnum;k++)
 {
 All_travese(Son+k,id);
 }

 }      
 */
bool AC::All_travese(Node *first)
{
	int i,k;
	int fatnum=1;
	int allson=patt_num;
	Node *fat=new Node[1];
	fat=first;
	int newfatnum=1;
	for(i=0;i<patt_maxlen;i++)
	{
		//Node *thistime=new Node[];
		fatnum=newfatnum;
		newfatnum=0;
		for(k=0;k<fatnum;k++)
		{
			//newfatnum=0;
			Node *cur=new Node;
			//Node *fat=New Node;
			cur=fat+i;
			cur->son=new char[patt_num];//调用AttainSon之前需要给son分配空间
			AttainSon(cur);

			char *son=new char[strlen(cur->son)];
			strcpy(son,cur->son);
			Trans_son(son);
			int sonnum=strlen(son);
			fat=cur;
			Node *Son=new Node[sonnum];
			for(int k=0;k<sonnum;k++)  //为子状态建立新结点，并为状态值和前缀赋值
			{ Son->state=id+1;
				id++;//id指示当前最后的状态值数值
				Son->PR=new char[strlen(cur->PR)+1];
				strcpy(Son->PR,cur->PR);
				strcat(Son->PR,son+k);
			}
			int init=Nextne;
			while(!Test_next(son,init))
				init++;
			if(init==Nextne)
			{
				Nextne++;
			}
			for(k=0;k<sonnum;k++)  //构造表并且为子结点的Nextindex赋值
			{
				if(!CreateTable(fat,Son+k,init,son+k,son))
				{ 
					cout<<"FAULT IN CreateTable! "<<endl;
					return false;
				}
			}
			newfatnum+=sonnum;

		}

		return true;      



	}
}

