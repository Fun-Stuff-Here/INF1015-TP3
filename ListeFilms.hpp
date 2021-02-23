/*
* Définition de la Classe ListeFilms et structures utiles, TD3-INF1015
*\file		ListeFilms.hpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		7 mars 2021
* Créé le	23 février 2021
*/
#pragma once
#ifndef LISTEFILMS_H
#define LISTEFILMS_H

#pragma region "Includes"//{
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"   // Ajout des numéros de ligne des "new" dans le rapport de fuites.
#include "gsl/span"
#include "cppitertools/range.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <memory>
#include <functional>
#include <iterator>

#include "Liste.hpp"
#pragma endregion//}

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.
using ListeActeurs = Liste<Acteur>;

struct Film
{
	std::string titre, realisateur; // Titre et nom du réalisateur (on suppose qu'il n'y a qu'un réalisateur).
	int anneeSortie, recette; // Année de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
	Film()
	{
		titre = realisateur = "";
		anneeSortie = recette = 0;
	}

	Film(Film* ptrFilm)
	{
		titre = ptrFilm->titre;
		realisateur = ptrFilm->realisateur;
		anneeSortie = ptrFilm->anneeSortie;
		recette = ptrFilm->recette;
		acteurs = ptrFilm->acteurs;
	}

};


class ListeFilms
{
	//https://www.youtube.com/watch?v=F9eDv-YIOQ0&ab_channel=TheCherno
public:
	using ValueType = Film*;
	using Iterator = ListeIterator<ValueType>;

public:
	explicit ListeFilms();
	explicit ListeFilms(const std::string& nomFichier);
	~ListeFilms() { detruire(); }

	void ajouterFilm(Film* film);
	void enleverFilm(Film* film);

	void afficher() const;
	std::ostream& afficherActeur(std::ostream& ostream, const std::shared_ptr<Acteur>& acteur);
	friend std::ostream& operator<< (std::ostream& ostream, const Film* film);
	
	void detruireFilm(Film* film);
	void detruire();

	Film* operator[] (const std::size_t index) const;
	Film* trouverFilmSi(const std::function<bool(Film*)>& critere) const;
	std::shared_ptr<Acteur> trouverActeur(const std::string& nom) const;

	//https://www.youtube.com/watch?v=F9eDv-YIOQ0&ab_channel=TheCherno
	ListeIterator<ValueType> begin() { return ListeIterator(elements_); }
	ListeIterator<ValueType> begin() const { return ListeIterator{ elements_ }; }
	ListeIterator<ValueType> end() { return ListeIterator(elements_ + nElements_); }
	ListeIterator<ValueType> end() const { return ListeIterator{ elements_ + nElements_ }; }

private:
	int capacite_, nElements_;
	Film** elements_;

	void doublerCapacite();
	Film* lireFilm(std::istream& fichier);
	std::shared_ptr<Acteur> lireActeur(std::istream& fichier);
	std::shared_ptr<Acteur> trouverActeurListeActeurs(const std::string& nomRechercher,const ListeActeurs& listeActeurs) const;
};


struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	Acteur(const std::string name, const int birthYear,const char sex)
	{
		nom = name;
		anneeNaissance = birthYear;
		sexe = sex;
	}
	Acteur()
	{
		nom = "";
		anneeNaissance = 0;
		sexe = ' ';
	}
};

std::ostream& operator<< (std::ostream& ostream, const Film* film);



#endif // !LISTEFILMS_H










