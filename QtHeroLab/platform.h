#ifndef PLATFORM_H
#define PLATFORM_H

#include <QQmlEngine>
#include <QObject>

class Platform : public QObject
{
	Q_OBJECT
	Q_PROPERTY(bool isWindows READ isWindows)
	Q_PROPERTY(bool isLinux READ isLinux)
	Q_PROPERTY(bool isAndroid READ isAndroid)
public:
	Platform(QQmlEngine* engine);

	inline bool isWindows()
	{
#ifdef Q_OS_WIN
		return true;
#else
		return false;
#endif
	}

	inline bool isLinux()
	{
#ifdef Q_OS_LINUX
		return true;
#else
		return false;
#endif
	}

	inline bool isAndroid()
	{
#ifdef Q_OS_ANDROID
		return true;
#else
		return false;
#endif
	}
};

#endif // PLATFORM_H
