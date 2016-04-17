#ifndef CLOUD_H
#define CLOUD_H

#include "object.h"

class Cloud : public Object
{
public:
    Cloud(glm::vec3 pos = glm::vec3(0), glm::vec3 vel = glm::vec3(0));
    virtual void Draw();
    void SetSize(glm::vec2 size);
    void SetWorldWidth(glm::vec2 width);
    virtual void Update(float dt);
    void SetTexture(GLuint texture);
private:
    glm::vec2 _size;
    glm::vec2 _worldWidth;
    GLuint _texture;
};
#endif // CLOUD_H
