#include<iostream>
#include<vector>
#include<queue>
#include<fstream>
using namespace std;

class VitoshaRun{
public:
	 typedef unsigned short coordinate;
	 typedef unsigned short time;
     typedef unsigned short altitude;
	 static int run(vector<vector<altitude> > &map,coordinate rowStart,coordinate columnStart,coordinate rowFinish,coordinate columnFinish){
		 const time INFINITY = std::numeric_limits<time>::max(); // defines infinity time;
		 vector<vector<time> > timeDist(map.size(),vector<time>(map.size(),INFINITY));//set times to every point to be infinity
		 vector<vector<bool> > visited(map.size(),vector<bool>(map.size(),false)); //array to check if a certain peace of area is already visited
		 timeDist[rowStart][columnStart] = 0;
		 //auxiliary node for the priority queue
		 class Node{
			public:
				coordinate x,y;
				time time_; 
				Node(coordinate x_,coordinate y_,time time__):x(x_),y(y_),time_(time__){}
			};
         //compare function for the queue
		 struct Compare
		 {
			 bool operator()(Node const& n1, Node const& n2)
			 {
				 return (n1.time_ > n2.time_);
			 }
		 };
		 //the priority queue itself
		std::priority_queue< Node, std::vector< Node >, Compare> priorityQ;
		//push the starting point to the queue and let's rock baby
		priorityQ.push(Node(rowStart,columnStart,0) );

		//dijkstra's algorithm
		while(!priorityQ.empty())
		{       
			    //we do not need nodes that we already have visited so we pop them out of the queue
				while (!priorityQ.empty() && visited[priorityQ.top().x][priorityQ.top().y]) priorityQ.pop();
				if(priorityQ.empty()) break; //in case there are no more left unvisited nodes in the queue
				Node currNode = priorityQ.top(); // so let's get the first waiting junction and prossed with him
				priorityQ.pop();//first we will remove it
				if(currNode.x == rowFinish && currNode.y == columnFinish) break; //once we get the shorthes path we no need to continue
				visited[currNode.x][currNode.y] = true; //then set it as a visited
				//consider all of the junction neighbors
				for(int x = currNode.x-1; x < (int)currNode.x+2; x++)
				{       
					    if( x < 0 || !(x < (int)map.size())) continue;
						for(int y = currNode.y-1; y < (int)currNode.y+2; y++)
						{
							if( y < 0 || !(y < (int)map.size())) continue;
                            if(!visited[x][y]){//if that adjacent point is not visited update the distence if the new one is shorter.
								//If the distance to the adjacent point is bigger than the one to the current point plus the distance to the corresponding point
								//we update that distance       --//absolute difference in altitudes between the current cell and the cell you are going to
								if(timeDist[x][y] > (timeDist[currNode.x][currNode.y] + abs(map[x][y]-map[currNode.x][currNode.y]) + 1 ) ){
								   timeDist[x][y] = timeDist[currNode.x][currNode.y] + abs(map[x][y]-map[currNode.x][currNode.y]) + 1 ;
								   //now let's puth into the queue new node with the updated time distance from the starting point to the adjacent point
								   priorityQ.push(Node(x,y,timeDist[x][y]));
								}
							}
						}
				}

		}
		if(timeDist[rowFinish][columnFinish] == INFINITY) return -1;
		else return timeDist[rowFinish][columnFinish];

	}

};
/*
6
0 0 5 5
5 3 1 4 6 7
8 1 5 6 3 1
9 8 5 1 5 2
0 9 1 3 5 8
5 2 5 7 1 7
9 8 1 4 3 9
*/
int main(){
	ifstream in("input.txt");
	short N, startX,startY,finishX,finishY;
	in>>N>>startX>>startY>>finishX>>finishY;
	vector<vector<VitoshaRun::altitude> > map(N,vector<VitoshaRun::altitude>());
	for (int i = 0; i < N; i++)
	{
		map[i].resize(N);
		for (int j = 0; j < N; j++)
		{
			in>>map[i][j];
		}
	}
	cout<<VitoshaRun::run(map,startX,startY,finishX,finishY)<<endl;
	return 0;
}