#include "UI.h"
#include <stdio.h>
#include <stdbool.h>

UI* createUI(offerCtrl* controller)
{
	UI* ui = (UI*)malloc(sizeof(UI));
	ui->controller = controller;

	return ui;
}
void destroyUI(UI* ui) {
	free(ui);
}
// validators-----------------------------------

bool commandValidator(UI* ui, int command) {
	if (command >= 0 && command <= 7)
		return 1;
	return 0;
}
bool typeValidator(UI* ui, char type[]) {
	if (strcmp(type, "seaside") != 0 && strcmp(type, "mountain") != 0 && strcmp(type, "city break") != 0)
		return 0;
	return 1;
}
bool dateValidator(UI* ui, date departure) {
	if (departure.year >= 2016) {
		if (departure.month == 1 || departure.month == 3 || departure.month == 5 || departure.month == 7 || departure.month == 8 || departure.month == 10 || departure.month == 12) {
			if (departure.day >= 1 && departure.day <= 31)
				return 1;
			else
				return 0;
		}
		else if (departure.month == 4 || departure.month == 6 || departure.month == 9 || departure.month == 11) {
			if (departure.day >= 1 && departure.day <= 30)
				return 1;
			else
				return 0;
		}
		else if (departure.month == 2) {
			if (departure.day >= 1 && departure.day <= 28)
				return 1;
			else
				return 0;
		}
	}
	else
		return 0;
}
//-----------------------------------------
//print menu------------------------------------------
void printMenu() {
	printf("\nMain Menu:");
	printf("\n1. Add an offer.");
	printf("\n2. Delete offer.");
	printf("\n3. Update offer price.");
	printf("\n4. List offers filtered by destination and sorted ascending by price.");
	printf("\n5. List offers filtered by type and following a given date.");
	printf("\n6. UNDO.");
	printf("\n7. REDO.");
	printf("\n0. EXIT.");
}

//-------------------------------------------------

//read stuff-----------------------------------------------
date readDate(UI* ui) {
	int day, month, year, check = 0;
	date newDate;
	while (check == 0) {
		printf("\nEnter the day: ");
		scanf("%d", &day);
		printf("\nEnter the month: ");
		scanf("%d", &month);
		printf("\nEnter year: ");
		scanf("%d", &year);
		newDate = createDate(day, month, year);
		if (dateValidator(ui, newDate))
			check = 1;
		else
			printf("\nInvalid date! Try again.");
	}
	return newDate;
}

char* readType(UI* ui) {
	char* newType = (char*)malloc(50 * sizeof(char));
	int check = 0;
	while (check == 0) {
		printf("\nEnter the type (seaside/mountain/city break): ");
		scanf("%s", newType);
		if (typeValidator(ui, newType))
			check = 1;
		else
			printf("\nInvalid type! Try again.");
	}
	return newType;
}

offer readOffer(UI* ui) {
	char destination[50];
	date departure;
	float price;
	printf("\nTo enter an offer please:");
	char* type = readType(ui);
	printf("\nEnter the destination: ");
	scanf("%s", &destination);
	departure = readDate(ui);
	printf("\nEnter the price: ");
	scanf("%f", &price);
	return createOffer(type, destination, departure, price);
}
//---------------------------------------------
//the functions needed for actions---------------------------
bool addOfferUI(UI* ui, offer newOffer) {
	int check = addOfferCtrl(ui->controller, newOffer.type, newOffer.destination, newOffer.departure, newOffer.price);
	if (check == 0)
		return 0;
	return 1;
}

bool deleteOfferUI(UI* ui, char destination[], date departure) {
	int check = deleteOfferCtrl(ui->controller, destination, departure);
	if (check == 0)
		return 0;
	return 1;
}

bool updatePriceUI(UI* ui, char destination[], date departure, float newPrice) {
	int check = updatePriceCtrl(ui->controller, destination, departure, newPrice);
	if (check == 0)
		return 0;
	return 1;
}

void filterByDestinationUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, char destination[]) {
	filterByDestinationCtrl(ui->controller, repository, filteredRepository, destination);
}
void filterByTypeUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, char type[]) {
	filterByTypeCtrl(ui->controller, repository, filteredRepository, type);

}

void filterByDateUI(UI* ui, offerRepo* repository, offerRepo* filteredRepository, date departure) {
	filterByDateCtrl(ui->controller, repository, filteredRepository, departure);
}


