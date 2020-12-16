#include "nrf24.h"
#include <string>



nrf24::nrf24() {
	usb_init(); /* initialize the library */
	usb_find_busses(); /* find all busses */
	usb_find_devices(); /* find all connected devices */
 
 	usb_bus *bus = NULL;
 	struct usb_device *dev = NULL;
 
	for (bus = usb_get_busses(); bus; bus = bus->next)
	{
		for (dev = bus->devices; dev; dev = dev->next)
		{
			if (dev->descriptor.idVendor == DONGLE_ID_Vendor
				&& dev->descriptor.idProduct == DONGLE_ID_Product)
			{
				m_dev = usb_open(dev);
				if (m_dev){
					break;
				}
				
			}
		}
	}
	if (m_dev == NULL) {
		printf("error:%s\r\n", "can't find dongle!");
		return;
	}

	usb_set_configuration(m_dev, 1);
	usb_claim_interface(m_dev, 0);
 }


nrf24::~nrf24() {
	if (m_dev != NULL) {
		usb_close(m_dev);
		m_dev = NULL;
	}
}


void nrf24::enable_lna() {
	std::string req;
	req.append(1, USB_COMMANDS::ENABLE_LNA_PA);

	send_and_recv(req, "");
}


void nrf24::enter_promiscuous_mode()
{
	std::string req;
	req.append(1, USB_COMMANDS::ENTER_PROMISCUOUS_MODE);

	std::string data;
	data.append(1, 0);
	send_and_recv(req, data);
}


void nrf24::enter_promiscuous_mode_generic()
{

}


void nrf24::enter_tone_test_mode()
{

}


std::string nrf24::receive_payload()
{
	std::string req;
	req.append(1, USB_COMMANDS::RECEIVE_PAYLOAD);


	return send_and_recv(req, "");
}


void nrf24::transmit_payload_generic()
{
	

}


bool nrf24::transmit_payload(std::string payload, char timeout, char retransmits)
{
	std::string req;
	req.append(1, USB_COMMANDS::TRANSMIT_PAYLOAD);

	std::string data;
	data.append(1, payload.size());
	data.append(1, timeout);
	data.append(1, retransmits);
	data.append(payload);

	std::string result = send_and_recv(req, data);
	if (result.empty()) {
		return false;
	}
	int ret = result.data()[0];
	return ret > 0;
}


void nrf24::transmit_ack_payload()
{

}


void nrf24::set_channel(int channel)
{
	if (channel > 125)
	{
		channel = 125;
	}
	std::string req;
	req.append(1, USB_COMMANDS::SET_CHANNEL);

	std::string data;
	data.append(1, channel);
	send_and_recv(req, data);

}


std::string nrf24::get_channel()
{
	std::string req;
	req.append(1, USB_COMMANDS::GET_CHANNEL);


	return send_and_recv(req, "");
}


void nrf24::enter_sniffer_mode(std::string address)
{
	std::string req;
	req.append(1, USB_COMMANDS::ENTER_SNIFFER_MODE);

	std::string data;
	data.append(1, address.size());
	data.append(address);

	send_and_recv(req, data);
}

std::string nrf24::send_and_recv(std::string request, std::string data)
{
	if (m_dev == NULL) {
		return "error";
	}
	std::string send_buffer;
	send_buffer.append(request.begin(), request.end());
	send_buffer.append(data.begin(), data.end());
	int r = usb_bulk_write(m_dev, 0x01, (char*)send_buffer.data(), send_buffer.size(), usb_timeout);
	//printf("send_and_recv usb_bulk_write:%d\r\n", r);
	std::string read_buffer;
	read_buffer.resize(0x1000);
	int size = usb_bulk_read(m_dev, 0x81, (char*)read_buffer.data(), 0x1000, usb_timeout);
	//printf("send_and_recv usb_bulk_read:%d\r\n", size);
	if (size > 0) {
		std::string result(read_buffer.data(), size);
		return result;
	}
	
	
	return "";
}


