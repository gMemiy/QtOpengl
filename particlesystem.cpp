#include "particlesystem.h"

ParticleSystem::ParticleSystem(int count, float lifeime) : _pos(0), _count(count), _lifeTime(lifeime), _timer(0)
{
    _spawnTime = _lifeTime/_count;
}

void ParticleSystem::AddParticle()
{
    _particles.push_back(QSharedPointer<Particle>(new Particle(_pos, _lifeTime)));
}

void ParticleSystem::Update(float dt)
{
    _timer += dt;
    if (_timer >= _spawnTime)
    {
        _timer = 0;
        AddParticle();
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
