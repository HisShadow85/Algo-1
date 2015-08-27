#include<iostream>
using namespace std;

        void jumpingSoldiers(istream &in,ostream &out){
                unsigned maxJumps = 0;
                unsigned char maxJumpsRow = 0;
                unsigned bound = 1;
                unsigned *row;
                int N , K;
                unsigned *rowJump;
                int currSoldier;

                in>>ws>>N>>ws>>K;

                //check for zero size input//
                if(N <1 || K<1 || K > 20 || N > 10000) throw "Invalid initial imput(N or K)\n"; 
                //the number of the input's elements must be always power of two so if they are not  we just make them so
                while (bound < (unsigned)N && bound < 2147483648) bound<<=1;
                /*since the nodes derived from the input data will take the same amount of memory 
                as the input itself minus one, we make the size of the work array twice the number 
                of the input data minus one */        
                row = new unsigned[(bound*2)-1];                                                             
                /*make the index of the bound to point the first element.*/
                bound--;                 
                //initialing the array where we are going to store the number of jumps for each row
                rowJump = new unsigned[K];
                std::fill_n(rowJump,K, 0);
                //the real job
                for( int i = 0; i < K && in; i++) //counting the rows
                {
                        
                        std::fill_n(row,((bound+1)*2)-1,0);
                

                        for (int j = 0; j < N; j++) //countig the soldiers
                        {
                                in>>ws>>currSoldier;
                                if(currSoldier < 1 || currSoldier > N){
                                        throw "Invalid soldier height\n";
                                }
                                currSoldier = N-currSoldier; //that the hight soldier will be market as N-1 and shortes wit zero
                               // if(currSoldier == N) currSoldier--;///!!!!onlyFor the test in the arena!!!!!!!!!!!!!!!!!!!!!!!!!!!!
                                unsigned index=currSoldier + bound;//compute the real index after the desired height
                                if(row[index]) {
                                        throw "Soldier height has been already used in the current row\n";
                                }
                                if(j)//computing the number before first soldier is useless
                                {
                                                        if(currSoldier < N-1)
                                                        {
                                                                int auxIndex = index + 1;
                                                                //starting from the leafs we climbing up the tree. Parent = ((left/right)Child-1)/2
                                                                for(int leftChild,parent; auxIndex > 0 ; auxIndex = parent)
                                                                {   
                                                                        parent = (auxIndex-1)/2;
                                                                        leftChild = parent*2 + 1 ;
                                                                        if(leftChild == auxIndex) continue; // if we are at leftChild then climbing up
                                                                        else rowJump[i]+=row[leftChild]; // else add the left child to the row jumps
                                                                }

                                                        }else{
                                                                rowJump[i]+=row[0];
                                                        }
                                }
                                
                                //insert the soldier into the working array
                                row[index]++;
                            //computing the values of the corresponding nodes(repairing the index tree)
                                for (unsigned parent ; index ; index = parent)
                         {
                                              parent = (index-1)/2;
                                      row[parent] = row[parent*2+1] + row[parent*2+2];
                         }
                        } // end //countig the soldiers

                        if(rowJump[i] > maxJumps) {
                                maxJumpsRow = i;  
                                maxJumps = rowJump[i];/////
                        }
                }//end //counting the rows

                out<<maxJumpsRow+1;
        }

int main(){

        try{
        jumpingSoldiers(cin,cout);
        }catch(const char *e){
        cout<<e<<endl;
        }catch(...){
         cout<<"unknown exception occurs"<<endl;
        }
        return 0;
}