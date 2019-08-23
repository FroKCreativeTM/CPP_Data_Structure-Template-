#pragma once

template <typename T>
class TListNode
{
private :
	// 생성자와 소멸자가 private가 되면 외부에서 객체를 생성하고 객체를 해제할 수 없다.
	// 생성자는 객체를 생성할 때 자동으로 호출되는 함수인데 private로 
	// 객체를 생성하면서 호출시 접근이 불가능하다.
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


// 반복자 클래스
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


// 반복자 클래스
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
	// friend : 친구 클래스 설정
	// friend로 지정해준 클래스에서 이 클래스의 private나 protected에 접근이 가능해진다.
	// 일반 클래스는 friend만 설정해주면 되지만 템플릿 클래스인 경우에는 아래처럼 template또한 
	// 붙여줘야 한다.

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
	// 레퍼런스로 받는 이유는 훨씬 빠른 속도로 접근이 가능하기 때문이다.
	void InsertBack(const T & data)
	{
		PNODE pNode = new NODE;

		pNode->m_data = data;

		// Tail의 이전 노드가 가장 마지막 노드이다.
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