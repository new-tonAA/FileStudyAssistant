#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    pdfDoc = new QPdfDocument(this);
    pdfView = new QPdfView(this);

    pdfView->setDocument(pdfDoc);
    pdfView->setPageMode(QPdfView::PageMode::MultiPage);
    pdfView->setZoomMode(QPdfView::ZoomMode::FitToWidth);

    pdfView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

    pdfView->setMinimumSize(800, QMainWindow::height());//暂时固定尺寸
    pdfView->setMaximumSize(1200, QMainWindow::height());

    pdfView->hide();

    connect(ui->FileView, &droplabel::pdfDropped,
            this, &MainWindow::openPdf);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::openPdf(const QString &path)
{
    if (pdfDoc->load(path) != QPdfDocument::Error::None)
        return;

    ui->FileView->hide();
    pdfView->show();
}


