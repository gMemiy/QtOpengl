#include "firework.h"
#include "glm/gtx/rotate_vector.hpp"

FireWork::FireWork()
{
}

/*
 *
 *     _ps.SetChildSpeed(0.2f);
    _ps.SetSize(0.5f);
    _ps.SetSpeed(glm::vec3(2, 5, 0));
    _ps.SetChildLifeTime(5.f);
    _ps.SetGravity(glm::vec3(0, -1, 0));

    _tail.SetChildSpeed(.9f);
    _tail.SetColor(glm::vec4(0.8f, 0.9f, 0.8f, 1.f));
    _tail.SetSize(0.3f);
    _tail.SetSpeed(glm::vec3(0, 2, 0));
 */

void FireWork::Push(glm::vec3 pos)
{
    auto b = QSharedPointer<ParticleSystem>(new ParticleSystem(1, pos, 100, 10));
    b->SetSize(0.5f);
    b->SetVelocity(glm::vec3(1, 5, 0));
    b->SetChildLifeTime(5);
    _bullets.push_back(b);
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

             for (int j = 0; j < count; ++j)
             {
                 auto p = QSharedPointer<ParticleSystem>(new ParticleSystem(b->GetType() - 1, b->GetPos(), 100, 5));
                 p->SetSize(0.5f);
                 glm::vec3 speed(5,0,0);
                 speed = glm::rotateZ(speed, (float)(rand() % 30 + g) /180.f*3.14f);
                 g += grad;
                 p->SetVelocity(glm::vec3(speed.x, speed.y, 0));
                 p->SetChildLifeTime(5);
                 p->SetGravity(glm::vec3(0, -1, 0));
                 _bullets.push_back(p);
             }
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
