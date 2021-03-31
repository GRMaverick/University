#include <iostream>
#include "BinTree.h"
using namespace std;

/*=== CONSTRUCTORS===*/
BinTree::BinTree(){
}
BinTree::BinTree(int val){
	
}

/*===DESTRUCTOR===*/
BinTree::~BinTree(){
	DeleteTree(_rootNode);
}

void BinTree::PreorderTraverse(BinNode* node){
	cout << node->GetValue() << endl;
	if (node->GetNextLeft() != nullptr)
		PreorderTraverse(node->GetNextLeft());
	if (node->GetNextRight() != nullptr)
		PreorderTraverse(node->GetNextRight());
}
void BinTree::InorderTraverse(BinNode* node){
	if (node->GetNextLeft() != nullptr)
		InorderTraverse(node->GetNextLeft());
	cout << node->GetValue() << endl;
	if (node->GetNextLeft() != nullptr)
		InorderTraverse(node->GetNextRight());
}
void BinTree::PostorderTraverse(BinNode* node){
	if (node->GetNextLeft != nullptr)
		PostorderTraverse(node->GetNextLeft());
	if (node->GetNextRight() != nullptr)
		PostorderTraverse(node->GetNextRight());
	cout << node->GetValue() << endl;
}

void BinTree::InsertLeftNode(BinNode* parent, BinNode* child){
	parent->SetNextLeft(child);
}
void BinTree::InsertRightNode(BinNode* parent, BinNode* child){
	parent->SetNextRight(child);
}
//Complete delete interfaces
void BinTree::DeleteTree(BinNode* rootNode){
}
void BinTree::DeleteNode(BinNode* deleteNode){
}

BinNode* CreateNode(int val){
	BinNode* newNode = new BinNode(val);
	return newNode;
}
//Complete InsertRoot interface
BinNode* InsertRoot(BinNode* priorParent, BinNode* newParent){

}
BinNode* DepthSeek(BinNode* rootNode, int val){
	BinNode* retNode;

	if (rootNode->GetValue() == val)
		return rootNode;
	if (rootNode->GetNextLeft() != nullptr)
		retNode = DepthSeek(rootNode->GetNextLeft(), val);
	if (retNode == nullptr && rootNode->GetNextRight() != nullptr)
		retNode = DepthSeek(rootNode->GetNextRight(), val);

	return retNode;
}