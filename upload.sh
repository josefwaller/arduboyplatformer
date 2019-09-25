find -name "*.cpp" -exec cp {} . \;
arduino-cli compile --fqbn arduino:avr:leonardo
rm *.cpp
cmd.exe /C start ArduboyPlatformer.arduino.avr.leonardo.hex
