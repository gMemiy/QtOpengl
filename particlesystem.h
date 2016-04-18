#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem : public Particle
{
public:

    ParticleSystem(int type, glm::vec3 pos = glm::vec3(0), int count = 300, float lifeime = 0.f, float speed = 0.5f, float size = 0.1f);
    virtual ~ParticleSystem(){}

    virtual void Draw();
    virtual void Update(float dt);
    void AddParticle();
    virtual bool IsAlive() override;

    void SetChildLifeTime(float lifeTime);
    void SetChildSpeed(float speed);
    int GetCount();
    int GetType();
    void SetType(int type);
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
