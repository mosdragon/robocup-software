#include "PlannerVisualizerFieldView.hpp"

#include <Constants.hpp>

PlannerVisualizerFieldView::PlannerVisualizerFieldView(QWidget* parent)
    : FieldBackgroundView(parent) {}

void PlannerVisualizerFieldView::paintEvent(QPaintEvent* e) {
    // superclass drawing
    FieldBackgroundView::paintEvent(e);

    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);

    setupWorldSpace(&p);

    if (drawingCallback) drawingCallback(p);
}

void PlannerVisualizerFieldView::drawRobot(QPainter& p,
                                           const Geometry2d::Point& pos,
                                           const QColor& color, int shellID) {
    QPen pen(color);
    pen.setWidth(0);
    p.setPen(pen);
    p.drawEllipse(QPointF(pos.x, pos.y), Robot_Radius, Robot_Radius);
    // FIXME: geometry here is wrong
}
