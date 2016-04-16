#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>
#include "particlesystem.h"
class Scene : public QGLWidget
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

    void mouseMoveEvent(QMouseEvent* pe);


private:
    GLint _angle;
    ParticleSystem _ps;
    ParticleSystem _tail;

    glm::vec2 _hor;
    glm::vec2 _vert;
    glm::vec2 _depth;

    glm::vec3 ScreenToWorld(QPoint p);
    void InitTextures();
    void drawAxis();
};

#endif // SCENE_H
