#include "configure.h"
#include "spi/spi.h"
#include "tle5012.h"
struct spi Tle5012Spi = { 
		.miso = TLE5012B_SPI_MISO_PIN,
		.mosi = TLE5012B_SPI_MOSI_PIN,
		.clk = TLE5012B_SPI_SCLK_PIN,
		.cs = TLE5012B_SPI_CS0_PIN,
		.spin = 5,
	};
void InitTle5012()
{
	spi_init(&Tle5012Spi);
}

uint16_t Tle5012_ReadAngle()
{
	uint16_t data = spi_readn(&Tle5012Spi, CMD_READ_ANGLE, 2);
	data &= 0x7FFF;
	return data;
}

uint16_t Tle5012_ReadSpeed()
{
	uint16_t data = spi_readn(&Tle5012Spi, CMD_READ_SPEED, 2);
	data &= 0x7FFF;
	return data;
}