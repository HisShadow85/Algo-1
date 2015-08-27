#include<iostream>
#include<algorithm>
#include<string>
#include<vector>
#include<fstream>
using namespace std;

class PhoneBook;

class Contact{
	  friend class PhoneBook;
	  string name;
      unsigned int number;
public:
	Contact():number(0){}
	Contact(string &name_,unsigned int number_=0 ):name(name_),number(number_){}

	const string &getName()const{return name;}
	unsigned int getNumber()const{return number;}

	void setName(string &name_){name = name_;}
	void setNumber(unsigned int number_) {number=number_;}

};

class PhoneBook{
	  vector<Contact> phone;
	  int size_;
public: 
	PhoneBook():size_(0){}
	PhoneBook(PhoneBook &init);
		
	//функцията прибавя нов запис по азбучен ред иползвайки двойно търсене
    void add(string name, unsigned int number = 0);

	// Find the names of people based on their phone numbers.
    vector<string> lookupNames(vector<int> numbers);

	//търси дали има такъв телефонен номер в поредицата от номера
    int interpolationSearch(vector<Contact*> &arr,unsigned key);

    //изпозлваме го за да подредим по азбучен ред обкетите Телефонни номера
    int binarySearch(vector<Contact> &A, string & nameKey, int imin, int imax);

	//извлича обекта телефоннен номер според зададен индекс -- само за демонстрацията
	Contact &getPhoneNumber(int index);
	
	int size(){return size_;}
};

int main(){
	//ifstream in("input.txt");
	istream &in = cin;
	int N , M;
	in>>N>>M;
	PhoneBook book;
	for (int i = 0; i < N; i++)
	{
		string name;
		unsigned int number;
		in>>number>>name;
		book.add(name,number);
	}

	vector<int> numbers(M);

	for (int i = 0; i < M; i++)
	{
		in>>numbers[i];
	}

	vector<string> names = book.lookupNames(numbers);

	for (int i = 0; i < names.size(); i++)
	{
		cout<<names[i]<<endl;
	}

	return 0;
	
}

void PhoneBook::add(string name, unsigned int number){
		switch (size_)
		{
		case 0: 
			    phone.push_back(Contact(name,number));break;
		case 1:
			    if(name < phone[0].name) phone.insert(phone.begin(),Contact(name,number));
				else phone.push_back(Contact(name,number));break;
		default:
			    long index =  binarySearch(phone,name,0,size_-1);
		        if(index < 0) throw exception("something's going rong with adding phone number");
		        phone.insert(phone.begin()+index,Contact(name,number));break;
		}
		size_++;
	}

// Find the names of people based on their phone numbers.
vector<string> PhoneBook::lookupNames(vector<int> numbers)
	{
		vector<string> names;
		int index;
		vector<Contact*> auxPhoneNumbers;
		//за да сортираме телефонните номера ще е по икономично ако направим вектор от указатели към
		// телефонните номера и сортираме тях
		for (int i = 0; i < size_; i++)
		{
			auxPhoneNumbers.push_back(&phone[i]);
		}
		//сортираме указателите от горния ред !!! изпозлвана е ламбда израз и това няма да тръгне на компилатор не поддържащ C++11
		sort(auxPhoneNumbers.begin(),auxPhoneNumbers.end(),[](Contact *ptr1,Contact *ptr2)->bool{ return ptr1->number < ptr2->number;});
		for (int i = 0; i < numbers.size(); i++)
		{
		//използваме interpolation search за да намерим дали тои номер съществува
		index = interpolationSearch(auxPhoneNumbers,numbers[i]);
		if(index>-1) //ако да то извличаме името от въпросния обект телефонен номер
			names.push_back(auxPhoneNumbers[index]->name);
		else names.push_back("There is no such number in the phone book"); //ако пък ли не зареждаме уведомителен стриг че няма съвпадение
		}
		
		return names;
	}

int PhoneBook::interpolationSearch(vector<Contact*> &arr,unsigned key)
	{
 
		int size = arr.size();
		if ( size < 0 || ! size )         // not the best way to handle this case, but it 
			 return -1 ;                 // serves to draw attention to it possibly happening. 
 
 
		unsigned long low = 0 ;
		unsigned long high = size - 1 ; 
		unsigned long mid ; 
 
 
		while ( ! (arr[high]->number == arr[low]->number || key < arr[low]->number || arr[high]->number < key)  )  
		{
				mid = low + (key - arr[low]->number) * ((high - low) / ( arr[high]->number - arr[low]->number)) ;
 
				if ( arr[mid]->number < key ) 
					 low = mid + 1 ;                                    
 
				else if ( key < arr[mid]->number )  
						  high = mid - 1 ;
 
				else return mid ;		     
		} 
 
		if ( key == arr[low]->number )  
			 return low ;
 
		else return -1 ;  
 
	}

int PhoneBook::binarySearch(vector<Contact> &A, string & nameKey, int imin, int imax)
		{
		  while (imin < imax)
			{
			  int imid = imin + (imax-imin)/2;
     
			  if (A[imid].getName() < nameKey)
				imin = imid + 1;
			  else
				imax = imid;
			}
  
		  if ((imax == imin) || (A[imin].getName() == nameKey))
			return A[imin].getName() < nameKey? imin+1 : imin;
		  else
			return -1;
		}

Contact &PhoneBook::getPhoneNumber(int index)
	{
		if(index >=size_ || index <0)
			throw exception("Index out of range\n");
		return phone[index];
	}

PhoneBook::PhoneBook(PhoneBook &init){
		size_= init.size_;
		for (auto var : init.phone)
		{
			phone.push_back(var);
		}
	}
