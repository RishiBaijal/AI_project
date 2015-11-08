AI: Optimizing longevity and robustness in Conway's Game of life 
-----------------------------------

INTRODUCTION
===========

In 1970, British mathematician John Conway conceptualized a cellular automaton in an attempt to simplify John von Neumann’s ideas of a hypothetical machine that could create copies of itself. This came to be known as “The Game of Life”.
The universe of this game consists of an infinite, two­dimensional and orthogonal grid of square cells. Each of these can be in one of the following possible states ­ alive or dead. Each cell interacts with cells that can be horizontally, vertically or diagonally adjacent to it (also called neighbours). Neighbours can transform between states as per the following rules:

1. Death by under­population: Any cell with fewer than two live neighbours dies.

2. Death by overpopulation: Any live cell with more than three neighbours dies.

3. Reproduction: Any dead cell with exactly three neighbours becomes alive.

4. Transition to the next generation: Any live cell with two or three neighbours moves on to
the next generation.

These rules are consistently applied over a discretized interval of time where each subsequent time unit produces the subsequent generation. One can define additional rules for the cellular automata to obtain different behavior over generations.

PROBLEM DESCRIPTION
==================

The Conway’s game of life, as described above, has quite a lot of potential for AI applications. We shall treat this as a cellular automata and use apply the genetic algorithm in order to explore how we can maximize life for structures that structures that are not permanent (for example blocks) last for a longer number of generations.

MOTIVATION FOR CHOOSING THIS PROBLEM
==================================

By choosing this problem, we feel that we will be tackling a unique and interesting idea as a part of this project. To the best of our knowledge, the existing literature in AI does not contain detailed descriptions of the role that Conway’s game of life plays in this field. Given the fame that this enjoys and the impact it has had in the field of theoretical mathematics and cellular automata, we feel that it is only appropriate to investigate the various possibilities in the field of AI.

PLAN OF ACTION
==============

We shall be using a performance function in order to determine how we can maximize life. In order to do so, we define the following metrics:

a) maximum number of cells at k units of time

b) maximum cell life in the grid over k intervals of time

We pick the one which is higher, and then the genetic algorithm processes the future generations as per the value computed by the performance function.

DELIVERABLES
============

We ultimately plan to deliver a fully functional AI that works on a normal game of life as defined by the four rules stated in the introduction of this proposal. This code will allow you to change the initial configuration of the world, and as per the modifications, display the final output on the main console.
