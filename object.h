#ifndef OBJECT_H
#define OBJECT_H


#include <QtOpenGL>
#include "glm/glm.hpp"


class Object
{
public:

    Object();
    Object(glm::vec3 pos, glm::vec3 vel, glm::vec4 color, glm::vec3 gravity);
    virtual ~Object();

    virtual void Draw();
    virtual void Update(float dt);

    void SetPos(glm::vec3 pos);    
    void SetVelocity(glm::vec3 vel);
    void SetColor(glm::vec4 color);
    void SetGravity(glm::vec3 gravity);

    glm::vec3 GetPos();
    glm::vec4 GetColor();

protected:

    glm::vec3 _pos;
    glm::vec3 _vel;
    glm::vec3 _gravity;
    glm::vec4 _color;
};

#endif // OBJECT_H
