#ifndef PARTICLESYSTEM_H
#define PARTICLESYSTEM_H

#include "particle.h"
//#include "bits/shared_ptr.h"
#include "QSharedPointer"

class ParticleSystem
{
public:

    ParticleSystem(int count = 300, float lifeime = 2.f, float speed = 0.5f, float size = 0.1f);
    ~ParticleSystem(){}
    void Draw();
    void Update(float dt);
    virtual void AddParticle();
    void SetPos(glm::vec3 pos);
    void SetSpeed(float speed);
    void SetColor(glm::vec4 color);
    void SetSize(float size);
    void SetLifeTime(float lifeTime);
    void SetSpeed(glm::vec3 speed);
    int GetCount();
private:

    std::vector< QSharedPointer <Particle> > _particles;
    glm::vec3 _pos;
    glm::vec3 _vel;
    float _lifeTime;
    int _count;
    float _spawnTime;
    float _timer;
    float _speed;
    float _size;
    glm::vec4 _color;
};

#endif // PARTICLESYSTEM_H
