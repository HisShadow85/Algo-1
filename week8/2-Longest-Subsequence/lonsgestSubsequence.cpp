﻿#include<iostream>
#include <vector>
using namespace std;
 
/* Finds longest strictly increasing subsequence. O(n log k) algorithm. */
void find_lis(vector<int> &input, vector<int> &ls)
{
	/*ls ше съдържа ПОСЦЛЕДНАТА най-дълга нарастваща поредица, като по време на нейното намиране
	  не е задалжително(а и рядко ще е) ls да съдържа реална последователност. Самата големина на ls
	  говори колко е дълга най-голямата намерена последователнос като на 100% е сигорно, чесамо последният
	  елемент от ls е част от тази най-голяма последователност. Тя може да се проследи чрез масива съхраняващ
	  пътя path. В самия ls ще се подреждат така елементите че те да са подредени по големина и така в самия 
	  масив може да има няколко под последователности.*/

	/*тук ще съхраняваме пътя. Или с други думи всеки индекс ще отговаря на индекс от входните данни,
	а стойността в клетката ще е индекса от входните данни на най-големия елемент по-малък от съответния 
	елемент отговарящ на индекс от path*/
	vector<int> path(input.size());
	int min, max;//ще ги ползваме предимно за binary search
 
	if (input.empty()) return;
 
	ls.push_back(0);//винаги започваме с първия индекс
 
	for (size_t i = 1; i < input.size(); i++) 
        {
                /* ако следващия елемент input[i] е по голям от последния елемент намиращ се в най-дългата
			    под последователност input[ls.back()], го вкарваме в ls и така получаваме последния елемент 
			    от най-голямата текуща нарастваща под последователност в лицето на посления елемент на ls,
			    както дължината на самата тази последователнос в лицето на дължината на ls. Да не забравяме, 
			    че въпросната последователност може да се извлече от path.*/
		if (input[ls.back()] < input[i]) 
                {
			path[i] = ls.back();//тук на съитветния индекс записваме елемента който седи плътно преди него.
			//под плътно имам предвид най-големия по малък елемент от този в въпросния индекс който настройваме
			ls.push_back(i); //тук увеличаваме текущата най-голяма под последователност.
			continue; //и след това преминаваме на следващия елемент от входа.
		}
         //ако обаче този следващ елемент не е по голям от най-големия в най-голямата текуща под последователност

		/*Използваме двойчно търсене търсене за да намерим най-малкия елемент от ls който да е по голям от 
		текущия входен елемент input[i]. Трябва да отбележим че двойчното търсене се осъществява върху ls а не 
		върху input.Понеже в ls се съхраняват индекс за да им изведем стойността ползваме input. Големината на 
		ls е <= на к(големината на най-голямата нарастваща под последователност) и заради това сложността е
		O(log k)*/   
		for (min = 0, max = ls.size()-1; min < max;) 
                {
			int mid = (min + max) / 2;
			if (input[ls[mid]] < input[i]) min=mid+1; else max=mid;
		}
 
            /*сега ако елемента намерен от двойчното търсене е наистина по голям(а не равен) от текущия входен
			елемнт, който обработваме(input[i]) то ние ще заменим индекса на input[i] този намерен от ls като така,
			input[i] ще е края на някава нарастваща под последователност в ls. */
		if (input[i] < input[ls[min]]) 
           {
			 //естествено да не забравяме пътя да отбележим. Тъй-като всички в ls са последователно нарастващи то 
			 //занчи  че min-1 ще е индекса на елемента плътно пред input[i]
			if (min > 0) path[i] = ls[min-1];
			ls[min] = i;
		   }	
	}
    //накрая чрез path възтановяваме в ls последната открита най-дълга нарастваща под последователност;
	for (min = ls.size(), max = ls.back(); min--; max = path[max]) ls[min] = max;
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
