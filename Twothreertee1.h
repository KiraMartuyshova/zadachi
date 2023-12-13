#include <iostream>
#include <fstream>
#include <string>
#include <cctype>

//Реализация 2-3 дерева и частотного словаря, обработка исключения открытия несуществующего и пустого файлов
using namespace std;

template <class Key, class Value>
class TwoThreeTree {
private:
    struct Node { //Структура, хранящая узел, ключ, значение, три поддерева
        Key key;
        Value value;
        Node* left;
        Node* middle;
        Node* right;

        Node(Key k, Value v, Node* p = nullptr) : key(k), value(v), left(nullptr), middle(nullptr), right(nullptr) {}
    
		bool isThreeNode() const {
			return (middle != nullptr); //проверяем, есть ли среднее поддерево, чтобы определить, является ли узел трехузловым
        }
    };

    Node* root; //Корень дерева

	//Метод поиска узла с заданным ключом
    Node* findNode(Node* node, Key key) const;

	//Вспомогательная функция для удаления узла по ключу
    Node* removeNode(Node* node, const Key& key);

	//Метод для поиска максимального узла в поддереве (перемещается по правым узлам и находит тот,у которого правого поддерева нет)
    Node* findMax(Node* node) const;

	//Метод для удаления максимального узла из поддерева
    Node* removeMax(Node* node);
	
	//Метод указателя на последний элемент в дереве
	Node* end() {
        return nullptr; 
	}
  
public:
	TwoThreeTree() : root(nullptr) {}
  
	//Поиск узла по ключу и присваивание значения ключа переменной 
	bool find(Key key, Value& value) const;

	//Метод удаления узла по ключу
	void remove(const Key& key);

	//Метод для добавления слова в дерево и определение его частоты встречаемости 
    void insert(Key key);

	//Рекурсивно выводит слово и его частоту, начиная с левого поддерева
	void print_recursiv(Node* node);

	//Вывод встречаемости всех слов дерева
    void print_tree();

	//Чтение слов из файла, извлечение и вставка в дерево
	void readFile(const string& filename);
  
	//Деструктор класса TwoThreetree
	~TwoThreeTree();

	//Вспомогательная функция для освобождения памяти
	void clear(Node* node);
	
	
};

template <class Key, class Value>
typename TwoThreeTree<Key, Value>::Node* TwoThreeTree<Key, Value>::findNode(Node* node, Key key) const { 
	if (node == nullptr) { //если текущий узел пуст, то ключ не найден в данной ветви дерева 
			return nullptr;
	}
	if (key == node->key) { //если ключ совпадает с ключом текущего узла, то нужный ключ найден
		return node;
	} else if (key < node->key) { //если ключ меньше ключа текущего узла, поиск продолжается в левом поддереве вызовом рекурсии для левого поддерева
		return findNode(node->left, key);
	} else if (key > node->key) { 
		return findNode(node->middle, key);
	} else { //если ключ больше ключа правого поддерева, поиск продолжается в правом поддереве вызовом рекурсии для правого поддерева
		return findNode(node->right, key);
	}
	return node;
}

template <class Key, class Value>
typename TwoThreeTree<Key, Value>::Node* TwoThreeTree<Key, Value>::removeNode(Node* node, const Key& key) {
	if (node == nullptr) { 
		return nullptr;
    }
	
	//проверяем, является ли узел единственным корневым и не имеет ли дочерних узлов
    if (node == root && node->left == nullptr && node->middle == nullptr && node->right == nullptr) {
        delete node;
        root = nullptr; //устанавливаем корень в nullptr, так как дерево становится пустым
        return nullptr;
    }
	
    if (key < node->key) { //сравниваем ключ с текущим узлом и переходим в левое поддерево
		node->left = removeNode(node->left, key);
    } else if (key > node->key) { //сравниваем ключ с текущим узлом и переходим в поддерево
        if (node->isThreeNode() && key > node->right->key) { //если текущий узел трехузловый, то выбираем из правого и среднего
			node->right = removeNode(node->right, key);
         } else {
            node->middle = removeNode(node->middle, key);
		 }	
	} else { //иначе переходим в среднее поддерево (так как у текущего узла два ключа и искомый узел может быть либо в правом, либо в среднем
		if (node->isThreeNode()) { //если узел трехузловый
			if (node->right->key == key) { //если ключ для удаления равен ключу в правом поддереве
				node->right = nullptr;
			} else { //иначе перестраиваем левое в правое и удаляем
				node->left = node->middle;
				node->middle = node->right;
				node->right = nullptr;
			}
		} else { 
			if (node->left == nullptr && node->middle == nullptr) { //у узла нет дочерних узлов
				delete node;
				return nullptr;
			}

			if (node->middle == nullptr) { //случай, когда у узла один или два ключа
				node->key = node->left->key; //переносим значение и ключ в левое поддерево и обнуляем его
				node->value = node->left->value;
				node->left = nullptr;
			} else { 
				Node* pred = findMax(node->left); //находим максимальный узел в левом поддереве, копируем его значение и ключ в текущий узел, а его обнуляем
				node->key = pred->key;
				node->value = pred->value;
				node->left = removeMax(node->left);
			}
		}
	}
	return node;
}

