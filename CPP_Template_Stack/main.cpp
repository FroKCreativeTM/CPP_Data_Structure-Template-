#include <iostream>
#include <cstring>
#include "CStack.h"
using namespace std;

int main()
{
	//CStack<int> intStack;

	//for (int i = 0; i < 100; i++)
	//{
	//	intStack.Push(i);
	//}

	//for (int i = 0; i < 100; i++)
	//{
	//	cout << intStack.Pop() << endl;
	//}

	CStack<char> charStack;

	char strText[10] = "TestStr";

	for (int i = 0; i < strlen(strText); ++i)
	{
		charStack.Push(strText[i]);
	}

	for (int i = 0; i < strlen(strText); ++i)
	{
		cout << charStack.Pop();
	}
	cout <<endl;

	return 0;
}