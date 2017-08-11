#include <fstream>
#include <iostream>
#include <vector>

#include "math.hpp"

int main(int argc, char ** argv)
{

    std::array<std::array<int, 2>, 2> temp = {1, 2, 3, 4};
    uint32_t width = 800;
    uint32_t height = 600;

    std::vector<vec3> image;
    image.reserve(width * height);
    for(uint32_t y = 0; y < height; y += 1) {
        for(uint32_t x = 0; x < width; x += 1) {
            image.emplace_back(0.0f);
        }
    }

    mat4 cameraToWorld{0.871214f, 0.0f, -0.490904f, 0.0f,
                       -0.192902f, 0.919559f, -0.342346f, 0.0f,
                       0.451415f, 0.392953f, 0.801132f, 0.0f,
                       14.777467f, 29.361945f, 27.993464f, 1.0f};

    mat4 inverted = cameraToWorld.inverse();
    std::cout << inverted;

    std::string out_filename("untitled.ppm");
    if(argc > 1) {
        out_filename = std::string(argv[1]);
    }

    std::ofstream out_file(out_filename.c_str(), std::ios::out | std::ios::binary);
    out_file << "P6\n" << width << " " << height << "\n255\n";
    for(uint32_t i = 0; i < width * height; ++i) {
        out_file << (unsigned char)(std::min(1.0f, image[i](0)) * 255) <<
               (unsigned char)(std::min(1.0f, image[i](1)) * 255) <<
               (unsigned char)(std::min(1.0f, image[i](2)) * 255);
    }
    out_file.close();

    return 0;
}
