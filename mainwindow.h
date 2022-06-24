#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sinxBtn_clicked();

    void on_cosBtn_clicked();

    void on_mainBtn_clicked();

private:
    Ui::MainWindow *ui;
    bool isDraw = true;
    float a, b, c;
    float x1, x2, y1, y2;
    float step;
    float temp;
    QVector<double> x, y;

};
#endif // MAINWINDOW_H
