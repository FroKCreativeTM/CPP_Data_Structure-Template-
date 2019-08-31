#include <iostream>
#include <string>

#include "CTree.h"
using namespace std;

/*
���ø��� �̿��� Ʈ�� ���� ������Ʈ(ver 2.0)
���� ������ : 190901
������ : �� ��ö

2.0 ���� ����
cTreeNode�� �θ� ��� ������ ������ �� �ְ� m_pParent ��������� �߰�

Insert ����(�θ� ��嵵 ������ �����ϰ�)

Ʈ�� ������ ����� ���� Ȯ���� �� �ְ� ����� OutputTree (�⺻���� 
��Ʈ������ �Ʒ��� ��������) ����

�Ҹ��� ȣ�� �� Clear �޼ҵ带 ���ؼ� �޸� ���� �� ���� ����
*/

int main()
{
	CTree<string, int> cTree;


	// ��Ʈ ��� 
	cTree.Insert("�����", 10);

	// ���� ���
	cTree.Insert("�ö�Ҵ�", 30, "�����", NIT_CHILD);
	cTree.Insert("������", 50, "�ö�Ҵ�", NIT_SIBLING);
	cTree.Insert("���", 100, "������", NIT_SIBLING);
	cTree.Insert("������", 35, "���", NIT_CHILD);
	cTree.Insert("�ɿ��� ��Ӵ�", 28, "�ö�Ҵ�", NIT_CHILD);
	cTree.Insert("������", 28, "�ɿ��� ��Ӵ�", NIT_SIBLING);

	cTree.OutputTree();

	return 0;
}