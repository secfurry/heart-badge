#include <Adafruit_NeoPixel.h>

#define GYRO_X A3
#define GYRO_Y A4
#define GYRO_Z A5

#define LED_PIN A1
#define LED_SIZE 39
#define LED_HEARTBEAT 13

volatile bool
    lines,
    blink,
    reverse;
volatile uint8_t stage, line;

Adafruit_NeoPixel lights = Adafruit_NeoPixel(LED_SIZE, LED_PIN, NEO_GRB + NEO_KHZ800);

void loop();
void setup();

void loop_lines();
void loop_stage();
void show_stage(uint8_t);
void set_half(uint8_t, uint8_t, uint8_t);

void loop() {
    if (blink) {
        digitalWrite(LED_HEARTBEAT, HIGH);
    } else {
        digitalWrite(LED_HEARTBEAT, LOW);
    }
    if (lines) {
        loop_lines();
    } else {
        loop_stage();
        lines = random(0, 20) == 0;
    }
    blink = !blink;
}
void setup() {
    pinMode(GYRO_X, INPUT);
    pinMode(GYRO_Y, INPUT);
    pinMode(GYRO_Z, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(LED_HEARTBEAT, OUTPUT);
    analogReference(EXTERNAL);
    lights.begin();
}

void loop_lines() {
    if (line > 6) {
        line = 0;
        lines = false;
        delay(500);
        return;
    }
    uint8_t s, e;
    uint8_t r = random(0, 20);
    uint8_t g = random(0, 20);
    uint8_t b = random(0, 20);
    switch (line++) {
    case 0:
        s = 0;
        e = 3;
        break;
    case 1:
        s = 4;
        e = 12;
        break;
    case 2:
        s = 13;
        e = 21;
        break;
    case 3:
        s = 22;
        e = 28;
        break;
    case 4:
        s = 29;
        e = 33;
        break;
    case 5:
        s = 34;
        e = 36;
        break;
    case 6:
        s = 37;
        e = 38;
        break;
    }
    lights.clear();
    for (; s <= e; s++) {
        lights.setPixelColor(s, r, g, b);
    }
    lights.show();
    delay(150);
}
void loop_stage() {
    show_stage(stage);
    if (reverse) {
        stage--;
    } else {
        stage++;
    }
    if (stage > 22) {
        if (random(0, 4) != 0) {
            for(uint8_t i = 0; i < LED_SIZE; i++) {
                lights.setPixelColor(i, 0, 0, 20);
            }
            set_half(20, 0, 20);
        } else {
            for(uint8_t i = 0; i < LED_SIZE; i++) {
                lights.setPixelColor(i, 20, 0, 20);
            }
            set_half(00, 0, 20);
        }
        reverse = !reverse;
        if (reverse) {
            stage = 21;
        } else {
            stage = 0;
        }
        lights.show();
        delay(1500);
    }
    delay(150);
}
void show_stage(uint8_t m) {
    if (stage < 18 || (reverse && stage == 21)) {
        lights.clear();
    }
    lights.show();
    switch (m) {
    case 0:
        lights.setPixelColor(37, 20, 0, 20);
        lights.setPixelColor(38, 0, 0, 20);
        break;
    case 1:
        lights.setPixelColor(34, 20, 0, 20);
        lights.setPixelColor(36, 0, 0, 20);
        break;
    case 2:
        lights.setPixelColor(29, 20, 0, 20);
        lights.setPixelColor(33, 0, 0, 20);
        break;
    case 3:
        lights.setPixelColor(22, 20, 0, 20);
        lights.setPixelColor(28, 0, 0, 20);
        break;
    case 4:
        lights.setPixelColor(13, 20, 0, 20);
        lights.setPixelColor(21, 0, 0, 20);
        break;
    case 5:
        lights.setPixelColor(4, 20, 0, 20);
        lights.setPixelColor(12, 0, 0, 20);
        break;
    case 6:
        lights.setPixelColor(0, 20, 0, 20);
        lights.setPixelColor(3, 0, 0, 20);
        break;
    case 7:
        lights.setPixelColor(1, 20, 0, 20);
        lights.setPixelColor(2, 0, 0, 20);
        break;
    case 8:
        lights.setPixelColor(6, 20, 0, 20);
        lights.setPixelColor(10, 0, 0, 20);
        break;
    case 9:
        lights.setPixelColor(7, 20, 0, 20);
        lights.setPixelColor(9, 0, 0, 20);
        break;
    case 10:
        lights.setPixelColor(8, 20, 20, 20);
        break;
    case 11:
        lights.setPixelColor(7, 20, 0, 20);
        lights.setPixelColor(9, 0, 0, 20);
        break;
    case 12:
        lights.setPixelColor(6, 20, 0, 20);
        lights.setPixelColor(10, 0, 0, 20);
        break;
    case 13:
        lights.setPixelColor(5, 20, 0, 20);
        lights.setPixelColor(11, 0, 0, 20);
        break;
    case 14:
        lights.setPixelColor(14, 20, 0, 20);
        lights.setPixelColor(20, 0, 0, 20);
        break;
    case 15:
        lights.setPixelColor(23, 20, 0, 20);
        lights.setPixelColor(27, 0, 0, 20);
        break;
    case 16:
        lights.setPixelColor(30, 20, 0, 20);
        lights.setPixelColor(32, 0, 0, 20);
        break;
    case 17:
        lights.setPixelColor(35, 20, 20, 20);
        break;
    case 18:
        lights.setPixelColor(31, 20, 20, 20);
        break;
    case 19:
        lights.setPixelColor(25, 20, 20, 20);
        break;
    case 20:
        lights.setPixelColor(17, 20, 20, 20);
        break;
    case 21:
        lights.setPixelColor(8, 20, 20, 20);
        break;
    }
    lights.show();
}
void set_half(uint8_t r, uint8_t g, uint8_t b) {
    lights.setPixelColor(0, r, g, b);
    lights.setPixelColor(1, r, g, b);
    lights.setPixelColor(4, r, g, b);
    lights.setPixelColor(5, r, g, b);
    lights.setPixelColor(6, r, g, b);
    lights.setPixelColor(7, r, g, b);
    lights.setPixelColor(8, r, g, b);
    lights.setPixelColor(13, r, g, b);
    lights.setPixelColor(14, r, g, b);
    lights.setPixelColor(15, r, g, b);
    lights.setPixelColor(16, r, g, b);
    lights.setPixelColor(22, r, g, b);
    lights.setPixelColor(23, r, g, b);
    lights.setPixelColor(24, r, g, b);
    lights.setPixelColor(25, r, g, b);
    lights.setPixelColor(29, r, g, b);
    lights.setPixelColor(30, r, g, b);
    lights.setPixelColor(34, r, g, b);
    lights.setPixelColor(35, r, g, b);
    lights.setPixelColor(37, r, g, b);
}
