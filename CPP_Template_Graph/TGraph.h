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

// 탐색용 멤버변수
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
//		그래프 연산용 메소드
/// =============================================
public : 
	void Insert_Vertex()
	{
		if ((nVertexSize + 1) > MAX_VERTEX)
		{
			cerr << "Graph : out of MAX_VERTEX\n";
			return;
		}
		
		cout << ++nVertexSize << "번째 버텍스 생성 완료!\n";
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
//		그래프 탐색용 메소드(DFS, BFS)
/// =============================================
public : 
	void DFS(int _nVisitVertex)
	{
		// 탐색을 위한 지역변수들
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
				cout << "정점 " << _nVisitVertex << " = > ";
				for (pSearchNode = pAdjList[_nVisitVertex]; pSearchNode; pSearchNode = pSearchNode->pNextVertex)
				{
					if (!bVisited[pSearchNode->nVertex])
					{
						bVisited[pSearchNode->nVertex] = true;
						cout << "정점 " << pSearchNode->nVertex << " = > ";
						newStack.push(pSearchNode->nVertex);
					}
				}
			}
		}
	}

	// 큐를 이용해서 너비 우선 탐색을 한다.
	// 무조건 큐에서 정점을 꺼내서 정점을 방문하고 인접 정점들을 큐에 추가하는 방식이다.
	void BFS(int _nVisitVertex)
	{
		PNODE pSearchNode;
		queue<int> newQueue;

		bVisited[_nVisitVertex] = true;
		cout << "정점 " << _nVisitVertex << " = > ";

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
					cout << "정점 " << pSearchNode->nVertex << " = > ";
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
//		기타 유틸리티용 메소드
/// =============================================
public : 
	void Print() const
	{
		for (int i = 0; i < nVertexSize; i++)
		{
			PNODE pSearchNode = pAdjList[i];
			cout << "정점 " << i << "의 인접 리스트 : ";
			while (pSearchNode)
			{
				cout << " => " << pSearchNode->nVertex;
				pSearchNode = pSearchNode->pNextVertex;
			}
			cout << endl;
		}
	}

};

