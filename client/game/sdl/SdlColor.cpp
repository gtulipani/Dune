#include "SdlColor.h"

SdlColor::SdlColor(int r, int g, int b) : r(r), g(g), b(b) {}

int SdlColor::getR() const {
    return r;
}
int SdlColor::getG() const {
    return g;
}
int SdlColor::getB() const {
    return b;
}
