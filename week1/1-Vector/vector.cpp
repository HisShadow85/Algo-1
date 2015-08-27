#include<iostream>
using namespace std;

template<class T>
class Vector {
	 T *data;
	 int size_ , capacity_ ;
	 //удвоява големината на масива контейнер като оставя осбодно мястото index
	 void expandVector(int index);
	 //раздяля масива при посочения индекс отмествайки всички елементи с едно надясно от index или
	 //ако е подаден аргумент друг масив като аргумет копира всички до index нормално а всички след 
	 //index с една позиция по нядясно, така елемнта на index е готов за запълване от нова стойност
	 void divideArray(int index, T *other = NULL);
public:
	  Vector(int capacity = 10);
	  Vector(Vector<T> &init);
  // Adds value at a specific index in the Vector.
  // Complexity: O(n)
 void insert(int index,T &value);

  // Adds value to the end of the Vector.
  // Complexity: O(1)
  void add(T &value);

  // Returns value at a specific index in the Vector
  // Complexity: O(1)
  T &get(int index);

  // Removes element at the specific index
  // Complexity: O(n)
  T remove(int index);

  // Removes element at the last index
  // Complexity: O(1)
  T pop();

  // Returns the number of elements in the Vector.
  // Complexity: O(1)
  int size();

  // Returns the total capacity of the Vector.
  // Complexity: O(1)
  int capacity();

  T &operator[](int index){
	  return data[index];
  }

};

template<class T>
Vector<T>::Vector(int capacity ):size_(0),capacity_(capacity){
	data = new T[capacity_];
}

template<class T>
Vector<T>::Vector(Vector<T> &init ):size_(init.size_),capacity_(init.capacity_){
	data = new T[capacity_];
	for (int i = 0; i < size_; i++)
	{
		data[i] = init.data[i];
	}
}

template<class T>
void Vector<T>::insert(int index,T &value){//throw(std::out_of_range){
	 if(index < 0 || index > size_) 
		 throw std::out_of_range("The index is out of bounds\n");
	 if(size_ +1 >= capacity_){
         expandVector(index);
	 }
	 else{
		 divideArray(index);
	 }
	 data[index] = value;
}

template<class T>
void Vector<T>::expandVector(int index){
	//създаваме нов динамичен масив за вектора с двойно по-голям капацитет
	T *tmpData = new T[capacity_*=2];
	//копираме стария масив в новия , като след index е отместено копието с едно на дясно
	divideArray(index,tmpData);
	delete data;
	data = tmpData;
};

template<class T>
void Vector<T>::divideArray(int index, T *other){
	if(other){
		//копираме данните от стaрiя масив в новия до зададения индекс като аргумент(без него)
		for (int i = 0; i < index; i++)
		{
			other[i] = data[i];
		}		
		//копираме стария масив в новия с едно отместване на дясно
		for (int i = index; i < size_; i++)
		{
			other[i+1] = data[i];
		}
	}
	else{
		for (int i = size_; i > index; i--)
		{
			data[i] = data[i-1];
		}
	}
	//увеличаваме размера с единицица тук тъй като така или иначе ако се нуждаем от нова памет то ще да е
    //за да вкараме нов елемент
	size_++;
}

template<class T>
void Vector<T>::add(T &value){
	insert(size_,value);
}

template<class T>
T &Vector<T>::get(int index){//throw(std::out_of_range){
	if(index < 0 || index >= size_) 
		 throw std::out_of_range("The index is out of bounds\n");
	return data[index];
}

template<class T>
T Vector<T>::remove(int index){//throw(std::out_of_range){
	if(index < 0 || index >= size_) 
		 throw std::out_of_range("The index is out of bounds\n");
	T result = data[index];
	for (int i = index+1; i < size_; i++)
	{
		data[i-1] = data[i];
	}
	size_--;
	return result;
}

template<class T>
T Vector<T>::pop(){
	return remove(size_-1);
}

template<class T>
int Vector<T>::size(){
	return size_;
}

template<class T>
int Vector<T>::capacity(){
	return capacity_;
}


int main(){
	int randValue;
    Vector<int> myvector;
	cout<<"My vector content: ";
	for (int i = 0; i < 20; i++)
	{
		randValue = rand()%99;
		myvector.add(randValue);
		cout<<myvector.get(i)<<" ";
	}
	cout<<endl<<"Inserting elements in 0,3,6,9,12,15,18 positions \nwhith values:";
	for (int i = 0; i < 20; i+=3)
	{
		randValue = rand()%99;
		myvector.insert(i,randValue);
		cout<<myvector.get(i)<<" ";
	}
	cout<<endl<<"My vector content: ";
	for (int i = 0; i < 20; i++)
	{	
		cout<<myvector.get(i)<<" ";
	}
	cout<<endl<<"Removing the elements in 0,3,6,9,12,15,18 positions!\n";
	for (int i = 0; i < 20; i+=3)
	{		
		myvector.remove(i);
	}
	cout<<"Showing My vector content using pop(): ";
	for (int i = myvector.size(); i ; i--)
	{
		cout<<myvector.pop()<<" ";
	}
	system("PAUSE");
	return 0;
}
