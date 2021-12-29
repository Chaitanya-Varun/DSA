// Including essential libraries
#include <bits/stdc++.h>
#include <iostream>
#include <fstream>
using namespace std;

//Adding edges between the nodes
void addEdge(vector<int> Adj[], int i,int j){
	// cout<<"Link : "<<i<<" "<<j<<endl;
	Adj[i].push_back(j);
}
//Displaying the adjacency lists
void displayAdjList(vector<int> Adj[],int N){
	for(int i=0;i<N;i++){						//Iterating through the lists
		cout<< i << " : " ;						
		for(auto x: Adj[i]){
			cout<< "--->"<<x;
		}
		cout<<" "<<endl;
	}
}

//Finding the minimum path between the nodes
void solve(vector<int> Adj[],vector<int>& p,int s,int N){
	queue<int> q;								//Initiating the queue
	q.push(s);									//Setting the root node
	vector<bool> visited(N+1,false);			//Track if the node is already visited
	visited[s] = true;							//Making the root position visited
	int node;
	while(!q.empty()){							//BFS
		node = q.front();						//Select the node
		q.pop();
		for(auto& itr:Adj[node]){				//Look for neighbours
			if(!visited[itr]){					//If unvisited visit them
				q.push(itr);
				visited[itr]=true;				//Set the appropriate path
				p[itr] = node;
			}
		}
	}
}
//Retracing the path back
void reconstructPath(vector<int> Adj[],vector<string>& hash,vector<int>& p,vector<int>& path,int s,int e){
	int i;										//Variable for traversing the nodes
	for(i=e;i!=-1;i=p[i]){						//Getting the path from corresponding connections
		path.push_back(i);
	}
	reverse(path.begin(),path.end());			//Reversing the vector to get start to end

	if(path[0]==s){								//There is connection between the required nodes
		cout<<"Path : ";
		for(int i=0;i<path.size();i++){
			cout<<path[i]<<"-->";
		}
		cout<<"end"<<endl;
		cout<<"Distance Between them : "<<path.size()-1<<endl;
	}
	else{										//Unconnected nodes
		cout<<"No path found!"<<endl;
	}
}
//BFS function
void bfs(vector<int> Adj[],vector<string>& hash, int s,int e,int N){
	vector<int> p(N+1,-1);   					//Connections between nodes
	vector<int> path{};							//Path of traversal
	solve(Adj,p,s,N);							//Get the route between nodes
	reconstructPath(Adj,hash,p,path,s,e);		//Get the required path
}


int main(void){
	// Ready adjacency list
	string path = "fb-pages-sport.csv";				//Path
	int N = 13865;									//Number of Nodes
	vector<int>	Adj[N+1];							//Adjacency Lists
	fstream fin,fin2;                               //file streamer
	fin.open(path, ios::in);                     	//Opening the csv file
	int node1,node2;
	string node,line;
	if(fin.is_open()){							 //File open check
		while(getline(fin,line,'\n')){           //Reading the line
			int pos = line.find(','),end=line.find('\n'); //Finding the delimiter
			node = line.substr(0,pos);	 
			node1 = stoi(node);
			node = line.substr(pos+1,line.length()-node.length()-1); 
			if(node[node.length()-1]==(char)13) //Removing the carry return if present
				node = line.substr(pos+1,node.length()-1);
			node2 = stoi(node);
			// cout<<node1<<" "<<node2<<endl;
			addEdge(Adj,node1,node2);
		}
	}
	fin.close();
	// displayAdjList(Adj,N);
	vector<string> hash{};
	path = "fb-pages-sportNodes.csv";
	fin2.open(path, ios::in);                     	//Opening the csv file
	string name;
	int index=0;
	if(fin2.is_open()){							 //File open check
		while(getline(fin2,line,'\n')){           //Reading the line
			if(index==0){
				index++;
				continue;
			}
			int pos = line.find(','),end=line.find('\n'); //Finding the delimiter
			node = line.substr(pos+1); 
			hash.push_back(node);
			index++;
			// cout<<index<< " : " <<node<<endl;
		}
	}
	// BFS
	// int s = 12633;
	// int e = 12071;
	int s,e;
	//Input
	//Starting Node
	cout<<"Start Node : ";
	cin>>s;
	//Ending Node
	cout<<"End Node : ";
	cin>>e;
	bfs(Adj,hash,s,e,N);
}