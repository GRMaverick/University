#pragma once

using namespace std;

class Listnode{
private:
	int _value;
	Listnode* _next;
public:
	Listnode(void);
	Listnode(int val);
	Listnode(int val, Listnode* next);
	~Listnode();

	int GetValue();
	Listnode* GetNext();
	void SetNext(Listnode* newNext);
};