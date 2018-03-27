# 2048-solver
an automated solver for the 2048 game
```
The purpose of this project:

• Increase proficiency in C programming, dexterity with dynamic memory allocation 
and understanding of data structures, through programming a search algorithm over Graphs.

• Gain experience with applications of graphs and graph algorithms to solving games, one form of
artificial intelligence.
```
### The 2048 game
2048 is played on a 4x4 grid, with numbered tiles that slide smoothly when a player moves them using
the four arrow keys. Every turn, a new tile will randomly appear in an empty spot on the board with
a value of either 2 or 4. Tiles slide as far as possible in the chosen direction until they are stopped
by either another tile or the edge of the grid. If two tiles of the same number collide while moving,
they will merge into a tile with the total value of the two tiles that collided. The resulting tile cannot
merge with another tile again in the same move.

A scoreboard on the upper-right keeps track of the user’s score. The user’s score starts at zero, and
is incremented whenever two tiles combine, by the value of the new tile.

The game is won when a tile with a value of 2048 appears on the board, hence the name of the game.
After reaching the 2048 tile, players can continue to play (beyond the 2048 tile) to reach
higher scores. In this assignment, your solver should continue playing after reaching tile 2048. When
the player has no legal moves (there are no empty spaces and no adjacent tiles with the same value),
the game ends.
