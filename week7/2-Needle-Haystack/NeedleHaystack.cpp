#include<iostream>
#include<cmath>
#include<vector>
#include<string>
//#include<fstream>
using namespace std;

class NeedleHaystack{
	unsigned maxBasePower; //the base raised to the power string size minus one
	unsigned const MOD;
	unsigned const base;
public:
	NeedleHaystack(int charsNumberMinusOne,unsigned base_,unsigned MOD_):base(base_),MOD(MOD_){
        maxBasePower=(long long)pow(base_,charsNumberMinusOne)%MOD;
	}
	//this will be a siple hash function for initializating hashes
	// (d*base^2 + o*base + g)%MOD (god string hash)
	unsigned int hash(string &str){
		unsigned int has=0;
		for (unsigned int i = 0; i < str.size(); i++)
		{
			//decoding tha charachtes from a to b to be 28-53 and from A to Z - 1 to 27
			has = (has*base + (str[i]>='a'?(str[i]-'a')+28:(str[i]-'A')+1) )%MOD;
		}
        return has;
	}
	//this is the rolling hash
	unsigned int rollingHash(unsigned int prevHash,char nextChar,char prevChar){
		//first from the previsus hash we subtract the first char from the previus string 
		//multiplicated by maxBasePower
		prevHash-= ( (prevChar>='a'?(prevChar-'a')+28:(prevChar-'A')+1) * maxBasePower )%MOD;
		if(prevHash < 0 ) prevHash+=MOD;//if the current hash became negative
		//multiplicate the hash by the base and add the next character
		prevHash = ( prevHash*base + (nextChar>='a'?(nextChar-'a')+28:(nextChar-'A')+1) )%MOD;
		return prevHash;
	}
	// Rabin-Karp algorithm
    vector<int> findSubstring(string &mainString, string &patternString){          
		vector<int> results;
		//take the hash of the wanted string and the on of the first wanted.size() long substring 
		unsigned int hs = hash(mainString.substr(0,patternString.size()));
		unsigned int hpattern = hash(patternString);
		//iterate throught the main string. Exlude the the last mainString.size()-wantedString.size() indices
		//beacouse if the wanted string s 3 symbols long there is no point check the last two indices of the 
		//main string
		for (int i = 0; i < mainString.size()-patternString.size(); i++)
		{
			//if the hashes are equal the we have to check if the wanted and the substring are equal
			 if (hs == hpattern){
				 if(mainString.substr(i,patternString.size()) == patternString){
					 results.push_back(i);
				 }
			 }
			 //take the hash of the next consecutive substring
			 hs = rollingHash(hs,mainString[i+patternString.size()],mainString[i]);
		}    
		return results;
	}
};

int main(){
	    //ifstream in("input.txt");
	    istream &in = cin;
		ios_base::sync_with_stdio(false);
		string s, pattern;
		getline(in,s);
		getline(in,pattern);

		NeedleHaystack nh(pattern.size()-1,53,37735849);

		vector<int> result = nh.findSubstring(s,pattern);
		for (int i = 0; i < result.size(); i++)
		{
			cout<<result[i]<<endl;
		}		 
		return 0;
}