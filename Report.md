## Table of contents

- [Week 2 Proposal and Deviations](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#week-2-proposal-and-deviations)
  - [Proposal](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#proposal)
  - [Deviations](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#deviations)
- [Gameplay Description](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#gameplay-description)
- [Use of AI](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#use-of-ai)
- [AI Development Log](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#ai-development-log)
- [Game Programming Patterns Used](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#game-programming-patterns-used)
- [Game Mechanics](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#game-mechanics)
  - [Unit Movement](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#unit-movement)
  - [Combat](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#combat)
  - [Terrain Interactions](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#terrain-interactions)
  - [Mouse Handling and Miscellaneous Player Input](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#mouse-handling-and-miscellaneous-player-input)
- [UML](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#uml)
- [Sample Screens](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#sample-screens)
- [Exception Handling and Test Cases](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#exception-handling-and-test-cases)
- [Playtesting](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#playtesting)
  - [Evidence](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#evidence)
  - [Reflection](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#reflection)
- [Evaluation](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#evaluation)

## Week 2 Proposal and Deviations

### Proposal

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mockup.png" width="500"><img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20055934.png" width="500">
<sub>[Fig.1: Mockup of a level from CW1 Proposal ](https://drive.google.com/file/d/1JqN8MFLXlnTU6tZYKFf4WPcNgiQDrppa/view?usp=sharing)[vs a screenshot from first level of implementation](https://drive.google.com/file/d/1nadpsVe3x1rwFJJ2YCq8OREQbdgiBOIs/view?usp=sharing)</sub>

My [CW1 Proposal](https://drive.google.com/file/d/1yix2X3n0gmWpXFAH5X0q1YIfyuHmA-Xx/view?usp=sharing) was for a turn-based tactical RPG with preset levels and puzzle elements. The implementation matches this description. Turn-based combat, use of multiple routes  to complete levels, and terrain interactions have all been implemented; the player's health also increases as they progress, and eventually they gain the ability to fight back (see [Combat](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#combat)). 

Core functionality is achieved through C++ and SDL3 as proposed. As proposed, no AI was used.

### Deviations

Although the proposed UML made use of playerTurnState and enemyTurnState, each level already possessing a vector of all entities on the map made it more straightforward to simply make "takeTurn()" a method of the Entity class, and to move necessary input handling for a player's turn into each level's eventHandling() method. Entity was also used to instantiate interactable tiles instead of making them subclasses of a separate Tile class to allow for straightforward collision handling. The enum class ObjectType was instead used to differentiate between different "types" of tiles and entities. 

## Gameplay Description

The player uses the arrow keys to move across a map towards the exit whilst evading the pursuing enemy units. During the enemy's turn, an enemy unit may collide with and attack the player, at which point they will lose health, risking a game over. To mitigate this, the player is able to trigger terrain interactions by standing on or interacting with specific tile types; for example, the player is able to push a boulder out of the way during the first level in order to gain access to the exit tile. This uses all of the player's movement points for a turn, but is a safer alternative to stepping on the poison tiles that surround the first level's exit otherwise. 

If a player is standing on a poison or forest tile at the end of their turn, they lose health or gain avoid respectively (avoid determines the likelihood of an enemy unit's attack connecting and thus damaging the player). The function of a tile can be checked during the player's turn by hovering over it with the mouse cursor -- this can also be done to view the stats and movement radius of a given unit, player and enemy alike.

As the player progresses through levels, they will earn stat increases and temporary boosts to their movement radius. Once the player has reached a sufficient level of strength, they may even be able to retaliate against enemy units instead of simply fleeing for their life. 

## Use of AI

No Generative AI was used in this project, as proposed.

## AI Development Log

As no Generative AI was used, no AI Development Log can be provided.

## Game Programming Patterns Used

I made use of the game state programming pattern; each level is its own Game State, alongside the title screen, intro, tutorial, game over, and game win screens.

<img width="578" height="307" alt="Game State class" src="https://file.garden/Zmr4jtTYzC9bqrh3/gamestate.png" /><img width="482" height="513" alt="image" src="https://file.garden/Zmr4jtTYzC9bqrh3/statehandling.png" />

The Game() class acts as a state manager, entering and exiting states and popping them off the state stack when necessary.

## Game Mechanics

### Unit Movement

Player movement is coded using SDL3's PollEvent() method: during a player's turn, whilst a given level state's eventHandling() is running, the player pressing the arrow keys calls the Entity class' playerInput() method, which calls the appropriate Move method as long as the player isn't attempting to move diagonally.  

<img width="977" height="345" alt="image" src="https://github.com/user-attachments/assets/965eb52e-84d3-476c-bb3e-dd336e3efd3a" />

Collision is checked for in every movement method, which creates a temporary copy of the entities vector from a given map (bar the entity calling the function), and runs collisionCheck() for all entities on the field that would trigger a collision (forest, poison, and the later weapon tiles are excluded from this check). This prevents the player (and enemy units) from stepping on boulder tiles or tiles containing enemies. 

### Combat

Combat is automatically called upon collision between an enemy and player unit during an enemy's turn. It is a method of the Entity() class, and utilises the \<random\> library.

<img width="557" height="372" alt="image" src="https://github.com/user-attachments/assets/869129be-5e34-42f6-baaf-615fc5707c0c" />

The method calculates the maximum damage the attacking unit is capable of, then randomly chooses a number between that and 1 using the Mersenne Twister 19937 generator, then does the same using the attacked unit's avoid stat as a maximum. If the randomised damage exceeds the health of the attacked unit, it will default to said unit's current health. 

If the value of damage exceeds the attacked unit's randomised avoid, the hit will connect and the attacked unit will lose health corresponding to the damage value. If the attacked unit's strength exceeds 10, they are able to counter half the damage regardless of the first hit connecting. As the player is incapable of initiating a combat encounter, this is the only way they can deal damage during later levels. 

### Terrain Interactions

Terrain interactions are . Forest and Poison tiles affect the player at the end of their turn during a given level state's Update() method, whilst boulder tiles can only be moved if the player 

### Mouse Handling and Miscellaneous Player Input

During the player's turn, they may hover over any unit to view their movement radius and basic stats.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/playerhover.png" width="500"><img src="https://file.garden/Zmr4jtTYzC9bqrh3/enemyhover.png" width="500">



This is implemented once again using SDL3's PollEvent() method, which, when a mouse motion event is detected, calls the Entity method mouseCheck() for each entity on the field and subsequently mouseHandling() if the cursor is detected to be hovering over an entity.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mousemovementevent.png">

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mousecheck.png">


PollEvent() is also used to detect if the player has pressed the space bar, which ends their turn early. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/endturnearly.png">

Furthermore, they may press enter at any point during their turn to get a short message from the player character indicating her status, based on her health. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/playermessage.png">

This makes use of the Entity method dialogue(), which is also used for segments such as the game's introduction and tutorial states. 

<img width="665" height="710" alt="image" src="https://github.com/user-attachments/assets/76ca57fe-db68-4869-851e-1a26a8a8522a" />

dialogue() takes in the window, the dialogue to display, the position of the text (above or below the entity), and the speed at which that text should be displayed. It then checks the entity's ObjectType to determine the text's colour, and uses the position of the given entity and the length of their dialogue to ensure that the text won't be rendered outside of the window. It then iterates through the length of the given string, rendering it and playing the given entity's "voice" a character at a time. Text is created using SDL3's RenderDebugText.

## UML
![Final UML](https://file.garden/Zmr4jtTYzC9bqrh3/COMP3016%20CW1.jpg)
<sub>[Fig. : Final UML for CW1](https://drive.google.com/file/d/1om6vWiERGeggQiyY3hICtm3T1GOsEaKp/view?usp=sharing)</sub>

## Sample Screens


## Exception Handling and Test Cases

An instance of SDLWindow cannot be created unless SDL initialises successfully.

<img width="752" height="728" alt="image" src="https://github.com/user-attachments/assets/3442f222-dba4-4dcf-9f04-0c1d78e1b503" />

<img width="445" height="105" alt="image" src="https://github.com/user-attachments/assets/e3ae3f47-2e7c-4020-822f-1d49a45942f2" />

Furthermore, each call of the SDLWindow method renderTextureFromFile(), the main method used to render image assets, checks if the file can actually be loaded and converted into a texture before rendering. 

<img width="817" height="243" alt="image" src="https://github.com/user-attachments/assets/3c589303-0954-4119-995a-b3fb242a282c" />

Additionally, a level state cannot be entered unless all entities are successfully created. 

<img width="395" height="126" alt="image" src="https://github.com/user-attachments/assets/b21ca918-a508-4517-bcfb-c63ed26c611e" />


## Playtesting

### Evidence

Playtesting was carried out periodically throughout various stages of development, spanning from 29/10/2026 to 03/11/2026. There were 7 playtesters in total, all of whom gave feedback via a Playtester Form which prompted them to test various game mechanics and identify issues in the process. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/10863317%20COMP3016%20CW1%20PLAYTESTER%20FORM-2.png">

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/10863317%20COMP3016%20CW1%20PLAYTESTER%20FORM-3.png">


### Reflection

Playtesters comprised friends, family, and university staff, all of whom had varying degrees of experience with strategy RPGs and puzzle games (for example, one playtester was an avid fan of the tactical RPG series <i>Fire Emblem</i>, whereas others were less/unfamiliar with the genre). 

Playtesting gave a stronger insight into a player's first instincts: many players would accidentally hit keys twice or spam movement keys in a panic. In earlier builds of the game, before SDL_PumpEvents() and SDL_FlushEvents() were implemented into a game state's eventHandling() and Update() functions respectively, this would cause issues in the event queue, skipping player turns indefinitely if space was pressed more than once and causing rendering errors. The latter was remedied via moving the enemy turn into the Update() function, however this caused its own issues: for example, a later playtester complained about the player sprite not being rerendered on the last tile they moved to until the beginning of the player's next turn.

<img width="987" height="243" alt="image" src="https://github.com/user-attachments/assets/7c5557b7-3d9e-4164-a330-05b95a0377e5" />

The final build of the game thus achieves a "happy medium", allowing for accidental key spamming whilst ensuring that the player character is rendered on the correct tile.


Furthermore, playtesters were confused or frustrated by lack of proper instructions, and sometimes had to be guided through the experience; to mitigate this, hovering over certain tiles in the final game gives the player more information about their functionality.

<img width="980" height="277" alt="image" src="https://github.com/user-attachments/assets/4b1fddb7-d80a-469a-86b9-686862139cd4" />

<img width="335" height="43" alt="image" src="https://github.com/user-attachments/assets/6fc665fa-a21a-4fcd-8a53-7fbf01986974" />

Game balance also became a point of contention: although combat is not meant to be particularly survivable for the player character, some playtesters were understandably frustrated by its heavy favouring of enemy units. 

<img width="995" height="260" alt="image" src="https://github.com/user-attachments/assets/fe10749a-9c71-4968-8d71-65268d0fce59" />

Conversely, some players felt that the game lacked real challenge in spite of this.

<img width="903" height="111" alt="image" src="https://github.com/user-attachments/assets/d5943afa-363b-4e36-afa2-c2b24e519e0b" />


<img width="922" height="65" alt="image" src="https://github.com/user-attachments/assets/8d22e3a5-bf93-4784-aeed-d490ab417be7" />

This was ultimately balanced not by tweaking the combat mechanic or reducing the amount of damage the player takes, but by changing the movement radius and starting position of the enemies, giving the player a better chance of escape whilst retaining the danger and tension of a combat encounter. takeTurn() was also adjusted to give enemy units a 25% chance of moving away from the player if they are on an adjacent tile, preventing them from permanently blocking off a player's escape route. 

Additionally, testers complained about the initial texture used for the information box on the bottom of the screen. 

<img width="671" height="422" alt="image" src="https://github.com/user-attachments/assets/62053edd-d94c-4f97-af37-06a78e45f1f3" />

<img width="983" height="227" alt="image" src="https://github.com/user-attachments/assets/b43b88ae-7323-48e2-8386-de4715355173" />

In response to this, the final game's information box uses a plain grey texture for the sake of readability. 

<img width="672" height="428" alt="image" src="https://github.com/user-attachments/assets/a7077eb2-1b3f-4e53-ba52-55157c53f8ef" />




## Evaluation

Had I the time, I would've liked to include a settings menu and proper scaling for different resolutions, alongside more robust combat; furthermore, I would've liked to implement map scrolling and different map types to give the terrain more variety, thus allowing for further variation in level completion strategy. I would've also liked to lean into the puzzle aspect of the game more. Finally, although the font used by SDL3's Debug Text fits the aesthetic of my implementation, I would've liked to implement an external font using SDL3.tff had I the time. 
