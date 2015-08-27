#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class HashTable{
	vector<vector<int> > table;
	unsigned const MOD;
	unsigned size;

	unsigned getKey(unsigned num) {
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num);
		return num % MOD; ;
    }

	

public:
	HashTable(unsigned mod):MOD(mod),size(0){
		table.resize(MOD-1);
	}

	void put(int item){
		  unsigned key = getKey(item);
		  table[key].push_back(item);
		  size++;
	  }

	

	bool isItemExist(int item){
	      unsigned key = getKey(item);
		  for (int i = 0; i < table[key].size(); i++)
		  {
			  if(table[key][i] == item) return true;
		  }
		  return false;
	}
	 
	void clear(unsigned mod){
		table.clear();
		table.resize(mod-1);
	}
};


class K_Intersect {

	 static void func(vector<int> &input,HashTable **ht){
		//make new empty hash table
		HashTable *newht = new HashTable(33333);

		for (int i = 0; i < input.size(); i++)
		{
			//put in the new hash table only the integers from the input array 
			//that match with thise in the ht 
			if((*ht)->isItemExist(input[i])) newht->put(input[i]);
		}
		//delete the input hash table
		delete (*ht);
		//and assign to the input hashtable the new one
		*ht = newht;
	}

public:
	static vector<int> findKIntersect(vector<vector<int> > &input){
		HashTable *ht = new HashTable(33333);
		vector<int> result;
		if(input.empty()) return result;
		else if(input.size()==1) return result = input[0];
		//put into the hash table the integers from the first list
		for (unsigned i = 0; i < input[0].size(); i++)
		{
			ht->put(input[0][i]);
		}

		unsigned size = input.size()-1;
		//put the all repeating integers from the rest of the list, exluding the last one, 
		//into one hash table
		for (unsigned i = 1; i < size; i++)
		{
			 func(input[i],&ht);
		}
		//the repeating integers from the last list with these in the common hash table
		// are the result set
		for (int i = 0; i < input[size].size(); i++)
		{
			if(ht->isItemExist(input[size][i]) ) result.push_back(input[size][i]);
		}
		delete ht;
        return result;
	}

};

int main(){

	ifstream in("input.txt");
	int N;
	in>>N;
	vector<vector<int> > input(N);
	for (int i = 0; i < input.size(); i++)
	{
		in>>N;
        input[i].resize(N);
		for (int j = 0; j < N; j++)
		{
			in>>input[i][j];
		}
	}
	input[0] =  K_Intersect::findKIntersect(input);

	for (unsigned i = 0; i < input[0].size(); i++)
	{
		cout<<input[0][i]<<endl;
	}
	return 0 ;
}

/*
3
5 2 5 10 3 1
8 7 13 3 9 2 55 47 10
3 42 2 3
*/