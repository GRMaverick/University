#include "Listnode.h"


Listnode::Listnode(void){

}
Listnode::Listnode(int val){
	_value = val;
}
Listnode::Listnode(int val, Listnode* next){
	_value = val;
	_next = next;
}
Listnode::~Listnode()
{
	delete _next;
}

int Listnode::GetValue(){
	return _value;
}
Listnode* Listnode::GetNext(){
	return _next;
}
void Listnode::SetNext(Listnode* newNext){
	_next =newNext;
}



