#include "router.h"
#include "BinaryHeapArray.h"
#include <iostream>
#include <cstring>
using namespace std;
Router::Router(const Map1000 *map, int width) : mapwidth(width)
{
    info = new HeapInfo[mapwidth*mapwidth*4]; //max number of edges 
    map2 = new Map1000;
    // memcpy(map2, map, sizeof(Map1000)); 

    //origin is lower left corner
    for(int y = width - 1; y >= 0; y--)
    {
        for(int x = 0; x < width; x++)
        {
            map2->map1000[x][y] = map->map1000[x][y];
            visited[x][y] = false;
        }
    }
} // Router()

Router::~Router()
{
    delete map2; 
}  // ~Router()

void Router::findRoutes(const CityPos *cityPos, int cityCount, Edge *paths, int &pathCount)
{
    BinaryHeap<HeapInfo> heap(mapwidth*mapwidth); 
    int citiesVisited = 0; 
    //pathcount is number of edges in the paths array
    //cityPos is an array of city locations 
    //cityCount is num of cities 
    //paths array to store edges

    //path starts at first found city
    //needs to account for all 8 edges (minus the 9th where pv was)


    // only bfs forward: up, down, right, northwest, southwest 
    // 0 = stay column. 1 = go right. 
    int horizontal [5] = {0,0,1,1,1};
    // -1 = down 1 row. 0 = stay in row. 1 = up 1 row
    int vertical [5] = {1,-1,0,1,-1}; 
    int x = mapwidth; 
    int y = 0; 
    //find the nearest city 
    for (int i = 0; i < cityCount; i++)
    {
        if (x > cityPos[i].x)
        {
            x = cityPos[i].x; 
            y = cityPos[i].y; 
        } if (x == 0) break;
    }
    
    // cout << "city: " << x << " " << y << endl;
   ;
    heap.insert(HeapInfo (x,y,0, NULL)); //first city to be inserted with distance zero.
    

    HeapInfo source; 
    HeapInfo *temp; 
    int newx, newy; 
    while (heap.currentSize != 0 && citiesVisited < cityCount )
    {
        heap.deleteMin(source);
        if (visited[source.x][source.y]) continue;
        visited[source.x][source.y] = true; 

        
        //cout << "heap popped: (" << source.x << ", " << source.y << ") -> " 
        //  << map2->map1000[source.x][source.y] << " dv: " << source.dv << endl;
        //if (source.pv)
        //   cout << "source check: (" << source.pv->x << "," << source.pv->y << ")" << endl;
        //if edge is actually a city, increment city count
        for (int i = 0; i < cityCount; i++)
            if (source.x == cityPos[i].x && source.y == cityPos[i].y) 
            {
                citiesVisited++;
                    //cout << "city found" << source.x << source.y << endl;
                    //temp = new HeapInfo(source.x, source.y, source.dv, source.pv); 
                // if (citiesVisited > 2)
                while ( source.pv )
                {
                    paths[pathCount].startX = source.pv->x;
                    paths[pathCount].startY = source.pv->y;

                    paths[pathCount].endX = source.x;
                    paths[pathCount].endY = source.y;

                    cout << "START: (" << paths[pathCount].startX << ", " << paths[pathCount].startY << ") " << map2->map1000[paths[pathCount].startX][paths[pathCount].startY];
                    cout << " END: (" << paths[pathCount].endX << ", " << paths[pathCount].endY  << ") " << map2->map1000[paths[pathCount].endX][paths[pathCount].endY]<< endl;
                    pathCount++; 
                    source = *(source.pv);
                }
                break; 
                //cout << "city found ! " << source.x << " " <<source.y <<  " " << source.dv <<endl;
            }
        //find x and y pos for all the adjacent neighbors
        for (int pos = 0; pos < 5; pos++)
        {
            newx = source.x+horizontal[pos];
            newy = source.y+vertical[pos];
            if (newx < 0 || newx >= mapwidth || newy < 0 || newy >= mapwidth)
                continue;  
            if (visited[newx][newy]) continue; 
            
            //cout << "entered: (" << newx <<", " <<newy << ") = " << map2->map1000[newx][newy] << endl;

            int initial = map2->map1000[ source.x ] [ source.y ];
            int final =  map2->map1000[ newx] [ newy ];
            int change = 10 + (final - initial) * (final - initial) ;
            //cout << " change is " << change << endl;
            temp = new HeapInfo(source.x, source.y, source.dv, source.pv);
            heap.insert(HeapInfo(newx,newy,source.dv + change, temp)); 
        }
    }

} // findRoutes()
