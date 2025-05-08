#pragma once
#include<iostream>
using namespace std;
bool checkCollision(char** lvl, int player_x, int player_y, int height, int width)
{
    int row = player_y / 64;
    int col = player_x / 64;
    if (row < 0 || row >= height || col < 0 || col >= width)
    {
        return false; 
    }
    return !(lvl[row][col] == 'e' || lvl[row][col] == 'w' || lvl[row][col] == 'q' || lvl[row][col] == 'p');
}

 bool checkCollisionExceptSpikes(char** lvl, int player_x, int player_y,int height,int width)
{
     int row = player_y / 64;
     int col = player_x / 64;
     if (row < 0 || row >= height || col < 0 || col >= width)
     {
         return false;
     }
    return (lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q');
}
 bool checkCollisionSpikes(char**lvl,int player_x,int player_y,int height,int width)
 {
     int row = player_y / 64;
     int col = player_x / 64;
     if (row < 0 || row >= height || col < 0 || col >= width)
     {
         return false;
     }
     return (lvl[player_y / 64][player_x / 64] == 'p');
 }