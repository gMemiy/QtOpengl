#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include "firework.h"
#include "cloud.h"

class Scene : public QGLWidget // класс для работы с  окном
{
    Q_OBJECT
public:
    Scene(QWidget *parent = 0);

public slots:
    void Update();

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

    void mousePressEvent(QMouseEvent *pe);


private:

    FireWork fw; // фейерверк

    bool isAllLoad;
    // размеры сцены
    glm::vec2 _hor; // горизонталь
    glm::vec2 _vert; // вертикаль
    glm::vec2 _depth; // глубина

    GLuint _backGround; // задний фон
    GLuint _foreGround; // пережний фон
    GLuint _spot; // текстура частицы
    GLuint _cloud[2]; // текстуры облаков

    CloudManager cloud; // менеджер облаков

    glm::vec3 ScreenToWorld(QPoint p); // перевод оконнх координат в координаты сцены
    GLuint InitTexture(QString path); // загрузка текстуры из файла
    void DrawBackGround(GLuint texture); // рисует прямоугольник на весь экран, с заданной текстурой
};

#endif // SCENE_H
