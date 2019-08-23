#pragma once

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
	}
	~CTreeNode()	{}


private : 
	CTreeNode<Key, Value>* m_pSibling;			// 형제 노드
	CTreeNode<Key, Value>* m_pChild;				// 자식노드
	Key m_Key;
	Value m_Value;
};

// Key는 목적
// Value는 데이터 저장용
template <typename Key, typename Value>
class CTree
{
private : 
	typedef CTreeNode<Key, Value> NODE;
	typedef CTreeNode<Key, Value>* PNODE;

private : 
	PNODE m_pRoot;			// 루트 노드(제일 맨 위에 있는 노드)
	int m_nSize;					// 트리에 쌓인 노드

public : 
	CTree()
	{
		m_pRoot = nullptr;
		m_nSize = 0;
	}

	~CTree()
	{

	}

public : 
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
			++m_nSize;
		}
		else
		{
			// 붙여줄 기준 노드를 찾아준다.
			PNODE pBaseNode = FindNode(BaseKey, m_pRoot);

			if (!pBaseNode)
			{
				delete newNode;
				return;
			}
			else if (pBaseNode == m_pRoot && eType == NIT_SIBLING)
			{
				delete newNode;
				return;
			}
			// 형제노드? or 자식노드로 추가?
			switch (eType)
			{
			case NIT_SIBLING:
				// 형제로 추가할 때 만약 형제가 없다면 바로 형제로 추가
				if (!pBaseNode->m_pSibling)
					pBaseNode->m_pSibling = newNode;
				else
				{
					// 기존 형제를 받아온다.
					PNODE pSibling = pBaseNode->m_pSibling;

					// 새로 생성한 노드의 형제로 기존의 형제노드를 준다.
					newNode->m_pSibling = pSibling;

					// 기준이 되는 노드의 형제로 새로 생성한다.
					pBaseNode->m_pSibling = newNode;
				}
				break;
			case NIT_CHILD:
				// 자식으로 추가할 때 만약 자식이 없다면 바로 자식으로 추가
				if (!pBaseNode->m_pChild)
					pBaseNode->m_pChild = newNode;
				else
				{
					// 기존 자식을 받아온다.
					PNODE pChild = pBaseNode->m_pChild;

					// 새로 생성한 노드의 자식으로 기존의 자식 노드를 준다.
					newNode->m_pSibling = pChild;

					// 기준이 되는 노드의 형제로 새로 생성한다.
					pBaseNode->m_pChild = newNode;
				}
				break;
			}
		}

	}

	bool IsEmpty() const
	{
		return m_nSize == 0;
	}

	int Size() const
	{
		return m_nSize;
	}


private : 
	// 재귀적인 방식으로 노드를 찾아준다.
	PNODE FindNode(const Key& _key, PNODE  pNode)
	{
		PNODE pResult = nullptr;

		if (pNode->m_Key == _key)
			return PNODE;

		// 형제 노드가 있다면 
		if(pNode->m_pSibling)
			pResult = FindNode(_key, pNode->m_pSibling);

		if (pNode->m_pChild && !pResult)
			pResult = FindNode(_key, pNode->m_pChild);

		return pResult;
	}
};

