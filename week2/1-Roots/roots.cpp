#include<iostream>
#include<iomanip>
using namespace std;

class Roots {
public:
  static double squareRoot(double number) {
    if(number == 0 || number == 1) {
            return number;
        }
                double start, end;
                if(number<1){
           start = number, end = 1;
                }
                else{
         start = 0, end = number+1 ;
                }
                double mid;
        while(end - start >= 0.0000001 ) {
            mid = start + (end - start) / 2;
            if(mid == number / mid) {
                return mid;
            }
            if(mid < number / mid) {
                start = mid ;
            } else {
                end = mid ;
            }
        }
        return start;
  }
};


int main()
{   
        double number;
        cin>>number;
                number = Roots::squareRoot(number);
                unsigned short significantDecimalFigures = 0;
                for (long i = (long)number; i; i/=10)
                {
                        significantDecimalFigures++;
                }
                                printf("%.5f\n",number);
        //cout<<setprecision(5+significantDecimalFigures)<<number<<endl;      
        return 0;
}
