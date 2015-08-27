#include<iostream>
#include <vector>
#include<string>

using namespace std;

class KMin {
public:

// Finds the k-th minimum element in an unsorted collection.
template<class T>
T kthMinimum(vector<T> numbers, int k) {
          if(k-1 < 1 || k > numbers.size()) throw "There is no element at such position\n";
          heapsort<T>(numbers,numbers.size());
          return numbers[k-1]; //exclude the existence of zero element
  }

template<class T>
void heapsort(vector<T> &a,int count){
    //input: an unordered array a of length count
 
    //Build the heap in array a so that largest value is at the root
    heapify(a, count);

    //The following loop maintains the invariants that a[0:end] is a heap and every element
    // beyond end is greater than everything before it (so a[end:count] is in sorted order)
    int end = count - 1;
    while (end > 0){
        //a[0] is the root and largest value. The swap moves it in front of the sorted elements.
        swap(a[end], a[0]);
        //the heap size is reduced by one
        end = end - 1 ;
        //the swap ruined the heap property, so restore it
        siftDown(a, 0, end);
                }
}

//Put elements of 'a' in heap order, in-place
template<class T>
void heapify(vector<T> &a,int count){
    //start is assigned the index in 'a' of the last parent node
    //the last element in a 0-based array is at index count-1; find the parent of that element
    int start = (count - 2) / 2;
    
    while (start >= 0){
       // sift down the node at index 'start' to the proper place such that all nodes below
        // the start index are in heap order
        siftDown(a, start, count - 1);
        //go to the next parent node
        start = start - 1;
        }
        //after sifting down the root all nodes/elements are in heap order
}

//Repair the heap whose root element is at index 'start', assuming the heaps rooted at its children are valid
template<class T>
void siftDown(vector<T> &a,int start,int end){
    int root = start;

    while ((root * 2 + 1) <= end){      //While the root has at least one child
        int child = root * 2 + 1 ;     // Left child
        int toSwap = root;            //Keeps track of child to swap with

        if (a[toSwap] < a[child])
            toSwap = child ;
        //If there is a right child and that child is greater
        if ( (child+1 <= end) && (a[toSwap] < a[child+1]) )
            toSwap = child + 1;
        if (toSwap == root)
            //The root holds the largest element. Since we assume the heaps rooted at the
            // children are valid, this means that we are done.
            return;
        else
            swap(a[root], a[toSwap]);
            root = toSwap ;           // repeat to continue sifting down the child now
                        }
  }
};

int main(){
        int N , K , number;
        cin>>N>>K;
        vector<int> input;
        //int *input = new int[N];
        for(int i = 0 ; i < N ; i++)
        {
                cin>>number;
                input.push_back(number);
        }
        KMin kmin;
        cout<<kmin.kthMinimum(input,K)<<endl;        
        return 0 ;
}

