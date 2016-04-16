#ifndef FIREWORK_H
#define FIREWORK_H

#include "particlesystem.h"

class FireWork
{
public:
    FireWork();

    void Push(glm::vec3 pos);
    void Update(float dt);
    void Draw();
    int ParticleCount();

private:
    std::vector< QSharedPointer <ParticleSystem> > _bullets;
};

#endif // FIREWORK_H
