#ifndef BARCHART_HPP
#define BARCHART_HPP

#include <QGraphicsWidget>
#include <QList>
#include <QString>

namespace QtCharts{
class QBarSeries ;
class QChart;
}

class BarChart : public QGraphicsWidget
{
    Q_OBJECT
    Q_PROPERTY(QString title READ title WRITE setTitle NOTIFY titleChanged)
private:
    QColor theme_color_;
    const QList<qreal> data_;
    static const QStringList axis_256_;
    QSizeF size_;
    QtCharts::QChart * chart_ = nullptr;
    QtCharts::QBarSeries * bar_;
    QString title_;
public:

    static constexpr int toolBarHeight() { return 16; }

    BarChart( QColor/**/ ,QList<qreal> );
    ~BarChart();

    const QString & title()const{return title_;}
    void setTitle( QString );

    void onClose();
signals:
    void titleChanged();
protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override ;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
private:
    void _on_size_changed();
};

#endif // BARCHART_HPP
