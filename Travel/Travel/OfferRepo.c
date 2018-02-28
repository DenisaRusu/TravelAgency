#include "OfferRepo.h"
#include <stddef.h>
#include <string.h>
#include <assert.h>


offerRepo* createRepo(int capacity) {
	offerRepo* repository = (offerRepo*)malloc(sizeof(offerRepo));
	if (repository == NULL)
		return NULL;
	repository->capacity = capacity;
	repository->length = 0;
	//allocate space for offers
	repository->offers = (offer*)malloc(capacity*sizeof(offer));
	if (repository->offers == NULL)
		return NULL;
	return repository;
}

void destroy(offerRepo* repository) {
	//free the space allocated for offers
	free(repository->offers);
	//free the space allocated for the whole dynamic structure of the repository
	free(repository);
}
void resize(offerRepo* repository) {
	repository->capacity *= 2;
	repository->offers = (offer*)realloc(repository->offers, repository->capacity*sizeof(offer));
}


int getLength(offerRepo* repository) {
	return repository->length;
}

int findOffer(offerRepo* repository, char destination[], date departure) {
	offer* o = NULL;
	for (int i = 0; i < repository->length; i++) {
		if (strcmp(repository->offers[i].destination, destination) == 0 && repository->offers[i].departure.day == departure.day && repository->offers[i].departure.month == departure.month && repository->offers[i].departure.year == departure.year)
			return i;
	}
	return -1;
}

bool addOffer(offerRepo* repository, offer o) {
	if (repository->length == repository->capacity)
		resize(repository);
	if (findOffer(repository, o.destination, o.departure) != -1)
		return 0;
	repository->offers[repository->length++] = o;
	return 1;
}

bool deleteOffer(offerRepo* repository, char destination[], date departure) {
	int pos = findOffer(repository, destination, departure);
	if (pos == -1)
		return 0;
	for (int i = pos; i < repository->length - 1; i++)
		repository->offers[i] = repository->offers[i + 1];
	repository->length--;
	return 1;
}

bool updatePrice(offerRepo* repository, char destination[], date departure, float newPrice) {
	int pos = findOffer(repository, destination, departure);
	if (pos == -1)
		return 0;
	repository->offers[pos].price = newPrice;
	return 1;
}

offer getOfferOnPos(offerRepo* repository, int pos)
{
	if (pos < 0 || pos >= repository->length)
		return createOffer("", "", createDate(-1, -1, -1), -1);
	return repository->offers[pos];
}

void sortByPrice(offerRepo* repository) {
	int i, j;
	offer aux;
	for (i = 0; i < repository->length - 1; i++)
		for (j = i + 1; j < getLength(repository); j++)
			if (repository->offers[j].price<repository->offers[i].price) {
				aux = repository->offers[i];
				repository->offers[i] = repository->offers[j];
				repository->offers[j] = aux;
			}
}


void filterByDestination(offerRepo* repository, offerRepo* filteredRepository, char destination[]) {
	int i, j;
	for (i = j = 0; i < repository->length; i++) {
		if (strstr(repository->offers[i].destination, destination) != NULL) {
			filteredRepository->offers[j] = repository->offers[i];
			j++;
		}
	}
	filteredRepository->length = j;
}


void filterByType(offerRepo* repository, offerRepo* filteredRepository, char type[]) {
	int i, j;
	for (i = j = 0; i < repository->length; i++) {
		if (strcmp(repository->offers[i].type, type) == 0) {
			filteredRepository->offers[j] = repository->offers[i];
			j++;
		}
	}
	filteredRepository->length = j;

}

bool compareDates(date compare, date criterion) {
	if (compare.year > criterion.year)
		return 1;
	else if (compare.year == criterion.year && compare.month > criterion.month)
		return 1;
	else if (compare.year == criterion.year && compare.month == criterion.month && compare.day >= criterion.day)
		return 1;
	else
		return 0;
}



void filterByDate(offerRepo* repository, offerRepo* filteredRepository, date departure) {
	int i, j;
	for (i = j = 0; i < getLength(repository); i++) {
		if (compareDates(repository->offers[i].departure, departure) != 0) {
			filteredRepository->offers[j] = repository->offers[i];
			j++;
		}
	}
	filteredRepository->length = j;

}


//Test for dynamic allocation and adding and reallocationg

void testOfferRepoDynamic() {
	offerRepo* repository = createRepo(2);
	if (repository == NULL)
		assert(0);
	assert(repository->capacity == 2);
	assert(repository->length == 0);

	offer first = createOffer("seaside", "Mamaia", createDate(2, 9, 2017), 500);
	addOffer(repository, first);
	assert(repository->length == 1);

	offer second = createOffer("mountain", "Italy", createDate(12, 12, 2018), 7000);
	addOffer(repository, second);
	assert(repository->length == 2);

	offer third = createOffer("mountain", "Alpi", createDate(15, 6, 2016), 450);
	addOffer(repository, third);
	assert(repository->length == 3);
	assert(repository->capacity == 4);

	offerRepo* filteredRepository = createRepo(repository->capacity);
	assert(filteredRepository->capacity == 4);

	filterByType(repository, filteredRepository, "mountain");
	assert(filteredRepository->length == 2);

	filterByDate(repository, filteredRepository, createDate(12, 12, 2018));
	assert(filteredRepository->length == 1);



	destroy(repository);
	destroy(filteredRepository);
}