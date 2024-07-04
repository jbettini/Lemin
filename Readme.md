# Lemin
## Overview

Lemin is a project focused on simulating the movement of ants through a graph from a starting node to an end node. The goal is to find the combination of paths that transports the group of ants with the least cost, avoiding bottlenecks and ensuring only one ant occupies a node at any time.
## Features

-   Custom BFS to find all possible paths.
-   Custom heuristic-based algorithm to find the optimal path combination.
-   Two binaries available for generating graphs to solve.
-   A visualizer to view the ant movements.

## Prerequisites

-   A Unix-like operating system.
-   GCC (GNU Compiler Collection) installed.
-   Basic knowledge of C programming and graph theory.

## Installation
```
git clone https://github.com/jbettini/Lemin.git;
cd Lemin;
```

### Build

To make visualizer :
```
make visu
```
To make cli version :
```
make
```

### Usage

Run the compiled executable with the graph file as an argument:
```
./lemin <graph_file>
```
To generate graphs:
```
./generator_<os> <options>
```
To visualize
```
./Visualizer/visu-hex < <graph_file>
```

## Project Structure

-   src/: Source files.
-   include/: Header files.
-   Makefile: Build configuration.
-   generator*/: Binaries for generating graphs.
-   visualizer/: Binaries for visualizing the ant movements.