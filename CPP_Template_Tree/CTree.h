#pragma once

#include <cassert>
#include <iostream>

using namespace std;

enum NODE_INSERT_TYPE
{
	NIT_SIBLING,
	NIT_CHILD
};

template <typename Key, typename Value>
class CTreeNode
{
private:
	template <typename Key, typename Value>
	friend class CTree;

private:
	CTreeNode()	
	{
		m_pSibling = nullptr;
		m_pChild = nullptr;
		m_pParent = nullptr;
	}
	~CTreeNode()	{}


private : 
	CTreeNode<Key, Value>* m_pSibling;			// 형제 노드
	CTreeNode<Key, Value>* m_pChild;				// 자식노드
	CTreeNode<Key, Value>* m_pParent;
	Key m_Key;
	Value m_Value;
};

// Key는 목적
// Value는 데이터 저장용
template <typename Key, typename Value>
class CTree
{
private:
	typedef CTreeNode<Key, Value> NODE;
	typedef CTreeNode<Key, Value>* PNODE;

private:
	PNODE m_pRoot;			// 루트 노드(제일 맨 위에 있는 노드)
	int m_nSize;					// 트리에 쌓인 노드

public:
	CTree()
	{
		m_pRoot = nullptr;
		m_nSize = 0;
	}

	~CTree()
	{
		Clear();
	}

public:
	// 노드를 생성해서 이를 넣는 메소드이다.
	// 이 때 노드의 넣는 타입 기본값은 형제값으로 넣게 되어있다.
	void Insert(const Key& _key, const Value& _val,
		const Key& BaseKey = Key(), NODE_INSERT_TYPE eType = NIT_SIBLING)
	{
		// 새로운 노드 생성
		PNODE newNode = new NODE;

		newNode->m_Key = _key;
		newNode->m_Value = _val;

		// 루트 노드가 nullptr인 경우 처음 추가하는 노드라는 것이다.
		if (!m_pRoot)
		{
			// 중요! 루트 노드는 오로지 자식 노드만 가진다.
			m_pRoot = newNode;
		}

		// 루트 노드가 있는 경우
		else
		{
			// 붙여줄 기준 노드를 찾아준다.
			PNODE pBaseNode = FindNode(BaseKey, m_pRoot);

			// 만약 노드가 아무 것도 없다면
			if (!pBaseNode)
			{
				delete newNode;
				return;
			}

			// 만약 베이스노드가 루트 노드에 
			// 새로운 노드를 넣는 방식이 자식이 아닌 형제라면
			// 말이 될 수 없는 상황(루트 노드는 반드시 하나만 있어야하지!)이기 
			// 때문에 아무 작업도 하지 않는다.
			else if (pBaseNode == m_pRoot && eType == NIT_SIBLING)
			{
				delete newNode;
				return;
			}

			// 형제노드(베이스 노드가 루트 노드는 아님)
			// or 자식노드로 추가
			switch (eType)
			{
			case NIT_SIBLING:
				// 형제로 추가할 때 만약 형제가 없다면 바로 형제로 추가
				if (!pBaseNode->m_pSibling)
				{
					// 지금 가리키고 있는 노드의 형제 노드에 새로운 노드를 넣는다.
					pBaseNode->m_pSibling = newNode;

					// 지금 가리키고 있는 노드와 새로운 노드는 형제기 때문에,
					// 부모 노드가 같다.
					newNode->m_pParent = pBaseNode->m_pParent;
				}
				else
				{
					// 기존 형제를 받아온다.
					PNODE pSibling = pBaseNode->m_pSibling;

					// 형제와 같은 부모 노드를 가진다.
					newNode->m_pParent = pSibling->m_pParent;

					// 새로 생성한 노드의 형제로 기존의 형제노드를 준다.
					newNode->m_pSibling = pSibling;

					// 기준이 되는 노드의 형제로 새로 생성한다.
					pBaseNode->m_pSibling = newNode;
				}
				break;
			case NIT_CHILD:
				// 자식으로 추가할 때 만약 자식이 없다면 바로 자식으로 추가
				if (!pBaseNode->m_pChild)
				{
					// 현재 가리키고 있는 노드의 자식 노드로 추가
					pBaseNode->m_pChild = newNode;

					// 새로운 노드의 부모노드는 현재 가리키고 있는 노드이다.
					newNode->m_pParent = pBaseNode;
				}
					
				else
				{
					// 기존 자식을 받아온다.
					PNODE pChild = pBaseNode->m_pChild;

					// 새로 추가된 노드는 기존 자식 노드의 부모 노드와 같다.
					newNode->m_pParent = pChild->m_pParent;

					// 새로 생성한 노드의 자식으로 기존의 자식 노드를 준다.
					newNode->m_pSibling = pChild;

					// 기준이 되는 노드의 형제로 새로 생성한다.
					pBaseNode->m_pChild = newNode;
				}
				break;
			}
		}
		m_nSize++;
	}

	// 루트 노드 하 모든 노드를 출력해주는 메소드
	void OutputTree()
	{
		if (IsEmpty())
			return;

		OutputTree(m_pRoot);
	}

	bool IsEmpty() const
	{
		return m_nSize == 0;
	}

	int Size() const
	{
		return m_nSize;
	}

	void Clear()
	{
		Clear(m_pRoot);

		m_pRoot = nullptr;
		m_nSize = 0;
	}

private:
	// 재귀적인 방식으로 노드를 찾아준다.
	PNODE FindNode(const Key& _key, PNODE  pNode)
	{
		PNODE pResult = nullptr;

		if (pNode->m_Key == _key)
			return pNode;

		// 형제 노드가 있다면 
		if (pNode->m_pSibling)
			pResult = FindNode(_key, pNode->m_pSibling);

		// 자식 노드가 있고 리절트 노드가 nullptr이면
		// 자식 노드에서 매개변수 키값과 동일한 키값을 가진 노드를 검색한다.
		if (pNode->m_pChild && !pResult)
			pResult = FindNode(_key, pNode->m_pChild);

		return pResult;
	}

	// 특정 노드를 받아서 그 하위 and 형제 노드를 모두 출력해주는 메소드
	void OutputTree(PNODE pNode)
	{
		cout << "===============" << pNode->m_Key << "===============" << endl;
		cout << "Key : " << pNode->m_Key << 
			"\tValue : " << pNode->m_Value << endl;

		cout << "부모 노드 : ";
		if (!pNode->m_pParent)
			cout << "없음" << endl;

		else
			cout << pNode->m_pParent->m_Key << endl;

		cout << "형제 : ";
		if (!pNode->m_pSibling)
			cout << "없음" << endl;
		else
			cout << pNode->m_pSibling->m_Key << endl;

		cout << "자식 : ";
		if (!pNode->m_pChild)
			cout << "없음" << endl;
		else
			cout << pNode->m_pChild->m_Key << endl;

		if (pNode->m_pSibling)
			OutputTree(pNode->m_pSibling);

		cout << endl;

		if (pNode->m_pChild)
			OutputTree(pNode->m_pChild);
	}

	void Clear(PNODE pNode)
	{
		if (pNode->m_pSibling)
			Clear(pNode->m_pSibling);
		if(pNode->m_pChild)
			Clear(pNode->m_pChild);

		delete pNode;
	}
};