void listAllOffers(UI* ui, offerRepo* repository) {
	if (getLength(repository) == 0)
		printf("\nThere's no stored offers!");
	else {
		for (int i = 0; i < getLength(repository); i++) {
			char str[200];
			toString(getOfferOnPos(repository, i), str);
			printf("\n%s", str);
		}
	}

}


//----------------------------------------------------------------

//the commands----------------------------------------------------
void firstCommand(UI* ui) {
	printf("\nYou selected the first command.");
	offer newOffer = readOffer(ui);
	if (addOfferUI(ui, newOffer) == 0)
		printf("\nOffer already exists! Try again.");
	else
		printf("\nOffer was added!");
}

void secondCommand(UI* ui) {
	printf("\nYou selected the second command.");
	printf("\nEnter the destination of the offer that you wish to delete: ");
	char destination[50];
	scanf("%s", &destination);
	printf("\nNow enter the date of the offer that you wish to delete:");
	date departure = readDate(ui);
	if (deleteOfferUI(ui, destination, departure) == 0)
		printf("\nThe offer doesn't exist! Try again.");
	else
		printf("\nThe offer was deleted!");
}

void thirdCommand(UI* ui) {
	printf("\nYou selected the third command.");
	printf("\nEnter the destination of the offer that you wish to update the price: ");
	char destination[50];
	scanf("%s", &destination);
	printf("\nNow enter the date of the offer that you wish to update the price:");
	date departure = readDate(ui);
	printf("\nNow enter the new price: ");
	float newPrice;
	scanf("%f", &newPrice);
	if (updatePriceUI(ui, destination, departure, newPrice) == 0)
		printf("\nThe offer doesn't exist! Try again.");
	else
		printf("\nThe price was updated!");
}

void forthCommand(UI* ui) {
	printf("\nYou selected the forth command.");
	printf("\nEnter the destination by which you want to filter the offers(* for all): ");
	char destination[50];
	scanf("%s", &destination);
	printf("\nThe wanted filtered list (sorted ascending) is: ");
	if (strcmp(destination, "*") == 0)
	{
		offerRepo* filteredRepository = createRepo(ui->controller->repository->length);
		filteredRepository = getRepository(ui->controller);
		sortByPrice(filteredRepository);
		listAllOffers(ui, filteredRepository);
		destroy(filteredRepository);
	}
	else
	{
		offerRepo* filteredRepository = createRepo(ui->controller->repository->length);
		filterByDestinationUI(ui, getRepository(ui->controller), filteredRepository, destination);
		sortByPrice(filteredRepository);
		listAllOffers(ui, filteredRepository);
		destroy(filteredRepository);
	}
}

void fifthCommand(UI* ui) {
	printf("\nYou selected the fifth command.");
	printf("\nEnter the type by which you want to filter the offers: ");
	char* type = readType(ui);
	printf("\nEnter the date starting from which you want to filter the offers: ");
	date departure = readDate(ui);
	printf("\nThe wanted filtered list is: ");

	offerRepo* filteredRepository = createRepo(ui->controller->repository->length);
	offerRepo* filteredRepository2 = createRepo(ui->controller->repository->length);
	filterByTypeUI(ui, ui->controller->repository, filteredRepository, type);
	filterByDateUI(ui, filteredRepository, filteredRepository2, departure);
	destroy(filteredRepository);
	listAllOffers(ui, filteredRepository2);
	destroy(filteredRepository2);

}

void undoUI(UI* ui) {
	bool check = undo(ui->controller);
	if (check == 1)
		printf("\nUndo was succesful!");
	else
		printf("\nUndo was unavailable!");
}

void redoUI(UI* ui) {
	bool check = redo(ui->controller);
	if (check == 1)
		printf("\nRedo was succesful!");
	else
		printf("\nRedo was unavailable!");
}
//---------------------------------------------------


void startUI(UI* ui) {
	bool stop = false;
	while (!stop) {
		printf("\nOffers:\n");
		listAllOffers(ui, ui->controller->repository);
		printMenu();
		int command;
		printf("\nEnter command: ");
		scanf("%d", &command);
		if (commandValidator(ui, command)) {
			if (command == 1)
				firstCommand(ui);
			else if (command == 2)
				secondCommand(ui);
			else if (command == 3)
				thirdCommand(ui);
			else if (command == 4)
				forthCommand(ui);
			else if (command == 5)
				fifthCommand(ui);
			else if (command == 6)
				undoUI(ui);
			else if (command == 7)
				redoUI(ui);
			else if (command == 0) {
				printf("\nProgram is ending...");
				stop = true;
			}
		}
		else
			printf("\nInvalid command!");

	}
}