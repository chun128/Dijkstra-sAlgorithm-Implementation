# Dijkstra-sAlgorithm-Implementation
Implement the Dijkstra’salgorithm to find the shortest distance from the source to the target <br/>
Use the “parent” information to reconstruct the shortest path from the source to the target <br/>

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

Develop on Dev C++

[Here is the link for Dev C++ downloading](https://sourceforge.net/projects/orwelldevcpp/)

## Running the tests

![image](https://github.com/chun128/Dijkstra-sAlgorithm-Implementation/blob/master/readme%20picture/test%20case.JPG)

Given:<br/>
* The size of a grid map<br/>
* The coordinates of a source and a target<br/>
* Horizontal/vertical edge weights<br/>

Parse the input file: <br/>
```
Usage: ./dij [input_case]
```

![image](https://github.com/chun128/Dijkstra-sAlgorithm-Implementation/blob/master/readme%20picture/dij_initial%20map.jpg)

## Execution Result

Show the routing map, d map and pi map as below

d map shows the total cost accumulate from start point to end point<br/>
pi map shows the parent point for each point<br>

![image](https://github.com/chun128/Dijkstra-sAlgorithm-Implementation/blob/master/readme%20picture/final%20map.jpg)


## Built With

* [Dev C++](http://www.bloodshed.net/devcpp.html) - The compiler used
