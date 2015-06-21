#include "list.h"
#include <assert.h>
#include "mtmtest.h"

class IntEquals
{
	int i;

	public:
		IntEquals(int i) : i(i) { }

		bool operator()(const int& x) const {
			return x == i;
		}
};

class IntCompare
{
	public:
		bool operator()(const int& i1, const int& i2) const {
			return i1 < i2;
		}
};

bool listTest()
{
	List<int> list;
	// Insert elements to the beginning of the list:
	ASSERT_NO_THROW(list.insert(1, list.begin())); // 1
	ASSERT_NO_THROW(list.insert(2, list.begin())); // 2 1
	// Insert elements to the end of the list:
	ASSERT_NO_THROW(list.insert(3, list.end())); // 2 1 3
	ASSERT_NO_THROW(list.insert(4, list.end())); // 2 1 3 4
	// Can't dereference an iterator pointing to the end of the list
	ASSERT_THROW(ListExceptions::ElementNotFound, *list.end());
	Iterator<int> iterator = list.find(IntEquals(1));
	ASSERT_EQUALS(1, *iterator);
	Iterator<int> iterator2 = ++iterator; // iterator2 & iterator points to the same element
	ASSERT_EQUALS(3, *iterator2);
	ASSERT_EQUALS(3, *iterator);
	iterator2 = iterator++; // iterator2 points to the element iterator pointed to before incrementation
	ASSERT_EQUALS(4, *iterator);
	ASSERT_EQUALS(3, *iterator2);
	// Insert element before iterator
	ASSERT_NO_THROW(list.insert(5, iterator)); // 2 1 3 5 4
	ASSERT_EQUALS(5, list.getSize());
	// sort list in ascending order
	ASSERT_NO_THROW(list.sort(IntCompare())); // 1 2 3 4 5

	int counter = 1;
	for (Iterator<int> it = list.begin(); it != list.end(); ++it, counter++)
	{
		ASSERT_EQUALS(counter,*it);
	}

	// iterator points to the end of the list - can't use it to remove elements in the list
	ASSERT_THROW(ListExceptions::ElementNotFound, list.remove(list.end()));

	// remove first element
	ASSERT_NO_THROW(list.remove(list.begin())); // 2 3 4 5
	ASSERT_EQUALS(list.end(),list.find(IntEquals(1)));
	ASSERT_EQUALS(4, list.getSize());
	ASSERT_NO_THROW(iterator = list.begin());
	ASSERT_NO_THROW(iterator++);

	// remove an element from the middle of the list
	ASSERT_NO_THROW(list.remove(iterator)); // 2 4 5
	ASSERT_EQUALS(list.end(),list.find(IntEquals(3)));
	ASSERT_EQUALS(3, list.getSize());

	// clear list
	ASSERT_NO_THROW(list.remove(list.begin()));
	ASSERT_NO_THROW(list.remove(list.begin()));
	ASSERT_NO_THROW(list.remove(list.begin()));
	ASSERT_EQUALS(0, list.getSize());
	ASSERT_NO_THROW(iterator = list.begin());

	// list is empty - iterator points to no concrete element - can't dereference it
	ASSERT_THROW(ListExceptions::ElementNotFound, *iterator);

	// can't remove an element from an empty list
	ASSERT_THROW(ListExceptions::ElementNotFound, list.remove(list.begin()));

	List<double> doublesList;
	ASSERT_NO_THROW(doublesList.insert(3.0, doublesList.begin()));

	List<double> doublesList2;
	ASSERT_NO_THROW(doublesList2.insert(3.0, doublesList2.begin()));

	// Can't mix iterators
	ASSERT_THROW(ListExceptions::ElementNotFound, doublesList.remove(doublesList2.begin()));
	ASSERT_THROW(ListExceptions::ElementNotFound, doublesList2.insert(5.0, doublesList.begin()));
	return true;
}

int main2()
{
	RUN_TEST(listTest);
	return 0;
}
