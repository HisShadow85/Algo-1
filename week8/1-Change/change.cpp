#include<iostream>
#include<vector>

using namespace std;

class Change{

public:
        typedef short sum;
        Change(const vector<int> &coints, int maxSum){
                if(maxSum < 0 || coints.empty()) return;
        /*indices reppresent all avalible sums including the maxSum
                cell values are the posible ways to be build the coresponding sum*/
                sums.resize(maxSum+1,0);
                //the zero sum can be achieved only by doing one thing - precisely nothing
                sums[0]++;

                for (unsigned i = 0; i < coints.size(); i++)
                {
                        int cuurCoin = coints[i];
                        for (sum j = 0; j < (sum)sums.size(); j++)
                        {
                                sum currSum = j+cuurCoin;
                                if(currSum < (sum)sums.size()){
                                        sums[currSum]+=sums[j];
                                }
                        }
                }
        }

        int poslebleWays(sum wantedSum){
                if(wantedSum < 0 || wantedSum >= (sum)sums.size()) return 0;
                return sums[wantedSum];
        }

private:
        vector<sum> sums;

};


int main(){
        int c[7] = {1,2,5,10,20,50,100};
        vector<int> coins;
        for (int i = 0; i < 7; i++)
        {
              coins.push_back(c[i]);
        }

        Change change(coins,1000);
        int sum;
        ios_base::sync_with_stdio(false);
        cin>>sum;
        cout<<change.poslebleWays(sum)<<endl;
        /*
        cout<<change.poslebleWays(2)<<endl<<change.poslebleWays(5)<<endl<<change.poslebleWays(25)<<endl;
        cout<<change.poslebleWays(40)<<endl<<change.poslebleWays(2)<<endl;
     */
        return 0;
};