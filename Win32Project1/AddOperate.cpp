#include "stdafx.h"
#include "AddOperate.h"
#include <iostream>
#include <string>
using namespace std;
int Sum(int a, int b) {
    if (a - (int)a != 0 || b - (int)b != 0) {
        cout << "ÇëÊäÈëÕûÊý" << endl;
        return -1;
    }
    return a + b;
}

char * QueryString() {
    return "SELECT * FROM JRT_CMN_DATA";
}
