#pragma once

#include <QMainWindow>
#include "ToolBar.h"
#include "Ulohy/TabulkaUloh.h"

class MainWindow : public QMainWindow {
//	Q_OBJECT
public:
	MainWindow(SortedSequenceTable<int, UzemnaJednotka*>*, SortedSequenceTable<int, PolitickySubjekt*>*, QWidget* parent = nullptr);
	virtual ~MainWindow();

	TableWidget* getTable() const;

	void nastavPaletu();

protected:
	void keyPressEvent(QKeyEvent* event) override;

//signals:
//	void vyvolanaAkcia();

public slots:
	void reaguj(int);

private:
	int uloha;
	TabulkaUloh** ulohy;
	ToolBar* bar;
	SortedSequenceTable<int, UzemnaJednotka*>* jednotky;
	SortedSequenceTable<int, PolitickySubjekt*>* subjekty;
};
