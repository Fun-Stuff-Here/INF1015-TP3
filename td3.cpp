/*
* Programme qui lit un fichier de film et le manipule, TD3-INF1015
*\file		td3.cpp
*\author	Elizabeth Michaud 2073093, Nicolas Dépelteau 2083544
*\date		7 mars 2021
* Créé le	23 février 2021
*/

#define _CRT_SECURE_NO_WARNINGS // On permet d'utiliser les fonctions de copies de chaînes qui sont considérées non sécuritaires.
#include "ListeFilms.hpp"

using namespace std;
using namespace gsl;
using namespace iter;


int main()
{
	#ifdef VERIFICATION_ALLOCATION_INCLUS
	bibliotheque_cours::VerifierFuitesAllocations verifierFuitesAllocations;
	#endif
	bibliotheque_cours::activerCouleursAnsi();  // Permet sous Windows les "ANSI escape code" pour changer de couleurs https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac les supportent normalement par défaut.

	static const string ligneDeSeparation = "\n\033[35m═══════════════════════════════════════\033[0m\n";

	ListeFilms listeFilms{ "films.bin" };

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	
	cout << listeFilms[0] << endl;

	cout << ligneDeSeparation << "Les films sont:" << endl;

	listeFilms.afficher();

	shared_ptr<Acteur> ptrCumberbatch = listeFilms.trouverActeur("Benedict Cumberbatch");
	ptrCumberbatch->anneeNaissance = 1976;

	cout << ligneDeSeparation << "Chap 7 :" << endl;
	//chap 7
	ostringstream tamponStringStream;
	tamponStringStream << listeFilms[1];
	string filmEnString = tamponStringStream.str();
	cout << filmEnString << endl;

	cout << ligneDeSeparation << "Chap 7-8 :" << endl;
	//chap 7-8
	Film skylien = listeFilms[0]; /* listeFilms[0] ou *listeFilms[0] selon ce qui fait du sens */
	skylien.titre = "Skylien";
	skylien.acteurs[0] = listeFilms[1]->acteurs[0];
	skylien.acteurs[0]->nom = "Daniel Wroughton Craig";
	cout << &skylien;
	cout << listeFilms[0];
	cout << listeFilms[1];

	cout << ligneDeSeparation << "Chap 10 :" << endl;
	//chap 10

	cout << listeFilms.trouverFilmSi([](Film* film) -> bool {return film->recette == 955; }) << endl;

	cout << ligneDeSeparation << "Chap 9 :" << endl;
	//chap 9

	struct Point { double x, y; };
	Liste<string> listeTextes{ 2 };
	*listeTextes[0]=  "Cute Koala" ; *listeTextes[1] = "Cute Panda";
	Liste<string> listeTextes2 = listeTextes;
	
	std::shared_ptr<string> newText = std::make_shared<string>("Cute Turtle");
	listeTextes[0] = newText;
	*listeTextes[1] = "Cute Night Owl";

	cout << "listeTextes[0]	  " << "	Text:  " << *listeTextes[0] << "	Adress" << listeTextes[0] <<endl;
	cout << "listeTextes[1]   " << "	Text:  " << *listeTextes[1] << "	Adress" << listeTextes[1] << endl;
	cout << "listeTextes2[0]   " << "	Text:  " << *listeTextes2[0] << "	Adress" << listeTextes2[0] << endl;
	cout << "listeTextes2[1]   " << "	Text:  " << *listeTextes2[1] << "	Adress" << listeTextes2[1] << endl;

	listeFilms.detruireFilm(listeFilms[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;

	listeFilms.afficher();
	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme
	//(aucune ligne rouge dans la couverture de code;
	//c'est normal que les lignes de "new" et "delete" soient jaunes).
	//Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	cout << listeFilms.trouverFilmSi([](Film* film) -> bool {return film->titre == "Not there"; }) << endl;

	//L'objet verifierFuitesAllocations devrait afficher "Aucune fuite detectee." a la sortie du programme;
	//il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	listeFilms.detruire();
}


