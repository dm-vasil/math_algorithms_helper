#include "mainwindow.h"

int main(int argc, char *argv[])
{
    int currentExitCode = 0;
    do { //Запуск в цикле для реализации перезапуска
        QApplication a(argc, argv);
        Window MainWindow;
        MainWindow.show();
        currentExitCode = a.exec();
    } while(currentExitCode == Window::EXIT_CODE_REBOOT); //При выходе с кодом-индикатором перезапускаем
    return currentExitCode;
}
