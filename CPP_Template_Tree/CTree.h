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
	CTreeNode<Key, Value>* m_pSibling;			// ���� ���
	CTreeNode<Key, Value>* m_pChild;				// �ڽĳ��
	Key m_Key;
	Value m_Value;
};

// Key�� ����
// Value�� ������ �����
template <typename Key, typename Value>
class CTree
{
private : 
	typedef CTreeNode<Key, Value> NODE;
	typedef CTreeNode<Key, Value>* PNODE;

private : 
	PNODE m_pRoot;			// ��Ʈ ���(���� �� ���� �ִ� ���)
	int m_nSize;					// Ʈ���� ���� ���

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
		// ���ο� ��� ����
		PNODE newNode = new NODE;

		newNode->m_Key = _key;
		newNode->m_Value = _val;

		// ��Ʈ ��尡 nullptr�� ��� ó�� �߰��ϴ� ����� ���̴�.
		if (!m_pRoot)
		{
			// �߿�! ��Ʈ ���� ������ �ڽ� ��常 ������.
			m_pRoot = newNode;
			++m_nSize;
		}
		else
		{
			// �ٿ��� ���� ��带 ã���ش�.
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
			// �������? or �ڽĳ��� �߰�?
			switch (eType)
			{
			case NIT_SIBLING:
				// ������ �߰��� �� ���� ������ ���ٸ� �ٷ� ������ �߰�
				if (!pBaseNode->m_pSibling)
					pBaseNode->m_pSibling = newNode;
				else
				{
					// ���� ������ �޾ƿ´�.
					PNODE pSibling = pBaseNode->m_pSibling;

					// ���� ������ ����� ������ ������ ������带 �ش�.
					newNode->m_pSibling = pSibling;

					// ������ �Ǵ� ����� ������ ���� �����Ѵ�.
					pBaseNode->m_pSibling = newNode;
				}
				break;
			case NIT_CHILD:
				// �ڽ����� �߰��� �� ���� �ڽ��� ���ٸ� �ٷ� �ڽ����� �߰�
				if (!pBaseNode->m_pChild)
					pBaseNode->m_pChild = newNode;
				else
				{
					// ���� �ڽ��� �޾ƿ´�.
					PNODE pChild = pBaseNode->m_pChild;

					// ���� ������ ����� �ڽ����� ������ �ڽ� ��带 �ش�.
					newNode->m_pSibling = pChild;

					// ������ �Ǵ� ����� ������ ���� �����Ѵ�.
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
	// ������� ������� ��带 ã���ش�.
	PNODE FindNode(const Key& _key, PNODE  pNode)
	{
		PNODE pResult = nullptr;

		if (pNode->m_Key == _key)
			return PNODE;

		// ���� ��尡 �ִٸ� 
		if(pNode->m_pSibling)
			pResult = FindNode(_key, pNode->m_pSibling);

		if (pNode->m_pChild && !pResult)
			pResult = FindNode(_key, pNode->m_pChild);

		return pResult;
	}
};

