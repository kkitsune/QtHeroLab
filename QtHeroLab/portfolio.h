#ifndef PORTFOLIO_H
#define PORTFOLIO_H

#include <quazipfile.h>
#include <QObject>
#include <QFile>
#include <QUrl>
#include <QMap>

class QDomElement;


class Portfolio : public QObject
{
	Q_OBJECT
	Q_PROPERTY(QString file READ fileName WRITE setFile NOTIFY fileChanged);
	Q_PROPERTY(QUrl searchPath READ searchPath);
public:
	static QUrl getGlobalSearchPath();

	Portfolio(QObject* parent = 0);
	virtual ~Portfolio();

	virtual inline QUrl searchPath() { return mSearchPath; }

	virtual QString fileName();
	virtual void setFile(const QString& file);

	Q_INVOKABLE virtual QString getCharacter(const QString& name);

signals:
	void fileChanged(const QString& newFile);

protected:
	virtual void parseIndex(QuaZip& qz, const QDomElement& root);

	QMap<QString, QString> clist;

	QuaZipFile* mZFile;
	QUrl mSearchPath;
	QFile* mPor;
};

#endif // PORTFOLIO_H
