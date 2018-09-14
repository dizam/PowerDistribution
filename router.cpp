// Author: Sean Davis

#include "router.h"
#include "RouterRunner.h"
#include <iostream>
#include "BinaryHeap.h"
#include "QueueAr.h"
#include <cstring>


using namespace std;

Router::Router(CityInfo *infos, int numCities) 
{
  numVertex = numCities;
  data = new CityInfo [numCities];
  memcpy(data, infos, sizeof(CityInfo) * numCities);  
} // Router()

int Router::setTransfers(Transfer **transfers)
{
  Vertex* cities  = new Vertex[numVertex];
  BinaryHeap minConnect (numVertex);
  int total = 0;

  for (int i = 0; i < numVertex; i++)
    {

          cities[i].index = i;
	  cities[i].city = data[i];
	  cities[i].indexPath = new int [numVertex];
          cities[i].usedUp = 0;
          cities[i].visited = false;
          cities[i].pathLength = 25001;
          cities[i].seen = false;
    if (data[i].production < data[i].usage)
      minConnect.insert(cities[i]);
    }
  while (!minConnect.isEmpty())
  {
  Vertex dest = minConnect.findMin();
  minConnect.deleteMin();
  circleMethod(transfers, dest.index, cities, &total);    
  }
  return total;  // should be set to total of all transfers.
}  // setTransfers

void Router::makeTransfers(Transfer **transfers, int* indexPath, int count, int amountFlow, int* total, int* needed, Vertex *cities)
{
  while (count > 0)
  {
    int sourceIndex = indexPath[count];
    int destIndex = indexPath[count-1];
    int adjList = 0;
    for (int i = 0; i < 8; i++)
    {
        if (cities[sourceIndex].city.adjList[i] == destIndex)
	{
        adjList = i;
	break;
	}
    }
    transfers[sourceIndex][adjList].destCity = destIndex;
    transfers[sourceIndex][adjList].amount+= amountFlow;
    *total += amountFlow;
    cities[sourceIndex].usedUp += amountFlow;
    count--;
  }
    *needed -= amountFlow;
}

void Router::circleMethod (Transfer **transfers, int dest, Vertex* cities, int* total)
{
  Queue near (numVertex);
  int resetVisit[numVertex];
  int resetPath[numVertex];
  int resetVisitCount = 0;
  int resetPathCount = 0;
  int needed = cities[dest].city.usage - cities[dest].city.production;
  cities[dest].indexPath[0] = dest;
  cities[dest].pathLength = 0;
  resetPath[resetPathCount] = dest;
  resetPathCount++;
  cities[dest].visited = true;
  resetVisit[resetVisitCount] = dest;
  resetVisitCount++;
  near.enqueue(dest);
  while (needed > 0)
    {
    Vertex start = cities[near.dequeue()];

    for (int p = 0; p < start.city.adjCount; p++)
    {

        if (cities[start.city.adjList[p]].visited)
	{
        continue;
	}
        cities[start.city.adjList[p]].visited = true;
        resetVisit[resetVisitCount] = cities[start.city.adjList[p]].index;
        resetVisitCount++;
        resetPath[resetPathCount] = cities[start.city.adjList[p]].index;
        resetPathCount++;
	changePaths(cities, start, p); 
        near.enqueue(start.city.adjList[p]);
      int maxFlow = cities[start.city.adjList[p]].city.production - cities[start.city.adjList[p]].city.usage;
      maxFlow -= cities[start.city.adjList[p]].usedUp;
      if (maxFlow <= 0)
	{
	  continue;
	}

      if (maxFlow >= needed)
	{
          int amountFlow = needed;
          makeTransfers(transfers, cities[start.city.adjList[p]].indexPath, cities[start.city.adjList[p]].pathLength, amountFlow, total, &needed, cities);
        }
       
      else
	{
          makeTransfers(transfers, cities[start.city.adjList[p]].indexPath, cities[start.city.adjList[p]].pathLength, maxFlow, total, &needed, cities);
	}
    }
      }

  resetValues(resetVisit, resetPath, resetVisitCount, resetPathCount, cities);    
}

void Router::changePaths(Vertex* cities, Vertex start, int p)
{

      bool changePath = false;
      int sourceIndex = start.city.adjList[p];
     if (cities[sourceIndex].pathLength > start.pathLength + 1)
      {
      cities[sourceIndex].pathLength = start.pathLength + 1;
      changePath = true;
      }
      Vertex source = cities[start.city.adjList[p]];
  
      if (changePath)
	{
          memcpy(cities[sourceIndex].indexPath, start.indexPath, sizeof(int) * source.pathLength);
          cities[sourceIndex].indexPath[source.pathLength] = source.index;
	}

}

void Router::resetValues(int* resetVisit, int* resetPath, int resetVisitCount, int resetPathCount, Vertex* cities)
{

  for (int r = 0; r < resetVisitCount; r++)
  {
    cities[resetVisit[r]].visited = false;
  }
  for (int rp = 0; rp < resetPathCount; rp++)
  {
    cities[resetPath[rp]].pathLength = 25001;
  }
}

