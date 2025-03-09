#pragma once

#include "../ecs/Component.h"
#include "SDL.h"
#include <cassert>

class Transform;
class Texture;

class ImageWithFrames: public ecs::Component {
public:

	__CMPID_DECL__(ecs::cmp::IMAGE_WITH_FRAMES)

	ImageWithFrames();
	ImageWithFrames(Texture *tex, int cols, int rows, Uint32 updateFrecuency);
	virtual ~ImageWithFrames();

	inline void setTexture(Texture* tex) {
		assert(tex != nullptr);
		_tex = tex;
	}

	void initComponent() override;
    void update() override;
	void render() override;

private:
	Transform *_tr;
	Texture *_tex;
    int _cols;
    int _rows;
    int _currentFrame;
    Uint32 _updateFrecuency;
    Uint32 _lastFrameTime;
};