#pragma once
#include"BinarySearchTree.h"

template<typename T>
class Set
{
private:
	template<class Iter>
	class SetIterator : public std::iterator<std::input_iterator_tag, Iter>
	{
		friend class Set;
	private:
		SetIterator(Iter it) : it(it) {}
	public:
		SetIterator(const SetIterator& other) : it(other.it) {}
		size_t Key() const { return this->it->Key(); }
		bool operator!=(const SetIterator& other) { return this->it != other.it; }
		bool operator==(const SetIterator& other) { return this->it == other.it; }
		T operator*() const { return *this->it; }
		SetIterator& operator++() { ++this->it; return *this; }
		SetIterator& operator++(int) { SetIterator temp = *this; ++this; return temp; }
	private:
		Iter it;//Итератор в binary_search_tree
	};
public:
	using iterator = SetIterator<typename BinarySearchTree<T>::iterator>;
	iterator begin() const { return this->binary_search_tree.begin(); }
	iterator end() const { return this->binary_search_tree.end(); };
	void Add(const T& value);
	bool Has(const T& value);
	void Delete(const T& value);
	void Clear();
	void UpdateRound();
private:
	BinarySearchTree<T> binary_search_tree;
};

template<typename T>
void Set<T>::Add(const T& value)
{
	if (!this->binary_search_tree.Find(value))
		this->binary_search_tree.Add(value);
}

template<typename T>
bool Set<T>::Has(const T& value)
{
	return this->binary_search_tree.Find(value);
}

template<typename T>
void Set<T>::Delete(const T& value)
{
	this->binary_search_tree.Delete(value);
}

template<typename T>
void Set<T>::Clear()
{
	this->binary_search_tree.Clear();
}

template<typename T>
void Set<T>::UpdateRound()
{
	this->binary_search_tree.UpdateRound();
}

template<typename T>
Set<T> Union(Set<T> first, Set<T> second)
{
	Set<T> union_set;
	first.UpdateRound();
	for (auto el : first)
		union_set.Add(el);
	second.UpdateRound();
	for (auto el : second)
		if(!first.Has(el))
			union_set.Add(el);
	return union_set;
}

template<typename T>
Set<T> Intersection(Set<T> first, Set<T> second)
{
	Set<T> intersection_set;
	first.UpdateRound();
	for (auto el : first)
		if (second.Has(el))
			intersection_set.Add(el);
	return intersection_set;
}

template<typename T>
Set<T> RelativeComplement(Set<T> first, Set<T> second)
{
	Set<T> relative_complement;
	first.UpdateRound();
	for (auto el : first)
		if (!second.Has(el))
			relative_complement.Add(el);
	return relative_complement;
}