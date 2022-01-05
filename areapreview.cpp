#include "areapreview.h"
#include "qpainter.h"
#include "qdebug.h"

AreaPreview::AreaPreview(QWidget *parent)
    : QWidget{parent}
{
    setBackgroundRole(QPalette::Base);
    setAutoFillBackground(true);
    update();
}

void AreaPreview::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    QSize size = QWidget::size();
    p.setPen(Qt::black);
    p.drawRect(QRect(0, 0, size.width()-1, size.height()-1));
    p.setPen(Qt::red);
    p.drawRect(currentArea);
}

QRect AreaPreview::scaleArea(int left, int top, int right, int down)
{
    const QSize drawingAreaSize = QWidget::size();
    const float ratio_vertical = (drawingAreaSize.height())/(max_down - max_top);
    const float ratio_horizontal = (drawingAreaSize.width())/(max_right - max_left);
    int width = (right-left)*ratio_horizontal;
    int height = (down-top)*ratio_vertical;
    const int newLeft = left*ratio_horizontal;
    const int newTop = top*ratio_vertical;
    if (width == drawingAreaSize.width()) {
        width--;
    }
    if (height == drawingAreaSize.height()) {
        height--;
    }
    QRect area = {newLeft, newTop, width, height};
    return area;
}

void AreaPreview::changeArea(int left, int top, int right, int down)
{
    currentArea = scaleArea(left, top, right, down);
    update();
}
