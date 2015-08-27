#include<iostream>
#include<vector>
#include<limits>
#include<queue>
#include<fstream>
using namespace std;

class LightSwitches{

	vector<int> path;//here we going to store the path.The index represent the state and the cell's value
	                 // the corresponding swith from whose switching the state is obtained;
	vector<unsigned short> &switches;//the index represent the number of the switch exlude 0.
	                                 //The cell's value represent the switch in 16bit variable
	                                 //each bit represent the lamp witch is controling
	unsigned short initState;//the initial state represented in 16bit variable, which bit is the on off state
	                         // og the coresponding lamp from 1 to 16
	unsigned short wantedState;//the state we want to achieve.All bulbs are off in state zero;
public:	
	LightSwitches(vector<unsigned short> &switches_,unsigned initState_,unsigned watedState_):
		switches(switches_),initState(initState_),wantedState(watedState_){
	              path.resize(numeric_limits<unsigned short>::max()+1,-1);
	}

	vector<int> run(){
		
		queue<unsigned short> q;
		q.push(initState);
		path[initState] = 0;
		//BFS
		while (!q.empty())
		{
			unsigned short currState = q.front(); q.pop();
			//Make a new stte from swiching all the switches one by one for the current state
			for (int i = 1; i < switches.size(); i++)
			{
				//the ne state onbtained by exor the current state and the switch
				unsigned short newState = currState^(switches[i]);
				if(  path[ newState ] == -1 ){ //if the new state is newer ontained
					 path[ newState ] = i; //update the path puting the switch's index 
					                       //in the correspondin path index
					 q.push(newState);//push the new state in the queue
					 //if we have aproach the wanted state just exit the BFS
					 if(newState == wantedState){
                          goto jump;
					 }
				}
			}
		}

		jump: ;
		//if the state is not reachable
        if(path[wantedState] == -1) return vector<int>();

		vector<int> result;
		//Extract the path 
		while (path[wantedState] != 0)
		{
			result.push_back(path[wantedState]);
			//by exor the state and the switch value from witch the state is obtained
			wantedState = wantedState^(switches[result.back()]);
		}
		//reverse the order in the result array
		for (int i = 0, j = result.size()-1 ; i < j; i++,j--)
		{
			swap(result[i],result[j]);
		}
		return result;
	}




};


int main(){

	//ifstream in("input.txt");
	istream &in = cin;
	char a[18];
	unsigned short initState=0;
	for (int i = 0; i < 16; i++)
	{
		in>>a;
		initState<<=1;
		if(strcmp(a,"on") ) initState++;
	}
	vector<unsigned short> switches(17);
	for (int j = 1; j < 17; j++)
	{
		int switch_=0;
		for (int i = 0; i < 16; i++)
		{
			in>>a;
			switch_<<=1;
			if(strcmp(a,"1") ) switch_++;
		}
		switches[j] = switch_;

	}
	LightSwitches ls(switches,initState,0);
	vector<int> result = ls.run();
	for (int i = 0; i < result.size(); i++)
	{
		cout<<result[i]<<' ';
	}
	cout<<endl;
	return 0;
};