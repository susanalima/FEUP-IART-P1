#pragma once
#include <vector>
#include <string>
#include "model.h"

class point
{
public:
  int x;
  int y;

  point(const int& x, const int& y)
  {
    this->x = x;
    this->y = y;
  }
  point()
  {
    this->x = -1;
    this->y = -1;
  }
};

class node
{
public:
  int cost;
  std::vector<model> map;
  std::vector<point> pos;
  point target;

  std::vector<std::vector<point>> parents = {};
  std::vector<std::string> steps = {};

  int cols;
  int rows;


  node(const std::vector<int> &initializer, const int &rows, const int &cols);
  ~node();

  bool operator<(const node& rhs) const;
  bool operator==(const node& rhs) const;
  bool objective() const;

  void print();
};

int get_index(const int &x, const int &y, const int &cols);