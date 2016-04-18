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
    b->SetGravity(glm::vec3(0, -5, 0));
    b->SetColor(color);
    _bullets.push_back(b);
}

void FireWork::AddBoom(glm::vec3 pos, float lifeTime, glm::vec4 color, float childLifeTime, float size, float speed, int count)
{
    auto b = new Boom(pos, count, lifeTime, speed, size);
    b->SetColor(color);
    b->AddAllParticles();
    auto newBoom = QSharedPointer<ParticleSystem>(b);
    _bullets.push_back(newBoom);
}

void FireWork::Push(glm::vec3 pos, int lvl)
{
    //AddBullet(glm::vec3 pos, int level, float lifeTime, glm::vec3 vel, glm::vec4 color, float childLifeTime, float size, int count)
    float speed = float(rand() % 20) + 20.f;
    float size = speed / 30.f;
    AddBullet(pos, 1, 2, glm::vec3(0, speed, 0), glm::vec4(GetRand(), GetRand(), GetRand(), 1), 3, size, 400);
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
             float s = rand() % 5 + 7;
             glm::vec4 color(GetRand(), GetRand(), GetRand(), 1);
             for (int j = 0; j < count; ++j)
             {
                 glm::vec3 speed(s * b->GetSize(),0,0);
                 speed = glm::rotateZ(speed, (float)(rand() % 30 + g) /180.f*3.14f);
                 g += grad;
                 AddBullet(b->GetPos(), b->GetType() - 1, 3, speed, color, 5, b->GetSize(), 500);
             }
             AddBullet(b->GetPos(), 0, 0.1f, glm::vec3(0), glm::vec4(1), 0.3f, 30 * b->GetSize(), 1);
             AddBoom(b->GetPos(), 0.1f, color, 5, b->GetSize(), 20.f * b->GetSize());
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
