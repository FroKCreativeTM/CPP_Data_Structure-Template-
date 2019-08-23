#include <iostream>
#include "TemplateQueue.h"
using namespace std;

int main()
{
	//TemplateQueue<int> tQueue;

	//for (int i = 0; i < 10; i++)
	//{
	//	tQueue.Enqueue(i + 1);
	//}

	//cout << tQueue.Size() << "\n";
	//
	//for (int i = 0; i < 10; i++)
	//{
	//	cout << tQueue.Dequeue() << "\n";
	//}

	CircleQueue<int, 10> circleQueue;

	for (int i = 0; i < 10; i++)
	{
		circleQueue.Enqueue(i);
	}

	cout << "Size : " << circleQueue.Size() << "\n";

	cout << "Dequeue 이전\n";
	for (int i = 0; i < 5; i++)
	{
		cout << circleQueue.Dequeue() << endl;
	}

	cout << "Size : " << circleQueue.Size() << "\n";
	for (int i = 0; i < 5; i++)
	{
		circleQueue.Enqueue(i);
	}

	cout << "Dequeue 이후\n";
	for (int i = 0; i < 10; i++)
	{
		cout << circleQueue.Dequeue() << endl;
	}

	return 0;
}