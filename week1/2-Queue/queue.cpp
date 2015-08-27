#include<iostream>
using namespace std;

template<class T> class Queue;

template<class T>
class Node{
	friend class Queue<T>;
	T data;
	Node *next;
	Node(T &newData,Node *prevNode = NULL):data(newData),next(NULL){
     if(prevNode) prevNode->next = this;
	}
};

template<class T>
class Queue {
protected:
	Node<T> *head, *tail;
	int size_;
public:
	Queue():size_(0),head(NULL),tail(NULL){}
	Queue(Queue &init);
  // Adds value to the end of the Queue.
  // Complexity: O(1)
  void push(T value);

  // Returns value from the front of the Queue and removes it.
  // Complexity: O(1)
  T pop();//throw(std::exception);

  // Returns value from the front of the Queue without removing it.
  // Complexity: O(1)
  T peek();//throw(std::exception);

  // Returns the number of elements in the Queue.
  // Complexity: O(1)
  int size()const;
};


template<class T>
Queue<T>::Queue(Queue &init){
	size_ = init.size_;
	Node<T> *cuurNode = new Node<T>(init.head->data);
	Node<T> *cuurInitNode = init.head;
	this.head = cuurNode;
	for (int i = 1; i < size_  ; i++)
	{
		Node<T> *cuurInitNode = cuurInitNode->next;
		cuurNode = new Node<T>(cuurInitNode->data,cuurInitNode);
	}
	tail = cuurNode;
}

template<class T>
void Queue<T>::push(T value){
	if(head){
		tail = new Node<T>(value,tail);
	}
	else{
        head = tail = new Node<T>(value);
	}
	size_++;
}

template<class T>
T Queue<T>::pop(){//throw(exception){
	try{
		 T result = peek();
		 Node<T> *tmp = head;
		 head = head->next;
		 size_--;
		 delete tmp;
		 return result;
	}
	catch(exception e){
          throw e;
	}
}

template<class T>
T Queue<T>::peek(){//throw(exception){
    if(size_){
		T result = head->data;
		return result;
	}
	else{
		throw exception("Queue is Empty\n");
	}
}

template<class T>
int Queue<T>::size()const{
	return size_;
}


int main(){
	int randValue;
    Queue<int> myQueue;
	cout<<"MyQueue content: ";
	for (int i = 0; i < 20; i++)
	{
		randValue = rand()%99;
		myQueue.push(randValue);
		cout<<randValue<<" ";
	}

	try{
	cout<<endl<<"Showing MyQueue content using: \npop():\tpeek(): ";
	for (int i = myQueue.size(); i ; i--)
	{
		cout<<endl<<myQueue.pop()<<"\t";
	    cout<<myQueue.peek();
	}
	cout<<endl;
	}catch(exception){
         cout<<"MyQueue is empty!"<<endl;
	}

	system("PAUSE");
	return 0;
}
