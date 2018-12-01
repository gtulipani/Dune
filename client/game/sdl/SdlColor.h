#ifndef __SDL_COLOR_H__
#define __SDL_COLOR_H__


class SdlColor {
private:
    int r;
    int g;
    int b;

public:
    SdlColor(int r, int g, int b);

    int getR() const;
    int getG() const;
    int getB() const;
};


#endif //__SDL_COLOR_H__
