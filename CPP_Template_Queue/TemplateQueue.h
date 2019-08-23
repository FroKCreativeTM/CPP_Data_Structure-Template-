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

// �⺻ �迭 Queue�� ���� Dequeue�ϸ� �� ��ŭ�� ������ ����ϱ� ���������.
// �̴� ������ ��ƸԴ� ������ ��������� �Ѵ�.(�������ٴ� ���̴�.)
// �׷��� ��ü������ ���� Queue�� ����� ��� ���� ���� ���̰� �����.

// �׷��� ��ü������ List��� Queue�� ���� ���� ���̴�.

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
	// �����Ͱ� ������ ������� ������ ����̴�.
	// �����ϰ� ��⿭�� �����ϸ� �Ǵµ� ���� ������ ���� ������ �� �ڿ� ����.
	void Enqueue(const T& _data)
	{
		PNODE newNode = new NODE;
		newNode->data = _data;

		// ���� ������ ��尡 nullptr�� ��� ó�� �߰��Ϸ��� ����� ���̴�.
		// �׷��⿡ nullptr�� �ƴ� ��쿡�� last ���� ���� ���� ������ ��带 �ش�.
		if (pLast)
			pLast->pNext = newNode;

		pLast = newNode;

		// first ��尡 ���� ���
		if (!pFirst)
			pFirst = newNode;

		++nSize;
	}

	// ���Լ����̱� ������ �� ���� �����͸� ������ ���ش�
	T Dequeue()
	{
		if (IsEmpty())
			assert(false);

		PNODE delNextNode = pFirst->pNext;
		T delData = pFirst->data;

		delete pFirst;
		pFirst = delNextNode;
		
		// pFirst�� nullptr�� ��� �� �̻� ������ ������ �����Ͱ� ���ٴ� ���̹Ƿ�
		// First�� Last�� ��� nullptr�̰� �������ش�.
		if (!pFirst)
			pLast = nullptr;

		--nSize;

		return delData;
	}

	void Clear()
	{
		PNODE delNode = pFirst;

		// nullptr�� ���� �� ����
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

// �迭 ��� Queue�� ��ȿ�����̱⿡ CircleQueue�� ���� �̿��Ѵ�.
template <typename T, int SIZE = 100>
class CircleQueue
{
private : 
	// CircleQueue���� ��쿡�� �߰�, ������ ���� Dummy Node�� �������´�.
	// ��, �� ĭ�� �ݵ�� ����дٴ� ���̴�.
	T QueueArray[SIZE + 1];
	int nSize;	// �����Ͱ� ���� Size ��Ʈ�ѿ�
	int nFirst;	// ������ �����Ͱ� ����ִ� ù �ε���
	int nLast;	// ������ �����Ͱ� ����ִ� ������ �ε���

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