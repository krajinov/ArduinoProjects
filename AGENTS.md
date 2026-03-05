## Cursor Cloud specific instructions

This repository is a collection of ~104 Arduino/embedded electronics sketches (`.ino` files). There is no traditional software application, web server, or test framework. The development workflow revolves around compiling sketches with the Arduino toolchain. Uploading and running sketches requires physical hardware (Arduino Uno/Mega, ESP8266/Wemos D1, ATtiny, etc.).

### Toolchain

- **Arduino CLI** is installed at `~/bin/arduino-cli` (added to `$PATH` via `~/.bashrc`).
- Board packages installed: `arduino:avr` (Uno, Mega, etc.) and `esp8266:esp8266` (Wemos D1 Mini, etc.).
- Libraries are in `~/Arduino/libraries/`. Some were installed via `arduino-cli lib install`, others cloned from GitHub/Bitbucket (ManchesterRF, Manchester, TimerFreeTone, VirtualWire, SFE_BMP180).

### Compiling sketches

```bash
# Arduino Uno target (most sketches)
arduino-cli compile --fqbn arduino:avr:uno "Weekend Projects TG/I2C_Scanner/I2C_Scanner.ino"

# Arduino Mega target (e.g. YMFC flight controller)
arduino-cli compile --fqbn arduino:avr:mega "Projects/YMFC-AL/YMFC-AL_Flight_controller/YMFC-AL_Flight_controller.ino"

# ESP8266 / Wemos D1 Mini target (WiFi/IoT sketches)
arduino-cli compile --fqbn esp8266:esp8266:d1_mini "Weekend Projects MO/2017Q2/webserver_mdns/webserver_mdns.ino"
```

### Known issues

- Some older sketches use library APIs that have changed in newer versions (e.g. `LiquidCrystal_I2C` constructor with `POSITIVE`, DS3232RTC v3.x removed the global `RTC` object, Blynk v1.3+ requires `BLYNK_TEMPLATE_ID`). These are pre-existing compatibility issues, not environment problems.
- The `ArduBot` directory has a filename casing mismatch (`arduBot.ino` vs directory `ArduBot`), which prevents `arduino-cli` from compiling it.
- No lint, automated tests, or CI exist in this repository.
- Uploading sketches to boards is not possible in the cloud VM (requires USB/serial connection to physical hardware).
