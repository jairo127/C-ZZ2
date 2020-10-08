#include <fstream>
#include <iostream>

#include "catch.hpp"
#include "point.hpp"
#include "rectangle.hpp"
#include "cercle.hpp"
#include "forme.hpp"
#include "groupe.hpp"

// NOTE : ce test utilise des enum "class"
// il faut donc utiliser un compilateur g++ >= 6.1
// ou activer l'option c++11 du compilateur
// -std=c++11 ou -std=c++0x sur les tres vieux compilateurs

// Les tests ne sont pas exhaustifs, loin de là

TEST_CASE("Instanciation", "[Point]") {
	Point p1;
	REQUIRE(p1.getX() == 0);
	REQUIRE(p1.getY() == 0);
	
    p1.setX(11);
    p1.setY(21);

    REQUIRE(p1.getX() == 11);
	REQUIRE(p1.getY() == 21);

	Point p2(12, 22);

	REQUIRE(p2.getX() == 12);
	REQUIRE(p2.getY() ==  22);
}

TEST_CASE("Origine", "[Point]") {
	REQUIRE(Point::ORIGINE.getX() == 0);
	REQUIRE(Point::ORIGINE.getY() == 0);
}

/*
TEST_CASE("Compteur", "[Forme]") {
   // Pour être correct, ce test doit etre le premier sur Forme
   REQUIRE(0 == Forme::prochainId());
   Forme f1;
   REQUIRE(0 == f1.getId());
   REQUIRE(1 ==  Forme::prochainId());	
   // Verification que la valeur n'est pas decrementee accidentellement.
   Forme *p = new Forme;
   REQUIRE(1 == p->getId());
   delete p;
   REQUIRE(2 == Forme::prochainId());	
}

TEST_CASE("Instanciation1", "[Forme]") {
	Forme f1;
	REQUIRE(f1.getPoint().getX() == 0);
	REQUIRE(f1.getPoint().getY() == 0);
	REQUIRE(f1.getCouleur() ==  COULEURS::BLEU);
}

TEST_CASE("Instanciation2", "[Forme]") {
	Forme f2;
	
	f2.setX(15);
	f2.setY(25);
	f2.setCouleur(COULEURS::VERT);
	REQUIRE (f2.getPoint().getX() == 15);
	REQUIRE (f2.getPoint().getY() == 25);
	REQUIRE (f2.getCouleur() == COULEURS::VERT);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::ROUGE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::JAUNE);
}

TEST_CASE("Instanciation3", "[Forme]") {
    // IL N'Y A PAS D'ERREUR DANS LE TEST, CELA DOIT MARCHER	
	Forme f2(Point(10,20), COULEURS::ROUGE);
	REQUIRE (f2.getPoint().getX() == 10);
	REQUIRE (f2.getPoint().getY() == 20);
	REQUIRE (f2.getCouleur() == COULEURS::ROUGE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);

	f2.getPoint().setX(15);
	f2.getPoint().setY(25);
	f2.setCouleur(COULEURS::JAUNE);
	REQUIRE (f2.getPoint().getX() == 15);
	REQUIRE (f2.getPoint().getY() == 25);
	REQUIRE (f2.getCouleur() == COULEURS::JAUNE);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::BLEU);
	REQUIRE_FALSE (f2.getCouleur() == COULEURS::ROUGE);
}

TEST_CASE("BoiteEnglobante", "[Forme]") {
	Forme f;
	REQUIRE (f.getLargeur() == 0);
	REQUIRE (f.getHauteur() == 0);
}
*/

TEST_CASE("Cercle", "[Cercle]") {
   int compteur = Forme::prochainId();
   Cercle c1;
   Cercle c2(6); 
   
   REQUIRE(c1.toString() == "CERCLE 0 0 0 0");
   REQUIRE(c2.toString() == "CERCLE 0 0 12 12");

   c2.setRayon(3);
   REQUIRE(c2.getRayon()   == 3);
   REQUIRE(c2.toString()   == "CERCLE 0 0 6 6");
   REQUIRE(c2.getLargeur() == 6);
   REQUIRE(c2.getHauteur() == 6);

   REQUIRE(Forme::prochainId() == (compteur+2) ); 
}

TEST_CASE("Polymorphisme", "[Forme]") {
   Forme * f1 = new Cercle;
   Forme * f2 = new Rectangle;

   REQUIRE(f1->toString() == "CERCLE 0 0 0 0");
   REQUIRE(f2->toString() == "RECTANGLE 0 0 0 0");

   delete f1;
   delete f2;
}

TEST_CASE("Groupe", "[Forme]") {
	Forme * f1 = new Cercle(2, 3, 4, 5);
	Forme * f2 = new Rectangle(1, 2, 8, 8);
	Forme * f3 = new Cercle(15, 15, 5, 5);
	Groupe p;

	REQUIRE(p.getPoint().getX() == 0);
	REQUIRE(p.getPoint().getY() == 0);
	REQUIRE(p.max_x == 0);
	REQUIRE(p.max_y == 0);
	REQUIRE(p.getLargeur() == 0);
	REQUIRE(p.getHauteur() == 0);
	REQUIRE(p.nb_forme == 0);

	p.ajouterForme(f1);
	REQUIRE(p.getPoint().getX() == 2);
	REQUIRE(p.getPoint().getY() == 3);
	REQUIRE(p.max_x == 6);
	REQUIRE(p.max_y == 8);
	REQUIRE(p.getLargeur() == 4);
	REQUIRE(p.getHauteur() == 5);
	REQUIRE(p.nb_forme == 1);

	p.ajouterForme(f2);
	REQUIRE(p.getPoint().getX() == 1);
	REQUIRE(p.getPoint().getY() == 2);
	REQUIRE(p.max_x == 9);
	REQUIRE(p.max_y == 10);
	REQUIRE(p.getLargeur() == 8);
	REQUIRE(p.getHauteur() == 8);
	REQUIRE(p.nb_forme == 2);

	p.ajouterForme(f3);
	REQUIRE(p.getPoint().getX() == 1);
	REQUIRE(p.getPoint().getY() == 2);
	REQUIRE(p.max_x == 20);
	REQUIRE(p.max_y == 20);
	REQUIRE(p.getLargeur() == 19);
	REQUIRE(p.getHauteur() == 18);
	REQUIRE(p.nb_forme == 3);

	delete f1;
	delete f2;
	delete f3;
}