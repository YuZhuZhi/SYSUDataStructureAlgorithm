#include <iostream>
#include "DEQUE.h"
#include "InfixCompute.h"
using namespace std;

int main()
{
	string str = "1 + 2 + 3";
	cout << InfixCompute::ExpressEval(str);
}