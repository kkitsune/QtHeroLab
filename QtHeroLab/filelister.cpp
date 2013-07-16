#include <QDebug>

#include "filelister.h"
#include "portfolio.h"

FileLister::FileLister(QObject* parent) : QObject(parent)
{
	path = new QDir(Portfolio::getGlobalSearchPath().toString());
}

FileLister::~FileLister()
{
	delete path;
}

QStringList FileLister::list(const QString& subDir)
{
	QStringList ret;
	if(!subDir.isEmpty())
	{
		m_level++;
		path->cd(subDir);
	}

	QFileInfoList fil = path->entryInfoList();
	foreach (QFileInfo f, fil)
	{
		if(f.isDir() && f.fileName() != "." && f.fileName() != "..")
			ret.append(f.fileName() + "/");
		else
			if(f.suffix() == "por")
				ret.append(f.fileName());
	}
	return ret;
}

void FileLister::upOne()
{
	m_level--;
	Q_ASSERT(m_level >= 0);
	Q_ASSERT(path->cdUp());
}
