#include<iostream>
using namespace std;

template<class T>
void insertion( T *a, int l , int r){
	int i;
	//тук преместваме най-отляво да е най малкия елемент
	//и тои ни служи за ограничител с което се прописка една проверка
    //за достигане левия край на масива
	for(i = r;i>l;i--) {
			if(a[i] < a[i-1]){
				T tmp = a[i];
			    a[i] = a[i-1];
				a[i-1] = tmp;
		      }
	}
	//тъй като сме подредили в началото да е най малкия то
	//първата възможна смqнa е между третия и втория елемент
	for(i = l+2; i<=r; i++)
	{
		int j = i; int v = a[i];

			while(v < a[j-1]){
				a[j] = a[j-1]; j--; }
	
		a[j] = v;
	}
}

template<class T>
T *sort(T *sequence,int l , int r) {
  T *sorted_sequence = new T[r-l+1];
  for (int i = l; i <= r; i++)
  {
	  *(sorted_sequence+i) = *(sequence+i);
  }
  insertion(sorted_sequence,l,r);
  return sorted_sequence;
}

int main(){
	int a[] = {7,8,5,2,4,6,3,10,11,16,43,17,52,18,14,20,89,23,64,73,85,25,67,19,4,25,89,65,23,67,89,43,23,55,33,36};
	cout<<"The unsorted array:";
	for (int i = 0; i < 36; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Using Insertion Sort!\nThe sorted array: ";
	int *b = sort(a,0,35);
	for (int i = 0; i < 36; i++)
	{
		cout<<b[i]<<" ";
	}

	cout<<endl;

	system("PASUE");

}
