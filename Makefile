CC = gcc
SRC = main.c \
      initialization\window.c \
      player\camera.c \
      player\player.c \
      player\controller.c \
      collision\detectcollision.c \
      collision\collisionplane.c \
	  models\src\modelimport.c \
	  models\src\model.c \
	  collision\interactionbox.c \
	  externmath\externmath.c \
	  collision\externcollision.c \
	  collision\raycasting.c \
	  gameplay\masterbuttons.c \
	  gameplay\inactivestate.c \
	  filereading\filereader.c \
	  gamea\gameamodels.c \
	  gameplay\sharedbuttons.c \
	  gamea\gameapuzzles.c \
	  gameb\gamebpuzzles.c \
	  gameb\gamebmodels.c \
	  ui\src\ui.c \
	  collision\overlapboxes.c \
	  gamea\gameainteractables.c \
	  gameplay\gameseparateinteractables.c \
	  gameb\gamebinteractables.c \
	  gameplay\door.c \
	  gameplay\gameplayelements.c \
	  gameplay\puzzles\togglepuzzle.c \
	  models\src\textures.c \
	  gamea\gameatextures.c \
	  models\src\buttonatlas.c \
	  gamea\gameaqueryboxes.c \
	  gameb\gamebqueryboxes.c \
	  gameb\gamebtextures.c \
	  shared\memory_setup.c \
	  shared\memory_editing.c \
	  initialization\globalfunc.c \
	  destruction\destroyobjects.c \
	  shared\threading.c \
	  shared\sharedpuzzle.c
OBJ = intermediate\main.o \
      intermediate\window.o \
      intermediate\camera.o \
      intermediate\player.o \
      intermediate\controller.o \
      intermediate\detectcollision.o \
      intermediate\collisionplane.o \
	  intermediate\modelimport.o \
	  intermediate\model.o \
	  intermediate\interactionbox.o \
	  intermediate\externmath.o \
	  intermediate\externcollision.o \
	  intermediate\raycasting.o \
	  intermediate\masterbuttons.o \
	  intermediate\inactivestate.o \
	  intermediate\filereader.o \
	  intermediate\gameamodels.o \
	  intermediate\sharedbuttons.o \
	  intermediate\gameapuzzles.o \
	  intermediate\gamebpuzzles.o \
	  intermediate\gamebmodels.o \
	  intermediate\ui.o \
	  intermediate\overlapboxes.o \
	  intermediate\gameainteractables.o \
	  intermediate\gameseparateinteractables.o \
	  intermediate\gamebinteractables.o \
	  intermediate\door.o \
	  intermediate\gameplayelements.o \
	  intermediate\togglepuzzle.o \
	  intermediate\texture.o \
	  intermediate\gameatextures.o \
	  intermediate\buttonatlas.o \
	  intermediate\gameaqueryboxes.o \
	  intermediate\gamebqueryboxes.o \
	  intermediate\gamebtextures.o \
	  intermediate\memory_setup.o \
	  intermediate\memory_editing.o \
	  intermediate\globalfunc.o \
	  intermediate\destroyobjects.o \
	  intermediate\threading.o \
	  intermediate\sharedpuzzle.o
!IFNDEF OUTPUT
OUTPUT = scenea.exe
!ENDIF
INCLUDE = -IC:\raylib\raylib\src
LIBS = -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm
CFLAGS = -Wall -Wextra

# Default target to build the executable
all: intermediate $(OUTPUT)

# Create the intermediate directory if it doesn't exist
intermediate:
	@if not exist intermediate mkdir intermediate

# Rule to link the object files into the final executable
$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT) $(INCLUDE) $(LIBS)

# Explicit rules for object file generation
intermediate\main.o: main.c intermediate
	$(CC) $(CFLAGS) -c main.c -o intermediate\main.o $(INCLUDE)

intermediate\window.o: initialization\window.c intermediate
	$(CC) $(CFLAGS) -c initialization\window.c -o intermediate\window.o $(INCLUDE)

