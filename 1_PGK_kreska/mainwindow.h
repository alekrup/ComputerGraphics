#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <cmath>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    QImage im;
    int x,y,x2,y2;

private:
    Ui::MainWindow *ui;

    QImage *img;
    QImage *imgCopy;

    int szer;
    int wys;
    int poczX;
    int poczY;

private slots:
    void paintEvent(QPaintEvent*);
    void mouseMoveEvent(QMouseEvent *e);
    void rysujPiksel(int x, int y);
    void on_pushButtonClose_clicked();
    //void mouseReleaseEvent(QMouseEvent *e);
    void mousePressEvent(QMouseEvent *e);
    void rysujLinie(int x, int y, int x2, int y2);
    void zaladujObraz();
    void mouseReleaseEvent(QMouseEvent *e);

//private:
//    Ui::MainWindow *ui;


    void on_clear_clicked();
};
#endif // MAINWINDOW_H
