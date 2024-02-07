#include <nxp_kx/rcm.h>
#include <nxp_kx/sim.h>
#include <nxp_kx/wdog.h>
#include <gpio/gpio.h>

Pin led1 = GPIO_LED1;

extern void laks_entry(void);

void entry(void)
{
	// MUST be early!
	WDOG.unlock();
	WDOG.disable();

	laks_entry();
}

int main()
{
	// Too late to turn off watchdog here!
	uint8_t reason0 = RCM->SRS0;
	uint8_t reason1 = RCM->SRS1;
	if (reason0 == 0x42 && reason1 == 0x69)
	{
		while (1)
			;
	}
	SIM.enable(RCC_ENABLE1);
	// lol
	// SIM.enable(sim::PORTA);
	// SIM.enable(sim::PORTB);
	// SIM.enable(sim::PORTC);
	// SIM.enable(sim::PORTD);
	// SIM.enable(sim::PORTE);
	// SIM.enable(sim::PORTF);

	// FIXME - this is gross.  want to use a ?friend? class
	// or something to get the right info out of the "Pin"?
	// PCRA.mux(10, NXP_PCR_KX_t<NXP_PCR_KX_reg_t>::Alt1_GPIO);
	// PCRA.mux(28, NXP_PCR_KX_t<NXP_PCR_KX_reg_t>::Alt1_GPIO);
	// PCRA.mux(29, NXP_PCR_KX_t<NXP_PCR_KX_reg_t>::Alt1_GPIO);
	// FIXME - not viable for template yet!
	PCRA.mux(11, NXP_PCR_KX_t<NXP_PCR_KX_reg_t>::Alt1_GPIO);
	PCRB.mux(21, NXP_PCR_KX_t<NXP_PCR_KX_reg_t>::Alt1_GPIO);

	led1.set_out();

	int qq = 0;
	while (1)
	{
		qq++;
		if (qq % 800000 == 0)
		{
			led1.toggle();
		}
	}
}
