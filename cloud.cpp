#include "cloud.h"


Cloud::Cloud() : Object()
  , _range(-1, 1)
  , _texture(0)
{

}

Cloud::Cloud(glm::vec2 pos, glm::vec2 vel): Object()
  , _range(-1, 1)
  , _texture(0)
{
    _pos = pos;
    _vel = vel;
}

Cloud::~Cloud()
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
        glVertex2fv(&glm::vec2(_pos.x - sx, _pos.y - sy / 2.f)[0]);
        glTexCoord2f(0,1);
        glVertex2fv(&glm::vec2(_pos.x - sx, _pos.y + sy)[0]);
        glTexCoord2f(1,0);
        glVertex2fv(&glm::vec2(_pos.x + sy, _pos.y - sy)[0]);
        glTexCoord2f(1,1);
        glVertex2fv(&glm::vec2(_pos.x + sy, _pos.y + sy)[0]);
    glEnd();

}

void Cloud::Update(float dt)
{
    Object::Update(dt);
    if (_pos.x > _range.y + _size.x / 2.f) // если вышли центром за пределы указанного диапазона, перескакиваем на его другую сторону
    {
        _pos.x = _range.x - _size.x / 2.f;
    }
    if (_pos.x <  _range.x - _size.x / 2.f)
    {
        _pos.x = _range.y + _size.x / 2.f;
    }
}

void Cloud::SetSize(glm::vec2 size)
{
    _size = size;
}

void Cloud::SetRange(glm::vec2 range)
{
    _range = range;
}

void Cloud::SetTexture(GLuint texture)
{
    _texture = texture;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

CloudManager::CloudManager() :
    _range(-1, 1)
  , _vertRange(-1, 1)
  , _color(1)
  , _maxSpeed(0)
  , _maxSize(1)
{
}

CloudManager::~CloudManager()
{
    _clouds.clear();
    _textures.clear();
}

void CloudManager::AddTexture(GLuint texture)
{
    _textures.push_back(texture);
}

void CloudManager::AddClouds(int count)
{
    if (_textures.empty())
    {
        return;
    }
    for (int i = 0; i < count; ++i)
    {
        float posX = rand() % (int)(abs(_range.x) + abs(_range.y)) - abs(_range.x);
        float posY = rand() % (int)(_vertRange.y - _vertRange.x) + _vertRange.x;
        float vel = (float)(rand() % (int)(_maxSpeed * 100) - _maxSpeed * 50) / 100.f;
        float size = rand() % (int)(_maxSize / 2) + _maxSize / 2;
        GLuint texture = rand() % (_textures.size() - 1);
        auto c = QSharedPointer<Cloud>(new Cloud(glm::vec2(posX, posY), glm::vec2(vel, 0)));
        c->SetRange(_range);
        c->SetSize(glm::vec2(size, size / 2.f));
        c->SetTexture(_textures[texture]);
        c->SetColor(_color);
        _clouds.push_back(c);
    }
}

void CloudManager::Draw()
{
    for (auto c : _clouds)
    {
        c->Draw();
    }
}

void CloudManager::Update(float dt)
{
    for (auto c : _clouds)
    {
        c->Update(dt);
    }
}

void CloudManager::SetRange(glm::vec2 range)
{
    _range = range;
}


void CloudManager::SetHorizontalRange(glm::vec2 range)
{
    _range = range;
}

void CloudManager::SetVerticalRange(glm::vec2 range)
{
    _vertRange = range;
}

void CloudManager::SetMaxSpeed(float speed)
{
    _maxSpeed = speed;
}

void CloudManager::SetMaxSize(float size)
{
    _maxSize = size;
}

void CloudManager::SetColor(glm::vec4 color)
{
    _color = color;
}
