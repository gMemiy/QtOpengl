#ifndef SCENE_H
#define SCENE_H

#include <QGLWidget>
#include <QtOpenGL>

class Scene : public QGLWidget
{
    Q_OBJECT
public:
    Scene(QWidget *parent = 0);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int w, int h) override;

private:
    void drawAxis();
};

#endif // SCENE_H
