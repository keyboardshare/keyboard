#include "stdafx.h"
#include "DuckyParser.h"
#include <sstream>
#include <iostream>


DuckyParser::DuckyParser()
{
	hid_map[""] = { 0, 0 };
	hid_map["ALT"] = { 0, 4 };
	hid_map["SHIFT"] = { 0, 2 };
	hid_map["CTRL"] = { 0, 1 };
	hid_map["GUI"] = { 0, 8 };
	hid_map["SCROLLLOCK"] = { 71, 0 };
	hid_map["ENTER"] = { 40, 0 };
	hid_map["F12"] = { 69, 0 };
	hid_map["HOME"] = { 74, 0 };
	hid_map["F10"] = { 67, 0 };
	hid_map["F9"] = { 66, 0 };
	hid_map["ESCAPE"] = { 41, 0 };
	hid_map["PAGEUP"] = { 75, 0 };
	hid_map["TAB"] = { 43, 0 };
	hid_map["PRINTSCREEN"] = { 70, 0 };
	hid_map["F2"] = { 59, 0 };
	hid_map["CAPSLOCK"] = { 57, 0 };
	hid_map["F1"] = { 58, 0 };
	hid_map["F4"] = { 61, 0 };
	hid_map["F6"] = { 63, 0 };
	hid_map["F8"] = { 65, 0 };
	hid_map["DOWNARROW"] = { 81, 0 };
	hid_map["DELETE"] = { 42, 0 };
	hid_map["RIGHT"] = { 79, 0 };
	hid_map["F3"] = { 60, 0 };
	hid_map["DOWN"] = { 81, 0 };
	hid_map["DEL"] = { 76, 0 };
	hid_map["END"] = { 77, 0 };
	hid_map["INSERT"] = { 73, 0 };
	hid_map["F5"] = { 62, 0 };
	hid_map["LEFTARROW"] = { 80, 0 };
	hid_map["RIGHTARROW"] = { 79, 0 };
	hid_map["PAGEDOWN"] = { 78, 0 };
	hid_map["PAUSE"] = { 72, 0 };
	hid_map["SPACE"] = { 44, 0 };
	hid_map["UPARROW"] = { 82, 0 };
	hid_map["F11"] = { 68, 0 };
	hid_map["F7"] = { 64, 0 };
	hid_map["UP"] = { 82, 0 };
	hid_map["LEFT"] = { 80, 0 };

	hid_map[" "] = { 44, 0 };
	hid_map["!"] = { 30, 2 };
	hid_map["\""] = { 52, 2 };
	hid_map["#"] = { 32, 2 };
	hid_map["$"] = { 33, 2 };
	hid_map["%"] = { 34, 2 };
	hid_map["&"] = { 36, 2 };
	hid_map["'"] = { 52, 0 };
	hid_map["("] = { 38, 2 };
	hid_map[")"] = { 39, 2 };
	hid_map["*"] = { 37, 2 };
	hid_map["+"] = { 46, 2 };
	hid_map[","] = { 54, 0 };
	hid_map["-"] = { 45, 0 };
	hid_map["."] = { 55, 0 };
	hid_map["/"] = { 56, 0 };
	hid_map["0"] = { 39, 0 };
	hid_map["1"] = { 30, 0 };
	hid_map["2"] = { 31, 0 };
	hid_map["3"] = { 32, 0 };
	hid_map["4"] = { 33, 0 };
	hid_map["5"] = { 34, 0 };
	hid_map["6"] = { 35, 0 };
	hid_map["7"] = { 36, 0 };
	hid_map["8"] = { 37, 0 };
	hid_map["9"] = { 38, 0 };
	hid_map[":"] = { 51, 2 };
	hid_map[";"] = { 51, 0 };
	hid_map["<"] = { 54, 2 };
	hid_map["="] = { 46, 0 };
	hid_map[">"] = { 55, 2 };
	hid_map["?"] = { 56, 2 };
	hid_map["@"] = { 31, 2 };
	hid_map["A"] = { 4, 2 };
	hid_map["B"] = { 5, 2 };
	hid_map["C"] = { 6, 2 };
	hid_map["D"] = { 7, 2 };
	hid_map["E"] = { 8, 2 };
	hid_map["F"] = { 9, 2 };
	hid_map["G"] = { 10, 2 };
	hid_map["H"] = { 11, 2 };
	hid_map["I"] = { 12, 2 };
	hid_map["J"] = { 13, 2 };
	hid_map["K"] = { 14, 2 };
	hid_map["L"] = { 15, 2 };
	hid_map["M"] = { 16, 2 };
	hid_map["N"] = { 17, 2 };
	hid_map["O"] = { 18, 2 };
	hid_map["P"] = { 19, 2 };
	hid_map["Q"] = { 20, 2 };
	hid_map["R"] = { 21, 2 };
	hid_map["S"] = { 22, 2 };
	hid_map["T"] = { 23, 2 };
	hid_map["U"] = { 24, 2 };
	hid_map["V"] = { 25, 2 };
	hid_map["W"] = { 26, 2 };
	hid_map["X"] = { 27, 2 };
	hid_map["Y"] = { 28, 2 };
	hid_map["Z"] = { 29, 2 };
	hid_map["["] = { 47, 0 };
	hid_map["\\"] = { 49, 0 };
	hid_map["]"] = { 48, 0 };
	hid_map["^"] = { 35, 2 };
	hid_map["_"] = { 45, 2 };
	hid_map["`"] = { 53, 0 };
	hid_map["a"] = { 4, 0 };
	hid_map["b"] = { 5, 0 };
	hid_map["c"] = { 6, 0 };
	hid_map["d"] = { 7, 0 };
	hid_map["e"] = { 8, 0 };
	hid_map["f"] = { 9, 0 };
	hid_map["g"] = { 10, 0 };
	hid_map["h"] = { 11, 0 };
	hid_map["i"] = { 12, 0 };
	hid_map["j"] = { 13, 0 };
	hid_map["k"] = { 14, 0 };
	hid_map["l"] = { 15, 0 };
	hid_map["m"] = { 16, 0 };
	hid_map["n"] = { 17, 0 };
	hid_map["o"] = { 18, 0 };
	hid_map["p"] = { 19, 0 };
	hid_map["q"] = { 20, 0 };
	hid_map["r"] = { 21, 0 };
	hid_map["s"] = { 22, 0 };
	hid_map["t"] = { 23, 0 };
	hid_map["u"] = { 24, 0 };
	hid_map["v"] = { 25, 0 };
	hid_map["w"] = { 26, 0 };
	hid_map["x"] = { 27, 0 };
	hid_map["y"] = { 28, 0 };
	hid_map["z"] = { 29, 0 };
	hid_map["{"] = { 47, 2 };
	hid_map["|"] = { 49, 2 };
	hid_map["}"] = { 48, 2 };
	hid_map["~"] = { 53, 2 };
	hid_map["BACKSPACE"] = { 42, 0 };
}

