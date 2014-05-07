/*************
* Simple program that can tell when the Kvaser is plugged in.
* Created 5/6/2014
* Last modified
*/
#include <iostream>
#include <stdio.h>
#include <array>
#include <fstream>
#include <string>
#include "canlib.h"
#include <sstream>

using namespace System;
using namespace std;

void main(){
	canInitializeLibrary();

	int handle = canOpenChannel(0, 0);

	cout << handle << endl;
	system("pause");
}
