#pragma once

#include <iostream>

// for DFS
#include <stack>

// For BFS
#include <queue>
using namespace std;

class GraphNode
{
private : 
	int nVertex;
	GraphNode* pNextVertex;

private: 
	template <int MAX_VERTEX = 50>
	friend class TGraph;
};

template < int MAX_VERTEX = 50>
class TGraph
{
private : 
	typedef GraphNode NODE;
	typedef GraphNode* PNODE;

private : 
	int nVertexSize;
	PNODE pAdjList[MAX_VERTEX];

// Ž���� �������
private: 
	bool bVisited[MAX_VERTEX];

public : 
	TGraph() : nVertexSize(0)
	{
		for (int i = 0; i < MAX_VERTEX; i++)
		{
			pAdjList[i] = nullptr;
			bVisited[i] = false;
		}			
	}

	~TGraph() {}


/// =============================================
//		�׷��� ����� �޼ҵ�
/// =============================================
public : 
	void Insert_Vertex()
	{
		if ((nVertexSize + 1) > MAX_VERTEX)
		{
			cerr << "Graph : out of MAX_VERTEX\n";
			return;
		}
		
		cout << ++nVertexSize << "��° ���ؽ� ���� �Ϸ�!\n";
	}

	void Insert_Edge(int _start, int _end)
	{
		if (_start >= nVertexSize || _end >= nVertexSize)
		{
			cerr << "Graph : vertex number error\n";
			return;
		}

		PNODE newNode = new NODE;

		newNode->nVertex = _end;
		newNode->pNextVertex = pAdjList[_start];

		pAdjList[_start] = newNode;
	}

/// =============================================
//		�׷��� Ž���� �޼ҵ�(DFS, BFS)
/// =============================================
public : 
	void DFS(int _nVisitVertex)
	{
		// Ž���� ���� ����������
		PNODE pSearchNode;
		stack<int> newStack;

		newStack.push(_nVisitVertex);
		
		while (!newStack.empty())
		{
			_nVisitVertex = newStack.top();
			newStack.pop();
			if (!bVisited[_nVisitVertex])
			{
				bVisited[_nVisitVertex] = true;
				cout << "���� " << _nVisitVertex << " = > ";
				for (pSearchNode = pAdjList[_nVisitVertex]; pSearchNode; pSearchNode = pSearchNode->pNextVertex)
				{
					if (!bVisited[pSearchNode->nVertex])
					{
						bVisited[pSearchNode->nVertex] = true;
						cout << "���� " << pSearchNode->nVertex << " = > ";
						newStack.push(pSearchNode->nVertex);
					}
				}
			}
		}
	}

	// ť�� �̿��ؼ� �ʺ� �켱 Ž���� �Ѵ�.
	// ������ ť���� ������ ������ ������ �湮�ϰ� ���� �������� ť�� �߰��ϴ� ����̴�.
	void BFS(int _nVisitVertex)
	{
		PNODE pSearchNode;
		queue<int> newQueue;

		bVisited[_nVisitVertex] = true;
		cout << "���� " << _nVisitVertex << " = > ";

		newQueue.push(_nVisitVertex);
		while (!newQueue.empty())
		{
			_nVisitVertex = newQueue.front();
			newQueue.pop();
			for (pSearchNode = pAdjList[_nVisitVertex]; pSearchNode; pSearchNode = pSearchNode->pNextVertex)
			{
				if (!bVisited[pSearchNode->nVertex])
				{
					bVisited[pSearchNode->nVertex] = true;
					cout << "���� " << pSearchNode->nVertex << " = > ";
					newQueue.push(pSearchNode->nVertex);
				}
			}
		}

	}

	void SearchAfter()
	{
		for (int i = 0; i < MAX_VERTEX; i++)
			bVisited[i] = false;
	}

/// =============================================
//		��Ÿ ��ƿ��Ƽ�� �޼ҵ�
/// =============================================
public : 
	void Print() const
	{
		for (int i = 0; i < nVertexSize; i++)
		{
			PNODE pSearchNode = pAdjList[i];
			cout << "���� " << i << "�� ���� ����Ʈ : ";
			while (pSearchNode)
			{
				cout << " => " << pSearchNode->nVertex;
				pSearchNode = pSearchNode->pNextVertex;
			}
			cout << endl;
		}
	}

};

