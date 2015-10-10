#include "christmas.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Christmas w;
    w.show();

    return a.exec();
}
