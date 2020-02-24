# THIS FILE IS AUTOMATICALLY GENERATED
# Project: C:\Projects\ENGG4000\software\firmware\ENGG4000_Firmware\Wearable_Firmware.cydsn\CE220818_I2C_Master_High_Level01.cydsn\CE220818_I2C_Master_High_Level01.cyprj
# Date: Mon, 24 Feb 2020 14:11:05 GMT
#set_units -time ns
create_clock -name {CyILO} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/ilo}]]
create_clock -name {CyClk_LF} -period 31250 -waveform {0 15625} [list [get_pins {ClockBlock/lfclk}]]
create_clock -name {CyFLL} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fll}]]
create_clock -name {CyClk_HF0} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/hfclk_0}]]
create_clock -name {CyClk_Fast} -period 10 -waveform {0 5} [list [get_pins {ClockBlock/fastclk}]]
create_clock -name {CyClk_Peri} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk}]]
create_generated_clock -name {CyClk_Slow} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/slowclk}]]
create_generated_clock -name {RGB_PWMclk} -source [get_pins {ClockBlock/periclk}] -edges {1 2 3} [list [get_pins {ClockBlock/ff_div_12}] [get_pins {ClockBlock/ff_div_14}] [get_pins {ClockBlock/ff_div_20}]]
create_generated_clock -name {sI2C_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 5 9} [list [get_pins {ClockBlock/ff_div_2}]]
create_generated_clock -name {mI2C_SCBCLK} -source [get_pins {ClockBlock/periclk}] -edges {1 7 13} [list [get_pins {ClockBlock/ff_div_3}]]
create_clock -name {CyPeriClk_App} -period 20 -waveform {0 10} [list [get_pins {ClockBlock/periclk_App}]]
create_clock -name {CyIMO} -period 125 -waveform {0 62.5} [list [get_pins {ClockBlock/imo}]]


# Component constraints for C:\Projects\ENGG4000\software\firmware\ENGG4000_Firmware\Wearable_Firmware.cydsn\CE220818_I2C_Master_High_Level01.cydsn\TopDesign\TopDesign.cysch
# Project: C:\Projects\ENGG4000\software\firmware\ENGG4000_Firmware\Wearable_Firmware.cydsn\CE220818_I2C_Master_High_Level01.cydsn\CE220818_I2C_Master_High_Level01.cyprj
# Date: Mon, 24 Feb 2020 14:10:37 GMT
