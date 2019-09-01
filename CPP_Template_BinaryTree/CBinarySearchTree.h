#pragma once

#include <cassert>

// 노드로 사용될 클래스
// 구성은 해시(키, 밸류)와 부모 그리고 왼,오른쪽 자식 노드가
// 저장 가능하게 되어있다.
template <typename Key, typename Value>
class CBinarySearchTreeNode
{
	template <typename Key, typename Value>
	friend class CBinarySearchTree;

private : 
	CBinarySearchTreeNode() :
		m_pLeft(nullptr), m_pRight(nullptr), m_pParent(nullptr)
	{}
	~CBinarySearchTreeNode() {}


private : 
	Key m_Key;
	Value m_Value;
	CBinarySearchTreeNode<Key, Value>* m_pLeft;
	CBinarySearchTreeNode<Key, Value>* m_pRight;
	CBinarySearchTreeNode<Key, Value>* m_pParent;
};


// 이진 탐색 트리이다.
// 이 트리 또한 저번에 짠 템플릿을 이용한 트리와 다른 점은 없다.
// 해시의 키값을 통해서 정렬이 된다.
template <typename Key, typename Value>
class CBinarySearchTree
{
private : 
	typedef CBinarySearchTreeNode<Key, Value> NODE;
	typedef CBinarySearchTreeNode<Key, Value>* PNODE;

private : 
	// 이너 클래스
	template <typename Key, typename Value>
	struct _tagPair
	{
		Key key;
		Value value;
	};

public : 
	typedef _tagPair<Key, Value> PAIR;
	typedef _tagPair<Key, Value>* PPAIR;

private : 
	// 구성은 루트노드와 사이즈로 구성된다.
	PNODE m_pRoot;
	int m_nSize;

public : 
	CBinarySearchTree() :
		m_pRoot(nullptr), m_nSize(0) {}
	~CBinarySearchTree() { Clear(); }

public : 
	// NODE를 생성해서 새로운 노드를 트리에 넣는 메소드이다.
	// 만약 비어있다면 새로운 노드는 루트 노드에 가게 되고
	// 아니라면 내려가서 키 값을 기준으로 정렬되서 노드가 넣어진다.
	void Insert(const Key& _key, const Value& _value)
	{
		if (IsEmpty())
		{
			m_pRoot = new NODE;

			m_pRoot->m_Key = _key;
			m_pRoot->m_Value = _value;
		}

		else
		{
			// 내려가서 찾아라
			insert(_key, _value, m_pRoot);
		}

		m_nSize++;
	}

	// 어떤 특수한 노드를 찾을 때 쓰는 함수이다.
	// 비어있을 경우 assert가 실행되고
	// 아니라면 루트 노드부터 차례차례 탐색한다.
	PAIR Find(const Key& _key)
	{
		if (IsEmpty())
			assert(false);

		return find(_key, m_pRoot);
	}

	// 소멸자가 실행될 때 자동적으로 실행되는 메소드
	void Clear()
	{
		clear(m_pRoot);
		m_nSize = 0;
		m_pRoot = nullptr;
	}

	bool IsEmpty() const
	{
		return m_nSize == 0;
	}

	int Size() const
	{
		return m_nSize;
	}

//실제 작동하는 부분은 외부에 노출될 필요가 없기 때문에 이런 식으로
// 은닉화를 시켰다.
private : 
	void insert(const Key& _key, const Value& _value, PNODE pNode)
	{
		// 넣어줄 키가 작을 경우
		if (pNode->m_Key > _key)
		{
			// 왼쪽으로 추가해야 하는데 왼쪽 자식노드가 없다면
			// 여기추가
			if (!pNode->m_pLeft)
			{
				PNODE pNewNode = new NODE;
				pNewNode->m_Key = _key;
				pNewNode->m_Value = _value;
				pNewNode->m_pParent = pNode;

				pNode->m_pLeft = pNewNode;

				return;
			}
			else
			{
				insert(_key, _value, pNode->m_pLeft);
			}
		}
		// 키 값이 크거나 같을 경우 오른쪽으로 전달
		else
		{
			// 오른쪽으로 추가해야 하는데 오른쪽 자식노드가 없다면
			// 여기추가
			if (!pNode->m_pRight)
			{
				PNODE pNewNode = new NODE;
				pNewNode->m_Key = _key;
				pNewNode->m_Value = _value;
				pNewNode->m_pParent = pNode;

				pNode->m_pRight = pNewNode;

				return;
			}
			else
			{
				insert(_key, _value, pNode->m_pRight);
			}
		}
	}

	// 실질적인 클리어 메소드
	void clear(PNODE pNode)
	{
		// 만약 왼쪽 노드가 있다면
		// 재귀적으로 계속 들어가서 지워라
		if (pNode->m_pLeft)
			clear(pNode->m_pLeft);

		// 만약 오른쪽 노드가 있다면
		// 재귀적으로 계속 들어가서 지워라
		if (pNode->m_pRight)
			clear(pNode->m_pRight);

		// 현재 가리키고 있는 노드의 동적 메모리를 해제하라
		delete pNode;
	}

	PAIR find(const Key& _key, PNODE pNode)
	{
		// 만약 찾는 노드가 없다면 NULL 해시를 반환하라.
		if (!pNode)
			return PAIR();

		// 만약 키값이 찾는 키값과 같은 해시가 있다면
		// 그 해시를 리턴해라
		if (pNode->m_Key == _key)
		{
			PAIR pair;
			pair.key = pNode->m_Key;
			pair.value = pNode->m_Value;
			return pair;
		}

		// 만약 가리키고 있는 키 값이 현재 찾는 키값보다 크다면
		// 왼쪽으로 가서 찾아라.
		else if (pNode->m_Key > _key)
			return find(_key, pNode->m_pLeft);

		// 만약 가리키고 있는 키 값이 현재 찾는 키값보다 작다면
		// 오른쪽으로 가서 찾아라.
		return find(_key, pNode->m_pRight);
	}
};

