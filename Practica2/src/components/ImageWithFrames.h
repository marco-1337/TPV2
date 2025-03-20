#pragma once
#include "../ecs/Component.h"
#include "../sdlutils/Texture.h"

struct ImageWithFrames: public ecs::Component {

	ImageWithFrames() :
			_tex(),
            _cols(),
            _rows(),
            _currentXSrc(),
            _currentYSrc(),
            _frameWidth(),
            _frameHeight() {
	}

	ImageWithFrames(Texture *tex, int cols = 1, int rows = 1, int frame = 0) :
   	_tex(tex),
    _cols(cols),
    _rows(rows),
    _frameWidth(_tex->width() / cols),
    _frameHeight(_tex->height() / rows) {

        assert(_cols > 0 && _rows > 0);

        setFrame(frame);
	}

	virtual ~ImageWithFrames() {
	}

    inline void setFrame(int frame) {
        assert(frame >= 0 && frame < (_cols * _rows));

        _currentXSrc = (frame % _cols) * _frameWidth;
        _currentYSrc = (frame / _cols) * _frameHeight;
    }

    inline std::pair<int, int> getFrameSrcPos() {
        return {_currentXSrc, _currentYSrc};
    }

	Texture* _tex;
    const int   _cols,
                _rows,
                _frameWidth,
                _frameHeight;
private:
    int _currentXSrc,
        _currentYSrc;
};

