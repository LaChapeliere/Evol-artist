COMPILER = g++
FLAGS = -Wall -std=c++11

default: test

test: main.o World.o FitnessFunctions.o Creature.o Spot.o
	$(COMPILER) $(FLAGS) -o test main.o World.o FitnessFunctions.o Creature.o Spot.o
	
main.o:
	$(COMPILER) $(FLAGS) -c "./Evol'artist/src/main.cpp"
	
World.o:
	$(COMPILER) $(FLAGS) -c "./Evol'artist/src/simulEngine/World.cpp"
	
FitnessFunctions.o:
	$(COMPILER) $(FLAGS) -c "./Evol'artist/src/simulEngine/FitnessFunctions.cpp"
	
Creature.o:
	$(COMPILER) $(FLAGS) -c "./Evol'artist/src/simulEngine/Creature.cpp"

Spot.o:
	$(COMPILER) $(FLAGS) -c "./Evol'artist/src/simulEngine/Spot.cpp"
	
clean: 
	$(RM) count *.o *~
