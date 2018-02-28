#pragma once
#include "Offer.h"
#include <stdbool.h>
/*This structure defines a new type, namely offerRepo, that represents the repository for offers.
It contains an array of objects of type offer and an integer representing the physical length of the array.*/
typedef struct {
	offer* offers;
	int length;
	int capacity;

}offerRepo;

/* This function creates a new object of type offerRepo and gives it the length 0.*/
offerRepo* createRepo(int capacity);

//This function frees the whole dynamic repository
void destroy(offerRepo* repository);

//This function doubles the size of the capacity and reallocs the memory for the offers
void resize(offerRepo* repository);

/*This functions is a getter for the length of the repository.
Input: repository - a pointer to an offerRepo object that points to the repository of which we want to get the length
Output: length - an integer that represents the length of the repository*/
int getLength(offerRepo* repository);

/*This function finds the offer that has the unique combination of the destination and the departure date given.
And returns its position in the repository or -1 if the offer wasn't found.
Input: repository - a pointer to an offerRepo object that points to the repository in which we search for the offer
destination - a char that represents the destination of the offer that we want to find
departure - a date type object that represents the date of departure of the offer that we're searching for
Output: pos - representing the position of the searched offer in the repository
-1 - an integer that showa us that the offer could not be found in the repository*/
int findOffer(offerRepo* repository, char destination[], date departure);


/*This function adds an offer type object to the repository and returns 1 if the addition was succesful,0 otherwise.
Input: repository - an offerRepo type pointer that points to the repository in which we want to add the new offer
o - an offer type object that represents the offer which needs to be added to the repository
Output: 1 - if the addition was made without any problem,0 otherwise*/
bool addOffer(offerRepo* repository, offer o);


/*This function deletes an offer type object from the repository and returns 1 if the action was succestul,0 otherwise
Input: repository - an offerRepo type pointer that points the the repository from which we want to delete an offer
destination - a char that represents the destination of the offer that we want to delete
departure - a date type object that represents the date of departure of the offer that we want to delete
Output: 1 - if the offer was deleted succesfuly,0 otherwise*/
bool deleteOffer(offerRepo* repository, char destination[], date departure);

/*This function updates the price of an offer and returns 1 if the action was succestul,0 otherwise
Input: repository - an offerRepo type pointer that points the the repository in which we find the offer
destination - a char that represents the destination of the offer that we want to update the price to
departure - a date type object that represents the date of departure of the offer that we want to update the price to
newPrice - a float that represents the new price that needs to replace the old one
Output: 1 - if the offer's price update was succesful,0 otherwise*/
bool updatePrice(offerRepo* repository, char destination[], date departure, float newprice);

/*This function finds and returns the offer type object on the position pos.
Input: repository - an offerRepo type pointer that points the the repository from which we need to get the offer
pos - an integer representing the position on which we'll find the offer
Outpu: an offer type object */
offer getOfferOnPos(offerRepo* repository, int pos);

/*This function sorts an offerRepo type object, which is a repository, ascending by the price of each offer type element.
Input: repository - an offerRepo type pointer that points the the repository which we need to sort*/
void sortByPrice(offerRepo* repository);

/*This function filteres the offerRepo type object, namely the repository, by the destination of each offer type element.
Also, creates a new offerRepo type object, namely filteredRepository, that will contain all the offer type elements from
the given repository.These offer type elements need to have their destination string equal to the given destination string
or their destination string should contain as a substring the given destination string
Input: repository - an offerRepo type pointer that points the the repository from which we'll filter the offer type
elements and from which we'll copy the elements that respect the filter
destination - a char type element that represents the criterion on which we'll filter the given repository
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDestination(offerRepo* repository, offerRepo* filteredRepository, char destination[]);

/*This function filteres the offerRepo type object, namely the repository, by the type of each offer type element.
Also,creates a new offerRepo type object, namely filteredRepository, that will contain all the offer type elements from
the given repository.These offer type elements need to have their type string equal to the given type string.
Input: repository - an offerRepo type pointer that points the the repository from which we'll filter the offer type
elements and from which we'll copy the elements that respect the filter
type - a char type element that represents the criterion on which we'll filter the given repository
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByType(offerRepo* repository, offerRepo* filteredRepository, char type[]);

/*This function compares two departure dates of two given offers. The criterion is that the comparedOffer needs to have
the departure date equal to the criterionOffer or needs to be greater, namely it need to follow the criterionOffer's date.
Input: comparedOffer - an offer type element that needs to be compared by date
criterion - a date type element used as a criterion to compare the departure date of the given offer
Output: 1 if the criterion is respected, 0 otherwise*/
bool compareDates(date compare, date criterion);

/*This function filteres the offerRepo type object, namely the repository, by the departure date of each offer type element.
Also,creates a new offerRepo type object, namely filteredRepository, that will contain all the offer type elements from
the given repository.These offer type elements need to have their departure date following the given criterion date.
Input: repository - an offerRepo type pointer that points the the repository from which we'll filter the offer type
elements and from which we'll copy the elements that respect the filter
departure - a date type element that represents the criterion on which we'll filter the given repository
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDate(offerRepo* repository, offerRepo* filteredRepository, date departure);