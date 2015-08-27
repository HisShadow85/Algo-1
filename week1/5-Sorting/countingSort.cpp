#include<iostream>
using namespace std;

void countingSort(int *a, int n)
{
	int maxValue = 0;
	for (int i = 0; i < n; i++)
	{
		if(a[i]>maxValue) maxValue = a[i];
	}
	maxValue++;
	int *auxIndeh = new int[maxValue];
	int *auxTemp = new int[n];
	memset(auxIndeh,0,maxValue*sizeof(int));
	memset(auxTemp,0,n*sizeof(int));
	for (int i = 0; i < n; i++)
	{
		auxIndeh[a[i]]++;
	}

	for (int i = 1; i < maxValue; i++)
	{
		auxIndeh[i]+=auxIndeh[i-1];
	}

	for (int i = n-1; i >= 0; i--)
	{
		auxTemp[--auxIndeh[a[i]]] = a[i];
	}

	for (int i = 0; i < n; i++)
	{
		a[i] = auxTemp[i];
	}
}


int *sort(int *sequence,int l , int r) {
  int *sorted_sequence = new int[r-l+1];
  for (int i = l; i <= r; i++)
  {
	  *(sorted_sequence+i) = *(sequence+i);
  }
  countingSort(sorted_sequence,r-l+1);
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