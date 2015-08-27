#include<iostream>
#include<string>
#include<vector>
#include<map>

using namespace std;
enum Protocol{UNKNOWN,TCP,DNS,IGMP,RTM,UDP,ICMP};
class BandwidthManager {
        class Packet{
       string data;
           Protocol protocol;
           unsigned long packetId;
           friend class BandwidthManager;
           Packet(const string data_,const Protocol protocol_,unsigned long packetId_):data(data_),protocol(protocol_),packetId(packetId_){}
           bool operator<(Packet &other){return protocol<other.protocol || ((protocol == other.protocol) && (packetId > other.packetId));}
           //bool operator<=(Packet &other){return protocol<=other.protocol;}
           //bool operator==(Packet &other){return protocol==other.protocol;}
        };
        vector<Packet> queue;
        //mutex que;
        int protocolsIds;
public:
        BandwidthManager():protocolsIds(0){}
        
           
   
    //receives a packet with specified protocol and payload
    void rcv(string protocol, string payload){
          //que.lock();
          queue.push_back(Packet(payload,extractProtocolFromString(protocol),protocolsIds++));
          siftUp(queue.begin(),0,queue.size()-1);
          //que.unlock();
  }

    void rcv(Protocol protocol, string payload){
         // que.lock();
          queue.push_back(Packet(payload,protocol,protocolsIds++));
          siftUp(queue.begin(),0,queue.size()-1);        
          //que.unlock();
  }
  
    //returns the payload of the packet which should be sent
    string send(){
      string result;
          //que.lock();
          if(queue.size()){
          result = queue[0].data;
          queue[0] = queue[queue.size()-1];
          siftDown(queue.begin(),0,queue.size()-1);
          queue.pop_back();
          //que.unlock();
          }else{
                  //que.unlock();
                  result = "Nothing to send!";
          }           
          return result;
  }     

    template<typename Iterator>
        void siftUp(Iterator a,int start,int end)
                {
                         // input:  start represents the limit of how far up the heap to sift.
                         // end is the node to sift up.
                         int child = end; 
                         while (child > start)
                         {
                                 int parent = (child-1) / 2 ;


                                 if (a[parent] < a[child] )//then out of max-heap order
                                 {                                            
                                         swap(a[parent], a[child]);
                                         child = parent; //repeat to continue sifting up the parent now
                                 }
                                 else
                                         return;
                         }
        }

        template<typename Iterator>
    void siftDown(Iterator a,int start,int end){
                int root = start;

                while ((root * 2 + 1) <= end){    //(While the root has at least one child)
                        int child = root * 2 + 1 ;     // (Left child)
                        int toSwap = root;                //(Keeps track of child to swap with)

                
                        if (a[toSwap] < a[child]) {
                                
                                toSwap = child ;
                                
                        }
                        //(If there is a right child and that child is greater)
                        if ( (child+1 <= end) && (a[toSwap] < a[child+1]) )
                                toSwap = child + 1;
                
                        if (toSwap == root)
                                //(The root holds the largest element. Since we assume the heaps rooted at the
                                // children are valid, this means that we are done.)
                                return;
                        else{
                                swap(a[root], a[toSwap]);
                                root = toSwap ;           // (repeat to continue sifting down the child now)
                            }
                         
                        }
                    
          }

    static Protocol extractProtocolFromString(string &protocol){
          static map<string,Protocol> protocols;
          protocols["TCP"] = TCP;
          protocols["DNS"] = DNS;
          protocols["IGMP"] = IGMP;
          protocols["RTM"] = RTM;
          protocols["UDP"] = UDP;
          protocols["ICMP"] = ICMP;
          try{
          return protocols[protocol];
          }catch(...){
                  return UNKNOWN;
          }
  }
};


int main(){
        //ifstream in("input.txt");
        short commds;
        BandwidthManager bm;
        int commands;
        string command;
        ios_base::sync_with_stdio(false);
        cin>>commands;
        while (commands--)
        {
                string command,load;
                cin>>command;
                if(command == "rcv"){
                        cin>>command>>load;
                        bm.rcv(command,load);
                }
                else if(command == "send"){
                        cout<<bm.send()<<endl;
                }        
        }

        return 0;
}
