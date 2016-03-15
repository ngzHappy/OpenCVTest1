#ifndef WINDOW_HPP
#define WINDOW_HPP

#include <MainWindow.hpp>

class Window : public MainWindow
{
    Q_OBJECT
public:
    explicit Window(QWidget *parent = 0);

signals:

public slots:
};

#endif // WINDOW_HPP
