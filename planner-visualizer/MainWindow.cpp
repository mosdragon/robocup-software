#include "MainWindow.hpp"

#include <iostream>

using namespace std;

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    _ui.setupUi(this);
    _ui.fieldBackgroundView->setFieldDimensions(
        Field_Dimensions::Double_Field_Dimensions);
    _ui.fieldBackgroundView->drawingCallback = [&](QPainter& painter) {
        _ui.fieldBackgroundView->drawRobot(painter, Geometry2d::Point(0, 1), Qt::blue, 5);
        // cout<< "Drawing robot" << endl;
    };
}
