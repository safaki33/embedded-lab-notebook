#include <stdint.h>
/* STM32F411RE SPI1 bare-metal. Illustrative sensor protocol, not hardware verified.
   PCLK2=16MHz assumed; 1MHz SPI mode 0.
   PA5=SCK(shared LD2), PA6=MISO, PA7=MOSI, PB6=CS. */
#define R32(a) (*(volatile uint32_t *)(a))
#define R16(a) (*(volatile uint16_t *)(a))
#define RCC_AHB1ENR R32(0x40023830U)
#define RCC_APB2ENR R32(0x40023844U)
#define GPIOA_MODER R32(0x40020000U)
#define GPIOA_AFRL R32(0x40020020U)
#define GPIOB_MODER R32(0x40020400U)
#define GPIOB_BSRR R32(0x40020418U)
#define SPI1_CR1 R32(0x40013000U)
#define SPI1_SR R32(0x40013008U)
#define SPI1_DR R16(0x4001300CU)
#define TEMP_HIGH_REG 0x10U
#define TEMP_LOW_REG 0x11U

static void spi1_cs_low(void) { GPIOB_BSRR = 1U << 22; }
static void spi1_cs_high(void) { GPIOB_BSRR = 1U << 6; }

static void spi1_init(void)
{
    RCC_AHB1ENR |= (1U << 0) | (1U << 1);
    RCC_APB2ENR |= 1U << 12;
    GPIOB_BSRR = 1U << 6; /* CS preloaded HIGH */
    GPIOA_MODER = (GPIOA_MODER & ~(63U << 10)) | (42U << 10);
    GPIOA_AFRL = (GPIOA_AFRL & ~((0xFU << 20)|(0xFU << 24)|(0xFU << 28)))
               | (5U << 20) | (5U << 24) | (5U << 28);
    GPIOB_MODER = (GPIOB_MODER & ~(3U << 12)) | (1U << 12);
    SPI1_CR1 = (1U << 2) | (3U << 3) | (1U << 8) | (1U << 9);
    SPI1_CR1 |= 1U << 6; /* SPE */
}

static uint8_t spi1_transfer(uint8_t data)
{
    while ((SPI1_SR & (1U << 1)) == 0U) {} /* TXE */
    SPI1_DR = data;
    while ((SPI1_SR & (1U << 0)) == 0U) {} /* RXNE */
    return (uint8_t)SPI1_DR;
}

/* CS managed by caller. length <= sizes of tx and rx. */
void spi1_transfer_buffer(const uint8_t *tx, uint8_t *rx, uint32_t length)
{
    for (uint32_t i = 0; i < length; ++i)
        rx[i] = spi1_transfer(tx[i]);
}

static void spi1_wait_complete(void)
{
    while ((SPI1_SR & (1U << 1)) == 0U) {} /* TXE */
    while ((SPI1_SR & (1U << 7)) != 0U) {} /* BSY */
}

/* Fictional slave: addr byte then dummy byte / reply. */
static uint8_t sensor_read_register(uint8_t reg_addr)
{
    spi1_cs_low();
    (void)spi1_transfer(reg_addr);
    uint8_t received = spi1_transfer(0x00U);
    spi1_wait_complete();
    spi1_cs_high();
    return received;
}

static float sensor_read_temperature(void)
{
    uint8_t high = sensor_read_register(TEMP_HIGH_REG);
    uint8_t low = sensor_read_register(TEMP_LOW_REG);
    uint16_t raw = ((uint16_t)high << 8) | low;
    return (float)raw / 100.0f;
}

int main(void)
{
    spi1_init();
    volatile float temperature = 0.0f;
    while (1) temperature = sensor_read_temperature();
}
