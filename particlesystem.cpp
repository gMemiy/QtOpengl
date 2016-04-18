#include "particlesystem.h"
#include "glm/gtx/rotate_vector.hpp"

ParticleSystem::ParticleSystem() :
    Particle()
  , _type(0)
  , _count(1)
  , _spawnTime(1)
  , _spawnTimer(1)
  , _speed(1)
  , _childLifeTime(1)
{
}

ParticleSystem::ParticleSystem(int type, glm::vec3 pos, int count, float lifeime,  float speed, float size) :
    Particle(pos, lifeime, size, 0)
  , _type(type)
  , _count(count)
  , _spawnTime(0)
  , _spawnTimer(0)
  , _speed(speed)
  , _childLifeTime(1)
{
    SetChildLifeTime(1);
}

ParticleSystem::~ParticleSystem()
{
    _particles.clear();
}

void ParticleSystem::AddParticle()
{
    QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _childLifeTime, _size, _speed));
    p->SetColor(_color);
    p->SetGravity(_gravity / 4.f);
    _particles.push_back(p);
}

void ParticleSystem::SetCount(int count)
{
    _count = count;
    SetChildLifeTime(_childLifeTime);
}

void ParticleSystem::UpdateChild(float dt)
{
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

    UpdateChild(dt);

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
    return (_lifeTimer >= 0 ) || !_particles.empty();
}

void ParticleSystem::SetChildSpeed(float speed)
{
    _speed = speed;
}


int ParticleSystem::GetCount()
{
    return _particles.size();
}

void ParticleSystem::SetChildLifeTime(float lifeTime)
{
    _childLifeTime = lifeTime;
    _spawnTime = _childLifeTime / _count;
    _spawnTimer = _spawnTime;
}

int ParticleSystem::GetType()
{
    return _type;
}

void ParticleSystem::SetType(int type)
{
    _type = type;
}

bool ParticleSystem::IsEnd()
{
    return !(_lifeTimer >= 0);
}


/////////////////////////////////////////////////////////////////////////////


Boom::Boom() : ParticleSystem()
{
}

Boom::Boom(glm::vec3 pos, int count, float lifeTime, float childSpeed, float size) :
    ParticleSystem(0, pos, count, lifeTime, childSpeed, size)
{
}

void Boom::AddAllParticles()
{
    float grad = 360.f / (float) _count;
    float angle = 0;
    for (int i = 0; i < _count; ++i)
    {
        QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _childLifeTime, _size, _speed));
        p->SetColor(_color);
        p->SetGravity(_gravity / 4.f);

        glm::vec3 speed(_speed, 0, 0);
        speed = glm::rotateZ(speed, angle);
        p->SetVelocity(speed);
        angle += grad;

        _particles.push_back(p);
    }
}

void Boom::Update(float dt)
{
    Particle::Update(dt);
    UpdateChild(dt);
}


