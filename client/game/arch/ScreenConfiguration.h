#ifndef __SCREEN_CONFIGURATION_H__
#define __SCREEN_CONFIGURATION_H__


class ScreenConfiguration {
private:
    int width;
    int height;
    int width_offset;
    int height_offset;

public:
    ScreenConfiguration(int width, int height, int width_offset, int height_offset);

    ScreenConfiguration(const ScreenConfiguration &other);

    ScreenConfiguration(ScreenConfiguration &&other) noexcept;

    // Overloading the assignment by copy
    ScreenConfiguration &operator=(const ScreenConfiguration &other);

    // Overloading the assignment by movement
    ScreenConfiguration &operator=(ScreenConfiguration &&other) noexcept;

    int getWidth() const;

    int getHeight() const;

    int getWidthOffset() const;

    int getHeightOffset() const;
};


#endif //__SCREEN_CONFIGURATION_H__
