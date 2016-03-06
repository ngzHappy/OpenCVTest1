#include "BarChart.hpp"
#include "ImageScene.hpp"
#include <memory>
#include <QChart>
#include <QBarSeries>
#include <QBarSet>
#include <QChartView>
#include <QBarCategoryAxis>


const QStringList BarChart::axis_256_{
    "0",	"1",	"2",	"3",	"4",	"5",	"6",	"7",	"8",	"9",	"10",	"11",	"12",	"13",	"14",	"15",
    "16",	"17",	"18",	"19",	"20",	"21",	"22",	"23",	"24",	"25",	"26",	"27",	"28",	"29",	"30",	"31",
    "32",	"33",	"34",	"35",	"36",	"37",	"38",	"39",	"40",	"41",	"42",	"43",	"44",	"45",	"46",	"47",
    "48",	"49",	"50",	"51",	"52",	"53",	"54",	"55",	"56",	"57",	"58",	"59",	"60",	"61",	"62",	"63",
    "64",	"65",	"66",	"67",	"68",	"69",	"70",	"71",	"72",	"73",	"74",	"75",	"76",	"77",	"78",	"79",
    "80",	"81",	"82",	"83",	"84",	"85",	"86",	"87",	"88",	"89",	"90",	"91",	"92",	"93",	"94",	"95",
    "96",	"97",	"98",	"99",	"100",	"101",	"102",	"103",	"104",	"105",	"106",	"107",	"108",	"109",	"110",	"111",
    "112",	"113",	"114",	"115",	"116",	"117",	"118",	"119",	"120",	"121",	"122",	"123",	"124",	"125",	"126",	"127",
    "128",	"129",	"130",	"131",	"132",	"133",	"134",	"135",	"136",	"137",	"138",	"139",	"140",	"141",	"142",	"143",
    "144",	"145",	"146",	"147",	"148",	"149",	"150",	"151",	"152",	"153",	"154",	"155",	"156",	"157",	"158",	"159",
    "160",	"161",	"162",	"163",	"164",	"165",	"166",	"167",	"168",	"169",	"170",	"171",	"172",	"173",	"174",	"175",
    "176",	"177",	"178",	"179",	"180",	"181",	"182",	"183",	"184",	"185",	"186",	"187",	"188",	"189",	"190",	"191",
    "192",	"193",	"194",	"195",	"196",	"197",	"198",	"199",	"200",	"201",	"202",	"203",	"204",	"205",	"206",	"207",
    "208",	"209",	"210",	"211",	"212",	"213",	"214",	"215",	"216",	"217",	"218",	"219",	"220",	"221",	"222",	"223",
    "224",	"225",	"226",	"227",	"228",	"229",	"230",	"231",	"232",	"233",	"234",	"235",	"236",	"237",	"238",	"239",
    "240",	"241",	"242",	"243",	"244",	"245",	"246",	"247",	"248",	"249",	"250",	"251",	"252",	"253",	"254",	"255",
};

namespace {
class CloseButtonItem : public QGraphicsWidget {
    friend class BarChart;
    BarChart *  const super_;
public:
    CloseButtonItem(BarChart * p):QGraphicsWidget(p),super_(p) {
        setToolTip(QString::fromUtf8(u8R"(关闭图片)"));
    }
    void mousePressEvent(QGraphicsSceneMouseEvent *) override {
        super_->onClose();
    }

    void paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget) {
        constexpr float _sp_=3.0f;
        constexpr float _width_=BarChart::toolBarHeight()-_sp_;

        painter->setPen(QPen(QColor(200,56,67),2.2f));
        painter->drawLine(
            QPointF{ _sp_,_sp_ },
            QPointF{ _width_,_width_ }
        );
        painter->drawLine(
            QPointF{ _width_,_sp_ },
            QPointF{ _sp_,_width_ }
        );

        return; (void)widget; (void)option;
    }
};
}

void BarChart::onClose() {
    QGraphicsScene * _sc_=scene();
    if (_sc_==nullptr) { this->deleteLater(); }
    _sc_->removeItem(this);
}

