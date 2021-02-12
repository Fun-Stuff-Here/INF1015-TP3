﻿
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

	static const string ligneDeSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";

	//TODO: Chaque TODO dans cette fonction devrait se faire en 1 ou 2 lignes, en appelant les fonctions écrites.

	//TODO: La ligne suivante devrait lire le fichier binaire en allouant la mémoire nécessaire.
	//Devrait afficher les noms de 20 acteurs sans doublons (par l'affichage pour fins de débogage dans votre fonction lireActeur).
	ListeFilms listeFilms{ "../films.bin" };

	cout << ligneDeSeparation << "Le premier film de la liste est:" << endl;
	//TODO: Afficher le premier film de la liste.  Devrait être Alien.
	cout << listeFilms[0] << endl;

	ostringstream tamponStringStream;
	tamponStringStream << listeFilms[1];
	string filmEnString = tamponStringStream.str(); 
	cout << filmEnString << endl;



	cout << ligneDeSeparation << "Les films sont:" << endl;
	//TODO: Afficher la liste des films.  Il devrait y en avoir 7.
	listeFilms.afficherListeFilms();
	//TODO: Modifier l'année de naissance de Benedict Cumberbatch pour être 1976 (elle était 0 dans les données lues du fichier).
	//Vous ne pouvez pas supposer l'ordre des films et des acteurs dans les listes, il faut y aller par son nom.
	shared_ptr<Acteur> ptrCumberbatch = listeFilms.trouverActeur("Benedict Cumberbatch");
	ptrCumberbatch->anneeNaissance = 1976;
	cout << ligneDeSeparation << "Liste des films où Benedict Cumberbatch joue sont:" << endl;


	//chap 7-8
	Film skylien = listeFilms[0]; /* listeFilms[0] ou *listeFilms[0] selon ce qui fait du sens */
	skylien.titre = "Skylien";
	skylien.acteurs.elements[0] = listeFilms[1]->acteurs.elements[0];
	skylien.acteurs.elements[0]->nom = "Daniel Wroughton Craig";
	cout << &skylien;
	cout << listeFilms[0];
	cout << listeFilms[1];


	//TODO: Afficher la liste des films où Benedict Cumberbatch joue.  Il devrait y avoir Le Hobbit et Le jeu de l'imitation.
	//afficherFilmographieActeur(listeFilms, ptrCumberbatch->nom);
	//TODO: Détruire et enlever le premier film de la liste (Alien).  Ceci devrait "automatiquement" (par ce que font vos fonctions)
	//détruire les acteurs Tom Skerritt et John Hurt, mais pas Sigourney Weaver puisqu'elle joue aussi dans Avatar.
	listeFilms.detruireFilm(listeFilms[0]);
	cout << ligneDeSeparation << "Les films sont maintenant:" << endl;
	//TODO: Afficher la liste des films.
	listeFilms.afficherListeFilms();
	//TODO: Faire les appels qui manquent pour avoir 0% de lignes non exécutées dans le programme
	//(aucune ligne rouge dans la couverture de code;
	//c'est normal que les lignes de "new" et "delete" soient jaunes).
	//Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	//afficherFilmographieActeur(listeFilms, "qwerty");
	//TODO: Détruire tout avant de terminer le programme.
	//L'objet verifierFuitesAllocations devrait afficher "Aucune fuite detectee." a la sortie du programme;
	//il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	listeFilms.detruireListeFilms();
}


