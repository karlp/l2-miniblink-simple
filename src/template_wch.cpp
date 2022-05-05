#if 1
#include <cstdio>
#if !defined(RCC_ENABLE1)
#define RCC_ENABLE1 "no enable1"
#endif

#define STRINGIZE_INNER(x) #x
#define STRINGIZE(x) STRINGIZE_INNER(x)

const char* GPIOA[] = {
	"pinA0",
	"pinA1",
	"pinA2",
	"pinA3",
	"pinA4",
	"pinA5",
	"pinA5",
	"pinA6",
	"pinA7",
	"pinA8",
};
const char* GPIO[] = {
	"pin0",
	"pin1",
	"pin2",
	"pin3",
	"pin4",
	"pin5",
	"pin5",
	"pin6",
	"pin7",
	"pin8",
};

int main() {
	printf("board: <%s> part: <%s> led1: <%s>(%s), enable1: <%s>\n",
		STRINGIZE(BOARD), STRINGIZE(PART), STRINGIZE(GPIO_LED1), GPIO_LED1, RCC_ENABLE1);
	//printf("led: <%s> enabl1: <%s>\n", GPIO_LED1, RCC_ENABLE1);
	return 0;
}

#else
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
#endif