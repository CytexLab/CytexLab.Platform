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

#pragma once

#include "Platform.hpp"

#ifdef CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API_EXPORT
#define CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API __declspec(dllexport)
#else
#define CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API __declspec(dllimport)
#endif

namespace cl
{
  namespace SystemPlatform
  {
    class Application
    {
    private:
      BOOL inited = FALSE;

    public:
      CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void Init();
      CYTEXLAB_SYSTEMPLATFORM_WINDOWS_API void Exit(UINT32 Code);
    };

    class UserApplication
    {
    public:
      virtual void Run(Application& App) = 0;
      virtual ~UserApplication() = 0;
    };
  }
}

#define REGISTER_USER_APP(UserAppClass) \
  extern "C" void clSysStartup() \
  { \
    cl::SystemPlatform::Application app; \
    app.Init(); \
    UserAppClass user_app; \
    user_app.Run(app); \
  }