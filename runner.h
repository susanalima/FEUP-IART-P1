#pragma once
#include "operators.h"
#include <queue>

class runner {
  std::vector<int> map_;
  int rows_;
  int cols_;

  std::vector<operators> ops_;
  std::priority_queue<node> queue_;
  mode mode_;
  heuristic heuristic_;

  cost_function cost_;

  node find_solution(bool output, int limit);

  int nodes_analyzed_ = 0;

 public:
	 //corre o (2)
	// node run();
  long long run(int i, node& node_ret);

  runner();
  runner(mode mode, const std::vector<int>& map, int rows, int cols);
  runner(mode mode, heuristic heuristic, const std::vector<int>& map, int rows, int cols);
  
  ~runner();

  int getNodes_Analyzed();


};
