#include <stdio.h>
#include <assert.h>
#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <stdlib.h>

#define H_ARRAYSIZE(a) \
    ((sizeof(a) / sizeof(*(a))) / \
    static_cast<size_t>(!(sizeof(a) % sizeof(*(a)))))

struct rectangle
{
	int begin;  // begin postition
	int end;    // end   postition
	int height;
	rectangle() : begin(0), end(0), height(0) {}
};

const char newline[] = "\n";
const char comma[]   = ",";

/**
* Get the total distance of the climber.
* @param input The string of triples 
* @return  The total distance.
*/
int resolve(const char* input)
{
	size_t inputLength  = strlen(input);
	size_t inputIndex   = 0;
	const std::string inputString = std::string(input, inputLength);
	

	/**
	*  Parse the input string, such as 3\n1, 3, 2\n2, 4, 4\n6, 7, 5\n
	*  First get the toal number of rectangle
	*  Then, parse the one triple, such as  1,3,2 through comma ','
	*  So, save the one triple in vector<rectangle> triples;
	*/

	std::vector<rectangle> triples;

	// Get the total number of rectangle 
	size_t newline_positon = inputString.find(newline, inputIndex);
	int total_rectangle_number = atol(inputString.substr(0, newline_positon).c_str());

	for (int count = 0; count < total_rectangle_number; count++)
	{
		size_t triple_begin_positon = newline_positon + 1;
		newline_positon = inputString.find(newline, triple_begin_positon);
		std::string one_triple = inputString.substr(triple_begin_positon, newline_positon - triple_begin_positon);

		//  Parse one triple such as 1,2,3 through comma ','
		struct rectangle param;
		size_t one_triple_index = 0;
		one_triple += comma;
		for (int i = 0; i < 3; i++)
		{
			size_t comma_pos = one_triple.find(comma, one_triple_index);
			int num = atol(one_triple.substr(one_triple_index, comma_pos - one_triple_index).c_str());

			switch (i)
			{
			case 0:
				param.begin = num;
				one_triple_index = comma_pos + 1;
				break;
			case 1:
				param.end = num;
				one_triple_index = comma_pos + 1;
				break;
			case 2:
				param.height = num;
				break;
			}
		}
		triples.push_back(param);
	}

	// Compute the distance of horizontal, which is the distance of from place A to place B
	int horizontal_distance = triples[total_rectangle_number - 1].end;
	
	// Compute the distance of climb up from left to right
	int climb_up_diatance = triples[0].height;
	for (int i = 1; i < total_rectangle_number; i++)
	{
		bool ok = (triples[i].begin >= triples[i - 1].begin && triples[i].begin <= triples[i - 1].end);

		if (ok)
		{
			if (triples[i].height - triples[i - 1].height > 0)  // if > 0, then means climb up
			{
				climb_up_diatance += (triples[i].height - triples[i - 1].height);
			}	
		}
		else
		{
			climb_up_diatance += triples[i].height;
		}
	}

	// Compute the distance of climb down from right to left
	int climb_down_diatance = triples[total_rectangle_number-1].height;
	for (int i = total_rectangle_number - 2; i >= 0; i--)
	{
		bool ok = triples[i].end >= triples[i + 1].begin && triples[i].end <= triples[i + 1].end;
		if (ok)
		{
			if (triples[i].height - triples[i + 1].height > 0)  // if > 0, then means climb down
			{
				climb_down_diatance += (triples[i].height - triples[i + 1].height);
			}
		}
		else
		{
			climb_down_diatance += triples[i].height;
		}
	}

	return horizontal_distance + climb_up_diatance + climb_down_diatance;
}

int main(int argc, char* argv[]) 
{
    const char* input[] = {
        "3\n1,3,2\n2,4,4\n6,7,5\n", //The giving example
        "1\n1,2,1\n",
        "2\n1,2,1\n2,3,2",
        "3\n1,2,1\n2,3,2\n3,6,1",
        "4\n1,2,1\n2,3,2\n3,6,1\n5,8,2",
        "5\n1,2,1\n2,3,2\n3,6,1\n5,8,2\n7,9,1",
        "1\n0,1,1",
        "2\n0,1,1\n2,4,3",
        "3\n0,1,1\n2,4,3\n3,5,1",
        "4\n0,1,1\n2,4,3\n3,5,1\n5,6,1",
        "5\n0,1,1\n2,4,3\n3,5,1\n5,6,1\n6,8,3",
        //TODO please add more test case here
        };
    int expectedSteps[] = {25, 4, 7, 10, 14, 15, 3, 12, 13, 14, 20};
    for (size_t i = 0; i < H_ARRAYSIZE(input); ++i)
    {
        assert(resolve(input[i]) == expectedSteps[i]);
    }
    return 0;
}
