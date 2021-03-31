#include "BinNode.h"

/*=== CONSTRUCTORS===*/
BinNode::BinNode(int val){
	_value = val;
	_leftChild = nullptr;
	_rightChild = nullptr;
}
BinNode::BinNode(BinNode* nextLeft, BinNode* nextRight, int val){
	_value = val;
	_leftChild = nextLeft;
	_rightChild = nextRight;
}

/*===DESTRUCTOR===*/
BinNode::~BinNode()
{
	delete _leftChild;
	delete _rightChild;
}

/*=== SETTERS===*/
void BinNode::SetNextLeft(BinNode* nextLeft){
	_leftChild = nextLeft;
}
void BinNode::SetNextRight(BinNode* nextRight){
	_rightChild = nextRight;
}

/*=== GETTERS===*/
int BinNode::GetValue(){
	return _value;
}
BinNode* BinNode::GetNextLeft(){
	return _leftChild;
}
BinNode* BinNode::GetNextRight(){
	return _rightChild;
}
