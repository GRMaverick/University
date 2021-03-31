#pragma once
#include "BinNode.h"
class BinTree
{
private:
	BinNode* _rootNode;
public:
	/*=== CONSTRUCTORS===*/
	BinTree(void);
	BinTree(int val);

	/*===DESTRUCTOR===*/
	~BinTree();

	void PreorderTraverse(BinNode* node);
	void InorderTraverse(BinNode* node);
	void PostorderTraverse(BinNode* node);
	void InsertLeftNode(BinNode* parent, BinNode* child);
	void InsertRightNode(BinNode* parent, BinNode* child);
	void DeleteTree(BinNode* rootNode);
	void DeleteNode(BinNode* deleteNode);

	BinNode* CreateNode(int val);
	BinNode* InsertRoot(BinNode* priorParent, BinNode* newParent);
	BinNode* DepthSeek(BinNode* rootNode, int val);
};

