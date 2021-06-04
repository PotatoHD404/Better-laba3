#pragma once

#include <QWidget>
#include "ui_TestWindow.h"

class TestWindow : public QWidget
{
	friend class MainWindow;

	Q_OBJECT

public:
	TestWindow(QWidget *parent = Q_NULLPTR);
	~TestWindow();

private:
	Ui::TestWindow ui;
};
