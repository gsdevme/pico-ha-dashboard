#include <stdio.h>
#include "hardware/spi.h"

#define SPI_PORT spi1

// Display resolution
#define DISPLAY_WIDTH       280
#define DISPLAY_HEIGHT      480

static const uint8_t lut_4Gray_GC[] =
        {
                0x2A,0x06,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
                0x28,0x06,0x14,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//2
                0x20,0x06,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
                0x14,0x06,0x28,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//4
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
                0x00,0x02,0x02,0x0A,0x00,0x00,0x00,0x08,0x08,0x02,//6
                0x00,0x02,0x02,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,//7
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//8
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//10
                0x22,0x22,0x22,0x22,0x22
        };

static const uint8_t lut_1Gray_GC[] =
        {
                0x2A,0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
                0x05,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//2
                0x2A,0x15,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
                0x05,0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//4
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
                0x00,0x02,0x03,0x0A,0x00,0x02,0x06,0x0A,0x05,0x00,//6
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//7
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//8
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//10
                0x22,0x22,0x22,0x22,0x22
        };

static const uint8_t lut_1Gray_DU[] =
        {
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//1
                0x01,0x2A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x0A,0x55,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//3
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//5
                0x00,0x00,0x05,0x05,0x00,0x05,0x03,0x05,0x05,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//7
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,//9
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,
                0x22,0x22,0x22,0x22,0x22
        };

static const uint8_t lut_1Gray_A2[] =
        {
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //1
                0x0A,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //2
                0x05,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //3
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //4
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //5
                0x00,0x00,0x03,0x05,0x00,0x00,0x00,0x00,0x00,0x00, //6
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //7
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //8
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //9
                0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00, //10
                0x22,0x22,0x22,0x22,0x22
        };

/**
 * GPIO
**/
int EPD_RST_PIN;
int EPD_DC_PIN;
int EPD_CS_PIN;
int EPD_BUSY_PIN;
int EPD_CLK_PIN;
int EPD_MOSI_PIN;

void wait_if_busy(void)
{
    uint8_t busy;
    do {
        busy = gpio_get(EPD_BUSY_PIN);

        printf("busy\r\n");
    } while(busy);

    sleep_ms(200);
}

void set_gpio_mode(uint16_t Pin, uint16_t Mode) {
    gpio_init(Pin);
    if (Mode == 0 || Mode == GPIO_IN) {
        gpio_set_dir(Pin, GPIO_IN);
    } else {
        gpio_set_dir(Pin, GPIO_OUT);
    }
}

void display_gpio_init(void) {
    EPD_RST_PIN = 12;
    EPD_DC_PIN = 8;
    EPD_BUSY_PIN = 13;

    EPD_CS_PIN = 9;
    EPD_CLK_PIN = 10;
    EPD_MOSI_PIN = 11;

    set_gpio_mode(EPD_RST_PIN, 1);
    set_gpio_mode(EPD_DC_PIN, 1);
    set_gpio_mode(EPD_CS_PIN, 1);
    set_gpio_mode(EPD_BUSY_PIN, 0);

    gpio_put(EPD_CS_PIN, 1);

    sleep_ms(10);
}

void display_spi_init(void) {
    spi_init(SPI_PORT, 4000 * 1000);
    gpio_set_function(EPD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(EPD_MOSI_PIN, GPIO_FUNC_SPI);

    sleep_ms(10);
}

void display_reset(void) {
    gpio_put(EPD_RST_PIN, 1);
    sleep_ms(50);

    gpio_put(EPD_RST_PIN, 0);
    sleep_ms(50);

    gpio_put(EPD_RST_PIN, 1);
    sleep_ms(50);
}

void display_send_command(uint8_t Value) {
    gpio_put(EPD_DC_PIN, 0);
    gpio_put(EPD_CS_PIN, 0);

    spi_write_blocking(SPI_PORT, &Value, 1);

    gpio_put(EPD_CS_PIN, 1);
}

static void display_send_data(uint8_t Value)
{
    gpio_put(EPD_DC_PIN, 1);
    gpio_put(EPD_CS_PIN, 0);

    spi_write_blocking(SPI_PORT, &Value, 1);

    gpio_put(EPD_CS_PIN, 1);
}

void display_init(void) {
    display_reset();

    display_send_command(0x12);
    sleep_ms(300);

    display_send_command(0x46);
    display_send_data(0xF7);
    wait_if_busy();
    display_send_command(0x47);
    display_send_data(0xF7);
    wait_if_busy();

    display_send_command(0x01); // setting gaet number
    display_send_data(0xDF);
    display_send_data(0x01);
    display_send_data(0x00);

    display_send_command(0x03); // set gate voltage
    display_send_data(0x00);

    display_send_command(0x04); // set source voltage
    display_send_data(0x41);
    display_send_data(0xA8);
    display_send_data(0x32);

    display_send_command(0x11); // set data entry sequence
    display_send_data(0x03);

    display_send_command(0x3C); // set border
    display_send_data(0x03);

    display_send_command(0x0C); // set booster strength
    display_send_data(0xAE);
    display_send_data(0xC7);
    display_send_data(0xC3);
    display_send_data(0xC0);
    display_send_data(0xC0);

    display_send_command(0x18); // set internal sensor on
    display_send_data(0x80);

    display_send_command(0x2C); // set vcom value
    display_send_data(0x44);

    display_send_command(0x37); // set display option, these setting turn on previous function
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x00);

    display_send_command(0x44); // setting X direction start/end position of RAM
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0x17);
    display_send_data(0x01);

    display_send_command(0x45); // setting Y direction start/end position of RAM
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_data(0xDF);
    display_send_data(0x01);

    display_send_command(0x22); // Display Update Control 2
    display_send_data(0xCF);
}

void load_lut(uint8_t lut)
{
    uint16_t i;
    display_send_command(0x32);
    for (i = 0; i < 105; i++)
    {
        if(lut == 0)
            display_send_data(lut_4Gray_GC[i]);
        else if(lut == 1)
            display_send_data(lut_1Gray_GC[i]);
        else if(lut == 2)
            display_send_data(lut_1Gray_DU[i]);
        else if(lut == 3)
            display_send_data(lut_1Gray_A2[i]);
        else
            printf("There is no such lut \r\n");
    }
}

void display_clear(void)
{
    uint16_t Width, Height;
    Width = (DISPLAY_WIDTH % 8 == 0)? (DISPLAY_WIDTH / 8 ): (DISPLAY_WIDTH / 8 + 1);
    Height = DISPLAY_HEIGHT;

    display_send_command(0x49);
    display_send_data(0x00);
    display_send_command(0x4E);
    display_send_data(0x00);
    display_send_data(0x00);
    display_send_command(0x4F);
    display_send_data(0x00);
    display_send_data(0x00);

    display_send_command(0x24);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            display_send_data(0xff);
        }
    }

    display_send_command(0x4E);
    display_send_data(0x00);
    display_send_data(0x00);

    display_send_command(0x4F);
    display_send_data(0x00);
    display_send_data(0x00);

    display_send_command(0x26);
    for (uint16_t j = 0; j < Height; j++) {
        for (uint16_t i = 0; i < Width; i++) {
            display_send_data(0xff);
        }
    }

    load_lut(0);
    display_send_command(0x22);
    display_send_data(0xC7);

    display_send_command(0x20);
    wait_if_busy();
}

//void display_clear(void) {
//    uint16_t Width, Height;
//
//    Width = (DISPLAY_WIDTH % 8 == 0)? (DISPLAY_WIDTH / 8 ): (DISPLAY_WIDTH / 8 + 1);
//    Height = DISPLAY_HEIGHT;
//}