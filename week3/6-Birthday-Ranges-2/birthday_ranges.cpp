#include<iostream>
#include<vector>
#include <string.h>
//#include<fstream>
using namespace std;

class BIT{
        vector<int> bit;
        int bound; 
        int maxIndex;
        
        void updateAndClimb(int index)
        {
       for (int parent = (index-1)/2; index ; index = parent,parent = (index-1)/2)
                {
                        bit[parent] = bit[parent*2+1] + bit[parent*2+2];
                }
        }

public:

        BIT(const vector<int> &input)
        {
                if(!input.size()) throw "BIT constructor \"Empty input\"\n"; 
                maxIndex = input.size();
                bound = 1;
                while (bound < input.size() && bound < 2147483648)bound<<=1;

                int bitSize = (bound*2)-1;
        
                bound--; 
        
                bit.resize(bitSize,0);
        
                for (int i = bound ,j=0; j < input.size(); i++,j++)
                {
                        bit[i]=input[j];
                }
        
                for (int i = bound-1; i >= 0; i--)
                {
                        bit[i] = bit[(i*2)+1] + bit[(i*2)+2];
                }
        }

        int Quary(int index)const
        {
                if(index < 1 || index > maxIndex) throw "No such element\n";
                if(index == maxIndex) return bit[0];
                int sum = 0;
                index+=bound;
                unsigned int leftChild,parent;
        
                for (parent = (index-1)/2; index; index = parent,parent = (index-1)/2)
                {
                        leftChild = parent*2 + 1 ;
                        if(leftChild == index) continue;
                        else sum+=bit[leftChild];
                }
                return sum;
        }
    int  getSum(int from,int to)const
     {
                if(from < 1 || from > maxIndex) throw "starting argument is out of range\n";
                if(to < 1 || to > maxIndex) throw "ending argument is out of range\n";
                if(from > to) throw "ending argument can not be less than starting one\n";
            return Quary(to)-Quary(from-1? from-1 : 1); 
                                                           
        }
        void replace(int index, int newValue)
        {
                if(index < 1 || index > maxIndex) throw "No such element\n";
                index+=bound-1;
                bit[index] = newValue;
                updateAndClimb(index);
        }

        void update(int index, int addition)
        {
                if(index < 1 || index > maxIndex) throw "No such element\n";
                index+=bound-1;
                bit[index] = bit[index] + addition;
                updateAndClimb(index);
        }

        int getElement(int index)const
        {
                if(index < 1 || index > maxIndex) throw "No such element\n";
                return bit[index+bound-1];
        }
};

class BirthdayRanges {
        BIT days;
public:
   BirthdayRanges():days(vector<int>(366,0)){ }
   BirthdayRanges(const vector<int> &input):days(input){ }

  void add(int day, int numberOfPeople) {
          try{
       days.update(day+1,numberOfPeople);
          }catch(...){
                  throw "there is no such day in the list of available birthdays\n";
          }
  }
  void remove(int day, int numberOfPeople) {
          try{
     day++;
         (days.getElement(day) - numberOfPeople) > 0 ? days.update(day,-numberOfPeople) : throw -1;
          }catch(int){
                  days.replace(day,0);
          }catch(const char *){
                  throw "there is no such day in the list of available birthdays\n";
          }
  }

  int count(int startDay, int endDay) {
          try{
          return days.getSum(startDay+1,endDay+1);
          }catch(const char *){
                  throw "there is no such day in the list of available birthdays\n";
          }
  }
};


int main(){
        try{
                //ifstream in("input.txt");
                istream &in = cin;
                char cmd[10];
        int N,M,birthDay,maxRange;
                ios_base::sync_with_stdio(false);
        in>>N>>M;
        vector<int> input(366,0);
        for (int i = 0; i < N; i++)
        {
                in>>birthDay;
                input[birthDay]++;
        }
        BirthdayRanges bdr(input);
        for (int i = 0; i < M; i++)
        {
                        in>>ws; in.getline(cmd,10,' ');
            in>>birthDay>>maxRange;
                        if(!strcmp(cmd,"count")){
                                cout<<bdr.count(birthDay,maxRange)<<endl;
                        }
                        else if(!strcmp(cmd,"add")){
                                 bdr.add(birthDay,maxRange);
                        }else if(!strcmp(cmd,"remove")){
                                 bdr.remove(birthDay,maxRange);
                        }
    
        }
        }catch(const char *exc){
                cout<<exc<<endl;
        }
        return 0;
}
