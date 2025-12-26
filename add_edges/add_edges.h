#pragma once

#ifndef ABS
#define ABS(x) ((x) < 0 ? -(x) : (x))
#endif

// edges will be marked with |/_\ characters based on the direction of the edge
void add_edges(const unsigned char *input_image, int input_width, int input_height,
               char *output_image, int output_width, int output_height)
{
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {1, 2, 1, 0, 0, 0, -1, -2, -1};

    int threshold = 220; // edge detection threshold

    for (int y = 1; y < input_height - 1; y++)
    {
        for (int x = 1; x < input_width - 1; x++)
        {
            int sumX = 0;
            int sumY = 0;

            for (int ky = -1; ky <= 1; ky++)
            {
                for (int kx = -1; kx <= 1; kx++)
                {
                    int pixel_value = input_image[(y + ky) * input_width + (x + kx)];
                    sumX += pixel_value * Gx[(ky + 1) * 3 + (kx + 1)];
                    sumY += pixel_value * Gy[(ky + 1) * 3 + (kx + 1)];
                }
            }

            int magnitude = (sumX * sumX + sumY * sumY);

            int scaled_x = x * output_width / input_width;
            int scaled_y = y * output_height / input_height;
            
            if (ABS(sumX) > threshold && ABS(sumY) < threshold)
            {
                output_image[scaled_y * output_width + scaled_x] = '|';
            }
            else if (ABS(sumY) > threshold && ABS(sumX) < threshold)
            {
                output_image[scaled_y * output_width + scaled_x] = '_';
            }
            else if (magnitude > threshold * threshold)
            {
                if (sumX * sumY > 0)
                {
                    output_image[scaled_y * output_width + scaled_x] = '\\';
                }
                else
                {
                    output_image[scaled_y * output_width + scaled_x] = '/';
                }
            }
        }
    }
}
