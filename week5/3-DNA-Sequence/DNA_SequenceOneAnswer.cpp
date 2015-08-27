#include<iostream>
#include<map>
#include<vector>
#include<set>
#include<string>
#include<fstream>
#include<stack>
using namespace std;


class Graph{
	friend class EulerPath;
	class Vertex{
	public:
		string lable; //the name cosists of the first three letters of the Nucleotides name;
		map<unsigned short,char> adjList; // first integer will represent the index of the neighbor
		                       // the char will represent the weight
		Vertex(string &lable_):lable(lable_){}
	};

	vector<Vertex> vertices; //tuk za po lesna obrabotk shte sahraniavame vazlite kato indeksi

	//towa shte swarzwa ime sas indeks
	map<string,unsigned short> map_;//it will be a map of the vertices and theire indices

public:

	void addEdge(string &edge1,string &edge2,char weight){
		  unsigned short index1, index2;// tezi promenlivi shte sadarjat
		  //ako parviq element ne sashtestvuva
		  map<string,unsigned short>::iterator it = map_.find(edge1);
		  //go vavejdame
	      if(it == map_.end()){
			  //saotvetnoto ime shte vodi kum posledniq indeks ot vazlite kadeto shte go butnem sega
			  map_[edge1] = vertices.size();
			  index1 = vertices.size();
			  //pravim noviq vazel
			  vertices.push_back(Vertex(edge1));			  
		  }else{
             index1 = it->second;
		  }
		  //i ako wtoriq vazel ne sashtestvuva
	      it = map_.find(edge2);
		  //go sazdavame
		  if(it == map_.end()){
			  map_[edge2] = vertices.size();
			  index2 = vertices.size();
			  vertices.push_back(Vertex(edge2));			  
		  }else{
			  index2 = it->second;
		  }
		  //osashtestvqvame dvoinata vrazka
		  vertices[index1].adjList.insert(pair<unsigned short,char>(index2,weight));
		  vertices[index2].adjList.insert(pair<unsigned short,char>(index1,weight));
	}

	//pomoshten klas pri koito teglata sa premahnati s cel po lesno izwlichane na oileroviq pat
	class WorkingGraph{

		vector<set<unsigned short> > vertices;

	public:

		WorkingGraph(int N):vertices(N){}

		void addEdge(unsigned short edge1,unsigned short edge2){
			vertices[edge1].insert(edge2);
			vertices[edge2].insert(edge1);
		}

		void addEdge(unsigned short edge,map<unsigned short,char>::iterator begin,
			                              map<unsigned short,char>::iterator end){
			for (; begin != end; begin++)
			{
				vertices[edge].insert(begin->first);
		    }
		}
		//po podaden indeks na vazel premahva vryzkata mejdu nego i parviq mu sased
		// vrushtaiki indeksa na saseda
		int removeNextEdge(unsigned short edge){
			unsigned short neihgbor = *vertices[edge].begin();
			vertices[edge].erase(neihgbor) ;
			vertices[neihgbor].erase(edge) ;
			return neihgbor;
		}

		int adjListSize(unsigned short edge){
			return vertices[edge].size();
		}

		int getFirstOddDegreeVertex(){
			for (unsigned i = 0; i < vertices.size(); i++)
			{
				if(vertices[i].size() & 1) return i;
			}
			return -1;
		}

		bool isEulerPath(){
			 int oddDegree = 0;
			 for (unsigned i = 0; i < vertices.size(); i++)
			 {
				if(vertices[i].size() & 1) oddDegree++;
			 }

			 return oddDegree == 2? true:false;
		}
	};
	//ot dadeniq graf izwlicha raboten takav
	WorkingGraph getWorkingGraph(){

		WorkingGraph result(vertices.size());


		for (unsigned i = 0; i < vertices.size(); i++)
		{
			for (map<unsigned short,char>::iterator it = vertices[0].adjList.begin();
				                            it !=  vertices[0].adjList.end(); it++)
			{
				result.addEdge(i,vertices[i].adjList.begin(),vertices[i].adjList.end());
			}
		}
		return result;
	}
};

class EulerPath{
	  Graph &graph;
	  Graph::WorkingGraph wg;
	  stack<int> path, unfinishedPath, finishedPath;
	  string pathByNameAndWeights;
	  int current;

	  bool visitVertex() {
        	//if there are no adjacency vertices left then visiting this vertex is useless.
        	//We have already remove his edges.
            if (wg.adjListSize(current) == 0) return false;
            //else we remove the next edge and take the adjacent vertex index.
            int edge = wg.removeNextEdge(current);
            //if there are some other edges we are not finish with that current 
            //vertex so we put it again into the unfinishedPath stack.
            if (wg.adjListSize(current) > 0) {
                unfinishedPath.push(current);
     
            }//else if the current vertex is on the top of the unfinishedPath stack we pop it.  
            else if (current == unfinishedPath.top()) {
                unfinishedPath.pop();
            }
            //we continue with the next vertex
            current = edge;
            return true;
        }



public:
	  EulerPath(Graph &graph_):graph(graph_),wg(graph.getWorkingGraph()),current(wg.getFirstOddDegreeVertex()){
	      if(wg.isEulerPath()){
			  unfinishedPath.push(current);
			  path.push(current);
	       
			  while(!unfinishedPath.empty()) {
					current = unfinishedPath.top(); unfinishedPath.pop();
					while (visitVertex()) {
						path.push(current);//we put the next vertex into the path
					}
					//докато стака с пътя е пълен и ( унфин стака  е празен  или  елемента на варха на пътя ne отговаря на този в ундин стека
					while (!path.empty() && ( unfinishedPath.empty() || !(path.top() == unfinishedPath.top() ) )) {
					   finishedPath.push(path.top());
					   path.pop();
					}
				}
			  while (!finishedPath.empty())
			  {
				  int index1;
				  index1 = finishedPath.top(); finishedPath.pop();
				  pathByNameAndWeights.append(graph.vertices[index1].lable);
				  if(finishedPath.empty()) continue;
				  pathByNameAndWeights.push_back(graph.vertices[index1].adjList[finishedPath.top()]);
			  }
		  }else{
			  pathByNameAndWeights ="IMPOSSIBLE";
		  }
	  }

	  
	  string getDNK(){
		  return pathByNameAndWeights;
	  }

};




int main(){

	ifstream in("input.txt");
	int N;
	in>>N;
	Graph graph; 
	for (int i = 0; i < N; i++)
	{
		string input;
		in>>input;
		graph.addEdge(input.substr(0,3),input.substr(4,7),input[3]);
	}

	EulerPath elp(graph);

	cout<<elp.getDNK()<<endl;

	return 0;
}
