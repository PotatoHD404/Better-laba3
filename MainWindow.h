#pragma once

#include <QtWidgets/QWidget>
#include "ui_MainWindow.h"
#include"QtCharts/qchart.h"
#include"QtCharts/qchartview.h"
#include"QtCharts/qlineseries.h"
#include"QtCharts/qvalueaxis.h"
#include"TestWindow.h"

using namespace QtCharts;

class MainWindow : public QWidget
{
	Q_OBJECT

public:
	MainWindow(QWidget *parent = Q_NULLPTR);
public slots:
	void StartTest();
private:
	Ui::MainWindowClass ui;
	QChart chrt;
	QValueAxis axisX, axisY;
	QLineSeries series_add, series_has;
	TestWindow test_window;
};
