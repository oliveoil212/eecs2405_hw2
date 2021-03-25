#include "mbed.h"
#include "uLCD_4DGL.h"
#define S 8
using namespace std::chrono;
DigitalIn buttom_up(D13);
DigitalIn buttom_down(D12);
DigitalIn buttom_select(D11);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
AnalogOut Aout(PA_4); // D7 pin

Ticker counter;
int cnt = 0;
double period;
void counting () {
    cnt++;
}

int main() {
    // uLCD.background_color(0);
    // uLCD.cls();
    // uLCD.printf("108061213_HW2\n");
    int freq = 100;
    printf("start\r\n");
    // period = 1000000.0 / freq;
    period = 100;
    double increasing_time = period * S /10;
    double decreasing_time =period - increasing_time;
    double out;
    // std::chrono::microseconds delay(1);
    // counter.attach_us(&counting,int (delay.count()));
    while(1) {
        printf("%f   %f", increasing_time, decreasing_time);
        if(cnt >= period) cnt = 0;
        if(cnt >= increasing_time) {
            out = 1 -  (cnt - increasing_time) / decreasing_time;
        }
        else {
            out = cnt / increasing_time;
        }
        Aout = out;
        wait_us(1);
        cnt++;
        printf("cnt=%d out = %f de= %f in= %f\n", cnt, out, decreasing_time, increasing_time);
    }
    // while(buttom_select != 1) {
    //     if(buttom_up) freq+=1;
    //     if(buttom_down) freq-=1;
    //     uLCD.locate(3,2);
    //     uLCD.printf("%d",freq);
    // }
}