intermediate\camera.o: player\camera.c intermediate
	$(CC) $(CFLAGS) -c player\camera.c -o intermediate\camera.o $(INCLUDE)

intermediate\player.o: player\player.c intermediate
	$(CC) $(CFLAGS) -c player\player.c -o intermediate\player.o $(INCLUDE)

intermediate\controller.o: player\controller.c intermediate
	$(CC) $(CFLAGS) -c player\controller.c -o intermediate\controller.o $(INCLUDE)

intermediate\detectcollision.o: collision\detectcollision.c intermediate
	$(CC) $(CFLAGS) -c collision\detectcollision.c -o intermediate\detectcollision.o $(INCLUDE)

intermediate\collisionplane.o: collision\collisionplane.c intermediate
	$(CC) $(CFLAGS) -c collision\collisionplane.c -o intermediate\collisionplane.o $(INCLUDE)

intermediate\modelimport.o: models\src\modelimport.c intermediate
	$(CC) $(CFLAGS) -c models\src\modelimport.c -o intermediate\modelimport.o $(INCLUDE)

intermediate\model.o: models\src\model.c intermediate
	$(CC) $(CFLAGS) -c models\src\model.c -o intermediate\model.o $(INCLUDE)

intermediate\interactionbox.o: collision\interactionbox.c intermediate
	$(CC) $(CFLAGS) -c collision\interactionbox.c -o intermediate\interactionbox.o $(INCLUDE)

intermediate\externmath.o: externmath\externmath.c intermediate
	$(CC) $(CFLAGS) -c externmath\externmath.c -o intermediate\externmath.o $(INCLUDE)

intermediate\externcollision.o: collision\externcollision.c intermediate
	$(CC) $(CFLAGS) -c collision\externcollision.c -o intermediate\externcollision.o $(INCLUDE)

intermediate\raycasting.o: collision\raycasting.c intermediate
	$(CC) $(CFLAGS) -c collision\raycasting.c -o intermediate\raycasting.o $(INCLUDE)

intermediate\masterbuttons.o: gameplay\masterbuttons.c intermediate
	$(CC) $(CFLAGS) -c gameplay\masterbuttons.c -o intermediate\masterbuttons.o $(INCLUDE)

intermediate\inactivestate.o: gameplay\inactivestate.c intermediate
	$(CC) $(CFLAGS) -c gameplay\inactivestate.c -o intermediate\inactivestate.o $(INCLUDE)

intermediate\filereader.o: filereading\filereader.c intermediate
	$(CC) $(CFLAGS) -c filereading\filereader.c -o intermediate\filereader.o $(INCLUDE)

intermediate\gameamodels.o: gamea\gameamodels.c intermediate
	$(CC) $(CFLAGS) -c gamea\gameamodels.c -o intermediate\gameamodels.o $(INCLUDE)

intermediate\sharedbuttons.o: gameplay\sharedbuttons.c intermediate
	$(CC) $(CFLAGS) -c gameplay\sharedbuttons.c -o intermediate\sharedbuttons.o $(INCLUDE)

intermediate\gameapuzzles.o: gamea\gameapuzzles.c intermediate
	$(CC) $(CFLAGS) -c gamea\gameapuzzles.c -o intermediate\gameapuzzles.o $(INCLUDE)

intermediate\gamebpuzzles.o: gameb\gamebpuzzles.c intermediate
	$(CC) $(CFLAGS) -c gameb\gamebpuzzles.c -o intermediate\gamebpuzzles.o $(INCLUDE)

intermediate\gamebmodels.o: gameb\gamebmodels.c intermediate
	$(CC) $(CFLAGS) -c gameb\gamebmodels.c -o intermediate\gamebmodels.o $(INCLUDE)

intermediate\ui.o: ui\src\ui.c intermediate
	$(CC) $(CFLAGS) -c ui\src\ui.c -o intermediate\ui.o $(INCLUDE)

intermediate\overlapboxes.o: collision\overlapboxes.c intermediate
	$(CC) $(CFLAGS) -c collision\overlapboxes.c -o intermediate\overlapboxes.o $(INCLUDE)

