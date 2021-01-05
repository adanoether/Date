/*
 --------------------------------------------------------------------------
 Fichier       : Date.h
 Auteur(e)     : Terrani Fabien, Ohan Mélodie
 Date          : 09.03.2020

 But           : Fichier d'entête de la librairie Date.
                 Ce fichier comprend la déclaration et la définition de la
                 classe Date ainsi que la liste d'enumération MonthList
                 et le vecteur nécessaire à son fonctionnement.
                 La librairie permet la création, la modification de dates
                 au format JJ.MM.AAAA.
                 Elle assume également l'affectation de Mois au format
                 string, MonthList ainsi qu'unsigned (1-12).
                 Elle met à disposition la comparaison entre deux dates
                 et la possibilité d'additionner ou soustraires des jours
                 tout comme la pré et post incrémentation de dates.

 Remarque(s)   : Nous n'avons pas implémenté de limite d'année.
                 A la saisie, une année sera considérée comme erronée
                 Ssi elle ne s'exprime pas sur 4 chiffres car le format
                 est jj.mm.aaaa

 Compilateur   : MinGW-g++ 4.9.3
 --------------------------------------------------------------------------
 */

#ifndef DATE_H
#define DATE_H

#include <string>
#include <vector>
#include <iostream>

// Fait la correspondance avec le vecteur et est utilisés pour les tests
enum class MonthList
{
  JANUARY = 1,
  FEBRUARY,
  MARCH,
  APRIL,
  MAY,
  JUNE,
  JULY,
  AUGUST,
  SEPTEMBER,
  OCTOBER,
  NOVEMBER,
  DECEMBER
};
// Est utilisé pour l'enregistrement d'une date
const std::vector<std::string> MONTHS =
    {"",        // pour correspondre à la liste d'enumération et no de mois.
     "janvier",
     "fevrier",
     "mars",
     "avril",
     "mai",
     "juin",
     "juillet",
     "aout",
     "septembre",
     "octobre",
     "novembre",
     "decembre"
    };


class Date
{
  // Surcharge d'opérateurs, fonctions amies
  //___________________________________________________________________

  /**
   * @brief   Cast la date en string avant de l'afficher.
   *          Si la date est incorrecte/impossible, affiche un texte d'erreur
   * @authors Terrani Fabien, Ohan Mélodie
   * @Date    09/03/2020
   *
   * @param os
   * @param d  objet date
   */
  friend std::ostream& operator<<(std::ostream& os, const Date& d);

  /**
   * @brief    Lit une date dans le flux d'entrée et la stocke dans d
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @param is Le flux d'entrée dans lequel s'est fait la saisie de la date
   * @param d L'objet Date qui contiendra la date saisie par l'utilisateur
   */
  friend std::istream& operator>>(std::istream& is, Date& d);

  /**
   * @brief   surcharge de l'opérateur +, permet l'addition n + date
   *          cela a pour effet d'additionner n au nbre de jours
   * @authors Terrani Fabien, Ohan Mélodie
   * @Date    09/03/2020
   * @param n nbre de jours à additionner
   * @param d objet date
   * @return  le resultat de l'addition
   */
  friend Date operator+(int n, const Date& d);

  /**
  * @brief   surcharge de l'opérateur +, permet l'addition date + n
  *          cela a pour effet d'additionner n au nbre de jours
  * @authors Terrani Fabien, Ohan Mélodie
  * @Date    09/03/2020
  * @param n nbre de jours à additionner
  * @param d objet date
  * @return  le resultat de l'addition
  */
  friend Date operator+(const Date& d, int n);

  /**
   * @brief   surcharge de l'opérateur -, permet l'addition date - n
   *          cela a pour effet de soustraire n au nbre de jours
   * @authors Terrani Fabien, Ohan Mélodie
   * @Date    09/03/2020
   * @param n nbre de jours à soustraire à la date
   * @param d objet date
   * @return  le resultat de la soustraction
   */
  friend Date operator-(const Date& d, int n);
  // remarques: l'opération n-date ne faisant pas sens nous ne l'avons pas implémenté


public:

  // Constructeurs
  //___________________________________________________________________

  /**
   * @brief    Constructeur par défaut. Crée une date au 1er janvier 1970.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date();

  /**
   * @brief    Constructeur de Date avec mois en unsigned
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date(unsigned day, unsigned month, unsigned year);

  /**
    * @brief    Constructeur de Date avec mois en enum class MonthList
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    */
  Date(unsigned day, const    MonthList& month, unsigned year);

  // Setters
  //___________________________________________________________________

  /**
   * @brief    Affecte le jour
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @param day
   */
  void setDay(unsigned day);

  /**
  * @brief    Affecte la date au format unsigned
  * @authors  Terrani Fabien, Ohan Mélodie
  * @Date     09/03/2020
  */
  void setMonth(unsigned month);

