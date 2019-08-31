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
	CTreeNode<Key, Value>* m_pSibling;			// ���� ���
	CTreeNode<Key, Value>* m_pChild;				// �ڽĳ��
	CTreeNode<Key, Value>* m_pParent;
	Key m_Key;
	Value m_Value;
};

// Key�� ����
// Value�� ������ �����
template <typename Key, typename Value>
class CTree
{
private:
	typedef CTreeNode<Key, Value> NODE;
	typedef CTreeNode<Key, Value>* PNODE;

private:
	PNODE m_pRoot;			// ��Ʈ ���(���� �� ���� �ִ� ���)
	int m_nSize;					// Ʈ���� ���� ���

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
	// ��带 �����ؼ� �̸� �ִ� �޼ҵ��̴�.
	// �� �� ����� �ִ� Ÿ�� �⺻���� ���������� �ְ� �Ǿ��ִ�.
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
		}

		// ��Ʈ ��尡 �ִ� ���
		else
		{
			// �ٿ��� ���� ��带 ã���ش�.
			PNODE pBaseNode = FindNode(BaseKey, m_pRoot);

			// ���� ��尡 �ƹ� �͵� ���ٸ�
			if (!pBaseNode)
			{
				delete newNode;
				return;
			}

			// ���� ���̽���尡 ��Ʈ ��忡 
			// ���ο� ��带 �ִ� ����� �ڽ��� �ƴ� �������
			// ���� �� �� ���� ��Ȳ(��Ʈ ���� �ݵ�� �ϳ��� �־������!)�̱� 
			// ������ �ƹ� �۾��� ���� �ʴ´�.
			else if (pBaseNode == m_pRoot && eType == NIT_SIBLING)
			{
				delete newNode;
				return;
			}

			// �������(���̽� ��尡 ��Ʈ ���� �ƴ�)
			// or �ڽĳ��� �߰�
			switch (eType)
			{
			case NIT_SIBLING:
				// ������ �߰��� �� ���� ������ ���ٸ� �ٷ� ������ �߰�
				if (!pBaseNode->m_pSibling)
				{
					// ���� ����Ű�� �ִ� ����� ���� ��忡 ���ο� ��带 �ִ´�.
					pBaseNode->m_pSibling = newNode;

					// ���� ����Ű�� �ִ� ���� ���ο� ���� ������ ������,
					// �θ� ��尡 ����.
					newNode->m_pParent = pBaseNode->m_pParent;
				}
				else
				{
					// ���� ������ �޾ƿ´�.
					PNODE pSibling = pBaseNode->m_pSibling;

					// ������ ���� �θ� ��带 ������.
					newNode->m_pParent = pSibling->m_pParent;

					// ���� ������ ����� ������ ������ ������带 �ش�.
					newNode->m_pSibling = pSibling;

					// ������ �Ǵ� ����� ������ ���� �����Ѵ�.
					pBaseNode->m_pSibling = newNode;
				}
				break;
			case NIT_CHILD:
				// �ڽ����� �߰��� �� ���� �ڽ��� ���ٸ� �ٷ� �ڽ����� �߰�
				if (!pBaseNode->m_pChild)
				{
					// ���� ����Ű�� �ִ� ����� �ڽ� ���� �߰�
					pBaseNode->m_pChild = newNode;

					// ���ο� ����� �θ���� ���� ����Ű�� �ִ� ����̴�.
					newNode->m_pParent = pBaseNode;
				}
					
				else
				{
					// ���� �ڽ��� �޾ƿ´�.
					PNODE pChild = pBaseNode->m_pChild;

					// ���� �߰��� ���� ���� �ڽ� ����� �θ� ���� ����.
					newNode->m_pParent = pChild->m_pParent;

					// ���� ������ ����� �ڽ����� ������ �ڽ� ��带 �ش�.
					newNode->m_pSibling = pChild;

					// ������ �Ǵ� ����� ������ ���� �����Ѵ�.
					pBaseNode->m_pChild = newNode;
				}
				break;
			}
		}
		m_nSize++;
	}

	// ��Ʈ ��� �� ��� ��带 ������ִ� �޼ҵ�
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
	// ������� ������� ��带 ã���ش�.
	PNODE FindNode(const Key& _key, PNODE  pNode)
	{
		PNODE pResult = nullptr;

		if (pNode->m_Key == _key)
			return pNode;

		// ���� ��尡 �ִٸ� 
		if (pNode->m_pSibling)
			pResult = FindNode(_key, pNode->m_pSibling);

		// �ڽ� ��尡 �ְ� ����Ʈ ��尡 nullptr�̸�
		// �ڽ� ��忡�� �Ű����� Ű���� ������ Ű���� ���� ��带 �˻��Ѵ�.
		if (pNode->m_pChild && !pResult)
			pResult = FindNode(_key, pNode->m_pChild);

		return pResult;
	}

	// Ư�� ��带 �޾Ƽ� �� ���� and ���� ��带 ��� ������ִ� �޼ҵ�
	void OutputTree(PNODE pNode)
	{
		cout << "===============" << pNode->m_Key << "===============" << endl;
		cout << "Key : " << pNode->m_Key << 
			"\tValue : " << pNode->m_Value << endl;

		cout << "�θ� ��� : ";
		if (!pNode->m_pParent)
			cout << "����" << endl;

		else
			cout << pNode->m_pParent->m_Key << endl;

		cout << "���� : ";
		if (!pNode->m_pSibling)
			cout << "����" << endl;
		else
			cout << pNode->m_pSibling->m_Key << endl;

		cout << "�ڽ� : ";
		if (!pNode->m_pChild)
			cout << "����" << endl;
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