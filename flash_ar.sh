#!/bin/sh

IDE_PWD="../arduino-1.8.5"
HARDWARE=${IDE_PWD}/hardware
BUILD_DIR="./build"
HASH_COMMIT="$(git rev-parse --short=8 HEAD)"
FIRMWARE_NAME="robojuice_ar_$HASH_COMMIT.hex"

if [ ! -f "$BUILD_DIR/$FIRMWARE_NAME" ]; then
    echo "\n Can't find the file $FIRMWARE_NAME."
    exit 1
fi

for key in "$@"
do
case $key in
    --port=*)
    PORT="${key#*=}"
        ;;
    *)
        echo "Invalid option."
        exit 1
        ;;
esac
done

if [ -z $PORT ]; then
    echo "Error. Set --port option."
    exit 1
fi

$HARDWARE/tools/avr/bin/avrdude -C$HARDWARE/tools/avr/etc/avrdude.conf -v -patmega2560 -cwiring -P$PORT -b115200 -D -Uflash:w:$BUILD_DIR/$FIRMWARE_NAME:i