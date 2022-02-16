// Author: Sean Davis

#ifndef ROUTER_H
  #define ROUTER_H

#include "RouterRunner.h"
class HeapInfo
{
  public:
  //location on map grid
  int x; 
  int y; 

  int dv; //distance in elevation from previous edge
  HeapInfo *pv; 

  bool operator< (const HeapInfo &rhs) const {return dv < rhs.dv;};
  HeapInfo() {};
  HeapInfo(int x_, int y_, int dv_ , HeapInfo *pv_) : 
      x(x_), y(y_), dv(dv_), pv(pv_) {};

};

class Router
{
public:
  Map1000 *map2; 
  int mapwidth; 
  bool visited[1000][1000]; 
  HeapInfo* info; 
  Router(const Map1000 *map, int width);
  ~Router();
  void findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount);
};


#endif
