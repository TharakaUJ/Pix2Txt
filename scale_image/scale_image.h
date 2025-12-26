// scale the image to size of final output

#pragma once

void scale_image(unsigned char* input_image, int input_width, int input_height,
                 unsigned char* output_image, int output_width, int output_height) {

    int neightborhood_size_x = input_width / output_width;
    int neightborhood_size_y = input_height / output_height;

    for (int y = 0; y < output_height; y++) {
        for (int x = 0; x < output_width; x++) {
            // // this is selecting pixel from a neighbor hood of pixels in the input image
            // int src_x = x * input_width / output_width;
            // int src_y = y * input_height / output_height;
            // output_image[y * output_width + x] = input_image[src_y * input_width + src_x];

            // averaging pixels in the neighborhood

            // FIXME: boundary check needed
            int sum = 0;
            for (int ny = 0; ny < neightborhood_size_y; ny++) {
                for (int nx = 0; nx < neightborhood_size_x; nx++) {
                    int src_x = x * neightborhood_size_x + nx;  // still room for improvement here. bufffer overflow or segmentation fault possible
                    int src_y = y * neightborhood_size_y + ny;
                    sum += input_image[src_y * input_width + src_x];
                }
            }
            int area = neightborhood_size_x * neightborhood_size_y;
            output_image[y * output_width + x] = sum / area;
        }
    }
}

