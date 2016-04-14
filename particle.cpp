#include "particle.h"

Particle::Particle(glm::vec3 pos , float lifeTime, float size, float speedMax) : _pos(pos), _size(size), _timeLife(lifeTime)
{
    float speed = (float)((float)(rand() % 10) * speedMax - 5.f * speedMax) / (10.f );
    _vel.x = speed;
    speed = (float)((float)(rand() % 10) * speedMax - 5.f * speedMax) / (10.f);
    _vel.y = speed;
    speed = (float)((float)(rand() % 10) * speedMax - 5.f * speedMax) / (10.f);
    _vel.z = speed;

    _timer = _timeLife;
}

void Particle::Draw()
{
    glColor4f(0,0,0, _timer / _timeLife);
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
    if (_timer > 0)
    {
        _pos.x += _vel.x * dt;
        _pos.y += _vel.y * dt;
        _pos.z += _vel.z * dt;
    }

    _timer -= dt;
}

bool Particle::IsAlive()
{
    return _timer > 0;
}
