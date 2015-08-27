#include<iostream>
#include<stack>
//#include<fstream>
using namespace std;


bool isBST(int *tree,unsigned N){

        unsigned maxLimit = 1,minLimit = 0;
        char bites = sizeof(unsigned)*8-1;
        while(bites--) maxLimit = (maxLimit<<1)|maxLimit;
        class AuxNode{
        public:
                unsigned index;
                unsigned currMaxLimit;
                unsigned currMinLimit;
                AuxNode(unsigned index_ = 0,unsigned currMinLimit_ = 0 ,unsigned currMaxLimit_ = 0):
                                index(index_),currMaxLimit(currMaxLimit_),currMinLimit(currMinLimit_){}
        };

        stack<AuxNode> stack;
        stack.push(AuxNode(0,minLimit,maxLimit));
        AuxNode currNode;
        while(!stack.empty()){
                currNode = stack.top();stack.pop();
                if(tree[currNode.index] >= currNode.currMinLimit && tree[currNode.index] < currNode.currMaxLimit){
                        unsigned leftChild = currNode.index*2+1;
                        if(leftChild+1 < N && tree[leftChild+1] > 0){
                                stack.push(AuxNode(leftChild+1,tree[currNode.index],currNode.currMaxLimit));
                        }
                        if(leftChild < N && tree[leftChild] > 0){
                                stack.push(AuxNode(leftChild,currNode.currMinLimit,tree[currNode.index]));
                    }
        }else return false;
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

        cout<<(isBST(tree,N)?"YES":"NO")<<endl;
        return 0;
}
