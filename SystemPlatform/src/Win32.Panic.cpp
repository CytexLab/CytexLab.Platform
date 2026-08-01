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

#include "Panic.hpp"

#ifdef Windows

#include "Win32.WinImports.hpp"
#include "UTF.hpp"

struct Frame
{
  LPCCHAR Function;
  LPCCHAR File;
  UINT64 Line;
};

Frame stack[STACK_SIZE];
UINT64 stack_pos;

HANDLE hOut;
BOOL isConsole;

void cl::SystemPlatform::Panic::Init()
{
  for (UINT64 i = 0; i < STACK_SIZE; i++)
  {
    stack[i].Function = "";
    stack[i].File = "";
    stack[i].Line = 0;
  }
  stack_pos = 0;

  hOut = ::GetStdHandle(STD_OUTPUT_HANDLE);

  if (!hOut || hOut == (HANDLE) UNSET)
  {
#ifdef CYTEXLAB_DEBUG
    __builtin_debugtrap();
#else
    ::ExitProcess(-1);
#endif
  }

  UINT32 mode = 0;
  INT32 isConsole = ::GetConsoleMode(hOut, &mode);

  if (isConsole != 1)
  {
    isConsole = FALSE;
  }
  else
  {
    isConsole = TRUE;
  }
}

void cl::SystemPlatform::Panic::StackPush(LPCCHAR Func, LPCCHAR File, UINT64 Line)
{
  if (stack_pos == STACK_SIZE)
  {
#ifdef CYTEXLAB_DEBUG
    __builtin_debugtrap();
#else
    ::ExitProcess(-2);
#endif
  }

  Frame f = {Func, File, Line};
  stack[stack_pos++] = f;
}

void cl::SystemPlatform::Panic::StackPop()
{
  if (stack_pos == 0)
  {
#ifdef CYTEXLAB_DEBUG
    __builtin_debugtrap();
#else
    ::ExitProcess(-3);
#endif
  }

  stack_pos--;
}

void WriteConsole(LPCECHAR Message)
{
  using namespace cl::UTF;

  while (*Message)
  {
    WCHAR buf[2];

    SConvertSymbolResult result = ConvertUTF32ToUTF16(Message, buf);

    if (!result.Success)
    {
#ifdef CYTEXLAB_DEBUG
      __builtin_debugtrap();
#else
      ::ExitProcess(-4);
#endif
    }

    UINT32 written = 0;
    INT32 result2 = ::WriteConsoleW(hOut, buf, result.BytesCount / 2, &written, nullptr);

    if (result2 != 1)
    {
      UINT32 error = ::GetLastError();

#ifdef CYTEXLAB_DEBUG
      __builtin_debugtrap();
#else
      ::ExitProcess(error);
#endif
    }

    Message++;
  }
}

void WriteFile(LPCECHAR Message)
{
  using namespace cl::UTF;

  while (*Message)
  {
    CHAR buf[4];

    SConvertSymbolResult result = ConvertUTF32ToUTF8(Message, buf);

    if (!result.Success)
    {
#ifdef CYTEXLAB_DEBUG
      __builtin_debugtrap();
#else
      ::ExitProcess(-4);
#endif
    }

    UINT32 written = 0;
    INT32 result2 = ::WriteFile(hOut, buf, result.BytesCount, &written, nullptr);

    if (result2 != 1)
    {
      UINT32 error = ::GetLastError();

#ifdef CYTEXLAB_DEBUG
      __builtin_debugtrap();
#else
      ::ExitProcess(error);
#endif
    }

    Message++;
  }
}

void Write(LPCECHAR Message)
{
  if (!isConsole)
  {
    WriteFile(Message);
  }
  else
  {
    WriteConsole(Message);
  }
}

void WriteNum(UINT64 num)
{
  using namespace cl::UTF;

  ECHAR tmp[30];

  SStringFunctionsResult result = UIntToString(num, tmp);

  if (!result.Success)
  {
#ifdef CYTEXLAB_DEBUG
    __builtin_debugtrap();
#else
    ::ExitProcess(-5);
#endif
  }

  Write(tmp);
}

void WriteU8(LPCCHAR Message)
{
  using namespace cl::UTF;

  while (*Message)
  {
    ECHAR sym[2];

    SConvertSymbolResult result = ConvertUTF8ToUTF32(Message, &sym[0]);

    if (!result.Success)
    {
#ifdef CYTEXLAB_DEBUG
      __builtin_debugtrap();
#else
      ::ExitProcess(-4);
#endif
    }

    sym[1] = U'\0';
    Write(sym);

    Message += result.BytesCount;
  }
}

void cl::SystemPlatform::Panic::Panic(LPCECHAR Message, LPCCHAR Function, LPCCHAR File, UINT64 Line, UINT32 SystemError)
{
  Write(U"===== [ Panic ] =====\n\r");
  Write(U" * Message: "); Write(Message); Write(U"\r\n");
  Write(U" * Function: "); WriteU8(Function); Write(U"\r\n");
  Write(U" * File: "); WriteU8(File); Write(U"\r\n");
  Write(U" * Line: "); WriteNum(Line); Write(U"\r\n");
  Write(U" * System error: "); WriteNum((UINT64) SystemError); Write(U"\r\n");
  Write(U"\r\n");

  Write(U"===== [ Stack ] ===== \r\n");

  for (UINT64 i = 0; i < stack_pos; i++)
  {
    Write(U"#");
    WriteNum(i);
    Write(U" ");
    WriteU8(stack[i].File);
    Write(U":");
    WriteNum(stack[i].Line);
    Write(U"`");
    WriteU8(stack[i].Function);
    Write(U"\r\n");
  }

  ::ExitProcess(-6);
}

#endif