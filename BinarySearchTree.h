#pragma once
#include<functional>
#include<cmath>
#include<list>
#include<stack>
#include<algorithm>

template<typename T>
class BinarySearchTree
{
private:
	struct Node
	{
		Node(const T& value, Node* right, Node* left, Node* parent) : value(value), key(std::hash<T>{}(value)), right(right), left(left), parent(parent) {}
		T value;
		size_t key;
		Node* right;
		Node* left;
		Node* parent;
	};
	template<class Iter>
	class BinarySearchTreeIterator: public std::iterator<std::input_iterator_tag, Iter>
	{
		friend class BinarySearchTree;
	private:
		BinarySearchTreeIterator(Iter it) : it(it) {}
	public:
		BinarySearchTreeIterator(const BinarySearchTreeIterator& other) : it(other.it) {}
		size_t Key() const { return (*this->it)->key; }
		bool operator!=(const BinarySearchTreeIterator& other) { return this->it != other.it; }
		bool operator==(const BinarySearchTreeIterator& other) { return this->it == other.it; }
		T operator*() const { return (*this->it)->value; }
		BinarySearchTreeIterator& operator++();
		BinarySearchTreeIterator& operator++(int);
	private:
		Iter it;//Итератор в thread
	};
public:
	//N-Node, L-left, R-right
	enum Round
	{
		NLR,
		NRL,
		LRN,
		LNR,
		RLN,
		RNL
	};
	using iterator = BinarySearchTreeIterator<typename std::list<Node*>::const_iterator>;
	iterator begin() const;
	iterator end() const;
private:
	void RotateRight(Node* parent);
	void RotateLeft(Node* parent);
	void MakeRotations(int count);
	void CreateList();
	void CreateBalancedBST();
public:
	BinarySearchTree() : root(nullptr), round(NLR), round_names{ "NLR", "NRL", "LRN", "LNR", "RLN", "RNL" } {}
	BinarySearchTree(const BinarySearchTree<T>& other);
	BinarySearchTree(BinarySearchTree<T>&& other);
	void SetRound(Round new_round) { this->round = new_round; }
	void Add(const T& value);
	void Delete(const T& value);
	void Clear();
	iterator FindPos(const T& value) const;
	bool Find(const T& value);
	void Balancing();
	void UpdateRound();
	std::string ToString(std::string separator = " ");
	~BinarySearchTree();
private:
	Node* root;
	std::vector<std::string> round_names; 
	Round round;
	std::list<Node*> thread;//Прошивка
};

template<typename T>
template<class Iter>
BinarySearchTree<T>::BinarySearchTreeIterator<Iter>& BinarySearchTree<T>::BinarySearchTreeIterator<Iter>::operator++()
{
	++(this->it);
	return *this;
}

template<typename T>
template<class Iter>
BinarySearchTree<T>::BinarySearchTreeIterator<Iter>& BinarySearchTree<T>::BinarySearchTreeIterator<Iter>::operator++(int)
{
	BinarySearchTreeIterator<Iter> temp = *this;
	++(*this);
	return temp;
}

template<typename T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::begin() const
{
	return iterator(this->thread.begin());
}

template<typename T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::end() const
{
	return iterator(this->thread.end());
}

template<typename T>
void BinarySearchTree<T>::RotateRight(Node* parent)
{
	Node* left_child = parent->left;
	if (parent->parent != nullptr)
		parent->parent->right = left_child;
	else
		this->root = left_child;
	parent->left = left_child->right;
	left_child->right = parent;
	left_child->parent = parent->parent;
	parent->parent = left_child;
}

template<typename T>
void BinarySearchTree<T>::RotateLeft(Node* parent)
{
	Node* right_child = parent->right;
	if (parent->parent != nullptr)
		parent->parent->right = right_child;
	else 
		this->root = right_child;
	parent->right = right_child->left;
	right_child->left = parent;
	right_child->parent = parent->parent;
	parent->parent = right_child;
}

template<typename T>
void BinarySearchTree<T>::MakeRotations(int count)
{
	Node* parent = this->root;
	Node* child = this->root->right;
	for (; count > 0; count--) 
	{
		if (child != nullptr) 
		{
			this->RotateLeft(parent);
			parent = child->right;
			if (parent == nullptr)
				break;
			child = parent->right;
		}
		else
			break;
	}
}

template<typename T>
void BinarySearchTree<T>::CreateList()
{
	Node* parent = this->root;
	while (parent != nullptr) {
		if (parent->left != nullptr) {
			this->RotateRight(parent);
			parent = parent->parent;
		}
		else {
			parent = parent->right;
		}
	}
}

