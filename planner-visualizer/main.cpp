#include <QApplication>

#include "MainWindow.hpp"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    app.setOrganizationName("RoboJackets");
    app.setApplicationName("Path Planner Visualizer");

    MainWindow win;
    win.show();

    return app.exec();
}
