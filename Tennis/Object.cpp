#include "Object.h"

bool Object::setStartPosition(Object *obj){
    obj->textures[0].loadFromFile("../assets/mario1.png");
    obj->sprite.setTexture(textures[0]);
    obj->sprite.setPosition(10, 600);
	return true;
};


float Object::left()
{
	return this->sprite.getPosition().x - Width / 2.f;
}
float Object::right()
{
	return this->sprite.getPosition().x + Width / 2.f;
}
float Object::top()
{
	return this->sprite.getPosition().y -Height / 2.f;
}
float Object::bottom()
{
	return this->sprite.getPosition().y +Height / 2.f;
}

