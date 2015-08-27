#include<iostream>
#include<vector>
#include<string>
//#include<fstream>
using namespace std;

class LongestCommonSubstring{

public:
	static vector<int> run(string str1, string str2,int &longest){
		//правим матрицата с по един допалнителен нулев ред и колона за да избегнем проверка дали
		//неизлизаме от матрицата(часта с +1)
		vector<vector<int> > L(str1.size()+1,vector<int>(str2.size()+1) );
		longest = 0;//тук ще съхраняваме най-дългата обща последователност
		vector<int> ret;//тук ще се садаржа най-дулгата/е обща/и полседователност/и
			for (int i = 1; i < str1.size(); i++)//за всяка буква от пърия стринг обикаляме из всяка
			{                                   
				for (int j = 1; j < str2.size(); j++) //буква от втория стринг
				{
					if(str1[i-1] == str2[j-1]){ //ако те са равни
						L[i][j] = L[i-1][j-1]+1; //прибавяме тази послдователност към тази от предишната клетка
					                             //така ако имаме последователнос АБ и се окаже че и В е обща
						                         // за клетката В*В ще сложим 2(АБ) + 1 и така става АБВ
						if(L[i][j] > longest){   //ако намерим по дълга последователност
							longest = L[i][j];   //обновяваме променливта саахраняваща броя 
							                     //на най-дългата последователнст
							ret.clear();         //изтриваме вектора сахраняващ най-дулгия/те стринг/ове
							ret.push_back(i);    //вкарваме индекса в който свършва въпросния стринг
						}else if(L[i][j] == longest){ //ако пък сме открили стриг равен на най-големия
							ret.push_back(i); //съхраняваме краиния индекс и на този стринг
						}
					}else{
						L[i][j] = 0; //ако пък двете букви не са равни то тази клетка ще е нула
					}
				}
			}

			return ret;
	}

};

int main(){

	//ifstream in("input.txt");
	istream &in = cin;
	ios_base::sync_with_stdio(false);
	string str1,str2;
	int longest;
	getline(in,str1);
	getline(in,str2);
	vector<int> result = LongestCommonSubstring::run(str1,str2,longest);
	str2.clear();
	//taq glupost ne q znam za kvo mi e . neshto se nagajdam na arenata
	if(result.size()>1){
		int smallest = str1.size() , smallestIdex=0;
		for (int i = 0; i < result.size(); i++)
		{
			if(result[i] < smallest) {
				smallestIdex = i;
				smallest = result[i];
			}
		}
		str2.append(str1.begin()+ result[smallestIdex]-longest,str1.begin()+ result[smallestIdex]);
	}else{
		//te tova samo treba da ostane
		str2.append(str1.begin()+ result[0]-longest,str1.begin()+ result[0]);
	}
	cout<<str2<<endl;
	return 0;

};