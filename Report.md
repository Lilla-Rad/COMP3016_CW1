## Table of contents

- [Week 2 Proposal and Deviations](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#week-2-proposal-and-deviations)
- [Gameplay Description](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#gameplay-description)
- [Game Programming Patterns Used](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#game-programming-patterns-used)
- [Game Mechanics](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#game-mechanics)
-   [Unit Movement](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#unit-movement)
-   [Combat](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#combat)
-   [Terrain Interactions](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#terrain-interactions)
- [UML](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#uml)
- [Sample Screens](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#sample-screens)
- [Exception Handling and Test Cases](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#exception-handling-and-test-cases)
- [Playtesting](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#playtesting)
-   [Evidence](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#evidence)
-   [Reflection](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#reflection)
- [Evaluation](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#evaluation)

## Week 2 Proposal and Deviations:

Although the proposed UML made use of playerTurnState and enemyTurnState, each level already possessing a vector of all entities on the map made it more straightforward to simply make "takeTurn" a method of the Entity class, and to the necessary input handling for a player's turn into each level's eventHandling method. 

## Gameplay Description:

The player uses the arrow keys to move across a map towards the exit whilst evading the pursuing enemy units. During the enemy's turn, an enemy unit may collide with and attack the player, at which point they will lose health, risking a game over. To mitigate this, the player is able to trigger terrain interactions by standing on or interacting with specific tile types; for example, the player is able to push a boulder out of the way during the first level in order to gain access to the exit tile. This uses all of the player's movement points for a turn, but is a safer alternative to stepping on the poison tiles that surround the first level's exit otherwise. 

If a player is standing on a poison or forest tile at the end of their turn, they lose health or gain avoid respectively (avoid determines the likelihood of an enemy unit's attack connecting and thus damaging the player). The function of a tile can be checked during the player's turn by hovering over it with the mouse cursor -- this can also be done to view the stats and movement radius of a given unit, player and enemy alike.

As the player progresses through levels, they will earn stat increases and temporary boosts to their movement radius. Once the player has reached a sufficient level of strength, they may even be able to retaliate against enemy units instead of simply fleeing for their life. 

## Game Programming Patterns Used:

I made use of the game state programming pattern; each level is its own Game State, alongside the title screen, intro, tutorial, game over, and game win screens.

<img width="578" height="307" alt="image" src="https://github.com/user-attachments/assets/cc9306cb-6fbd-4451-a8b7-d04acd4e86be" /><img width="482" height="513" alt="image" src="https://github.com/user-attachments/assets/ad789cfd-b1d8-4112-aeb3-11210c2a1851" />

The Game() class acts as a state manager, entering and exiting states and popping them off the state stack when necessary.

## Game Mechanics:

### Unit Movement

Player movement is coded using 

### Combat

Combat is automatically triggered upon collision during an enemy's turn. It is a method of the Entity() class, and utilises the <random> library.

<img width="557" height="372" alt="image" src="https://github.com/user-attachments/assets/869129be-5e34-42f6-baaf-615fc5707c0c" />

The method calculates the maximum damage the attacking unit is capable of, then randomly chooses a number between that and 1 using the Mersenne Twister 19937 generator, at which point it will . If the damage exceeds the health of the attacked unit, it will default to said unit's current health. 

<img width="977" height="345" alt="image" src="https://github.com/user-attachments/assets/965eb52e-84d3-476c-bb3e-dd336e3efd3a" />

Collision is checked for in every movement method, which creates a temporary copy of the entities vector from a given map (bar the entity calling the function), and runs collisionCheck() for all entities on the field that would trigger a collision (forest, poison, and the later weapon tiles are excluded from this check).

### Terrain Interactions

Terrain interactions are 

## UML:
![Final UML](https://file.garden/Zmr4jtTYzC9bqrh3/COMP3016%20CW1.jpg)
<sub>[Fig.1: Final UML for CW1](https://drive.google.com/file/d/1om6vWiERGeggQiyY3hICtm3T1GOsEaKp/view?usp=sharing)</sub>

## Sample Screens:


## Exception Handling and Test Cases:

If SDL fails to initialise, the program won't boot at all. 

## Playtesting:



### Evidence:

### Reflection:

## Evaluation:

Had I the time, I would've liked to include a settings menu and proper scaling for different resolutions, alongside more robust combat; furthermore, I would've liked to implement map scrolling and different map types to give the terrain more variety, thus allowing for further variation in level completion strategy.
