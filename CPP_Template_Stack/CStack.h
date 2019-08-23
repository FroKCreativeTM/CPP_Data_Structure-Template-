#pragma once

#include <cassert>

template <typename T>
class CStackNode
{
private : 
	template <typename T>
	friend class CStack;

private:
	CStackNode<T>* m_pNext;
	T m_data;

public : 
	CStackNode() : m_pNext(nullptr) {}
	~CStackNode() {}

};

template <typename T>
class CStack
{
private : 
	typedef CStackNode<T> NODE;
	typedef CStackNode<T>* PNODE;

private : 
	PNODE m_pNode;
	int m_iSize;

public:
	CStack() : m_pNode(nullptr),
		m_iSize(0)
	{

	}
	~CStack()
	{
		Clear();
	}

public : 
	bool IsEmpty() const
	{
		return m_iSize == 0;
	}

	void Push(const T& data)
	{
		PNODE newNode = new NODE;

		newNode->m_data = data;

		newNode->m_pNext = m_pNode;
		m_pNode = newNode;

		m_iSize++;
	}

	T Pop()
	{
		// assert 함수는 정해진 조건이 맞지 않을 경우 프로그램을 중단한다.
		// 즉 assert에 지정한 조건식이 거짓(false)일 때 프로그램을 중단한다.
		if (IsEmpty())
			assert(false);

		PNODE delNextNode = m_pNode->m_pNext;
		T delData = m_pNode->m_data;

		delete m_pNode;
		m_pNode = delNextNode;

		m_iSize--;

		return delData;
	}

	void Clear()
	{
		PNODE delNode = m_pNode;

		// delNode가 nullptr이 아닌 경우
		while (delNode)
		{
			PNODE delNextNode = delNode->m_pNext;
			delete delNode;
			delNode = delNextNode;
		}

		m_iSize = 0;
	}

	T Peek() const
	{
		if (IsEmpty())
			assert(false);

		return m_pNode->m_data;
	}

	int Size() const
	{
		return m_iSize;
	}
};