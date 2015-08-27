#include<iostream>
#include<queue>
#include<fstream>
#include<limits>
#include<vector>
using namespace std;

//non-zero based graph
class Map{
public:
	  typedef unsigned short junctionNum;
	  typedef unsigned short distance_;
	  class Street{
	  public:
		  junctionNum  end;
		  distance_ distance;
		  Street(junctionNum end_ = 0,distance_ distance__ = 0):end(end_),distance(distance__){}
	  };
	  vector<Street> &operator[](junctionNum index){
		  if(index <1 || index >= junctions.size()) throw "Invalid junction index";
		  return junctions[index];
	  }
	  unsigned size(){return junctions.size();}
	  void addStreet(junctionNum first, junctionNum second,distance_ distance){
		    if(first <1 || first >= junctions.size()) throw "Invalid junction index";
			if(second <1 || second >= junctions.size()) throw "Invalid junction index";
			junctions[first].push_back(Street(second,distance));
			junctions[second].push_back(Street(first,distance));
	  }
	  Map(junctionNum num){
		  junctions.resize(num+1);
		  junctions.push_back(vector<Street>());
	  }
		
private:
	vector<vector<Street>> junctions;
};

class Navigation{

public:

	static vector<int> navigate(Map &map,Map::junctionNum start, Map::junctionNum end){
		const Map::distance_ INFINITY = std::numeric_limits<Map::distance_>::max(); // defines infinity
		vector<bool> visited(map.size(),false); //array to check if a certain junction is already visited
		vector<unsigned> distance(map.size(),INFINITY); // holds the current distance from the starting junction to a certain one
		vector<unsigned> path(map.size(),0); // store the path to the ending point
		distance[start] = 0;
		//auxiliary node for the priority queue
		class Node{
		public:
			Map::junctionNum  junction; //the index of the certain current junction
			Map::distance_ distance; // and the distance from the previus to the current junction
			Node(Map::junctionNum junction_,Map::distance_ distance_):junction(junction_),distance(distance_){}
	    };
		//compare function for the queue
		struct Compare
		{
			bool operator()(Node const& n1, Node const& n2)
			{
				return (n1.distance > n2.distance);
			}
		};
		//the priority queue itself
		std::priority_queue< Node, std::vector< Node >, Compare> priorityQ;
		//push the starting point to the queue and let's rock baby
		priorityQ.push(Node(start,0) );
		//dijkstra's algorithm
		while(!priorityQ.empty())
		{       
			    //we do not need nodes that we already have visited so we pop them out of the queue
				while (!priorityQ.empty() && visited[priorityQ.top().junction]) priorityQ.pop();
				if(priorityQ.empty()) break; //in case there are no more left unvisited nodes in the queue
				Node tempNode = priorityQ.top(); // so let's get the first waiting junction and prossed with him
				priorityQ.pop();//first we will remove it
				Map::junctionNum nodeIndex = tempNode.junction;//only for clarity
				if(nodeIndex == end) break; //once we get the shorthes path we no need to continue
				visited[nodeIndex] = true; //then set it as a visited
				//consider all of the junction neighbors
				for (Map::junctionNum i = 0; i < map[nodeIndex].size(); i++)
				{
					Map::junctionNum ajdNodeIndex = map[nodeIndex][i].end; //only for clarity
					if(!visited[ajdNodeIndex]){ //if that adjacent junction is not visited update the distence if the new one is shorter
						//if the distance to the adjacent junction is bigger than the one to the current junction plus the distance to the corresponding junction
						//we update that distance
						if(distance[ajdNodeIndex] > distance[nodeIndex] + map[nodeIndex][i].distance ){
						  distance[ajdNodeIndex] = distance[nodeIndex] + map[nodeIndex][i].distance;
						  path[ajdNodeIndex] = nodeIndex;//and set the the current junction as path to that adjacent juction
						  //now let's puth into the queue new node with the updated distance from start to the adjacent juction
						  priorityQ.push(Node(map[nodeIndex][i].end,distance[ajdNodeIndex] ) );
						}
					}
				}
    
			}
			if(distance[end] == INFINITY) return vector<int>();//make some different return
			//now we are going to extract the path
			vector<int> result;
			result.push_back(distance[end]);
			result.push_back(end);
			while (path[end] != end)
			{
				result.push_back(path[end]);
				end = path[end];
			}
			for (int i = 1,j = result.size()-1; i < j; i++ , j--)
			{
				swap(result[i],result[j]);
			}
			return result;
	}
};

int main(){
	ifstream in("input.txt");
	Map::junctionNum N , start, trainStation, firstJunction , secondJuction;
	int M;
	Map::distance_ distance;
	in>>N>>M>>start>>trainStation;
	Map map(N);
	for (int i = 0; i < M; i++)
	{
		in>>firstJunction>>secondJuction>>distance;
		map.addStreet(firstJunction,secondJuction,distance);
	}

	vector<int> result = Navigation::navigate(map,start,trainStation);
	if(result.size()){
			cout<<result[0]<<endl;
			
			for (M = 1; M < (int)result.size()-1; M++)
			{
				cout<<result[M]<<' ';
			}
			cout<<result[M]<<endl;
		}
	else cout<<"NO WAY\n";
    
	return 0;

}