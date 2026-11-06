## Table of contents

- [HOW TO RUN GAME](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#how-to-run-game)
- [VIDEO LINK](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#video-link)
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
- [Appendices](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#appendices)
  - [Appendix A](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#appendix-a)
  - [Appendix B](https://github.com/Lilla-Rad/COMP3016_CW1/blob/master/Report.md#appendix-b)

## HOW TO RUN GAME

Extract EXECUTABLE.zip from the submitted .zip archive and run "COMP3016_CW1.exe".

Use arrow keys to move and spacebar to end your turn early.

## VIDEO LINK

[YouTube Upload of Demo](https://youtu.be/RWV8UCstXdM)

## Week 2 Proposal and Deviations

### Proposal

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mockup.png" width="500"><img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20055934.png" width="500">

<sub>[Figs. 1&2: Mockup of a level from CW1 Proposal ](https://drive.google.com/file/d/1JqN8MFLXlnTU6tZYKFf4WPcNgiQDrppa/view?usp=sharing)[vs a screenshot from first level of implementation](https://drive.google.com/file/d/1nadpsVe3x1rwFJJ2YCq8OREQbdgiBOIs/view?usp=sharing)</sub>

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

<img width="578" height="300" alt="Game State class" src="https://file.garden/Zmr4jtTYzC9bqrh3/gamestate.png" />
<sup>Fig. 3: Game State class</sup>
<br><br>
<img width="482" height="513" alt="image" src="https://file.garden/Zmr4jtTYzC9bqrh3/statehandling.png" />
<sup>Fig. 4: State handling in Game class</sup>
<br><br>
The Game() class acts as a state manager, entering and exiting states and popping them off the state stack when necessary.

## Game Mechanics

### Unit Movement

Player movement is coded using SDL3's PollEvent() method: during a player's turn, whilst a given level state's eventHandling() is running, the player pressing the arrow keys calls the Entity class' playerInput() method, which calls the appropriate Move method as long as the player isn't attempting to move diagonally.  

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/moveup.png">
<sup>Fig. 5: MoveUp() Entity method</sup>  
<br><br>

Collision is checked for in every movement method, which creates a temporary copy of the entities vector from a given map (bar the entity calling the function), and runs collisionCheck() for all entities on the field that would trigger a collision (forest, poison, and the later weapon tiles are excluded from this check). This prevents the player (and enemy units) from stepping on boulder tiles or tiles containing enemies. 

### Combat

Combat is automatically called upon collision between an enemy and player unit during an enemy's turn. It is a method of the Entity() class, and utilises the \<random\> library.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/combat.png">
<sup>Fig. 6: combat() Entity method</sup>
<br><br>
The method calculates the maximum damage the attacking unit is capable of, then randomly chooses a number between that and 1 using the Mersenne Twister 19937 generator, then does the same using the attacked unit's avoid stat as a maximum. If the randomised damage exceeds the health of the attacked unit, it will default to said unit's current health. 

If the value of damage exceeds the attacked unit's randomised avoid, the hit will connect and the attacked unit will lose health corresponding to the damage value. If the attacked unit's strength exceeds 10, they are able to counter half the damage regardless of the first hit connecting. As the player is incapable of initiating a combat encounter, this is the only way they can deal damage during later levels. 

### Terrain Interactions

Terrain interactions are implemented based on the type of tile; Forest and Poison tiles affect the player at the end of their turn during a given level state's Update() method, while Boulder tiles can only be interacted with if the player is adjacent to one at the start of their turn.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20145456.png">
<sup>Fig. 7: Forest tile collision check in Update()</sup>
<br><br>
<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20144850.png">
<sup>Fig. 8: Poison tile collision check in Update()</sup>
<br><br>
<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20144757.png">
<sup>Fig. 9: Boulder tile movement during eventHandling()</sup>
<br><br>

Moving a boulder uses up the player's entire turn, but may make safer paths accessible.

### Mouse Handling and Miscellaneous Player Input

During the player's turn, they may hover over any unit to view their movement radius and basic stats.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/playerhover.png" width="500"><img src="https://file.garden/Zmr4jtTYzC9bqrh3/enemyhover.png" width="500">

<sub>[Figs. 10&11: Hovering over the player ](https://drive.google.com/file/d/1kcWd8wI-Fcjl_XwhljBTp71jS7LD97Bw/view?usp=sharing)[vs an enemy unit](https://drive.google.com/file/d/1PMuc-qsPNGi3WhxJ9ao5K-fPQoLVUcaR/view?usp=sharing)</sub>

This is implemented once again using SDL3's PollEvent() method, which, when a mouse motion event is detected, calls the Entity method mouseCheck() for each entity on the field and subsequently mouseHandling() if the cursor is detected to be hovering over an entity.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mousemovementevent.png">
<sup>Fig. 12: Mouse motion event handling in eventHandling()</sup>
<br><br>
<img src="https://file.garden/Zmr4jtTYzC9bqrh3/mousecheck.png">
<sup>Fig. 13: mouseCheck() Entity method</sup>
<br><br>
PollEvent() is also used to detect if the player has pressed the space bar, which ends their turn early. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/endturnearly.png">
<sup>Fig. 14: Spacebar key press handling in eventHandling()</sup>
<br><br>
Furthermore, they may press enter at any point during their turn to get a short message from the player character indicating her status, based on her health. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/playermessage.png">
<sup>Fig. 15: Enter/Return key press handling in eventHandling()</sup>
<br><br>
This makes use of the Entity method dialogue(), which is also used for segments such as the game's introduction and tutorial states. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20072152.png">
<sup>Fig. 16: dialogue() Entity method</sup>
<br><br>

dialogue() takes in the window, the dialogue to display, the position of the text (above or below the entity), and the speed at which that text should be displayed. It then checks the entity's ObjectType to determine the text's colour, and uses the position of the given entity and the length of their dialogue to ensure that the text won't be rendered outside of the window. It then iterates through the length of the given string, rendering it and playing the given entity's "voice" a character at a time. Text is created using SDL3's RenderDebugText.

## UML
![Final UML](https://file.garden/Zmr4jtTYzC9bqrh3/COMP3016%20CW1.jpg)
<sub>[Fig. 17: Final UML for CW1](https://drive.google.com/file/d/1om6vWiERGeggQiyY3hICtm3T1GOsEaKp/view?usp=sharing)</sub>

## Sample Screens

![Intro State](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100242.png)

<sup>[Fig. 18: Intro State](https://drive.google.com/file/d/1OLv_DDRjOf44TA5iO89_jYV4LU3jMRPg/view?usp=sharing)</sup>

![Tutorial State](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100443.png)

<sup>[Fig. 19: Tutorial State](https://drive.google.com/file/d/1qhskmSFypp_ogBClcTtrcKu9P8nF21GY/view?usp=sharing)</sup>

![Moving a boulder](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100543.png)

<sup>[Fig. 20: Moving a boulder](https://drive.google.com/file/d/1n4iWWtqYEJIwyplqBjHPkzgdjfnLSYVi/view?usp=sharing)</sup>

![Level 2](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100614.png)

<sup>[Fig. 21: Level 2](https://drive.google.com/file/d/1l3fMuTI1QLe3iSeadOJlm6MgXteMHfP3/view?usp=sharing)</sup>

![Taking poison damage](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100709.png)

<sup>[Fig. 22: Taking poison damage](https://drive.google.com/file/d/1Btg1b4kvYhuG4Jhfz8EewEKLt9VzXzXZ/view?usp=sharing)</sup>

![Weapon pickup](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100720.png)

<sup>[Fig. 23: Picking up a weapon](https://drive.google.com/file/d/1i2VJ2HEo-I_8Av6sWBGYobgOEqmFjvEB/view?usp=sharing)</sup>

![Paladin enemy](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100811.png)

<sup>[Fig. 24: Checking an enemy on the third level](https://drive.google.com/file/d/1_JapgyJU9hb-ch6dipTDT5PfYs2t94ow/view?usp=sharing)</sup>

![Taking damage](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100739.png)

<sup>[Fig. 25: Taking damage](https://drive.google.com/file/d/1n7sbe6Be4rhTxhRiZ1rFdL1_ozsdeGtV/view?usp=sharing)</sup>

![Retaliating](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20100749.png)

<sup>[Fig. 26: Countering an enemy attack](https://drive.google.com/file/d/1kiVPUBV_54QtCj1iKSvkXb8vTwIiQVxf/view?usp=sharing)</sup>

![Murdering an enemy](https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20185132.png)

<sup>[Fig. 27: The aftermath of killing an enemy](https://drive.google.com/file/d/1f75Iv7LXSDp0ZREvGpQGn6GgjpSgAww0/view?usp=sharing)</sup>

## Exception Handling and Test Cases

An instance of SDLWindow cannot be created unless SDL initialises successfully.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20072152.png">
<sup>Fig. 28: SDLWindow SDL initialisation checks</sup>
<br><br>
<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20090726.png">
<sup>Fig. 29: SDLWindow constructor</sup>
<br><br>

Furthermore, each call of the SDLWindow method renderTextureFromFile(), the main method used to render image assets, checks if the file can actually be loaded and converted into a texture before rendering. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20085942.png">
<sup>Fig. 30: renderTextureFromFile() tests</sup>
<br><br>

Additionally, a level state cannot be entered unless all entities are successfully created. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20090026.png">
<sup>Fig. 31: Level state enter() tests</sup>

## Playtesting

### Evidence

Playtesting was carried out periodically throughout various stages of development, spanning from 29/10/2026 to 03/11/2026. There were 7 playtesters in total, all of whom gave feedback via a Playtester Form which prompted them to test various game mechanics and identify issues in the process. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/10863317%20COMP3016%20CW1%20PLAYTESTER%20FORM-2.png">

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/10863317%20COMP3016%20CW1%20PLAYTESTER%20FORM-3.png">

<sup>[Fig. 32: Playtester form](https://drive.google.com/file/d/1WZk42o93CK3cg2fT9d2y_yR-jzcJ2QPT/view?usp=sharing)</sup>

### Reflection

Playtesters comprised friends, family, and university staff, all of whom had varying degrees of experience with strategy RPGs and puzzle games (for example, one playtester was an avid fan of the tactical RPG series <i>Fire Emblem</i>, whereas others were less/unfamiliar with the genre). 

Playtesting gave a stronger insight into a player's first instincts: many players would accidentally hit keys twice or spam movement keys in a panic. In earlier builds of the game, before SDL_PumpEvents() and SDL_FlushEvents() were implemented into a game state's eventHandling() and Update() functions respectively, this would cause issues in the event queue, skipping player turns indefinitely if space was pressed more than once and causing rendering errors. The latter was remedied via moving the enemy turn into the Update() function, however this caused its own issues: for example, a later playtester complained about the player sprite not being rerendered on the last tile they moved to until the beginning of the player's next turn.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester7.png">

<sup>[Fig. 33: Playtester 7 response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)

The final build of the game thus achieves a "happy medium", allowing for accidental key spamming whilst ensuring that the player character is rendered on the correct tile.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20193502.png">

<sup>[Fig. 34: Commit addressing playtester 7's response](https://github.com/Lilla-Rad/COMP3016_CW1/commit/34ba077a1a290ff9739be3a03388006937351d8f)


Furthermore, playtesters were confused or frustrated by lack of proper instructions, and sometimes had to be guided through the experience; to mitigate this, hovering over certain tiles in the final game gives the player more information about their functionality.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester5.png">

<sup>[Fig. 35: Playtester 5 response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester6a.png">

<sup>[Fig. 36: Part of playtester 6's response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)


Game balance also became a point of contention: although combat is not meant to be particularly survivable for the player character, some playtesters were understandably frustrated by its heavy favouring of enemy units. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester1a.png">

<sup>[Fig. 37: Playtester 1's second response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)


Conversely, some players felt that the game lacked real challenge in spite of this.

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester6b.png">

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester6c.png">

<sup>[Figs. 38&39: Parts of playtester 6's response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)

This was ultimately balanced not by tweaking the combat mechanic or reducing the amount of damage the player takes, but by changing the movement radius and starting position of the enemies, giving the player a better chance of escape whilst retaining the danger and tension of a combat encounter. takeTurn() was also adjusted to give enemy units a 25% chance of moving away from the player if they are on an adjacent tile, preventing them from permanently blocking off a player's escape route. 

Additionally, testers complained about the initial texture used for the information box on the bottom of the screen. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/beta.png">

<sup>[Figs. 40: Screenshot of a beta version using placeholder assets](https://drive.google.com/file/d/1Mqh01mdMrb2mQp5bvaZzo9VRVULjWi3K/view?usp=sharing)

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/tester3.png">

<sup>[Fig. 41: Playtester 3's response](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)

In response to this, the final game's information box uses a plain grey texture for the sake of readability. 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20055934.png">

<sup>[Fig. 42: Final game's improved information box](https://drive.google.com/file/d/1nadpsVe3x1rwFJJ2YCq8OREQbdgiBOIs/view?usp=sharing)

## Evaluation

Although I have implemented all proposed features, and have even built on intended mechanics, I believe there is room for improvement as far the optimisation and exception handling of the game is concerned. Further, had I the time, I would've liked to include a settings menu and proper scaling for different resolutions, alongside more robust combat. I would've also liked to implement map scrolling and different map types to give the terrain more variety, thus allowing for further variation in level completion strategy; to that end, I would've liked to lean into the puzzle aspect of the game more. Finally, although the font used by SDL3's Debug Text fits the aesthetic of my implementation, I would've liked to implement an external font using SDL3.tff.

## Appendices

### Appendix A

Figure A1

Playtester Form Responses 

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Screenshot%202026-11-05%20200242.png">

[Playtester Form Response Spreadsheet](https://docs.google.com/spreadsheets/d/1HPJTjVKhtQPvPDYfWWxkHu493J-TqYHQ9LSlFVBgvII/edit?usp=sharing)

END OF Appendix A

### Appendix B

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Student%20Declaration%20of%20AI%20Tool%20use%20in%20this%20Assessment-1.png">

<img src="https://file.garden/Zmr4jtTYzC9bqrh3/Student%20Declaration%20of%20AI%20Tool%20use%20in%20this%20Assessment-2.png">

[Student Declaration of AI Tool use in this Assessment](https://drive.google.com/file/d/1q_s5xwI6qdZqoAYJDGdLcRwwxEytE8uX/view?usp=sharing)

END OF Appendix B
