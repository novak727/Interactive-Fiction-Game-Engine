# Interactive Fiction Game Engine
A semester long project that was built throughout my Data Structures and Algorithms class. The program reads in a file provided by the user which is written in almost an XML style format, with a .ifd extension. It's still plain text, but just with a special file extension. A sample file has been provided, Derelict.ifd.

## Project Installation
C++ is needed for this project, see instructions below.
### Option 1: using [git](https://git-scm.com/downloads)
1. Clone the repository:
```sh
git clone https://github.com/novak727/Interactive-Fiction-Game-Engine.git
```
2. Navigate to the project directory:

### Option 2: without git
1. Download the project as a zip file
2. [Extract the zip file](https://www.wikihow.com/Unzip-a-File)
3. Find the location of the files
4. Copy the path
5. go to the command line and run the following:
```sh
cd /path/to/files
```

## C++ Installation and Usage
The program in this repository is executed using the C++ language and the g++ compiler.

g++ for [Windows](https://sourceforge.net/projects/mingw/), don't forget to add the binary to your [path environment variable](https://www.architectryan.com/2018/03/17/add-to-the-path-on-windows-10/).

g++ can be installed on Linux using your favorite package manager.

### Compile and Execute
#### Option 1: using [Make](https://www.gnu.org/software/make/)
Run the following:
```sh
make all
```
#### Option 2: without Make
Compile the program:
```sh
g++ main.cpp Area.cpp basicArea.cpp BattleItem.cpp CombatPlayer.cpp ConsumeItem.cpp Enemy.cpp eventArea.cpp Game.cpp HPSPPlayer.cpp IFDParser.cpp Item.cpp LinkData.cpp Map.cpp MapV2.cpp Player.cpp restArea.cpp UseItem.cpp -o if_game
```

## Execute the program
### Windows:
```sh
if_game.exe
```

### Linux/Mac:
```sh
./if_game.out
```
