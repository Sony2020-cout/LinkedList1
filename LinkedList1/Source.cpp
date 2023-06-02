#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::string;

template < typename T>
class List
{
public:
	List();
	~List();
	void clear();
	void popFront();
	void pushBack(T data);//добавление в конец списка
	int GetSize() { return Size; }//количество элементов в списке

	void pushFront(T data);
	void popBack();
	void insert(T data, int index);
	void removeAt(int index);


	T& operator[](const int index);

private:
	template < typename T>
	class Node //элемент хранит данные(указатель на следующий элемент)
	{
	public:
		Node* pNext;
		T data;
		Node(T data=T(), Node* pNext = nullptr)
		{
			this->data = data;
			this->pNext = pNext;
		}
	};
	int Size;
	Node<T> *head;

};

template <typename T>
List<T>::List()
{
	Size = 0;
	head = nullptr;
}


template <typename T>
List<T>::~List()
{
	clear();
}

template<typename T>
void List<T>::clear()
{
	while (Size) 
	{
		popFront();
	}
}

template<typename T>
void List<T>::popFront()
{
	Node<T> *temp = head;

	head = head->pNext;
	delete temp;

	Size--;
}

template <typename T>
void List<T>::pushBack(T data)
{
	if (head == nullptr)
	{
		head = new Node<T>(data);
	}
	else
	{
		Node<T>* current = this->head;

		while (current->pNext != nullptr)
		{
			current = current->pNext;
		}
		current->pNext = new Node<T>(data);
	}

	Size++;
}
template<typename T>
void List<T>::pushFront(T data)
{
	head = new Node<T>(data, head);
	Size++;
}
template<typename T>
void List<T>::popBack()
{
	removeAt(Size - 1);
}
template<typename T>
void List<T>::insert(T data, int index)
{
	if (index == 0)
	{
		pushFront(data);
	}
	else
	{
		Node<T>* previous = this->head;

		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* newNode = new Node<T>(data, previous->pNext);
		previous->pNext = newNode;

		Size++;
	}
	
	Node<T>* previous = this->head;

	for (int i = 0; i < index; i++)
	{
		previous = previous->pNext;
	}

}
template<typename T>
void List<T>::removeAt(int index)
{
	if (index == 0)
	{
		popFront();
	}
	else
	{
		Node<T>* previous = this->head;
		for (int i = 0; i < index - 1; i++)
		{
			previous = previous->pNext;
		}

		Node<T>* toDelete = previous->pNext;

		previous->pNext = toDelete->pNext;

		delete toDelete;
		Size--;
	}
}
template <typename T>
T& List<T>::operator[](const int index)
{
	int counter = 0;
	Node<T>* current = this->head;
	while (current != nullptr)
	{
		if (counter == index)
		{
			return current->data;
		}
		current = current->pNext;
		counter++;
	}
}

int main()
{
	setlocale(LC_ALL, "ru");

	List<int> lst;
	int numbersCount;
	std::cin >> numbersCount;


	for (int i = 0; i < numbersCount; i++)
	{
		lst.pushBack(rand()%10);
	}

	for (int i = 0; i < lst.GetSize(); i++)
	{
		cout << lst[i] << endl;
	}

	return 0;

}