#include "firework.h"
#include "glm/gtx/rotate_vector.hpp"

FireWork::FireWork()
{
}

float GetRand()
{
    float k = rand() % 50;
    return k / 50.f + 0.5f;
}

void FireWork::AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime, float size, int count)
{
    auto b = QSharedPointer<ParticleSystem>(new ParticleSystem(level, pos, count, lifeTime));
    b->SetSize(size);
    b->SetVelocity(vel);
    b->SetChildLifeTime(childLifeTime);
    b->SetGravity(glm::vec3(0, -1, 0));
    b->SetColor(color);
    _bullets.push_back(b);
}

void FireWork::Push(glm::vec3 pos, int lvl)
{
    AddBullet(pos, 1, 10, glm::vec3(0, 10, 0), glm::vec4(GetRand(), GetRand(), GetRand(), 1));
}

void FireWork::Update(float dt)
{
    std::vector<int> dead;
    std::vector<int> toBorn;
    int i = 0;
    for (auto b  = _bullets.begin(); b != _bullets.end(); ++b)
    {
        (*b)->Update(dt);
        if (((*b)->GetType() > 0) && (*b)->IsEnd())
        {
            toBorn.push_back(i);
        }
        if (!(*b)->IsAlive())
        {
            dead.push_back(i);
        }
        ++i;
    }

     while (!toBorn.empty())
     {
         int index = toBorn.back();
         toBorn.pop_back();
         auto b = _bullets[index];
         if (b->GetType() > 0)
         {

             int count = 5;
             float grad = 360.f / count;
             float g = grad;
             glm::vec4 color(GetRand(), GetRand(), GetRand(), 1);
             for (int j = 0; j < count; ++j)
             {
                 glm::vec3 speed(5,0,0);
                 speed = glm::rotateZ(speed, (float)(rand() % 30 + g) /180.f*3.14f);
                 g += grad;
                 AddBullet(b->GetPos(), b->GetType() - 1, 5, speed, color);
             }
             AddBullet(b->GetPos(), 0, 0.1f, glm::vec3(0), glm::vec4(1), 0.1f, 10, 1);
             b->SetType(0);
         }
     }


    while (!dead.empty())
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
        count += b->GetCount();
    }
    return count;
}
