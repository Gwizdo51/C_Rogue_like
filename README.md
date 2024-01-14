<!-- # TODO

- [x] add the player and the stairs
- add game mechanics:
    - [x] the player can move up, down, left and right with WASD
    - [x] if the player tries to move into a wall, cancel the movement
    - [x] if the player is on top of the stairs, get to the level below if he presses "e"
    - [x] add gold coins that the player can collect
    - [x] add a level counter and a gold counter
    - [x] add a fog of war system
    - [x] find a way to turn the FOW on and off
- [x] add a batch file to compile the game
- [x] add colors -->

# Mini-game - Rogue-like in C

This repo contains the code for a Rogue-like game with a command prompt interface. This game was created as a semester project for the ESAIP engineering school.

## Installation

Download the latest version of the **rogue_like.exe** executable (cf. [releases](https://github.com/Gwizdo51/C_Rogue_like/releases))

## Quick start

Run the program by double-clicking on it (on windows 11, make sure to run the program with "**Windows Console Host**", not "**Windows Terminal**")

## How to play

- Move with **ZQSD** (french keyboard)
- Collect gold coins (**$**) by moving over them
- Complete the current level by entering the stairs (**¤**) with **ENTER**
- Exit the game with **ESCAPE**

Cheats:
- Force win the current level with **R**
- Enable/disable the fog of war with **F**

## Compile the game

On windows 10/11:
1. Install [MinGW](https://sourceforge.net/projects/mingw/)
2. Add the path to **gcc.exe** folder to your **PATH** environment variable ("MinGW\bin")
3. Run **compile.bat** by double-clicking on it
