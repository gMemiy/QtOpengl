#include "particlesystem.h"

ParticleSystem::ParticleSystem(int count, float lifeime,  float speed, float size) :
    _pos(0)
  , _count(count)
  , _lifeTime(lifeime)
  , _timer(0)
  , _speed(speed)
  , _color(glm::vec4(1,1,1,1))
  , _size(size)
  , _vel(0)
{
    _spawnTime = _lifeTime/_count;
}

void ParticleSystem::AddParticle()
{
    QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _lifeTime, _size, _speed));
    p->SetColor(_color);
    _particles.push_back(p);
}

void ParticleSystem::Update(float dt)
{

    _pos += _vel*dt;

    _timer += dt;
    if (_timer >= _spawnTime)
    {
        int count = _timer / _spawnTime;
        _timer = 0;
        for (int i = 0; i < count; ++i)
        {
            AddParticle();
        }
    }

    std::vector<int> dead;
    int i = 0;
    for ( std::vector< QSharedPointer<Particle> >::iterator p = _particles.begin(); p != _particles.end(); ++p, ++i)
    {
        (*p)->Update(dt);
        if (!(*p)->IsAlive())
        {
            dead.push_back(i);
        }
    }

    while (!dead.empty())
    {
        int index = dead.back();
        dead.pop_back();
        _particles.erase(_particles.begin() + index);
    }

}

void ParticleSystem::Draw()
{
    for ( std::vector< QSharedPointer<Particle> >::iterator p = _particles.begin(); p != _particles.end(); ++p)
    {
        (*p)->Draw();
    }
}

void ParticleSystem::SetPos(glm::vec3 pos)
{
    _pos = pos;
}


void ParticleSystem::SetSpeed(float speed)
{
    _speed = speed;
}

void ParticleSystem::SetColor(glm::vec4 color)
{
    _color = color;
}

int ParticleSystem::GetCount()
{
    return _particles.size();
}

void ParticleSystem::SetSize(float size)
{
    _size = size;
}

void ParticleSystem::SetLifeTime(float lifeTime)
{
    _lifeTime = lifeTime;
}

void ParticleSystem::SetSpeed(glm::vec3 speed)
{
    _vel = speed;
}

