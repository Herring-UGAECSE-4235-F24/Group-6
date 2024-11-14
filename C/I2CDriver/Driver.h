#ifndef driver_H
#define driver_H

int i2c_setup(int sda, int scl);
int i2c_write(int bytes[8]);
int i2c_send(char byte[]);
void i2c_read(char thing[]);
#endif
