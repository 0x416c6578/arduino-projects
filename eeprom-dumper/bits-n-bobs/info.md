# EEPROM Dumper
- This is a simple program I use to dump 24 / 25 series serial EEPROMS which are ubiquitous in modern embedded electronics
- To dump the EEPROM simply connect it to the SPI port of the arduino (pins 10,11,12,13 on 328p based boards)
- Then flash this to the Arduino and run picocom pointing to the Arduino serial port
- On starting picocom the raw data from the EEPROM will be dumped
- You can save this with the `-g` switch in picocom which will direct any output to a log file of your choosing