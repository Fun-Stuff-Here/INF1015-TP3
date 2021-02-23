/*
* Définition de la Classe Liste, TD3-INF1015
*\file		Liste.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		7 mars 2021
* Créé le	23 février 2021
*/
#pragma once
#ifndef LISTE_H
#define LISTE_H

#include <memory>
#include "gsl/span"
#include "cppitertools/range.hpp"
#include "cppitertools/enumerate.hpp"

//https://www.youtube.com/watch?v=F9eDv-YIOQ0&ab_channel=TheCherno
template<typename T>
class ListeIterator
{
public:
	using ValueType = T;
	using PointerType = ValueType*;
	using ReferenceType = ValueType&;
public:
	ListeIterator(PointerType ptr)
		:mPtr(ptr) {}

	ListeIterator& operator++() { mPtr++; return *this; }
	ListeIterator& operator++(int) { ListeIterator iterator = *this; ++(*this); return iterator; }
	ListeIterator& operator--() { mPtr--; return *this; }
	ListeIterator& operator--(int) { ListeIterator iterator = *this; --(*this); return iterator; }

	ReferenceType operator[] (int index) { return *(mPtr + index); }
	PointerType operator->() { return mPtr; }
	ReferenceType operator*() { return *mPtr; }

	bool operator==(const ListeIterator& other) const { return mPtr == other.mPtr; }
	bool operator!=(const ListeIterator& other) const { return !(*this == other); }
private:
	PointerType mPtr;
};

template<typename T>
class Liste
{
//https://www.youtube.com/watch?v=F9eDv-YIOQ0&ab_channel=TheCherno
public:
	using ValueType = std::shared_ptr<T>;
	using Iterator = ListeIterator<ValueType>;

public:
	Liste(int size);
	Liste();
	Liste(const Liste<T>& liste);
	gsl::span<std::shared_ptr<T>> toSpan() { return gsl::span<std::shared_ptr<T>>(elements_, nElements_); }
	~Liste();
	Liste<T>& operator= (const Liste<T>& liste);
	const std::shared_ptr<T>& operator[] (const std::size_t index) const { return elements_[index]; }
	std::shared_ptr<T>& operator[] (const std::size_t index) { return elements_[index]; }
	int get_capacite() const { return capacite_; }
	int get_nElements() const {return nElements_;}

	//https://www.youtube.com/watch?v=F9eDv-YIOQ0&ab_channel=TheCherno
	ListeIterator<ValueType> begin() { return ListeIterator(elements_.get()); }
	ListeIterator<ValueType> begin() const { return ListeIterator{ elements_.get() }; }
	ListeIterator<ValueType> end() { return ListeIterator(elements_.get() + nElements_); }
	ListeIterator<ValueType> end() const { return ListeIterator{ elements_.get() + nElements_ }; }
	
private:
	int capacite_, nElements_;
	std::unique_ptr <std::shared_ptr<T>[]> elements_;
};


template<typename T>
Liste<typename T>::Liste(int size)
{
	capacite_ = nElements_ = size;
	elements_ = std::make_unique <std::shared_ptr<T>[]>(capacite_);

	for (int i : iter::range(nElements_))
	{
		elements_[i] = std::make_shared<T>();
	}

}

template<typename T>
Liste<typename T>::Liste()
{
	nElements_ = 0;
	capacite_ = 1;
	elements_ = std::make_unique <std::shared_ptr<T>[]>(capacite_);
	elements_[0] = std::make_shared<T>();
}


template<typename T>
Liste<typename T>::Liste(const Liste<T>& liste)
{
	capacite_ = liste.get_capacite();
	nElements_ = liste.get_nElements();
	elements_ = std::make_unique< std::shared_ptr<T>[] >(liste.get_capacite());
	
	for (auto&& [i, element] : iter::enumerate(*this))
	{
		element = liste[i];
	}

}


template<typename T>
Liste<T>& Liste<typename T >::operator= (const Liste<T>& liste)
{
	capacite_ = liste.get_capacite();
	nElements_ = liste.get_nElements();
	elements_ = std::make_unique< std::shared_ptr<T>[] >(liste.get_capacite());

	for (auto&& [i, element] : iter::enumerate(*this))
	{
		element = liste[i];
	}
	return *this;
}

template<typename T>
Liste<typename T>::~Liste()
{
	elements_ = nullptr;
}

#endif // !LISTE_H