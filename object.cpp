#include "object.h"

Object::Object():
    _pos(0)
  , _vel(0)
  , _gravity(0)
  , _color(1)
{

}

Object::Object(glm::vec3 pos, glm::vec3 vel, glm::vec4 color, glm::vec3 gravity):
    _pos(pos)
  , _vel(vel)
  , _color(color)
  , _gravity(gravity)
{

}

Object::~Object()
{

}

void Object::SetPos(glm::vec3 pos)
{
    _pos = pos;
}

void Object::SetVelocity(glm::vec3 vel)
{
    _vel = vel;
}

void Object::Update(float dt)
{
    _pos += _vel * dt;
    _vel += _gravity * dt;
}

void Object::SetGravity(glm::vec3 gravity)
{
    _gravity = gravity;
}

void Object::SetColor(glm::vec4 color)
{
    _color = color;
}

void Object::Draw()
{

}

glm::vec3 Object::GetPos()
{
    return _pos;
}

glm::vec4 Object::GetColor()
{
    return _color;
}
