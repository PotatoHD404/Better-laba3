#include "MainWindow.h"
#include "Test.h"
#include"BinarySearchTree.h"
#include "Set.h"
#include<functional>
#include<complex>
#include<chrono>
//#include"vld.h"

MainWindow::MainWindow(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	ui.widget1->setChart(&chrt);
	chrt.setTitle("Graph");

	size_t max_count = 1000000;

	axisX.setRange(0, max_count - max_count / 100);
	axisX.setTickCount(10);
	axisX.setLabelFormat("%g");
	axisX.setTitleText("N");

	axisY.setRange(0, 10000);
	axisY.setTickCount(11);
	axisY.setLabelFormat("%g");
	axisY.setTitleText("t, ns");

	Set<int> set;
	BinarySearchTree<int> int_bst;
	for (size_t j = 0; j < max_count; j++)
	{
		if (j % (max_count / 100) == 0)
		{
			auto start = std::chrono::system_clock::now();
			set.Add(j);
			auto end = std::chrono::system_clock::now();
			double curr_time_add = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			start = std::chrono::system_clock::now();
			set.Has(j);
			end = std::chrono::system_clock::now();
			double curr_time_has = std::chrono::duration_cast<std::chrono::nanoseconds>(end - start).count();
			series_add.append(j, curr_time_add);
			series_has.append(j, curr_time_has);
		}
		else
			set.Add(j);
	}

	series_add.setName("Add");
	series_has.setName("Set");

	chrt.addSeries(&series_add);
	chrt.setAxisX(&axisX, &series_add);
	chrt.setAxisY(&axisY, &series_add);
	chrt.addSeries(&series_has);
	chrt.setAxisX(&axisX, &series_has);
	chrt.setAxisY(&axisY, &series_has);

	QObject::connect(ui.TestButton, SIGNAL(clicked()), this, SLOT(StartTest()));
}

void MainWindow::StartTest()
{
	test_window.show();
	test_window.ui.TestAddLable->setText(TestAdd() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
	test_window.ui.TestHasLable->setText(TestHas() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
	test_window.ui.TestDeleteLable->setText(TestDelete() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
	test_window.ui.TestUnionLable->setText(TestUnion() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
	test_window.ui.TestIntersectionLable->setText(TestIntersection() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
	test_window.ui.TestRelativeComplementLable->setText(TestRelativeComplement() ? "<font color=\"green\">Success</font>" : "<font color=\"red\">Failure</font>");
}
