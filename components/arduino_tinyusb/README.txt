This is the ESP-IDF arduino_tinyusb component.
This component is normally part of binary distributions of espressif/arduino-esp32, 
and ESP Arduino depends on it. Since we're not using a binary arduino-esp32 distribution,

This code is extracted from the github.com/espressif/arduino-esp32 library 
builder (github.com/espressif/esp32-arduino-lib-builder), which generates it using a
shell script. Version numbers below were the defaults for : 
- https://docs.espressif.com/projects/arduino-esp32/en/latest/lib_builder.html
- git clone --branch release/v4.4 --recursive https://github.com/espressif/esp32-arduino-lib-builder
- Remove the arduino git pull command in tools/update-components.sh due to 4.4 being a tag not a branch.
- ./build.sh -I v4.4.7 -A tags/2.0.17 -t esp32s3
- (build.sh will download and unpack a bunch of stuff, then probably fail to build it, but hopefully that doesn't matter)
- cd components/arduino_tinyusb/tinyusb/
- git checkout ea4f9ce  # Otherwise tinyusb is too new.
- Copy components/arduino_tinyusb from esp32-arduino-lib-builder to here.
