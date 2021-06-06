#ifndef _EPD_2IN9_H
#define _EPD_2IN9_H

#define WIDTH       128
#define HEIGHT      296

void epd_iface_setup(void (*p0)(void), void (*p1)(void),
                     void (*p2)(char), void (*p3)(char));

void epd_init(void);

void epd_clear(char v);

void epd_draw(const char *p);

#endif