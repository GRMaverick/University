#include <iostream>
#include "List.h"

using namespace std;
/*=== CONSTRUCTORS===*/
List::List(void){
	_head = _tail = nullptr;
}
List::List(int val){
	_head = new Listnode(val);
	_tail = _head;
}

/*===DESTRUCTOR===*/
List::~List(void){
	DeleteList(_head);
}

void List::Traverse(){
	Listnode* node = _head;
	
	if (_head == nullptr){
		cout << "ERROR: List is empty!" << endl;
		return;
	}

	cout << "List";
	while (node != nullptr){
		cout << node->GetValue();
		node = node->GetNext();
	}
	cout << endl;
}
void List::InsertNode(Listnode* priorNode, Listnode* newNode){
	newNode->SetNext(priorNode->GetNext());
	priorNode->SetNext(priorNode);
}
void List::DeleteList(Listnode* headNode){
	Listnode * tempNode = nullptr;
	while (headNode != nullptr){
		tempNode = headNode;
		headNode = headNode->GetNext();
		delete tempNode;
	}
}
void List::DeleteNode(Listnode* headNode){
	Listnode* tempNode = nullptr;
	if (headNode != nullptr && headNode->GetNext() != nullptr){
		tempNode->SetNext(headNode);
		headNode->SetNext(tempNode->GetNext());
		delete tempNode;
	}
}

Listnode* List::CreateNode(int val){
	Listnode* newNode = new Listnode(val);
	return newNode;
}
Listnode* List::InsertHead(Listnode* priorHead, Listnode* newHead){
	newHead->SetNext(priorHead);
	return newHead;
}
Listnode* List::Seek(Listnode* headNode, int val){
	while (headNode != nullptr){
		if (headNode->GetValue() == val)
			return headNode;
		headNode = headNode->GetNext();
	}
	return nullptr;
}
