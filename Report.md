Week 2 Proposal and Deviations:

Although the proposed UML made use of playerTurnState and enemyTurnState, each level already possessing a vector of all entities on the map made it more straightforward to simply make "takeTurn" a method of the Entity class, and to the necessary input handling for a player's turn into each level's eventHandling method. 

Gameplay Description:

The player uses the arrow keys to move across a map towards the exit whilst evading the pursuing enemy units. During the enemy's turn, an enemy unit may collide with and attack the player, at which point they will lose health, risking a game over. To mitigate this, the player is able to trigger terrain interactions by standing on or interacting with specific tile types; for example, the player is able to push a boulder out of the way during the first level in order to gain access to the exit tile. This uses all of the player's movement points for a turn, but is a safer alternative to stepping on the poison tiles that surround the first level's exit otherwise. 
If a player is standing on a poison or forest tile at the end of their turn, they lose health or gain avoid respectively (avoid determines the likelihood of an enemy unit's attack connecting and thus damaging the player). The function of a tile can be checked during the player's turn by hovering over it with the mouse cursor -- this can also be done to view the stats and movement radius of a given unit, player and enemy alike.

As the player progresses through levels, they will earn stat increases and temporary boosts to their movement radius. Once the player has reached a sufficient level of strength, they may even be able to retaliate against enemy units instead of simply fleeing for their life. 

Game Programming Patterns Used:

I made use of the game state programming pattern; each level is its own Game State, alongside the title screen, intro, tutorial, game over, and game win screens.

Game Mechanics:

UML:


Sample Screens:

Exception Handling and Test Cases:

Playtesting:

Evidence:

Reflection:

Evaluation:

Had I the time, I would've liked to include a settings menu and proper scaling for different resolutions, alongside more robust combat; furthermore, I would've liked to implement map scrolling and different map types to give the terrain more variety, thus allowing for further variation in level completion strategy.
