# FEUP-IART-P1

Second project developed for Artificial Intelligence class.

Made in colaboration with [Gonçalo Santos](https://github.com/gregueiras) and [Afonso Azevedo](https://github.com/4-Z3r0).

## Specification

Implementation of an intelligent agent, in the C ++ language, for the resolution of Bloxorz game levels.

Bloxorz is a puzzle whose objective is to transport a block through successive bearings, from a starting house to a destination house. The board is divided into several squares, its size and composition varying between different levels.

The block can move up, down, left and right and can be positioned either upright, occupying only one square of the game board, or lying down, occupying two spaces on the board. The puzzle is only completed when the block is positioned upright in the target square. There are also some bonuses that allow the block to be directly transported from one house to another (teleportation) or to unlock / block additional houses.

The search algorithms implemented were Depth-First Search (DFS), Breadth-First Search (BFS), greedy, Iterative Deepening Search and A *.
