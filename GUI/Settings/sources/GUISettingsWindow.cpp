
#include <GUISettingsWindow.h>


GUISettingsWindow::GUISettingsWindow(QWidget *parent) : QWidget(parent), qvbox_(new QVBoxLayout(this)), enableDarkMode_(new Switch("Enable dark mode")) {
    enableDarkMode_->setChecked(true);

    qvbox_->addWidget(enableDarkMode_);
}

GUISettingsWindow::~GUISettingsWindow() {
    delete qvbox_;
    delete enableDarkMode_;
}
