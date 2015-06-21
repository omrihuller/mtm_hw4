#ifndef LIST_H_
#define LIST_H_

#include <iostream>
#include "assert.h"
#include "exception.h"

using namespace std;

template <class T>
class Iterator;

template <class T>
class List {
	private:
		struct Node;

		Node* first;
		int size;

		friend class Iterator<T>;

	public:
		List() :
			first(NULL), size(0) { }

		List(const List& list) :
			size(list.size) {
			first = NULL;
			Iterator<T> iterator = begin();
			for (const T& data : list) {
				insert(data, iterator++);
			}
		}

		~List() {
			if (size == 0) {
				return;
			}

			Iterator<T> i = --end();
			for (; i != begin(); --i) {
				delete i.node;
			}

			delete i.node;
			first = NULL;
		}

		Iterator<T> begin() const {
			return Iterator<T>(*this, first);
		}

		Iterator<T> end() const {
			return Iterator<T>(*this, NULL);
		}

		Iterator<T> begin() {
			return Iterator<T>(*this, first);
		}

		void insert(const T& data, Iterator<T> iterator) {
			if (iterator.list != this) {
				throw ListExceptions::ElementNotFound();
			}

			++size;
			Node* newNode = new Node(data, iterator.node);
			if (iterator.node != first) {
				(--iterator).node->next = newNode;

				return;
			}

			first = newNode;
		}

		void remove(Iterator<T> iterator) {
			if (iterator.list != this || size == 0 || iterator.node == NULL) {
				throw ListExceptions::ElementNotFound();
			}

			--size;
			if (iterator.node == first) {
				Node* next = first->next;
				delete first;

				first = next;

				return;
			}

			--iterator;
			Node* next = iterator.node->next->next;
			delete iterator.node->next;

			iterator.node->next = next;
		}

		template <class Predicate>
		Iterator<T> find(const Predicate& predicate) {
			Iterator<T> iterator = begin();
			for (; iterator != end(); ++iterator) {
				if (predicate(*iterator)) {
					break;
				}
			}

			return iterator;
		}

		template <class Comapre>
		void sort(const Comapre& comparer) {
			bool swapped = true;
			while (swapped) {
				swapped = false;
				for (Iterator<T> i = ++(begin()); i != end(); ++i) {
					T& data1 = *(--i);
					T& data2 = *(++i);
					if (!comparer(data1, data2)) {
						T temp = data1;
						data1 = data2;
						data2 = temp;
						swapped = true;
					}
				}
			}
		}

		int getSize() {
			return size;
		}
};

template <class T>
struct List<T>::Node {
	private:
		T data;
		Node* next;

		friend class List<T>;
		friend class Iterator<T>;

		Node(const T& data, Node* next) :
			data(data), next(next) { }
};

template <class T>
class Iterator {
	private:
		const List<T>* list;
		typename List<T>::Node* node;

		friend class List<T>;

	public:
		Iterator(const List<T>& list, typename List<T>::Node* node) :
			list(&list), node(node) { }

		T& operator*() {
			if (node == NULL) {
				throw ListExceptions::ElementNotFound();
			}

			return node->data;
		}

		T operator*() const {
			if (node == NULL) {
				throw ListExceptions::ElementNotFound();
			}

			return node->data;
		}

		Iterator& operator++() {
			assert(node != NULL);

			node = node->next;
			return *this;
		}

		Iterator operator++(int) {
			Iterator iterator = *this;
			++*this;
			return iterator;
		}

		Iterator& operator--() {
			assert(node != list->first);

			typename List<T>::Node* prevNode;
			for (prevNode = list->first; prevNode->next != node;
					prevNode = prevNode->next);
			node = prevNode;
			return *this;
		}

		Iterator operator--(int) const {
			Iterator iterator = *this;
			++*this;
			return iterator;
		}

		const Iterator& operator--() const {
			assert(node != list->first);

			typename List<T>::Node* prevNode;
			for (prevNode = list->first; prevNode->next != node;
					prevNode = prevNode->next);
			node = prevNode;
			return *this;
		}

		bool operator==(const Iterator& iterator) {
			assert(list == iterator.list);
			return node == iterator.node;
		}

		bool operator!=(const Iterator& iterator) {
			return !(*this == iterator);
		}

		Iterator& operator=(const Iterator& iterator) {
			if (this == &iterator) {
				return *this;
			}

			list = iterator.list;
			node = iterator.node;
			return *this;
		}
};

#endif /* LIST_H_ */
