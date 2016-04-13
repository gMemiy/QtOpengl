#include <QApplication>
#include <scene.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Scene s;
    s.show();
    return a.exec();
}
