#include<iostream>
using namespace std;

template<class T> class Queue;
template<class T> class Stack;

template<class T>
class Node{
	friend class Queue<T>;
	friend class Stack<T>;
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

template<class T>
class Stack:public Queue<T>{
	
public:
	Stack(){}
	Stack(Queue &init):Queue(Queue &init){}

	  // Adds value to the end of the Stack.
	  // Complexity: O(1)
	  //void push(T value); inherited

	  // Returns value from the end of the Stack and removes it.
	  // Complexity: O(n)
	  T pop();//throw(exception); //override

	  // Returns value from the end of the Stack without removing it.
	  // Complexity: O(n) 
	  //since I'm using Queue the Complexity will be O(1), because the tail pointer holds the top data
	  T peek();//throw(exception); //override

	  // Returns the number of elements in the Stack.
	  // Complexity: O(1)
	  //size() //inherited
};

template<class T>
T Stack<T>::pop(){//throw(exception){
	try{
		 T result = peek();
		 if(size_ > 1){
		 Node<T> *currNode = head;
		 for (int i = 2; i < size_; i++)
		 {
			 currNode=currNode->next;
		 }
		 delete tail;
		 tail = currNode;
		 }
		 else{
			 delete head;
			 head = tail =NULL;
		 }
		 size_--;
		 
		 return result;
	}
	catch(exception e){
          throw e;
	}
}

template<class T>
T Stack<T>::peek(){//throw(exception){
    if(size_){
		T result = tail->data;
		return result;
	}
	else{
		throw exception("Queue is Empty\n");
	}
}


int main(){
	int randValue;
    Stack<int> myStack;
	cout<<"MyStack content: ";
	for (int i = 0; i < 20; i++)
	{
		randValue = rand()%99;
		myStack.push(randValue);
		cout<<randValue<<" ";
	}

	try{
	cout<<endl<<"Showing MyStack content using: \npop():\tpeek(): ";
	for (int i = myStack.size(); i ; i--)
	{
		cout<<endl<<myStack.pop()<<"\t";
	    cout<<myStack.peek();
	}
	cout<<endl;
	}catch(exception){
         cout<<"MyStack is empty!"<<endl;
	}
	

	system("PAUSE");
	return 0;
}
