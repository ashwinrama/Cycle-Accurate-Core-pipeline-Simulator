# CPU-Performance-Simulator - CycleAccurate
Basic C++ based CPU performance simulator (N-stage inorder issue):
Generates a test ASM code.
Developed this repo to quickly understand the opcode parsing, pipeline executions and performance stats measurement.
Executes and measures the cycle count of the execution and IPC.
Number pipeline stages is a parameter and execution unit cycles are parameter constants.

#Usage:
## To Compile:
 g++ core_main.cc fetchpipeline.cc decodepipeline.cc executepipeline.cc -o core_sim.o
  
## To Run:
./core_sim.o

