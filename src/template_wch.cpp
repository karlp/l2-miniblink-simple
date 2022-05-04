#include <gpio/gpio.h>
#include <rcc/rcc.h>

//// add to laks!!! 

void entry();
extern int _ram_end;

[[gnu::naked]]
[[gnu::section(".vectors")]]
void _reset_handler()
{
	// Initialize stack pointer.
	asm volatile("lui sp, %%hi(%0); add sp, sp, %%lo(%0)" ::"i"(&_ram_end));
	// Absolute jump to entry function.
	asm volatile("jr %0" ::"m"(entry));
}
//// add to laks end....


Pin led1 = GPIO_LED1;

int main()
{
	// FIXME.... what is the variable for this?
#if defined(RCC_ENABLE1)
	RCC.enable(RCC_ENABLE);
#endif
			
	// FIXME - this needs to be a stable family wide API at least?
	led1.set_mode(Pin::Output, Pin::Pull::Floating, Pin::Drive::Low5);

	auto i = 0;

	while(1) {
		i++;
		if (i % 80000 == 0) {
			led1.toggle();
		}
	}
}
