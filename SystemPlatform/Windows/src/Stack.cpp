/*
 * CytexLab Platform
 * Copyright (c) 2026 CytexLab
 *
 * Данный файл является частью платформы CytexLab и распространяется
 * согласно условиям CytexLab Public Community License (CL2P) v1.0.
 * Полный текст лицензии доступен в файле LICENSE.txt.
 *
 * Для получения коммерческой лицензии: programminyka@mail.ru
 */

#include "Stack.hpp"
#include "Imports.hpp"

#define STACK_SIZE 50

StackItem stack[STACK_SIZE];
UINT64 stackPos = 0;

void StackInit()
{
  for (UINT64 i = 0; i < STACK_SIZE; i++)
  {
    stack[i] = {nullptr, nullptr, nullptr, (UINT64)-1};
  }
}

void StackPush(StackItem Item)
{
  if (stackPos == STACK_SIZE)
    ExitProcess(-6);

  stack[stackPos++] = Item;
}

void StackPop()
{
  if (stackPos == 0)
    ExitProcess(-7);

  stackPos--;
}

