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
#include "StringIntConvert.hpp"

class App : public cl::SystemPlatform::UserApplication
{
public:
  void Run(cl::SystemPlatform::Application& App) override
  {
    UINT64 out;
    cl::UTF::Utils::StringIntConvert::Result result = cl::UTF::Utils::StringIntConvert::ConvertStringToInt(U"235", &out);

    App.Exit(0);
  }
};

REGISTER_USER_APP(App);