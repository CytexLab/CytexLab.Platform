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

#include "Application.hpp"

class App : public cl::SystemPlatform::UserApplication
{
public:
  void Run(cl::SystemPlatform::Application& App) override
  {
    App.Exit(0);
  }
};

REGISTER_USER_APP(App);