#include<iostream>
#include<stdio.h>
//#include<fstream>
using namespace std;

class Quadruplets {
public:
   
        static bool compereDec(int a, int b) {return a < b;}
        static bool compereDes(int a, int b) {return a > b;}

static int zeroQuadrupletsCount(int *first,int* second,int *third , int *fourth ,short N)
{
        int resultCount = 0;
        int size = N;
                int *firstPair,*secondPair;
                firstPair = new int[size*size];
                secondPair = new int[size*size];
        for (int i = 0; i < size; i++)
        {
                for (int j = 0; j < size; j++)
                {       
                        firstPair[i*size+j] = first[i]+ second[j];
                        secondPair[i*size+j] = third[i]+ fourth[j];
                        
                }
        }
                size*=size;
            mergeSort(secondPair,0, size-1,compereDec);
                mergeSort(firstPair,0, size-1,compereDes);
                for (int i = 0,j=0; i < size && j < size;)
                {
                          short firstPairMatched = 0;
                          short secondPairMatched = 0;
                          while(firstPair[i] < -secondPair[j]) {j++; if(j >= size) goto breakPoint;}
                          while(firstPair[i] > -secondPair[j]) {i++; if(i >= size) goto breakPoint;}
                          if(firstPair[i] != -secondPair[j])continue;
                          else{
                                  firstPairMatched++;
                                  while(firstPair[i] == -secondPair[j] ){secondPairMatched++;j++;if(j >= size)break;}
                                  while( (++i < size) && (firstPair[i-1] == firstPair[i]) ){firstPairMatched++;}
                          }
                          resultCount+=firstPairMatched*secondPairMatched;
                }
                breakPoint:
        return resultCount;
    }

 
static void merge(int *c,int *a,int N, int *b, int M,bool (*less)(int,int))
{
        for(int i = 0, j = 0 , k=0; k<N+M; k++)
        {
                if(i==N) { c[k] = b[j++]; continue;}
                if(j==M) { c[k] = a[i++]; continue;}
                c[k] = less(a[i],b[j])? a[i++] : b[j++];
        }
}


static void _mergeSort(int *a,int *b, int l , int r,bool (*less)(int,int))
 {
         int m = (l+r)/2;
         if(r<=l) return;

         _mergeSort(b,a,l,m,less); 
         _mergeSort(b,a,m+1,r,less);

         merge(a+l,b+l,m-l+1,b+m+1,r-m,less);
 }

 
static void mergeSort(int *a,int l , int r,bool (*less)(int,int))
 {
         int *aux = new int[r-l+1];
         for(int i = l; i<=r; i++) aux[i] = a[i];
         _mergeSort(a,aux,l,r,less);
         delete aux;
 }
};

int main()
{
            //ifstream in("Input.txt");
        int N, number;
        cin>>N;
                if(1 > N  || N > 7000 ) cout<<"0";
                int **input = new int*[4*N];
                for (int i = 0; i < 4; i++)
                {
                        input[i] = new int[N];
                }
        for (int i = 0; i < 4; i++)
        {
                for (int j = 0; j < N; j++)
                {
                        cin>>number;
                        input[i][j] = number;
                }
        }
        cout<<Quadruplets::zeroQuadrupletsCount(input[0],input[1],input[2],input[3],N)<<endl;
        return 0;
}
