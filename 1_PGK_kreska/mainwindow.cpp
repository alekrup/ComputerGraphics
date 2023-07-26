#include "mainwindow.h"
#include "./ui_mainwindow.h"

using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)   //: dziedziczenie => klasa MainWindow rozszerza klase QMainWindow (dziedzinaczneie z klasy QMainWinadow(rodzic))
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    szer = ui->frame->width();
    wys = ui->frame->height();
    poczX = ui->frame->x();
    poczY = ui->frame->y();

    img = new QImage(szer, wys, QImage::Format_RGB32);   //obiekt klasy qimage czyli przestrzeń po której mogę rysować
    imgCopy = new QImage(szer, wys, QImage::Format_RGB32);   //obiekt klasy qimage przeznaczona do ubdejtowania lini

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::paintEvent(QPaintEvent*)
{
    // Obiekt klasy QPainter pozwala nam rysowac na komponentach
    QPainter p(this);

    // Rysuje obrazek "img" w punkcie (poczX,poczY)
    // (tu bedzie lewy gorny naroznik)
    p.drawImage(poczX,poczY,*img);
}

void MainWindow::mouseMoveEvent(QMouseEvent *e)
{
    QPoint m = e->pos();
   // qDebug("x: %d   y: %d", m.x(), m.y());
    x2 = m.x();
    y2 = m.y();

    zaladujObraz();

    rysujLinie(x, y, x2, y2);

    update();
}

void MainWindow::rysujPiksel(int x, int y)
{
    if(
        x >= szer + poczX ||
        x < poczX         ||
        y >= wys + poczY  ||
        y < poczY
    ) {
        return;
    }
    x -= poczX;
    y -= poczY;

    uchar *pix = img->scanLine(y);
    pix[4*x] = 255;             //b
    pix[4*x + 1] = 255;         //g
    pix[4*x + 2] = 255;         //r
}




void MainWindow::on_pushButtonClose_clicked()
{
    qApp->quit();
}



void MainWindow::mousePressEvent(QMouseEvent *e)
{
    QPoint m = e->pos();
    qDebug("x: %d   y: %d", m.x(), m.y());
    x = m.x();
    y = m.y();

    rysujPiksel(x, y);

    update();           //funkcja update odświerza komponent
}


void MainWindow::rysujLinie(int x, int y, int x2, int y2)
{
    if(x2 - x == 0){
        for(int i = y; i < y2; i++)
            rysujPiksel(x, i);
    }

      double m = (double)(y2 - y)/(double)(x2 - x);

      if(abs(m) < 1) {
          if(x > x2){
            swap(x, x2); //swap - zamienia miejscami
            swap(y, y2);
          }
          for(int i = x; i <= x2; i++)
          {
              double j = m * (i - x) + y;
              rysujPiksel(i, (int)floor(j + 0.5));
          }
      }
      else {
          if(y > y2) {
              swap(x, x2);
              swap(y, y2);
              }//swap - zamienia miejscami
              double m = (double)(x2 - x)/(double)(y2 - y);
          for(int i = y; i <= y2; i++)
          {
              double j = m * (i - y) + x;
              rysujPiksel((int)floor(j + 0.5), i);
          }
      }
}

void MainWindow::on_clear_clicked()
{
    for(int i = 0; i < wys; i++){
        for(int j = 0; j < szer; j++){
            uchar *pix = img->scanLine(i);
            pix[4*j] = 0;             //b
            pix[4*j + 1] = 0;         //g
            pix[4*j + 2] = 0;         //r

        }
    }
    update();
}

void MainWindow::zaladujObraz()
{
    *img = imgCopy->copy();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *e) {

    *imgCopy = img->copy();
    update();
}
