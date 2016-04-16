#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem : public Particle
{
public:

    ParticleSystem(glm::vec3 pos = glm::vec3(0), int count = 300, float lifeime = 2.f, float speed = 0.5f, float size = 0.1f);
    virtual ~ParticleSystem(){}

    virtual void Draw();
    virtual void Update(float dt);
    virtual void AddParticle();

    void SetSpeed(float speed);
    void SetSpeed(glm::vec3 speed);
    int GetCount();
private:

    std::vector< QSharedPointer <Particle> > _particles;
    int _count;
    float _spawnTime;
    float _timer;
    float _speed;
};

#endif // PARTICLESYSTEM_H
