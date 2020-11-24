#ifndef USB_IAD
#define USB_IAD

#include <cmsis_compiler.h>
#include <stdint.h>

#define USB_CLASS_IAD					((uint8_t)0xfe)
#define USB_SUBCLASS_IAD				((uint8_t)0x02)
#define USB_PROTOCOL_IAD				((uint8_t)0x01)

#define USB_DTYPE_IAD					((uint8_t)0x0b)

typedef __PACKED_STRUCT usb_iad_descriptor_s{
	uint8_t	bLength;
	uint8_t	bDescriptorType;
	uint8_t bFirstInterface;
	uint8_t bInterfaceCount;
	uint8_t	bFunctionClass;
	uint8_t	bFunctionSubClass;
	uint8_t	bFunctionProtocol;
	uint8_t	iFunction;
}usb_iad_descriptor_st;

#endif