#include <QApplication>
#include <Windows.h>

#include "Widgets/CMainWidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
    CMainWidget w;
    w.ShowCenter();
    CoUninitialize(); // «Â¿ÌCOM
    return a.exec();
}