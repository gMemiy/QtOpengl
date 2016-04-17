#ifndef FIREWORK_H
#define FIREWORK_H

#include "particlesystem.h"

class FireWork
{
public:
    FireWork();

    void Push(glm::vec3 pos, int lvl);
    void Update(float dt);
    void Draw();
    int ParticleCount();
    void AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime = 5.f, float size = 1.f, int count = 100);

private:
    std::vector< QSharedPointer <ParticleSystem> > _bullets;
};

#endif // FIREWORK_H
