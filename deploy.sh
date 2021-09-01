# This script should be ran from the Arduino IDE installation directory
(if [[ "$#" -eq 0 ]]; then
	echo -e "Please provide a path to the project .ino file\n";
else
sudo ./arduino-cli compile --fqbn CONTROLLINO_Boards:avr:controllino_maxi $1 -p /dev/ttyACM0 -v -u
    fi )
