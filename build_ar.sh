#!/bin/sh

# Arduino IDE 1.8.5
# Ethernet 2.0.0
# Controllino 3.0.7
# Mudbus
# BTS7960 1.0.0
# Adafruit_PWM_Servo_Driver_Library 2.4.0

IDE_PWD="../arduino-1.8.5"
BUILDER=${IDE_PWD}/arduino-builder
HARDWARE=${IDE_PWD}/hardware
PACKAGES="../packages"
BUILD_DIR="./build"
CACHE_DIR="./cache"
HASH_COMMIT="$(git rev-parse --short=8 HEAD)"
HEX_FILE_NAME="robojuice.ino.hex"
FIRMWARE_NAME="robojuice_ar_$HASH_COMMIT.hex"

if [ -d "$BUILD_DIR" ]; then
    rm -rf $BUILD_DIR
fi

if [ -d "$CACHE_DIR" ]; then
    rm -rf $CACHE_DIR
fi

mkdir -p $BUILD_DIR
mkdir -p $CACHE_DIR

$BUILDER -dump-prefs -logger=machine -hardware $HARDWARE -hardware $PACKAGES -tools $IDE_PWD/tools-builder -tools $HARDWARE/tools/avr -tools $PACKAGES -built-in-libraries $IDE_PWD/libraries -libraries $IDE_PWD/libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path $PWD/$BUILD_DIR -warnings=none -build-cache $PWD/$CACHE_DIR -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avrdude.path=$HARDWARE/tools/avr -prefs=runtime.tools.arduinoOTA.path=$HARDWARE/tools/avr -prefs=runtime.tools.avr-gcc.path=$HARDWARE/tools/avr -prefs=compiler.cpp.extra_flags=-DCOMMIT=\"$HASH_COMMIT\" -verbose ./robojuice.ino

$BUILDER -compile -logger=machine -hardware $HARDWARE -hardware $PACKAGES -tools $IDE_PWD/tools-builder -tools $HARDWARE/tools/avr -tools $PACKAGES -built-in-libraries $IDE_PWD/libraries -libraries $IDE_PWD/libraries -fqbn=arduino:avr:mega:cpu=atmega2560 -ide-version=10805 -build-path $PWD/$BUILD_DIR -warnings=none -build-cache $PWD/$CACHE_DIR -prefs=build.warn_data_percentage=75 -prefs=runtime.tools.avrdude.path=$HARDWARE/tools/avr -prefs=runtime.tools.arduinoOTA.path=$HARDWARE/tools/avr -prefs=runtime.tools.avr-gcc.path=$HARDWARE/tools/avr -prefs=compiler.cpp.extra_flags=-DCOMMIT=\"$HASH_COMMIT\" -verbose ./robojuice.ino

if [ ! -f "$BUILD_DIR/$HEX_FILE_NAME" ]; then
    echo -e "\n Error generate."
    exit 1
fi

cp $BUILD_DIR/$HEX_FILE_NAME $BUILD_DIR/$FIRMWARE_NAME
echo =======================================
echo Firmware $BUILD_DIR/$FIRMWARE_NAME
echo =======================================