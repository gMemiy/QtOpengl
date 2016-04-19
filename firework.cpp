#include "firework.h"
#include "glm/gtx/rotate_vector.hpp"

FireWork::FireWork()
{

    InitBullets();
}

void FireWork::InitBullets() // создадим типы ракет
{
    for (int i = 4; i <= 7; ++i) // сигнальные ракеты по 4-7 штук
    {
        auto b = QSharedPointer<Bullet>(new Bullet());
        b->childCount = 400;
        b->childLifeTime = 5;
        b->childSize = 1;
        b->childSpeed = 1;
        b->lifeTime = 5;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _bulletTypes.push_back(b);
    }

    for (int i = 3; i <= 5; ++i) // звёзды по 3, 4 и 5 лучей
    {
        auto b = QSharedPointer<Bullet>(new Bullet());
        b->childCount = 400;
        b->childLifeTime = 5;
        b->childSize = 1;
        b->childSpeed = 5;
        b->lifeTime = 1.5f;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _bulletTypes.push_back(b);
    }


    auto b = QSharedPointer<Bullet>(new Bullet()); // шары
    b->childCount = 100;
    b->childLifeTime = 1;
    b->childSize = 1;
    b->childSpeed = 40;
    b->lifeTime = .1f;
    b->bulletCount = 3;
    b->speed = 20;
    b->bulletCount = 5;
    _bulletTypes.push_back(b);

    for (int i = 3; i <= 5; ++i) // искорки
    {
        auto b = QSharedPointer<Bullet>(new Bullet());
        b->childCount = 50;
        b->childLifeTime = 1;
        b->childSize = 1;
        b->childSpeed = 50;
        b->lifeTime = 2.f;
        b->bulletCount = 3;
        b->speed = 10;
        b->bulletCount = i;
        _bulletTypes.push_back(b);
    }


}

float GetRand() // берём токлько цвета с яркостью больше 0.3f
{
    int percent = 70;
    float k = rand() % percent;
    return k / (float)percent + (100.f - (float)percent) / 100.f;
}


void FireWork::AddBulletByType(glm::vec3 pos, int level, glm::vec4 color, QSharedPointer<Bullet> bType, float scale) // добавление ракеты по типу
{
    int count = bType->bulletCount; // количество добавляемых ракет
    float grad = 360.f / count; // равномерно рспределяем их по окружности
    float g = rand() % 90;  // со случайным смещением
    for (int j = 0; j < count; ++j)
    {
        glm::vec3 speed(bType->speed * scale, 0, 0); // скорость полёта ракет
        speed = glm::rotateZ(speed, g / 180.f * 3.14f);
        g += grad;

        auto b = QSharedPointer<ParticleSystem>(new ParticleSystem());

        b->SetLevel(level); //
        b->SetPos(pos);
        b->SetColor(color);
        b->SetVelocity(speed);

        b->SetCount(bType->childCount); // количество частиц
        b->SetLifeTime(bType->lifeTime); // время жизни ракеты
        b->SetSize(bType->childSize * scale); // размер частиц
        b->SetChildLifeTime(bType->childLifeTime); // время жизнии частиц
        b->SetChildSpeed(bType->childSpeed * scale); // скорость частиц
        b->SetGravity(glm::vec3(0, -5, 0)); // гравитация

        _bullets.push_back(b);
    }

}


void FireWork::AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime, float childSpeed, float size, int count)
{
    auto b = QSharedPointer<ParticleSystem>(new ParticleSystem());
    b->SetLevel(level);
    b->SetPos(pos);
    b->SetCount(count);
    b->SetLifeTime(lifeTime);
    b->SetSize(size);
    b->SetVelocity(vel);
    b->SetChildLifeTime(childLifeTime);
    b->SetChildSpeed(childSpeed);
    b->SetGravity(glm::vec3(0, -5, 0));
    b->SetColor(color);
    _bullets.push_back(b);
}

void FireWork::AddBoom(glm::vec3 pos, float lifeTime, glm::vec4 color, float childLifeTime, float size, float speed, int count)
{
    auto b = new Boom();
    b->SetPos(pos);
    b->SetCount(count);
    b->SetChildSpeed(speed);
    b->SetLifeTime(lifeTime);
    b->SetSize(size);
    b->SetColor(color);
    b->SetChildLifeTime(childLifeTime);
    b->AddAllParticles();
    auto newBoom = QSharedPointer<ParticleSystem>(b);
    _bullets.push_back(newBoom);
}

void FireWork::Push(glm::vec3 pos, int lvl) // первый выстрел
{
    float speed = float(rand() % 20) + 20.f;
    float size = speed / 30.f;
    AddBullet(pos, 1, 2, glm::vec3(0, speed, 0), glm::vec4(GetRand(), GetRand(), GetRand(), 1), 3, 1, size, 400);
}

void FireWork::Update(float dt)
{
    std::vector<int> dead;
    std::vector<int> toBorn;
    int i = 0;
    for (auto b  = _bullets.begin(); b != _bullets.end(); ++b)
    {
        (*b)->Update(dt); // обновляем все ракеты
        if (((*b)->GetLevel() > 0) && (*b)->IsEnd()) // если у какой-то ракеты закончлся таймер жизни, и она может создать новую
        {
            toBorn.push_back(i); // запоминаем её
        }
        if (!(*b)->IsAlive()) // запоминаем мёртвые ракеты (у которых пропали все частицы)
        {
            dead.push_back(i);
        }
        ++i;
    }

     while (!toBorn.empty()) // обрабатываем ракеты, которые могут создать другие
     {
         int index = toBorn.back();
         toBorn.pop_back();
         auto b = _bullets[index];
         if (b->GetLevel() > 0)
         {
             float bSize = b->GetSize(); // от размера будет зависить скорость. Чем ракета дальше, тем она меньше, и тем медленнее кажется
             glm::vec4 color(GetRand(), GetRand(), GetRand(), 1); // случайный цвет
             AddBulletByType(b->GetPos(), b->GetLevel() - 1, color, _bulletTypes[ rand() % _bulletTypes.size() ], b->GetSize()); // ракета случайного типа
             AddBullet(b->GetPos(), 0, 0.1f, glm::vec3(0), glm::vec4(1), 0.3f, 0, 30 * bSize, 1); // вспышка
             AddBoom(b->GetPos(), 0.1f, glm::vec4(color.r, color.g, color.b, 0.3f), 0.7f, bSize, 30.f * bSize, 100); // волна
             b->SetLevel(0); // ракета больше не может создавать ракеты
         }
     }


    while (!dead.empty()) // убиваем мёртвые ракеты
    {
        int index = dead.back();
        dead.pop_back();
        auto b = _bullets[index];
        _bullets.erase(_bullets.begin() + index);
    }

}

void FireWork::Draw()
{
    for (auto b : _bullets)
    {
        b->Draw();
    }
}

int FireWork::ParticleCount()
{
    int count = 0;
    for (auto b : _bullets)
    {
        count += b->GetCount(); // считаем количество частиц каждой ракеты
    }
    return count;
}
