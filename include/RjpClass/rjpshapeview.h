#ifndef RJPSHAPEVIEW_H
#define RJPSHAPEVIEW_H

#include <QWidget>

class RjpShapeView : public QWidget
{
    Q_OBJECT
public:
    explicit RjpShapeView(QWidget *parent = 0);
    virtual void paintEvent(QPaintEvent* event);
};

#endif // RJPSHAPEVIEW_H
