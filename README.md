# SEEN (Working Title)
#### Video Demo:  https://youtu.be/6d0kLv_rQyc
#### Description: A first person puzzler in which you solve puzzles of buttons to progress through the game. This project was created through the use 
#### of a graphics framework known as Raylib which you can find here: https://www.raylib.com/index.html. It was also written using C, Visual Studio Code and compiled using GCC, Developer Command Prompt
#### for VS, and Microsoft's NMAKE. 

### You can find the GitHub repo which will contain all future updates to the project here: https://github.com/4ullstop/raylibGame

# For starters:
This project is very complex so I will try and explain it as best I can in simple terms for a more digestible read. The game is currently incomplete
however, the complexity of it will only continue to grow which would only result in a larger .md file.

# The idea of the game:
The main goal of this game is to have it so there are multiple windows for players to interact with as this will create very interesting
interactions between the ideas of the puzzles. 

This explains why there are separated folders labeled gamea and gameb

# From the beginning:
My introduction to this project was through the creation of a custom collision detection and response algorithm. An integral part of any game
is the proper working order of these systems. Starting in the folder labeled collision:

# /collision:

detectcollision.c:
This is where most of the magic happens. Here we have all of our code where we check potential collision between the player and meshes within the world.
Each mesh is destructed down to its triangles where we then check each triangle against the player's future velocity to determine whether a collision is in bound.
We also have code for checking the edges and vertices of the mesh in case the velocity is headed towards them rather than the middle of the triangle of the mesh.

collisionplane.c:
In this file, we take care of basic functionality that is used in the collision detection (as well as some other parts of our code) such as if a point
is within a triangle. It also is where we construct our triangles for our collision detection based on the mesh.

externcollision.c:
This file is used to get the vertices for the meshes depending on whether the mesh was indexed or not. This is also where we calculate when the player's velocity
will intersect with the plane to determine a location for the collision response. It is separated in to this file as the function is used elsewhere in other types of collision 
which I will get into. This is also where we hold our basic functionality for checking whether a point is on a vertex or edge of the mesh.

raycasting.c:
I found it useful to create my own raycasting system as well because the built in one to raylib wasn't as robust as I needed it to be. It actually uses 
a lot of the same functionality as the collision detection algorithm just a little differently for the purposes of raycasting. In this file we are able to determine whether
a cast from the player hit an object (an object intentionally checked into the system) as well as functionality of drawing lines for the purposes of debugging. I acutally use a linked list 
here to draw these lines because the amount of lines produced by the player is determined by the player themselves (based on when they press the interact button) so it needed to be dynamic.

