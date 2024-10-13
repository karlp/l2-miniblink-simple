#include <gpio/gpio.h>
#include <rcc/rcc.h>

Pin led1 = GPIO_LED1;

// extern void laks_entry(void);
// void entry(void)
// {
// 	// FUCK, fixme... this was meant to be weak, not garbage collected!
// 	asm volatile("nop");
// 	laks_entry();
// }

int main()
{
#if defined(RCC_ENABLE1)
	RCC.enable(RCC_ENABLE1);
#endif

	// FIXME - this needs to be a stable family wide API at least?
	led1.set_mode(Pin::Output);
	led1.set_type(Pin::PushPull);

	int i = 0;

	while (1)
	{
		i++;
		// asm volatile("nop");
		if (i % 600000 == 0)
		{
			led1.toggle();
		}
		else
		{
			asm volatile("nop");
		}
	}
}