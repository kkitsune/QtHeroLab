#ifndef FILELISTER_H
#define FILELISTER_H

#include <QObject>
#include <QDir>

class FileLister : public QObject
{
	Q_OBJECT
	Q_PROPERTY(int level READ level)
public:
	FileLister(QObject* parent = 0);
	virtual ~FileLister();

	virtual inline int level() { return m_level; }

	Q_INVOKABLE virtual QStringList list(const QString& subDir = QString());
	Q_INVOKABLE virtual void upOne();

protected:
	QDir* path;
	int m_level;
};

#endif // FILELISTER_H
