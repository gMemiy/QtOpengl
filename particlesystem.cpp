#include "particlesystem.h"

ParticleSystem::ParticleSystem(glm::vec3 pos, int count, float lifeime,  float speed, float size) : Particle(pos, lifeime, size)
  , _count(count)
  , _speed(speed)
{
    _spawnTime = _timeLife/_count;
}

void ParticleSystem::AddParticle()
{
    QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _timeLife, _size, _speed));
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

void ParticleSystem::SetSpeed(float speed)
{
    _speed = speed;
}


int ParticleSystem::GetCount()
{
    return _particles.size();
}

void ParticleSystem::SetSpeed(glm::vec3 speed)
{
    _vel = speed;
}

