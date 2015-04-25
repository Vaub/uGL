#include "uglwindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	a.setStyle(QStyleFactory::create("Fusion"));

	uGLWindow w;
	w.show();
	return a.exec();
}
