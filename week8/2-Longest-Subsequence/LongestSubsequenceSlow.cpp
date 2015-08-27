#include<iostream>
#include <vector>
using namespace std;
 
/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
void find_lis(vector<int> &input, vector<int> &output)
{
	//тък даден индекс отговаря на индек от входа а стоиноста на броя елементи в полседователността
	//до съответния елемент и включително него
	vector<int> sequencesCounter(input.size());
	vector<int> path(input.size());//тук пак всеки индекс съответства на индексите от входа но тук стохността
	              //в клетката преставлява индекса на елемента от входа който седи плътно преди текущия елемент
	//sequencesCounter[0] = 1;//първия елемент образува поредица сам със себеси
	int maxSequence = 0;//това ще показва колко е най-дългата последователност
	for (unsigned i = 0; i < input.size(); i++)
	{
		int prevIndex = 0;//това ще отбелязва индекса на елемента в най-голяма поредица по-малък от текущия 
		                  //елемент input[i]
		for (unsigned  j = 0; j < i ; j++)
		{
			if( ( input[j] < input[i] ) && ( sequencesCounter[j] > sequencesCounter[prevIndex] ) )
			            prevIndex = j; 
		}
		//поредицата от елементи до текущия е броя на елементите до предишния по-малък + 1
		sequencesCounter[i] = sequencesCounter[prevIndex] + 1;
		path[i] = prevIndex;

		if( maxSequence < sequencesCounter[i] ) maxSequence = sequencesCounter[i];
	}
	vector<vector<int> > result;
	for (unsigned  i = 0; i < sequencesCounter.size(); i++)
	{
		if(sequencesCounter[i] == maxSequence){
			result.push_back(vector<int>(maxSequence));
		
			for (int j = i, k = maxSequence; k--; j= path[j])
			{
				result.back()[k]= j;//тука сахраняваме само индексите но може и стоиностите
			}
		}
	}
	//тук ще върнем само един ресултат но може и всичките
	output.assign(result[0].begin(),result[0].end());
}
 
/* Example of usage: */
int main()
{
        int N;
        ios_base::sync_with_stdio(false);
        cin>>N;
        vector<int> seq(N); // seq : Input Vector
        for (int i = 0; i < seq.size(); i++)
        {
                cin>>seq[i];
        }
 
         vector<int> lis;  // lis : Vector containing indexes of longest subsequence 
        find_lis(seq, lis);
         cout<<lis.size()<<endl;
        //Printing actual output 
                int i;
        for (i = 0; i < lis.size()-1; i++)
                cout<<seq[lis[i]]<<' ';
            cout<<seq[lis[i]]<<endl;  
 
        return 0;
}