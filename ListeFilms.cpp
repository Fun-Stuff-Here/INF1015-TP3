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


ListeFilms::ListeFilms(std::string nomFichier)
{

	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);

	nElements_ = 0;
	capacite_ = 1;
	int nFilms = lireUint16(fichier);
	elements_ = new Film * [capacite_];

	for (int i = 0; i < nFilms; i++) {
		Film* ptrFilm = lireFilm(fichier);
		ajouterFilm(ptrFilm);
	}
}


ListeFilms::~ListeFilms()
{
	//vu à la semaine 4, utiliser la méthode detruireListeFilms à la place
}

void ListeFilms::detruireListeFilms()
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
	Film* filmPtr = new Film;
	filmPtr->titre = lireString(fichier);
	filmPtr->realisateur = lireString(fichier);
	filmPtr->anneeSortie = lireUint16(fichier);
	filmPtr->recette = lireUint16(fichier);

	//Allocation de la liste d'acteur
	filmPtr->acteurs = ListeActeurs{ lireUint8(fichier) }; 

	for (int i = 0; i < filmPtr->acteurs.get_capacite(); i++) 
	{
		filmPtr->acteurs[i] = lireActeur(fichier); 
	}
	return filmPtr;
}


shared_ptr<Acteur> ListeFilms::lireActeur(istream& fichier)
{
	string nom = lireString(fichier);
	int anneeNaissance = lireUint16(fichier);
	char sexe = lireUint8(fichier);

	shared_ptr<Acteur> actPtr = make_shared<Acteur>(nom, anneeNaissance, sexe);

	shared_ptr<Acteur> acteurExistant = trouverActeur(actPtr->nom);
	//check si existant
	if (acteurExistant != nullptr)
	{
		actPtr = nullptr;
		return acteurExistant;
	}
	else
	{	//Debug line
		cout << actPtr->nom << endl;
		return  actPtr; 
	}
}

shared_ptr<Acteur> ListeFilms::trouverActeur(string nom) const
{
	shared_ptr<Acteur> ptrActeur = nullptr;
	for (int i = 0; i < nElements_; i++)
	{
		ptrActeur = trouverActeurListeActeurs(nom, elements_[i]->acteurs);
		if (ptrActeur != nullptr)
			break;
	}
	return ptrActeur;
}

shared_ptr<Acteur> ListeFilms::trouverActeurListeActeurs(string nomRechercher, ListeActeurs& listeActeurs) const
{
	for (int i = 0; i < listeActeurs.get_nElements(); i++)
	{
		if (listeActeurs[i]->nom == nomRechercher)
			return listeActeurs[i];
	}
	return nullptr;
}

void ListeFilms::detruireFilm(Film* ptrFilm)
{
	enleverFilm(ptrFilm);
	delete ptrFilm;
	ptrFilm = nullptr;
}


void ListeFilms::enleverFilm(Film* ptrFilm)
{
	for (int i = 0; i < nElements_; i++)
	{
		if (ptrFilm == elements_[i])
		{
			elements_[i] = elements_[--nElements_];
			elements_[nElements_] = nullptr;
			break;
		}

	}
}

void ListeFilms::ajouterFilm(Film* ptrFilm)
{
	if (nElements_ >= capacite_)
		doublerCapacite();
	//add film
	elements_[nElements_] = ptrFilm;

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
	for (int i = 0; i < nElements_; i++)
	{
		elements_[i] = oldElements[i];
	}
	//delete
	delete[] oldElements;
	oldElements = nullptr;
}



void ListeFilms::afficherListeFilms() const
{
	static const string ligneDeSeparation = "\n\033[35mфффффффффффффффффффффффффффффффффффффффф\033[0m\n";
	cout << ligneDeSeparation;
	span<Film*> lFilms{ elements_, nElements_ };
	for (int i = 0; i < lFilms.size(); i++) {
		cout << lFilms[i];
		cout << ligneDeSeparation;
	}
}

ostream& ListeFilms::afficherActeur(ostream& o,const shared_ptr<Acteur>& acteur)
{
	o << "  " << acteur->nom << ", " << acteur->anneeNaissance << " " << acteur->sexe << endl;
	return o;
}


Film* ListeFilms::operator[] (size_t const index) const
{
	return elements_[index];
}

ostream& operator<< (ostream& o, const Film* film)
{
	o << " " << film->titre << ", " << film->realisateur << ", " << film->anneeSortie << ", " << film->recette << endl;
	for (int i = 0; i < film->acteurs.get_nElements(); i++)
	{
		shared_ptr<Acteur> acteur = film->acteurs[i];
		o << "  " << acteur->nom << ", " << acteur->anneeNaissance << " " << acteur->sexe << endl;
	}
	return o;
}


Film* ListeFilms::trouverFilmSi(const std::function<bool(Film*)>& critere) const
{

	for (Film* film : span<Film*>{elements_,nElements_})
	{
		if (critere(film))
			return film;
	}

	return nullptr;
}

