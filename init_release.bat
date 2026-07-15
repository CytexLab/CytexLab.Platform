@echo off

mkdir Build 2>nul
mkdir Build\Release 2>nul

cmake -G Ninja -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++ -DCMAKE_ASM_COMPILER=clang -B Build\Release -S .