#include <iostream>
#include <string>

#include "CBinarySearchTree.h"

using namespace std;

/*
���� Ʈ�� : �ڽ� ��尡 �ִ� 2�������� ���� �� �ִ� Ʈ���̴�.


���� Ž�� Ʈ�� : ���� Ʈ���� �̿��� ���ϴ� ���� Ž���� ����ȭ�� �˰���
Ư¡ : �߰��ϰ��� �ϴ� ���� ���� ����� ������ ���� ��� ����
Ŭ ��� ������ �ڽ����� �߰��ϰ� �Ѵ�.
���� : Ž�� �ӵ��� ������.(O(logn))
*/

int main()
{
	CBinarySearchTree<int, string> cBSTree;

	cBSTree.Insert(37, "�����");
	cBSTree.Insert(20, "�ö�Ҵ�");
	cBSTree.Insert(57, "�ɿ�");
	cBSTree.Insert(14, "������");

	CBinarySearchTree<int, string>::PAIR pair = cBSTree.Find(14);
	cout << pair.key << "\t" << pair.value << endl;
	pair = cBSTree.Find(100);
	cout << pair.key << "\t" << pair.value << endl;
	pair = cBSTree.Find(20);
	cout << pair.key << "\t" << pair.value << endl;

	return 0;
}