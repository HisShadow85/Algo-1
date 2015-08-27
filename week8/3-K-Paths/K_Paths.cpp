#include<iostream>
#include<vector>
#include<fstream>
using namespace std;

//a directed acyclic graph(with reversed directions)
class Graph{
	//every index represent a junction
	vector<vector<short> > vertecies;

public:

	Graph(short size):vertecies(size){}

	//store the edges with reversed directions
	void addEdge(short from , short to){
		vertecies[to].push_back(from);//we save the reverse direction of the edges
	}
	//return the adjacency list of a certain junction
	vector<short> &operator[](short vertex){
		return vertecies[vertex];
	}

	unsigned size() { return vertecies.size(); }
};


class K_Paths{
	Graph &graph;	// graph with reversed directions
	vector<short> availablePaths; //here we will store the all possible ways from a certain junction
	short startVertex; //this variable will hold the starting point for comparison in the DFS
public:
	K_Paths(Graph &graph_):graph(graph_){
	}

	short findKPaths(short startVertex_,short edningVertex,short k){
		availablePaths.clear();
		availablePaths.resize(graph.size(),0);
		startVertex = startVertex_;
		return DFS(edningVertex,k);
	}
	//find a path trought DFS by given starting vertex and the number(lenght) of the 
	//possible junctions to the ending one.Return the possible ways to the ending point.
	//The last recursive call allways returns 1 ot 0 and the previus call sum the single results
	//Remember, hence we store the revers directions of the edges the ending point is the starting
	//point and vise versa, the ending point is the starting one.
	short DFS(short currVertex,short pathLenght){
		if(!pathLenght){	//if we reach the possible amount of steps through the junctions
			//check if we are ot the wanted ending junctions and return the result of 1 possible 
			//way to the ending point
			return startVertex == currVertex ? 1 : 0;
		}
		//if we have already checked the possible ways from that junctions to the einding one
		//we just return the stored result;
		if(availablePaths[currVertex]) return availablePaths[currVertex];
		int paths = 0; //here we will compute the available ways to the ending point
		for (int i = 0; i < graph[currVertex].size(); i++)
		{
			//call DFS for every adjacent junction with possible number(length) of steps minus 1
			 paths+=DFS(graph[currVertex][i],pathLenght-1);
		}
		//if we haven't store the all possible ways from that junction to the ednisg one - store it
		if(paths) availablePaths[currVertex] = paths;
		return paths;
	}
};

int main(){

	//ifstream in("input.txt");
	istream &in = cin;
	short N , from , to, max=0;
	in>>N;
	short** input = new short*[N];
	for(short i = 0 ; i < N ; i++)
	{
		input[i] = new short[2];
		in>>input[i][0]>>input[i][1];
		if(input[i][0] > max) max = input[i][0];
		if(input[i][1] > max) max = input[i][1];
	} 
	Graph graph(max+1);
	for (int i = 0; i < N; i++)
	{
		graph.addEdge(input[i][0],input[i][1]);
	}
	delete[] input;
	K_Paths paths(graph);
	in>>from>>to>>max;
	cout<<paths.findKPaths(from ,to , max)<<endl;
	return 0;
};