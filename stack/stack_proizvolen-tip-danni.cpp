#include <iostream>
using namespace std;

#include "stack.h"

int const EMPTY_STACK = -1; // отбелязваме празен стек
template <typename T>
Stack::Stack() {
	topIndex = EMPTY_STACK;
}
template <typename T>
bool Stack::empty() const {
	return topIndex == EMPTY_STACK;
}
template <typename T>
T Stack::top() const {
	if (empty()) {
		cout << "Грешка: опит за поглеждане в празен стек!\n";
		return 0;
	}

	return a[topIndex];
}
template <typename T>
void Stack::push(T const& x) {
	if (full()) {
		cout << "Грешка: опит за включване в пълен стек!\n";
	}
	else
		a[++topIndex] = x;
}
template <typename T>
bool Stack::full() const {
	return topIndex == MAX - 1;
}
template <typename T>
T Stack::pop() {
	if (empty()) {
		cout << "Грешка: опит за изключване от празен стек!\n";
		return 0;
	}
	return a[topIndex--];
}
