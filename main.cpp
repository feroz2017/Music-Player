#include "mainwindow.h"
#include <QApplication>
#include<QIcon>
int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	MainWindow w;

    w.setWindowIcon(QIcon(":/icons/untitled.png"));
    w.setWindowTitle("Black Player");
	w.show();

	return a.exec();
}
