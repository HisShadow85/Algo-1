#include<iostream>

using namespace std;

template<class T>
void exchange(T &A, T &B){
	T tmp = A; A = B ; B = tmp;
}

template<class T>
void QuickSort(T *a, int l, int r){
	if(l>=r) return;
	T &pivot = a[r]; //взимаме крайния десен елемент за опорна точка, той ще е и ограничител от дясно
	int
		i = l-1, //инкреметиращ се индекс указващ елементите по големи от опор. точка
		j = r,  //деклементиращ се индекс указващ елементите по малки от опорната точка(пивот)
		p = l,  //индекс указващ края на подредените елемети равни на пивота от левия край
		q = r-1; //индекс указващ края на подредените елемети равни на пивота от десния край
	//контролен код
	/*cout<<endl<<"In the Sort Body:\The intput Array:\n";
	for (int i = l; i < r+1; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl<<"Pivot:"<<pivot<<endl;
	*/

	while(true)
	{
		  while(a[++i] < pivot);   //спира се на първия елемент който не е по-малък от опор. точка
		  while(a[--j] > pivot) if(j == l) break; //спира се на първия елемент който не е по-голям от опор. точка
		  if(i>=j) break;
		  exchange(a[i],a[j]); //разменя елеметите на правилните им места
		  if(a[i] == pivot) exchange(a[i],a[p++]); //ако даден разменен елемент е равен на опор. точка то той се мести към най близкия си край.
		  if(a[j] == pivot) exchange(a[j],a[q--]); //Така всички елементи равни на опор. точка са подредени един след друг в двата края
	}
	exchange(a[i],a[r]); //пивота се мети в така наречената среда на масива която вече е подредена и повече няма да се пипа
	j = i+1; // j сочи първия елемент след повота от дясно на ляво и вече ще е инклементиращ се индекс
	i--; // i сочи последния елемент преди повота от ляво на дясно и вече ще е деклементиращ се индекс
	for(int k = l; k < p ; k++, i--) exchange(a[i],a[k]); //Тези два цикъла долепят от ляво и дясно на пивота
	for(int k = r-1; k > q  ; k--, j++) exchange(a[j],a[k]); // неговите еквивалентни елементи
	//контролен код
	/*cout<<"output Array:\n";
	for (int i = l; i < r+1; i++)
	{
		cout<<a[i]<<" ";
	}
	cout<<endl;
	*/
	QuickSort(a,l,i);
	QuickSort(a,j,r);
	}

template<class T>
T *sort(T *sequence,int l , int r) {
  T *sorted_sequence = new T[r-l+1];
  for (int i = l; i <= r; i++)
  {
	  *(sorted_sequence+i) = *(sequence+i);
  }
  QuickSort(sorted_sequence,l,r);
  return sorted_sequence;
}

int main(){
	
	int a[] = {1,2,7,4,1,6,0,3,6,8,1,7,8,9,3,1,2,5,8,6,5,2,1,3,4,5,8,0,7,5,4,3,2,1};
	cout<<"The unsorted array:";
	for (int i = 0; i < 34; i++)
	{
		cout<<a[i]<<" ";
	}	
	int *b = sort(a,0,33);
	cout<<endl<<"Using Quick Sort!\nThe sorted array: ";
	for (int i = 0; i < 34; i++)
	{
		cout<<b[i]<<" ";
	}

	cout<<endl;

	system("PASUE");

}
