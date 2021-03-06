#ifndef PARTICLE_H
#define PARTICLE_H

#include "object.h"

class Particle : public Object // тот же объект, только с размером и временем жизни
{
public:
    Particle();
    Particle(glm::vec2 pos, float lifeTime, float size, float speedMax);
    virtual ~Particle();

    virtual void Draw();
    virtual void Update(float dt);

    virtual bool IsAlive();

    void SetSize(float size);
    void SetMaxSpeed(float maxSpeed);
    void SetLifeTime(float lifeTime);

    float GetSize();

protected:

    float _lifeTime;
    float _lifeTimer;
    float _size;
};

#endif // PARTICLE_H
