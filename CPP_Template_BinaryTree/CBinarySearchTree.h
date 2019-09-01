#pragma once

#include <cassert>

// ���� ���� Ŭ����
// ������ �ؽ�(Ű, ���)�� �θ� �׸��� ��,������ �ڽ� ��尡
// ���� �����ϰ� �Ǿ��ִ�.
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


// ���� Ž�� Ʈ���̴�.
// �� Ʈ�� ���� ������ § ���ø��� �̿��� Ʈ���� �ٸ� ���� ����.
// �ؽ��� Ű���� ���ؼ� ������ �ȴ�.
template <typename Key, typename Value>
class CBinarySearchTree
{
private : 
	typedef CBinarySearchTreeNode<Key, Value> NODE;
	typedef CBinarySearchTreeNode<Key, Value>* PNODE;

private : 
	// �̳� Ŭ����
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
	// ������ ��Ʈ���� ������� �����ȴ�.
	PNODE m_pRoot;
	int m_nSize;

public : 
	CBinarySearchTree() :
		m_pRoot(nullptr), m_nSize(0) {}
	~CBinarySearchTree() { Clear(); }

public : 
	// NODE�� �����ؼ� ���ο� ��带 Ʈ���� �ִ� �޼ҵ��̴�.
	// ���� ����ִٸ� ���ο� ���� ��Ʈ ��忡 ���� �ǰ�
	// �ƴ϶�� �������� Ű ���� �������� ���ĵǼ� ��尡 �־�����.
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
			// �������� ã�ƶ�
			insert(_key, _value, m_pRoot);
		}

		m_nSize++;
	}

	// � Ư���� ��带 ã�� �� ���� �Լ��̴�.
	// ������� ��� assert�� ����ǰ�
	// �ƴ϶�� ��Ʈ ������ �������� Ž���Ѵ�.
	PAIR Find(const Key& _key)
	{
		if (IsEmpty())
			assert(false);

		return find(_key, m_pRoot);
	}

	// �Ҹ��ڰ� ����� �� �ڵ������� ����Ǵ� �޼ҵ�
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

//���� �۵��ϴ� �κ��� �ܺο� ����� �ʿ䰡 ���� ������ �̷� ������
// ����ȭ�� ���״�.
private : 
	void insert(const Key& _key, const Value& _value, PNODE pNode)
	{
		// �־��� Ű�� ���� ���
		if (pNode->m_Key > _key)
		{
			// �������� �߰��ؾ� �ϴµ� ���� �ڽĳ�尡 ���ٸ�
			// �����߰�
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
		// Ű ���� ũ�ų� ���� ��� ���������� ����
		else
		{
			// ���������� �߰��ؾ� �ϴµ� ������ �ڽĳ�尡 ���ٸ�
			// �����߰�
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

	// �������� Ŭ���� �޼ҵ�
	void clear(PNODE pNode)
	{
		// ���� ���� ��尡 �ִٸ�
		// ��������� ��� ���� ������
		if (pNode->m_pLeft)
			clear(pNode->m_pLeft);

		// ���� ������ ��尡 �ִٸ�
		// ��������� ��� ���� ������
		if (pNode->m_pRight)
			clear(pNode->m_pRight);

		// ���� ����Ű�� �ִ� ����� ���� �޸𸮸� �����϶�
		delete pNode;
	}

	PAIR find(const Key& _key, PNODE pNode)
	{
		// ���� ã�� ��尡 ���ٸ� NULL �ؽø� ��ȯ�϶�.
		if (!pNode)
			return PAIR();

		// ���� Ű���� ã�� Ű���� ���� �ؽð� �ִٸ�
		// �� �ؽø� �����ض�
		if (pNode->m_Key == _key)
		{
			PAIR pair;
			pair.key = pNode->m_Key;
			pair.value = pNode->m_Value;
			return pair;
		}

		// ���� ����Ű�� �ִ� Ű ���� ���� ã�� Ű������ ũ�ٸ�
		// �������� ���� ã�ƶ�.
		else if (pNode->m_Key > _key)
			return find(_key, pNode->m_pLeft);

		// ���� ����Ű�� �ִ� Ű ���� ���� ã�� Ű������ �۴ٸ�
		// ���������� ���� ã�ƶ�.
		return find(_key, pNode->m_pRight);
	}
};

