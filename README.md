# STM32F411RE — SPI1 bare-metal reference

**Status: Educational example, NOT verified on hardware.** Fictional temperature sensor protocol, not a DWM3000 driver.

```text
main()
  └ sensor_read_temperature() — two 8-bit registers, merge, /100
     └ sensor_read_register() — CS low, address, dummy, wait, CS high
        └ spi1_transfer() — write SPI1_DR, read SPI1_DR
           └ SPI1_SR / SPI1_DR — hardware registers
```

## Pins and configuration

PA5=SCK (AF5; **shares Nucleo LD2 LED**), PA6=MISO (AF5), PA7=MOSI (AF5), PB6=CS (GPIO). Master, SPI mode 0, 8 bit, MSB-first, software NSS, prescaler /16. Assumed PCLK2=16 MHz gives SCK=1 MHz.

## Illustrative protocol

CS low, send register address `0x10`, send dummy `0x00`, capture reply, wait TXE and BSY, CS high. Then repeat for `0x11`. If the hypothetical slave replies `0x09` and `0xF6`, raw = `0x09F6` = 2550, temperature = 25.50 C.

## Caveats

- No physical slave or hardware test performed. The `temperature` variable is not a real measurement.
- No UART or display output; observe variables through a debugger.
- Polling has no timeout or error codes and can hang indefinitely.
- `spi1_transfer_buffer()` is an independent helper; caller must manage CS and correct buffer length.
- An existing STM32F411 startup/linker/project is required to compile and flash the example.
- Actual SPI sensor register formats, dummy cycles, timing, and physical pin load must be verified from its datasheet.
