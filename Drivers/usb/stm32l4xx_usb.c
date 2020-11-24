#include <stdint.h>
#include <stdbool.h>

#include <stm32l4xx.h>

#define PMA_SIZE 0x400

#define USB_EP_SWBUF_TX USB_EP_DTOG_RX
#define USB_EP_SWBUF_RX USB_EP_DTOG_TX

typedef struct buffer_desc_s{
	uint16_t Address;
	uint16_t Count;
}buffer_desc_st;

typedef union buffer_desc_table_u{
	struct{
		buffer_desc_st tx;
		buffer_desc_st rx;
	};
	struct{
		buffer_desc_st tx0;
		buffer_desc_st tx1;
	};
	struct{
		buffer_desc_st rx0;
		buffer_desc_st rx1;
	};
}buffer_desc_table_ut;