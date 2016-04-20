#include "particle.h"
#include "glm/gtx/rotate_vector.hpp"

///////////////////////////////////////////////////////////////////////////////

Particle::Particle() : Object()
  , _lifeTime(0)
  , _lifeTimer(_lifeTime)
  , _size(1)
{

}

Particle::Particle(glm::vec2 pos , float lifeTime, float size, float maxSpeed) :
    Object()
  ,  _size(size)
  ,  _lifeTime(lifeTime)
  , _lifeTimer(lifeTime)
{
    _pos = pos;
    SetMaxSpeed(maxSpeed);
}

Particle::~Particle()
{

}

void Particle::Draw()
{

    float alpha = _lifeTimer / _lifeTime + 0.1f;
    _color.a *= alpha;

    glColor4fv(&_color[0]);
    float size = _size / 2;
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex2fv(&glm::vec2(_pos.x - size, _pos.y - size)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(_pos.x - size, _pos.y + size)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(_pos.x + size, _pos.y - size)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(_pos.x + size, _pos.y + size)[0]);
    glEnd();
}

void Particle::Update(float dt)
{
    if (_lifeTimer >= 0)
    {
        Object::Update(dt);
        if (_lifeTime > 0) // частица с _lifeTime = 0 живёт вечно (как и система частиц)
        {
            _lifeTimer -= dt;
        }
    }


}

bool Particle::IsAlive()
{
    return _lifeTimer >= 0;
}

void Particle::SetSize(float size)
{
    _size = size;
}

float Particle::GetSize()
{
    return _size;
}

void Particle::SetMaxSpeed(float maxSpeed) // частица буедт иметь скорость в случайном направлении
{
    float speed = (float)((float)(rand() % 10) * maxSpeed - 5.f * maxSpeed) / (10.f );

    ;
    glm::vec3 vec = glm::rotateZ(glm::vec3(speed, 0, 0), (float)(rand() % 360) / 180.f * 3.14f);
    _vel.x = vec.x;
    _vel.y = vec.y;

}

void Particle::SetLifeTime(float lifeTime)
{
    _lifeTime = lifeTime;
    _lifeTimer = lifeTime;
}

