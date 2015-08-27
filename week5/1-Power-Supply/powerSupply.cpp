#include<iostream>
#include<queue>
#include<functional>
#include<vector>
#include<algorithm>
#include<fstream>
#include<stack>
using namespace std;
class Connection;
class Vertex{
		public:
		unsigned ID;
		int index;
		int lowlink;
		bool onStack;
		vector<Connection> adj;
		Vertex():ID(0),index(-1),onStack(false){}
		Vertex(int ID_):ID(ID_),index(-1),onStack(false){}
	};
//priority_queue<int,vector<int>,greater<int> > q;
class Connection{
		public:
		int first;
		int second;
		int distance;
		Connection(int first_, int second_ ,int distance_):first(first_),second(second_),distance(distance_){}
		Connection(const Connection &init):first(init.first),second(init.second),distance(init.distance){}
		bool operator<(const Connection &other){return distance < other.distance;}
    };

class MPT{
	
public:

	MPT(vector<Connection> &connections,int N){
		//intializating the MST (with stell not connected vertces
		for (int i = 0; i < N; i++) MST.push_back(Vertex(i)); 
		
        int *junctions = new int[N];/*we are going to use this array for the Kruskal's algorithm.
		Each of the indices represents the vertex ID and the value in the corresponding cell the 
		index representing the vertex to witch the current vertex is connected;*/
	    // init the junctions array so every vertex to be connected to himself
	    for (int i = 0; i <N ; i++) junctions[i] = i;
		//sort the connection so we peek every time the shortest one
	    sort(connections.begin(),connections.end());
        //declare and initialize the the variable in which we are going to store the needed length  of cable
	    lenghtOfTheMST = 0;
		//now is the time for Kruskal baby!!! :)//here we extract the first MST
	    for (int i = 0; i < connections.size(); i++)
	    {
				int first = connections[i].first; //this will represents the starting point(one side of the coonection)
				int second; //this will represents the ending point(second side of the coonection)
				int firstRoot, secondRoot; //well this is clear.
				//lets find the root of the starting junction
				while(first != junctions[first]) first = junctions[first];
				//now let's save the root and normalize(relax) the corresponding tree
				firstRoot = first;first=connections[i].first;
				//using second as a temporaly variable
				while(junctions[first] != firstRoot){
					  second = junctions[first]; 
					  junctions[first] = firstRoot; 
					  first = second;
				}
				//let's do the same for the ending junction
				second = connections[i].second;
				while(second != junctions[second]) second = junctions[second];
				secondRoot = second; second = connections[i].second;
				//using firs as a temporaly variable
				while(secondRoot != junctions[second]) { 
					first = junctions[second]; 
					junctions[second] = secondRoot ; 
					second = first;
				}
				//if the roots are the same this means that both junctions are connected
				if(firstRoot != secondRoot){
					junctions[secondRoot] = firstRoot; //connecting the second tree to the first
					lenghtOfTheMST+=connections[i].distance; //add the new distance to the cable needs
				    //lets now add theconnection between the two junction. It has to be directed one
					MST[connections[i].first].adj.push_back(connections[i]);
					MST[connections[i].second].adj.push_back(Connection(connections[i].second,connections[i].first,connections[i].distance));
				}
				else{
					notUsedConnections.push_back(connections[i]);
				}
		}
	}//we are done with the MST initialization

	unsigned run(){

			unsigned secondMPTLength = 2147483647, seconBiggestEnge;
			for (int i = 0; i < notUsedConnections.size(); i++)
			{
				MST[notUsedConnections[i].first].adj.push_back(notUsedConnections[i]);
				MST[notUsedConnections[i].second].adj.push_back( Connection(notUsedConnections[i].second,notUsedConnections[i].first,notUsedConnections[i].distance) );
				currBigestEdge = notUsedConnections[i].distance;
				seconBiggestEnge = tarjanSCC(MST);
				if(lenghtOfTheMST - seconBiggestEnge + currBigestEdge  < secondMPTLength)
					secondMPTLength = lenghtOfTheMST - seconBiggestEnge + currBigestEdge;
				MST[notUsedConnections[i].first].adj.pop_back();
				MST[notUsedConnections[i].second].adj.pop_back();
			}
			return secondMPTLength;
	  }

