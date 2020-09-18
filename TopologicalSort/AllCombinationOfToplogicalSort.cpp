using namespace std;
#include <algorithm>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>

class AllTaskSchedulingOrders {
 public:
    void printAllTopologicalSort(unordered_map<int,vector<int>> &g, const vector<int> source, vector<int>inDegree, 
    vector<int> sortedOrder){
		if (!source.empty()){
			for (auto v:source){
				sortedOrder.emplace_back(v);
				vector<int> sourceForNext = source;
                // as current vertex is already saved in sortedOrder. removing the current vertex cases are 
                // being considered in current execution. all the other element used for next calls/
				sourceForNext.erase(find(sourceForNext.begin(), sourceForNext.end(), v));
				auto children = g[v];
				for (auto n: children){
					if (--inDegree[n] == 0) sourceForNext.push_back(n); // save the source for next call.
				}
				printAllTopologicalSort(g, sourceForNext, inDegree, sortedOrder);
				sortedOrder.erase(find(sortedOrder.begin(), sortedOrder.end(), v));
                // for backtrack all the degree are restored for the next call.
				for (auto n: children){
					++inDegree[n];
				}
			}			
		}
        // if not equal either we have cyclic dependency in the graph or we have not processed all the not yet
		if (inDegree.size() == sortedOrder.size()){
			for (auto &s: sortedOrder) cout<<s<<" ";
			cout<<endl;
		}
	}
	void printOrders(int tasks, vector<vector<int>> &prerequisites) {
        if(tasks <= 0) return;
        unordered_map<int,vector<int>> g;
        vector<int> inDegree(tasks);
        vector<int> sortedOrder;
        vector<int> source;
        for (auto &p:prerequisites){
            inDegree[p[1]]++;
            g[p[0]].push_back(p[1]);
        }

        for (int i = 0; i < inDegree.size(); ++i){
            if (!inDegree[i]) source.emplace_back(i);
        }
        printAllTopologicalSort(g, source, inDegree,sortedOrder);
    } 
};

int main(int argc, char *argv[]) {
  vector<vector<int>> vec = {{0, 1}, {1, 2}};
  AllTaskSchedulingOrders().printOrders(3, vec);
  cout << endl;

  vec = {{3, 2}, {3, 0}, {2, 0}, {2, 1}};
  AllTaskSchedulingOrders().printOrders(4, vec);
  cout << endl;

  vec = {{2, 5}, {0, 5}, {0, 4}, {1, 4}, {3, 2}, {1, 3}};
  AllTaskSchedulingOrders().printOrders(6, vec);
  cout << endl;
}