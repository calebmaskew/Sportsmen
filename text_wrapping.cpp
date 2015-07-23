#include "text_wrapping.h"

std::vector<std::string> text_wrap(std::string original, int width/*box width*/){
	char letter;
	std::vector<std::string> output;
	int current_line_size = 0;
	std::string cur_word = "";
	std::string cur_line = "";
	unsigned int max_chars_per_line = width/8;	//will determine when to jump to next line
	for(unsigned int i=0; i<original.size(); i++){
		letter = original[i];
		cur_word += letter;
		if(isspace(letter) || i == original.size()-1){	//we've made it to the end of a word, check to see if there's space for it on the line
			if(cur_line.size() + cur_word.size() > max_chars_per_line){	//there's not space, add cur_line to output
				output.push_back(cur_line);
				cur_line = cur_word;
			}
			else{	//if there is room, simply add the current word to the current line
				cur_line += cur_word;
			}
			cur_word = "";	//always clear out current word so that size checks function properly and output doesn't look weird
		}
	}
	if(cur_line.size() > 0)
		output.push_back(cur_line);
	return output;
}
