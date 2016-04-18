#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem : public Particle
{
public:

    ParticleSystem();
    ParticleSystem(int type, glm::vec3 pos, int count, float lifeime, float speed, float size);
    virtual ~ParticleSystem();

    virtual void Draw();
    virtual void Update(float dt);

    virtual bool IsAlive() override;

    void AddParticle();

    void SetCount(int count);
    void SetChildLifeTime(float lifeTime);
    void SetChildSpeed(float speed);
    void SetType(int type);

    int GetCount();
    int GetType();

    bool IsEnd();

protected:

    void UpdateChild(float dt);

    std::vector< QSharedPointer <Particle> > _particles;
    int _type;
    int _count;
    float _spawnTime;
    float _spawnTimer;
    float _speed;
    float _childLifeTime;
};

class Boom : public ParticleSystem
{
public:
    Boom();
    Boom(glm::vec3 pos, int count, float lifeTime, float childSpeed, float size);
    void AddAllParticles();
    virtual void Update(float dt);
};

#endif // PARTICLESYSTEM_H
