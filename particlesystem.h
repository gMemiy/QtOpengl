#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem : public Particle
{
public:

    ParticleSystem(glm::vec3 pos = glm::vec3(0), int count = 300, float lifeime = 0.f, float speed = 0.5f, float size = 0.1f);
    virtual ~ParticleSystem(){}

    virtual void Draw();
    virtual void Update(float dt);
    virtual void AddParticle();
    virtual bool IsAlive() override;

    void SetChildLifeTime(float lifeTime);
    void SetChildSpeed(float speed);
    int GetCount();
private:

    std::vector< QSharedPointer <Particle> > _particles;
    int _count;
    float _spawnTime;
    float _spawnTimer;
    float _speed;

    float _childLifeTime;
};

#endif // PARTICLESYSTEM_H
