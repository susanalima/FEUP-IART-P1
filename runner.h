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
  int limit_;
  bool steps;

  cost_function cost_;

  node find_solution();

  int nodes_analyzed_ = 0;
  int nodes_created_ = 0;
  int solution_size_ = 0;

 public:
	 //corre o (2)
	// node run();
  long long run(int i, node& node_ret);
  int get_solution_size() const;

  runner();
  runner(mode mode, const std::vector<int>& map, int rows, int cols, bool steps);
  runner(mode mode, heuristic heuristic, const std::vector<int>& map, int rows, int cols, bool steps);
  runner(mode mode, int limit, const std::vector<int>& map, int rows, int cols, bool steps);
  
  ~runner();

  int get_nodes_analyzed() const;
  int get_nodes_created() const;
};
