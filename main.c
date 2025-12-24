#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "scale_image.h"
#include "convert_to_ascii.h"
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char** argv) {
    if (argc != 4) {
        printf("Usage: %s <input_image> <output_width> <output_height>\n", argv[0]);
        return 1;
    }

    const char* input_filename = argv[1];
    int output_width = atoi(argv[2]);
    int output_height = atoi(argv[3]);

    int input_width, input_height, channels;
    unsigned char* input_image = stbi_load(input_filename, &input_width, &input_height, &channels, 1);
    if (!input_image) {
        printf("Failed to load image: %s\n", input_filename);
        return 1;
    }

    unsigned char* scaled_image = (unsigned char*)malloc(output_width * output_height);
    if (!scaled_image) {
        printf("Failed to allocate memory for scaled image\n");
        stbi_image_free(input_image);
        return 1;
    }

    scale_image(input_image, input_width, input_height, scaled_image, output_width, output_height);

    char* ascii_image = (char*)malloc(output_width * output_height + 1);
    if (!ascii_image) {
        printf("Failed to allocate memory for ASCII image\n");
        free(scaled_image);
        stbi_image_free(input_image);
        return 1;
    }
    ascii_image[output_width * output_height] = '\0'; // Null-terminate the string

    convert_to_ascii(scaled_image, output_width, output_height, ascii_image);

    // Print the ASCII image
    for (int y = 0; y < output_height; y++) {
        for (int x = 0; x < output_width; x++) {
            putchar(ascii_image[y * output_width + x]);
        }
        putchar('\n');
    }

    free(ascii_image);
    free(scaled_image);
    stbi_image_free(input_image);

    return 0;
}