template<typename T>
void BinarySearchTree<T>::CreateBalancedBST()
{
	int n = 0;
	for (Node* tmp = this->root; tmp != nullptr; tmp = tmp->right)
		n++;
	//m = 2^floor[log2(n+1)]-1
	int m = (1 << int(log2(n + 1))) - 1;
	this->MakeRotations(n - m);
	while (m > 1)
		this->MakeRotations(m /= 2);
}

template<typename T>
void BinarySearchTree<T>::UpdateRound()
{
	using pair = std::pair<Node*, bool>;
	std::stack<pair> stack;
	stack.push(pair{ this->root, false });
	std::string round_name = this->round_names[this->round];
	std::reverse(round_name.begin(), round_name.end());
	this->thread.clear();
	while (!stack.empty())
	{
		pair current_node = stack.top();
		stack.pop();
		if (current_node.second)
			this->thread.push_back(current_node.first);
		else
		{
			if (current_node.first == nullptr)
				continue;
			for (auto ch : round_name)
				switch (ch)
				{
				case 'N':
					stack.push(pair{ current_node.first, true });
					break;
				case 'L':
					stack.push(pair{ current_node.first->left, false });
					break;
				case 'R':
					stack.push(pair{ current_node.first->right, false });
					break;
				}
		}
	}
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const BinarySearchTree<T>& other) : BinarySearchTree()
{
	for (auto el : other)
		this->Add(el);
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(BinarySearchTree<T>&& other)
{
	this->root = other.root;
	other.root = nullptr;
	this->round_names = other.round_names;
	this->round = other.round;
	this->thread = other.thread;
}

template<typename T>
void BinarySearchTree<T>::Add(const T& value)
{
	if (root == nullptr)
		root = new Node(value, nullptr, nullptr, nullptr);
	else
	{
		Node* current = this->root;
		Node* current_parent = this->root->parent;
		size_t key = std::hash<T>{}(value);
		while (current != nullptr)
		{
			current_parent = current;
			if (key > current->key)
				current = current->right;
			else
				current = current->left;
		}
		if(key > current_parent->key)
			current_parent->right = new Node(value, nullptr, nullptr, current_parent);
		else
			current_parent->left = new Node(value, nullptr, nullptr, current_parent);
	}
}

template<typename T>
void BinarySearchTree<T>::Delete(const T& value)
{
	Node* current = this->root;
	size_t key = std::hash<T>{}(value);
	while (current != nullptr)
	{
		if (current->key == key && current->value == value) //Второе условие на случай коллизии
		{
			Node* new_node;
			if (current->left != nullptr)
			{
				new_node = current->left;
				if (new_node->right != nullptr)
				{
					while (new_node->right != nullptr)
						new_node = new_node->right;
					new_node->parent->right = new_node->left;
					if (new_node->left != nullptr)
						new_node->left->parent = new_node->parent;
				}
				else
				{
					current->left = new_node->left;
				}
				current->value = new_node->value;
				current->key = new_node->key;
				delete new_node;
				return;
			}
			else if(current->right != nullptr)
			{
				new_node = current->right;
				current->value = new_node->value;
				current->key = new_node->key;
				current->left = new_node->left;
				current->right = new_node->right;
				delete new_node;
				return;
			}
			else
			{
				if (current->parent == nullptr)
					this->root = nullptr;
				else 
				{
					if (current->parent->right == current)
						current->parent->right = nullptr;
					if (current->parent->left == current)
						current->parent->left = nullptr;
				}
				delete current;
				return;
			}
		}
		else
		{
			if (key > current->key)
				current = current->right;
			else
				current = current->left;
		}
	}
}

template<typename T>
void BinarySearchTree<T>::Clear()
{
	while (!this->thread.empty())
	{
		delete this->thread.back();
		this->thread.pop_back();
	}
	this->root = nullptr;
}

template<typename T>
typename BinarySearchTree<T>::iterator BinarySearchTree<T>::FindPos(const T& value) const
{
	return iterator(std::find(this->thread.begin(),this->thread.end(), value));
}

template<typename T>
bool BinarySearchTree<T>::Find(const T& value)
{
	Node* current = root;
	size_t key = std::hash<T>{}(value);
	while (current != nullptr)
	{
		if (current->key == key && current->value == value) //Второе условие на случай коллизии
			return true;
		else
		{
			if (key > current->key)
				current = current->right;
			else
				current = current->left;
		}
	}
	return false;
}

//DSW algorithm
template<typename T>
void BinarySearchTree<T>::Balancing()
{
	if (this->root != nullptr) 
	{
		this->CreateList();
		this->CreateBalancedBST();
	}
}

template<typename T>
std::string BinarySearchTree<T>::ToString(std::string separator)
{
	std::ostringstream ss;
	for (auto it = this->begin(); it != this->end(); ++it)
		ss << *it << separator;
	return ss.str();
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
	this->UpdateRound();
	while (!this->thread.empty())
	{
		delete this->thread.back();
		this->thread.pop_back();
	}
}
