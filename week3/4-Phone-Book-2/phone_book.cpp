#include<iostream>
#include<string>
#include<vector>
#include<stack>
#include<map>
//#include<fstream>
using namespace std;

class PhoneBook {
                class Contact {
                  public:
                  string name;
                  string number;
                  Contact *left;
                  Contact *right;
                  Contact(const string &name_,string &number_):name(name_),number(number_),left(NULL),right(NULL){}
                  Contact(const Contact &init):name(init.name),number(init.number),left(NULL),right(NULL){}
       };
       Contact *root;
public:

  //inserts a new contact
  void insert(Contact &contact)
  {   
                Contact **curr = &root;
                while(*curr != NULL){
                        if(contact.name < (*curr)->name)
                        {
                curr= &((*curr)->left);
                        }
                        else if( contact.name > (*curr)->name){
                                curr= &((*curr)->right);
                        }
                        else if( contact.name == (*curr)->name){
                                (*curr)->number = contact.number;
                        }
                }

                *curr = new Contact(contact);
                //size++;
        }
  
  //inserts a new contact
  void insert(const string& name, string &number )
  {   
                Contact **curr = &root;
                while(*curr != NULL){
                        if(name < (*curr)->name)
                        {
                curr= &((*curr)->left);
                        }
                        else if( name > (*curr)->name){
                                curr= &((*curr)->right);
                        }
                        else if( name == (*curr)->name){
                                (*curr)->number = number;
                                return;
                        }
                }

                *curr = new Contact(name,number);
                //size++;
        }
  
  //lookup a name and print its phone number
  string lookup(string &name){
          Contact **curr = &root;
                        while(*curr != NULL){
                                if(name < (*curr)->name)
                                {
                                        curr= &((*curr)->left);
                                }
                                else if( name > (*curr)->name){
                                        curr= &((*curr)->right);
                                }
                                else if( name == (*curr)->name){
                                        break;
                                }
                        }
                        if(*curr) return (*curr)->number;
                        else return  "NOT FOUND!";

  }
  
  //list all records in an alphabetical order
  void list(ostream &out) {
            stack<Contact*> stack;
                        stack.push(NULL);
                        stack.push(root);
                        Contact *curr;
                        bool goLeft = true;
                        while(curr = stack.top())
                        {
                                        if(goLeft){
                                                while(curr->left){
                                                        stack.push(curr->left);
                                                        curr = curr->left;
                                                }
                                                goLeft =false;
                                        }
                                        stack.pop();
                                        if(curr->right)
                                        {
                                                stack.push(curr->right);
                                                goLeft = true;
                                        }
                                        out<<curr->name<<' '<<curr->number<<endl;
                        }
  }
  
  //remove a record for a given name
  void remove(string &name) {
     if(root == NULL) return;
                Contact *curr = root;
                Contact *prev = NULL;
                while(curr)
                {
        
                  //if the value is greater than the curr's one
                  if(name > curr->name && curr->right)
                  {
                          prev = curr;
                          curr = curr->right;
                          continue;
                  }
                  //if the value is smalest than curr's one
                  else if(name < curr->name && curr->left)
                  {
                          prev = curr;
                          curr = curr->left;
                          continue;
                  }
                  //if they are equal
                  else if(name == curr->name)
                  {
                          //ako imame savpadenie;
                          break;
                  }
                  else return; //thre is no node with such value

                }
                //if(!curr) return;

                /*to this point "curr" is pointing to the node which we are supposed to delete*/

                //if the node ,which is going to be deleted, has both right and left child
                if(curr->left && curr->right){
                        Contact *tmp1 = curr;//it will point to the node whose left child will replace the one being deleted
                        Contact *tmp2 = curr->right; //it will point to the node which will replace the one being deleted
                        //until tmp2 is the smalest we proceed only to the left nodes
                        while(tmp2->left != NULL)
                        {
                                tmp1 = tmp2;
                                tmp2 = tmp2->left;
                        }

                        //in case that the first right node from/of the one being deleted is not the smallest in the right subtree
                        if(tmp1 != curr)
                        {
                                //if the smalest node has no children we set previus Node's left poiter to NULL
                                if(!tmp2->right)
                                {
                                   tmp1->left =NULL;
                                }
                                else{  //else we set previus Node's left poiter to point the right child of the current node
                                        tmp1->left = tmp2->right;
                                }

                                tmp2->right = curr->right;
                                
                        }
                        
                         tmp2->left = curr->left;
                         delete curr;
                     curr = tmp2;
                }
                //in case the the node ,which is going to be deleted, has only left child
                else if(curr->left){
                        Contact *tmp = curr->left;
                        delete curr;
                        curr = tmp;
                }
                //int case the node ,which is going to be deleted, has only right child
                else if(curr->right){
                        Contact *tmp = curr->right;
                        delete curr;
                        curr = tmp;
                }
                //int case the node ,which is going to be deleted, has no child
                else
                {                
                         delete curr;
                     curr = NULL;
                }

                /*
                o this point we have deleted the node containing the passed value as an function's argument.
                The main tree has been divided to two subtrees. 
                The pointer "prev" is pointing to the bigest/smallest node from the first and the pointer "curr" 
                points to the smallest/bigest node from the second tree. Now is the time to connect those nodes, 
                making the tree whole again.
                */

                //in case we havn't deleted the root
                if(prev)
                {
                        if(name >= prev->name) //if we have deleted the right child from prev
                        {                        //the equalition cheking is in case that there is a node with the same value
                                prev->right = curr;  //like the one whose node we have been deleted
                        }
                        else
                        {
                                prev->left = curr;
                        }
                }
                //in case we have been deleted the root
                else
                {
                        root = curr;
                }

                //size--;
  }
  
   PhoneBook():root(NULL){}

   class Iterator{
                  friend class PhoneBook;
                  stack<Contact*> Stack;
                  bool goLeft;
                  Iterator(Contact *root):goLeft(true)
                  {
                          Stack.push(NULL);
                          Stack.push(root);
                  }
        public:
                 
                  int isEmpty(){
                          return (Stack.top() == NULL);
                  }
                
        vector<string> next()
                {
                        Contact *curr = Stack.top();
                        if(curr == NULL) throw "The tree is empty";
                        if(goLeft){
                                while(curr->left){
                                        Stack.push(curr->left);
                                        curr = curr->left;
                                }
                                goLeft =false;
                        }
                        Stack.pop();
                        if(curr->right)
                        {
                Stack.push(curr->right);
                                goLeft = true;
                        }
                        
                        vector<string> result;
                        result.push_back(curr->name);
                    result.push_back(curr->number);
                        return result;                                
                }
        };

   PhoneBook::Iterator begin()
        {
                return Iterator(root);
        }        
};


int main(){
        //ifstream in("input.txt");
        map<string,short> cmd;
        cmd["insert"] = 1;
        cmd["lookup"] = 2;
        cmd["remove"] = 3;
        cmd["list"] = 4;
        short commds;
        PhoneBook pb;
        int commands;
        string command;
        ios_base::sync_with_stdio(false);
        cin>>commands;
        while (commands--)
        {
                string command,number;
                cin>>command;
                commds = cmd[command];
                switch (commds)
                {
                case 1: cin>>number>>command;
                pb.insert(command,number); break;
                case 2: cin>>command;
                            cout<<pb.lookup(command)<<endl; break;
                case 3: cin>>command;
                            pb.remove(command);break;
                case 4: pb.list(cout); break;
                
                }
        
        }

        return 0;
};
