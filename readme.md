# Arduino Multiserial

Write to and read from multiple serial interfaces as if they were only a single interface.

One of my projects relies on [SerialCommand](https://github.com/kroimon/Arduino-SerialCommand)
and has two interfaces -- a BLE device I can use for interacting with it from my phone, and
a traditional Bluetooth device I use when connecting to it from my computer.  Rather than reading
and writing to both streams individually when printing messages or reading for input, I wrote
this library to abstract away the fact that multiple serial interfaces might be in use simultaneously.

## Example

```c++
#include <multiserial.h>

MultiSerial Output

def setUp() {
    // Your other setup logic
    Output.addInterface(&Serial);
    Output.addInterface(&Serial1);
    Output.begin(115200);

    Output.println("Ready");
    Output.flush();
}
```
