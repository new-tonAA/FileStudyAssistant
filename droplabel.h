#ifndef DROPLABEL_H
#define DROPLABEL_H

#include <QLabel>

class droplabel : public QLabel
{
    Q_OBJECT
public:
    explicit droplabel(QWidget *parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;

signals:
    void pdfDropped(const QString &path);
};

#endif // DROPLABEL_H
