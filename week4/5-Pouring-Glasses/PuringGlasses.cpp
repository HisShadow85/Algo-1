#include<iostream>
#include<vector>
#include<queue>
#include<stack>
using namespace std;

class PouringGlasses{
        class Vertex{
        public:
                short glass1;
        short glass2;
                short glass3;
                Vertex(short glass1_=0,short glass2_=0,short glass3_=0):glass1(glass1_),glass2(glass2_),glass3(glass3_){}
                Vertex(const Vertex &init):glass1(init.glass1),glass2(init.glass2),glass3(init.glass3){}
        };
        class Parent{
        public:
                short pouringGlass, pouringToGlass;
                Vertex parent;
                Parent():pouringGlass(0),pouringToGlass(0){}
                Parent(short pouringGlass_,short pouringToGlass_,Vertex parent_):pouringGlass(0),pouringToGlass(0),parent(parent_){}
        };
    
        Parent ***pathMatrix;
        vector<int> result;
public:

        PouringGlasses(short glassesCapacity[3], short wasser[3],short targetedQuantity){
                if(wasser[0] == targetedQuantity || wasser[1] == targetedQuantity || wasser[3] == targetedQuantity){
                        result.push_back(-1); return; 
                }
                //make some checks
                //allocatind memory for the 3D pathMatrix
                pathMatrix = new Parent**[glassesCapacity[0]+1];
                for (int i = 0; i < glassesCapacity[0]+1; i++)
                {
                        pathMatrix[i] = new Parent*[glassesCapacity[1]+1];
                        for (int j = 0; j < glassesCapacity[1]+1; j++)
                        {
                              pathMatrix[i][j] = new Parent[glassesCapacity[2]+1];
                        }
                }

                //set the starting vertex as discovered with negative values showing that there is no parent vertex
                pathMatrix[wasser[0]][wasser[1]][wasser[2]].pouringGlass = -1;
        pathMatrix[wasser[0]][wasser[1]][wasser[2]].pouringToGlass = -1;

                queue<Vertex> queue;
                queue.push(Vertex(wasser[0],wasser[1],wasser[2]));
                short glasses[3];
                short auxGlasses[3];
                Vertex currVertex,newVertex;
                while (!queue.empty())
                {
                        currVertex = queue.front();queue.pop();
                        glasses[0]=currVertex.glass1; glasses[1]=currVertex.glass2; glasses[2]=currVertex.glass3;
                        for (short i = 0; i < 3; i++)
                        {
                                for (short j = 0; j < 3; j++)
                                {
                                        if(i == j || !glasses[i] || glasses[j] == glassesCapacity[j]) continue;
                                        else{
                         if(glasses[i] <= glassesCapacity[j] - glasses[j]){
                                                         auxGlasses[j] = glasses[i] + glasses[j];
                                                     auxGlasses[i] = 0;
                                                 }else{
                                                         auxGlasses[j] = glassesCapacity[j];
                                                         auxGlasses[i] = glasses[i]-( glassesCapacity[j] - glasses[j]);
                                             }
                                                 auxGlasses[3-(i+j)] = glasses[3-(i+j)];
                                                 if(pathMatrix[auxGlasses[0]][auxGlasses[1]][auxGlasses[2]].pouringGlass) continue;
                                                 else{
                                                         //mark the new Vertex as visited
                                                         pathMatrix[auxGlasses[0]][auxGlasses[1]][auxGlasses[2]].pouringGlass=i+1;
                                                         pathMatrix[auxGlasses[0]][auxGlasses[1]][auxGlasses[2]].pouringToGlass = j+1;
                                                         pathMatrix[auxGlasses[0]][auxGlasses[1]][auxGlasses[2]].parent = currVertex;
                                                         //insert Vertex in queue
                                                         queue.push(Vertex(auxGlasses[0],auxGlasses[1],auxGlasses[2]));
                                                         //check if we achieve the wanted quantity
                                                         if(queue.back().glass1 == targetedQuantity  
                                                                 || queue.back().glass2 == targetedQuantity
                                                         || queue.back().glass3 == targetedQuantity){
                                                                         currVertex = queue.back();
                                                                         goto end;
                                                         }

                                                 }

                                        }
                                }
                        }
                }
                result.push_back(0); return;
        end:
                //while(!queue.empty()) queue.pop();
                //extract the path
                stack<int> stepBystep;
                unsigned long steps = 0L;
                //Parent currParent = pathMatrix[currVertex.glass1][currVertex.glass2][currVertex.glass3];
                for (short 
                        i = currVertex.glass1,
                        j = currVertex.glass2,
                        k = currVertex.glass3;
                    pathMatrix[i][j][k].pouringToGlass!=-1; steps++)
                {  
                        stepBystep.push(pathMatrix[i][j][k].pouringToGlass);
                        stepBystep.push(pathMatrix[i][j][k].pouringGlass);
                                        currVertex = pathMatrix[i][j][k].parent;
            i = currVertex.glass1,
                        j = currVertex.glass2,
                        k = currVertex.glass3; 
                }
                delete pathMatrix;
                result.push_back(steps);
                while (!stepBystep.empty())
                {
                        result.push_back(stepBystep.top());
                        stepBystep.pop();
                }
        }


        vector<int> &getResult(){
                return result;
        }

};

int main(){

        short input[2][3];
        short wantedQuantity;
        ios_base::sync_with_stdio(false);
        for (char i = 0; i < 2; i++)
        {
                for (char j = 0; j < 3; j++)
                {
                        cin>>input[i][j];
                }
        }
        cin>>wantedQuantity;
        PouringGlasses pg(input[0],input[1],wantedQuantity);
        vector<int> &result = pg.getResult();
        if(result[0] == 0) cout<<"IMPOSSIBLE"<<endl;
        else if(result[0] == -1) cout<<"0\n";
        else{
                cout<<result[0]<<endl;
                for (char i = 0, j = 1; i < result[0]; i++)
                {
                        cout<<result[j++]<<' ';
                        cout<<result[j++]<<endl;
                }
        }
        return 0;
}