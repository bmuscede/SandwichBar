#!/bin/bash

#First, run cmake to build the program.
echo "Building Project..."
cmake .
make
echo ""

#Next, executes BFX.
echo "Generating TA Files..."
bfx `find CMakeFiles/SandwichBar.dir -name "*.o"` -o SandwichBar.bfx.ta
mv SandwichBar.bfx.ta TA_Files/SandwichBar.bfx.ta

#Generates intermediate TA files.
ql $QLDX/script/bfx/rawlink.ql  ./TA_Files/SandwichBar.bfx.ta ./TA_Files/SandwichBar.bfx.raw.ta
ql $QLDX/script/bfx/liftfile.ql ./TA_Files/SandwichBar.bfx.raw.ta ./TA_Files/SandwichBar.bfx.file.ta
ql $QLDX/script/bfx/syscontain.ql ./TA_Files/SandwichBar.bfx.raw.ta ./TA_Files/SandwichBar.bfx.con.ta
schema ./TA_Files/SandwichBar.bfx.con.ta ./TA_Files/SandwichBar.bfx.ls.ta
echo ""

#Analyze project.
echo "Running QL Scripts..."
ql $QL_SCRIPTS/dependFunction.bfx.ql ./TA_Files/SandwichBar.bfx.ls.ta > ./TA_Files/Question3.txt
ql $QL_SCRIPTS/files.bfx.ql ./TA_Files/SandwichBar.bfx.ls.ta > ./TA_Files/Files.txt
ql $QL_SCRIPTS/functionDepend.bfx.ql ./TA_Files/SandwichBar.bfx.ls.ta > ./TA_Files/Question2.txt
ql $QL_SCRIPTS/globalVar.bfx.ql ./TA_Files/SandwichBar.bfx.ls.ta > ./TA_Files/Question1.txt

echo ""

#Cleans the project.
echo "Cleaning project..."
#make clean
rm CMakeCache.txt Makefile cmake_install.cmake 
rm -r CMakeFiles/