BarChart::BarChart(QColor c__,QList<qreal> value__):data_(std::move(value__)){
    this->resize(256*3,256*2);
    size_=QSize(0,0);
    theme_color_=c__;
    this->setFlag( QGraphicsItem::ItemIsMovable );

    {
        auto * _close_ = new CloseButtonItem(this);
        _close_->resize( toolBarHeight(),toolBarHeight() );
    }

    {
        using namespace QtCharts;
        QChart * _chart_=new QChart(this);
        chart_=_chart_;
        _chart_->setBackgroundBrush( Qt::transparent );
        _chart_->setAnimationOptions(QChart::SeriesAnimations);
        _chart_->legend()->hide();
        QBarSet * _barset_=new QBarSet("?");
        _barset_->append(data_);
        _barset_->setBrush( theme_color_ );
        _barset_->setBorderColor( theme_color_ );
        QBarSeries * _bars_=new QBarSeries;
        _bars_->append( _barset_ );
        bar_=_bars_;
        _chart_->addSeries(_bars_);
        _chart_->createDefaultAxes();
        _chart_->setBackgroundVisible(false);

        if (data_.size()<=256) {
            QBarCategoryAxis *_axis_ = new QBarCategoryAxis();
            int i__=0; const auto size__ = data_.size();
            QStringList tmp__; tmp__.reserve( size__ );
            for ( const auto & i:axis_256_ ) {
                if (i__<size__) { ++i__; }
                else { break; }
                tmp__.push_back(i);
            }
            _axis_->append(tmp__);
            _chart_->setAxisX(_axis_, _bars_);
        }

        if ( data_.size()>0 ) {
            qreal max__=*data_.begin();
            qreal min__=max__;
            for (const auto & i:data_) {
                if (i>max__) { max__=i; }
                else if (i<min__) { min__=i; }
            }
            const qreal diff__=std::abs(max__-min__);
            _chart_->axisY()->setMax(diff__*0.1f+max__);
        }

        if (data_.size()>32) {
            _chart_->axisX()->setGridLineVisible(false);
            _chart_->axisX()->setLabelsVisible(false);
            _chart_->axisX()->setLineVisible(false);
        }

    }

    _on_size_changed();
    connect(this,&BarChart::geometryChanged,
            this,&BarChart::_on_size_changed);
}

void BarChart::setTitle(QString v__) {
    if (v__==title_) { return; }
    title_=std::move(v__);
    titleChanged();
    update();
}

void BarChart::_on_size_changed(){
    if(size_ == size() ){return;}
    size_ = size();
    chart_->setPos( 0,toolBarHeight() );
    auto _height_=size_.height()-toolBarHeight();
    chart_->resize( size_.width(), _height_>0?_height_:toolBarHeight() );
    if (data_.size()>0) {
        bar_->setBarWidth(1);
    }
}

void BarChart::paint(
        QPainter *painter,
        const QStyleOptionGraphicsItem *option,
        QWidget *widget){
    painter->setPen( QPen(QColor(0,0,0,0) , 0) );
    painter->setBrush( theme_color_ );
    painter->drawRect( 0,0,size().width(),size().height() );

    if(title_.isEmpty()==false)
    {
        painter->setPen( QPen(QColor(0,0,0,250),1) );
        painter->setBrush( QColor(0,0,0,250) );
        {
            auto _font_=painter->font();
            _font_.setPixelSize( toolBarHeight()-1 );
            painter->setFont(_font_);
        }
        painter->drawText(
            QRectF( toolBarHeight()*1,0 ,size().width(),toolBarHeight()),
            title_);
    }

    return;
    (void)widget;(void)option;
}

void BarChart::mousePressEvent(QGraphicsSceneMouseEvent * ) {
    QGraphicsScene * _sc_=scene();
    ImageScene * _scene_=qobject_cast<ImageScene *>(_sc_);
    if (_scene_) {
        _scene_->setTopItem(this);
    }
}

BarChart::~BarChart(){

}

/*

*/

