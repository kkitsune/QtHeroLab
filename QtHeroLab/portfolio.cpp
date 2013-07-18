#include <quazip.h>
#include <QDebug>
#include <QtXml>
#include <QDir>

#include "portfolio.h"

Portfolio::Portfolio(QObject* parent) :
	QObject(parent), mZFile(new QuaZipFile(this)), mSearchPath(getGlobalSearchPath()), mPor(0)
{
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

	parseIndex(qz, doc->documentElement());

	delete doc;
	qz.close();
}

QString Portfolio::getCharacter(const QString& name)
{
	if(clist.contains(name))
		return clist[name];
	else
		return QString();
}

void Portfolio::parseIndex(QuaZip& qz, const QDomElement& root)
{
	Q_ASSERT(root.firstChildElement("game").hasAttribute("name"));
	Q_ASSERT(root.firstChildElement("game").attribute("name") == "Pathfinder Roleplaying Game");
	for(QDomElement c = root.firstChildElement("characters").firstChildElement("character"); !c.isNull(); c = c.nextSiblingElement("character"))
	{
		qDebug() << "Name : " << c.attribute("name");
		QDomElement block;
		for(block = c.firstChildElement("statblocks").firstChildElement("statblock"); !block.isNull(); block.nextSiblingElement("statblock"))
			if(block.attribute("format") == "text")
				break;
		Q_ASSERT(!block.isNull());
		qDebug() << "Statblock location : " << block.attribute("folder") + "/" + block.attribute("filename");
		qz.setCurrentFile(block.attribute("folder") + "/" + block.attribute("filename"));
		Q_ASSERT(mZFile->open(QIODevice::ReadOnly));
		clist.insert(c.attribute("name"), QString(mZFile->readAll().constData()));
		mZFile->close();
	}
}

QUrl Portfolio::getGlobalSearchPath()
{
#if defined(Q_OS_WIN)
	return QDir::homePath() + "/My Documents/Hero Lab/Portfolios/";
#elif defined(Q_OS_ANDROID)
	return QUrl("/sdcard/HeroLab/");
#elif defined(Q_OS_LINUX)
	return QDir::homePath() + "/HeroLab/";
#endif
}
