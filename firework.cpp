#include "firework.h"
#include "glm/gtx/rotate_vector.hpp"

FireWork::FireWork()
{
}

void FireWork::Push(glm::vec2 pos, int lvl) // первый выстрел
{
    float speed = rand() % (int)(_first.speed / 2) + _first.speed / 2.f;
    float size = _first.childSize * speed / _first.speed;
    AddBullet(pos, lvl, _first.lifeTime, glm::vec2(0, speed), _colors[rand() % _colors.size()], _first.childLifeTime, _first.childSpeed, size, _first.childCount);
}

void FireWork::AddBulletByType(glm::vec2 pos, int level, glm::vec4 color, QSharedPointer<BulletType> bType, float scale) // добавление ракеты по типу
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
        b->SetVelocity(glm::vec2(speed.x, speed.y));

        b->SetCount(bType->childCount); // количество частиц
        b->SetLifeTime(bType->lifeTime); // время жизни ракеты
        b->SetSize(bType->childSize * scale); // размер частиц
        b->SetChildLifeTime(bType->childLifeTime); // время жизнии частиц
        b->SetChildSpeed(bType->childSpeed * scale); // скорость частиц
        b->SetGravity(glm::vec2(0, -5)); // гравитация

        _bullets.push_back(b);
    }

}


void FireWork::AddBullet(glm::vec2 pos, int level, float lifeTime, glm::vec2 vel, glm::vec4 color, float childLifeTime, float childSpeed, float size, int count)
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
    b->SetGravity(glm::vec2(0, -5));
    b->SetColor(color);
    _bullets.push_back(b);
}

void FireWork::AddBoom(glm::vec2 pos, float lifeTime, glm::vec4 color, float childLifeTime, float size, float speed, int count)
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
    auto newBoom = QSharedPointer<Boom>(b);
    _bullets.push_back(newBoom);
}



void FireWork::Update(float dt)
{
    if (_bulletTypes.empty() || _colors.empty())
    {
        return; // если нет пула цветов или пула типов ракет, то ничего делать не нужно.
    }

    for (int i  = _bullets.size() - 1; i >  0; --i)
    {
        auto b = _bullets[i];
        b->Update(dt); // обновляем все ракеты
        if (b->IsEnd() && (b->GetLevel() > 0)) // если у какой-то ракеты закончлся таймер жизни, и она может создать новую
        {
            float bSize = b->GetSize(); // от размера будет зависить скорость. Чем ракета дальше, тем она меньше, и тем медленнее кажется
            glm::vec4 color = _colors[rand() % _colors.size()];
            AddBulletByType(b->GetPos(), b->GetLevel() - 1, color, _bulletTypes[ rand() % _bulletTypes.size() ], b->GetSize()); // ракета случайного типа
            AddBullet(b->GetPos(), 0, 0.1f, glm::vec2(0), glm::vec4(1), 0.3f, 0, 30.f * bSize, 1); // вспышка
            AddBoom(b->GetPos(), 0.1f, glm::vec4(color.r, color.g, color.b, 0.3f), 0.7f, bSize, 30.f * bSize, 100); // волна

            b->SetLevel(0); // ракета больше не может создавать ракеты
        }
        if (!b->IsAlive()) // запоминаем мёртвые ракеты (у которых пропали все частицы)
        {
            _bullets.erase(_bullets.begin() + i);
        }
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

void FireWork::AddColor(glm::vec4 color)
{
    _colors.push_back(color);
}

void FireWork::AddBulletType(QSharedPointer<BulletType> type)
{
    if (type)
    {
        _bulletTypes.push_back(type);
    }
}

void FireWork::SetFirst(BulletType first)
{
    _first = first;
}
