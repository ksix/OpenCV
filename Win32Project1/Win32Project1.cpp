// Win32Project1.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "OutputInt.h"

extern "C" __declspec(dllexport) int TestFunction()
{
    OutputInt outPut;
    return outPut.TestFunction();
}