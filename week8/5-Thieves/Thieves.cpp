#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

class Thieves{

public:

	struct Item{
		unsigned value,weight;
		Item(unsigned value_=0,unsigned weight_=0):value(value_),weight(weight_){}
	};

	static vector<int> krajba(vector<Item> &items, unsigned bagWeight){
		vector<int> result;
		vector<vector<int> > workMatrix(items.size()+1,vector<int>(bagWeight));
		vector<vector<bool> > path(items.size()+1,vector<bool>(bagWeight,false));
		//hence the workMatrix is one row bigger than the item's number the zero row will represen the
		//value when we put non of the items in the bag, and this is zero value. So the first row will 
		//be line of zeroes
		//iterate trought the items
		for (int i = 0; i < items.size(); i++)
		{   
			//pretend that the bag is with capacity from 1 to bagWeight increasing each loop row
			for (int j = 0; j < bagWeight; j++)
			{
				//if the bag was with capacity of j+1 weight(0+1 = 1kg) and the item can fit in;
				if(j+1 > items[i].weight){
					/*if the above cell  value is greater then the current item's value + value in the cell
					from the above row represented by the index calculate from residue of subtraction between 
					the current weight of the backpack and the current item's weight*/
					if(workMatrix[i][j] >= items[i].value + workMatrix[i][j-items[i].weight]){
						workMatrix[i+1][j] = workMatrix[i][j]; //we take the greatest value;
					}else {
						//else we calculate the new value if the bag was with capacity j+1 and has to bears
						//one or many of the items from 0 to i
						workMatrix[i+1][j] = items[i].value + workMatrix[i][j-items[i].weight];
						path[i+1][j] = true; //and keep the path saying that we want to put that item
						                           // into the bag
					}
				}//if they are equal, both the current bag capacity and the current item
				else if(j+1 == items[i].weight){//same as above but with less calculations
					if(workMatrix[i][j] > items[i].value){
						workMatrix[i+1][j] = workMatrix[i][j];
					}
					else{
						workMatrix[i+1][j] = items[i].value;
						path[i+1][j] = true; //and keep the path saying that we want to put that item
						                           // into the bag
					}
				}// in case the item dosent fit we take the value from the above cell
				else{
					workMatrix[i+1][j] = workMatrix[i][j];
				}
			}
		}//end of the item's calculation
		//the firs element will contain the max posible value we can take in our bag
		result.push_back(workMatrix[items.size()][bagWeight-1]);
		workMatrix.clear();//we don't need anymore the waorking matrix
		//the algorith for recovering the path is as follows:
		//First we start with the last element(item) with the full bag capacity(weight).
		//If the cell coresponding to item*weight is true then we take the element and
		//subtract it weight from the current capacity(weight)
		//Else if the cell is false we prossed with the next item(reverse order) with the same
		//current capacity
		for (int item = items.size(),weight = bagWeight-1; item > 0 ; item-- )
		{
			if(path[item][weight]){
				result.push_back(item-1);
				weight -= items[item-1].weight;
			};
		}

		return result;
	}


};

int main(){

	//ifstream in("input.txt");
	istream &in = cin;
	int N, W;
	in>>N>>W;
	vector<Thieves::Item> input(N);
	for (int i = 0; i < N; i++)
	{
		in>>input[i].weight>>input[i].value;
	}
	vector<int> result = Thieves::krajba(input,W);
	cout<<result[0]<<endl;
	for (int i = 1; i < result.size(); i++)
	{
		cout<<result[i]<<' ';
	}
	cout<<endl;
	return 0;
};