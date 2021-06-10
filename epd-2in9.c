#include "epd-2in9.h"

const unsigned char epd_2in9_lut_full_update[] = {
    0x50, 0xAA, 0x55, 0xAA, 0x11, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
    0x00, 0x00, 0xFF, 0xFF, 0x1F, 0x00,
    0x00, 0x00, 0x00, 0x00, 0x00, 0x00
};

static void (*epd_wait_until_idle)(void) = 0;
static void (*epd_reset)(void) = 0;
static void (*epd_send_command)(char) = 0;
static void (*epd_send_data)(char) = 0;

void epd_iface_setup(void (*p0)(void), void (*p1)(void),
                     void (*p2)(char), void (*p3)(char))
{
    epd_wait_until_idle = p0;
    epd_reset = p1;
    epd_send_command = p2;
    epd_send_data = p3;
}

void epd_init(void)
{
    volatile char i;
    epd_reset();

    epd_send_command(0x01);
    epd_send_data((HEIGHT-1) & 0xff);
    epd_send_data(((HEIGHT-1) >> 8) & 0xff);
    epd_send_data(0x00);

    epd_send_command(0x0c);
    epd_send_data(0xd7);
    epd_send_data(0xd6);
    epd_send_data(0x9d);

    epd_send_command(0x2c);
    epd_send_data(0xa8);

    epd_send_command(0x3a);
    epd_send_data(0x1a);

    epd_send_command(0x3b);
    epd_send_data(0x08);

    epd_send_command(0x3c);
    epd_send_data(0x03);

    epd_send_command(0x11);
    epd_send_data(0x03);

    epd_send_command(0x32);
    for (i = 0; i < 30; i++) {
        epd_send_data(epd_2in9_lut_full_update[i]);
    }
}

void epd_set_window(int xs, int ys, int xe, int ye)
{
    epd_send_command(0x44);
    epd_send_data((xs >> 3) & 0xff);
    epd_send_data((xe >> 3) &0xff);

    epd_send_command(0x45);
    epd_send_data(ys & 0xff);
    epd_send_data((ys >> 8) & 0xff);
    epd_send_data(ye & 0xff);
    epd_send_data((ye >> 8) & 0xff);
}

void epd_set_cursor(int xs, int ys)
{
    epd_send_command(0x4e);
    epd_send_data((xs >> 3) & 0xff);

    epd_send_command(0x4f);
    epd_send_data(ys & 0xff);
    epd_send_data((ys >> 8) & 0xff);
}

void epd_turnon()
{
    epd_send_command(0x22);
    epd_send_data(0xc4);
    epd_send_command(0x20);
    epd_send_command(0xff);
    epd_wait_until_idle();
}

void epd_clear(char v)
{
    volatile int i, j;
    unsigned int w, h;
    w = WIDTH/8;
    h = 296;
    epd_set_window(0, 0, WIDTH, HEIGHT);
    for (i = 0; i< h; i++) {
        epd_set_cursor(0, i);
        epd_send_command(0x24);
        for (j = 0; j < w; j++) {
            epd_send_data(v);
        }
    }
}

void epd_draw(const char *p)
{
    volatile int i, j;
    unsigned int w, h;
    w = WIDTH/8;
    h = 296;
    epd_set_window(0, 0, WIDTH, HEIGHT);
    for (i = 0; i< h; i++) {
        epd_set_cursor(0, i);
        epd_send_command(0x24);
        for (j = 0; j < w; j++) {
            epd_send_data(*p++);
        }
    }
}