// !!! BUILD WITH Magick++-config CFLAGS AND LIBS

#include <iostream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <fstream>
#include <Magick++.h>

#define FRAME_WIDTH 88
#define FRAME_HEIGHT 64
#define FRAME_SIZE 704 // 88 * 64 / 8

void set_value(uint8_t *map, uint8_t x, uint8_t y, uint8_t bit_value)
{	
	int bit_index = FRAME_WIDTH * y + x;
	int index = bit_index % 8;
	int num_index = bit_index / 8;
	map[num_index] &= ~(1 << (7 - index));
	map[num_index] |= bit_value << (7 - index);
}

int main()
{	
	Magick::ColorMono pixel;
	std::ifstream input("sorted_file_list");  // the names of all frames in alphabetical order
	FILE *output;
	output = fopen("frames", "wb");
	uint8_t frame_buffer[FRAME_SIZE];
	for(std::string filename; getline(input, filename);)
	{
		Magick::Image frame("apple64x88_inverted/" + filename);
		for (int y = 0; y < FRAME_HEIGHT; y++)
			for (int x = 0; x < FRAME_WIDTH; x++)
				set_value(frame_buffer, x, y, !((Magick::ColorMono)frame.pixelColor(x, y)).mono());
		fwrite(&frame_buffer, sizeof(uint8_t), FRAME_SIZE, output);
	}
	fclose(output);
	input.close();
	return 0;
}
