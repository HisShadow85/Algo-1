#include<iostream>

using namespace std;

template<class T>
void merge(T *c,T *a,int N, T *b, int M)
{
	for(int i = 0, j = 0 , k=0; k<N+M; k++)
	{
		if(i==N) { c[k] = b[j++]; continue;}
		if(j==M) { c[k] = a[i++]; continue;}
		c[k] = (a[i]<b[j])? a[i++] : b[j++];
	}
}

template<class T>
 void _mergeSort(T *a,T *b, int l , int r)
 {
	 int m = (l+r)/2;
	 if(r<=l) return;

	 _mergeSort(b,a,l,m); //разменяйки местата на главния и помощния масив при явсяко рекурсивно викане
	 _mergeSort(b,a,m+1,r); //  спестяваме едно излишно копиране на вече сортиран масив

	 merge(a+l,b+l,m-l+1,b+m+1,r-m);
 }

 template<class T>
 void mergeSort(T *a,int l , int r)
 {
	 T *aux = new T[r-l+1];
	 for(int i = l; i<=r; i++) aux[i] = a[i];
	 _mergeSort(a,aux,l,r);
	 delete aux;
 }

 template<class T>
 T *sort(T *sequence,int l , int r) {
	  T *sorted_sequence = new T[r-l+1];
	  for (int i = l; i <= r; i++)
	  {
		  *(sorted_sequence+i) = *(sequence+i);
	  }
	  mergeSort(sorted_sequence,l,r);
	  return sorted_sequence;
}

int main(){
	int a[] = {7,8,5,2,4,6,3,10,11,16,43,17,52,18,14,20,89,23,64,73,85,25,67,19,4,25,89,65,23,67,89,43,23,55,33,36};
	cout<<"The unsorted array:";
	for (int i = 0; i < 36; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Using Counting Sort!\nThe sorted array: ";
	int *b = sort(a,0,35);
	for (int i = 0; i < 36; i++)
	{
		cout<<b[i]<<" ";
	}

	cout<<endl;

	system("PASUE");

}
