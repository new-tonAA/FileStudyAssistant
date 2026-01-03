#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QStackedLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // 1. 创建 PDF 文档和视图
    pdfDoc = new QPdfDocument(this);
    pdfView = new QPdfView(this);
    pdfView->setDocument(pdfDoc);
    pdfView->setPageMode(QPdfView::PageMode::MultiPage);
    pdfView->setZoomMode(QPdfView::ZoomMode::FitToWidth);

    // 让 pdfView 高度自动填满，宽度范围内变动
    pdfView->setMinimumWidth(600);
    pdfView->setMaximumWidth(1000);
    pdfView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Expanding);
    pdfView->hide(); // 拖 PDF 前隐藏

    // 2. 核心：用 QStackedLayout 管理 FileView 和 pdfView
    // 删除 UI 中原有布局（如果有）
    if (ui->centralwidget->layout())
        delete ui->centralwidget->layout();

    QStackedLayout *stack = new QStackedLayout(ui->centralwidget);
    stack->setContentsMargins(0,0,0,0); // 去掉边距
    stack->addWidget(ui->FileView); // 拖拽提示
    stack->addWidget(pdfView);      // PDF 显示

    // 3. 连接拖拽信号
    connect(ui->FileView, &droplabel::pdfDropped,
            this, &MainWindow::openPdf);
}

MainWindow::~MainWindow()
{
    delete ui;
}

// 4. 打开 PDF
void MainWindow::openPdf(const QString &path)
{
    if (pdfDoc->load(path) != QPdfDocument::Error::None)
        return;

    // 切换到 pdfView
    QStackedLayout *stack = qobject_cast<QStackedLayout*>(ui->centralwidget->layout());
    if (stack)
        stack->setCurrentWidget(pdfView);
}


