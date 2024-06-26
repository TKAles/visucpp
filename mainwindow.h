#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtConcurrent>
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
    void UpdateUIDCStarted();
    void UpdateUIDCInProgress();
    void PlotDCScanValue();
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WFMCollection Waveforms;
    QFutureWatcher<void> DCVoidWatcher;

};
#endif // MAINWINDOW_H
