#include "mbed.h"
#include "uLCD_4DGL.h"
#define S 8
using namespace std::chrono;
InterruptIn buttom_up(D13);
InterruptIn buttom_down(D12);
InterruptIn buttom_select(D11);
uLCD_4DGL uLCD(D1, D0, D2); // serial tx, serial rx, reset pin;
AnalogOut Aout(PA_4); // D7 pin
AnalogIn Ain(A0);
Thread g, s;
Ticker counter;
int cnt = 0;
long int  period;
int freq = 1;
int selected = 0;
int selection =2;
bool sampling = 0;
float out;
void count_func() {
    cnt++;
}
void freq_up(){
    selection++;
    if(selection > 2) selection = 1;
}
void freq_down(){
    selection--;
    if(selection < 1) selection = 2;
}
void select_isr(){
    selected = 1;
}
void generator_thread() {

    float i;
    while(1) {
        if (1) {
            if (selection == 1) {        // 200Hz
                for (i = 0.0f; i < 1; i+=0.0075635f) {
                    Aout = i;
                }
                for (i = 1.0f; i > 0.0f; i -= 0.001896f) {
                    Aout = i;
                }
            }
            else if (selection == 2) {        // 20Hz
                for (i = 0.0f; i < 1; i+=0.00074635f) {
                    Aout = i;
                }
                for (i = 1.0f; i > 0.0f; i -= 0.0001776f) {
                    Aout = i;
                }
            }    
        }
    }
}
int sample = 500;
float ADCdata[500];
void sample_thread() {
    int i = 0;
    sampling = 1;
    // t.start();
    for (i = 0; i < sample; i++){
        // Aout = Ain;
        ADCdata[i] = Ain;
        ThisThread::sleep_for(1000ms/sample); // sampling rate = 500/s 實際55/s
    }
    sampling = 0;
    //t.stop();
    //auto ms = chrono::duration_cast<chrono::milliseconds>(t.elapsed_time()).count();
    for (i = 0; i < sample; i++) {
        printf("%f\r\n", ADCdata[i]);
    }
    //printf ("Timer time: %llu ms\n", ms);
}
int main() {
    uLCD.reset();
    uLCD.background_color(0);
    uLCD.cls();
    uLCD.printf("108061213_HW2\n");
    uLCD.printf("cutoff freq 152Hz\n");
    uLCD.text_width(2); //3X size text
    uLCD.text_height(2);
    uLCD.color(GREEN);
    uLCD.locate(1,2);
    uLCD.printf("200Hz");
    uLCD.locate(1,4);
    uLCD.printf("20Hz");
    buttom_down.rise(&freq_down);
    buttom_up.rise(&freq_up);
    buttom_select.rise(&select_isr);
    g.start(generator_thread);
    while(selected != 1) {
        //  uLCD.locate(0,3);
        //         uLCD.printf("%d",selection);
       switch(selection){
           case 1: 
                // uLCD.textbackground_color(WHITE);
                uLCD.locate(0,2);
                uLCD.printf("-");
                uLCD.locate(0,4);
                uLCD.printf(" ");
                break;
            case 2: 
                // uLCD.textbackground_color(WHITE);
                uLCD.locate(0,2);
                uLCD.printf(" ");
                uLCD.locate(0,4);
                uLCD.printf("-");
                break;
                // uLCD.printf("error");
       }
    }
    uLCD.locate(0,6);
    uLCD.printf(" start!");

    sample_thread();
    uLCD.locate(0,6);
    uLCD.printf(" done!");
    
}
