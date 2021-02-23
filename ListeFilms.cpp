/*
* Implémentation de la Classe ListeFilms, TD3-INF1015
*\file		ListeFilms.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		7 mars 2021
* Créé le	23 février 2021
*/
#include "ListeFilms.hpp"

typedef uint8_t UInt8;
typedef uint16_t UInt16;

using namespace std;
using namespace gsl;
using namespace iter;

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}


ListeFilms::ListeFilms()
{
	nElements_ = 0;
	capacite_ = 1;
	elements_ = new Film * [capacite_];
}


ListeFilms::ListeFilms(const string& nomFichier)
{

	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	nElements_ = 0;
	capacite_ = 1;
	int nFilms = lireUint16(fichier);
	elements_ = new Film * [capacite_];

	for (int i : iter::range(nFilms))
	{
		Film* film = lireFilm(fichier);
		ajouterFilm(film);
	}
}


void ListeFilms::detruire()
{
	while (nElements_ != 0)
	{
		detruireFilm(elements_[0]);
	}
	delete[] elements_;
	elements_ = nullptr;
}


Film* ListeFilms::lireFilm(istream& fichier)
{
	Film* film = new Film;
	film->titre = lireString(fichier);
	film->realisateur = lireString(fichier);
	film->anneeSortie = lireUint16(fichier);
	film->recette = lireUint16(fichier);

	//Allocation de la liste d'acteur
	film->acteurs = ListeActeurs{ lireUint8(fichier) }; 

	for (auto&& acteur:film->acteurs)
	{
		acteur= lireActeur(fichier);
	}
	return film;
}


shared_ptr<Acteur> ListeFilms::lireActeur(istream& fichier)
{
	string nom = lireString(fichier);
	int anneeNaissance = lireUint16(fichier);
	char sexe = lireUint8(fichier);

	shared_ptr<Acteur> acteur = make_shared<Acteur>(nom, anneeNaissance, sexe);

	shared_ptr<Acteur> acteurExistant = trouverActeur(acteur->nom);
	//check si existant
	if (acteurExistant)
	{
		acteur = nullptr;
		return acteurExistant;
	}
	else
	{	//Debug line
		cout << acteur->nom << endl;
		return  acteur; 
	}
}

shared_ptr<Acteur> ListeFilms::trouverActeur(const string& nom) const
{
	shared_ptr<Acteur> acteur = nullptr;

	for(auto&& film : *this)
	{
		acteur = trouverActeurListeActeurs(nom, film->acteurs);
		if (acteur)
			break;
	}
	return acteur;
}

shared_ptr<Acteur> ListeFilms::trouverActeurListeActeurs(const string& nomRechercher, const ListeActeurs& listeActeurs) const
{
	for(auto&& acteur: listeActeurs)
	{
		if (acteur->nom == nomRechercher)
			return acteur;
	}
	return nullptr;
}

void ListeFilms::detruireFilm(Film* film)
{
	enleverFilm(film);
	delete film;
	film = nullptr;
}


void ListeFilms::enleverFilm(Film* film)
{	
	for(int i : range(nElements_))
	{
		if (film == elements_[i])
		{
			elements_[i] = elements_[--nElements_];
			elements_[nElements_] = nullptr;
			break;
		}
	}
}

void ListeFilms::ajouterFilm( Film* film)
{
	if (nElements_ >= capacite_)
		doublerCapacite();
	//add film
	elements_[nElements_] = film;

	//update listeFilms
	nElements_++;

}


void ListeFilms::doublerCapacite()
{
	//doubler
	capacite_ *= 2;
	Film** oldElements = elements_;
	elements_ = new Film * [capacite_];
	//copier
	for (int i :range(nElements_))
	{
		elements_[i] = oldElements[i];
	}
	//delete
	delete[] oldElements;
	oldElements = nullptr;
}



void ListeFilms::afficher() const
{
	static const string ligneDeSeparation = "\n\033[35mфффффффффффффффффффффффффффффффффффффффф\033[0m\n";
	cout << ligneDeSeparation;
	for (auto&& film : *this)
	{
		cout << film;
		cout << ligneDeSeparation;
	}
}

ostream& ListeFilms::afficherActeur(ostream& ostream,const shared_ptr<Acteur>& acteur)
{
	ostream << "  " << acteur->nom << ", " << acteur->anneeNaissance << " " << acteur->sexe << endl;
	return ostream;
}


Film* ListeFilms::operator[] (size_t const index) const
{
	return elements_[index];
}

ostream& operator<< (ostream& ostream, const Film* film)
{
	ostream << " " << film->titre << ", " << film->realisateur << ", " << film->anneeSortie << ", " << film->recette << endl;
	for (auto&& acteur : film->acteurs)
	{
		ostream << "  " << acteur->nom << ", " << acteur->anneeNaissance << " " << acteur->sexe << endl;
	}
	return ostream;
}


Film* ListeFilms::trouverFilmSi(const std::function<bool(Film*)>& critere) const
{

	for (auto&& film : *this)
	{
		if (critere(film))
			return film;
	}
	return nullptr;
}

