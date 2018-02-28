#pragma once
#include "OfferRepo.h"
#include "OperationStack.h"
#include <stdbool.h>
//This structure defines a new type, namely offerCtrl, that contains an offerRepo type pointer to a repository
typedef struct {
	offerRepo* repository;
	OperationsStack* undoStack;
	OperationsStack* redoStack;
}offerCtrl;


/*This function creates an offerCtrl type object
Input: repository - an offerRepo type pointer, that points to the repository which will be used in the controller
Output: controller - an offerCtrl type object*/
offerCtrl* createController(offerRepo* repository, OperationsStack* undoStack, OperationsStack* redoStack);

void destroyController(offerCtrl* controller);


//Getter for the offerRepo type object from the controller
offerRepo* getRepository(offerCtrl* controller);

/*This function gets all the elements that form an offer, creates it and then adds it to the repository by calling the
function addOffer.Also, it return 1 if the action was succesful,0 otherwise
Input: controller - an offerCtrl type pointer that points to the controller
type - a string representing the type of the offer (seaside/mountain/city break)
destination - a string representing the destination of the offer
departure - a date type object representing the date of the departure of the offer
price - a float representing theprice of the offer
Obs! an offer is uniquely identified by it's combination od departure date and destination
Output: 1 if the addition was succesful,0 otherwise*/
bool addOfferCtrl(offerCtrl* controller, char type[], char destination[], date departure, float price);


/*This function gets the unique characteristics of an offer,its departure date and destination, and removes
the offer that has those characteristics by calling the function deleteOffer.
Input: controller - an offerCtrl type pointer that points to the controller
destination - a string representing the destination of the offer
departure - a date type object representing the departure date of the offer
Output: 1 if the offer was deleted succesfuly,0 otherwise*/
bool deleteOfferCtrl(offerCtrl* controller, char destination[], date departure);


/*This function gets the unique characteristics of an offer,its departure date and destination, and the new price that
is wanted to replace the old price and updates the offer by calling the function updatePrice.
Input: controller - an offerCtrl type pointer that points to the controller
destination - a string representing the destination of the offer
departure - a date type object representing the departure date of the offer
newPrice - a float representing the new price
Output:  1 if the offer was updated succesfuly,0 otherwise*/
bool updatePriceCtrl(offerCtrl* controller, char destination[], date departure, float newPrice);



/*This function filteres the offers from the repository by calling the function filterByDestination.
Input: controller - an offerCtrl type pointer that points to the controller
repository - an offerRepo type pointer that points to the repository that needs to be filtered
destination - a string that is used as a criterion for the filterByDestination function
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDestinationCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, char destination[]);



/*This function filteres the offers from the repository by calling the function filterByType.
Input: controller - an offerCtrl type pointer that points to the controller
repository - an offerRepo type pointer that points to the repository that needs to be filtered
type - a string that is used as a criterion for the filterByType function
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByTypeCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, char type[]);

/*This function filteres the offers from the repository by calling the function filterByDate.
Input: controller - an offerCtrl type pointer that points to the controller
repository - an offerRepo type pointer that points to the repository that needs to be filtered
departure - a date type element that is used as a criterion for the filterByDate function
filteredRepository - an offerRepo type pointer representing the filtered repository*/
void filterByDateCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, date departure);

bool undo(offerCtrl* controller);

bool redo(offerCtrl* controller);
