CONFIG += c++14
CONFIG += console
CONFIG += no_batch

QT += core
QT += gui
QT += widgets
QT += charts

TARGET = LUT
TEMPLATE = app


HEADERS  += $$PWD/Window.hpp

SOURCES += $$PWD/main.cpp
SOURCES += $$PWD/Window.cpp

SOURCES += $$PWD/../Utility/ImageItem.cpp
SOURCES += $$PWD/../Utility/ImageScene.cpp
SOURCES += $$PWD/../Utility/MainWindow.cpp
SOURCES += $$PWD/../Utility/ImageView.cpp
SOURCES += $$PWD/../Utility/BarChart.cpp

HEADERS  += $$PWD/../Utility/BarChart.hpp
HEADERS  += $$PWD/../Utility/MainWindow.hpp
HEADERS  += $$PWD/../Utility/ImageItem.hpp
HEADERS  += $$PWD/../Utility/OpencvQtUtility.hpp
HEADERS  += $$PWD/../Utility/ImageScene.hpp
HEADERS  += $$PWD/../Utility/ImageView.hpp

INCLUDEPATH += $$PWD/../Utility

DEFINES += BUILD_PATH_=\\\"$$PWD\\\"
win32 :{
DEFINES += LOCAL_CODEC_=\\\"GBK\\\"
}else{
DEFINES += LOCAL_CODEC_=\\\"UTF-8\\\"
}

include( $$PWD/../Utility/opencv2.pri )
