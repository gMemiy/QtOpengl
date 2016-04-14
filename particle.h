#ifndef PARTICLE_H
#define PARTICLE_H
#include <math.h>
#include <QtOpenGL>
#include "glm/glm.hpp"

class Particle
{
public:
    Particle(glm::vec3 pos = glm::vec3(0), float lifeTime = 0.5f, float size = 0.5f, float speedMax = 0.2f);
    void Draw();
    void Update(float dt);
    bool IsAlive();

private:
    glm::vec3 _pos;
    glm::vec3 _vel;

    float _timeLife;
    float _timer;
    float _size;
};

#endif // PARTICLE_H