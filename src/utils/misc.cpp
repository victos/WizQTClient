#include "misc.h"

#include <QDateTime>
#include <QDir>
#include <QFile>
#include <QFileInfo>
#include <QTextStream>

namespace Utils {

QString Misc::time2humanReadable(const QDateTime& time) {
    QDateTime t(QDateTime::currentDateTime());
    int nElapseSecs = time.secsTo(t);
    int nElapseDays = time.daysTo(t);

    if (nElapseDays == 1) {
        return QObject::tr("Yesterday");
    } else if (nElapseDays == 2) {
        return QObject::tr("The day before yesterday");
    } else if (nElapseDays > 2) {
        return time.toString("yy-M-d");
    }

    if (nElapseSecs < 60) {
        // less than 1 minutes: "just now"
        return QObject::tr("Just now");

    } else if (nElapseSecs >= 60 && nElapseSecs < 60 * 2) {
        // 1 minute: "1 minute ago"
        return QObject::tr("1 minute ago");

    } else if (nElapseSecs >= 120 && nElapseSecs < 60 * 60) {
        // 2-60 minutes: "x minutes ago"
        QString str = QObject::tr("%1 minutes ago");
        return str.arg(nElapseSecs/60);

    } else if (nElapseSecs >= 60 * 60 && nElapseSecs < 60 * 60 * 2) {
        // 1 hour: "1 hour ago"
        return QObject::tr("1 hour ago");

    } else if (nElapseSecs >= 60 * 60 * 2 && nElapseSecs < 60 * 60 * 24) {
        // 2-24 hours: "x hours ago"
        QString str = QObject::tr("%1 hours ago");
        return str.arg(nElapseSecs/60/60);
    }

    return QString("Error");
}

bool Misc::loadUnicodeTextFromFile(const QString& strFileName, QString& strText)
{
    QFile file(strFileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QTextStream stream(&file);
    strText = stream.readAll();
    file.close();

    return true;
}

void Misc::addBackslash(QString& strPath)
{
    strPath.replace('\\', '/');

    if (strPath.endsWith('/'))
        return;

    strPath += '/';
}

void Misc::removeBackslash(CString& strPath)
{
    while (1)
    {
        if (!strPath.endsWith('/'))
            return;

        strPath.remove(strPath.length() - 1, 1);
    }
}

CString Misc::addBackslash2(const CString& strPath)
{
    CString str(strPath);
    addBackslash(str);
    return str;
}
CString Misc::removeBackslash2(const CString& strPath)
{
    CString str(strPath);
    removeBackslash(str);
    return str;
}

void Misc::ensurePathExists(const CString& path)
{
    QDir dir;
    dir.mkpath(path);
}

void Misc::ensureFileExists(const QString& strFileName)
{
    QFile file(strFileName);
    if (!file.exists()) {
        file.open(QIODevice::ReadWrite);
        file.close();
    }
}

CString Misc::extractFilePath(const CString& strFileName)
{
    CString str = strFileName;
    str.Replace('\\', '/');
    int index = str.lastIndexOf('/');
    if (-1 == index)
        return strFileName;
    //
    return str.left(index + 1); //include separator
}


CString Misc::extractLastPathName(const CString& strFileName)
{
    CString strPath = removeBackslash2(strFileName);
    return extractFileName(strPath);
}

QString Misc::extractFileName(const QString& strFileName)
{
    QString str = strFileName;
    str.replace('\\', '/');
    int index = str.lastIndexOf('/');
    if (-1 == index)
        return strFileName;

    return strFileName.right(str.length() - index - 1);
}

QString Misc::extractFileTitle(const QString &strFileName)
{
    QString strName = extractFileName(strFileName);

    int index = strName.lastIndexOf('.');
    if (-1 == index)
        return strName;

    return strName.left(index);
}

CString Misc::extractTitleTemplate(const CString& strFileName)
{
    return strFileName;
}

CString Misc::extractFileExt(const CString& strFileName)
{
    CString strName = extractFileName(strFileName);
    //
    int index = strName.lastIndexOf('.');
    if (-1 == index)
        return "";
    //
    return strName.right(strName.GetLength() - index);  //include .
}

qint64 Misc::getFileSize(const CString& strFileName)
{
    QFileInfo info(strFileName);
    return info.size();
}

void Misc::deleteFile(const CString& strFileName)
{
    QDir dir(extractFilePath(strFileName));
    dir.remove(extractFileName(strFileName));
}

bool Misc::isSimpChinese()
{
    QLocale local;
    QString name = local.name().toLower();
    if (name == "zh_cn"
        || name == "zh-cn")
    {
        return true;
    }
    return false;
}



} // namespace Utils
