#include "ScreenInformation.h"

ScreenInformation::ScreenInformation() : offset_x(0), offset_y(0) {}

int ScreenInformation::getOffsetX() const {
    return offset_x;
}
int ScreenInformation::getOffsetY() const {
    return offset_y;
}

void ScreenInformation::setOffsetX(int offset_x) {
    this->offset_x = offset_x;
}
void ScreenInformation::setOffsetY(int offset_y) {
    this->offset_y = offset_y;
}

Point ScreenInformation::getRelativePoint(int row, int column) {
    return {row - this->offset_y, column - this->offset_x};
}
