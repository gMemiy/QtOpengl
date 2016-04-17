#include "scene.h"


GLuint Scene::InitTexture(QString path)
{
    GLuint textureId(0);

    QImage pm(path);
    pm = QGLWidget::convertToGLFormat(pm);

    glGenTextures(1, &textureId);

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)pm.width(), (GLsizei)pm.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pm.bits());

    glBindTexture(GL_TEXTURE_2D, textureId);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MULT);

    return textureId;
}

Scene::Scene(QWidget *parent) : QGLWidget(parent)
{
    _angle = 0;
}

void Scene::initializeGL()
{
    //qglClearColor(Qt::gray);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    _spot = InitTexture("spot.png");
    _backGround = InitTexture("11.jpg");
    _foreGround = InitTexture("11.png");

}

void Scene::resizeGL(int w, int h)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    _hor = glm::vec2(-50, 50);
    _vert = glm::vec2(-50, 50);
    _depth = glm::vec2(2, -2);

    glOrtho(_hor.x, _hor.y, _vert.x, _vert.y, _depth.x, _depth.y);
    glViewport(0, 0, w, h);
}

void Scene::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    DrawBackGround(_backGround);

    glBindTexture(GL_TEXTURE_2D, _spot);
    /*drawAxis();

    glRotated(_angle, 1, 0, 0);


    glBindTexture(GL_TEXTURE_2D, textureId[0]);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_TEXTURE_COORD_ARRAY);
    //glEnableClientState(GL_COLOR_ARRAY);

    glBindTexture(GL_TEXTURE_2D, textureId[0]);

    glVertexPointer(3, GL_FLOAT, 0, VertexArray);
    // указываем, откуда нужно извлечь данные о массиве цветов вершин
    glTexCoordPointer(2, GL_FLOAT, 0, textCoord);
   // glColorPointer(3, GL_FLOAT, 0, ColorArray);
    // используя массивы вершин и индексов, строим поверхноси
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_BYTE, IndexArray);

    glDisableClientState(GL_TEXTURE_COORD_ARRAY);
    glDisableClientState(GL_VERTEX_ARRAY);*/

    fw.Draw();
    DrawBackGround(_foreGround);
}


void Scene::drawAxis()
{
}

void Scene::Update()
{
    static float t = 0.f;
    static float oldTime;
    static QTime *timer;
    if (!timer)
    {
        timer = new QTime();
        timer->start();
        oldTime = (float)timer->msecsTo(QTime::currentTime()) / 1000.f;
    }
    float time = (float)timer->msecsTo(QTime::currentTime()) / 1000.f;


    float dt = time - oldTime;
    oldTime = time;

    fw.Update(dt);

    _angle += 1;
    updateGL();

    static int fps = 0;
    fps++;
    t += dt;
    if (t >= 1)
    {
        int pCount = fw.ParticleCount();
        setWindowTitle(QString::number(fps) + " " + QString::number(pCount));
        t = 0;
        fps = 0;
    }
}

void Scene::mousePressEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
    fw.Push(ScreenToWorld(pe->pos()), 1);
}

glm::vec3 Scene::ScreenToWorld(QPoint p)
{
    float x = (float)p.x() / (float)width() * (float)(abs(_hor.x) + abs(_hor.y)) - (float)abs(_hor.x);
    float y = ((float)height() - (float)p.y()) / (float)height() * (float)(abs(_vert.x) + abs(_vert.y)) - (float)abs(_vert.x);
    return glm::vec3( x, y, 0.f);
}

void Scene::DrawBackGround(GLuint texture)
{
    glBindTexture(GL_TEXTURE_2D, texture);
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex3fv(&glm::vec3(_hor.x, _vert.x, 0)[0]);
        glTexCoord2f(0,1);
        glVertex3fv(&glm::vec3(_hor.x, _vert.y, 0)[0]);
        glTexCoord2f(1,0);
        glVertex3fv(&glm::vec3(_hor.y, _vert.x, 0)[0]);
        glTexCoord2f(1,1);
        glVertex3fv(&glm::vec3(_hor.y, _vert.y, 0)[0]);
    glEnd();
}

void Scene::InitShader()
{
    shader = new QGLShaderProgram(this);


   shader->addShaderFromSourceFile( QGLShader::Fragment, "fShader.fsh" );
   shader->addShaderFromSourceFile( QGLShader::Vertex, "vShader.glsl" );


   // Bind vertex array object
   QOpenGLVertexArrayObject *vao = new QOpenGLVertexArrayObject( this );
   vao->bind();

   // Bind shader pipeline for use
   shader->link();
   shader->bind();

}
