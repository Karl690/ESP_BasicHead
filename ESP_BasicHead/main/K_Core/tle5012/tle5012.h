#define CMD_READ_ANGLE        0x8021
#define CMD_READ_SPEED        0x8031
void InitTle5012();

uint16_t Tle5012_ReadAngle();
uint16_t Tle5012_ReadSpeed();