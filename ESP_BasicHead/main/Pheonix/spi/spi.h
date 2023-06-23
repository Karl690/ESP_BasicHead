#include "driver/gpio.h"
struct spi {
	int miso, mosi, clk, cs; // Pins
	int spin; // Number of NOP spins for bitbanging
};
bool spi_init(struct spi *spi);
void spi_begin(struct spi *spi);
void spi_end(struct spi *spi);
unsigned char spi_txn(struct spi *spi, unsigned char tx);

unsigned spi_readn(struct spi *spi, uint16_t reg, int n);