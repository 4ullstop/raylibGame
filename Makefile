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
	  collision\raycasting.c
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
	  intermediate\raycasting.o 
!IFNDEF OUTPUT
OUTPUT = test.exe
!ENDIF
INCLUDE = -IC:\raylib\raylib\src
LIBS = -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm

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
	$(CC) -c main.c -o intermediate\main.o $(INCLUDE)

intermediate\window.o: initialization\window.c intermediate
	$(CC) -c initialization\window.c -o intermediate\window.o $(INCLUDE)

intermediate\camera.o: player\camera.c intermediate
	$(CC) -c player\camera.c -o intermediate\camera.o $(INCLUDE)

intermediate\player.o: player\player.c intermediate
	$(CC) -c player\player.c -o intermediate\player.o $(INCLUDE)

intermediate\controller.o: player\controller.c intermediate
	$(CC) -c player\controller.c -o intermediate\controller.o $(INCLUDE)

intermediate\detectcollision.o: collision\detectcollision.c intermediate
	$(CC) -c collision\detectcollision.c -o intermediate\detectcollision.o $(INCLUDE)

intermediate\collisionplane.o: collision\collisionplane.c intermediate
	$(CC) -c collision\collisionplane.c -o intermediate\collisionplane.o $(INCLUDE)

intermediate\modelimport.o: models\src\modelimport.c intermediate
	$(CC) -c models\src\modelimport.c -o intermediate\modelimport.o $(INCLUDE)

intermediate\model.o: models\src\model.c intermediate
	$(CC) -c models\src\model.c -o intermediate\model.o $(INCLUDE)

intermediate\interactionbox.o: collision\interactionbox.c intermediate
	$(CC) -c collision\interactionbox.c -o intermediate\interactionbox.o $(INCLUDE)

intermediate\externmath.o: externmath\externmath.c intermediate
	$(CC) -c externmath\externmath.c -o intermediate\externmath.o $(INCLUDE)

intermediate\externcollision.o: collision\externcollision.c intermediate
	$(CC) -c collision\externcollision.c -o intermediate\externcollision.o $(INCLUDE)

intermediate\raycasting.o: collision\raycasting.c intermediate
	$(CC) -c collision\raycasting.c -o intermediate\raycasting.o $(INCLUDE)
# Clean rule to delete
clean:
	del /q intermediate\*.o 
	del /q $(OUTPUT)


