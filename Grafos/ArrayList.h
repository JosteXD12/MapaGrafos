#pragma once
#include <fstream>
#include <iostream>
#include <functional>
using namespace sf;
using namespace std;
// Clase arraylist
template <typename T>
struct Node
{
	Node* next;
	Node* prev;
	int index;
	T value;
};

template <typename T>

class ArrayList
{
private:
	Node<T>* init;
	Node<T>* iterator;
	int size;
	Node<T>* end;

	void fixIndexes()
	{
		size = 0;
		if (init != nullptr)
		{
			iterator = init;
			while (true)
			{
				iterator->index = size;
				size++;

				iterator = iterator->next;
				if (iterator == nullptr)
				{
					iterator = init;
					break;
				}
			}
		}
	}
public:
	ArrayList() { init = nullptr, iterator = nullptr, end = nullptr, size = 0; }
	~ArrayList() {}

	void set(T object)
	{
		if (init == nullptr)
		{
			init = new Node<T>{ nullptr, nullptr, size, object };
			iterator = init;
			end = init;
			size++;
		}
		else
		{
			end->next = new Node<T>{ nullptr, end, size, object };
			end = end->next;
			size++;
		}
	}
	int getSize()
	{
		return size;
	}
	T get(int index)
	{
		if (init != nullptr || index < size || index >= 0)
		{
			while (true)
			{
				if (index >= iterator->index)
				{
					if (index == iterator->index)
					{
						return iterator->value;
					}
					else
					{
						iterator = iterator->next;
					}
				}
				else if (index < iterator->index)
				{
					iterator = iterator->prev;
				}
			}
		}
		return nullptr;
	}
	bool remove(T object)
	{
		for (int i = 0; i < size; i++)
		{
			if (get(i) == object)
			{
				return remove(i);
			}
		}
		return false;
	}
	bool drop(T object)
	{
		for (int i = 0; i < size; i++)
		{
			if (get(i) == object)
			{
				return drop(i);
			}
		}
		return false;
	}
	void deleteAll()
	{
		for (int i = 0; i < size; i++)
		{
			remove(i);
			i--;
		}
		init = nullptr, iterator = nullptr, end = nullptr, size = 0;
	}
	void clear() {
		init = nullptr, iterator = nullptr, end = nullptr, size = 0;
	}
	bool isEmpty()
	{
		return (size == 0);
	}
	bool drop(int index)
	{
		Node<T>* aux = nullptr;
		if (init != nullptr || index < size || index >= 0)
		{
			while (true)
			{
				if (index >= iterator->index)
				{
					if (index == iterator->index)
					{
						aux = iterator;
						break;
					}
					else
					{
						iterator = iterator->next;
					}
				}
				else if (index < iterator->index)
				{
					iterator = iterator->prev;
				}
			}
			if (size == 1)
			{
				init = nullptr;
				iterator = nullptr;
				end = nullptr;
			}
			else if (init == iterator)
			{
				iterator->next->prev = nullptr;
				init = iterator->next;
				end = iterator->next;
				iterator = iterator->next;
			}
			else if (end == aux)
			{
				end = end->prev;
				iterator = end;
				end->next = nullptr;
			}
			else
			{
				iterator->next->prev = iterator->prev;
				iterator->prev->next = iterator->next;
				iterator = iterator->prev;
			}
			fixIndexes();
		}
	}
	bool remove(int index)
	{
		Node<T>* aux = nullptr;
		if (init != nullptr || index < size || index >= 0)
		{
			while (true)
			{
				if (index >= iterator->index)
				{
					if (index == iterator->index)
					{
						aux = iterator;
						break;
					}
					else
					{
						iterator = iterator->next;
					}
				}
				else if (index < iterator->index)
				{
					iterator = iterator->prev;
				}
			}
			if (size == 1)
			{
				init = nullptr;
				iterator = nullptr;
				end = nullptr;
				delete aux->value;
				delete aux;
			}
			else if (init == iterator)
			{
				iterator->next->prev = nullptr;
				init = iterator->next;
				end = iterator->next;
				iterator = iterator->next;
				delete aux->value;
				delete aux;
			}
			else if (end == aux)
			{
				end = end->prev;
				iterator = end;
				end->next = nullptr;
				delete aux->value;
				delete aux;
			}
			else
			{
				iterator->next->prev = iterator->prev;
				iterator->prev->next = iterator->next;
				iterator = iterator->prev;
				delete aux->value;
				delete aux;
			}
			fixIndexes();
		}
		else
		{
			std::cout << "INDEX OUT OF BOUNDS| DELETE INDEX: " << index << "| SIZE: " << size << std::endl;
			abort();
		}
		return true;
	}
	void foreach(function<void (T element)> instruction)
	{
		for (int i = 0; i < size; i++)
		{
			instruction(get(i));
		}
	}
};


