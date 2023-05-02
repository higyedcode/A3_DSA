#include "Bag.h"
#include "BagIterator.h"
#include <exception>
#include <iostream>
using namespace std;


int Bag::allocateP()
{
	if (firstFree == -1)
	{
		DLLANode* newNodes = new DLLANode[cap * 2];
		int itHead = head;
		for(long i = 0; i<cap;i++)
			newNodes[i] = nodes[i];
		for (long i = cap; i < cap * 2 - 1; i++)
		{
			newNodes[i].next = i + 1;
			newNodes[i].prev = i - 1;
			newNodes[i].frequency = 0;
		}
		newNodes[cap * 2 - 1].next = -1;
		newNodes[cap * 2 - 1].prev = cap * 2 - 2;
		newNodes[cap * 2 - 1].frequency = 0;
		delete[] nodes;
		nodes = newNodes;
		firstFree = cap;
		cap = cap * 2;
	}
	int firstFreeCopy = firstFree;
	firstFree = nodes[firstFree].next;
	return firstFreeCopy;
}

void Bag::freeP(int i)
{
	nodes[i].next = firstFree;
	firstFree = i;
}

Bag::Bag() {
	//TODO - Implementation
	head = -1;
	nodes = new DLLANode[cap];

	for (int i = 0; i < cap - 1; i++)
	{
		nodes[i].next = i + 1;
		nodes[i].frequency = 0;
	}
	nodes[cap - 1].next = -1;
	nodes[cap - 1].frequency = 0;
	for (int i = cap - 1; i > 0; i--)
		nodes[i].prev = i - 1;
	nodes[0].prev = -1;
	tail = -1;
	head = -1;
	firstFree = 0;
	
}


void Bag::add(TElem elem) {
	//TODO - Implementation
	//adding it to the beginning of bag
	int itHead = head;
	bool found = false;
	while (itHead != -1) {
		if (nodes[itHead].info == elem)
		{
			found = true;
			nodes[itHead].frequency++;
			break;
		}
		itHead = nodes[itHead].next;
	}
	if (!found)
	{
		int i = allocateP();
		nodes[i].info = elem;
		nodes[i].frequency = 1;
		nodes[i].next = head;
		nodes[head].prev = i;
		head = i;
		nodes[i].prev = -1;
		
	}
}


bool Bag::remove(TElem elem) {
	//TODO - Implementation
	if (!search(elem))
		return false;
	int itHead = head;
	int prev = -1;
	while (itHead != -1) 
	{
		if (nodes[itHead].info == elem) 
		{
			if (nodes[itHead].frequency > 1)
				nodes[itHead].frequency--;
			else if (nodes[itHead].frequency == 1)
			{
				if (itHead == head)
				{
					head = nodes[head].next;
				}
				else
				{
					nodes[prev].next = nodes[itHead].next;
				}
				this->freeP(itHead);
			}
		}
		prev = itHead;
		itHead = nodes[itHead].next;
	}
	return true;
}


bool Bag::search(TElem elem) const {
	//TODO - Implementation
	BagIterator it = this->iterator();
	while (it.valid())
	{
		if (it.getCurrent() == elem)
			return true;
		it.next();
	}
	return false; 
}

int Bag::nrOccurrences(TElem elem) const {
	//TODO - Implementation
	int itHead = head;
	while (itHead != -1) {
		if (nodes[itHead].info == elem)
			return nodes[itHead].frequency;
		itHead = nodes[itHead].next;
	}

	return 0; 
}


int Bag::size() const {
	//TODO - Implementation
	int size = 0;
	int itHead = head;
	while (itHead != -1) {
		size += nodes[itHead].frequency;
		itHead = nodes[itHead].next;
	}
	return size;
}


bool Bag::isEmpty() const {
	//TODO - Implementation
	if(size() == 0)
		return true;
	return false;
}

BagIterator Bag::iterator() const {
	return BagIterator(*this);
}


Bag::~Bag() {
	//TODO - Implementation
	delete[] nodes;
}

