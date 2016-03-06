#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QWidget>
#include <QImage>

class QGraphicsScene;
class ImageView;
class ImageItem;
class BarChart;

class MainWindow : public QWidget
{
    Q_OBJECT
private:
    ImageView * image_view_ = nullptr ;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

    ImageItem * addImage(QImage image__);
    BarChart * addBarChart(  QColor,QList<qreal>);
    QGraphicsScene * getScene() const;

};

#endif // MAINWINDOW_HPP
