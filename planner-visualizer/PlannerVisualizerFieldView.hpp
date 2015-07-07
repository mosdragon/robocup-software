#include "FieldBackgroundView.hpp"
#include <functional>

class PlannerVisualizerFieldView : public FieldBackgroundView {
public:
    PlannerVisualizerFieldView(QWidget* parent = nullptr);

    /// @drawingCallback is called each time this view repaints and allows a
    /// client to draw additional objects.  The painter passed to the callback
    /// is initialized to world coordinates.
    typedef std::function<void(QPainter& painter)> DrawingCallback;
    DrawingCallback drawingCallback;

    void drawRobot(QPainter& p, const Geometry2d::Point& pos,
                   const QColor& color, int shellID);

protected:
    virtual void paintEvent(QPaintEvent* e) override;
};
