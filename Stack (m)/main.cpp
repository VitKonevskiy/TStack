#include <iostream>
#include "Stack.h"
#include "TParser.h"
using namespace std;

int main()
{
	int n = 0;
	TStack<int> S(5);
	S.Push(10);
	n = S.Top();
	char* A = "";
	TParser q(A);
	printf("TParser\n");
	printf("Stack\n");
	printf("n=%d\n", n);
	double result = q.CalcP();
	printf("result=%lf\n",result);
	return 0;
}