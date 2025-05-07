#pragma once
bool checkCollision(char** lvl, int player_x, int player_y)
{
    return !(lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q' || lvl[player_y / 64][player_x / 64] == 'p');
}
 bool checkCollisionExceptSpikes(char** lvl, int player_x, int player_y)
{
    return (lvl[player_y / 64][player_x / 64] == 'e' || lvl[player_y / 64][player_x / 64] == 'w' || lvl[player_y / 64][player_x / 64] == 'q');
}
 bool checkCollisionSpikes(char**lvl,int player_x,int player_y)
 {
     return (lvl[player_y / 64][player_x / 64] == 'p');

 }