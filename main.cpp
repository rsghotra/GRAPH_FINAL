#define MAXV 1000 /*maximum number of vertices*/
#include<iostream>
#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<queue>
#include<list>
#include<stack>
using namespace std;

//assume n vertices, m edges; theta(n + m); m << n^2(sparse vs dense graph);
//#1: Graph Representation: Adj List
//adjacency list o(m+n)

class Graph {
private:
	int num_vertices;
	list<int>* edges;
public:
	Graph(int num_vertices) {
		this->num_vertices = num_vertices;
		edges = new list<int>[this->num_vertices];
	}
	
	void AddEdge(int u, int v, bool undir = false) {
		this->edges[u].push_back(v);
		if(undir) {
			this->edges[v].push_back(u);
		}
	}
	
	void PrintEdgeList() {
		//iterate over all the rows;
		for(int i = 0; i < this->num_vertices; i++) {
			cout << i << "-->";
			for(int node:  this->edges[i]) {
				cout << node << ", ";
			}
			cout << endl;
		}
	}
};

class Node {
public:
	string name;
	list<string> neighbors;
	Node(string name) {
		this->name = name;
	}
};

class Graph2 {
	unordered_map<string, Node*> graph;
public:
	Graph2(vector<string>& cities) {
		for(auto city: cities) {
			graph[city] = new Node(city);
			
		}
	}
	void AddEdge(string u, string v, bool undir = false) {
		graph[u]->name = u;
		graph[u] = new Node(v);
		if(undir) {
			graph[v]->name = v;
			graph[v]->neighbors.push_back(u);
		}
	}
	
	void PrintGraph() {
		for(auto entry: graph) {
			cout << entry.first << "-->";
			auto neighbors = entry.second->neighbors;
			for(auto node: neighbors) {
				cout << node << ", ";
			}
			cout << endl;
		}
	}
};

//#2: Graph Traversal: BFS
void BFS(unordered_map<char, vector<char>>& graph, char source) {
	queue<char> inputs;
	inputs.push(source);
	while(!inputs.empty()) {
		auto entry = inputs.front();
		inputs.pop();
		cout << entry << " ";
		vector<char> children = graph[entry];
		for(auto child: children) {
			inputs.push(child);
		}
	}
}

//
//#2: Graph Traversal: DFS
void DFS(unordered_map<char, vector<char>>& graph, char source) {
	stack<char> stk;
	stk.push(source);
	while(!stk.empty()) {
		auto entry = stk.top();
		stk.pop();
		cout << entry << " ";
		vector<char> children = graph[entry];
		for(auto child: children) {
			stk.push(child);
		}
	}
}

void DFSRecursive(unordered_map<char, vector<char>>& graph, char source) {
	cout << source << endl;
	vector<char> children = graph[source];
	for(auto child: children) {
		DFS(graph, child);
	}
}

//#CountCounnectedComponents - BFS & DFS Solution

bool ExploreForConnectedComponentsDFS(unordered_map<int, vector<int>>&graph, int source, unordered_set<int>& visited) {
  if(visited.find(source) != visited.end()) {
    return false;
  }
  visited.insert(source);
  vector<int> children = graph[source];
  for(auto child: children) {
    ExploreForConnectedComponentsDFS(graph, child, visited);
  }
  return true;
}

bool ExploreForConnectedComponentsBFS(unordered_map<int, vector<int>>&graph, int source, unordered_set<int>& visited) {
  if(visited.find(source) != visited.end()) {
    return false;
  }
  queue<int> inputs;
  inputs.push(source);
  while(!inputs.empty()) {
    auto entry = inputs.front();
    inputs.pop();
    visited.insert(entry);
    vector<int> children = graph[entry];
    for(auto child: children) {
      if(visited.find(child) == visited.end()) {
        inputs.push(child);
      }
    }
  }
  return true;
}

int CountConnectedComponents(unordered_map<int, vector<int>>&graph, bool dfs = true) {
  int count = 0;
  unordered_set<int> visited;
  //will do marking + processing in helper funcion
  for(auto entry: graph) {
    if(dfs) {
      if(ExploreForConnectedComponentsDFS(graph, entry.first, visited) == true) {
        count++;
      }
    } else {
      if(ExploreForConnectedComponentsBFS(graph, entry.first, visited) == true) {
        count++;
      }
    }
  }
  return count;
}

void CountConnectedComponents() {
  unordered_map<int, vector<int>> graph = unordered_map<int, vector<int>>();
  graph[1] =  vector<int>{2};
  graph[2] =  vector<int>{1};
  graph[3] =  vector<int>{};
  graph[4] =  vector<int>({6});
  graph[5]=   vector<int>({6});
  graph[6] =  vector<int>({4,5,7,8});
  graph[7]=   vector<int>({6});
  graph[8]=   vector<int>({6});
  cout << "\nNumber of Connected Components: " << CountConnectedComponents(graph) << endl;
}


int LargestComponetDFS(unordered_map<int, vector<int>>&graph, int source, unordered_set<int>& visited) {
  if(visited.find(source) != visited.end()) {
    return 0;
  }

  visited.insert(source);
  int size = 1;
  vector<int> children = graph[source];
  for(auto child: children) {
    size += LargestComponetDFS(graph, child, visited);
  }
  return size;
}
int LargestComponetBFS(unordered_map<int, vector<int>>&graph, int source, unordered_set<int>& visited) {
  return 0;
}

int LargestComponet(unordered_map<int, vector<int>>&graph, bool dfs = true) {
  unordered_set<int> visited;
  int maxComponentSize = INT32_MIN;
  int currentComponentSize = 0;
  for(auto entry: graph) {
    if(dfs) {
      currentComponentSize =  LargestComponetDFS(graph, entry.first, visited);      
    } else {
      currentComponentSize  = LargestComponetBFS(graph, entry.first, visited);
    }
    maxComponentSize = max(maxComponentSize, currentComponentSize);
  }
  return maxComponentSize;
}

void LargestComponet() {
  unordered_map<int, vector<int>> graph = unordered_map<int, vector<int>>();
  graph[0] =  vector<int>{8,1,5};
  graph[1] =  vector<int>{0};
  graph[2] =  vector<int>{3,4};
  graph[3] =  vector<int>({2,4});
  graph[4] =  vector<int>({3,2});
  graph[5] =  vector<int>({0,8});
  graph[8] =  vector<int>({0,5});
  cout << "\nLargest Connected Component: " << LargestComponet(graph, false) << endl;
}

int main() {
  CountConnectedComponents();
  LargestComponet();
  return 0;
}