intermediate\gameainteractables.o: gamea\gameainteractables.c intermediate
	$(CC) $(CFLAGS) -c gamea\gameainteractables.c -o intermediate\gameainteractables.o $(INCLUDE)

intermediate\gameseparateinteractables.o: gameplay\gameseparateinteractables.c intermediate
	$(CC) $(CFLAGS) -c gameplay\gameseparateinteractables.c -o intermediate\gameseparateinteractables.o $(INCLUDE)

intermediate\gamebinteractables.o: gameb\gamebinteractables.c intermediate
	$(CC) $(CFLAGS) -c gameb\gamebinteractables.c -o intermediate\gamebinteractables.o $(INCLUDE)

intermediate\door.o: gameplay\door.c intermediate
	$(CC) $(CFLAGS) -c gameplay\door.c -o intermediate\door.o $(INCLUDE)

intermediate\gameplayelements.o: gameplay\gameplayelements.c intermediate
	$(CC) $(CFLAGS) -c gameplay\gameplayelements.c -o intermediate\gameplayelements.o $(INCLUDE)

intermediate\togglepuzzle.o: gameplay\puzzles\togglepuzzle.c intermediate
	$(CC) $(CFLAGS) -c gameplay\puzzles\togglepuzzle.c -o intermediate\togglepuzzle.o $(INCLUDE)

intermediate\texture.o: models\src\texture.c intermediate
	$(CC) $(CFLAGS) -c models\src\texture.c -o intermediate\texture.o $(INCLUDE)

intermediate\gameatextures.o: gamea\gameatextures.c intermediate
	$(CC) $(CFLAGS) -c gamea\gameatextures.c -o intermediate\gameatextures.o $(INCLUDE)

intermediate\buttonatlas.o: models\src\buttonatlas.c intermediate
	$(CC) $(CFLAGS) -c models\src\buttonatlas.c -o intermediate\buttonatlas.o $(INCLUDE)

intermediate\gameaqueryboxes.o: gamea\gameaqueryboxes.c intermediate
	$(CC) $(CFLAGS) -c gamea\gameaqueryboxes.c -o intermediate\gameaqueryboxes.o $(INCLUDE)

intermediate\gamebqueryboxes.o: gameb\gamebqueryboxes.c intermediate
	$(CC) $(CFLAGS) -c gameb\gamebqueryboxes.c -o intermediate\gamebqueryboxes.o $(INCLUDE)

intermediate\gamebtextures.o: gameb\gamebtextures.c intermediate
	$(CC) $(CFLAGS) -c gameb\gamebtextures.c -o intermediate\gamebtextures.o $(INCLUDE)

intermediate\memory_setup.o: shared\memory_setup.c intermediate
	$(CC) $(CFLAGS) -c shared\memory_setup.c -o intermediate\memory_setup.o $(INCLUDE)

intermediate\memory_editing.o: shared\memory_editing.c intermediate
	$(CC) $(CFLAGS) -c shared\memory_editing.c -o intermediate\memory_editing.o $(INCLUDE)

intermediate\globalfunc.o: initialization\globalfunc.c intermediate
	$(CC) $(CFLAGS) -c initialization\globalfunc.c -o intermediate\globalfunc.o $(INCLUDE)

intermediate\destroyobjects.o: destruction\destroyobjects.c intermediate
	$(CC) $(CFLAGS) -c destruction\destroyobjects.c -o intermediate\destroyobjects.o $(INCLUDE)

intermediate\threading.o: shared\threading.c intermediate
	$(CC) $(CFLAGS) -c shared\threading.c -o intermediate\threading.o $(INCLUDE)

intermediate\sharedpuzzle.o: shared\sharedpuzzle.c intermediate
	$(CC) $(CFLAGS) -c shared\sharedpuzzle.c -o intermediate\sharedpuzzle.o $(INCLUDE)

# Clean rule to delete
clean:
	del /q intermediate\*.o 
	del /q $(OUTPUT)


run: $(OUTPUT)
	$(OUTPUT) $(ARGS)
