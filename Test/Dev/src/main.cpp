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
    cl::UTF::Utils::StringIntConvert::Result result = cl::UTF::Utils::StringIntConvert::ConvertStringToInt(nullptr, &out);

    INT64 out2;
    cl::UTF::Utils::StringIntConvert::Result result2 = cl::UTF::Utils::StringIntConvert::ConvertStringToInt(nullptr, &out2);

    ECHAR out3[24];
    UINT64 in = 0;
    cl::UTF::Utils::StringIntConvert::Result result3 = cl::UTF::Utils::StringIntConvert::ConvertIntToString(&in, nullptr);

    ECHAR out4[24];
    INT64 in2 = -0;
    cl::UTF::Utils::StringIntConvert::Result result4 = cl::UTF::Utils::StringIntConvert::ConvertIntToString(&in2, nullptr);

    App.Exit(0);
  }
};

REGISTER_USER_APP(App);