#include "runner.h"
#include <algorithm>
#include "levels.h"
#include <chrono>
#include <iostream>
#include <objidlbase.h>


node runner::find_solution() {
  std::priority_queue<node> queue;
  node initial(this->map_, this->rows_, this->cols_);
  queue.push(initial);
  this->nodes_created_++;

  while (!queue.empty() && !queue.top().objective()) {
    this->nodes_analyzed_++;
    auto no = queue.top();
	
    auto old_door_state = no.closedTiles;
    queue.pop();
	

    for (auto& op : this->ops_) {
      try {
        auto child = op(no, this->cost_, this->heuristic_);

        auto conditions = false;
        auto new_door_state = child.closedTiles;

        std::vector<point> reverse_pos;
        for (int i = child.pos.size() - 1; i >= 0; --i)
        {
          reverse_pos.push_back(child.pos.at(i));
        }

        if (this->mode_ == iterative) {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end() &&
                       std::find(no.parents.begin(), no.parents.end(),
                                 reverse_pos) == no.parents.end() &&
                       -child.cost <= this->limit_;
        } else {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end() &&
                       std::find(no.parents.begin(), no.parents.end(),
                                 reverse_pos) == no.parents.end();
        }

        if (conditions) {
          this->nodes_created_++;
		  if (old_door_state == new_door_state) {
			  child.parents.emplace_back(no.pos);
		  }
		  child.parents_print.emplace_back(no.pos);
		  
		  queue.emplace(child);
		  
        }
      } catch (...) {
      }
    }
  }

  if (!queue.empty()) {
    auto solution = queue.top();
    this->solution_size_ += solution.steps.size();
	  return solution;
  }

  throw std::exception();
}

long long runner::run(const int i, node& node_ret) {
  this->nodes_analyzed_ = 0;
  this->nodes_created_ = 0;
  this->solution_size_ = 0;

  const auto begin =
      std::chrono::steady_clock::now();

  for (auto j = 0; j < i; ++j)
  {
	  try {
		node_ret = find_solution();
	  }
	  catch (std::exception e) {
		  std::cout << "No solution found! \n";
	  }
	  if (this->steps) {
		  node_ret.printPoint();
	  }

	  
	
  }
  const auto end = std::chrono::steady_clock::now();
  
  return std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count();
}

runner::runner() {
  this->ops_ = {roll_up, roll_down, roll_left, roll_right};
  this->mode_ = dfs;
  this->heuristic_ = none;
  this->map_ = LVL1;
  this->cols_ = 7;
  this->rows_ = 5;
  this->cost_ = inc;
  this->limit_ = -1;
  
}

runner::runner(const mode mode, const std::vector<int>& map, const int rows,
               const int cols, bool steps)
    : runner() {
  this->mode_ = mode;
  this->map_ = map;
  this->cols_ = cols;
  this->rows_ = rows;
  this->steps = steps;
  switch(mode) {
  case bfs:
	  this->cost_ = inc;
	  break;
  case dfs:
  case iterative :
	  this->cost_ = dec;
	  break;
  case greedy :
	  this->cost_ = greedy_;
	  break;
  case a_star :
	  this->cost_ = a_star_;
	  break;
  default:
	  break;
  }
}

runner::runner(const mode mode, const heuristic heuristic,
               const std::vector<int>& map, const int rows, const int cols, bool steps)
    : runner(mode, map, rows, cols, steps) {
  this->heuristic_ = heuristic;
}

runner::runner(const mode mode, const int limit,
               const std::vector<int>& map, const int rows, const int cols, bool steps)
    : runner(mode, map, rows, cols, steps) {
  this->limit_ = limit;
}

runner::~runner() = default;

int runner::get_nodes_analyzed() const
{ return nodes_analyzed_; }

int runner::get_nodes_created() const { return nodes_created_; }

int runner::get_solution_size() const { return this->solution_size_; }
