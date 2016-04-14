#include <QApplication>
#include <scene.h>
#include <QTimer>
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    srand(0);

    Scene *s = new Scene();
    QTimer *timer = new QTimer();
    timer->start(1000/60);

    QObject::connect(timer, SIGNAL(timeout()), s, SLOT(Update()));
    s->show();
    return a.exec();
}