interactionbox.c:
This file takes care of all things with the custom interaction system I implemented through the use of the custom raycasting system. This file is in charge of the templates for constructing, destructing and 
the following functionality upon the player 'interacting' with said interaction box. This file also has some small functionality correlating to the system as a whole: I decided it would be more efficient if
we sectioned interaction boxes inside of larger boxes (which check the player's location and determines if the player is inside of the box where the interaction boxes are). This way when checking for 
collision with the raycasting system, not all of the boxes in the world would have to be checked for collision, only the ones inside of the box in which the player resides in.

overlapbox.c:
This file is for the creation, destruction and checking of overlap boxes. Simply, these boxes continuously check whether a player is inside of them to determine some sort of gameplay event.

# /externmath:

externmath.c:
This file and subsequently, this folder, is in charge of holding functions which are used throughout the project that required separated functionality (to evade circular referencing). For instance this file 
has our function for checking whether a point is inside of a box which is used in various other parts of the project. This also holds some math functions for things like rotating an object around a point and a
determing the distance between two objects.

# /filereading:

While currently out of commission, the hope was to have a file reading system that read csv files for simple implementation of puzzle solutions, but I discovered that this was turning out
to be more work than to actually physically determine the solutions through a coordinate system which you will see later on. 

filereading.c:
This system took in a csv file by file location and read it to determine the location of solutions for our button puzzles.

# /gameplay:

This file contains a lot of things that involve the gameplay, mostly mechanics

door.c:
This file contains all information for the constuction, destruction and implementation of doors in the game.

gameplayelements.c:
Gameplay elements will likely comprise of many elements, currently the only gameplay elements are doors but I thought it'd be useful to set the project up in the future when I want 
to add other things that the button puzzles effect. This file contains a template for the future of these elements.

gameplayseparateinteractables.c:
This file simply allows for the construction of our interactables in the game. Since the game will be separated into two executables, we need to determine which objects to build
which is done through the use of an enum which is determined in our main.c. 

inactivestate.c:
This file takes care of our inactive state which occurs when the player presses 'f' and will allow them to switch windows for gameplay purposes.

masterbuttons.c:
This file is a large file which contains most of our functionality for the button puzzles (theres another file which contains more functionality split up for once again the avoidance of circular referencing).
This file contains construction and destruction of puzzles based on the game type, destruction of buttons, cursor movement functionality (happens when you move with arrow keys) as well as our check if the player
has input the correct solution.

sharedbuttons.c:
This is the aforementioned file which other files use separated functionality to avoid circular referencing. This contains information such as the construction of buttons, what happens when a puzzle is completed
the assignation of gameplay elements (such as doors to open when the puzzle is solved) as well as the construction of the puzzles themselves. The assignation of solutions buttons (buttons which the player needs to 
input for the correct solution of the puzzle) and their textures. The assignation of specialized buttons (such as directional toggle buttons) and their textures. The assignation of textures is done through 
a texture atlas because at some point individual textures became way too much to handle as well as load in for performance reasons.

# /gameplay/puzzles

This folder contains and will contain more of in the future, all different rules for the puzzles. Currently there is only separated rule the buttons have which has been created.

togglepuzzle.c:
This enables the toggling of buttons depending the direction as indicated by the texture. Meaning, when you select the single toggle button, the row in which the direction indicates, will subsequently toggle on or off 
(depending on the state the buttons are currently in). There is also another linked list here to determine if the toggle buttons hits another toggle button in which case it will also inact it's toggling as well.

# /intialization:

corestructs.c:
Since structs are essentially being used as objects, this is where we house all of the structs that are needed to be global to the entire project for their manipulation. This includes structs such as the buttons,
puzzles, models, textures, collision boxes and so on...

window.c:
Houses the information for the creation of the window's themselves. While currently there isn't much functionality associated with the windows, there will definitely be so in the future, so the idea
was to separate it so I wouldn't need to do so in the future.

# /intermediate:

This contains all of the .o compiled files for all of our c files as established by our Makefile.

# /libs:

This folder will likely contain more things in the future.

drawingstructs.h:
Since the functionality of drawing lines is only needed in one file, it's struct for linked list (as described in our raycasting.c file) is located here.

# /models:
This folder contains all of our information for the creation of models and their textures, the /obj file contains all of our obj files and png texture images

# /models/src:

buttonatlas.c:
This file contains the ability to utilize an atlas for our button textures. To do this, I created a custom shader which shifts the button's texture coordinates to correlate to the desired
button texture as indicated by an enum.

model.c:
This file creates all of our models for the game type, draws and destroys them. It was important for all of the models to be kept track of for drawing and 
collision purposes so they are all loaded into an array which is passed around throughout the project to establish this functionality.

modelimport.c:
This file contains the physical ability to draw models, it's also where we have our functionality for unloading the models upon game destruction.

textcoordhelpers.h:
This contains the enums which are used to determine the locations on the texture atlas for the buttons. By using the constant values from the enums, I was easily able to 
switch between the different textures based on some small mathematical functions used in buttonatlas.c.

texture.c:
This is where we load all of our textures onto the models for the game. The textures themselves are in a separate file as an array which made it simpler for loading and unloading the textures
as before I was running into a lot of segmentation faults and such.

# /player:

camera.c:
I also decided to create a more customized camera from raylib because I didn't like the default one and didn't want to have to edit the project files.
This file takes care of everything which is required for utilizing a 3D camera. Most of the functionality comes from the camera provided by raylib which had functions like Start3DMode which I'm not entirely sure what it 
does but regardless, it was needed for the implementation of my own PlayerCam struct.

controller.c:
This houses all of the information for player input as well as where our collision detection algorithm collides with the response algorithm. This is also where we do things like the functionality
for looking around in the world.
The collide and slide functions are our collision response algorithm entirely, pushing the player away from the object we are colliding with by changing the player's velocity directly.

player.c:
This is where all of our information for the player is located such as setting the default values for the player as well as our connection to the controller.

# /shaders:

buttonatlas.fs:
A fragment shader written to take in the information of the offset to determine a new texture for the button to have based on our button atlas.

# /ui:

Like with our models, the /png folder contains all of our png textures for the ui elements.

ui.c:
Contains all of the information required for constructing our ui elements in as well as manipulating and destructing them.

uistructs.h:
Contains the necessary structs for the UI which other files don't need (why it isn't in corestructs.h).

# /gamea & /gameb:
These folders will eventually hold very similar information pertaining to the game type. Since the game will be an interaction between two executables, it was necessary to 
throw the two games informations such as puzzles and models into two separate folders. While I will only be going over the gamea information as both files will hold the same functionality just different information
pertaining to the game type.

gameainteractables.c:
This houses all of the constructor functions for our interactables for the game type (for this instance gamea).

gameamodels.c:
Contains the construction of all of the static models in the world for gamea including the floor and walls.

gameapuzzles.c:
Contains all of the construction of puzzles for gamea as well as the assignation of specialized textures for the puzzles such as solution textures or toggle texures.

gameatextures.c:
Contains all of the file locations in an array for the locations of the textures that will be used in gamea. We also assign all of the values here to an array which is used in a separate file to assign them 
to the models.

# /:

main.c:
This is where we have our main function, global variables and all sorts of functionality required to actually start the game. This is where we physically draw all of our items,
where we call the construction of all elements, where we call the polls (tick) for all objects that require it (such as collision and such) and where we also call the functions for destruction.

Makefile:
Contains all of the rules so that all I have to do to compile the project is type 'nmake'. I do not want to have to write all of the rules for linking myself, that would not be fun.