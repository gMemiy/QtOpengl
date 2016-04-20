#ifndef OBJECT_H
#define OBJECT_H


#include <QtOpenGL>
#include "glm/glm.hpp"


class Object // объект, имеющий своё положение и скорость в пространстве и цвет.
{
public:

    Object();
    Object(glm::vec2 pos, glm::vec2 vel, glm::vec4 color, glm::vec2 gravity);
    virtual ~Object();

    virtual void Draw();
    virtual void Update(float dt);

    void SetPos(glm::vec2 pos);
    void SetVelocity(glm::vec2 vel);
    void SetColor(glm::vec4 color);
    void SetGravity(glm::vec2 gravity);

    glm::vec2 GetPos();
    glm::vec4 GetColor();

protected:

    glm::vec2 _pos;
    glm::vec2 _vel;
    glm::vec2 _gravity;
    glm::vec4 _color;
};

#endif // OBJECT_H
