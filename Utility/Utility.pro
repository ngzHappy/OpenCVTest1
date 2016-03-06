CONFIG += c++14
CONFIG += console
CONFIG += no_batch

QT += core
QT += gui
QT += widgets
QT += charts

TARGET = Utility
TEMPLATE = app

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/BarChart.cpp
SOURCES += $$PWD/ImageItem.cpp
SOURCES += $$PWD/ImageScene.cpp
SOURCES += $$PWD/MainWindow.cpp
SOURCES += $$PWD/ImageView.cpp

HEADERS  += $$PWD/MainWindow.hpp
HEADERS  += $$PWD/BarChart.hpp
HEADERS  += $$PWD/ImageItem.hpp
HEADERS  += $$PWD/OpencvQtUtility.hpp
HEADERS  += $$PWD/ImageScene.hpp
HEADERS  += $$PWD/ImageView.hpp

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
win32 :{
DEFINES += LOCAL_CODEC_=\\\"GBK\\\"
}else{
DEFINES += LOCAL_CODEC_=\\\"UTF-8\\\"
}

include( opencv2.pri )


DISTFILES += $$PWD/../Images/000000.jpg
DISTFILES += $$PWD/../Images/000001.jpg
DISTFILES += $$PWD/../Images/000002.jpg
DISTFILES += $$PWD/../Images/000003.jpg




