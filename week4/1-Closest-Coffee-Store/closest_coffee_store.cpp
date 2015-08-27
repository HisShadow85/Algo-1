#include<iostream>
#include<vector>
//#include<fstream>
#include<queue>
//#include<stack>
//#include<string>
using namespace std;

class ClosestCoffeeStore {
public:

  // Finds the closest coffee store to a point.
  static short closestCoffeeStore(bool** graph, bool* isCoffeStore, short size, short startingPoint) {
         vector<bool> isVisited;
                 vector<short> path;
         isVisited.resize(size,false);
                 path.resize(size);
                 for (short i = 0; i < path.size(); i++)
                 {
                         path[i] = i;
                 }
                 queue<short> q;
                 q.push(startingPoint);
                 isVisited[startingPoint] = true;
                 short curr = startingPoint;
                 if(!isCoffeStore[startingPoint]){
                         while (!q.empty())
                         {
                                 curr = q.front(); q.pop();
                                 for (short i = 0; i < size; i++)
                                 {
                                        if(graph[curr][i] && !isVisited[i]){
                                                path[i]=curr;
                                                if(isCoffeStore[i]){
                                                        curr = i;
                                                        goto end;
                                                   }
                                                isVisited[i] = true;
                                                q.push(i);
                                        }
                                 }
                         }
                 }else goto end;
                 return -1;
         end: ;
                 isVisited.clear();
                 delete[] graph; //optional
                 delete isCoffeStore; //optional
                 //string result;
                 //stack<int> stack;
                 short count = 0,endPoint = curr;
                 while (path[curr] != curr)
                 {
                         //stack.push(curr);
                         curr = path[curr];
                         count++;
                 }
                 return count;
                 /*
                 if(count == 0 ) return string("0");
                 char buff[10000];
                 result.append(itoa(count,buff,10));
                 result.append(" Because the nearest coffee store to `");
                 result.append(itoa(startingPoint,buff,10));
                 result.append("'  is `");
                 result.append(itoa(endPoint,buff,10));
                 result.append("' and the path to it is `");
                  result.append(itoa(startingPoint,buff,10));
                 while(!stack.empty())
                 {
                          result.append(" -> ");
                          result.append(itoa(stack.top(),buff,10));
                          stack.pop();                 
                 }
                //result.append(itoa(stack.top(),buff,10));
                result.append("'.");
                return result;
                */
  }

};

int main(){
        //ifstream in("input.txt");
        istream &in = cin;
        short N;
        ios_base::sync_with_stdio(false);
        in>>N;
        bool *properties = new bool[N];
        fill_n(properties,N,false);
        bool **matrix = new bool*[N];
        for (int i = 0; i < N; i++)
        {   
                short adjancent;
                matrix[i] = new bool[N];
                fill_n(matrix[i],N,false);
                for (int j= 0; j < N; j++)
                {
                        in>>adjancent;
                        if(adjancent) matrix[i][j] = true;
                }
        }
        short start;
        in>>start;
        for (int i = 0; i < N; i++)
        {
                int propertie;
                in>>propertie;
                if(propertie) properties[i] = true;
        }
        
        cout<<ClosestCoffeeStore::closestCoffeeStore(matrix,properties,N,start)<<endl;
        return 0;
        
}