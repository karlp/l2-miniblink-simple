#include <gpio/gpio.h>
#include <rcc/rcc.h>

Pin led1 = GPIO_LED1;

int main()
{
#if defined(RCC_ENABLE1)
	RCC.enable(RCC_ENABLE1);
#endif

	// FIXME - this needs to be a stable family wide API at least?
	led1.set_mode(Pin::Output, Pin::Pull::Floating, Pin::Drive::Low5);

	auto i = 0;

	while (1)
	{
		i++;
		if (i % 80000 == 0)
		{
			led1.toggle();
		}
	}
}