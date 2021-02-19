#pragma once
#include <memory>
#include "gsl/span"
#include "cppitertools/range.hpp"


template<typename T>
class Liste
{
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

	
private:
	int capacite_, nElements_;
	std::unique_ptr <std::shared_ptr<T>[]> elements_;
};


template<typename T>
Liste<typename T>::Liste(int size)
{
	capacite_ = nElements_ = size;
	elements_ = std::make_unique <std::shared_ptr<T>[]>(capacite_);

	for (int i = 0;  i < nElements_; i++)
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
	for (int i = 0; i < liste.get_nElements(); i++)
	{
		elements_[i] = liste[i];
	}
}


template<typename T>
Liste<T>& Liste<typename T >::operator= (const Liste<T>& liste)
{
	capacite_ = liste.get_capacite();
	nElements_ = liste.get_nElements();
	elements_ = std::make_unique< std::shared_ptr<T>[] >(liste.get_capacite());
	for (int i = 0; i < liste.get_nElements(); i++)
	{
		elements_[i] = liste[i];
	}
	return *this;
}

template<typename T>
Liste<typename T>::~Liste()
{
	elements_ = nullptr;
}





