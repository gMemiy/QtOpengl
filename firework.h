#ifndef FIREWORK_H
#define FIREWORK_H

#include "particlesystem.h"


struct BulletType // структура для настройки эффектов ракет
{
    float bulletCount = 1;
    float speed = 1;
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

    void Push(glm::vec2 pos, int lvl); // первый выстрел
    int ParticleCount(); // количество частиц
    void AddBullet(glm::vec2 pos, int level, float lifeTime, glm::vec2 vel, glm::vec4 color, float childLifeTime, float childSpeed, float size, int count); // добавить ракету
    void AddBoom(glm::vec2 pos, float lifeTime, glm::vec4 color, float childLifeTime, float size, float speed, int count); // добавить волну
    void AddBulletByType(glm::vec2 pos, int level, glm::vec4 color, QSharedPointer<BulletType> bType, float scale); // добваить ракету по настройке из BulletType
    void AddBulletType(QSharedPointer<BulletType> type);
    void AddColor(glm::vec4 color);
    void SetFirst(BulletType first);

private:

    BulletType _first;

    std::vector<glm::vec4> _colors; // цвета
    std::vector< QSharedPointer <ParticleSystem> > _bullets; // ракеты
    std::vector<QSharedPointer <BulletType>> _bulletTypes; // настроенные типы ракет
};

#endif // FIREWORK_H
