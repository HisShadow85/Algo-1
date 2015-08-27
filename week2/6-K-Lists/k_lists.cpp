#include<iostream>
#include <vector>

using namespace std;
template<class T> class Heap;

template<class T>
class Node {
public:
  T value;
  Node* next;

  bool operator>(const Node<T> &other){ return this->value > other.value;}
  Node<T> &operator=(const Node<T> &other){ value = other.value;next = other.next;return *this;}
};




template<class T>
class KLists {
        vector<Node<T>> heap;
public:

  // Merge K sorted lists.
  Node<T> *merge(vector<Node<T>> lists) {
          
          Node<T> *HeadResult = NULL;;
          Node<T> **curr = &HeadResult;
          for(auto var : lists){ insert(var);}

          for (;!heap.empty(); )
          {
                  *curr = new Node<T>();
                  (*curr)->next = NULL;
                  (*curr)->value = getMin().value;
                  if(getMin().next == NULL) removeMin();
                  else{
                          getMin() = *getMin().next;
                          siftDown(heap.begin(),0,heap.size()-1);
                  }
                  curr = &((*curr)->next);

          }
         
          return HeadResult;
  }

  void insert(Node<T> &value){
                heap.push_back(value);
                siftUp(heap.begin(),0,heap.size()-1);                
        }

        template<typename Iterator>
        void siftUp(Iterator a,int start,int end)
                {
                         // input:  start represents the limit of how far up the heap to sift.
                         // end is the node to sift up.
                         int child = end; 
                         while (child > start)
                         {
                                 int parent = (child-1) / 2 ;
                                 if (a[parent] > a[child] )//then out of max-heap order
                                 {
                                         swap(a[parent], a[child]);
                                         child = parent; //repeat to continue sifting up the parent now
                                 }
                                 else
                                         return;
                         }
        }
        template<typename Iterator>
    void siftDown(Iterator a,int start,int end){
                int root = start;

                while ((root * 2 + 1) <= end){    //(While the root has at least one child)
                        int child = root * 2 + 1 ;     // (Left child)
                        int toSwap = root;                //(Keeps track of child to swap with)

                        if (a[toSwap] > a[child])
                                toSwap = child ;
                        //(If there is a right child and that child is greater)
                        if ( (child+1 <= end) && (a[toSwap] > a[child+1]) )
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
        Node<T> &getMin(){ return heap[0];}
        void removeMin(){
                heap[0] = heap[heap.size()-1];
                heap.pop_back();
                siftDown(heap.begin(),0,heap.size()-1);
        }
};

template<class Iterator ,class T>
Node<T> *makeList(Iterator a, int count)
{
        if(count){
        Node<T> *curr = NULL;
        Node<T> head;
        curr = &head;
        for(int i = 0; i < count; i++)
        {
                curr->next = new Node<T>();
                curr = curr->next;
                curr->value = a[i];
                curr->next = NULL;
        }
        return head.next;
        }else return NULL;

}

int main(){

        int N;
        cin>>N;
        vector<int> consoleInput;
        vector<Node<int>> input;
        for (int i = 0; i < N; i++,consoleInput.clear())
        {
                int number;
                cin>>number;
                for (; number != -1; cin>>number)
                {
          consoleInput.push_back(number);
                }
                input.push_back(*makeList<vector<int>::iterator,int>(consoleInput.begin(),consoleInput.size()));
        }


        KLists<int> klists;
        for (Node<int> *curr = klists.merge(input);curr; curr=curr->next)
        {
                cout<<curr->value<<" ";
        }
        cout<<endl;
        return 0;
}
