#include "spi.h"
#include "gpio/pininit.h"
bool spi_init(struct spi *spi) {
	if (spi->miso < 0 || spi->mosi < 0 || spi->clk < 0) return false;
	gpio_input(spi->miso);
	gpio_output(spi->mosi);
	gpio_output(spi->clk);
	if (spi->cs >= 0) {
		gpio_output(spi->cs);
		gpio_write(spi->cs, 1);
	}
	return true;
}

// Perform `count` "NOP" operations
static inline void spin(volatile unsigned long count) {
	while (count--) asm volatile("nop");
}

// Send a byte, and return a received byte
unsigned char spi_txn(struct spi *spi, unsigned char tx) {
	unsigned count = spi->spin <= 0 ? 9 : (unsigned) spi->spin;
	unsigned char rx = 0;
	for (int i = 0; i < 8; i++) {
		gpio_write(spi->mosi, tx & 0x80); // Set mosi
		spin(count); // Wait half cycle
		gpio_write(spi->clk, 1); // Clock high
		rx = (unsigned char)(rx << 1); // "rx <<= 1" gives warning??
		if (gpio_read(spi->miso)) rx |= 1; // Read miso
		spin(count); // Wait half cycle
		gpio_write(spi->clk, 0); // Clock low
		tx = (unsigned char)(tx << 1); // Again, avoid warning
	}
	return rx;  // Return the received byte
}


unsigned spi_readn(struct spi *spi, uint16 reg, int n) {
	unsigned rx = 0;
	spi_begin(spi);
	//spi_txn(spi, reg | 0x80);
	spi_txn(spi, (uint8_t)reg);
	spi_txn(spi, (uint8_t)(reg>>8));
	for (int i = 0; i < n; i++) rx <<= 8, rx |= spi_txn(spi, 0);
	spi_end(spi);
	return rx;
}
