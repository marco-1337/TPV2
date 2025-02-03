// This file is part of the course TPV2@UCM - Samir Genaim

#pragma once


#include <SDL.h>

#include "Vector2D.h"

class GameObject {
public:
	GameObject() :
			_pos(), _vel(), _width(), _height(), _rot(0.0f) {
	}
	virtual ~GameObject() {
	}

	virtual void handleInput() = 0;
	virtual void update() = 0;
	virtual void render() = 0;

	inline float getHeight() const {
		return _height;
	}

	inline void setHeight(float height) {
		_height = height;
	}

	inline Vector2D& getPos() {
		return _pos;
	}

	inline Vector2D& getVel() {
		return _vel;
	}

	inline float getWidth() const {
		return _width;
	}

	inline void setWidth(float width) {
		_width = width;
	}

	inline float getRotation() const {
		return _rot;
	}

	inline void setRotation(float rot) {
		_rot = rot;
		if(_rot >= 360.0f)
			_rot = _rot / 360.0;
	}

protected:

	Vector2D _pos;
	Vector2D _vel;
	float _width;
	float _height;
	float _rot;
};

