#ifndef CLOUD_H
#define CLOUD_H

#include "object.h"

class Cloud : public Object
{
public:

    Cloud();
    Cloud(glm::vec3 pos, glm::vec3 vel);
    virtual ~Cloud();

    virtual void Update(float dt);
    virtual void Draw();

    void SetSize(glm::vec2 size);
    void SetRange(glm::vec2 range);
    void SetTexture(GLuint texture);

private:
    glm::vec2 _size;
    glm::vec2 _range;
    GLuint _texture;
};

class CloudManager
{
public:

    CloudManager();
    ~CloudManager();

    void Update(float dt);
    void Draw();

    void SetRange(glm::vec2 range);
    void AddTexture(GLuint texture);
    void AddClouds(int count);

private:
    std::vector<QSharedPointer<Cloud>> _clouds;
    std::vector<GLuint> _textures;
    glm::vec2 _range;
};


#endif // CLOUD_H
