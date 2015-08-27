#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;
//This solution uses the binary search to choose ramdom periot of time to stay in the bank
// and BFS to calculate the needed time for the arriving of the robber and the police
class City{
	
public:
	class Junction{
	public:
		int policeTime;//represent the time needed by the police to arrive on a certain junction
		int robberyTime;//represent the time needed by the robber to arrive on a certain junction
		vector<int> adjList;// tha adjancency list
		Junction():policeTime(-1),robberyTime(-1){}
	};

	City(int junctionsNumber){
		junctions.resize(junctionsNumber+1,Junction());
	}

	void addStreet(int firstJunction,int secondJunction){
		 junctions[firstJunction].adjList.push_back(secondJunction);
		 junctions[secondJunction].adjList.push_back(firstJunction);
	}

	Junction &operator[](int index){
		return junctions[index];
	}
	unsigned size(){return junctions.size();}
private:
	vector<Junction>  junctions;
};

class BankRobbery{
	    City &city;
		int bank; //the junction on which is the bank
		int police; //the junction on which is the police station
		int helicopter; //the junction on which is the helicopter
public:  
	BankRobbery(City &city_,int bank_,int police_,int helicopter_):city(city_),bank(bank_),police(police_),helicopter(helicopter_){}

	int fideMaxTimeInBank(){
		//cut the graph by the police arriving time at every junction
		BFSPolice(city,police);
		int min = 0; // min time in the bak. Needed for the binary search
		int max = city[helicopter].policeTime-1;// the ending point's arriving time of the police.
		                                       // Needed for the binary search.
		int lastMaching; //Contains the last time find by BS which is enough 
		                 //to stay in the bank and to arrive at the helicopter location on time
		while (min <= max)//binary search. Each time choose a time to stay in the bank
		{                 // from min to max
			int mid = min + (max - min )/2; // choose the time
			BFS(mid); //update the thime for robber to arrive at a certain place
			if(isEnoughtTime()){// check if this time is enought
               min = mid;
			   lastMaching = mid;
			   min++;
			}else{
               max = mid-1;
			}
		}

		return lastMaching;

	}
	// chek if the time for the robber is enough to arrive ot the helicopter's junction
	bool isEnoughtTime(){
		bool result = false;
		//if the police have delayed and the robber has arrived at the ending junction
		if(city[helicopter].policeTime > city[helicopter].robberyTime && city[helicopter].robberyTime != -1){
			result = true; // return true
		}
		//else return false

		//set all the junctions as not visited by the robber
		for (int i = 1; i < city.size(); i++)
		{
			city[i].robberyTime = -1;
		}
		return result;
	}

	//cutting the graph by calculating the time needed for the police to arrive at a certain junction
    void BFSPolice(City &city,int policeStation){
		queue<int> q;
		q.push(policeStation);
		city[policeStation].policeTime = 0;
		while (!q.empty())
		{
			int junctionIndex = q.front();q.pop();
			City::Junction &CurrJunction = city[junctionIndex];
			for (int i = 0; i < CurrJunction.adjList.size(); i++)
			{
				//if the adjancent junction has not been visited
				if( city[ CurrJunction.adjList[i] ].policeTime == -1){					
					city[ CurrJunction.adjList[i] ].policeTime = CurrJunction.policeTime+ 1;
					q.push(CurrJunction.adjList[i]);
				}
			}
		}
	}
	//set the time needed by the robber to arrives on a certain junction
	void BFS(int bankStartTime = 0){
		queue<int> q;
		q.push(bank);
		city[bank].robberyTime = bankStartTime;
		while (!q.empty())
		{
			int junctionIndex = q.front();q.pop();
			City::Junction &CurrJunction = city[junctionIndex];
			for (int i = 0; i < CurrJunction.adjList.size(); i++)
			{
				//if the junction is not yet visited by the robber and the time need to by visited by him is
				// less than the one needed by the police. The time needed from ane junction to another is 1 min.
				if( city[ CurrJunction.adjList[i] ].robberyTime == -1 && CurrJunction.robberyTime + 1 < city[ CurrJunction.adjList[i] ].policeTime ){					
					city[ CurrJunction.adjList[i] ].robberyTime = CurrJunction.robberyTime + 1;
					q.push(CurrJunction.adjList[i]);
				}
			}
		}
	}

};

int main(){

	//ifstream in("input.txt");
	istream &in = cin;
	int N, M;
	in>>N>>M;
	City city(N);

	for (int i = 0; i < M; i++)
	{
		int first, second;
		in>>first>>second;
		city.addStreet(first,second);
	}

	int police , bank , helicopter;
	in>>bank>>police>>helicopter;
	BankRobbery br(city,bank,police,helicopter);
	cout<<br.fideMaxTimeInBank();
	return 0;
};

/*
11 15
1 2
1 3
2 4
3 4
3 5
4 6
4 7
5 7
6 8
6 9
7 9
7 10
8 9
9 10
10 11
8 1 11
*/