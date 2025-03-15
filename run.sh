arduino-cli compile --clean -b arduino:avr:nano:cpu=atmega328old -p /dev/ttyUSB${NUMARD} && arduino-cli upload -b arduino:avr:nano:cpu=atmega328old -p /dev/ttyUSB${NUMARD}
