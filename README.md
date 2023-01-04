# DijkstraAlgorithm
Program based on Dijkstra Algorithm which allows you to find the cheapest connections between the cities depending on the ticket cost of the train or bus.

The input of the program is:
n - number of the cities; m - number of the train connections; k - source city; a - train cost; b - bus cost;
Each of the following 'm' lines has two inputs - Ui (start) and Vi which are number of the cities connected with rails directly.
The value of Ui and Vi cannot be the same nor bigger than number of the cities, which is why the usage of the square matrix as a graph connection seems to be the most effective one.

The output of the program is:
n lines, each of them with one value which is the cheapest way to get from the source city to 'i' (i=1, 2, ..., n) city. The k-th line should be equal zero naturally, because you are not able to move from the same city to the same city.

The documentation is written in polish. Short explanations next to most of the crucial operations helping you understand what is going on in the code!
