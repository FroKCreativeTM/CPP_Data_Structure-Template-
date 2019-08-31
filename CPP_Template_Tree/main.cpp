#include <iostream>
#include <string>

#include "CTree.h"
using namespace std;

/*
템플릿을 이용한 트리 구현 프로젝트(ver 2.0)
최종 수정일 : 190901
수정자 : 차 승철

2.0 수정 내용
cTreeNode에 부모 노드 정보도 저장할 수 있게 m_pParent 멤버변수를 추가

Insert 수정(부모 노드도 저장이 가능하게)

트리 내용을 출력을 통해 확인할 수 있게 만드는 OutputTree (기본값은 
루트노드부터 아래로 차례차례) 구현

소멸자 호출 시 Clear 메소드를 통해서 메모리 릭이 안 나게 수정
*/

int main()
{
	CTree<string, int> cTree;


	// 루트 노드 
	cTree.Insert("김두한", 10);

	// 서브 노드
	cTree.Insert("시라소니", 30, "김두한", NIT_CHILD);
	cTree.Insert("이정재", 50, "시라소니", NIT_SIBLING);
	cTree.Insert("삼수", 100, "이정재", NIT_SIBLING);
	cTree.Insert("정진영", 35, "삼수", NIT_CHILD);
	cTree.Insert("심영이 어머니", 28, "시라소니", NIT_CHILD);
	cTree.Insert("조병옥", 28, "심영이 어머니", NIT_SIBLING);

	cTree.OutputTree();

	return 0;
}