void split(const std::string& s, std::vector<std::string>& tokens, const std::string& delimiters = " ")
{
	std::string::size_type lastPos = s.find_first_not_of(delimiters, 0);
	std::string::size_type pos = s.find_first_of(delimiters, lastPos);
	while (std::string::npos != pos || std::string::npos != lastPos) {
		tokens.push_back(s.substr(lastPos, pos - lastPos));//use emplace_back after C++11
		lastPos = s.find_first_not_of(delimiters, pos);
		pos = s.find_first_of(delimiters, lastPos);
	}
}

std::string& trim(std::string &s, const std::string& delimiters = " ")
{
	if (s.empty())
	{
		return s;
	}

	s.erase(0, s.find_first_not_of(delimiters));
	s.erase(s.find_last_not_of(delimiters) + 1);
	return s;
}
std::vector<blank_entry> DuckyParser::parse(std::string script)
{
	std::vector<blank_entry> result_entries;
	std::vector<std::string> vector_attack_script;
	split(script, vector_attack_script, "\n");

	for each (std::string attack_script in vector_attack_script)
	{
		attack_script = trim(attack_script, "\r");
		if (attack_script.rfind("STRING") == 0) {
			std::vector<std::string> vector_string;
			split(attack_script, vector_string, " ");
			if (vector_string.size() > 1) {
				for (size_t i = 1; i < vector_string.size(); i++)
				{
					std::string str = vector_string[i];
					for (size_t j = 0; j < str.size(); ++j)
					{
						{
							blank_entry curr_key;
							curr_key.key_char = str.data()[j];
							std::string str_key = std::string(1, str.data()[j]);
							curr_key.hid = hid_map[str_key].hid;
							curr_key.sleep = 0;
							curr_key.mod = hid_map[str_key].mod;
							result_entries.push_back(curr_key);
						}
					}
				}
			}
		}
		else if (attack_script.rfind("ALT") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 4 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("GUI") == 0 || attack_script.rfind("WINDOWS") == 0 || attack_script.rfind("COMMAND") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 8 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("CTRL-ALT") == 0 || attack_script.rfind("CONTROL-ALT") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 4 | 1 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("CTRL-SHIFT") == 0 || attack_script.rfind("CONTROL-SHIFT") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 4 | 2 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("CTRL") == 0 || attack_script.rfind("CONTROL") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 1 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("SHIFT") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "";
				if (attack_script.find(" ") != std::string::npos) {
					std::vector<std::string> vector_string;
					split(attack_script, vector_string, " ");
					if (vector_string.size() > 1) {
						curr_key.key_char = vector_string[1][0];
					}
				}

				curr_key.hid = hid_map[curr_key.key_char].hid;
				curr_key.sleep = 0;
				curr_key.mod = 2 | hid_map[curr_key.key_char].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("ESC") == 0 || attack_script.rfind("APP") == 0 || attack_script.rfind("ESCAPE") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "ESC";
				curr_key.hid = hid_map["ESCAPE"].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map["ESCAPE"].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("DELAY") == 0) {
			{
				std::vector<std::string> vector_string;
				split(attack_script, vector_string, " ");
				if (vector_string.size() > 1) {
					
					blank_entry curr_key;
					curr_key.sleep = strtol(vector_string[1].c_str(), NULL, 10);
					result_entries.push_back(curr_key);
				}
				
			}
		}
		else if (attack_script.rfind("ENTER") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "\n";
				std::string str_key = "ENTER";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("TAB") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "\t";
				std::string str_key = "TAB";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("SPACE") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = " ";
				std::string str_key = "SPACE";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("F3") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = " ";
				std::string str_key = "F3";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("F2") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = " ";
				std::string str_key = "F2";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("UP") == 0 || attack_script.rfind("UPARROW") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "UP";
				std::string str_key = "UP";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("DOWN") == 0 || attack_script.rfind("DOWNARROW") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "DOWN";
				std::string str_key = "DOWN";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("LEFT") == 0 || attack_script.rfind("LEFTARROW") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "LEFT";
				std::string str_key = "LEFT";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
		else if (attack_script.rfind("RIGHT") == 0 || attack_script.rfind("RIGHTARROW") == 0) {
			{
				blank_entry curr_key;
				curr_key.key_char = "RIGHT";
				std::string str_key = "RIGHT";
				curr_key.hid = hid_map[str_key].hid;
				curr_key.sleep = 0;
				curr_key.mod = hid_map[str_key].mod;
				result_entries.push_back(curr_key);
			}
		}
	}

	return result_entries;
}

DuckyParser::~DuckyParser()
{
}
