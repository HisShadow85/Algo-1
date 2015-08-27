#include<iostream>
#include<vector>
#include<string>
using namespace std;

class RMQ {
        vector<int> bit;
        int bound;
        int maxIndex;
public:

        RMQ(vector<int> &input){
                if(!input.size()) throw "BIT constructor \"Empty input\"\n"; 
                maxIndex = input.size();
                bound = 1;
                while (bound < input.size() && bound < 2147483648){bound *= 2;};
                int bitSize = (bound*2)-1;
                bound-=2; 
                bit.resize(bitSize,0);
                for (int i =bound+1 ,j=0; j < (int)input.size(); i++,j++)
                {
                        bit[i]=input[j];
                }
                for (int i = bound,leftChild; i >= 0; i--)
                {
                        leftChild = (i*2)+1; 
                        bit[i] = bit[leftChild] < bit[leftChild+1] ? bit[leftChild] : bit[leftChild+1];
                }
        }
  void set(int index, int newValue){
                if(index < 0 || index >= maxIndex) throw "No such element\n";
                index+=bound+1;
                bit[index] = newValue;
                for (int parent = (index-1)/2; index ; index = parent,parent = (index-1)/2)
                {
                        bit[parent] = bit[parent*2+1] < bit[parent*2+2]? bit[parent*2+1] : bit[parent*2+2];
                }
        }
  int min(int start, int end){        
                if(start < 0 || start >= maxIndex) throw "starting argument is out of range\n";
                if(end < 0 || end >= maxIndex) throw "ending argument is out of range\n";
                if(start > end) throw "ending argument can not be less than starting one\n";
                start +=bound+1;
                end +=bound+1;
                int leftMin = start,rightMin = end;

                while(start<end){
                        if( ( ( (start-1)/2 )*2 + 2 ) == start)
                          {
                                  start++;
                          }
                    start        = (start-1)/2; 
                          

                        if( ( ( (end-1)/2 )*2 + 1 ) == end)
               {
                                        end--;                                
                           }
                        end = (end-1)/2; 

                        if(start<=end){
             leftMin = bit[leftMin] > bit[start] ? start : leftMin;
                         rightMin = bit[rightMin] > bit[end] ? end : rightMin;
                        }
                }

                return bit[leftMin] < bit[rightMin] ? bit[leftMin] : bit[rightMin] ;
        }
};


int main(){
        istream &in = cin;
        ostream &out = cout;
        vector<int> input;
        int N,K;
        int number;
    in>>ws>>N>>ws>>K;
        if(N < 0 || K < 0 || N > 1000000 || K > 100000){
                out<<"K or/and N are out of  limits\n";
                return -1;
        }

        for (int i = 0; i < N; i++)
        {
                in>>ws>>number;
                input.push_back(number);
        }

        RMQ rmq(input);

        int max;
        string command;
                try{
        for (int i = 0; i < K; i++)
        {
                in>>ws>>command;
                if(command == "min"){
                        in>>ws>>number>>ws>>max;
                        out<<rmq.min(number,max)<<endl;
                }
                else if(command == "set"){
                        in>>ws>>number>>ws>>max;
                        rmq.set(number,max);
                }
                else{
            out<<"unknown command\n";
                        return -1;
                }
        }
                }catch(const char *e){
                        out<<e;
                        return -1;
                }
        return 0;
}
