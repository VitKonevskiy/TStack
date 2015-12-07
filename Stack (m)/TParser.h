#ifndef __TPARSER_H__
#define __TPARSER_H__

#include "Stack.h"
#include <string.h>
//#include <cstdlib>

#pragma warning(disable : 4996)

const int MaxLen = 201;
//Строка, длины 200; последний элемент-знак окончания строки('\о')


class TParser
{
	char inf[MaxLen];							//Массив для префиксной формы
	char postf[MaxLen];							//Массив для постфиксной формы	
	TStack<double> st_double;					//Стек чисел - double
	TStack<char> st_char;						//Стек символов
	bool IsOperation(char ch);					//Проверка на знак (+/-*)
	bool IsNumber(char ch);						//Проверка на число.
	
public:
	TParser(char *s = NULL) : st_double(100), st_char(100)
	{
		if (s == NULL) inf[0] = '\0';
		else strcpy(inf, s);
	}
	~TParser();
	int BracketCheck(char *str);				//Проверка, все ли открывающиеся скобки закрыты.
	void CopyString(char *s);					//Копирование строки в инфиксную форму
	void inftopost();							//Перевод из инфексной формы в постфиксную
	double CalcPostf();							//Отдельные вычисления??
	double ExNumber(char *s, int &len);			//Проверка на число
	double CalcP();								//Метод вычисления выражения, внутри стека.
	int Priority(char ch);						//Умение определять приоритет принимаего знака
};//----------------------------------------------------------------------------------------------------------------------------	


