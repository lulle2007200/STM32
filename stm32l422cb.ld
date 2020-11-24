ENTRY(Reset_Handler)

PROVIDE(stack_min_size = 0x4000);
PROVIDE(heap_min_size = 0x4000);
PROVIDE(stack_end = 0x2000A000);
__stack = stack_end;
_estack = stack_end;

MEMORY
{
	RAM(xrwa) :	ORIGIN = 0x20000000, LENGTH = 40K
	ROM(rx) :	ORIGIN = 0x08000000, LENGTH = 128K
}

SECTIONS
{
	.interrupt_vector_table :
	{
		. = ALIGN(8);
		KEEP(*(.interrupt_vector_table))
		. = ALIGN(8);
	} > ROM

	.text :
	{
		. = ALIGN(8);
		*(.text*)
		*(.text)
		*(.eh_frame)
		*(.eh_frame*)
		KEEP(*(.init))
		KEEP(*(.fini))
		_etext = .;
		. = ALIGN(8);
	} > ROM

	.rodata :
	{
		. = ALIGN(8);
		*(.rodata*)
		*(.rodata)
		. = ALIGN(8);
	} > ROM

	.preinit_array :
	{
		. = ALIGN(8);
		__preinit_array_start = .;
		KEEP(*(.preinit_array*))
		__preinit_array_end = .;
		. = ALIGN(8);
	} > ROM

	.init_array :
	{
		. = ALIGN(8);
		__init_array_start = .;
		KEEP(*(.init_array*))
		KEEP(*(.init_array))
		__init_array_end = .;
		. = ALIGN(8);
	} > ROM

	.fini_array :
	{
		. = ALIGN(8);
		__fini_array_start = .;
		KEEP(*(.fini_array.*))
		KEEP(*(.fini_array))
		__fini_array_end = .;
		. = ALIGN(8);
	} > ROM

	.ARM :
	{
		. = ALIGN(8);
		__exidx_start = .;
		*(.ARM.exidx*)
		__exidx_end = .;
		. = ALIGN(8);
	} > ROM

	.ARM.extab :
	{
		. = ALIGN(8);
		*(.ARM.extab*)
		. = ALIGN(8);
	} > ROM

	.data :
	{
		. = ALIGN(8);
		_sdata = .;
		*(.data*)
		*(.data)
		. = ALIGN(8);
		_edata = .;
	} > RAM AT > ROM
	_sidata = LOADADDR(.data);

	end = .;
	_end = end;

	.bss (NOLOAD) :
	{
		. = ALIGN(8);
		_sbss = .;
		__bss_start__ = _sbss;
		*(.bss*)
		*(.bss)
		. = ALIGN(8);
		_ebss = .;
		__bss_end__ = _ebss;
	} > RAM

	.heap (NOLOAD) :
	{
		. = ALIGN(8);
		. = . + heap_min_size;
		. = ALIGN(8);
	} > RAM

	.stack (NOLOAD) :
	{
		. = ALIGN(8);
		. = . + stack_min_size;
		. = ALIGN(8);
	} > RAM

}