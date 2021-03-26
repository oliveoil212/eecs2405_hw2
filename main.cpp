#include "mbed.h"
#include "uLCD_4DGL.h"
#define S 8
using namespace std::chrono;
InterruptIn buttom_up(D13);
InterruptIn buttom_down(D12);
InterruptIn buttom_select(D11);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
AnalogOut Aout(PA_4); // D7 pin

Ticker counter;
int cnt = 0;
double period;
int freq = 100;
void count_func() {
    cnt++;
}
void freq_up(){
    freq++;
}
void freq_down(){
    freq--;
}
int main() {
    uLCD.reset();
    uLCD.background_color(0);
    uLCD.cls();
    uLCD.printf("108061213_HW2\n");
    buttom_down.rise(&freq_down);
    buttom_up.rise(&freq_up);
    while(buttom_select != 1) {
        uLCD.locate(2,2);
        uLCD.printf("%4d",freq);
        // printf("%d\r\n", freq);
    }
    printf("start\r\n");
    period = 1000000.0 / freq;
    // period = 10000;
    double increasing_time = period * S /10;
    double decreasing_time =period - increasing_time;
    double out;
    // std::chrono::microseconds delay(1);
    // counter.attach_us(&count_func,int (delay.count()));
    // us_timestamp_t delay = 100;
    // counter.attach_us(&count_func, delay us);
    while(1) {
        if(cnt >= period) cnt = 0;
        if(cnt >= increasing_time) {
            out = 1 -  (cnt - increasing_time) / decreasing_time;
        }
        else {
            out = cnt / increasing_time;
        }
        Aout = out;
        printf("%f", 3.3*out);
        wait_us(1);
        cnt++;
        // printf("cnt=%d out = %f de= %f in= %f\n", cnt, out, decreasing_time, increasing_time);
    }
}

