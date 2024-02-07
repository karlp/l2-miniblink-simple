#!python3
import os.path
from collections import namedtuple

Board = namedtuple("Board", "brd part led1 led1_enable")
Family = namedtuple("Family", "template boards")

boards_wch = [
        Board("CH582M-R0-1v0", "ch582m", "GPIO[0]", None), # Needs jumper wire to "LED1" or "LED2"
        # umm, this has a different gpio mode setter... yuk.
        #Board("CH32V307V-R1-1v0", "ch32v307vct6", "GPIOA[0]", "rcc::GPIOA"), # Needs jumper wire to "LED1" or "LED2"
]
boards_gd32v = [
        ("GD32VF103C-START", "gd32vf103cb", "GPIOA[7]", "GPIOA"),
        ("Longan-Nano", "gd32vf103cb", "GPIOA[1]", "GPIOA"),
]
boards_kx = [
    Board("TWR-K70F120M", "mk70fn1m0vmj12", "GPIOA[11]", "sim::PORTA"), # orange led
    Board("FRDM-K66", "mk66fn2m0vmd18", "GPIOA[11]", "sim::PORTA"), # Blue led on RGB
    Board("FRDM-K64", "MK64FN1M0VLL12", "GPIOB[21]", "sim::PORTB"), # Blue led on RGB
]

fam_wch = Family("template_wch.cpp", boards_wch)
fam_kx = Family("template_kx.cpp", boards_kx)
families = [fam_wch, fam_kx]

for fam in families:
    for b in fam.boards:
        bdir = "buildx/" + b.part
        env = SConscript("extern/laks/build/env.py")
        env.SelectMCU(b.part, variant_dir=bdir)
        env.SetOption("num_jobs", 8) # lala, fingers in ears
        env.Append(CPPPATH=bdir)
        env.Append(CPPDEFINES = [
            ("BOARD", b.brd),
            ("PART", b.part),
            ("GPIO_LED1", b.led1),
        ])
        if b.led1_enable:
            env.Append(CPPDEFINES = [
                ("RCC_ENABLE1", b.led1_enable),
            ])
        objs = [env.Object(target=f"{bdir}/{f}.o", source=f"#src/{f}") for f in [fam.template]]
        env.Firmware(f"miniblink-{b.brd}.elf", objs, variant_dir=bdir)

