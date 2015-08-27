#include<iostream>
#include<vector>

using namespace std;

class HeapSort{
        vector<int> heap;
        bool isHeap;
public:
        HeapSort():isHeap(true){}
        template<typename Iterator>
        static void heapsort(Iterator a,int count,bool isAlreadyHeap = false){
                //input: an unordered array a of length count
 
                //(Build the heap in array a so that largest value is at the root)
                if(!isAlreadyHeap) heapify(a, count);

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



     void insert(int value){
                heap.push_back(value);
                siftUp(heap.begin(),0,heap.size()-1);                
        }

        template<typename Iterator>
        static void siftUp(Iterator a,int start,int end)
                {
                         // input:  start represents the limit of how far up the heap to sift.
                         // end is the node to sift up.
                         int child = end; 
                         while (child > start)
                         {
                                 int parent = (child-1) / 2 ;
                                 if (a[parent] < a[child] )//then out of max-heap order
                                 {
                                         swap(a[parent], a[child]);
                                         child = parent; //repeat to continue sifting up the parent now
                                 }
                                 else
                                         return;
                         }
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

        void sort() {
    heapsort(heap.begin(),heap.size(),isHeap);
        isHeap = false;
  }
        int &operator[](int index){

                return heap[index];
        }
};

int main(){
        int N,number;
        cin>>N;
        HeapSort hs;
        for (int i = 0; i < N; i++)
        {   
                cin>>number;
                hs.insert(number);
        }
        hs.sort();
        for (int i = 0; i < N; i++)
        {
                if(i){
                        cout<<' ';
                }
                cout<<hs[i];
        }
        cout<<endl;
        return 0;

}
