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

    InitFireWork();

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


void Scene::InitFireWork() // тут нахардкожено, вместо работы с фалом настроек
{
    for (int i = 4; i <= 7; ++i) // сигнальные ракеты по 4-7 штук
    {
        auto b = QSharedPointer<BulletType>(new BulletType());
        b->childCount = 400;
        b->childLifeTime = 5;
        b->childSize = 1;
        b->childSpeed = 1;
        b->lifeTime = 2;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _fw.AddBulletType(b);
    }

    for (int i = 3; i <= 5; ++i) // звёзды по 3, 4 и 5 лучей
    {
        auto b = QSharedPointer<BulletType>(new BulletType());
        b->childCount = 400;
        b->childLifeTime = 5;
        b->childSize = 1;
        b->childSpeed = 5;
        b->lifeTime = 1.5f;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _fw.AddBulletType(b);
    }


    auto b = QSharedPointer<BulletType>(new BulletType()); // шары
    b->childCount = 100;
    b->childLifeTime = 2.f;
    b->childSize = 1;
    b->childSpeed = 40;
    b->lifeTime = .1f;
    b->bulletCount = 3;
    b->speed = 20;
    b->bulletCount = 5;
    _fw.AddBulletType(b);

    for (int i = 3; i <= 5; ++i) // искорки
    {
        auto b = QSharedPointer<BulletType>(new BulletType());
        b->childCount = 50;
        b->childLifeTime = 1;
        b->childSize = 1;
        b->childSpeed = 50;
        b->lifeTime = 2.f;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _fw.AddBulletType(b);
    }

    _fw.AddColor(glm::vec4(1.f, 0.09f, 0.14f, 1.f)); // каждый
    _fw.AddColor(glm::vec4(1.f, .6f, 0.07f, 1.f)); // охотник
    _fw.AddColor(glm::vec4(1.f, 1.f, 0.3f, 1.f)); // желает
    _fw.AddColor(glm::vec4(0.09f, 1.0f, 0.34f, 1.f)); // знать
    _fw.AddColor(glm::vec4(0.09f, 0.74f, 1.f, 1.f)); // где
    _fw.AddColor(glm::vec4(0.25f, 0.4f, 1.f, 1.f)); // сидит
    _fw.AddColor(glm::vec4(1.f, .0f, 0.8f, 1.f)); // фазан

    BulletType first;
    first.childCount = 400;
    first.childLifeTime = 5;
    first.childSize = 1.5f;
    first.childSpeed = 1;
    first.lifeTime = 2;
    first.bulletCount = 3;
    first.speed = 40;

    _fw.SetFirst(first);



    if (_isAllLoad)
    {
        _cloud.AddTexture(_cloudTextures[0]);
        _cloud.AddTexture(_cloudTextures[1]);
        _cloud.SetRange(_hor);
        _cloud.SetVerticalRange(glm::vec2(_vert.y * 0.6f, _vert.y * 1.1f));
        _cloud.SetMaxSpeed(1.5f);
        _cloud.SetMaxSize(60);
        _cloud.SetColor(glm::vec4(0.2f, 0.2f, 0.2f, 0.9f));
        _cloud.AddClouds(30);
    }
}

