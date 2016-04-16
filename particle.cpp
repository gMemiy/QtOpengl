#include "particle.h"
Object::Object(glm::vec3 pos, glm::vec3 vel, glm::vec4 color):
    _pos(pos)
  , _vel(vel)
  , _color(color)
  , _gravity(glm::vec3(0))
{

}

Object::~Object()
{

}

void Object::SetPos(glm::vec3 pos)
{
    _pos = pos;
}

void Object::SetVelocity(glm::vec3 vel)
{
    _vel = vel;
}

void Object::Update(float dt)
{
    _pos += _vel * dt;
    _vel += _gravity * dt;
}

void Object::SetGravity(glm::vec3 gravity)
{
    _gravity = gravity;
}

void Object::SetColor(glm::vec4 color)
{
    _color = color;
}

void Object::Draw()
{

}

glm::vec3 Object::GetPos()
{
    return _pos;
}

///////////////////////////////////////////////////////////////////////////////

Particle::Particle(glm::vec3 pos , float lifeTime, float size, float maxSpeed) :
    Object(pos)
  ,  _size(size)
  ,  _lifeTime(lifeTime)
  , _lifeTimer(lifeTime)
{
    SetMaxSpeed(maxSpeed);
}

Particle::~Particle()
{

}

void Particle::Draw()
{

    float alpha = _lifeTimer / _lifeTime + 0.2f;
    _color.a *= alpha;

    glColor4fv(&_color[0]);
    float size = _size / 2;
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex3fv(&glm::vec3(_pos.x - size, _pos.y - size, _pos.z)[0]);
        glTexCoord2f(0,1);
        glVertex3fv(&glm::vec3(_pos.x - size, _pos.y + size, _pos.z)[0]);
        glTexCoord2f(1,0);
        glVertex3fv(&glm::vec3(_pos.x + size, _pos.y - size, _pos.z)[0]);
        glTexCoord2f(1,1);
        glVertex3fv(&glm::vec3(_pos.x + size, _pos.y + size, _pos.z)[0]);
    glEnd();
}

void Particle::Update(float dt)
{
    if (_lifeTimer >= 0)
    {
        Object::Update(dt);
        if (_lifeTime > 0)
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

void Particle::SetMaxSpeed(float maxSpeed)
{
    float speed = (float)((float)(rand() % 10) * maxSpeed - 5.f * maxSpeed) / (10.f );
    _vel.x = speed;
    speed = (float)((float)(rand() % 10) * maxSpeed - 5.f * maxSpeed) / (10.f);
    _vel.y = speed;
    speed = (float)((float)(rand() % 10) * maxSpeed - 5.f * maxSpeed) / (10.f);
    _vel.z = speed;
}

void Particle::SetLifeTime(float lifeTime)
{
    _lifeTime = lifeTime;
}
