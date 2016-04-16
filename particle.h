#ifndef PARTICLE_H
#define PARTICLE_H
#include <math.h>
#include <QtOpenGL>
#include "glm/glm.hpp"


class Object
{
public:
    Object(glm::vec3 pos = glm::vec3(0), glm::vec3 vel = glm::vec3(0), glm::vec4 color = glm::vec4(1));
    virtual ~Object();
    void SetPos(glm::vec3 pos);
    virtual void Update(float dt);
    void SetVelocity(glm::vec3 vel);
    void SetColor(glm::vec4 color);
    virtual void Draw();
    void SetGravity(glm::vec3 gravity);

    glm::vec3 GetPos();
protected:
    glm::vec3 _pos;
    glm::vec3 _vel;
    glm::vec3 _gravity;
    glm::vec4 _color;
};

class Particle : public Object
{
public:
    Particle(glm::vec3 pos = glm::vec3(0), float lifeTime = 0, float size = 0.5f, float speedMax = 0.2f);
    virtual ~Particle();
    virtual void Draw();
    virtual void Update(float dt);
    virtual bool IsAlive();
    virtual void SetSize(float size);
    virtual void SetMaxSpeed(float maxSpeed);
    virtual void SetLifeTime(float lifeTime);

protected:

    float _lifeTime;
    float _lifeTimer;
    float _size;
};

#endif // PARTICLE_H
