#include <QQmlContext>

#include "platform.h"

Platform::Platform(QQmlEngine* engine) : QObject(0)
{
	engine->rootContext()->setContextProperty("platform", this);
}
