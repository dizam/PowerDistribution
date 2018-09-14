#ifndef ROUTER_H
#define	ROUTER_H

#include "RouterRunner.h"
#include "vector.h"

typedef struct
{
  int index;
    CityInfo city;
 
  int usedUp;
  int* indexPath;
  bool visited;
  int pathLength;
  bool seen;
}Vertex;

class Router {
  int numVertex;
  CityInfo *data;  
public:
  Router(CityInfo *infos, int numCities);
  int setTransfers(Transfer **transfers);
  void makeTransfers(Transfer **transfers, int* indexPath, int count, int amountFlow, int *total, int *needed, Vertex* cities);
  void circleMethod (Transfer **transfers, int start, Vertex* cities, int* total);
  void changePaths(Vertex* cities, Vertex start, int p);
  void resetValues(int* resetVisit, int* resetPath, int resetVisitCount, int resetPathCount, Vertex* cities);
}; // class Router 

#endif	// ROUTER_H

