# CycleAccurate version of 3-stage core Simulator
Basic C++ based CPU performance simulator (3-stage inorder issue):
Generates a test ASM code.
Developed this repo to quickly understand the opcode parsing, pipeline executions and performance stats measurement.
Executes and measures the cycle count of the execution and IPC.

#Usage:
## To Compile:
g++ fetchpipeline.h executepipeline.h decodepipeline.h core_main.cc fetchpipeline.cc decodepipeline.cc executepipeline.cc -o core_main

## To Run:
./core_main.o

