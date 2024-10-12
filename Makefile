CC = gcc
SRC = main.c window.c camera.c player.c controller.c detectcollision.c collisionplane.c
OBJ = main.o window.o camera.o player.o controller.o detectcollision.o collisionplane.o
OUTPUT = test.exe
INCLUDE = -IC:\raylib\raylib\src
LIBS = -LC:\raylib\raylib\src -lraylib -lopengl32 -lgdi32 -lwinmm

# Default target to build the executable
all: $(OUTPUT)

# Rule to link the object files into the final executable
$(OUTPUT): $(OBJ)
	$(CC) $(OBJ) -o $(OUTPUT) $(INCLUDE) $(LIBS)

# Individual rules to compile each .c file into a .o file
main.o: main.c
	$(CC) -c main.c -o main.o $(INCLUDE)

window.o: window.c
	$(CC) -c window.c -o window.o $(INCLUDE)

camera.o: camera.c
	$(CC) -c camera.c -o camera.o $(INCLUDE)
	
player.o: player.c
	$(CC) -c player.c -o player.o $(INCLUDE)

controller.o: controller.c
	$(CC) -c controller.c -o controller.o $(INCLUDE)

detectcollision.o: detectcollision.c
	$(CC) -c detectcollision.c -o detectcollision.o $(INCLUDE)

collisionplane.o: collisionplane.c
	$(CC) -c collisionplane.c -o collisionplane.o $(INCLUDE)

# Clean rule to delete all generated files
clean:
	del *.o $(OUTPUT)