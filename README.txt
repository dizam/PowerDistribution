C++ program that implements a solution for supplying power throughout a grid of cities.
Using the file CreatePowerFile.cpp, one can create a random grid of cities based on the number of cities specified as a parameter and the random seed specified as a parameter.
The created power file contains the number of cities on the first line. Each line after that contains what city it describes, the production of power units it provides, the usage of power units the city uses, and the cities it is connected to in that order.
The program uses Breadth First Search to efficiently distribute the appropriate amount of power to each city, and is quick to find a solution even with a large number of cities.
This is not, however, the optimal transfer total and an alternative method could be used to find a more optimal transfer at the cost of a more exhaustive search.
The repository provides some example created grids. An example usage of the program is: router.out power10_5.csv.

