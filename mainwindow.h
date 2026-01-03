#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPdfDocument>
#include <QPdfView>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openPdf(const QString &path);

private:
    Ui::MainWindow *ui;
    QPdfDocument *pdfDoc;
    QPdfView *pdfView;
};
#endif // MAINWINDOW_H
