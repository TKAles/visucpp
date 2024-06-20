#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    WFMCollection Waveforms;
};
#endif // MAINWINDOW_H
