/*	Author: Marco Baez
 *  Partner(s) Name: NA
 *	Lab Section:021
 *	Assignment: Lab #13  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *	Demo link: https://drive.google.com/drive/folders/1-1_Zf0EL01XEZT5VoUOW-SXjQH8O5fE9?usp=sharing
 */
#include <avr/io.h>
#include <avr/interrupt.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif


typedef struct task{
        int state;
        unsigned long period;
        unsigned long elapsedtime;
        int(*TickFct)(int);
} task;

task tasks[5];

volatile unsigned char TimerFlag = 0;

unsigned long _avr_timer_M = 1;
unsigned long _avr_timer_cntcurr = 0;

void TimerOn(){

        TCCR1B = 0x0B;

        OCR1A = 125;

        TIMSK1 = 0x02;

        TCNT1 = 0x02;

        _avr_timer_cntcurr = _avr_timer_M;

        SREG |= 0x80;
}

void TimerOff(){

        TCCR1B = 0x00;

}

void TimerISR(){
        //TimerFlag = 1;
        unsigned char i;
        for(i=0;i<5;i++){
                if(tasks[i].elapsedtime>=tasks[i].period){
                        tasks[i].state=tasks[i].TickFct(tasks[i].state);
                        tasks[i].elapsedtime=0;
                }
                tasks[i].elapsedtime+=50;
        }
}

ISR(TIMER1_COMPA_vect){
        _avr_timer_cntcurr--;
        if(_avr_timer_cntcurr == 0){
                TimerISR();
                _avr_timer_cntcurr = _avr_timer_M;
        }
}

void TimerSet(unsigned long M){
        _avr_timer_M = M;
        _avr_timer_cntcurr = _avr_timer_M;
}

void A2D_init(){
	ADCSRA |= (1<<ADEN)|(1<<ADSC)|(1<<ADATE);
}

unsigned short temp;
enum ADCstat{RefreshADC};
int tick_ADC(int state){
	switch(state){
		case RefreshADC:
			temp=ADC;
			break;
		default:
			state=RefreshADC;
			break;
	}
	return state;
}

static unsigned char pattern[3] = {0x07, 0x10, 0x38};
static unsigned char row[3] = {0xFE, 0xFD, 0xEF};
unsigned char paddlecenterx = 2;
unsigned char ballx = 5;
unsigned char bally = 2;

enum statesLEDS{start, shiftL, shiftR};
int tick_LEDS(int ledstate){
	
	// pattern = 0x07;
	// row = 0xFE;
	switch(ledstate){
		case start:
			if((temp>500)&&(temp<600)){ledstate=start;}
			else if(temp<500){ledstate=shiftL;}
			else if(temp>600){ledstate=shiftR;}
			break;
		case shiftL:
			if(temp<500){ledstate=shiftL;}
			else{ledstate=start;}
			break;
		case shiftR:
			if(temp>600){ledstate=shiftR;}
			else{ledstate=start;}
			break;
		default:
			break;
	}
	switch(ledstate){
		case start:
			break;
		case shiftL:
			if(pattern[0]==0xE0){pattern[0]=0xE0;paddlecenterx=7;}
			else{pattern[0]=pattern[0]<<1;paddlecenterx+=1;}
			break;
		case shiftR:
			if(pattern[0]==0x07){pattern[0]=0x07;paddlecenterx=2;}
			else{pattern[0]=pattern[0]>>1;paddlecenterx-=1;}
		default:
			break;
	}

//	PORTC=pattern;
//	PORTD=row;
	return ledstate;
}
	unsigned char countv = 0x00;
