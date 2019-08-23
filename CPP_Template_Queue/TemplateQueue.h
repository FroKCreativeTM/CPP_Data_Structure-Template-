#pragma once

#include <assert.h>
#include <cstring>

template <typename T>
class QueueNode
{
private:
	T data;
	QueueNode<T>* pNext;

public:
	QueueNode() : pNext(nullptr) {}
	~QueueNode() {}

private : 
	template <typename T>
	friend class TemplateQueue;
};

// 기본 배열 Queue는 앞을 Dequeue하면 그 만큼의 공간을 사용하기 곤란해진다.
// 이는 성능을 잡아먹는 괴물이 만들어지게 한다.(느려진다는 뜻이다.)
// 그래서 대체적으로 정적 Queue를 만들고 어느 정도 쓰면 끝이게 만든다.

// 그래서 대체적으로 List기반 Queue를 많이 쓰는 편이다.

template <typename T>
class TemplateQueue
{
private : 
	typedef QueueNode<T> NODE;
	typedef QueueNode<T>* PNODE;

private : 
	PNODE pFirst;
	PNODE pLast;
	int nSize;

public : 
	TemplateQueue() : pFirst(nullptr), pLast(nullptr), nSize(0) {}
	~TemplateQueue() 
	{
		Clear();
	}

public : 
	// 데이터가 들어오는 순서대로 나가는 방식이다.
	// 간단하게 대기열을 생각하면 되는데 새로 들어오는 노드는 무조건 맨 뒤에 선다.
	void Enqueue(const T& _data)
	{
		PNODE newNode = new NODE;
		newNode->data = _data;

		// 만약 마지막 노드가 nullptr인 경우 처음 추가하려는 노드라는 뜻이다.
		// 그렇기에 nullptr이 아닐 경우에만 last 다음 노드로 새로 생성한 노드를 준다.
		if (pLast)
			pLast->pNext = newNode;

		pLast = newNode;

		// first 노드가 없는 경우
		if (!pFirst)
			pFirst = newNode;

		++nSize;
	}

	// 선입선출이기 때문에 맨 앞의 데이터만 삭제를 해준다
	T Dequeue()
	{
		if (IsEmpty())
			assert(false);

		PNODE delNextNode = pFirst->pNext;
		T delData = pFirst->data;

		delete pFirst;
		pFirst = delNextNode;
		
		// pFirst가 nullptr인 경우 더 이상 데이터 구조에 데이터가 없다는 뜻이므로
		// First와 Last가 모두 nullptr이게 설정해준다.
		if (!pFirst)
			pLast = nullptr;

		--nSize;

		return delData;
	}

	void Clear()
	{
		PNODE delNode = pFirst;

		// nullptr이 나올 때 까지
		while (delNode)
		{
			PNODE delNextNode = delNode->pNext;
			delete delNode;
			delNode = delNextNode;
		}

		nSize = 0;

		pFirst = nullptr;
		pLast = nullptr;
	}

	int Size() const
	{
		return nSize;
	}

	bool IsEmpty() const
	{
		return nSize == 0;
	}

	T Front() const
	{
		if (IsEmpty())
			assert(false);

		return pFirst->data;
	}
};

// 배열 기반 Queue는 비효율적이기에 CircleQueue를 만들어서 이용한다.
template <typename T, int SIZE = 100>
class CircleQueue
{
private : 
	// CircleQueue같은 경우에는 추가, 삭제를 위해 Dummy Node를 만들어놓는다.
	// 즉, 한 칸은 반드시 비워둔다는 뜻이다.
	T QueueArray[SIZE + 1];
	int nSize;	// 데이터가 들어온 Size 컨트롤용
	int nFirst;	// 실질적 데이터가 들어있는 첫 인덱스
	int nLast;	// 실질적 데이터가 들어있는 마지막 인덱스

public : 
	CircleQueue() : nSize(0), nFirst(0), nLast(0)
	{
	}
	~CircleQueue()
	{

	}

public : 
	bool Enqueue(const T& _data)
	{
		if (Full())
			assert(false);

		int nHead = (nFirst + 1) % (SIZE + 1);

		QueueArray[nHead] = _data;
		nFirst = nHead;
		++nSize;

		return true;
	}

	T Front() const
	{
		if (IsEmpty())
			assert(false);

		int nTail = (nLast + 1) % (SIZE + 1);

		return QueueArray[nTail];
	}

	T Dequeue()
	{
		if (IsEmpty())
			assert(false);

		int nTail = (nLast + 1) % (SIZE + 1);

		T delData = QueueArray[nTail];
		nLast = nTail;
		--nSize;

		return delData;
	}

	void Clear()
	{
		nSize = 0;
		nFirst = -1;
		nLast = -1;
	}

	bool Full() const
	{
		return nSize == SIZE;
	}

	bool IsEmpty() const
	{
		return nSize == 0;
	}

	int Size() const
	{
		return nSize;
	}
};