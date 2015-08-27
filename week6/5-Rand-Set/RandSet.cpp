#include<iostream>
#include<vector>
#include<limits>
#include<string>
#include<fstream>
using namespace std;


class HashTable{
	vector<vector<unsigned> > table;
	unsigned const MOD;
	//unsigned const BASE;
	unsigned size;

	unsigned hash(unsigned num) {
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num) * 0x45d9f3b;
		num = ((num >> 16) ^ num);
		return num;
    }

	//if a given element exist the function returs the corresponding index
	 unsigned &findItem(int &item,vector<int> &storage){
		   unsigned index = getKey(item);
		   for (unsigned i = 0; i < table[index].size(); i++)
		   {
			   if(storage[table[index][i]]==item){
				  return table[index][i];
			   }
		   }
		   throw -1;
	  }

public:
	HashTable(unsigned mod):MOD(mod),size(0){
		table.resize(MOD-1);
		//MASK = numeric_limits<unsigned>::max();
	}

	unsigned getKey(int &item){
		int item_size = ( sizeof(item) + sizeof(unsigned)/2) / sizeof(unsigned);
		unsigned *item_ = (unsigned *)&item;
		unsigned hash_ = 0;
		for (int i = 0; i < item_size; i++)
		{
			hash_ += hash( *(item_+i) )%MOD;
		}
		return hash_ % MOD;
	}


	void put(int &item,unsigned storageIndex){
		  unsigned key = getKey(item);
		  table[key].push_back(storageIndex);
		  size++;
	  }

	void remove(int &item,vector<int> &storage){
		 unsigned key = getKey(item);
		// long itemIndex = -1;
		 for (unsigned i = 0; i < table[key].size(); i++)
		   {
			   //if the item exists
			   if(storage[table[key][i]]==item){
				    unsigned int itemIndex = table[key][i];	
				   //if the items is not the last one in the storage
				   if(itemIndex != (storage.size()-1) ){
					   //update the index of the exlast
					   findItem(storage[itemIndex],storage) = itemIndex;
					   //swap the last one with the current item
					   swap(storage[itemIndex],storage[storage.size()-1]);
					   
				   }

				   //remove the item index from that position
			       if(i != table[key].size()-1){
						   swap(table[key][i],table[key][table[key].size()-1]);
					}
				   table[key].pop_back();
				   //remove the last element from the storage
				   storage.pop_back();

				   size--;
			   }
		   }
		 
	}

	bool isItemExist(int &item, vector<int> &storage){
		try{
			findItem(item,storage);
			return true;
		}catch(int exp){
			return false;
		}
	}
	 
	void clear(unsigned mod){
		table.clear();
		table.resize(mod-1);
	}

	unsigned getMOD(){return MOD;}

	float getOccupancy(){ return ( (float)size*100 ) / table.size() ; }
};


class RandSet{
	  
	vector<int> storage;
	HashTable hashTable;

public:
	RandSet(unsigned mod):hashTable(mod){}
	void insert(int &item){
		 //if the Occupancy is above certain percentage
		 if(hashTable.getOccupancy() > 80.0){
			 //rehash with bigger capacity
			 hashTable.clear(hashTable.getMOD()*2-1);
			 for (unsigned i = 0; i < storage.size(); i++)
			 {
				 insert(storage[i]);
			 }
		 }
		 if(!contains(item) ){
		 storage.push_back(item);
		 unsigned index = storage.size()-1;
         hashTable.put(item,index);
		 }
	}

	void remove(int &item){	 
		hashTable.remove(item,storage);
	}

	bool contains(int &item){
		return hashTable.isItemExist(item,storage);
	}

	int random(){
		return storage[rand()%storage.size()];
	}
};



int main(){
    ifstream in("input.txt");
	RandSet rs(33333);
	int N;
	in>>N;
	while (N--)
	{
		string command;
		int operand;
		in>>command;
		if(command == "insert"){
			in>>operand;
			rs.insert(operand);
		}
		else if(command == "contains"){
		     in>>operand;
			 cout<<boolalpha<<rs.contains(operand)<<endl;
		}
		else if(command == "remove"){
			in>>operand;
			rs.remove(operand);
		}
		else if(command == "random"){
			cout<<rs.random()<<endl;
		}
	}
	
	return 0;


};

