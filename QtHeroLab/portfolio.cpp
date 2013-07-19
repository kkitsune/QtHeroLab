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
	mPor = new QFile(fullPath, this);

	QuaZip qz(mPor);
	if(qz.open(QuaZip::mdUnzip))
	{
		qz.setCurrentFile("index.xml");
		mZFile->setZip(&qz);
		if(mZFile->open(QIODevice::ReadOnly))
		{
			QDomDocument* doc = new QDomDocument;
			doc->setContent(mZFile);
			mZFile->close();

			parseIndex(qz, doc->documentElement());

			delete doc;
		}
		else Q_ASSERT(false);

		qz.close();
	}
	else Q_ASSERT(false);
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
	clist.clear();

	Q_ASSERT(root.firstChildElement("game").hasAttribute("name"));
	Q_ASSERT(root.firstChildElement("game").attribute("name") == "Pathfinder Roleplaying Game");
	for(QDomElement c = root.firstChildElement("characters").firstChildElement("character"); !c.isNull(); c = c.nextSiblingElement("character"))
	{
		QDomElement block;
		for(block = c.firstChildElement("statblocks").firstChildElement("statblock"); !block.isNull(); block.nextSiblingElement("statblock"))
			if(block.attribute("format") == "text")
				break;
		Q_ASSERT(!block.isNull());
		qz.setCurrentFile(block.attribute("folder") + "/" + block.attribute("filename"));
		if(mZFile->open(QIODevice::ReadOnly))
		{
			clist.insert(c.attribute("name"), QString(mZFile->readAll().constData()));
			mZFile->close();
		}
		else Q_ASSERT(false);
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
