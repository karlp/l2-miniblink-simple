#!python3
import os.path
from collections import namedtuple

Board = namedtuple("Board", "brd part led1 led1_enable")

boards_wch = [
        Board("CH582M-R0-1v0", "ch582m", "GPIO[0]", None), # Needs jumper wire to "LED1" or "LED2"
        Board("CH32V307V-R1-1v0", "ch32v307vct6", "GPIOA[0]", "GPIOA"), # Needs jumper wire to "LED1" or "LED2"
]
boards_gd32v = [
        ("GD32VF103C-START", "gd32vf103cb", "GPIOA[7]", "GPIOA"),
        ("Longan-Nano", "gd32vf103cb", "GPIOA[1]", "GPIOA"),
]

toolpath = 'extern/laks/build/scons_tools',
tools = [
    'default',
    'tool_selectmcu',
    'tool_firmware',
    'tool_jinja2',
    'tool_platform_spec',
    'tool_protonium',
],


for b in boards_wch:
    bdir = "buildx/" + b.part
    #env = SConscript("extern/laks/build/env.py", variant_dir=bdir)
    env = Environment(
        ENV=os.environ,
        LAKS_PATH="#extern/laks",
        tools=[
        'default',
        'tool_selectmcu',
        'tool_firmware',
        'tool_jinja2',
        'tool_platform_spec',
        'tool_protonium',
        ],
        toolpath=["extern/laks/build/scons_tools"])
    #env.VariantDir(bdir, "src")
    #env.t
    #env = SConscript("extern/laks/build/env.py", variant_dir=bdir)
    #env.Replace(LAKS_PATH=Dir("extern/laks"))
    #env.VariantDir(bdir, "src")
    #env = Environment()
    env.SelectMCU(b.part, variant_dir=bdir)
    env.SetOption("num_jobs", 8) # lala, fingers in ears
    env.Append(CPPDEFINES = [
        ("BOARD", b.brd),
        ("PART", b.part),
        ("GPIO_LED1", b.led1),
    ])
    if b.led1_enable:
        env.Append(CPPDEFINES = [
            ("RCC_ENABLE1", b.led1_enable),
        ])
    #env.Firmware(f"miniblink-{b.brd}.elf", f"{bdir}/template_wch.cpp")
    #env.Program(f"miniblink-{b.brd}.elf", f"#{bdir}/template_wch.cpp", variant_dir=bdir)
    objs = [env.Object(target=f"{bdir}/{f}.o", source=f"#src/{f}") for f in ["template_wch.cpp"]]
    #env.Program(f"miniblink-{b.brd}.elf", f"#src/template_wch.cpp", variant_dir=bdir)
    #env.Program(f"miniblink-{b.brd}.elf", objs, variant_dir=bdir)
    env.Firmware(f"miniblink-{b.brd}.elf", objs, variant_dir=bdir)

