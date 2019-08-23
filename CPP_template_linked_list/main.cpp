#include <iostream>
#include "TLinkedList.h"
using std::cout;
using std::cin;
using std::endl;

int main()
{
	TLinkedList<int> listInt;
	TLinkedList<float> listFloat;

	for (int i = 0; i < 100; ++i)
	{
		listInt.InsertBack(i + 1);
	}

	//cout << listInt.size() << endl;

	TLinkedList<int>::iterator iter;
	for (iter = listInt.begin(); iter != listInt.end(); ++iter)
	{
		cout << *iter << endl;
	}

	TLinkedList<int>::reverseiterator riter;
	for (riter = listInt.rbegin(); riter != listInt.rend(); ++riter)
	{
		cout << *riter << endl;
	}

	return 0;
}