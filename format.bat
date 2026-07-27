@echo off
for /R Core %f in (*.cpp *.hpp) do clang-format -i -style=file "%f"