#pragma once

#include <string>
#include <vector>
#include <map>

struct frame_entry
{
	std::string frame;
	unsigned int frame_sleep;
};

struct blank_entry
{
	std::string key_char;
	std::vector<frame_entry> frames;
	unsigned char mod = 0;
	unsigned char hid = 0;
	unsigned int sleep = 0;
};

struct hid_mod
{
	unsigned char hid;
	unsigned char mod;
};

class DuckyParser
{
	std::map<std::string, hid_mod> hid_map;
public:
	DuckyParser();
	std::vector<blank_entry> parse(std::string attack_script);

	~DuckyParser();
};