	unsigned tarjanSCC(vector<Vertex> &graph){
	  //input: graph G = (V, E)
	  //output: set of strongly connected components (sets of vertices)
	  vector<Vertex*> SCC;
	  index = 0;
	  stack<Vertex*> pathStack;
	  unsigned result = 0;
	  for (int i = 0; i < graph.size(); i++)
	  {
		  if(graph[i].index == -1){
			if(result = strongconnect(&graph[i],graph,SCC,pathStack,NULL)) break ;
			}
	  }
	  for (int i = 0; i < graph.size(); i++){
				graph[i].index = -1;
				graph[i].onStack = false;
			}
	  return result;
	}
	//it return true if the only one SCC is build
	unsigned strongconnect(Vertex *v,vector<Vertex> &graph,vector<Vertex*> &SCC,stack<Vertex*> &pathStack,Vertex *previus){
		// Set the depth index for v to the smallest unused index
		v->index = index;
		v->lowlink = index;
		index = index + 1;
		pathStack.push(v);
		v->onStack = true; // mark v as on the stack

		// Consider successors of v
		for (int j = 0; j < v->adj.size(); j++){
			 Vertex *adj = &graph[v->adj[j].second];
			 if(adj->index == -1){
			   if(unsigned result = strongconnect(adj,graph,SCC,pathStack,v)) return result;
			   v->lowlink  = v->lowlink < adj->lowlink ? v->lowlink : adj->lowlink;
			}else if(adj->onStack && adj != previus && v->lowlink != adj->lowlink) {
				v->lowlink  = v->lowlink < adj->index ? v->lowlink : adj->index;
			}
		}
	

		// If v is a root node, pop the stack and generate an SCC
		if (v->lowlink == v->index){
			if( pathStack.top() !=  v){
				Vertex *tmp = pathStack.top();
				Vertex *prev = v;
				unsigned secondBiggestEnge = 0; // this will hold the second biggest edge in the cycle. If we remove it the grap will be MST again
			
				do{
					tmp = pathStack.top();
					tmp->onStack = false;
					//tmp->index = -1;
					pathStack.pop();
					SCC.push_back(tmp);
					for (int k = 0; k < tmp->adj.size(); k++) //check the distance to the previus vetex of the cycle
					{
					  if(tmp->adj[k].second == prev->ID && tmp->adj[k].distance != currBigestEdge && tmp->adj[k].distance > secondBiggestEnge){
								secondBiggestEnge = tmp->adj[k].distance;
						}
					}
					prev = tmp;
				}while(tmp != v);
				return secondBiggestEnge ;
			}
			else {
				//since we are looking only for one cycle the SCC made from only one component does not concern us
				pathStack.top()->onStack = false;
				//pathStack.top()->index = -1;
				pathStack.pop();
			}
		   }
	
		return 0;
	}

	unsigned getMSTLength() {return lenghtOfTheMST;}

	private:		
	vector<Vertex> MST; // vector conrtaining all of the Minimum spanning tree(MST)
	vector<Connection> usedConnections;// represents the edges in the MST
	// hear we will store the unused connections
	vector<Connection> notUsedConnections;
	int index;
	
	//declare the the variable in which we are going to store the needed length  of cable
	unsigned lenghtOfTheMST;

	unsigned currBigestEdge;
};

int main(){
	//ifstream in("input.txt");
	istream &in = cin;
	vector<Connection> connections;
	int N,biggest= 0,number1,number2,distance;
	in>>N;
	for (int i = 0; i < N; i++)
	{
		in>>number1>>number2>>distance;
		if(number1 > biggest) biggest = number1;
		if(number2 > biggest) biggest = number2;
		connections.push_back(Connection(number1-1,number2-1,distance));
	}
	 MPT ps(connections,biggest);
	 //first MST
	 cout<<ps.getMSTLength()<<endl;
	 //second MST
	 //cout<<ps.run()<<endl;
	 return 0;
}