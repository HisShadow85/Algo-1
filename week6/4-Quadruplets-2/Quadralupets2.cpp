#include<iostream>
#include<stdio.h>
#include<vector>
#include<fstream>
using namespace std;

class HashTable{
	struct MyStruct
	{
		int data;
		short count;
		MyStruct(int data_ = 0,int count_=0):data(data_),count(count_){}
	};

	  unsigned const MOD;

	  vector<vector<MyStruct> >  hash_table; 

	  unsigned getKey(unsigned num) {
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num);
		return num%MOD;
      }


public:
	  HashTable(unsigned int size):MOD(size){
		  hash_table.resize(size);
	  }

	  void put(int item){
		  bool find = false;
		  int key  =  getKey(item);
		  for (int i = 0; i < hash_table[key].size(); i++)
		  {
			  if(hash_table[key][i].data == item) {
				  hash_table[key][i].count++;
				  find = true;
				  break;
			  }
		  }
		  if(!find){
			  hash_table[key].push_back(MyStruct(item,1));
		  }

	  }

	  short isInChash(int item){
		  int key  =  getKey(item);
		  for (int i = 0; i < hash_table[key].size(); i++)
		  {
			  if(hash_table[key][i].data == item) return hash_table[key][i].count;
		  }
		 return 0;
	  }



};

class Quadruplets {
public:
   

static int zeroQuadrupletsCount(int *first,int* second,int *third , int *fourth ,short N)
{
        int resultCount = 0;
        int size = N;
		HashTable ht(N*N);
                int *firstPair;
                firstPair = new int[size*size];
        for (int i = 0; i < size; i++)
        {
                for (int j = 0; j < size; j++)
                {       
                        firstPair[i*size+j] = first[i]+ second[j];
                        ht.put(third[i]+ fourth[j]);
                        
                }
        }
                size*=size;
				int tmp = 0;
				for (int i = 0; i < size; i++)
				{
					if(tmp = ht.isInChash(-firstPair[i]) ) resultCount+=tmp;
				}
				return resultCount;
}
           
};

int main()
{
        ifstream in("input.txt");
	    ios_base::sync_with_stdio(false);
		//istream &in = cin;
        int N, number;
		
        in>>N;
                if(1 > N  || N > 7000 ) cout<<"0";
                int **input = new int*[4*N];
                for (int i = 0; i < 4; i++)
                {
                        input[i] = new int[N];
                }
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < N; j++)
                {
                        in>>number;
                        input[i][j] = number;
                }
        }
        cout<<Quadruplets::zeroQuadrupletsCount(input[0],input[1],input[2],input[3],N)<<endl;
        return 0;
}