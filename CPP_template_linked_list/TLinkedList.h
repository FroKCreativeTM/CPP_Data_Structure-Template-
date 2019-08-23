#pragma once

template <typename T>
class TListNode
{
private :
	// �����ڿ� �Ҹ��ڰ� private�� �Ǹ� �ܺο��� ��ü�� �����ϰ� ��ü�� ������ �� ����.
	// �����ڴ� ��ü�� ������ �� �ڵ����� ȣ��Ǵ� �Լ��ε� private�� 
	// ��ü�� �����ϸ鼭 ȣ��� ������ �Ұ����ϴ�.
	TListNode()
		: m_pNext(NULL),
		m_pPrev(NULL)
	{

	}
	~TListNode()
	{

	}

private : 
	template <typename T>
	friend class TLinkedList;
	template <typename T>
	friend class TListIterator;
	template <typename T>
	friend class TListReverseIterator;

private:
	T m_data;
	TListNode<T> * m_pNext;
	TListNode<T> * m_pPrev;
};


// �ݺ��� Ŭ����
template <typename T>
class TListIterator
{
private : 
	template <typename T>
	friend class TListNode;
	template <typename T>
	friend class TLinkedList;

public:
	TListIterator()
	{

	}

	~TListIterator()
	{

	}

private : 
	typedef TListNode<T> NODE;
	typedef TListNode<T>* PNODE;
	   
private :
	PNODE m_pNode;

public : 
	bool operator == (const TListIterator<T>& iter)
	{
		return m_pNode == iter.m_pNode;
	}

	bool operator != (const TListIterator<T>& iter)
	{
		return m_pNode != iter.m_pNode;
	}

	void operator ++()
	{
		m_pNode = m_pNode->m_pNext;
	}

	void operator --()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	T operator *()
	{
		return m_pNode->m_data;
	}
};


// �ݺ��� Ŭ����
template <typename T>
class TListReverseIterator
{
private:
	template <typename T>
	friend class TListNode;
	template <typename T>
	friend class TLinkedList;

public:
	TListReverseIterator()
	{

	}

	~TListReverseIterator()
	{

	}

private:
	typedef TListNode<T> NODE;
	typedef TListNode<T>* PNODE;

private:


private:
	PNODE m_pNode;

public:
	bool operator == (const TListReverseIterator<T>& riter)
	{
		return m_pNode == riter.m_pNode;
	}

	bool operator != (const TListReverseIterator<T>& riter)
	{
		return m_pNode != riter.m_pNode;
	}

	void operator ++()
	{
		m_pNode = m_pNode->m_pPrev;
	}

	void operator --()
	{
		m_pNode = m_pNode->m_pNext;
	}

	T operator *()
	{
		return m_pNode->m_data;
	}
};

template <typename T>
class TLinkedList
{
private : 
	// friend : ģ�� Ŭ���� ����
	// friend�� �������� Ŭ�������� �� Ŭ������ private�� protected�� ������ ����������.
	// �Ϲ� Ŭ������ friend�� �������ָ� ������ ���ø� Ŭ������ ��쿡�� �Ʒ�ó�� template���� 
	// �ٿ���� �Ѵ�.

private : 
	typedef TListNode<T> NODE;
	typedef TListNode<T>* PNODE;

private : 
	PNODE m_pHead;
	PNODE m_pTail;
	unsigned int m_iSize;

public : 
	typedef TListIterator<T> iterator;
	typedef TListReverseIterator<T> reverseiterator;

public:
	TLinkedList()
	{
		m_pHead = new NODE;
		m_pTail = new NODE;

		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;

		m_iSize = 0;
	}
	~TLinkedList()
	{
		clear();
		delete m_pHead;
		delete m_pTail;
		m_iSize = 0;
	}
	
public : 
	// ���۷����� �޴� ������ �ξ� ���� �ӵ��� ������ �����ϱ� �����̴�.
	void InsertBack(const T & data)
	{
		PNODE pNode = new NODE;

		pNode->m_data = data;

		// Tail�� ���� ��尡 ���� ������ ����̴�.
		PNODE pPrev = m_pTail->m_pPrev;

		pPrev->m_pNext = pNode;
		pNode->m_pPrev = pPrev;

		pNode->m_pNext = m_pTail;
		m_pTail->m_pPrev = pNode;

		(m_iSize)++;
	}

	void InsertFront(const T & data)
	{
		PNODE pNode = new NODE;
		pNode->m_data = data;

		PNODE pNext = m_pHead->m_pNext;

		pNext->m_pPrev = pNode;
		pNode->m_pNext = pNext;

		pNode->m_pPrev = m_pHead;
		m_pHead->m_pNext = pNode;

		(m_iSize)++;
	}

	unsigned int size() const
	{
		return m_iSize; 
	}

	bool empty() const
	{
		return m_iSize == 0;
	}

	void clear()
	{
		PNODE delNode = m_pHead->m_pNext;

		while (delNode != m_pTail)
		{
			PNODE delNextNode = delNode->m_pNext;
			delete delNode;
			delNode = delNextNode;
		}

		m_pHead->m_pNext = m_pTail;
		m_pTail->m_pPrev = m_pHead;
		m_iSize = 0;
	}

	iterator begin()
	{
		iterator iter;
		iter.m_pNode = m_pHead->m_pNext;
		return iter;
	}

	iterator end()
	{
		iterator iter;
		iter.m_pNode = m_pTail;
		return iter;
	}

	reverseiterator rbegin()
	{
		reverseiterator riter;
		riter.m_pNode = m_pTail->m_pPrev;
		return riter;
	}

	reverseiterator rend()
	{
		reverseiterator riter;
		riter.m_pNode = m_pHead;
		return riter;
	}
};