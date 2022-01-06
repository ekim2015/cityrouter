#include "router.h"
#include "QueueAr.h"
#include <iostream>
using namespace std;
Router::Router(const Map1000 *map, int width) : mapwidth(width)
{
    map2 = new Map1000;
    // memcpy(map2, map, sizeof(Map1000)); 

    //origin is lower left corner
    for(int y = width - 1; y >= 0; y--)
    {
        for(int x = 0; x < width; x++)
        {
            map2->map1000[x][y] = map->map1000[x][y];
            //visited[x][y] = false;
        }
    }
} // Router()

Router::~Router()
{
    delete map2; 
}  // ~Router()

void Router::findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount)
{
    int count = 0;
    pathCount = 0;  
    Queue<HeapInfo> q(mapwidth*mapwidth);
    //pathcount is number of edges in the paths array
    //cityPos is an array of city locations 
    //cityCount is num of cities 
    //paths array to store edges

    //path starts at first found city
    //needs to account for all 8 edges (minus the 9th where pv was)

    //int x = ; 
    //int y = ; 
    //int newx, newy; 
    int newx = cityPos[0].x; 
    int newy = cityPos[0].y; 
    //q.enqueue(HeapInfo(x,y));
    //cout << "x: " << x << " y: " << y << endl;
    for (int i = 1; i < cityCount; i++)
    { 
        //newx = x; 
        //newy = y; 
        while (newx != cityPos[i].x || newy != cityPos[i].y)
        {
            if (newx < cityPos[i].x)
                newx++;
            if (newx > cityPos[i].x)
                newx--; 

            if (newy < cityPos[i].y)
                newy++;
            if (newy > cityPos[i].y)
                newy--; 
            q.enqueue(HeapInfo(newx,newy));
            HeapInfo test = q.getFront();
            cout << test.x << " " << test.y << endl;
            count++; 
            //cout << "x: " << newx << " y: " << newy << endl;
        }

        
    }
    
    HeapInfo source; 
    paths[pathCount].startX = cityPos[0].x; 
    paths[pathCount].startY = cityPos[0].y; 
    while (count > 0)
    {
        source = q.dequeue();
        
        paths[pathCount].endX = source.x; 
        paths[pathCount].endY = source.y; 

        pathCount++; 

        paths[pathCount].startX = source.x; 
        paths[pathCount].startY = source.y; 
        count--; 
    }

} // findRoutes()
