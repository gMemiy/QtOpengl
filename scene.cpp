#include "scene.h"



GLuint textureId[1];

void Scene::InitTextures()
{
    textureId[0] = 15;

    QImage pm(QString("spot.png"));
    pm = QGLWidget::convertToGLFormat(pm);
    //textureId = bindTexture(pm, GL_TEXTURE_2D, GL_RGBA);

    glGenTextures(1, textureId); // создаём два имени и записываем их в массив

       // создаём и связываем текстурные объекты с состоянием текстуры
       // 1-ый текстурный объект
       // создаём и связываем 1-ый текстурный объект с последующим состоянием текстуры
    glBindTexture(GL_TEXTURE_2D, textureId[0]);
       // связываем текстурный объект с изображением

    glTexImage2D(GL_TEXTURE_2D, 0, 4, (GLsizei)pm.width(), (GLsizei)pm.height(), 0, GL_RGBA, GL_UNSIGNED_BYTE, pm.bits());

    glBindTexture(GL_TEXTURE_2D, textureId[0]);
    // задаём линейную фильтрацию вблизи:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
       // задаём линейную фильтрацию вдали:
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
}

Scene::Scene(QWidget *parent) : QGLWidget(parent)
{
    _angle = 0;
}

void Scene::initializeGL()
{
    qglClearColor(Qt::gray);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_BLEND);
    InitTextures();
    _ps.SetSpeed(0.2f);
    _ps.SetSize(0.5f);
    _ps.SetSpeed(glm::vec3(0, 5, 0));
    _ps.SetLifeTime(5.f);
    _tail.SetSpeed(.9f);
    _tail.SetColor(glm::vec4(0.8f, 0.9f, 0.8f, 1.f));
    _tail.SetSize(0.3f);
    _tail.SetSpeed(glm::vec3(0, 2, 0));
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

    glBindTexture(GL_TEXTURE_2D, textureId[0]);
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

    _ps.Draw();
    _tail.Draw();

}


void Scene::drawAxis()
{
   // устанавливаем ширину линии приближенно в пикселях
   glLineWidth(3.0f);
   // до вызова здесь команды ширина была равна 1 пикселю по умолчанию

   // устанавливаем цвет последующих примитивов
   glColor4f(1.00f, 0.00f, 0.00f, 1.0f);
   // ось x красного цвета
   glBegin(GL_LINES); // построение линии
      glVertex3f( 1.0f,  0.0f,  0.0f); // первая точка
      glVertex3f(-1.0f,  0.0f,  0.0f); // вторая точка
   glEnd();

   QColor halfGreen(0, 128, 0, 255);
   qglColor(halfGreen);
   glBegin(GL_LINES);
      // ось y зеленого цвета
      glVertex3f( 0.0f,  1.0f,  0.0f);
      glVertex3f( 0.0f, -1.0f,  0.0f);

      glColor4f(0.00f, 0.00f, 1.00f, 1.0f);
      // ось z синего цвета
      glVertex3f( 0.0f,  0.0f,  1.0f);
      glVertex3f( 0.0f,  0.0f, -1.0f);
   glEnd();
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

    _ps.Update(dt);
    _tail.Update(dt);

    _angle += 1;
    updateGL();

    static int fps = 0;
    fps++;
    t += dt;
    if (t >= 1)
    {
        int pCount = _tail.GetCount() + _ps.GetCount();
        setWindowTitle(QString::number(fps) + " " + QString::number(pCount));
        t = 0;
        fps = 0;
    }
}

void Scene::mouseMoveEvent(QMouseEvent* pe) // нажатие клавиши мыши
{
   // при нажатии пользователем кнопки мыши переменной ptrMousePosition
   // будет присвоена координата указателя мыши
   //_ps.SetPos(ScreenToWorld(pe->pos()));
    //_tail.SetPos(ScreenToWorld(pe->pos()));
   // ptrMousePosition = (*pe).pos(); // можно и так написать
}

glm::vec3 Scene::ScreenToWorld(QPoint p)
{
    float x = (float)p.x() / (float)width() * (float)(abs(_hor.x) + abs(_hor.y)) - (float)abs(_hor.x);
    float y = ((float)height() - (float)p.y()) / (float)height() * (float)(abs(_vert.x) + abs(_vert.y)) - (float)abs(_vert.x);
    return glm::vec3( x, y, 0.f);
}
