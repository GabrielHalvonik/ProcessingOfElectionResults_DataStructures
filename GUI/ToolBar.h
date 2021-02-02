#pragma once

#include <QToolBar>
#include <QObject>
#include <QButtonGroup>

class ToolBar : public QToolBar {
	Q_OBJECT
public:
	ToolBar(QWidget* parent = nullptr);
	virtual ~ToolBar();

signals:
	void stlacene(int);

private:
	QButtonGroup* btnGroup;
};

