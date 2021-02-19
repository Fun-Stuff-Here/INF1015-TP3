/////////////////////////////////////////////////////////////////
// D�finitions de la classe ListeFilms 
// Auteurs : Elizabeth Michaud 2073093, Nicolas D�pelteau 2083544
// TD3-INF1015
/////////////////////////////////////////////////////////////////
#pragma once
#pragma region "Includes"//{
#include "ListeFilms.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp" // Nos fonctions pour le rapport de fuites de m�moire.
#include "debogage_memoire.hpp"   // Ajout des num�ros de ligne des "new" dans le rapport de fuites.
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
#include "Liste.hpp"
#pragma endregion//}

struct Film; struct Acteur; // Permet d'utiliser les types alors qu'ils seront d�fini apr�s.
using ListeActeurs = Liste<Acteur>;

struct Film
{
	std::string titre, realisateur; // Titre et nom du r�alisateur (on suppose qu'il n'y a qu'un r�alisateur).
	int anneeSortie, recette; // Ann�e de sortie et recette globale du film en millions de dollars
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
	std::ostream& afficherActeur(std::ostream& o, const std::shared_ptr<Acteur>& acteur);
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
	Acteur(std::string name, int birthYear, char sex)
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

std::ostream& operator<< (std::ostream& o, const Film* film);










