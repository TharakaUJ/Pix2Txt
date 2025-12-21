#include "image_scale.h"

void scale_image(unsigned char* input_image, int input_width, int input_height,
                 unsigned char* output_image, int output_width, int output_height) {
    for (int y = 0; y < output_height; y++) {
        for (int x = 0; x < output_width; x++) {
            // this is selecting pixel from a neighbor hood of pixels in the input image
            int src_x = x * input_width / output_width;
            int src_y = y * input_height / output_height;
            output_image[y * output_width + x] = input_image[src_y * input_width + src_x];
        }
    }
}