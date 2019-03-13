#include "runner.h"
#include <algorithm>
#include "levels.h"
#include <chrono>


node runner::find_solution(bool output, int limit) {
  std::priority_queue<node> queue;
  node initial(this->map_, this->rows_, this->cols_);
  queue.push(initial);

  while (!queue.empty() && !queue.top().objective()) {
    auto no = queue.top();
    queue.pop();

    if (no.objective()) no.print();

    for (auto& op : this->ops_) {
      try {
        auto child = op(no, this->cost_, this->heuristic_);

        auto conditions = false;

        if (this->mode_ == iterative) {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end() &&
                       child.cost <= limit;
        } else {
          conditions = std::find(no.parents.begin(), no.parents.end(),
                                 child.pos) == no.parents.end();
        }

        if (conditions) {
          /*
            for (size_t j = 0; j < child.steps.size(); j++)
            {
              std::cout << child.steps.at(j) << "  ";
            }
            std::cout << "\t" << child.parents.size() << std::endl;
           */
          child.parents.emplace_back(no.pos);
          queue.emplace(child);
        }
      } catch (...) {
      }
    }
  }

  if (!queue.empty()) return queue.top();

  throw std::exception("NO MORE NODES");
}

long long runner::run(const int i)
{
  const auto begin =
      std::chrono::steady_clock::now();

  for (auto j = 0; j < i; ++j)
  {
    find_solution(true, NULL);
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
}

runner::runner(const mode mode, const std::vector<int>& map, const int rows,
               const int cols)
    : runner() {
  this->mode_ = mode;
  this->map_ = map;
  this->cols_ = cols;
  this->rows_ = rows;
}

runner::runner(const mode mode, const heuristic heuristic,
               const std::vector<int>& map, const int rows, const int cols)
    : runner(mode, map, rows, cols) {
  this->heuristic_ = heuristic;
}

runner::~runner() = default;
