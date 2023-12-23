# Long Distance Lamp

Long Distance Lamp is a project the aim to create an infrastructure between two lamp.
When a lamp get an hit, the other around the world will blink.

## Tecnologies

- Esp32
- PlatformIO
- C/C++
- MQTT

## Instruction

1. Clone the repo

```bash
git clone https://github.com/manuandru/ldl-esp32.git
```

2. Open it in VsCode with PlatformIO extension installed.

3. Modify the configuration `config.h` file in order to set an mqtt broker.

4. Flash the board.

6. Build a circuit with a LED and a Button wired to the given PINS constant in config file.

5. Enjoy it!
