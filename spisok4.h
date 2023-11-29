#include <iostream>
#include "a.h" 

//Однонаправленный список, внешний итератор
//Сортировка списка методом insertion (по возрастанию и убыванию), проверка на корректную работу сортировки
//Сравнение библиотечной сортировки и моей, время работы двух программ
using namespace std;
template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T data) : data(data), next(nullptr) {}
};

template <typename T>
class List {
private:
    Node<T>* head;
    int size;

public:
    List() : head(nullptr), size(0) {}
	
	//Метод для добавления элемента в начало списка
	void prepend(T data);
	
	//Метод для добавления элемента в конец списка
    void append(T data);

    //Метод для вывода элементов
    void print();

    //Метод для удаления элемента по значению
    void remove(T data);

    //Метод для удаления элемента по индексу
    void remove_num(int n);

    //Деструктор для освобождения памяти при уничтожении списка
    ~List();

    //Внутренний итератор для начала итерации
    Node<T>* begin() const {
        return head;
    }

    //Внутренний итератор для окончания итерации
    Node<T>* end() {
        return nullptr;
    }

    //Внутренний итератор для перехода к следующему элементу
    Node<T>* next(Node<T>* current) const {
        if (current) {
            return current->next;
        }
        return nullptr;
    }

    //Функция для итерации и выполнения операции над каждым элементом списка
    void foreach(void (*operation)(T&));
	
	//Метод для вставки элемента после указанного итератора
    void insert(Node<T>* iter, T data);

    //Метод для удаления элемента после указанного итератора
    void erase(Node<T>* iter);
	
	//Сортировка
	template <typename Compare>
    void insertionSort(Compare comp);

	//Проверка сортировки
    template <typename Compare>
    bool proverka(Compare comp) const;

};

template <typename T>
void List<T>::prepend(T data) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = head;
        head = newNode;
}
	
template <typename T>
void List<T>::append(T data) {
    Node<T>* newNode = new Node<T>(data);
    if (!head) {
        head = newNode;
    } else {
        Node<T>* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
    size++;
}

template <typename T>
void List<T>::print() {
    Node<T>* current = head;
    while (current) {
        cout << current->data << " ";
        current = current->next;
    }
    cout << endl;
}

template <typename T>
void List<T>::remove(T data) {
    if (!head) {
        return;
    }

    if (head->data == data) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    Node<T>* current = head;
    while (current->next) {
        if (current->next->data == data) {
            Node<T>* temp = current->next;
            current->next = current->next->next;
            delete temp;
            size--;
            return;
        }
        current = current->next;
    }
}

template <typename T>
void List<T>::remove_num(int n) {
    if (n < 0 || n >= size) {
        return;
    }

    if (n == 0) {
        Node<T>* temp = head;
        head = head->next;
        delete temp;
        size--;
        return;
    }

    Node<T>* current = head;
    for (int i = 0; i < n - 1; i++) {
        current = current->next;
    }

    Node<T>* temp = current->next;
    current->next = current->next->next;
    delete temp;
    size--;
}

template <typename T>
List<T>::~List() {
    Node<T>* current = head;
    while (current) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }
}

template <typename T>
void List<T>::foreach(void (*operation)(T&)) {
        Node<T>* current = head;
        while (current) {
            operation(current->data);
            current = current->next;
        }
    }

template <typename T>
void List<T>::insert(Node<T>* iter, T data) {
    if (iter) {
        Node<T>* newNode = new Node<T>(data);
        newNode->next = iter->next;
        iter->next = newNode;
        size++;
    }
}

template <typename T>
void List<T>::erase(Node<T>* iter) {
    if (iter) {
        if (iter == head) {
            //если удаляем первый элемент, обновляем указатель на голову списка
            head = iter->next;
            delete iter;
            size--;
        } else {
            //иначе, ищем предыдущий элемент и обновляем его указатель
            Node<T>* current = head;
            while (current && current->next != iter) {
                current = current->next;
            }
            if (current) {
                current->next = iter->next;
                delete iter;
                size--;
            }
        }
    }
}

template <typename T>
List<T>* merge_lists(const List<T>& list1, const List<T>& list2, Node<T>* startNode) {
    List<T>* mergedList = new List<T>();

    Node<T>* iter1 = list1.begin();
    while (iter1) {
        mergedList->append(iter1->data);
        iter1 = list1.next(iter1);
    }

    Node<T>* iter2 = startNode;
    while (iter2) {
        mergedList->append(iter2->data);
        iter2 = list2.next(iter2);
    }

    return mergedList;
}

template <typename T>
template <typename Compare>
void List<T>::insertionSort(Compare comp) {
    if (head == nullptr || head->next == nullptr) {
        return; // если список пуст или содержит только один элемент, он уже отсортирован
    }
    Node<T>* sort = nullptr; // инициализация списка, содержащего отсортированные элементы
    Node<T>* current = head; 
    while (current != nullptr) {
        Node<T>* next = current->next; 
        // вставляем текущий элемент в отсортированный список с использованием функции сравнения
        if (sort == nullptr || comp(current->data, sort->data)) {
            current->next = sort;
            sort = current; 
        } else {
            Node<T>* sortCurr = sort; 
            while (sortCurr->next != nullptr && !comp(current->data, sortCurr->next->data)) {
                sortCurr = sortCurr->next;
            }
            current->next = sortCurr->next;
            sortCurr->next = current;
        }
        current = next;
    }
    head = sort; 
}

template <typename T>
template <typename Compare>
bool List<T>::proverka(Compare comp) const {
    if (head == nullptr || head->next == nullptr) {
        return true;
    }

    Node<T>* current = head;
    while (current->next != nullptr) {
        if (!comp(current->data, current->next->data)) {
            return false;
        }
        current = current->next;
    }

    return true;
}
