#ifndef __serailf_h__
#define __serailf_h__

#include <Arduino.h>

static int printf_putchar(char c, FILE *fp)
{
  ((class Print *)(fdev_get_udata(fp)))->write((uint8_t)c);
  return 0;
};

class Serialf : public Print {
  public:
    Serialf(Print *print) {
      out = print;
    };

    ~Serialf() {
      delete out;
    };

    virtual size_t write(uint8_t data) {
      out->write(data);
    };

    virtual size_t write(const uint8_t *buffer, size_t size) {
      out->write(buffer, size);
    };

    using Print::write;

    int printf(const char *format, ...);
    int printf(const __FlashStringHelper *format, ...);

  private:
    Print *out;
};

int Serialf::printf(const char *format, ...) {
  FILE f;
  va_list ap;

  fdev_setup_stream(&f, printf_putchar, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&f, this);
  va_start(ap, format);
  return vfprintf(&f, format, ap);
}


int Serialf::printf(const __FlashStringHelper *format, ...) {
  FILE f;
  va_list ap;

  fdev_setup_stream(&f, printf_putchar, NULL, _FDEV_SETUP_WRITE);
  fdev_set_udata(&f, this);
  va_start(ap, format);
  return vfprintf_P(&f, (const char *)format, ap);
}

#endif
