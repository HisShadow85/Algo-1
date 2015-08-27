#include<iostream>
#include<vector>
//#include<fstream>
using namespace std;

class Median {
            static bool compareMin(int &parent, int &child){return parent > child;}
                static bool compareMax(int &parent, int &child){return parent < child;}
        class Heap{
        vector<int> heap;
        bool (*func)(int&,int&);
        public: 
        Heap(bool (*func_)(int&,int&)):func(func_){}
        template<class Iterator>
        void siftDown(Iterator a, int start , int end){
          int toSwap = start;
          int child;
          while ( (child = start*2+1) <= end ){
                 if(func(a[start],a[child]))toSwap = child;
                 if((child +1 <= end) &&  func( a[toSwap] , a[child+1] ) ) toSwap = child+1;
                 if(toSwap != start){
                         swap(a[start],a[toSwap]);
                         start = toSwap;
                 }
                 else return;
          }
}
        template<class Iterator>
        void siftUp(Iterator a, int start , int end){   
              while(end>start){
                          int parent = (end-1)/2;
                          if( func(a[parent],a[end]) ){
                                  swap(a[parent],a[end]);
                                  end = parent;
                          }
                          else return;
                  }
}       
        int size(){return heap.size();}
        int getTop(){return heap[0];}
        int getTopAndReplace(int newValue){
                int result = heap[0];
                heap[0] = newValue;
                siftDown(heap.begin(),0,heap.size()-1);
                return result;
        }       
        void insert(int value){
                heap.push_back(value);
                siftUp(heap.begin(),0,heap.size()-1);
        }
                void removeTop(){
                heap[0] = heap[heap.size()-1];
                siftDown(heap.begin(),0,heap.size()-1);
                heap.pop_back();
        }
        };
        Heap minHeap;
        Heap maxHeap;
public:
        Median():minHeap(compareMin),maxHeap(compareMax){}
        int insert(int number){
          Heap *toPut, *other;
          if(minHeap.size()){
                   if(number > minHeap.getTop()) { toPut = &minHeap ; other = &maxHeap;}
                   else { toPut = &maxHeap ; other = &minHeap ; }
                   switch (toPut->size() - other->size())
                   {
                   case 0:  toPut->insert(number); return toPut->getTop();
                   case -1: toPut->insert(number); return minHeap.getTop();
                   case 1:  if(number<minHeap.getTop() && number > maxHeap.getTop()){
                                        other->insert(number);
                            }else{
                                        other->insert(toPut->getTopAndReplace(number));
                            }
                            return minHeap.getTop();        
                   }
           }
           else{
                   minHeap.insert(number); return number;
           }
      }
};

int main(){
            //ifstream in("input.txt");
        Median median;
        int number,N;
        cin>>N;
                for (int i = 0; i < N; i++)
                {
                        cin>>number;
                        cout<<median.insert(number)<<endl;
                 }

                return 0;
}
