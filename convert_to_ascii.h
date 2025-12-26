#pragma once

#define ascii_chars " .-=+*x#$&X@"
#define num_levels (sizeof(ascii_chars) - 1) // Exclude null


void convert_to_ascii(const unsigned char* input_image, int width, int height,
                      char* output_image) {
    // const char* ascii_chars = "@%#*+=-:. "; // 10 levels of brightness
    // const char* ascii_chars = " .:-=+*#%@"; // 10 levels of brightness reverse order
    // int num_levels = 10;

    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            unsigned char pixel_value = input_image[y * width + x];
            int index = pixel_value * (num_levels - 1) / 255; // Map pixel value to ascii_chars index
            output_image[y * width + x] = ascii_chars[index];
        }
    }
}