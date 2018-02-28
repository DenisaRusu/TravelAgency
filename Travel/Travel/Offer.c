#include "Offer.h"
#include <stdio.h>
#include <string.h>


date createDate(int day, int month, int year) {
	date d;
	d.day = day;
	d.month = month;
	d.year = year;
	return d;
}
int getDay(date* d) {
	return d->day;
}
int getMonth(date* d) {
	return d->month;
}
int getYear(date* d) {
	return d->year;
}


offer createOffer(char type[], char destination[], date departure, float price) {
	offer o;
	strcpy(o.type, type);
	strcpy(o.destination, destination);
	o.price = price;
	o.departure = departure;
	return o;
}

char* getType(offer* o) {
	return o->type;
}
char* getDestination(offer* o) {
	return o->destination;
}

float getPrice(offer* o) {
	return o->price;
}

date getDeparture(offer* o) {
	return o->departure;
}



void toString(offer o, char str[]) {
	sprintf(str, "The offer of type %s has the destination %s.\nIts departure date is %d/%d/%d.\nIt has the price of: %f.\n", o.type, o.destination, o.departure.day, o.departure.month, o.departure.year, o.price);
}