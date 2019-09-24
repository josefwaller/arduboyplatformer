find -name "*.cpp" -exec cp {} . \;
arduino-cli compile --fqbn arduino:avr:leonardo --build-cache-path ./cache/
rm *.cpp
cmd.exe /C start ArduboyPlatformer.arduino.avr.leonardo.hex
