#ifndef FILELISTER_H
#define FILELISTER_H

#include <QObject>
#include <QDir>

class FileLister : public QObject
{
	Q_OBJECT
public:
	FileLister(QObject* parent = 0);
	virtual ~FileLister();

	Q_INVOKABLE virtual QStringList list(const QString& subDir = QString());

protected:
	QDir* path;
};

#endif // FILELISTER_H
