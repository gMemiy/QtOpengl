#ifndef FIREWORK_H
#define FIREWORK_H

#include "particlesystem.h"

class FireWork
{
public:
    FireWork();

    void Update(float dt);
    void Draw();

    void Push(glm::vec3 pos, int lvl);
    int ParticleCount();
    void AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime = 5.f, float size = 1.f, int count = 150);
    void AddBoom(glm::vec3 pos, float lifeTime, glm::vec4 color, float childLifeTime = 5.f, float size = 1.f, float speed = 1.f, int count = 150);

private:
    std::vector< QSharedPointer <ParticleSystem> > _bullets;
};

#endif // FIREWORK_H
