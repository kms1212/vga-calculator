#ifndef MODE_H__
#define MODE_H__

#include <stdint.h>
#include <stddef.h>

enum video_memory_model {
    MM_TEXT, MM_CGA, MM_PLANAR, MM_PACKED
};

struct video_mode_info {
    enum video_memory_model mmodel;
    int width, height;
    int bpp;
    int chr_width, chr_height;
    void* buf_base;
};

struct video_mode {
    int mode;
    struct video_mode_info info;
    uint8_t miscreg;
    uint8_t *sequencer;  // register 0 is skipped
    uint8_t *crtc;
    uint8_t *graphics;
    uint8_t *attribute;
};

#define END_OF_VMODE_TABLE { -1, {}, 0, NULL, NULL, NULL, NULL }
#define IS_VMODE_TABLE_END(vmode) (vmode->mode < 0)

#endif  // MODE_H__
