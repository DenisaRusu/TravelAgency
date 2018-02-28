#include "OfferRepo.h"
#include "UI.h"

int main() {
	offerRepo* repository = createRepo(10);
	OperationsStack* undoStack = createStack(10);
	OperationsStack* redoStack = createStack(10);
	offerCtrl* controller = createController(repository, undoStack, redoStack);
	UI* ui = createUI(controller);

	bool a = addOffer(repository, createOffer("seaside", "Hawaii", createDate(12, 03, 2020), 4500));
	bool b = addOffer(repository, createOffer("mountain", "Germany", createDate(21, 05, 2018), 7500));
	bool c = addOffer(repository, createOffer("seaside", "Maroc", createDate(17, 03, 2022), 3500));
	bool d = addOffer(repository, createOffer("mountain", "Maroc", createDate(19, 07, 2017), 2000));
	bool e = addOffer(repository, createOffer("city break", "Maroc", createDate(03, 12, 2017), 2500));
	bool f = addOffer(repository, createOffer("city break", "Himalaya", createDate(15, 02, 2021), 9500));
	//--------------Tests------------------
	testOfferRepoDynamic();
	//-------------------------------------

	startUI(ui);
	destroy(repository);
	destroyStack(undoStack);
	destroyStack(redoStack);
	destroyController(controller);
	destroyUI(ui);


	_CrtDumpMemoryLeaks();
	return 0;
}