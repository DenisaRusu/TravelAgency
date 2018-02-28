#pragma once
#include <stdio.h>
#include <stdbool.h>

//This structure defines a new type, namely "date", which consists of 3 integers that represent the day, the month and the year.
typedef struct {
	int day;
	int month;
	int year;
}date;

/*This structure defines the caracteristic type of the program which is the Offer. Each offer consists in:
a char type (which can be seaside, mountain or citytbreak), a char destination, a float price, and an item defined previously
as an class type date.*/
typedef struct {
	char type[50];
	char destination[50];
	date departure;
	float price;
}offer;


/*This function creates the object date.
Input: day- an integer representing the day
month- an integer representing the month
year- an integer representing the year
Output: d- the object of type date that has all the integers set*/
date createDate(int day, int month, int year);
//Getter for the day of the date
int getDay(date* d);
//Getter for the month of the date
int getMonth(date* d);
//Getter for the year of the date
int getYear(date* d);


/*This function creates the object offer.
Input: type- a char representing the type.Can only be: seaside, mountain or city break
destination- a char representing the destination for the holiday offer
departure- a date type object, representing the date of the departure
price- a float representing the price
Output: o- the created object of type offer
Observation! An offer is uniquely identified by the combination of the departure(date) and destination(char) */
offer createOffer(char type[], char destination[], date departure, float price);

/*This function returns the type of the offer o .It can only be: seaside, mountain or city break*/
char* getType(offer* o);

/*This function returns the destination of the offer o.*/
char* getDestination(offer* o);

/*This function returns the departure date of the offer o.*/
date getDeparture(offer* o);

/*This function returns the price of the offer o.*/
float getPrice(offer* o);



/*This function sets the object offer to look in a certain way. Here, the date will be seen as dd/mm/yyyy*/
void toString(offer o, char str[]);



#pragma once
