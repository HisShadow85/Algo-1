#include<iostream>
#include<vector>
#include<algorithm>
#include<stack>
//#include<fstream>
using namespace std;

class PhoneNumbers{
        class PhoneNumber{
        public:
                unsigned short number;
                bool alreadyCalled;
                vector<PhoneNumber*> *adjList;
                PhoneNumber(unsigned short number_):number(number_),alreadyCalled(false){}
                PhoneNumber():alreadyCalled(false){adjList = new vector<PhoneNumber*>();}
                ~PhoneNumber(){delete adjList;}
        };
public:
        static short run(istream &in,ostream &out){
                unsigned short N;
                in>>N;
                //PhoneNumber *phoneList = new PhoneNumber[N];
                //PhoneNumber **phoneListPointer = new PhoneNumber*[N];
                vector<PhoneNumber> phoneList;
                vector<PhoneNumber*> phoneListPointer;
                phoneListPointer.resize(N);
                phoneList.resize(N);
                for (unsigned short i = 0; i < N; i++)
                {
                        in>>phoneList[i].number;
                        phoneListPointer[i] = &phoneList[i]; 
                }
                struct Compare
                {
                    bool operator()(PhoneNumber *n1,PhoneNumber *n2)
                        {
                                return ((*n1).number < (*n2).number);
                        }
                };
                sort(phoneListPointer.begin(),phoneListPointer.end(),Compare());
                
                for (unsigned short i = 0; i < phoneList.size(); i++)
                {
                        unsigned short number;
                        short index;
                        in>>N;
                        for (int j = 0; j < N; j++)
                        {
                        in>>number;
                                                //check if this number already exists
                        index = binarySearch(phoneList[i].adjList->begin(),number,0,phoneList[i].adjList->size()-1);
                        if(index != -1) continue; // if so we have no need to put it again into the adjacency list
                                                //check if this number has owner from the main pnone list
                        index = binarySearch(phoneListPointer.begin(),number,0,phoneListPointer.size()-1);
                        if(index == -1) continue;//if it hasn't we can't make connection
                        phoneList[i].adjList->push_back(phoneListPointer[index]);//else we put the owner of the number to the adjacency List
                        sort(phoneList[i].adjList->begin(),phoneList[i].adjList->end(),Compare());//and sort it avcorse for the binary search
                        //in case that It is not guaranteed it the input that if student i has the number of student j, student j also has the number of student i
                        /*int secondIndex = binarySearch(phoneList[index].adjList->begin(),number,0,phoneList[index].adjList->size()-1);
                        if(secondIndex != -1) continue;
                        secondIndex = binarySearch(phoneListPointer.begin(),number,0,phoneListPointer.size()-1);
                        if(secondIndex == -1) continue;
                        phoneList[index].adjList->push_back(phoneListPointer[secondIndex]);
                        sort(phoneList[index].adjList->begin(),phoneList[index].adjList->end(),Compare());
                        */
                        }
                        
                }

                phoneListPointer.clear();
                unsigned short calls = 0;
                stack<PhoneNumber*> theStack;
                for (unsigned short i = 0; i <phoneList.size(); i++)
                {
                        if(phoneList[i].alreadyCalled)continue;
                        calls++;
                        theStack.push(&phoneList[i]);
                        phoneList[i].alreadyCalled = true;
                        while (!theStack.empty())
                        {
                                PhoneNumber* curr = theStack.top(); theStack.pop();
                                for (unsigned short i = 0; i < curr->adjList->size(); i++)
                                {
                                        if((*curr->adjList)[i]->alreadyCalled) continue;
                                        (*curr->adjList)[i]->alreadyCalled = true;
                                        theStack.push((*curr->adjList)[i]);
                                }
                        }

                }
                return calls;
        }

        static short binarySearch(vector<PhoneNumber*>::iterator phoneListPointer,unsigned short key, int l, int h){

                while (l<=h)
                {
                        int mid = l + (h-l)/2;
                        if(phoneListPointer[mid]->number < key)
                                l = mid + 1;
                        else if(phoneListPointer[mid]->number > key)
                                h = mid -1;
                        else return mid;
                }
                return -1;
        }

};


int main(){
        istream &in = cin;
        //ifstream in("input.txt");
    ios_base::sync_with_stdio(false);
        cout<<PhoneNumbers::run(in,cout)<<endl;
    return 0;
}
