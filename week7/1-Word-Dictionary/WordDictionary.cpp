#include<iostream>
//#include<fstream>
#include<map>
#include<string>
using namespace std;

class Disctonary{

          class Node{
          public:
                  bool isEnd; //this will indicate the end of a word
                  map<char,Node*> subStrings; //a map which will contain the adjacent nodes.
                                              //The chars are the weight of the edges                                         
                  Node():isEnd(false){};
          };
         Node root;
public:
          
          void insert(string &str){
                  int index = 0; //this will watch for the depth of the current node
                  Node *curr = &root; //the current Node
                  while (true)
                  {
             if(index < str.size()){ //if we are not at the end of the string
                                 //check if the current char exist
                                   std::map<char,Node*>::iterator it = curr->subStrings.find(str[index]); //-1
                                   //if not greate a new node coresponding to the missing char
                                   if(it == curr->subStrings.end()){                                  
                                           curr->subStrings[str[index]] = new Node(); //-1
                                           //and update the current node to refer the new one
                                           curr = curr->subStrings[str[index]];
                                   }
                                   else{
                                           //if there is maching go to the coresponding node
                                           curr=it->second;
                                   }
                         }else{//if we are at the end of the string 
                                 curr->isEnd = true;  //return the value indicating the end of a word
                                 break;
                         }
                         index++; //procced with the next char/depth
                  }
          }

          bool contains(string &str){

                  int index = 0; //this will watch for the depth of the current node
                  Node *curr = &root; //the current Node
                  while (index < str.size())
                  {
             if(index < str.size()){
                                 //check if the current char exist
                                   std::map<char,Node*>::iterator it = curr->subStrings.find(str[index]); //-1
                                   //if not return false
                                   if(it == curr->subStrings.end()){
                                        return false;
                                   }
                                   else{
                                           //if there is maching go to the coresponding node
                                           curr=it->second;
                                   }
                         }
                          index++; //procced with the next char/depth
                  }
                  return curr->isEnd; //return the value indicating the end of a word
          }
};

int main(){
        //ifstream in("input.txt");
        Disctonary d;
        istream &in = cin;
    ios_base::sync_with_stdio(false);
        int N;
        in>>N;
        for (int i = 0; i <N ; i++)
        {
                string command, str;
                in>>command>>str;
                if(command == "insert"){
                        d.insert(str);
                }else if(command == "contains"){
                        cout<<boolalpha<<d.contains(str)<<endl;
                }        
        }
        return 0;
}