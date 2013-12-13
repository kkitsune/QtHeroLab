#include <qtquick2controlsapplicationviewer.h>
#include <QGuiApplication>
#include <QtQml>

int main(int argc, char *argv[])
{
	Application app(argc, argv);
	QtQuick2ControlsApplicationViewer viewer;

	viewer.setMainQmlFile(QStringLiteral("qml/main.qml"));
	viewer.show();

    return app.exec();
}
