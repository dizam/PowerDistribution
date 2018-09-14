C++ program that implements a solution for supplying power throughout a grid of cities.
Using the file CreatePowerFile.cpp, one can create a random grid of cities based on the number of cities specified as a parameter and the random seed specified as a parameter.
The created power file contains the number of cities on the first line. Each line after that contains what city it describes, the production of power units it provides, the usage of power units the city uses, and the cities it is connected to in that order.
The program uses Breadth First Search to efficiently distribute the appropriate amount of power to each city, and is quick to find the solution even with a large number of cities.

