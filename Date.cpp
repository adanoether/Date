/*
 --------------------------------------------------------------------------
 Fichier       : Date.cpp
 Auteur(e)     : Terrani Fabien, Ohan Mélodie
 Date          : 09.03.2020
 
 But           : Fournir une implémentation de la classe Date décrite 
				 dans Date.h

 Remarque(s)   : Fichier de sources de la librairie Date.h,
                 contient le codes des fonctions membres de la classe
                 Date.h.

   Remarque(s)   : -

   Compilateur   : MinGW-g++ 4.9.3
 --------------------------------------------------------------------------
 */

#include <algorithm>    // distance, find
#include <iostream>     // cout
#include <sstream>      // stringstream
#include <iomanip>
#include <cctype>       // isdigit
#include <limits>
#include "Date.h"

using namespace std;

// Surcharge d'opérateurs, fonctions amies
//___________________________________________________________________

ostream& operator<<(ostream& os, const Date& d){
  return os << string(d);
}

istream& operator>>(istream& is, Date& d){
  static const size_t MAX_LINE_LENGTH = 16;
  char chars[MAX_LINE_LENGTH];
  bool validFormat = true;

  is.getline(chars, MAX_LINE_LENGTH);
  string str(chars);

  if (str.length() == 10){

    for (size_t i = 0; validFormat && i < str.length(); ++i){

      if (i == 2 || i == 5){
        validFormat = str[i] == '.';
      }else{ // si l'index n'est ni 2 ni 5
        validFormat = isdigit(str[i]);
      }
    }

    if (validFormat){

      d.setDay(stoi(str.substr(0, 2),   nullptr, 10));
      d.setMonth(stoi(str.substr(3, 2), nullptr, 10));
      d.setYear(stoi(str.substr(6, 4),  nullptr, 10));

    }
  }else{  // si la longueur n'est pas de 10
    validFormat = false;
  }

  // Si le format est incorrecte
  if (!validFormat){
    is.setstate(ios::failbit);
  }

  return is;
}

Date operator+(int n, const Date& d){
  // appelle à l'autre opérateur d'addition
  return (d+n);
}

Date operator+(const Date& d, int n){
  // Si on demande à additionner un nombre négatif
  if(n<0){
    return d-(-n);
  }
  // cas plus complexes
  Date resDate = d;

  do{ // tant que n!=0

    // cas trivial et sortie
    if(n+resDate.day < resDate.nbDaysOfMonth()){
      resDate.day+=(unsigned)n;
      return resDate;
    }

    // si on doit changer de mois:
    if(resDate.day == resDate.nbDaysOfMonth()){
      resDate.day = 1;
      --n;
      // si on était à la fin de l'année
      if(resDate.month==(unsigned)MonthList::DECEMBER){
        resDate.month = (unsigned)MonthList::JANUARY;
        ++resDate.year;

        // Si non on incrémente juste le mois
      }else{
        ++resDate.month;
      }
    }
    // si l'addition qui dépasse le mois
    if((resDate.day + n) > resDate.nbDaysOfMonth() ){

      // on va forcer le fait d'atteindre le 31
      unsigned difference = resDate.nbDaysOfMonth() - resDate.day;
      n-=difference;
      resDate.day+= difference;
    }
  }while(n!=0);
  return resDate;
}

Date operator-(const Date& d, int n){

  // La soustraction d'un nbre négatif est une addition
  // Donc, on fait appel à l'autre surcharge.
  if (n < 0){
    return d + (-n);
  }

  unsigned daysToRemove = unsigned(n);     //  pour éviter de cast en unsigned à chaque fois.
  Date resDate(d);                         //  resultat de la soustraction

  // Cas trivial, si le nbre de jours est plus petit que le jour
  if (daysToRemove < resDate.day){
    resDate.day -= daysToRemove;
    return resDate;
    // Cas plus complexe, l'on risque de changer de mois ou d'années
  }else{

    // Pour s'abstenir de vérifier tous les cas, on calcule tout depuis la fin.
    // on conserve cette difference ici
    daysToRemove += (resDate.nbDaysOfMonth() - resDate.day);
    resDate.day    = resDate.nbDaysOfMonth();

    // Tant que le nbre de jours est plus grand que le nbre
    // de jours du mois courant
    while (daysToRemove >= resDate.nbDaysOfMonth()){

      daysToRemove -= resDate.nbDaysOfMonth();

      if (resDate.month == (unsigned)MonthList::JANUARY){
        resDate.month = (unsigned)MonthList::DECEMBER;
        --resDate.year;
      }else{
        --resDate.month;
      }
    }
    // réajuste
    resDate.day -= daysToRemove;
  }

  return resDate;
}


// Constructeurs
//__________________________________________________________________

Date::Date() : Date::Date(1, 1, 1970){}

Date::Date(unsigned day, unsigned month, unsigned year) :
    day(day), month(month), year(year){
  this->checkDate();
}
Date::Date(unsigned day, const MonthList& month, unsigned year) :
    Date::Date(day, (unsigned) month, year)
{
}


// Setters
//__________________________________________________________________

void Date::setDay(unsigned day){
  this->day = day;
  this->checkDate();
}

