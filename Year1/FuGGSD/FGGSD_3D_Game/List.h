#pragma once
#include "Listnode.h"

class List
{
private:
	Listnode* _head;
	Listnode* _tail;

public:
	List(void);
	List(int val);
	~List(void);

	void Traverse();
	void InsertNode(Listnode* priorNode, Listnode* newNode);
	void DeleteList(Listnode* headNode);
	void DeleteNode(Listnode* headNode);

	Listnode* CreateNode(int val);
	Listnode* InsertHead(Listnode* priorHead, Listnode* newHead);
	Listnode* Seek(Listnode* headNode, int val);
};