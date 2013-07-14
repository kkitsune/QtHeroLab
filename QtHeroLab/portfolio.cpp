#include <quazip.h>
#include <QDebug>
#include <QtXml>
#include <QDir>

#include "portfolio.h"

Portfolio::Portfolio(QObject* parent) :
	QObject(parent), mZFile(new QuaZipFile(this)), mPor(0)
{
#if defined(Q_OS_WIN)
	mSearchPath = QDir::homePath() + "/My Documents/Hero Lab/Portfolios/";
#elif defined(Q_OS_ANDROID)
	mSearchPath = "/sdcard/HeroLab/";
#elif defined(Q_OS_LINUX)
	mSearchPath = QDir::homePath() + "/HeroLab/";
#endif
}

Portfolio::~Portfolio()
{
}

QString Portfolio::fileName()
{
	if(mPor && mPor->isOpen())
		return mPor->fileName();
	else
		return "";
}

void Portfolio::setFile(const QString &file)
{
	if(file.isEmpty() && mPor != 0)
	{
		if(mPor->isOpen())
			mPor->close();
		delete mPor;
		mPor = 0;
	}

	QString fullPath = searchPath().resolved(QUrl("./" + file)).toString();
	qDebug() << "Path : " << fullPath;
	mPor = new QFile(fullPath, this);
	qDebug() << "Exists : " << mPor->exists();

	QuaZip qz(mPor);
	Q_ASSERT(qz.open(QuaZip::mdUnzip));
	Q_ASSERT(qz.setCurrentFile("index.xml"));
	qDebug() << "Current file : " << qz.getCurrentFileName();

	mZFile->setZip(&qz);
	Q_ASSERT(mZFile->open(QIODevice::ReadOnly));
	qDebug() << "Actual file : " << mZFile->getActualFileName();

	QDomDocument* doc = new QDomDocument;
	Q_ASSERT(doc->setContent(mZFile));
	mZFile->close();

	parseIndex(doc);

	delete doc;
	qz.close();
}


void Portfolio::parseIndex(QDomDocument* doc)
{
}
