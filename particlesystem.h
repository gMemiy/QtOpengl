#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem : public Particle // та же частица, только пораждает другие частицы. Рождает частицы в течении всего времени своей жизни, равномерно распределяя их во времени
{
public:

    ParticleSystem();
    virtual ~ParticleSystem();

    virtual void Draw();
    virtual void Update(float dt);

    virtual bool IsAlive() override;

    void AddParticle();

    void SetCount(int count);
    void SetChildLifeTime(float lifeTime);
    void SetChildSpeed(float speed);
    void SetLevel(int level);

    int GetCount();
    int GetLevel();

    bool IsEnd();

protected:

    void UpdateChild(float dt);

    std::vector< QSharedPointer <Particle> > _particles;
    int _level; // уровень ракеты.
    int _count; // количество частиц
    float _spawnTime; // время, за которое рождается 1 частица
    float _spawnTimer;
    float _speed; // максимальная скорость частиц
    float _childLifeTime;  // время жизни частиц
};

class Boom : public ParticleSystem // рождает все частицы одновременно и равномерно распределяет их по окружности
{
public:
    Boom();
    void AddAllParticles();
    virtual void Update(float dt);
};

#endif // PARTICLESYSTEM_H
