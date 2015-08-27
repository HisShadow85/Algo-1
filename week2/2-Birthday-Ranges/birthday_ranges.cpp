#include<iostream>
#include<algorithm>
#include<vector>
#include<fstream>

using namespace std;

typedef struct{
	int from;
	int to;
}range;


class BirthdayRanges {

static int search(vector<int> &A, int key, int imin, int imax)
{
  
  while (imin < imax)
    {
      int imid = imin + (imax - imin)/2;
      
      if (A[imid] < key)
        imin = imid + 1;
      else
        imax = imid;
    }
  
  if ((imax == imin) && (A[imin] == key))
	 return imin; 
  else if(imax == imin)
	  //проверка при ситуацията когато дадена граница подадена за ключ 
	  //е по-голямя от най-голямия ден на раждане.Връща индекса след края на масива
	  return  A[imin] < key ? imin + 1 : imin;
  else return -1; 
}

public:
static vector<int> birthdaysCount(vector<int> Birhtdays, vector<range> &BirhtdayRanges)
{
	vector<int> result;
	int birhtdaysNum;
	int loopNum, lowRangeIndexOfmatching, hightRangeIndexOfmatching ;
	if(!(birhtdaysNum =Birhtdays.size()) || !(loopNum = BirhtdayRanges.size())) return result;
	sort(Birhtdays.begin(),Birhtdays.end()); //сортираме последователността от рожденни дни
	//извличаме резултатите на базата броя на зададените обхвати
	for (int i = 0; i < loopNum; i++)
	{
		//пускаме долнта граница през двойчно търсене и получаваме първия еменет по-голям или равен на долната граница
		lowRangeIndexOfmatching = search(Birhtdays,BirhtdayRanges[i].from,0,birhtdaysNum-1);
		//за гормата граница правим същото но я увеличаваме с 1 за да получим индекса на първия по-голям елемент от гор. граница
		hightRangeIndexOfmatching = search(Birhtdays,BirhtdayRanges[i].to+1,0,birhtdaysNum-1);
		//зареждаме дадения разултат на базата на индексна аритметика.
		result.push_back(hightRangeIndexOfmatching - lowRangeIndexOfmatching);
	}
	return result;
}
};


int main()
{   

	ifstream in("input.txt");
	int N , M;

	in>>N>>M;
	vector<int> Birhtdays(N);
	vector<range> BirhtdayRanges(M);

	for (int i = 0; i < N; i++)
	{
		in>>Birhtdays[i];
	}

	for (int i = 0; i < M; i++)
	{
		in>>BirhtdayRanges[i].from>>BirhtdayRanges[i].to;
	}

	vector<int> result = BirthdayRanges::birthdaysCount(Birhtdays,BirhtdayRanges);

	for (int i = 0; i < result.size(); i++)
	{
		cout<<result[i]<<endl;
	}

	return 0;


}

