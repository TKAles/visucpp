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
    ui->ProcessFFTValues->connect(ui->ProcessFFTValues, &QPushButton::clicked,
                                  this, &MainWindow::ProcessFFTValues_Click);
    connect(&DCVoidWatcher, &QFutureWatcher<void>::finished, this,
            &MainWindow::PlotDCScanValue);
    connect(this->tabFwd, &QShortcut::activated, this, &MainWindow::ForwardTab);
    connect(this->tabBack, &QShortcut::activated, this, &MainWindow::BackTab);
    // Setup the display widget
    this->ui->scanViewTabWidget->removeTab(0);
    QWidget* zeroTab = new QWidget();
    QCustomPlot* zeroPlot = new QCustomPlot();
    QVBoxLayout* zeroLayout = new QVBoxLayout();
    zeroLayout->addWidget(zeroPlot);
    zeroTab->setLayout(zeroLayout);
    this->scanTabs.push_back(zeroTab);
    this->scanPlots.push_back(zeroPlot);
    this->ui->scanViewTabWidget->addTab(zeroTab, "Scan Not Loaded");
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
        QString foundFilesMsg = QString::fromStdString(
                                std::format("Found {0} DC and RF files in {1} scans.",
                                this->Waveforms.FilesInCollection, this->Waveforms.ScansInCollection));
        this->statusBar()->showMessage(foundFilesMsg);
        this->ui->ProcessDCValues->setEnabled(true);
        this->ui->ProcessFFTValues->setEnabled(true);
    }
}

void MainWindow::ProcessDCValues_Click()
{
    QFuture<void> dcProcessingFuture;
    dcProcessingFuture = QtConcurrent::run([&]()
                         {
                            this->Waveforms.ComputeDCAverage_mp(this->Waveforms.DCScanList);
                         });

    DCVoidWatcher.setFuture(dcProcessingFuture);
    return;
}

void MainWindow::ProcessFFTValues_Click()
{
    this->Waveforms.ComputeFFT_mp(this->Waveforms.RFScanList);
}
/**
 * @brief MainWindow::PlotDCScanValue is responsible for creating the plots upon completion
 *        of averaging of the DC files.
 */
void MainWindow::PlotDCScanValue()
{

    this->ui->ProcessDCValues->setEnabled(true);
    this->ui->ProcessDCValues->setText("View DC Maps");
    this->ui->statusbar->showMessage("Showing DC Scan #0");
    QCPColorMap *currentDCMap = new QCPColorMap(this->scanPlots[0]->xAxis, this->scanPlots[0]->yAxis);
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
    QCPColorScale *dcColorScaling = new QCPColorScale(this->scanPlots[0]);
    this->scanPlots[0]->plotLayout()->addElement(0, 0.5, dcColorScaling);
    currentDCMap->setColorScale(dcColorScaling);
    currentDCMap->rescaleDataRange();
    dcColorScaling->setType(QCPAxis::atRight);

    this->scanPlots[0]->rescaleAxes();
    this->scanPlots[0]->replot();
    if(this->ui->scanViewTabWidget->count() != this->Waveforms.DCValues.size())
    {
        for(int i = this->ui->scanViewTabWidget->count(); i < this->Waveforms.DCValues.size(); ++i)
        {
            QWidget* tabWidget = new QWidget();
            QCustomPlot* tabPlot = new QCustomPlot();
            QVBoxLayout* tabLayout = new QVBoxLayout();
            if(i == this->ui->scanViewTabWidget->count())
            {
                this->ui->scanViewTabWidget->setTabText(0, "Scan 0");
            }
            QCPColorMap* colorMap = new QCPColorMap(tabPlot->xAxis, tabPlot->yAxis);
            colorMap->data()->setSize(this->Waveforms.DCValues[i].size(),
                                      this->Waveforms.DCValues[i][0].size());
            colorMap->data()->setRange(QCPRange(0, this->Waveforms.DCValues[i].size()),
                                       QCPRange(0, this->Waveforms.DCValues[i][0].size()));
            for(int scanRow = 0; scanRow < this->Waveforms.DCValues[i].size(); scanRow++)
            {
                for(int pixel = 0; pixel < this->Waveforms.DCValues[i][0].size(); pixel++)
                {
                    colorMap->data()->setCell(scanRow, pixel,
                                              this->Waveforms.DCValues[i][scanRow][pixel]);
                }
            }
            QCPColorScale *mapColorScaling = new QCPColorScale(tabPlot);
            tabPlot->plotLayout()->addElement(0, 0.5, mapColorScaling);
            colorMap->setColorScale(mapColorScaling);
            colorMap->rescaleDataRange();
            mapColorScaling->setType(QCPAxis::atRight);
            tabPlot->rescaleAxes();
            tabPlot->replot();
            tabLayout->addWidget(tabPlot);
            tabWidget->setLayout(tabLayout);
            this->scanTabs.emplace_back(tabWidget);
            this->scanPlots.emplace_back(tabPlot);
            this->ui->scanViewTabWidget->addTab(tabWidget, QString("Scan %1").arg(i));
        }
    }
}
/**
 * @brief MainWindow::ForwardTab, slot function to catch a CTRL+Tab keyboard
 *        shortcut
 * @return void
 */
void MainWindow::ForwardTab()
{
    if(this->scanPlots.size() == 1)
    {
        return;
    }
    int tabPosition = this->ui->scanViewTabWidget->currentIndex();
    if (tabPosition == this->scanPlots.size() - 1)
    {
        this->ui->scanViewTabWidget->setCurrentIndex(0);
    } else {
        this->ui->scanViewTabWidget->setCurrentIndex(tabPosition + 1);
    }
}
/**
 * @brief MainWindow::BackTab, slot function to catch a SHIFT+CTRL+Tab
 *        keyboard shortcut.
 * @return void
 */
void MainWindow::BackTab()
{
    if(this->scanPlots.size() == 1)
    {
        return;
    }
    int tabPosition = this->ui->scanViewTabWidget->currentIndex();
    if(tabPosition == 0)
    {
        this->ui->scanViewTabWidget->setCurrentIndex(this->scanPlots.size() - 1);
    } else {
        this->ui->scanViewTabWidget->setCurrentIndex(tabPosition - 1);
    }
}

