#include <iostream>
#include "Stack.h"
#include <stdio.h>
#include "TParser.h"
using namespace std;

int main()
{
	int n = 0;
	TStack<int> S(5);
	S.Push(10);
	n = S.Top();
	char str[200];
	
	while (1)
	{
		printf("Input:\n");
		gets(str);
		TParser q(str);
		double result = q.CalcP();
		printf("result=%lf\n",result);
	}
	return 0;
}