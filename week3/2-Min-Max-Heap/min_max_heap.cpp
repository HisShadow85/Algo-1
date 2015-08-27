#include<iostream>
#include<stack>
//#include<fstream>
using namespace std;


bool isMinMaxHeap(int *tree,unsigned N){
     unsigned nodeIndex = 1;
         unsigned nodesInLevel = 1;
         unsigned maxIndexOfLevel;
                 for (int level = 1; nodeIndex < N; level++)
                 {   
                         nodesInLevel<<=1;
                         if(nodesInLevel+nodeIndex > N) maxIndexOfLevel = N;
                         else maxIndexOfLevel = nodesInLevel+nodeIndex;
                         if(!(level%2)){
                                 for (; nodeIndex < maxIndexOfLevel ;nodeIndex++)
                                 {
                                         unsigned parent = (nodeIndex-1)/2;
                                         if(tree[nodeIndex++] > tree[parent]) return false;
                                         if(nodeIndex < maxIndexOfLevel && tree[nodeIndex]> tree[parent]) return false;
                                 }
                         }else{
                                 for (; nodeIndex < maxIndexOfLevel ;nodeIndex++)
                                 {
                                         unsigned parent = (nodeIndex-1)/2;
                                         if(tree[nodeIndex++] < tree[parent]) return false;
                                         if(nodeIndex < maxIndexOfLevel && tree[nodeIndex] < tree[parent]) return false;
                                 }
             }
                 }
                 return true;
}

int main(){
        //ifstream in("input.txt");
        int N;
        cin>>N;
        int *tree = new int[N];
        for (int i = 0; i < N; i++)
        {
                cin>>tree[i];
        }

        cout<<(isMinMaxHeap(tree,N)?"YES":"NO")<<endl;
        return 0;
}
