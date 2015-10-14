#ifndef CWIZSINGLEDOCUMENTVIEW_H
#define CWIZSINGLEDOCUMENTVIEW_H

#include <QWidget>
#include <QMap>
#include "wizdef.h"

class WIZDOCUMENTDATA;
namespace Core {

class CWizDocumentView;
class CWizSingleDocumentViewer : public QWidget
{
    Q_OBJECT
public:
    CWizSingleDocumentViewer(CWizExplorerApp& app, const QString& guid, QWidget* parent = 0);
    ~CWizSingleDocumentViewer();

    CWizDocumentView* docView();
    QString guid() const { return m_guid; }

signals:
    void documentViewerDeleted(QString guid);

private:
#ifdef USEWEBENGINE
    CWizDocumentWebEngine* m_webEngine;
#else
    CWizDocumentView* m_docView;
#endif
    QString m_guid;
};



class CWizSingleDocumentViewDelegate : public QObject
{
    Q_OBJECT
public:
    CWizSingleDocumentViewDelegate(CWizExplorerApp& app, QObject* parent = 0);

    CWizSingleDocumentViewer* getDocumentViewer(const QString& guid);
    QMap<QString, CWizSingleDocumentViewer*>& getDocumentViewerMap();

public slots:
    void viewDocument(const WIZDOCUMENTDATA& doc);
    void onDocumentViewerDeleted(QString guid);

signals:
    void documentChanged(const QString& strGUID, CWizDocumentView* viewer);
    void documentViewerClosed(QString guid);

private:

private:
    QMap<QString, CWizSingleDocumentViewer*> m_viewerMap;
    CWizExplorerApp& m_app;
};

}

void bindESCToQuitFullScreen(QWidget* wgt);
void bringWidgetToFront(QWidget* wgt);

#endif // CWIZSINGLEDOCUMENTVIEW_H
