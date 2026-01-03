#include "droplabel.h"

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QMimeData>
#include <QFileInfo>

#include <QPdfDocument>
#include <QPdfView>

droplabel::droplabel(QWidget *parent)
    : QLabel(parent)
{
    setAcceptDrops(true);                 // 关键，使得能够接收
    setAlignment(Qt::AlignCenter);
    setText("Drag Word / PDF / PPT here");
    setStyleSheet("border: 2px dashed #888;");
}

void droplabel::dragEnterEvent(QDragEnterEvent *event)
{
    if (event->mimeData()->hasUrls()) {
        event->acceptProposedAction();
    }
}

void droplabel::dropEvent(QDropEvent *event)
{
    const auto urls = event->mimeData()->urls();
    if (urls.isEmpty())
        return;

    QString filePath = urls.first().toLocalFile();
    QFileInfo info(filePath);

    QString ext = info.suffix().toLower();
    if (ext != "pdf" && ext != "doc" && ext != "docx"
        && ext != "ppt" && ext != "pptx") {
        setText("Unsupported file");
        return;
    }

    //setText("File:\n" + info.fileName());
    if (ext == "pdf")
    {
        emit pdfDropped(filePath);
        return;
    }
    /*
    QPdfDocument *doc = new QPdfDocument(this);
    doc->load(filePath);

    QPdfView *view = new QPdfView;
    view->setDocument(doc);
    view->show();
*/
}
