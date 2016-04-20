#ifndef CLOUD_H
#define CLOUD_H

#include "object.h"

class Cloud : public Object // объект, знающий о своём размере и текстуре
{
public:

    Cloud();
    Cloud(glm::vec2 pos, glm::vec2 vel);
    virtual ~Cloud();

    virtual void Update(float dt);
    virtual void Draw();

    void SetSize(glm::vec2 size);
    void SetRange(glm::vec2 range);
    void SetTexture(GLuint texture);

private:
    glm::vec2 _size;
    glm::vec2 _range; // область, в которой облако будет двигаться
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
    void AddClouds(int count); // добавить count облаков в случайные места со случайной текстурой

private:
    std::vector<QSharedPointer<Cloud>> _clouds; // облака
    std::vector<GLuint> _textures; // текстуры облаокв
    glm::vec2 _range; // область существования облаков
};


#endif // CLOUD_H
