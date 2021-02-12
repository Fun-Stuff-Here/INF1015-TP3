#pragma once
#pragma region "Includes"//{
#include "ListeFilms.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de m�moire.
#include "debogage_memoire.hpp"        // Ajout des num�ros de ligne des "new" dans le rapport de fuites.

#include <iostream>
#include <fstream>
#include <string>
#include <limits>
#include <algorithm>
#include "gsl/span"
#include "cppitertools/range.hpp"

#pragma endregion//}


struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront d�fini apr�s.


struct ListeActeurs {
	int capacite, nElements;
	Acteur** elements; // Pointeur vers un tableau de Acteur*, chaque Acteur* pointant vers un Acteur.
};

struct Film
{
	std::string titre, realisateur; // Titre et nom du r�alisateur (on suppose qu'il n'y a qu'un r�alisateur).
	int anneeSortie, recette; // Ann�e de sortie et recette globale du film en millions de dollars
	ListeActeurs acteurs;
};


class ListeFilms
{
public:
	explicit ListeFilms();
	explicit ListeFilms(std::string nomFichier);
	~ListeFilms();
	void ajouterFilm(Film* ptrFilm);
	Acteur* trouverActeur(std::string nom) const;
	void enleverFilm(Film* PtrFilm);
	void afficherListeFilms() const;
	void afficherFilm(const Film& film)const;
	void afficherActeur(const Acteur& acteur) const;
	void detruireFilm(Film* ptrFilm);
	void detruireListeFilms();
	Film* operator[] (const std::size_t index) const;


private:
	int capacite_, nElements_;
	Film** elements_;
	void doublerCapacite();
	Film* lireFilm(std::istream& fichier);
	Acteur* lireActeur(std::istream& fichier);
	Acteur* trouverActeurListeActeurs(std::string nomRechercher, ListeActeurs& listeActeurs) const;


};


struct Acteur
{
	std::string nom; int anneeNaissance; char sexe;
	ListeFilms joueDans;
};

void afficherFilmographieActeur(const ListeFilms& listeFilms, const std::string& nomActeur);