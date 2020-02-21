#pragma once
#include <string>
//
//
//
class SpriteSheet {
public:
    std::string filename;
    int frame_width = 0;
    int frame_height = 0;
    int spriteset_frames = 0;
    int start_row = 0;
    int start_col = 0;
    int sheet_cols = 0;
    int vertical_offset = 0;
};