enum bstates{moveball};
int moveball_tick(int bstate){
//	countv = 0x01;
	switch(bstate){
		case moveball: 
			if(countv==0x00){row[1]=0xFD;bally=2;} //double check these values...
			else if(countv==0x01){row[1]=0xFB;bally=3;}//nvm
			else if(countv==0x02){row[1]=0xF7;bally=4;}
			else if(countv==0x03){row[1]=0xEF;bally=5;}
			else if(countv==0x04){row[1]=0xF7;bally=4;}
			else if(countv==0x05){row[1]=0xFB;bally=3;}
			else if(countv==0x06){row[1]=0xFD;bally=2;}
			else if(countv==0x07){row[1]=0xFE;bally=1;}
			countv++;
			if(countv>7){countv=0;}
		//	if cout
		//	row[1]=0xFB;

			
	}
	return bstate;
}

unsigned char bx = 0x00;
unsigned char countx = 0x00;
enum bxstates{movexball,keepleft,keepright, keepvert};
int movexball_tick(int bxstate){
	switch(bxstate){
		case movexball:
			if(bally==1){
				if(ballx==paddlecenterx){bxstate=keepvert;}
				else if(ballx==(paddlecenterx+1)){bxstate=keepleft;}
				else if(ballx==(paddlecenterx-1)){bxstate=keepright;}
			}
			break;
		case keepleft:
				if(ballx==8){bxstate=keepright;}
				else{
					if(ballx==1){pattern[1]=0x02;}
					else if(ballx==2){pattern[1]=0x04;}
					else if(ballx==3){pattern[1]=0x08;}
					else if(ballx==4){pattern[1]=0x10;}
					else if(ballx==5){pattern[1]=0x20;}
					else if(ballx==6){pattern[1]=0x40;}
					else if(ballx==7){pattern[1]=0x80;}
					ballx++;
				}
			break;
		case keepright:
			if(ballx==1){bxstate=keepleft;}
			else{
				if(ballx==8){pattern[1]=0x40;}
				else if(ballx==7){pattern[1]=0x20;}
				else if(ballx==6){pattern[1]=0x10;}
				else if(ballx==5){pattern[1]=0x08;}
				else if(ballx==4){pattern[1]=0x04;}
				else if(ballx==3){pattern[1]=0x02;}
				else if(ballx==2){pattern[1]=0x01;}
				ballx--;
			}
			break;
		case keepvert:
			ballx=paddlecenterx; //doublecheck
		//	pattern[1]=pattern[0];
			break;

//	}
}
return bxstate;
}
enum states{StartLED};
int combine_tick(int state){
//	button=~PINA&0x01;
//	button2=(~PINA>>1)&0x01;

//	static unsigned char pattern[3]  = {0x3C, 0x24, 0x3C}; //fix these two values later
//	static unsigned char row[3] = {0xF7, 0xFB, 0xFD}; 
	
	static unsigned char temp_pattern = 0x00;
	static unsigned char temp_row = 0x00;
	static unsigned char count = 0x00;

	switch(state){
		case StartLED:
			temp_pattern=pattern[count]; 
			temp_row=row[count]; 
			count++;
			if(count==3){count=0;}
	}
	PORTC=temp_pattern;
	PORTD=temp_row;
//	PORTC=0xFF;
//	PORTD=0xFB;
	return state;
}

int main(void) {
   // DDRA=0x00; PORTA=0xFF;
    DDRC=0xFF; PORTC=0x00;
    DDRD=0xFF; PORTD=0x00;
    A2D_init();
    unsigned char temp2 = 0x00;
    tasks[temp2].state=RefreshADC;
    tasks[temp2].period=500;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&tick_ADC;
    ++temp2;
    tasks[temp2].state=start;
    tasks[temp2].period=500;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&tick_LEDS;
    ++temp2;
    tasks[temp2].state=moveball;
    tasks[temp2].period=10000;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&moveball_tick;
    ++temp2;
    tasks[temp2].state=movexball;
    tasks[temp2].period=10000;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&movexball_tick;
    ++temp2;    
    tasks[temp2].state=StartLED;
    tasks[temp2].period=1;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&combine_tick;
    TimerSet(1);
    TimerOn(); 
   
    while (1) {
//	PORTC=0xFF;
//	PORTD=0xFB;
//	PORTC=0x07;
//	PORTD=0xEF;
    }
    return 1;
}
