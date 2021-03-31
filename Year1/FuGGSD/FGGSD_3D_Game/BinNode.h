#pragma once

class BinNode
{
private:
	int _value;
	BinNode* _leftChild;
	BinNode* _rightChild;

public:
	/*=== CONSTRUCTORS===*/
	BinNode();
	BinNode(int val);
	BinNode(BinNode* nextLeft, BinNode* nextRight, int val);

	/*===DESTRUCTOR===*/
	~BinNode();

	/*=== SETTERS===*/
	void SetNextLeft(BinNode* nextLeft);
	void SetNextRight(BinNode* nextRight);

	/*=== GETTERS===*/
	int GetValue();
	BinNode* GetNextLeft();
	BinNode* GetNextRight();
};

