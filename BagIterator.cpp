#include <exception>
#include "BagIterator.h"
#include "Bag.h"

using namespace std;


BagIterator::BagIterator(const Bag& c): bag(c)
{
	//TODO - Implementation
	current = c.head;
	freq = bag.nodes[current].frequency;
}

void BagIterator::first() {
	//TODO - Implementation
	current = bag.head;
	freq = bag.nodes[current].frequency;
}


void BagIterator::next() {
	//TODO - Implementation
	if (!valid()) throw exception();
	if (freq > 1)
		freq--;
	else
	{
		current = bag.nodes[current].next;
		freq = bag.nodes[current].frequency;
	}

}


bool BagIterator::valid() const {
	//TODO - Implementation
	return (current != -1 || freq > 0);
}



TElem BagIterator::getCurrent() const
{
	//TODO - Implementation
	if (!valid()) throw exception();
	return bag.nodes[current].info;
}
