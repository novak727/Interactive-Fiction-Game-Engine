# Compiler and flags
CC = g++
FLAGS = -g -c -Wall
LFLAGS = 

# Source files and object files
OBJS = Area.o BasicPlayer.o BattleItem.o CombatPlayer.o ConsumeItem.o Enemy.o Game.o HPSPPlayer.o IFDParser.o Item.o LinkData.o Map.o MapV2.o Player.o UseItem.o basicArea.o eventArea.o main.o restArea.o
SOURCE = Area.cpp BasicPlayer.cpp BattleItem.cpp CombatPlayer.cpp ConsumeItem.cpp Enemy.cpp Game.cpp HPSPPlayer.cpp IFDParser.cpp Item.cpp LinkData.cpp Map.cpp MapV2.cpp Player.cpp UseItem.cpp basicArea.cpp eventArea.cpp main.cpp restArea.cpp
HEADER = Area.h BasicPlayer.h BattleItem.h CombatPlayer.h ConsumeItem.h Enemy.h Game.h HPSPPlayer.h IFDParser.h Item.h LinkData.h Map.h MapV2.h Player.h UseItem.h areaNode.h basicArea.h eventArea.h restArea.h structs.h ull.h
OUT = if_game

# Libraries
LDLIBS = 

# Default target
all: $(OUT)

# Linking rules
$(OUT): $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) $(LDLIBS)

# Compilation rules
%.o: %.cpp $(HEADER)
	$(CC) $(FLAGS) -o $@ $<

# Clean rule
clean:
	rm -f $(OBJS) $(OUT)
