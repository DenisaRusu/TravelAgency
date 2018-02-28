#include "OfferController.h"
#include <string.h>



offerCtrl* createController(offerRepo* repository, OperationsStack* undoStack, OperationsStack* redoStack) {
	offerCtrl* controller = (offerCtrl*)malloc(sizeof(offerCtrl));
	controller->repository = repository;
	controller->undoStack = undoStack;
	controller->redoStack = redoStack;
	return controller;
}
void destroyController(offerCtrl* controller) {
	free(controller);

}


offerRepo* getRepository(offerCtrl* controller) {
	return controller->repository;
}

bool addOfferCtrl(offerCtrl* controller, char type[], char destination[], int day, int month, int year, float price) {
	offer newOffer = createOffer(type, destination, createDate(day, month, year), price);
	bool check = addOffer(controller->repository, newOffer);
	if (check == 1) {
		operation o = createOperation(newOffer, "add");
		if (controller->undoStack->length == controller->undoStack->capacity)
			resizeStack(controller->undoStack);
		if (controller->redoStack->length == controller->redoStack->capacity)
			resizeStack(controller->redoStack);
		push(controller->undoStack, o);
		push(controller->redoStack, o);
	}
	return check;
}

bool deleteOfferCtrl(offerCtrl* controller, char destination[], date departure) {
	bool check = deleteOffer(controller->repository, destination, departure);
	if (check == 1) {
		operation o = createOperation(getOfferOnPos(controller->repository, findOffer(controller->repository, destination, departure)), "delete");
		if (controller->undoStack->length == controller->undoStack->capacity)
			resizeStack(controller->undoStack);
		if (controller->redoStack->length == controller->redoStack->capacity)
			resizeStack(controller->redoStack);
		push(controller->undoStack, o);
		push(controller->redoStack, o);
	}

	return check;

}

bool updatePriceCtrl(offerCtrl* controller, char destination[], date departure, float newPrice) {
	offer oldOffer = getOfferOnPos(controller->repository, findOffer(controller->repository, destination, departure));
	bool check = updatePrice(controller->repository, destination, departure, newPrice);
	offer newOffer = getOfferOnPos(controller->repository, findOffer(controller->repository, destination, departure));
	if (check == 1) {
		operation oUndo = createOperation(oldOffer, "update");
		operation oRedo = createOperation(newOffer, "update");
		if (controller->undoStack->length == controller->undoStack->capacity)
			resizeStack(controller->undoStack);
		if (controller->redoStack->length == controller->redoStack->capacity)
			resizeStack(controller->redoStack);
		push(controller->undoStack, oUndo);
		push(controller->redoStack, oRedo);
	}
	return check;
}



void filterByDestinationCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, char destination[]) {
	filterByDestination(repository, filteredRepository, destination);
}

void filterByTypeCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, char type[]) {
	filterByType(repository, filteredRepository, type);
}

void filterByDateCtrl(offerCtrl* controller, offerRepo*repository, offerRepo* filteredRepository, date departure) {
	filterByDate(repository, filteredRepository, departure);
}

bool undo(offerCtrl* controller) {
	operation* o = pop(controller->undoStack);
	char* type = getOperationType(o);
	if (strcmp(type, "add") == 0) {
		offer toDelete = getOfferBackup(o);
		bool check = deleteOffer(controller->repository, toDelete.destination, toDelete.departure);
		//if check==1 => undo succesful
		return check;
	}
	else if (strcmp(type, "delete") == 0) {
		offer toAdd = getOfferBackup(o);
		bool check = addOffer(controller->repository, toAdd);
		//if check==1 => undo succesful
		return check;
	}
	else if (strcmp(type, "update") == 0) {
		offer oldOffer = getOfferBackup(o);
		bool check = updatePrice(controller->repository, oldOffer.destination, oldOffer.departure, oldOffer.price);
		//if check==1 => undo succesful
		return check;
	}
	return 0;
}

bool redo(offerCtrl* controller) {
	operation* o = pop(controller->redoStack);
	char* type = getOperationType(o);
	if (strcmp(type, "add") == 0) {
		offer toAdd = getOfferBackup(o);
		bool check = addOffer(controller->repository, toAdd);
		//if check==1 => undo succesful
		return check;

	}
	else if (strcmp(type, "delete") == 0) {
		offer toDelete = getOfferBackup(o);
		bool check = deleteOffer(controller->repository, toDelete.destination, toDelete.departure);
		//if check==1 => undo succesful
		return check;

	}
	else if (strcmp(type, "update") == 0) {
		offer newOffer = getOfferBackup(o);
		bool check = updatePrice(controller->repository, newOffer.destination, newOffer.departure, newOffer.price);
		//if check==1 => undo succesful
		return check;
	}
	return 0;
}

