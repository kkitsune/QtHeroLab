#include <qtquick2applicationviewer.h>
#include <QGuiApplication>
#include <QtQml>

#include "filelister.h"
#include "portfolio.h"
#include "platform.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
	Platform p(viewer.engine());
	Q_UNUSED(p);

	qmlRegisterType<Portfolio>("HeroLab", 1, 0, "Portfolio");
	qmlRegisterType<FileLister>("HeroLab", 1, 0, "FileLister");

    viewer.setMainQmlFile(QStringLiteral("qml/QtHeroLab/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
