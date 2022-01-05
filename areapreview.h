#ifndef AREAPREVIEW_H
#define AREAPREVIEW_H

#include <QtGui>
#include <QWidget>

class AreaPreview : public QWidget
{
    Q_OBJECT
public:
    explicit AreaPreview(QWidget *parent = nullptr);
    void changeArea(int left, int top, int right, int down);
protected:
    void paintEvent(QPaintEvent *) override;
public slots:
private:
    QRect currentArea;
    QRect scaleArea(int left, int top, int right, int down);
    const float max_left = 0;
    const float max_top = 0;
    const float max_right = 15200;
    const float max_down = 9500;
};

#endif // AREAPREVIEW_H
