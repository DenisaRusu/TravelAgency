#pragma once
#include "OfferController.h"
#include <stdbool.h>

//This structure defines the new type, namely UI, that contains an offerCtrl type pointer to a controller
typedef struct
{
	offerCtrl* controller;
} UI;

/*This function creates the object ui, having the type UI
Input: controller - an offerCtrl type pointer to a controller
Output: ui - the created UI type object*/
UI* createUI(offerCtrl* controller);
void destroyUI(UI* ui);

/*Validator for command.This function verifies if the command that the user enters is valid.
Input: ui - an UI type pointer
command - an integer representing the command that the user entered
Output: 1 if the command is valid,0 otherwise*/
bool commandValidator(UI* ui, int command);

/*Validator for type.This function verifies if the type that the user enters is valid,
namely if it is one of the following: seaside,mountain or city break.
Input: ui- an UI type pointer
type - a string representing the type that the user entered
Output: 1 if the type is valid,0 otherwise*/
bool typeValidator(UI* ui, char type[]);

/*Validator for departure date.This function verifies if the date that the user entered is a valid one.
The year must be greater of equal than 2016.The month can only be a number between 1 and 12.And for each month
the possible number of days is different:31,30 or 28.
Input: ui - an UI type pointer
departure - a date type object representing the date that the user entered
Output: 1 if the date is valid,0 otherwise*/
bool dateValidator(UI* ui, date departure);

//Prints the Menu with its options on the screen
void printMenu();

/*User Interface function for reading a date.This function also calls the dateValidator function,therefore
the date type object that is returned is valid.
Input: ui - an UI type pointer
Output: newDate - the valid date that was entered by the user*/
date readDate(UI* ui);


/*User Interface function for reading a type.This function alco calls the typeValidator function,therefore
the type that is returned is valid.
Intpu: ui- an UI type pointer
Output: newType - a valid type that was entered by the user */
char* readType(UI* ui);

/*User Interface function for reading an offer.This function alco calls the typeValidator function,therefore
the type of the offer that is returned is valid.
Intpu: ui- an UI type pointer
Output: a valid offer type object that was entered by the user */
offer readOffer(UI* ui);

/*This function gets an offer type object and adds it to the repository by calling the function addOfferCtrl
Input: ui - an UI type pointer
newOffer - an offer type object that is trying to be added to the repository
Output: 1 if the action was succesful,0 otherwise*/
bool addOfferUI(UI* ui, offer newOffer);

/*This function gets the unique characteristics of an offer, the destination and the date of departure, and
by calling the function deleteOfferCtrl removes the offer from the repository
Input: ui - an UI type pointer
destination - a string representing the destination of the offer
departure - a date type object representing the departure date of the offer
Ouput: 1 if the action was succesful,0 otherwise*/
bool deleteOfferUI(UI* ui, char destination[], date departure);

/*This function gets the unique characteristics of an offer, the destination and the date of departure, and the
new price that needs to replace the old price.And by calling the function updatePriceCtrl updates the price of the offer
Input: ui - an UI type pointer
destination - a string representing the destination of the offer
departure - a date type object representing the departure date of the offer
newPrice - a float representing the new price
Output: 1 if the action was succesful,0 otherwise*/
bool updatePriceUI(UI* ui, char destination[], date departure, float newPrice);

/*This function gets the destination as a criterion and filteres the repository by calling the function
filterByDestinationCtrl
Input: ui - an UI type pointer
repository - an offerRepo type pointer that points to the repository that needs to be filtered
destination - a string representing the criterion of the filter
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDestinationUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, char destination[]);

/*This function gets the type as a criterion and filteres the repository by calling the function filterByTypeCtrl
Input: ui - an UI type pointer
repository - an offerRepo type pointer that points to the repository that needs to be filtered
type - a string representing the criterion of the filter
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByTypeUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, char type[]);

/*This function gets the type as a criterion and filteres the repository by calling the function filterByDateCtrl
Input: ui - an UI type pointer
repository - an offerRepo type pointer that points to the repository that needs to be filtered
departure - a date type element representing the criterion of the filter
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDateUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, date departure);

//This function gets an offerRepo type pointer to a repository and prints it on the screen
void listAllOffers(UI* ui, offerRepo* repository);

void undoUI(UI* ui);

void redoUI(UI* ui);




//Function that solves the actions implied by the first command
void firstCommand(UI* ui);
//Function that solves the actions implied by the second command
void secondCommand(UI* ui);
//Function that solves the actions implied by the third command
void thirdCommand(UI* ui);
//Function that solves the actions implied by the forth command
void forthCommand(UI* ui);
//Function that solves the actions implied by the fifth command
void fifthCommand(UI* ui);
//Function that puts everything together and starts the UI
void startUI(UI* ui);
