#include <iostream>
#include <string>

#include "CBinarySearchTree.h"

using namespace std;

/*
이진 트리 : 자식 노드가 최대 2개까지만 만들 수 있는 트리이다.


이진 탐색 트리 : 이진 트리를 이용한 원하는 값의 탐색을 최적화한 알고리즘
특징 : 추가하고자 하는 값이 현재 노드의 값보다 작을 경우 왼쪽
클 경우 오른쪽 자식으로 추가하게 한다.
장점 : 탐색 속도가 빠르다.(O(logn))
*/

int main()
{
	CBinarySearchTree<int, string> cBSTree;

	cBSTree.Insert(37, "김두한");
	cBSTree.Insert(20, "시라소니");
	cBSTree.Insert(57, "심영");
	cBSTree.Insert(14, "조병옥");

	CBinarySearchTree<int, string>::PAIR pair = cBSTree.Find(14);
	cout << pair.key << "\t" << pair.value << endl;
	pair = cBSTree.Find(100);
	cout << pair.key << "\t" << pair.value << endl;
	pair = cBSTree.Find(20);
	cout << pair.key << "\t" << pair.value << endl;

	return 0;
}