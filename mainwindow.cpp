#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "wfmcollection.hpp"
#include <iostream>
#include <QFileDialog>
#include <QtConcurrent>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->InitializeUI();
    // Signals
    ui->SelectScanButton->connect(ui->SelectScanButton, &QPushButton::clicked,
                                  this, &MainWindow::LoadWFMDirectory_Click);
    ui->ProcessDCValues->connect(ui->ProcessDCValues, &QPushButton::clicked,
                                  this, &MainWindow::ProcessDCValues_Click);
    connect(&DCVoidWatcher, &QFutureWatcher<void>::finished, this,
            &MainWindow::PlotDCScanValue);
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
    this->statusBar()->showMessage("Waiting for directory selection...");
    wfmDirectoryDialog.setFileMode(QFileDialog::Directory);
    wfmDirectoryDialog.setOption(QFileDialog::ShowDirsOnly, true);
    wfmDirectoryDialog.setViewMode(QFileDialog::List);

    if (wfmDirectoryDialog.exec())
    {
        QString dirString = "Selected ";
        dirString.append(wfmDirectoryDialog.selectedFiles()[0]);
        this->statusBar()->showMessage(dirString);
        this->Waveforms.SearchForWFMs(wfmDirectoryDialog.selectedFiles()[0].toStdString());
        QString foundFilesMsg = QString::fromStdString(std::format("Found {0} DC and RF files in {1} scans.",
                                                                   this->Waveforms.FilesInCollection, this->Waveforms.ScansInCollection));
        this->statusBar()->showMessage(foundFilesMsg);
        this->ui->ProcessDCValues->setEnabled(true);

    }
}

void MainWindow::ProcessDCValues_Click()
{
    QFuture<void> dcProcessingFuture;
    dcProcessingFuture = QtConcurrent::run([&]() {this->Waveforms.ComputeDCAverage_mp(this->Waveforms.DCScanList);});
    DCVoidWatcher.setFuture(dcProcessingFuture);
    return;
}

void MainWindow::UpdateUIDCStarted()
{

}


void MainWindow::PlotDCScanValue()
{
    this->ui->ProcessDCValues->setEnabled(true);
    this->ui->ProcessDCValues->setText("View DC Maps");
    this->ui->statusbar->showMessage("Showing DC Scan #0");
    QCPColorMap *currentDCMap = new QCPColorMap(this->ui->displayWidget->xAxis, this->ui->displayWidget->yAxis);
    currentDCMap->data()->setSize(this->Waveforms.DCValues[0].size(), this->Waveforms.DCValues[0][0].size());
    currentDCMap->data()->setRange(QCPRange(0, this->Waveforms.DCValues[0].size()),
                                   QCPRange(0, this->Waveforms.DCValues[0][0].size()));
    for(int scanRow = 0; scanRow < this->Waveforms.DCValues[0].size(); scanRow++)
    {
        for(int pixel = 0; pixel < this->Waveforms.DCValues[0][0].size(); pixel++)
        {
            currentDCMap->data()->setCell(scanRow, pixel, this->Waveforms.DCValues[0][scanRow][pixel]);
        }
    }
    QCPColorScale *dcColorScaling = new QCPColorScale(this->ui->displayWidget);
    this->ui->displayWidget->plotLayout()->addElement(0, 0.5, dcColorScaling);
    currentDCMap->setColorScale(dcColorScaling);
    currentDCMap->rescaleDataRange();
    dcColorScaling->setType(QCPAxis::atRight);

    this->ui->displayWidget->rescaleAxes();
    this->ui->displayWidget->replot();
}
