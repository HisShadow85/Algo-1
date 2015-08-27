#include<iostream>
#include<vector>
#include<queue>
#include<ios>
#include<string>
#include<fstream>
#include<stack>
using namespace std;


/*Според условието на Иван Тодоров, ако имаме пристанища свързани а-б-в то освен че пътя от а до б е 1-ца то и от
а до в е също еденица защото не се слиза от пристанището, и заради това не изкарва същия отговор като в примера.
За да се изкара същия отговор трябва от пристанище а до в да се минава за 2. 
За целта подкоментирайте извикването на функцията seeHarbors(); тялото на  Castaway::run*/

class Castaway{

#define LAND '#'
#define SEA '.'
#define START '0'
#define RESCUE '1'
	
	  class Vertex{
	  public:
		  int x,y;		
		  Vertex(int x_=0, int y_=0):x(x_),y(y_){}
	  };

	  class Harbor{
	  public:
		  char name;
		  int x, y;
		  int day;
		  vector<Harbor*> adjList;
		  Harbor();
		  Harbor(char name_ , int x_, int y_):name(name_),x(x_),y(y_),day(0){}
		  bool operator<=(const Harbor &other) { return name<=other.name;}
		  bool operator<(const char ch){ return name<ch;}
		  bool operator>(const char ch){ return name>ch;}
		  bool operator==(const char ch){ return name==ch;}
	  };

	  bool ** isDiscovered;
	  vector<Harbor> harbors;
	  vector<vector<char> > SCC; //strongly conected components
	  char **map;
	  int X,Y,startX,startY,rescueX,rescueY;

public:
	  Castaway():map(NULL){}

