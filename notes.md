# SPI quick notes

- `SPI1_DR = data` writes to the peripheral data register and shifts one byte on MOSI. It is not `printf`.
- Full-duplex SPI also receives one byte per byte sent; MISO input is read from `SPI1_DR`.
- `spi1_transfer(0x00)` generates 8 clocks for a read response (for this *fictional* protocol).
- `TXE` SR bit 1: transmit buffer empty. `RXNE` bit 0: receive buffer contains byte. `BSY` bit 7: transfer active.
- `tx[i]` retrieves outgoing byte; `rx[i] = spi1_transfer(tx[i])` stores simultaneous incoming byte.
- `const uint8_t *tx` cannot be modified through tx; `uint8_t *rx` points to writable output; `length` required because pointer holds no array length.
- `sizeof(array)/sizeof(array[0])` works for actual arrays at their declaration scope, not for decayed pointers.
- Wait for transfer complete before raising CS; this educational polling function has no timeout.
- PA5 shares LED LD2 on Nucleo; check routing before wiring external SPI slave.
