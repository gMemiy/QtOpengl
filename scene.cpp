#include "scene.h"



GLuint Scene::InitTexture(QString path)
{
    GLuint textureId(0);

    QImage pm(path);
    if (pm.isNull()) // проверка на загрузку текстуры
    {
        setWindowTitle("no image: " + path);
        _isAllLoad = false;
        return 0;
    }
    pm = QGLWidget::convertToGLFormat(pm);

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)pm.width(), (GLsizei)pm.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pm.bits());

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    return textureId;
}

Scene::Scene(QWidget *parent) : QGLWidget(parent)
{
    _isAllLoad = true;
    resize(1024, 768);
    _timer = QSharedPointer<QTime>(new QTime());
    _timer->start();
    _oldTime = (float)_timer->msecsTo(QTime::currentTime()) / 1000.f;

    _sec = 0;
    _fps = 0;
}

void Scene::initializeGL()
{

    _hor = glm::vec2(-50, 50);
    _vert = glm::vec2(-50, 50);
    _depth = glm::vec2(2, -2);

    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);

    QString path("images/");
    _spot = InitTexture(path + "spot.png");
    _backGround = InitTexture(path + "background.jpg");
    _foreGround = InitTexture(path + "forest.png");
    _cloudTextures[0] = InitTexture(path + "cloud.png");
    _cloudTextures[1] = InitTexture(path + "cloud1.png");

    if (_isAllLoad)
    {
        _cloud.AddTexture(_cloudTextures[0]);
        _cloud.AddTexture(_cloudTextures[1]);
        _cloud.SetRange(_hor);
        _cloud.AddClouds(30);
    }

}

void Scene::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glOrtho(_hor.x, _hor.y, _vert.x, _vert.y, _depth.x, _depth.y);
    glViewport(0, 0, w, h);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    if (!_isAllLoad) // не загрузили текстуру? тогда и рисовать нечего
    {
        return;
    }

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawBackGround(_backGround);

    glBindTexture(GL_TEXTURE_2D, _spot);



    _fw.Draw();
    glTexEnvi(GL_TEXTURE_ENV, GL_COMBINE_RGB, GL_MODULATE);
    _cloud.Draw();
    DrawBackGround(_foreGround);
}

float Scene::GetDt()
{
    float time = (float)_timer->msecsTo(QTime::currentTime()) / 1000.f;
    float dt = time - _oldTime;
    _oldTime = time;
    return dt;
}

void Scene::UpdateStatistic(float dt)
{
    _fps++;
    _sec += dt;
    if (_sec >= 1)
    {
        int pCount = _fw.ParticleCount();
        setWindowTitle("fps = " + QString::number(_fps) + " | particles count = " + QString::number(pCount));
        _sec -= 1;
        _fps = 0;
    }
}

void Scene::Update()
{
    if (!_isAllLoad) // и обновлять тоже. (хотя можно было бы)
    {
        return;
    }

    float dt = GetDt();

    _fw.Update(dt);
    _cloud.Update(dt);

    updateGL();

    UpdateStatistic(dt);
}

void Scene::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    _fw.Push(ScreenToWorld(pe->pos()), 1);
}

glm::vec2 Scene::ScreenToWorld(QPoint p)
{
    float x = (float)p.x() / (float)width() * (float)(abs(_hor.x) + abs(_hor.y)) - (float)abs(_hor.x);
    float y = ((float)height() - (float)p.y()) / (float)height() * (float)(abs(_vert.x) + abs(_vert.y)) - (float)abs(_vert.x);
    return glm::vec2( x, y);
}

void Scene::DrawBackGround(GLuint texture)
{
    if (!_isAllLoad)
    {
        return;
    }

    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(_hor.x, _vert.x)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(_hor.x, _vert.y)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(_hor.y, _vert.x)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(_hor.y, _vert.y)[0]);
    glEnd();
}

