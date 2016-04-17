#include "cloud.h"


Cloud::Cloud(glm::vec3 pos, glm::vec3 vel): Object(pos, vel)
  , _worldWidth(-1, 1)
  , _texture(0)
{

}

void Cloud::Draw()
{
    glBindTexture(GL_TEXTURE_2D, _texture);
    glColor4fv(&_color[0]);
    float sx = _size.x / 2.f;
    float sy = _size.y / 2.f;
    glBegin(GL_TRIANGLE_STRIP);
        glTexCoord2f(0,0);
        glVertex3fv(&glm::vec3(_pos.x - sx, _pos.y - sy / 2.f, 0)[0]);
        glTexCoord2f(0,1);
        glVertex3fv(&glm::vec3(_pos.x - sx, _pos.y + sy, 0)[0]);
        glTexCoord2f(1,0);
        glVertex3fv(&glm::vec3(_pos.x + sy, _pos.y - sy, 0)[0]);
        glTexCoord2f(1,1);
        glVertex3fv(&glm::vec3(_pos.x + sy, _pos.y + sy, 0)[0]);
    glEnd();

}

void Cloud::Update(float dt)
{
    Object::Update(dt);
    if (_pos.x > _worldWidth.y + _size.x / 2.f)
    {
        _pos.x = _worldWidth.x - _size.x / 2.f;
    }
    if (_pos.x <  _worldWidth.x - _size.x / 2.f)
    {
        _pos.x = _worldWidth.y + _size.x / 2.f;
    }
}

void Cloud::SetSize(glm::vec2 size)
{
    _size = size;
}

void Cloud::SetWorldWidth(glm::vec2 width)
{
    _worldWidth = width;
}

void Cloud::SetTexture(GLuint texture)
{
    _texture = texture;
}
