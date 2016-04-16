#include "particlesystem.h"

ParticleSystem::ParticleSystem(glm::vec3 pos, int count, float lifeime,  float speed, float size) : Particle(pos, lifeime, size)
  , _count(count)
  , _speed(speed)
{
    SetChildLifeTime(1);
}

void ParticleSystem::AddParticle()
{
    QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _childLifeTime, _size, _speed));
    p->SetColor(_color);
    _particles.push_back(p);
}

void ParticleSystem::Update(float dt)
{

    Particle::Update(dt);

    if (_lifeTimer >= 0)
    {
        _spawnTimer += dt;
        if (_spawnTimer >= _spawnTime)
        {
            int count = _spawnTimer / _spawnTime;
            _spawnTimer = 0;
            for (int i = 0; i < count; ++i)
            {
                AddParticle();
            }
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

bool ParticleSystem::IsAlive()
{
    return _lifeTimer > 0 && !_particles.empty();
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

void ParticleSystem::SetChildLifeTime(float lifeTime)
{
    _childLifeTime = lifeTime;
    _spawnTime = _childLifeTime / _count;
}

