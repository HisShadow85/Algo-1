#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
//#include<fstream>
#include<stack>
#include<iterator>
using namespace std;

class Compiler{
        class Program{
        public:
                string name;
                bool visited;
                bool compiled;
                vector<Program*> adjacencyList;
                //Program(const string &name_):name(NULL),onStack(false){}
                Program():compiled(false),visited(false){}
                bool operator<(const Program &other){return name < other.name;}
                bool operator==(const Program &other){return name == other.name;}
        };
        vector<Program> programsSet;
        //unsigned  sizeOfSet;
        //vector<Program> programsSet;
        Program *programToCompile; 
        
public:
        Compiler(istream &in, ostream &out){
       int N;
           in>>N;
           //sizeOfSet = N;

           class Node{
           public:
                   string name;
                   unsigned idex;
                   Node(const string &name_, unsigned idex_):name(name_),idex(idex_){}
                   bool operator<(const Node &other){ return name < other.name;}
                   bool operator<(const string &other){ return name < other;}
                   bool operator>(const string &other){ return name > other;}
           };
           vector<Node> aux;
           programsSet.resize(N,Program());
           for (int i = 0; i < N; i++)
           {
                   in>>programsSet[i].name;
                   aux.push_back(Node(programsSet[i].name,i));
           }
           //sorting tha aux array for faster finding the coresponding program
           heapsort(aux.begin(),aux.size());//sort(aux.begin(),aux.end());
           //let's extract the main compiling program
           string programNameToCompile;
           in>>programNameToCompile;
           int index = binary_search(aux.begin(),programNameToCompile,0,aux.size()-1);
           if(index != -1) { programToCompile = &programsSet[aux[index].idex]; }
           else throw "Invalid name for main compiling program\n";
           //noe le't set the adjacency list
           for (int i = 0; i < programsSet.size(); i++)
           {
                   in>>N;
                   string adj;
                   for (int j = 0; j < N; j++)
                   {
                           in>>adj;
                           index = binary_search(aux.begin(),adj,0,aux.size()-1);
                   if(index != -1) { programsSet[i].adjacencyList.push_back(&programsSet[aux[index].idex]);}
                           else throw "Unknow frogram name occurs\n";
                   }
           }


          
        }
vector<string> build(){
     vector<string> build;
     stack<Program*> stack;

         stack.push(programToCompile);
         programToCompile->visited = true;
         while (!stack.empty())
         {
                 Program *curr = stack.top();

                 for (int i = 0; i < curr->adjacencyList.size(); i++)
                 {
                         if(curr->adjacencyList[i]->visited){//if the adjacency program is already visited
                                 if(curr->adjacencyList[i]->compiled) continue; //if compiled everything is ok
                                 else { build.clear(); build.push_back("BUILD ERROR"); return build; } //else the is a cycle
                       }
                         else{//if is it not visited then we put it in the stack and proceeds with it in the next main loop row
                                 curr->adjacencyList[i]->visited = true; //kiping the current praogram into the stack
                                 stack.push(curr->adjacencyList[i]);
                                 goto continue_to_next;
                         }
                 }
                 //the program with has no more unvisited and uncompiled programs on with it depends is being build
                 curr->compiled = true; // set as compiled
                 build.push_back(curr->name); //load the name into the result vector
                 stack.pop(); // remove it from the stack

                 continue_to_next:;
         }

     return build;

        }
        template<class Iterator>
        int binary_search(Iterator a,string key,int min , int max){
                int mid;
                while(min < max){
                        mid = min + (max - min) / 2;
                        if(a[mid] > key) max = mid-1;
                        else if(a[mid] < key) min = mid+1;
                        else return mid;
        }
                if(!(a[min] < key) && !(a[min] > key) ) return min;
                return -1;
        }

        template<typename Iterator>
    static void heapsort(Iterator a,int count){
                //input: an unordered array a of length count
 
                //(Build the heap in array a so that largest value is at the root)
                heapify(a, count);

                //(The following loop maintains the invariants that a[0:end] is a heap and every element
                // beyond end is greater than everything before it (so a[end:count] is in sorted order))
                int end = count - 1;
                while (end > 0){
                        //(a[0] is the root and largest value. The swap moves it in front of the sorted elements.)
                        swap(a[end], a[0]);
                        //(the heap size is reduced by one)
                        end = end - 1 ;
                        //(the swap ruined the heap property, so restore it)
                        siftDown(a, 0, end);
                        }
        }

        //(Put elements of 'a' in heap order, in-place)
    template<typename Iterator> 
    static void heapify(Iterator a,int count){
                //(start is assigned the index in 'a' of the last parent node)
                //(the last element in a 0-based array is at index count-1; find the parent of that element)
                int start = (count - 2) / 2;
    
                while (start >= 0){
                   // (sift down the node at index 'start' to the proper place such that all nodes below
                        // the start index are in heap order)
                        siftDown(a, start, count - 1);
                        //(go to the next parent node)
                        start = start - 1;
                }
                //(after sifting down the root all nodes/elements are in heap order)
        }
        template<typename Iterator>
    static void siftDown(Iterator a,int start,int end){
                int root = start;

                while ((root * 2 + 1) <= end){    //(While the root has at least one child)
                        int child = root * 2 + 1 ;     // (Left child)
                        int toSwap = root;                //(Keeps track of child to swap with)

                        if (a[toSwap] < a[child])
                                toSwap = child ;
                        //(If there is a right child and that child is greater)
                        if ( (child+1 <= end) && (a[toSwap] < a[child+1]) )
                                toSwap = child + 1;
                        if (toSwap == root)
                                //(The root holds the largest element. Since we assume the heaps rooted at the
                                // children are valid, this means that we are done.)
                                return;
                        else
                                swap(a[root], a[toSwap]);
                                root = toSwap ;           // (repeat to continue sifting down the child now)
                                }
          }
};

int main(){
        //ifstream in("input.txt");
        istream &in = cin;
        ios_base::sync_with_stdio(false);
        Compiler cmp(in,cout);
        vector<string> result = cmp.build();
        copy(result.begin(),result.end(),std::ostream_iterator<string>(cout," "));
        cout<<endl;
        return 0;
}