/*-------------------------------------------------------------------------*/
bool TParser::IsOperation(char ch)			//Проверка на знак (+/-*)
{
	if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == '^'))
	{
		return true;
	}
	else 
		return false;
}
/*-------------------------------------------------------------------------*/
bool TParser::IsNumber(char ch)				//Проверка на число.
{
	if ((!IsOperation(ch)) && (ch != '(') && (ch != ')'))
		return true;
	else
		return false;
}
/*-------------------------------------------------------------------------*/
int TParser::Priority(char ch)			//Умение определять приоритет принимаего знака
{
	int prior = 0;
	switch (ch)
	{
	case '(':
	case ')': prior = 0; break;
	case '+':;
	case '-': prior = 1; break;
	case '/':;
	case '*': prior = 2; break;
	case '^': prior = 3; break;
	default: prior = -1;
		break;
	}
	return prior;
}
/*-------------------------------------------------------------------------*/
TParser::~TParser()
{
	//delete[] inf;
	//delete[] postf;
}
/*-------------------------------------------------------------------------*/
int TParser::BracketCheck(char *str)				//Проверка, все ли открывающиеся скобки закрыты.
{
	TStack <char> stack(MaxLen);
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '(')
			stack.Push('(');
		if (str[i] == ')')
		{
			if (stack.IsEmpty())
				return 0;
			stack.Pop();
		}
		i++;
	}
	if (!stack.IsEmpty())
		return 0;
	return 1;
}
/*-------------------------------------------------------------------------*/
void TParser::CopyString(char *s)			//Копирование строки в инфиксную форму
{
	if (!BracketCheck(s))		//Проверка на кол-во скобок
		throw !BracketCheck(s);
	else
	if (s == NULL)
		inf[0] = '\0';
	else strcpy(inf, s);
}
/*-------------------------------------------------------------------------*/
void TParser::inftopost()			//Перевод из инфексной формы в постфиксную
{
	int i = 0;
	int j = 0;
	st_char.Push('=');
	while (inf[i] != '\0')
	{
		if (IsNumber(inf[i]))
		{
			postf[j++] = inf[i];
		}
		else
		if (inf[i] == '(')
		{
			st_char.Push('(');
		}
		else
		if (inf[i] == ')')
		{
			char tmp = st_char.Pop();
			while (tmp != '(')
			{
				postf[j++] = tmp;
				tmp = st_char.Pop();
			}
		}
		else
		if (IsOperation(inf[i]))
		{
			char tmp = st_char.Pop();
			while (Priority(tmp) >= Priority(inf[i]))
			{
				postf[j++] = tmp;
				tmp = st_char.Pop();
			}
			st_char.Push(tmp);
			st_char.Push(inf[i]);
		}
		i++;
	}
}
/*-------------------------------------------------------------------------*/
double TParser::CalcPostf()					//Отдельные вычисления??
{
	int i = 0;
	st_double.Clear();
	while ((postf[i] != '\0') && (postf[i] = !'='))
	{
		if (IsNumber(postf[i]))
			st_double.Push(postf[i] - '0');
		if (IsOperation(postf[i]))
		{
			double oper1, oper2;
			double sum;
			oper2 = st_double.Pop();
			oper1 = st_double.Pop();
			switch (postf[i])
			{
			case '+': st_double.Push(oper1 + oper2); break;
			case '-': st_double.Push(oper1 - oper2); break;
			case '*': st_double.Push(oper1 * oper2); break;
			case '/': st_double.Push(oper1 / oper2); break;
			case '^': st_double.Push(pow(oper1, oper2)); break;
			default: throw - 1;
				break;
			}
		}
		i++;
	}
	return (st_double.Pop());
}
/*-------------------------------------------------------------------------*/
double TParser::ExNumber(char *s, int &len)  //Проверка на число
{
	double tmp = atof(s);
	int i = 0;
	while (s[i] != '\0')
	if (IsNumber(s[i]))
		i++;
	else break;
	len = i;
	return tmp;
}
/*-------------------------------------------------------------------------*/
double TParser::CalcP()					//Метод вычисления выражения, внутри стека.
{
	if (!BracketCheck(inf))
		throw MaxLen;
	st_double.Clear();
	int len = 0;
	st_char.Clear();
	int i = 0;
	st_char.Push('=');
	while (inf[i] != '\0')
	{
		if (IsNumber(inf[i]))
		{
			double tmp = ExNumber(&inf[i], len);
			st_double.Push(tmp);
			i += len - 1;
		}
		else if (inf[i] == '(')
			st_char.Push(inf[i]);
		else if (inf[i] == ')')
		{
			char tmpc = st_char.Pop();
			while (tmpc != '(')
			{
				double oper2 = st_double.Pop();
				double oper1 = st_double.Pop();
				switch (tmpc)
				{
				case '+': st_double.Push(oper1 + oper2);     break;
				case '-': st_double.Push(oper1 - oper2);     break;
				case '*': st_double.Push(oper1 * oper2);     break;
				case '/': st_double.Push(oper1 / oper2);     break;
				case '^': st_double.Push(pow(oper1, oper2)); break;
				default: throw - 1;
					break;
				}
				tmpc = st_char.Pop();
			}
		}
		else if (IsOperation(inf[i]))
		{
			char tmp = st_char.Pop();
			while (Priority(tmp) >= Priority(inf[i]))
			{
				double oper2 = st_double.Pop();
				double oper1 = st_double.Pop();
				switch (tmp)
				{
				case '+': st_double.Push(oper1 + oper2);     break;
				case '-': st_double.Push(oper1 - oper2);     break;
				case '*': st_double.Push(oper1 * oper2);     break;
				case '/': st_double.Push(oper1 / oper2);     break;
				case '^': st_double.Push(pow(oper1, oper2)); break;
				default: throw - 1;
					break;
				}
				tmp = st_char.Pop();
			}
			st_char.Push(tmp);
			st_char.Push(inf[i]);
		}
		i++;
	}
	char tmp = st_char.Pop();
	while (tmp != '=')
	{
		double oper2 = st_double.Pop();
		double oper1 = st_double.Pop();
		switch (tmp)
		{
		case '+': st_double.Push(oper1 + oper2);    break;
		case '-': st_double.Push(oper1 - oper2);    break;
		case '*': st_double.Push(oper1 * oper2);    break;
		case '/': st_double.Push(oper1 / oper2);    break;
		case '^': st_double.Push(pow(oper1, oper2)); break;
		default: throw - 1;
			break;
		}
		tmp = st_char.Pop();
	}
	return (st_double.Pop());
}
/*-------------------------------------------------------------------------*/
#endif