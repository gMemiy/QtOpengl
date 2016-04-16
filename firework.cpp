#include "firework.h"

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
    auto b = QSharedPointer<ParticleSystem>(new ParticleSystem(pos, 100, 5));
    b->SetSize(0.5f);
    b->SetVelocity(glm::vec3(1, 5, 0));
    b->SetChildLifeTime(5);
    _bullets.push_back(b);
}

void FireWork::Update(float dt)
{
    std::vector<int> dead;
    int i = 0;
    for (auto b : _bullets)
    {
        b->Update(dt);
        if (!b->IsAlive())
        {
            dead.push_back(i);
        }
        ++i;
    }
    while (!dead.empty())
    {
        int index = dead.back();
        dead.pop_back();
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