template <class Key, class Value>
typename TwoThreeTree<Key, Value>::Node* TwoThreeTree<Key, Value>::findMax(Node* node) const {
	while (node->right != nullptr) {
		node = node->right;
    }
	return node;
}

template <class Key, class Value>
typename TwoThreeTree<Key, Value>::Node* TwoThreeTree<Key, Value>::removeMax(Node* node) {
	if (node->right == nullptr) {
		Node* temp = node->left;
        delete node;
        return temp;
    }
	node->right = removeMax(node->right);
    return node;
}

template <class Key, class Value>
bool TwoThreeTree<Key, Value>::find(Key key, Value& value) const {
	Node* foundNode = findNode(root, key); //вызываем функция для поиска узла с ключом, начиная с корня
		if(foundNode != nullptr) { //если узел был найден, то присваиваем значение переменной 
			value = foundNode->value;
            return true;
        }
    return false;
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::remove(const Key& key) {
	root = removeNode(root, key);
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::insert(Key key) {
	if (root == nullptr) { //если дерево пустое, то создаем новый корневой узел со значением частоты 1
		root = new Node(key, 1);
		return;
	}

	Node* current = root;
	Node* parent = nullptr;

	while (true) { //если слово уже существует, то увеличиваем значение
		if (key == current->key) {
			current->value++;
			break;
		}

		parent = current;
		
		//если слово отсутствует, то добавляем в соответствующее поддерево 
		if (key < current->key) {
			if (current->left == nullptr) {
				current->left = new Node(key, 1);
				break;
			} else {
                current = current->left;
			}
		} else {
            if (current->middle == nullptr) {
                current->middle = new Node(key, 1);
                break;
            } else {
                current = current->middle;
			}
		}		
	}
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::print_recursiv(Node* node) {
	if (node != nullptr) {
		print_recursiv(node->left);
		//печать текущего узла
		cout << "Слово: " << node->key << "; Частота: " << node->value << endl;
		print_recursiv(node->middle);
		print_recursiv(node->right);
	}
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::print_tree() {
	print_recursiv(root);
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::readFile(const string& filename) {
    try {
		//Проверка на открытие файла
		ifstream file(filename);
		if (!file.is_open()) {
            throw runtime_error("Не удалось открыть файл");
		}

		//Проверка на пустоту файла
		file.seekg(0, ios::end); //устанавливаем указатель в конец файла
		
		if (file.tellg() == 0) { //определяем текущую позицию указателя и если она равна нулю, то размер ноль
			throw runtime_error("Файл пуст");
		}

		file.seekg(0, ios::beg); //возвращаем указатель на начало файла после проверки

        string word;
        while (file >> word) {
            //удаление знаков препинания из слова перед вставкой в дерево
            for (char& c : word) {
                c = tolower(c); //приведение к нижнему регистру
                if (ispunct(c)) {
                    c = ' '; //замена знаков препинания пробелами
                }
            }

            //вставка слова в дерево
            if (!word.empty()) {
                insert(word);
            }
        }

        file.close();
    } catch (const runtime_error& e) {
        cerr << "Ошибка: " << e.what() << endl;
    }
}

	
template <class Key, class Value>
TwoThreeTree<Key, Value>::~TwoThreeTree() {
	//вызываем вспомогательную функцию для освобождения памяти
	clear(root);
}

template <class Key, class Value>
void TwoThreeTree<Key, Value>::clear(Node* node) {
	if (node) {
		//рекурсивно освобождаем память для левого поддерева
		clear(node->left);
        
		//рекурсивно освобождаем память для среднего поддерева (если есть)
		if (node->isThreeNode()) {
			clear(node->middle);
		}
        
		//рекурсивно освобождаем память для правого поддерева
		clear(node->right);
        
		//удаляем узел
		delete node;
	}
}
