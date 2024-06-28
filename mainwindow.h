#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
#include <QShortcut>
#include <qcustomplot.h>
#include "wfmcollection.hpp"

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
    void InitializeUI();
    void LoadWFMDirectory_Click();
    void ProcessDCValues_Click();
    void ProcessFFTValues_Click();
    void UpdateUIDCStarted();
    void UpdateUIDCInProgress();
    void PlotDCScanValue();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    std::vector<QWidget*> scanTabs;
    std::vector<QCustomPlot*> scanPlots;
    WFMCollection Waveforms;
    QFutureWatcher<void> DCVoidWatcher;
    QShortcut *tabFwd = new QShortcut((Qt::CTRL | Qt::Key_Tab), this);
    QShortcut *tabBack = new QShortcut((Qt::CTRL | Qt::SHIFT | Qt::Key_Tab), this);
    void ForwardTab();
    void BackTab();

};
#endif // MAINWINDOW_H
