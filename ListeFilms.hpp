#pragma once
#pragma region "Includes"//{
#include "ListeFilms.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de mémoire.
#include "debogage_memoire.hpp"   // Ajout des numéros de ligne des "new" dans le rapport de fuites.
#include "Liste.hpp"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <limits>
#include <algorithm>
#include <memory>
#include "gsl/span"
#include <functional>
#include "cppitertools/range.hpp"


#pragma endregion//}


struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront défini après.


struct ListeActeurs {

	int capacite{}, nElements;
	std::unique_ptr <std::shared_ptr<Acteur>[]> elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
	ListeActeurs(int size)
	{
		capacite = nElements = size;
		elements = std::make_unique <std::shared_ptr<Acteur>[]>(capacite);
	}
	ListeActeurs()
	{
		nElements = 0;
		capacite = 1;
		elements = std::make_unique <std::shared_ptr<Acteur>[]>(capacite);
	}

	ListeActeurs& operator= (const ListeActeurs& listeActeurs)
	{
		capacite = listeActeurs.capacite;
		nElements = listeActeurs.nElements;
		elements = std::make_unique< std::shared_ptr<Acteur>[] >(listeActeurs.capacite);
		for (int i = 0; i < listeActeurs.nElements; i++)
		{
			elements[i] = listeActeurs.elements[i];
		}
		return *this;
	}
};




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
public:
	explicit ListeFilms();
	explicit ListeFilms(std::string nomFichier);
	~ListeFilms();
	void ajouterFilm(Film* ptrFilm);
	std::shared_ptr<Acteur> trouverActeur(std::string nom) const;
	void enleverFilm(Film* PtrFilm);
	void afficherListeFilms() const;
	friend std::ostream& operator<< (std::ostream& o, const Film* film);
	//void afficherFilm(const Film& film)const;
	std::ostream& afficherActeur(std::ostream& o, const std::shared_ptr<Acteur>& acteur);
	//void afficherActeur(const std::shared_ptr<Acteur>& acteur) const;
	void detruireFilm(Film* ptrFilm);
	void detruireListeFilms();
	Film* operator[] (const std::size_t index) const;

	
	Film* trouverFilmSi(const std::function<bool(Film*)>& critere) const;


private:
	int capacite_, nElements_;
	Film** elements_;
	void doublerCapacite();
	Film* lireFilm(std::istream& fichier);
	std::shared_ptr<Acteur> lireActeur(std::istream& fichier);
	std::shared_ptr<Acteur> trouverActeurListeActeurs(std::string nomRechercher, ListeActeurs& listeActeurs) const;


};


struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	//ListeFilms joueDans;
	Acteur(std::string name, int birthYear, char sex)
	{
		nom = name;
		anneeNaissance = birthYear;
		sexe = sex;
		//	joueDans = ListeFilms{};
	}

};

std::ostream& operator<< (std::ostream& o, const Film* film);

//void afficherFilmographieActeur(const ListeFilms& listeFilms, const std::string& nomActeur);








