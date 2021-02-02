#include <QApplication>
#include <QDebug>
#include <iostream>
#include "Table/SortedSequenceTable.h"
#include "Table/UnsortedSequenceTable.h"
#include "Table/BinarySearchTree.h"
#include "Table/Treap.h"

#include "App/DataLoading.h"
#include "App/DataLoader.h"
#include "App/Kriterium.h"
#include "App/Filter.h"
#include "Table/Sorting/SelectSort.h"
#include "Table/Sorting/BubbleSort.h"
#include "Table/Sorting/MergeSort.h"
#include "Table/Sorting/QuickSort.h"
#include "Table/Sorting/Shuffle.h"
#include "List/ArrayList.h"

#include "GUI/MainWindow.h"

#include <QToolBar>
#include <QToolButton>
#include <QButtonGroup>
#include "GUI/ToolBar.h"



using namespace	Structures;

//class TimeTest {
//public:
//	TimeTest() : start(std::chrono::high_resolution_clock::now()) {}
//	~TimeTest() {
//		this->stop = std::chrono::high_resolution_clock::now();
//		std::cout << (stop - start).count() << std::endl;
//	}
//private:
//	std::chrono::time_point<std::chrono::high_resolution_clock> start, stop;
//};
//using Typ = std::variant<UzemnaJednotka, PolitickySubjekt>;


int main(int argc, char *argv[]) {

	SortedSequenceTable<int, UzemnaJednotka*> jednotky;
	SortedSequenceTable<int, PolitickySubjekt*> subjekty;


	UzemnaJednotkaDataLoading uLoad(&jednotky);
	uLoad.load();

	VysledkyHlasovaniaOkrskovDataLoading vLoad(&jednotky);
	vLoad.load();

	PolitickySubjektDataLoading psLoad(&jednotky, &subjekty);
	psLoad.load();

	HlasyPrePolitickeSubjektyLoading oLoad(&jednotky, &subjekty);
	oLoad.load();

	QApplication app(argc, argv);

	MainWindow mw(&jednotky, &subjekty);
	mw.showFullScreen();


	return app.exec();



	////	1


//	std::wstring str = L"Nov";
//	FilterValue<UzemnaJednotka, std::wstring> f1a(kNazovUJ, str);
//	FilterRange<UzemnaJednotka, int> f1b(kVoliciUJ, 1000, 5000);
//	FilterRange<UzemnaJednotka, double> f1c(kUcastUJ, 70.0, 80.0);

//	for (TableItem<int, UzemnaJednotka*>* temp : f1a.vyfiltruj(jednotky)) {
//		ExplicitQueue<UzemnaJednotka*> stack = temp->accessData()->getVyssieUzemia();
//		while (!stack.isEmpty()) {
//			std::wcout << kNazovUJ(stack.pop()) << " -> ";
//		}
//		std::wcout << kNazovUJ(temp->accessData()) << ", " << kZucastneniUJ(temp->accessData()) << "/" << kVoliciUJ(temp->accessData()) << "(";
//		std::wcout << kUcastUJ(temp->accessData()) << ") " << kPodielPlatnychUJ(temp->accessData()) << std::endl;
//	}




//	////	3


//	FilterRange<UzemnaJednotka, int> f1(KriteriumUzemnaJednotkaVolici(), 1000, 10000);
//	FilterRange<UzemnaJednotka, double> f2(KriteriumUzemnaJednotkaUcast(), 70.0, 100.0);
//	FilterRange<UzemnaJednotka, int> f3(KriteriumUzemnaJednotkaZucastneniVolici(), 600, 1000);
//	FilterValue<UzemnaJednotka, TypUzemnejJednotky> f4(KriteriumUzemnaJednotkaTyp(), Okres);

//	Filter<UzemnaJednotka>&& fx = f4 && f1 && f3 || f1 && !f2;





	return 0;
}