	int run(char **map_,char **harboardConnectiond,int harConnCount,int X_, int Y_, int startX_, int startY_, int rescueX_, int rescueY_){
		X=X_;Y=Y_;startX=startX_;startY=startY_;rescueX = rescueX_; rescueY = rescueY_;map=map_;
		if(startX == rescueX && startY == rescueY) return 0;
		//initialize the matrix indicating if a field is already visited  
		isDiscovered = new bool*[X];
		for (int i = 0; i < X; i++)
		{
			isDiscovered[i] = new bool[Y];
			fill_n(isDiscovered[i],Y,false);
		}

		//extract the harboards
		for (int i = 0; i < X; i++)
		{
			for (int j = 0; j < Y; j++)
			{
				if( !isDiscovered[i][j] && !(!isalpha(map[i][j]) && !(map[i][j] == LAND) )){
					char res;
					if(res = island(i,j)){
						if(res == 1) return 1; //on the same island
						else if(res == -1) return -1; //no way to safty DOOM!
					} 
				}
			}
		}
		delete map; //optional
		//sorting the harbors for the binry search;
		quickSort(harbors.begin(),0, harbors.size()-1);
		
		//init the harboards Adjacency lists
		for (int i = 0; i < harConnCount; i++)
		{
			int first,second;
			first=binarySearch(harbors,harboardConnectiond[i][0],0,harbors.size()-1);
			second=binarySearch(harbors,harboardConnectiond[i][1],0,harbors.size()-1);
			if(first != - 1 && second != -1 && second != first)
				harbors[first].adjList.push_back(&harbors[second]);
			    harbors[second].adjList.push_back(&harbors[first]);
		}
		delete harboardConnectiond;//optional
		unvisiteTheHarbors();
		// make SCC trough sea
		seeHarbors();
		//make the final graph
		refreshAdjancacyList();
		unvisiteTheHarbors();
		queue<Harbor*> queue;
		Harbor *curr;
		//push the starting point in to the queue
		for (int i = 0; i < harbors.size(); i++)
		{
			if(harbors[i].name == START){
              curr = &harbors[i];
			  break;
			}
		}
		queue.push(curr);
		//set the starting point as visited
		isDiscovered[curr->x][curr->y] = true;
		int d = 0;
		while(!queue.empty()){
              
			 curr = queue.front(); queue.pop();

			 for (int j = 0; j < curr->adjList.size(); j++)
			 {
				 if(curr->adjList[j]->x == rescueX && curr->adjList[j]->y == rescueY ){
					 return 1+curr->day;
				 }
				 if(!isDiscovered[curr->adjList[j]->x][curr->adjList[j]->y]){
					 isDiscovered[curr->adjList[j]->x][curr->adjList[j]->y] = true;
					 curr->adjList[j]->day = curr->day+1;
					 queue.push(curr->adjList[j]);
				 }
			 } // end adjancacy list iteration
			

			} // edn of iteratin the graph



		return -1;
		}


char island(int landX,int landY){
	bool isThereHarbor = false;
	bool isStartingPointOnThisLand = false;
	bool isRescueTeamOnThisLand = false;


	vector<char> harborsConnectedByLand;
	
	
	    queue<Vertex> queue;
		//push in to the queue the starting point
		queue.push(Vertex(landX,landY));
		//set the starting point to visited
		isDiscovered[landX][landY] = true;
		while(!queue.empty()){
              
				Vertex curr = queue.front(); queue.pop();
				//make a list of strongly connected componenets by land. We represent stating and rescue point as a harbords
				if(isalpha(map[curr.x][curr.y])){// if a land is a harbor
					harbors.push_back(Harbor(map[curr.x][curr.y],curr.x,curr.y));
					harborsConnectedByLand.push_back(map[curr.x][curr.y]);
					isThereHarbor = true;
				}else if(curr.x == startX && curr.y == startY){ // if the piece of the land is the starting point
					harbors.push_back(Harbor(START,curr.x,curr.y));
					harborsConnectedByLand.push_back(START);
					isStartingPointOnThisLand = true;
				}else if(curr.x == rescueX && curr.y == rescueY){// if the piece of the land is the rescue point
					harbors.push_back(Harbor(RESCUE,curr.x,curr.y));
					harborsConnectedByLand.push_back(RESCUE);
					isRescueTeamOnThisLand = true;
				}

				if(curr.y-1 >= 0 && !isDiscovered[curr.x][curr.y-1] && map[curr.x][curr.y-1] != SEA ){
					isDiscovered[curr.x][curr.y-1] = true;
					queue.push(Vertex(curr.x,curr.y-1));
				}
				if(curr.y+1 < Y && !isDiscovered[curr.x][curr.y+1] && map[curr.x][curr.y+1] != SEA ){
					isDiscovered[curr.x][curr.y+1] = true;
					queue.push(Vertex(curr.x,curr.y+1));
				}
				if(curr.x+1 < X && !isDiscovered[curr.x+1][curr.y] && map[curr.x+1][curr.y] != SEA ){
					isDiscovered[curr.x+1][curr.y] = true;
					queue.push(Vertex(curr.x+1,curr.y));
				}
				if(curr.x-1 >= 0 && !isDiscovered[curr.x-1][curr.y] && map[curr.x-1][curr.y] != SEA ){
					isDiscovered[curr.x-1][curr.y] = true;
					queue.push(Vertex(curr.x-1,curr.y));
				}

		}

		if(isStartingPointOnThisLand && isRescueTeamOnThisLand)  return 1;
		//if the rescue team and starting point are not in same island and there is no harbor the castaway is screwed
		if( !isThereHarbor && !( !(isStartingPointOnThisLand && !isRescueTeamOnThisLand) 
			                     && !(!isStartingPointOnThisLand && isRescueTeamOnThisLand) ) ){
			return -1;
		}
		 //only if we have atlease one harbor in the island or else 
		 //there will be either no way to rescue team or they well be on a same island and flag will be set to note that
		if(isThereHarbor && (harborsConnectedByLand.size() > 1 )) SCC.push_back(harborsConnectedByLand);
		
		return 0;
}

void seeHarbors(){
	vector<char> harborsConnectedBySea;

	queue<Harbor*> queue;
	for (int i = 2; i < harbors.size(); i++)// warning it suppose 0 and 1 indices are the starting and rescue point
	{
		if(isDiscovered[harbors[i].x][harbors[i].y]) continue;
    
		//push in to the queue the starting point
		queue.push(&harbors[i]);
		//set the starting point to visited
		isDiscovered[harbors[i].x][harbors[i].y] = true;
		harborsConnectedBySea.push_back(harbors[i].name);
		while(!queue.empty()){
			Harbor *curr = queue.front(); queue.pop();
			for (int j = 0; j < curr->adjList.size(); j++) //iterate trough the Adjacency list of the current harbor
			{
				if( !isDiscovered[curr->adjList[j]->x][curr->adjList[j]->y] ){

					isDiscovered[curr->adjList[j]->x][curr->adjList[j]->y] = true;
					harborsConnectedBySea.push_back(curr->adjList[j]->name);
					queue.push(curr->adjList[j]);
				}
			}//end Adjacency iteration
		}//end discovering SCC
		SCC.push_back(harborsConnectedBySea);
		harborsConnectedBySea.clear();
	}//end the iteration trought all of the harbors

}

void refreshAdjancacyList(){

	for (int i = 0; i < SCC.size(); i++) //iterate trought SCC groups
	{
		for (int j = 0; j < SCC[i].size(); j++) //iterate trought the consecutive group
		{
			Harbor *first;
			//takes the consecutive element and compers it with the next ones
			try{
			first = &harbors[binarySearch(harbors.begin(),SCC[i][j],0,harbors.size()-1)];
			}catch(...) {continue;}

			for (int k = j+1; k < SCC[i].size(); k++)//heare e take the next harbor name and chek if the are already connected with the "first"
			{
				bool isAlreadyConnected = false;
				for (int z = 0; z < first->adjList.size(); z++)
				{
					if(first->adjList[z]->name == SCC[i][k]){
						isAlreadyConnected = true;
						break;
					}
				}
				//make a connection beteen the two harbors
				if(!isAlreadyConnected){
					Harbor *second;
					try{
			         second = &harbors[binarySearch(harbors.begin(),SCC[i][k],0,harbors.size()-1)];
			         first->adjList.push_back(second);
					 second->adjList.push_back(first);
					}catch(...) {}
				}

			}
		}
	}

}

template<class Iterator>
void quickSort(Iterator arr, int l, int h)
{
    stack<int> stack;
  
    stack.push(l);
    stack.push(h);
 
        while ( !stack.empty() )
    {
    
        h = stack.top();stack.pop();
        l = stack.top();stack.pop();
 
                        Harbor &x = arr[h];
                        int i = (l - 1);
 
                        for (int j = l; j <= h- 1; j++)
                        {
                                if (arr[j] <= x)
                                {
                                        i++;
                                        swap(arr[i], arr[j]);
                                }
                        }
                        swap(arr[i + 1], arr[h]);
                        int p = i + 1;
 
        if ( p-1 > l )
        {
            stack.push(l);
            stack.push(p - 1);
        }
 
        if ( p+1 < h )
        {
            stack.push(p + 1);
            stack.push(h);
        }
    }
}
template<class Iterator>
int binarySearch(Iterator A,const char nameKey, int imin, int imax)
                {
                  while (imin < imax)
                        {
                          int imid = imin + (imax-imin)/2;
     
                          if (A[imid] < nameKey)
                                imin = imid + 1;
                          else if(A[imid] > nameKey)
                                imax = imid-1;
                          else return imid;
                        }
           if(A[imin] == nameKey){
			   return imin;
		   }
		   return -1;
                }
void unvisiteTheHarbors(){
	for (int i = 0; i < harbors.size(); i++)
	{
		isDiscovered[harbors[i].x][harbors[i].y] = false;
	}
}
};

int main(){
	//istream &in = cin; 
	ifstream in("input.txt");
	int X,Y,startX,startY,rescueX,rescueY;
	in>>X>>Y>>startX>>startY>>rescueX>>rescueY>>ws;
	char **map = new char*[X];
	for (int i = 0; i < X; i++)
	{    
		map[i] = new char[Y];
		in.getline(map[i],Y+1);
	}
	int N;
	in>>N>>ws;
	char **harborsConnections = new char*[N];
	for (int i = 0; i < N; i++)
	{   
		harborsConnections[i] = new char[2];
		in>>harborsConnections[i][0]>>ws>>harborsConnections[i][1]>>ws;
	}
	Castaway c;
	cout<<c.run(map,harborsConnections,N,X,Y,startX,startY,rescueX,rescueY)<<endl;
return 0;
}
