#include "particlesystem.h"
#include "glm/gtx/rotate_vector.hpp"

ParticleSystem::ParticleSystem() :
    Particle()
  , _level(0)
  , _count(1)
  , _spawnTime(1)
  , _spawnTimer(1)
  , _speed(1)
  , _childLifeTime(1)
{
}

ParticleSystem::~ParticleSystem()
{
    _particles.clear();
}

void ParticleSystem::AddParticle() // добавление одной частицы
{
    QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _childLifeTime, _size, _speed));
    p->SetColor(_color);
    p->SetGravity(_gravity / 4.f);
    _particles.push_back(p);
}

void ParticleSystem::SetCount(int count)
{
    _count = count;
    SetChildLifeTime(_childLifeTime); // вычисляем время между появлениями 2х частиц
}

void ParticleSystem::UpdateChild(float dt)
{
    for ( std::vector< QSharedPointer<Particle> >::iterator p = _particles.begin(); p != _particles.end();)
    {
        (*p)->Update(dt);
        if (!(*p)->IsAlive())
        {
            p = _particles.erase(p);
        }
        else
        {
            ++p;
        }
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
            int count = _spawnTimer / _spawnTime; // dt может быть всякое. Не стоит из-за него пропускать рождение частиц
            _spawnTimer = 0;
            for (int i = 0; i < count; ++i)
            {
                AddParticle();
            }
        }
    }

    UpdateChild(dt); // обновляем частицы

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
    return (_lifeTimer >= 0 ) || !_particles.empty(); // система частиц метртва, когда все её частицы мертвы
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
    float min = std::min(_childLifeTime, _lifeTime);
    _spawnTime = min / (float)_count; // беру минимальное заначение из жизни системы частиц и жизни частицы. Это позволяет создавать разовые взрывы частиц и хвосты из них-же
    _spawnTimer = _spawnTime;
}

int ParticleSystem::GetLevel()
{
    return _level;
}

void ParticleSystem::SetLevel(int level)
{
    _level = level;
}

bool ParticleSystem::IsEnd()
{
    return !(_lifeTimer >= 0);
}

/////////////////////////////////////////////////////////////////////////////


Boom::Boom() : ParticleSystem()
{
}

void Boom::AddAllParticles()
{
    float grad = 360.f / (float) _count;
    float angle = 0;
    for (int i = 0; i < _count; ++i) // рождаем все частицы разом
    {
        QSharedPointer<Particle> p = QSharedPointer<Particle>(new Particle(_pos, _childLifeTime, _size, _speed));
        p->SetColor(_color);
        p->SetGravity(_gravity / 4.f);

        glm::vec3 speed(_speed, 0, 0);
        speed = glm::rotateZ(speed, angle);
        p->SetVelocity(glm::vec2(speed.x, speed.y));
        angle += grad;

        _particles.push_back(p);
    }
}

void Boom::Update(float dt)
{
    Particle::Update(dt);
    UpdateChild(dt);
}


