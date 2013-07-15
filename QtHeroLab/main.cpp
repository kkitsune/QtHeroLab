#include <QGuiApplication>
#include <QtQml>
#include "qtquick2applicationviewer.h"

#include "filelister.h"
#include "portfolio.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QtQuick2ApplicationViewer viewer;
	qmlRegisterType<Portfolio>("HeroLab", 1, 0, "Portfolio");
	qmlRegisterType<FileLister>("HeroLab", 1, 0, "FileLister");

    viewer.setMainQmlFile(QStringLiteral("qml/QtHeroLab/main.qml"));
    viewer.showExpanded();

    return app.exec();
}
