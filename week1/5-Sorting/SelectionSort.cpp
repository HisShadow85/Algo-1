#include<iostream>
using namespace std;

template<class T>
void selection(T *a, int l , int r)
{
	int smalest;
	T tmp;
	for (int i = l; i < r; i++)
	{   
		smalest = i;
		for (int j = i+1; j <= r; j++)
		{
			if(a[smalest]>a[j]) smalest=j;
		}
      if(smalest != i){
		  tmp = a[i];
		  a[i] = a[smalest];
		  a[smalest] = tmp;
	      }
	}
}

template<class T>
T *sort(T *sequence,int l , int r) {
  T *sorted_sequence = new T[r-l+1];
  for (int i = l; i <= r; i++)
  {
	  *(sorted_sequence+i) = *(sequence+i);
  }
  selection(sorted_sequence,l,r);
  return sorted_sequence;
}

int main(){
	int a[] = {7,8,5,2,4,6,3,10,11,16,43,17,52,18,14,20,89,23,64,73,85,25,67,19,4,25,89,65,23,67,89,43,23,55,33,36};
	cout<<"The unsorted array:";
	for (int i = 0; i < 36; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Using Selection Sort!\nThe sorted array: ";
	int *b = sort(a,0,35);
	for (int i = 0; i < 36; i++)
	{
		cout<<b[i]<<" ";
	}

	cout<<endl;

	system("PASUE");

}
