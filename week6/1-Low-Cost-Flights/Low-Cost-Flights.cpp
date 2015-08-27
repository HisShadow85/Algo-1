#include<iostream>
#include<limits>
#include<vector>
#include<fstream>
using namespace std;
class LowCostFlights{	
public:
	typedef unsigned short airport;
    typedef short cost;
	const cost INFINITY ; //cost that shows there is no fly to this direction
	
	LowCostFlights(vector<vector<cost> > &adjMatrix,airport N):
	  INFINITY(std::numeric_limits<cost>::max()),
	  NOWAY(std::numeric_limits<airport>::max()){
      dist.resize(N,vector<cost>(N,INFINITY));
	  next.resize(N,vector<airport>(N,NOWAY));
	  AirportsNum=N;
	  FloydWarshall(adjMatrix);
	}

    void FloydWarshall(vector<vector<cost> > &adjMatrix){
    //for each edge (u,v)
	  for (airport u = 0; u < AirportsNum; u++)
	  {
		  dist[u][u] = 0; //the distance from the vertex to itself
		  for(airport v = 0; v < AirportsNum; v++){
			  if(adjMatrix[u][v]){
                 dist[u][v] = adjMatrix[u][v]; // the weight of the edge (u,v)
				 next[u][v] = v; //to pass from u to v we must go first throughout v
			  }
		  }
	  }
	  // standard Floyd-Warshall implementation
	  for (airport k = 0; k < AirportsNum; k++)
	  {
		  for (airport i = 0; i < AirportsNum; i++)
		  {
			  for (airport j = 0; j < AirportsNum; j++)
			  {
				  if( (dist[i][k]+ dist[k][j]) < dist[i][j] ){
					   dist[i][j] = dist[i][k] + dist[k][j];
					   next[i][j] = next[i][k];

				  }
			  }
		  }
	  }
}

	vector<airport> getPath(airport start,airport end){
		   if (next[start][end] == NOWAY)
			   return vector<airport>();
		   vector<airport> path;
		   airport currAirport = start;
		   path.push_back(currAirport);
		   while(currAirport != end){
			   currAirport = next[currAirport][end];
			   path.push_back(currAirport);
		   }
		   return path;
		}

	cost getLowestCost(airport start,airport end){
		return dist[start][end];
	}

private:
	vector<vector<cost> > dist;//a V*V array of minimum distances initialized to infinity.
	vector<vector<airport> > next; //a V*V array of vertex indices initialized to null (-1)
    airport AirportsNum; //the number of vertices
	const airport NOWAY;
};

int main(){
	ifstream in("input.txt");

	LowCostFlights::airport N;
	in>>N;
	vector<vector<LowCostFlights::cost> > adjMatrix;
	adjMatrix.resize(N);
	for (LowCostFlights::airport i = 0; i < N; i++)
	{
		adjMatrix[i].resize(N);
		for (LowCostFlights::airport j = 0; j < N; j++)
		{
			in>>adjMatrix[i][j];
		}
	}
	LowCostFlights lcf(adjMatrix,N);
	unsigned short M;
	LowCostFlights::cost cost;
	LowCostFlights::airport start,end;
	in>>M;
	for (unsigned short i = 0; i < M; i++)
	{
		in>>start>>end;
		cost = lcf.getLowestCost(start,end);
		if(cost != lcf.INFINITY) cout<<cost<<endl;
		else cout<<"NO WAY\n";
	}
	return 0;
}
/*8
0 9 0 3 2 0 0 0
0 0 7 2 0 0 9 0
7 0 0 0 0 7 7 0
0 2 0 0 0 0 0 0
0 0 0 0 0 0 5 0
0 3 0 0 0 0 0 0
0 0 0 0 0 0 0 0
0 0 0 0 0 0 4 0
9
0 5
3 6
6 4
3 2
5 4
5 3
7 6
4 5
2 6*/