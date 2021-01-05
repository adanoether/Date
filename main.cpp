 /*
 --------------------------------------------------------------------------
 Fichier       : main.cpp
 Auteur(e)     : Terrani Fabien, Ohan Mélodie
 Date          : 09.03.2020
 
 But           : Le but de ce laboratoire est de mettre à disposition une
                 librairie permettant de créer, manipuler des dates au
                 format : jj/mm/aaaa
                 Il doit notamment permettre l'affichage, la comparaison
                 entre deux dates ainsi que  d'additionner ou soustraire
                 des jours tout comme d'afficher une date.
                 Il doit être possible d'enregistrer un mois via
                 une liste d'enumération, une chaîne de caractère ou
                 un entier.
                 En cas de jours, mois incorrectes, un texte indiquant
                 l'erreur s'affiche au lieu d'une date impossible.

 Remarque(s)   :  -
 
 Compilateur   : MinGW-g++ 4.9.3
 --------------------------------------------------------------------------
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <limits>

#include "Date.h"

using namespace std;

// Fonction nécessaire à la démo
void showTitle(const string& s)
{
  cout << endl << endl;
  cout << s    << endl;
  cout << setfill('=') << setw(s.length()) << "" << endl;
  cout << setfill(' ');
}

int main()
{
  // Test des différents constructeurs
  //___________________________________________________________
  showTitle("Constructeurs");
  Date d1;
  Date d2(2, 3, 1995);
  Date d3(17, MonthList::APRIL, 2034);
  cout << "Constructeur sans parametre         : " << d1 << endl;
  cout << "Constructeur avec mois en unsigned  : " << d2 << endl;
  cout << "Constructeur avec mois en enum class: " << d3 << endl;

  // Test des getters
  //___________________________________________________________
  showTitle("Getters");
  Date dateGet(5, 8, 1967);
  cout << "Date             : "   << dateGet                          << endl;
  cout << "getDay()         : "   << dateGet.getDay()                 << endl;
  cout << "getMonthNo()     : "   << dateGet.getMonthNo()             << endl;
  cout << "getMonthString() : "   << dateGet.getMonthString()         << endl;
  cout << "getMonthEnum()   : "   << (unsigned)dateGet.getMonthEnum() << endl;
  cout << "getYear()        : "   << dateGet.getYear()                << endl;


  // Test des setters
  //___________________________________________________________
  showTitle("Setters");
  Date dateSet(5, 8, 1967);
  cout << "Date                            : "   << dateSet << endl;

  dateSet.setDay(23);
  cout << "Apres setDay(23)                : "   << dateSet << endl;

  dateSet.setMonth(2);
  cout << "Apres setMonth(2)               : "   << dateSet << endl;

  dateSet.setMonth("avril");
  cout << "Apres setMonth(\"avril\")         : " << dateSet << endl;

  dateSet.setMonth(MonthList::JUNE);
  cout << "Apres setMonth(MonthList::JUNE) : "   << dateSet << endl;

  dateSet.setYear(1999);
  cout << "Apres setYear(1999)             : "   << dateSet << endl;

  // Tests d'affichages de dates incorrectes
  //___________________________________________________________

  // Mois incorrecte:
  cout << endl
       << "Mois erronne        :"     << endl;
  Date incorrectMonth(14, 12, 2002);
  cout << "Date                : "    << incorrectMonth << endl;
  incorrectMonth.setMonth(13);
  cout << "Apres setMonth(13)  : "    << incorrectMonth << endl;

  // Jour erronnee
  cout << endl
       << "Jour erronne        : "   << endl;
  Date incorrectDay(17, 2, 2004);
  cout << "Date                : "   << incorrectDay << endl;
  incorrectDay.setDay(30);
  cout << "Apres setDay(30)    : "   << incorrectDay << endl;


  // Test décrémentation
  //___________________________________________________________
  showTitle("Test decrementation");
  Date dateDecr(2, 1, 2019);
  cout << "Date initiale: " << dateDecr << endl;

  for (int i = 1; i <= 3; ++i)
  {
    Date result = --dateDecr;
    cout << "Date apres pre-decrementation : "  << result   << " ";
    cout << "(Valeur retournee par ++d     : "  << result   << ")"  << endl;
    result = dateDecr--;
    cout << "Date apres post-decrementation: " << dateDecr  << " ";
    cout << "(Valeur retournee par d++     : " << result    << ")"  << endl;
  }

  // Test incrémentation
  //___________________________________________________________
  showTitle("Test incrementation");
  Date dateIncr(27, 2, 2020);
  cout << "Date initiale: " << dateIncr << endl;

  for (int i = 1; i <= 3; ++i)
  {
    Date result = ++dateIncr;
    cout << "Date apres pre-decrementation  : " << result   << " ";
    cout << "(Valeur retournee par ++d      : " << result   << ")" << endl;
    result = dateIncr++;
    cout << "Date apres post-decrementation : " << dateIncr << " ";
    cout << "(Valeur retournee par d++      : " << result   << ")" << endl;
  }


  // Test addition et soustraction d'entiers
  //___________________________________________________________
  showTitle("Test addition et soustraction d'entiers");
  Date datePlusMoins(18, 12, 2019);
  int nbDays = 23;
  cout << nbDays        << " + " << datePlusMoins << " = " << (nbDays + datePlusMoins) << endl;
  cout << datePlusMoins << " + " << nbDays        << " = " << (datePlusMoins + nbDays) << endl;
  cout << datePlusMoins << " - " << nbDays        << " = " << (datePlusMoins - nbDays) << endl;


  // Test comparaison de dates
  //___________________________________________________________
  showTitle("Test comparaison de dates");
  Date a(18, 12, 2019);
  Date b(17, 12, 2019);

  cout << boolalpha;
  cout << a << " <  " << b << " ? " << (a < b)  << endl;
  cout << a << " >  " << b << " ? " << (a > b)  << endl;
  cout << a << " == " << b << " ? " << (a == b) << endl;
  cout << a << " != " << b << " ? " << (a != b) << endl;
  cout << a << " >= " << b << " ? " << (a >= b) << endl;
  cout << a << " <= " << b << " ? " << (a <= b) << endl;

  // Test saisies de date
  //___________________________________________________________
  showTitle("Test saisie de date et cast en string");
  Date dateInput;
  bool retry;

  do
  {
    retry = false;
    cout << "Veuillez saisir une date [jj.mm.aaaa] : ";
    cin >> dateInput;

    if (cin.fail())
    {
      cin.clear();
      // Pas besoin de clear le buffer de cin car getline() prend le caractère \n
      cout << "Date invalide! Veuillez respecter le format prevu." << endl;
      retry = true;
    }
  } while (retry);

  cout << "Date saisie          : " << dateInput         << endl;
  cout << "Date castee en string: " << string(dateInput) << endl;

  return EXIT_SUCCESS;
}