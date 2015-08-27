#include<iostream>
#include<vector>
//#include<fstream>
using namespace std;

class MaxBanana{

public:

        static int FindMaxBanana(vector<vector<int> > input){
                //If the final task is to find the all moves, the dinamyc optimization will
                //consist of the all simplest moves.The simple move to a certain cell is from left
                //or from below(dolna) cell. So we must chose the one we with biger value
                for (int i = input.size(); i--;)//iterate through the rows
                {
                        for (int j = 0; j < input.size(); j++)
                        {
                                if( (i+1<input.size() ) && (j-1)>=0 ){ //if we are not out of the matrix
                                        //wen we jump to the nex cell we add the bannas from the cell we are jumping from
                                        input[i][j] += input[i+1][j] > input[i][j-1] ? input[i+1][j] : input[i][j-1] ;
                                }else if(  (i+1)<input.size() ){
                                        //the case we are jumping of the matrix X edge
                                        input[i][j]+=input[i+1][j];
                                }else if ((j-1)>=0){
                                        //the case we are jumping of the matrix Y edge
                                        input[i][j] += input[i][j-1];
                                }
                        }
                }
                //returning the top right cell's value
                return input[0][input.size()-1];
        }

};


int main(){

        //ifstream in("input.txt");
        istream &in = cin;
        ios_base::sync_with_stdio(false);
        int N;
        in>>N;
        vector<vector<int> > input(N,vector<int>(N));
        for (int i = 0; i < N; i++)
        {
                for (int j = 0; j < N; j++)
                {
                        in>>input[i][j];
                }
        }
        cout<<MaxBanana::FindMaxBanana(input)<<endl;

        return 0;
};