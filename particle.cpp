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

glm::vec4 Object::GetColor()
{
    return _color;
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

    float alpha = _lifeTimer / _lifeTime + 0.1f;
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

float Particle::GetSize()
{
    return _size;
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


Cloud::Cloud(glm::vec3 pos, glm::vec3 vel): Object(pos, vel)
  , _worldWidth(-1, 1)
  , _texture(0)
{

}

void Cloud::Draw()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    glColor4fv(&_color[0]);
    float sx = _size.x / 2.f;
    float sy = _size.y / 2.f;
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex3fv(&glm::vec3(_pos.x - sx, _pos.y - sy / 2.f, 0)[0]);
        glTexCoord2f(0,1);
        glVertex3fv(&glm::vec3(_pos.x - sx, _pos.y + sy, 0)[0]);
        glTexCoord2f(1,0);
        glVertex3fv(&glm::vec3(_pos.x + sy, _pos.y - sy, 0)[0]);
        glTexCoord2f(1,1);
        glVertex3fv(&glm::vec3(_pos.x + sy, _pos.y + sy, 0)[0]);
    glEnd();

}

void Cloud::Update(float dt)
{
    Object::Update(dt);
    if (_pos.x > _worldWidth.y + _size.x / 2.f)
    {
        _pos.x = _worldWidth.x - _size.x / 2.f;
    }
    if (_pos.x <  _worldWidth.x - _size.x / 2.f)
    {
        _pos.x = _worldWidth.y + _size.x / 2.f;
    }
}

void Cloud::SetSize(glm::vec2 size)
{
    _size = size;
}

void Cloud::SetWorldWidth(glm::vec2 width)
{
    _worldWidth = width;
}

void Cloud::SetTexture(GLuint texture)
{
    _texture = texture;
}
