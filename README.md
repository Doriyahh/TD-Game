Created for Computer Science 122 at WSU Pullman
Instructor - Andy O'Fallon

Video: https://youtu.be/YRssFylg98g

Team Members - Brock Childers(Doriyahh), Brandon Montgomery(brandonmonty07-cyber), Blake Watson(Pairadise), Josh Torres(WearingKoala64)

Description:
An Andy O'Fallon themed tower defense game built in MS Visual Studio Community using the SFML graphics library for C++.


-- How to Play --
Upon starting the application, you will be greeted with a heartwarming main menu. After you are done admiring, press enter to begin the game.
A game map resembling the WSU Campus (with a lot more grass and greenery) should appear. There will also be a side menu presenting your gold,
health, and the available towers. Pressing space begins the round, spawning enemies. Before that, you should click on the charming images of 
Andy, andd drag them onto the map. If he appears red, it is an invalid placement, and you'll need to find a different placement. You'll
notice upon successful placement, a different side menu will appear, and the tower range will ddisplay. If you have enough gold, you 
can purchase upgrades for that tower by clicking on the image of the asssociated upgrade. You can click on the tower tto exit the upgrade menu
and click on it again to enter it again. Each tower has unique properties, so have some variety! Towers will attack enemies as they enter their
range. Upon defeat an enemy will reward the player with a set amount of gold, but if it reaches the end, it removes an amount of health. Zero
health means you lose. Upon a successful round win, you will get a cash bonus and the next round will not proceed until you press space. As
of now there are 10 rounds. Have fun!


DISCLAIMER: AI WAS USED IN THE PROCESS OF CREATING THIS PROJECT. PRIMARY USES WERE FOR DEBUGGING, TESTS, AND LOGIC ASSISTANCE.



Current Contribution List:

Brock:
- Created project files and repository
- Created base projectile class
- Created all towers and defined all behaviors for towers
- Created game object (tracks player values, object list vectors)
- Created side menu, main menu, upgrade menus, and associated behaviors
- Adjusted balances for towers and enemies

Brandon:
- Created map and path graphics
- Created list of vector "waypoints" (treated as coordinates) in map
  and path functions/graphics used for enemy travel and tower placement. 
- Contributed to enemy and tower map-based functions
- Contributed to tower range functions
- Created test functions and implimented them in main
  

Blake:
- Created base tower class and base enemy class
- Contributed to enemy types and behaviors
- Contributed to End screen Menu behaviors
- Contributed to tower behavior of priority enemy attacks
- Contributed to balance changes for the enemies gold and damage
- Contributed to adding enemies to each of the rounds

  
Josh:
- Contributed to enemy classes
- Contributed to enemy types and behaviors
- Contributed to enemy pathing system
- Contributed to End screen Menu behaivors
- Contributed to tower behavior of attacking enemy in the front
