// Win32Project1.cpp : ���� DLL Ӧ�ó���ĵ���������
//

#include "stdafx.h"
#include "OutputInt.h"

extern "C" __declspec(dllexport) int TestFunction()
{
    OutputInt outPut;
    return outPut.TestFunction();
}