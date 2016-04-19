#ifndef FIREWORK_H
#define FIREWORK_H

#include "particlesystem.h"


struct Bullet // структура для настройки эффектов ракет
{
    float bulletCount = 1;
    float speed;
    float lifeTime = 1;
    float childLifeTime = 1;
    float childSpeed = 1;
    float childSize = 1;
    int childCount = 1;
};

class FireWork
{
public:
    FireWork();

    void Update(float dt);
    void Draw();

    void Push(glm::vec3 pos, int lvl); // первый выстрел
    int ParticleCount(); // количество частиц
    void AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime, float childSpeed, float size, int count); // добавить ракету
    void AddBoom(glm::vec3 pos, float lifeTime, glm::vec4 color, float childLifeTime, float size, float speed, int count); // добавить волну
    void AddBulletByType(glm::vec3 pos, int level, glm::vec4 color, QSharedPointer<Bullet> bType, float scale); // добваить ракету по настройке из Bullet
    void InitBullets(); // дефолтные ракеты
private:
    std::vector< QSharedPointer <ParticleSystem> > _bullets; // ракеты
    std::vector<QSharedPointer <Bullet>> _bulletTypes; // настроенные типы ракет
};

#endif // FIREWORK_H
