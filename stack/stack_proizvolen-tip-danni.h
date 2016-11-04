#pragma once
#ifndef STACK_H_
#define STACK_H_

int const MAX = 100;
template <typename T>
class Stack {
private:
	T a[MAX];	// елементите на стека
	int topIndex;	// индекс на последния елемент

					// проверка дали стек е пълен
	bool full() const;

public:

	// създаване на празен стек
	Stack();

	// селектори

	// проверка дали стек е празен
	bool empty() const;

	// намиране на елемента на върха на стека
	T top() const;

	// мутатори

	// включване на елемент
	void push(T const&);

	// изключване на елемент
	T pop();
};

#endif /* STACK_H_ */
