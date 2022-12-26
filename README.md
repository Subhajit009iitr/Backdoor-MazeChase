# Backdoor-MazeChase
#### Maze Chase is a 3-D game developed on Unreal Engine using C++ and Blueprints.
##### Developed as a challenge for the BackdoorCTF
---
# Problem Statement of BackdoorCTF challenge:
 In the Maze Chase game, players must explore every nook and cranny of the map in order to uncover its hidden secrets and find the path to victory. But be warned, the maze is full of twists and turns, and only the most dedicated and determined players will be able to solve the puzzle
 the path is not always obvious and you may need to think outside the box to find the best solution.
* Hint ---> "What would a Bird's view be? Think from some other perspectives but for that you must COVER them all"
---
## Game Visuals:

![Screenshot 2022-12-26 131958](https://user-images.githubusercontent.com/99145719/209521909-5fef296c-90c8-45a3-9dd6-191735cff134.jpg)
![Screenshot 2022-12-26 132038](https://user-images.githubusercontent.com/99145719/209521929-e46ff451-40fc-4c2a-a8c0-609fa3410ee0.jpg)
![Screenshot 2022-12-26 132253](https://user-images.githubusercontent.com/99145719/209521946-9b12da09-0a3b-4f43-aa61-c0e4c0149d85.jpg)
---

## How to Play:
Maze Chase is a 3d Maze game with a number of paths and checkpoints diplayed on the map as circular platforms(mostly red except the start and finish points). The Goal of the player is to search for the RIGHT path from the start to the end that will lead the player to Victory. On reaching the finish line the game will terminate automatically and after quitting, you will find a flag.txt file in the launch folder.
On choosing the wrong path in the game the flag.txt file will display "Not the Right way!!!" but if you choose the destined path you will achieve your flag for the challenge in the flag.txt file.
To know the solution check the Solution below.

# Solution of Maze Chase
The Maze Chase is a puzzle game as well as a CTF challenge for Mathematical minds who are expert at finding patterns. Here, after traversing the map a few times the player is supposed to draw a map with its given Distances between checkpoints whose top view would look like this
![photo_2022-12-26_13-55-18](https://user-images.githubusercontent.com/99145719/209569745-928e6506-1234-4d5f-9aab-3b4d1242ac63.jpg)

After that all the player has to do is to find the smallest path to go from the starting point to the finish point covering all the checkpoints atleast once. This can be done using PRIM's ALGORITHM which will yield these 2 possible solutions, both of which will give you the flag in flag.txt file.

The Solution paths are:
0->2->0->1->3->6->3->4->3->7->5->7->8  and  0->2->0->1->3->4->3->6->3->7->5->7->8