void Date::setMonth(unsigned month){
  this->month = month;
  this->checkDate();
}

void Date::setMonth(const MonthList& month){
  this->month = (unsigned)month;
  this->checkDate();
}

void Date::setMonth(const std::string& month){
  auto it = find(MONTHS.cbegin(), MONTHS.cend(), month);
  // Si le mois n'est pas trouvé dans la liste il vaut 0
  this->month = (it != MONTHS.end()) ? (unsigned) distance(MONTHS.cbegin(), it) : 0;
  this->checkDate();
}

void Date::setYear(unsigned year){
  this->year = year;
  this->checkDate();
}

// Getters
//__________________________________________________________________

unsigned Date::getDay() const{
  return day;
}

unsigned Date::getMonthNo() const{
  return month;
}

string Date::getMonthString() const{
  if (!this->isMonthCorrect()){
    return MONTHS[0];
  }
  return MONTHS[month];
}

MonthList Date::getMonthEnum() const{
  return MonthList(month);
}

unsigned Date::getYear() const{
  return year;
}


// Fonctions membres de vérifications
//___________________________________________________________________

bool Date::isCorrect() const{
  return correct;
}

void Date::checkDate(){
  correct = (isMonthCorrect() && isDayCorrect());
}

bool Date::isLeapYear() const{
  return this->isLeapYear(this->year);
}

bool Date::isLeapYear(unsigned year) const{
  // si multiple de 400 ou de 4 et pas 100
  return (year % 400 == 0) || (year % 4 == 0  &&  year % 100 != 0);
}




// Surcharge, opérateurs membres
//___________________________________________________________________

bool Date::operator<(const Date& d) const{
  // Si la date à droite est antérieur à celle de gauche
  return (year  >= d.year  &&
          month >= d.month &&
          day   > d.day);
}

bool Date::operator>(const Date& d) const{
  return d < *this;
}

bool Date::operator==(const Date& d) const{
  // si les dates sont strictement égales
  return (d.day   == this->day   &&
          d.month == this->month &&
          d.year  == this->year);
}

bool Date::operator!=(const Date& d) const{
  return !(*this == d);
}

bool Date::operator<=(const Date& d) const{
  return (*this < d || *this == d);
}

bool Date::operator>=(const Date& d) const{
  return *this > d || *this == d;
}

Date& Date::operator++(){
  // Cas trivial, on procède à l'incrément de 1
  if (this->day != nbDaysOfMonth())   {
    this->day += 1;
    // Si non on fait attention au passage à un nouveau mois/année
  }else{
    this->day = 1;
    // Si on est pas en décembre, on incrémente le mois
    if (this->month != (unsigned)MonthList::DECEMBER){
      this->month +=1;
      // Si non, on incrémente l'année et on passe à janvier
    }else{
      this->month  = (unsigned)MonthList::JANUARY;
      this->year  += 1;
    }
  }
  return *this;
}

Date Date::operator++(int){
  Date temp = *this;
  ++(*this);
  return temp;
}

Date& Date::operator--(){
  // cas trivial, on ne change pas de mois
  if (this->day != 1)
  {
    this->day -= 1;
    return *this;
  }
  // Si l'on ne doit pas changer d'année l'on décrémente le mois
  if (this->month != (unsigned)MonthList::JANUARY)   {
    this->month -= 1;
    // Sinon on décrémente l'année, on set le mois de décembre
  } else{
    this->year -= 1;
    this->month = (unsigned)MonthList::DECEMBER;
  }
  // dans les deux cas, on sera le dernier jour du mois affecté
  this->day = this->nbDaysOfMonth();

  return *this;
}

Date Date::operator--(int){
  Date temp = *this;
  --(*this);
  return temp;
}

Date::operator string() const{
  // Si la date est impossible
  if ( !correct )   {
    return "invalide";
  }

  stringstream ss;

  ss << setfill('0');
  ss << setw(2) << this->day   << '.';
  ss << setw(2) << this->month << '.';
  ss << setw(4) << this->year;

  return ss.str();
}




bool Date::isMonthCorrect() const{
  // si le mois est compris entre janvier et décembre
  return this->isMonthCorrect(month);
}

bool Date::isMonthCorrect(unsigned month) const {
  return MonthList(month) >= MonthList::JANUARY &&
         MonthList(month) <= MonthList::DECEMBER;
}

bool Date::isDayCorrect() const{
  return (day >= 1 and day <= this->nbDaysOfMonth());
}

unsigned Date::nbDaysOfMonth(unsigned month, unsigned year) const{

  if(!this->isMonthCorrect()){
    return 0;
  }

  switch(MonthList(month)){
    // uniquement pour FEVRIER
    case MonthList::FEBRUARY 	: return 28 + (unsigned)this->isLeapYear(year);
      // tous les mois à 30 jours
    case MonthList::APRIL  	  :
    case MonthList::JUNE 	  :
    case MonthList::SEPTEMBER :
    case MonthList::NOVEMBER  :  return 30;
    default                   :  return 31;
  }
}

unsigned Date::nbDaysOfMonth() const
{
  return nbDaysOfMonth(this->month, this->year);
}


