#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wfmcollection.hpp"
#include <iostream>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->InitializeUI();
    // Signals
    ui->SelectScanButton->connect(ui->SelectScanButton, &QPushButton::clicked,
                                  this, &MainWindow::LoadWFMDirectory_Click);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::InitializeUI()
{
    // Disable all controls except for the load button.
    ui->ProcessDCValues->setEnabled(false);
    ui->ProcessFFTValues->setEnabled(false);
    ui->AlignScanButton->setEnabled(false);
    ui->ScanDataLabel->setEnabled(false);
    ui->ScanTitleLabel->setEnabled(false);
    ui->ScanTitleLineEdit->setEnabled(false);
    ui->XOriginLabel->setEnabled(false);
    ui->XOriginLineEdit->setEnabled(false);
    ui->YOriginLabel->setEnabled(false);
    ui->YOriginLineEdit->setEnabled(false);
    ui->XDeltaLabel->setEnabled(false);
    ui->XDeltaLineEdit->setEnabled(false);
    ui->YDeltaLabel->setEnabled(false);
    ui->YDeltaLineEdit->setEnabled(false);
    this->showMaximized();
}

void MainWindow::LoadWFMDirectory_Click()
{
    QFileDialog wfmDirectoryDialog(this);
    wfmDirectoryDialog.setFileMode(QFileDialog::Directory);
    wfmDirectoryDialog.setOption(QFileDialog::ShowDirsOnly, true);
    wfmDirectoryDialog.setViewMode(QFileDialog::List);

    if (wfmDirectoryDialog.exec())
    {
        std::cout << "Selected directory was: " <<
            wfmDirectoryDialog.selectedFiles()[0].toStdString() << std::endl;
        WFMCollection wfmCollection;
        wfmCollection.SearchForWFMs(wfmDirectoryDialog.selectedFiles()[0].toStdString());
    }
}
