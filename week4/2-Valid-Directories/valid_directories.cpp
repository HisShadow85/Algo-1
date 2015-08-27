#include<iostream>
#include<vector>
//#include<fstream>
using namespace std;
//fake task
class ValidDirectories{
      vector<bool> onPath;
          vector<bool> isVisited;
          bool **map;
public:
        bool check(bool **map_,int count){

                isVisited.resize(count,false);
                onPath.resize(count,false);
                map = map_;
                for (int i = 0; i < count; i++){
                           if(!isVisited[i]){
                                   if(!DFS(i)) return false;
                           }
                }
                return true;
        }

        bool DFS(unsigned short v){
                  onPath[v] = true;
                  isVisited[v] = true;
                  for (int i = 0; i < isVisited.size(); i++)
                  {      if(map[v][i]){
                                                         if(onPath[i]) return false;
                                                         if(!isVisited[i])     
                                                                  if(!DFS(i)) return false;        
                                           }
                  }
                                  onPath[v]=false;
                  return true;
        }
};

int main(){
        //ifstream in("input.txt");
        istream &in = cin;
        int N,edge;
        bool **map;
        ios_base::sync_with_stdio(false);
        in>>N;
        map = new bool*[N];
        for (unsigned short i = 0; i < N; i++)
        {    
                map[i] = new bool[N];
            fill_n(map[i],N,false);
                for (int j = 0; j < N; j++)
                {
                        in>>edge;
                        if(edge==1)map[i][j] = true;
                }
        }
        ValidDirectories vd;
    cout<<boolalpha<<vd.check(map,N)<<endl;
        delete[] map;
        return 0;
}
