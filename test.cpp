
#include "string"
#include "vector"
#include "unordered_map"
#include "queue"
#include "cstdlib"
#include "ctime"
#include <iostream>
#include "algorithm"
#include "stack"

using namespace std;

char VISITED = 'o';
char NOT_VISITED = '#';

class Solution{
public:
  // Definition for singly-linked list.
    void maze(vector<vector<char>>& map){
        //U unvisited, ' ' visited
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                map[i][j] = NOT_VISITED;
            }
        }
        _maze(map, 0, 0);
        _clean_maze(map);
    }

    void showMaze(vector<vector<char>>& map){
        for (int i = 0; i < map.size(); ++i)
        {
            for (int j = 0; j < map[0].size(); ++j)
            {
                cout<<map[i][j];
            }
            cout<<endl;
        }
    }
    //Use DFS
    void _maze(vector<vector<char>>& map, int i, int j){
        int direct[][2] = {{0,1}, {0,-1}, {-1,0}, {1,0}};
        int visitOrder[] = {0,1,2,3};
        //out of boundary
        if(i < 0 || j < 0 || i >= map.size() || j >= map[0].size()) return ;

        //visited, go back the the coming direction, return
        if(map[i][j] == VISITED) return ;

        //some neightbors are visited in addition to the coming direction, return
        //this is to avoid circles in maze
        //if(countVisitedNeighbor(map, i, j) > 1){
          if(cornersVisited(map, i, j)){
            //if(rand() % 2 == 0){
            //  map[i][j] = VISITED; // visited
            //}
            return;
          }
          //return ;
        //}

        map[i][j] = VISITED; // visited

        //shuffle the visitOrder
        shuffle(visitOrder, 4);

        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[visitOrder[k]][0];
            int nj = j + direct[visitOrder[k]][1];
            _maze(map, ni, nj);
        }
    }

    void _clean_maze(vector<vector<char>>& map){
        for (int i = 0; i < map.size(); ++i){
            map[i][0] = NOT_VISITED;
            map[i][map.size() - 1] = NOT_VISITED;
        }
        for (int i = 0; i < map[0].size(); ++i){
            map[0][i] = NOT_VISITED;
            map[map[0].size() - 1][i] = NOT_VISITED;
        }
    }

    int countVisitedNeighbor(vector<vector<char>>& map, int i, int j){
        int direct[][2] = {{1,0}, {-1,0}, {0,1}, {0,-1}};
        int count = 0;
        for (int k = 0; k < 4; ++k)
        {
            int ni = i + direct[k][0];
            int nj = j + direct[k][1];
            //out of boundary
            if(ni < 0 || nj < 0 || ni >= map.size() || nj >= map[0].size()) continue;
            if(map[ni][nj] == VISITED) count++;//visited
        }
        return count;
    }

    bool cornersVisited(vector<vector<char>>& map, int i, int j){
        int direct[][2] = {{1,0}, {1,1}, {0,1}, {-1,1}, {-1,0}, {-1,-1}, {0,-1}, {1,-1}};
        for (int k = 1; k < 8; k+=2)
        {
            int ni = i + direct[k][0];
            int nj = j + direct[k][1];
            int niprev = i + direct[((k-1) % 8)][0];
            int njprev = j + direct[((k-1) % 8)][1];
            int ninext = i + direct[((k+1) % 8)][0];
            int njnext = j + direct[((k+1) % 8)][1];

            //out of boundary
            if(ni < 0 || nj < 0 || ni >= map.size() || nj >= map[0].size()) continue;
            if(niprev < 0 || njprev < 0 || niprev >= map.size() || njprev >= map[0].size()) continue;
            if(ninext < 0 || njnext < 0 || ninext >= map.size() || njnext >= map[0].size()) continue;
            if(map[ni][nj] == VISITED && map[niprev][njprev] == VISITED && map[ninext][njnext] == VISITED) return true; //visited
        }
        return false;
    }

    void shuffle(int a[], int n){
        for (int i = 0; i < n; ++i)
        {
            swap(a[i], a[rand() % n]);
        }
    }
    void swap(int & a, int &b){
        int c = a;
        a = b;
        b = c;
    }
};
int main(int argc, char const *argv[])
{
	Solution s;
  int height = 20;
  int width = 20;
  srand(time(0));
  vector<char> row(width);
  vector<vector<char>> map;
  for (int i = 0; i < height; ++i)
  {
      map.push_back(row);
  }
  s.maze(map);
  s.showMaze(map);
  return 0;
}
