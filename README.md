# Project Name

Baremetal-mco1-generation

## Project



### Target Hardware
	
- MCU:	STM32F446RE
- Board:	NUCLEO-F446RE
- Toolchain:	STM32CubeIDE
- Hardware- Logic Analyser

#### Feature
-
-
-

##### Project Structure
```text
├── Inc/           # Header files (None)
├── Src/           # Source files (main)
├── Startup/       # Startup assembly file
├── STM32F446RETX_FLASH.ld   # Linker script (Flash)
├── STM32F446RETX_RAM.ld     # Linker script (RAM)
├── .project / .cproject     # STM32CubeIDE project files
└── .gitignore
```
###### Usage API

```c
void mco1_m4(void);
```

**NOTE:**
- Clock source is determined from the Block Diagram in the Datasheet DS10693 Rev 11.
- Nucleo board pin for the mco1 output in PA8 - f446re schematic MB1136.

