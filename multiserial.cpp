#include <multiserial.h>

MultiSerial::MultiSerial() {}

void MultiSerial::addInterface(HardwareSerial* interface) {
    interfaces[interfaceCount] = interface;
    interfacesEnabled[interfaceCount] = true;
    interfaceCount++;
}

void MultiSerial::begin(unsigned long b, uint8_t m) {
    baud = b;
    mode = m;

    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            interfaces[i]->begin(baud, mode);
        }
    }
}

void MultiSerial::enableInterface(HardwareSerial* interface) {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfaces[i] == interface) {
            interfacesEnabled[i] = true;
        }
    }
}

void MultiSerial::disableInterface(HardwareSerial* interface) {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfaces[i] == interface) {
            interfacesEnabled[i] = false;
        }
    }
}

void MultiSerial::end() {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            interfaces[i]->end();
        }
    }
}

int MultiSerial::available() {
    int available = 0;

    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            available += interfaces[i]->available();
        }
    }

    return available;
}

int MultiSerial::peek() {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            if(interfaces[i]->available()) {
                return interfaces[i]->peek();
            }
        }
    }
}

int MultiSerial::read() {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            if(interfaces[i]->available()) {
                return interfaces[i]->read();
            }
        }
    }
}

int MultiSerial::availableForWrite() {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            if(!interfaces[i]->availableForWrite()) {
                return false;
            }
        }
    }

    return true;
}

void MultiSerial::flush() {
    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            interfaces[i]->flush();
        }
    }
}

size_t MultiSerial::write(uint8_t value) {
    size_t count = 0;

    for(uint8_t i = 0; i < interfaceCount; i++) {
        if(interfacesEnabled[i]) {
            count += interfaces[i]->write(value);
        }
    }

    return count;
}
