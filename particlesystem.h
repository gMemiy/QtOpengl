#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem
{
public:

    ParticleSystem(int count = 120, float lifeime = 2.f);
    void Draw();
    void Update(float dt);
    void AddParticle();
    void SetPos(glm::vec3 pos);
private:

    std::vector< QSharedPointer <Particle> > _particles;
    glm::vec3 _pos;
    float _lifeTime;
    int _count;
    float _spawnTime;
    float _timer;
};

#endif // PARTICLESYSTEM_H
