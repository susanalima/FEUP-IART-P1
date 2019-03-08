#pragma once
#include "node.h"
#include "model.h"
#include <stdexcept>
#include <iostream>


node::node(const std::vector<int> &initializer, const int &rows, const int &cols) {
  this->cost = 0;
  this->pos = {};
  this->map = {};
  this->cols = cols;
  this->rows = rows;

  const int length = initializer.size();
  if (length != rows * cols)
  {
    throw std::invalid_argument("number of tiles doesn't match rows*cols");
  }

  for (auto i = 0; i < length; ++i)
  {
    const auto elem = initializer[i];
    if (elem == block_tile)
    {
         
      const point p(i % cols, i / cols);
      this->pos.push_back(p);
      this->map.emplace_back(block_tile);
      

    }
    else if (elem == target_tile)
    {
      
      const point t(i % cols, i / cols);
      this->target = t;
      this->map.emplace_back(target_tile);
      
    } 
    else if (elem == empty_tile)
    {
      this->map.emplace_back(empty_tile);
    }
  }

}


node::~node()
= default;

void node::print()
{
  auto i = 0;
  for (auto tile : this->map)
  {
    i++;
    char c;
    switch (tile)
    {
      case empty_tile: c = 'O';  break;
      case target_tile: c = 'T';  break;
      case block_tile: c = 'M'; break;
      default: c = 'O';
    }

    std::cout << c;
    if (i % this->cols == 0) std::cout << std::endl;
  }
}

int get_index(const int& x, const int& y, const int &cols)
{
  return x + y * cols;
}