  /**
  * @brief    Affecte la date au format unsigned
  *           à partir d'un enum Montlist
  * @authors  Terrani Fabien, Ohan Mélodie
  * @Date     09/03/2020
  */
  void setMonth(const MonthList& month);

  /**
  * @brief    Affecte la date au format unsigned
  *           à partir d'un string correspondant au vecteur.
  * @authors  Terrani Fabien, Ohan Mélodie
  * @Date     09/03/2020
  */
  void setMonth(const std::string& month);

  /**
  * @brief    Affecte l'année.
  * @authors  Terrani Fabien, Ohan Mélodie
  * @Date     09/03/2020
  */
  void setYear(unsigned year);

  // Getters
  //___________________________________________________________________

  /**
   * @brief    Retourne le jour de l'objet date
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return  jour de la date
   */
  unsigned getDay() const;

  /**
   * @brief    Retourne le no du mois en unsigned
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return  no du mois de la date
   */
  unsigned getMonthNo() const;

  /**
   * @brief    Retourne le mois en chaîne de caractère.
   *           Se base sur le vecteur de string
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return  chaîne du mois de la date
   */
  std::string getMonthString() const;

  /**
   * @brief    Retourne le no sous forme enum MonthList du mois
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return  Monthlist du mois de la date
   */
  MonthList getMonthEnum() const;
  /**
   * @brief    Retourne l'année de la date
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return  année
   */
  unsigned getYear() const;


  // Fonctions membres de vérifications
  //___________________________________________________________________

  /**
   * @brief    Getter de l'attribut correct, indique si la date est
   *           erronée ou non
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return vrai si la date est correcte
   */
  bool isCorrect() const;

  /**
   * @brief    Effectue la vérification de tous les elements d'une
   *           date.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return vrai si la date est correcte
   */
  void checkDate();

  /**
   * @brief    Vérifie si l'année est bissextile
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return vrai si il s'agit d'une année bissextile
   */
  bool isLeapYear() const;

  /**
   * @brief    Vérifie si l'année est bissextile, cette variante
   *           permet de vérifier n'importe quelle année.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   * @return vrai si il s'agit d'une année bissextile
   */
  bool isLeapYear(unsigned year) const;


  // Surchage, opérateurs membres
  //___________________________________________________________________
  /**
    * @brief    Retourne vrai si la date de droite est antérieur
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    * @param d date
    */
  bool operator<(const Date& d) const;

  /**
    * @brief    Retourne vrai si la date de gauche est antérieur
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    * @param d date
    */
  bool operator>(const Date& d) const;

  /**
    * @brief    Retourne vrai si les dates sont identiques
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    * @param d date
   */
  bool operator==(const Date& d) const;

  /**
    * @brief    Retourne vrai si les dates sont différentes
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    * @param d date
   */
  bool operator!=(const Date& d) const;

  /**
    * @brief    Retourne vrai la date de droite est antérieur ou égal
    *           à celle de droite.
    * @authors  Terrani Fabien, Ohan Mélodie
    * @Date     09/03/2020
    * @param d date
   */
  bool operator<=(const Date& d) const;

  /**
   * @brief    Retourne vrai la date de gauche est antérieur ou égal
   *           à celle de droite.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  bool operator>=(const Date& d) const;

  /**
   * @brief    Pré-incrémente la date d'un jour
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date& operator++();

  /**
   * @brief    Post-incrémente la date d'un jour
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date operator++(int);

  /**
   * @brief    Pré-décrémente la date d'un jour
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date& operator--();

  /**
   * @brief    Post-décrémente la date d'un jour
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  Date operator--(int);

  /**
   * @brief    Permet le cast en string de l'objet Date courrant.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  operator std::string() const;



private:
  unsigned day;
  unsigned month;
  unsigned year;
  bool correct;

  /**
   * @brief    Vérifie que le no mois est compris entre Janvier
   *           et Décembre.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  bool isMonthCorrect() const;

  /**
   * @brief    Vérifie qu'un no mois est compris entre Janvier
   *           et Décembre.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  bool isMonthCorrect(unsigned month) const;

  /**
   * @brief    Vérifie que le jour est correcte.
   *           Elle se base sur l'année courante.
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  bool isDayCorrect() const;

  /**
  * @brief    Retourne le nbre de jours d'un mois.
  *           Se base sur l'année courrante.
  * @authors  Terrani Fabien, Ohan Mélodie
  * @Date     09/03/2020
  */
  unsigned nbDaysOfMonth() const;

  /**
   * @brief    Retourne le nbre de jours d'un mois
   * @authors  Terrani Fabien, Ohan Mélodie
   * @Date     09/03/2020
   */
  unsigned nbDaysOfMonth(unsigned month, unsigned year) const;
};

#endif /* DATE_H */
