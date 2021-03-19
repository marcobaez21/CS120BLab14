/*	Author: Marco Baez
 *  Partner(s) Name: NA
 *	Lab Section:021
 *	Assignment: Lab #14  Exercise Advancement 3
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
#include <stdlib.h>
#include <time.h>
#endif


typedef struct task{
        int state;
        unsigned long period;
        unsigned long elapsedtime;
        int(*TickFct)(int);
} task;

task tasks[7];

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
        for(i=0;i<7;i++){
                if(tasks[i].elapsedtime>=tasks[i].period){
                        tasks[i].state=tasks[i].TickFct(tasks[i].state);
                        tasks[i].elapsedtime=0;
                }
                tasks[i].elapsedtime+=1;
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

void transmit_data(unsigned char data, unsigned char port){//I acknowledge this is pretty stupid and barely qualifies under the requirement of doing it in one func, but hey it works
	
	 data = (data & 0xF0) >> 4 | (data & 0x0F) << 4; 
    data = (data & 0xCC) >> 2 | (data & 0x33) << 2;
    data = (data & 0xAA) >> 1 | (data & 0x55) << 1;

	if(port==1){
	int i;
	for(i=0;i<8;++i){
		PORTC=0x08;
		PORTC|=((data>>i)&0x01);
		PORTC|=0x02;
 	}
 	PORTC|=0x04;
 	PORTC=0x00;}
else if(port==2){
	int j;
	for(j=0;j<8;++j){
        	PORTD=0x08;
       	        PORTD|=((data>>j)&0x01);
        	PORTD|=0x02;
 	}
 PORTD|=0x04;
 PORTD=0x00;


}


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
unsigned char wasleft = 0x00;
unsigned char wasright = 0x00;
int rnum = 0;
unsigned char lbutton=0x00;
unsigned char rbutton=0x00;
unsigned char AIBOOL = 0x01;
unsigned char dontdisplay=0x00; 
unsigned char score = 0x00;
unsigned char chance = 80;

enum AIStates{checkAI, startAI, NoAIStart, bshiftl, bshiftr};
int AI_tick(int aistate){
	rnum=rand()%100;
	lbutton=(~PINA>>5)&0x01;
        rbutton=(~PINA>>6)&0x01;
	switch(aistate){
		case checkAI:
			if(AIBOOL==0x00){aistate=NoAIStart;}
			if(AIBOOL==0x01){aistate=startAI;}
			break;
		case startAI:
			if(chance>10&&score>2){chance=chance-10;}
			if(ballx==1&&rnum<chance){pattern[2]=0x07;}
			else if(ballx==2&&rnum<chance){pattern[2]=0x07;}
			else if(ballx==3&&rnum<chance){pattern[2]=0x0E;}
			else if(ballx==4&&rnum<chance){pattern[2]=0x1C;}
			else if(ballx==5&&rnum<chance){pattern[2]=0x38;}
			else if(ballx==6&&rnum<chance){pattern[2]=0x70;}
			else if(ballx==7&&rnum<chance){pattern[2]=0xE0;}
			else if(ballx==8&&rnum<chance){pattern[2]=0xE0;}
			aistate=startAI;
			break;
		case NoAIStart:
			if(lbutton&&!rbutton){aistate=bshiftl;}
			else if(!lbutton&&rbutton){aistate=bshiftr;}
			else{aistate=NoAIStart;}
			break;
		case bshiftl:
			if(lbutton){aistate=bshiftl;}
			else{aistate=NoAIStart;}
			break;
		case bshiftr:
			if(rbutton){aistate=bshiftr;}
			else{aistate=NoAIStart;}
			break;
	}

	switch(aistate){
		case checkAI:
			break;
		case startAI:
			break;
		case NoAIStart:
			break;
		case bshiftl:
			if(pattern[2]==0xE0){pattern[2]=0xE0;}
			else{pattern[2]=pattern[2]<<1;}
			break;
		case bshiftr:
			if(pattern[2]==0x07){pattern[2]=0x07;}
			else{pattern[2]=pattern[2]>>1;}
			break;
	}

    return aistate;	
}

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

			
	}
	return bstate;
}

unsigned char bx = 0x00;
unsigned char countx = 0x00;
unsigned char paddleleftx = 0x00;
unsigned char paddlerightx = 0x00;
enum bxstates{ballstart, movexball,keepleft,keepright};
int movexball_tick(int bxstate){
//	paddleleftx=paddlecenterx+1;
//	paddlerightx=paddlecenterx-1;
	switch(bxstate){
		case ballstart:
			bxstate=movexball;
			break;

		case movexball:
			if(bally==1){
				if((wasleft==0x01)&&(ballx==paddlecenterx+1)){bxstate=keepright;tasks[3].period-=5;}
				else if((wasleft==0x01)&&(ballx==paddlecenterx-1)){bxstate=keepright;tasks[3].period-=5;}
				else if((wasleft==0x01)&&(ballx==paddlecenterx)){bxstate=keepleft;tasks[3].period+=5;}
				else if((wasright==0x01)&&(ballx==paddlecenterx+1)){bxstate=keepleft;tasks[3].period-=5;}
				else if((wasright==0x01)&&(ballx==paddlecenterx-1)){bxstate=keepleft;tasks[3].period-=5;}
				else if((wasright==0x01)&&(ballx==paddlecenterx)){bxstate=keepright;tasks[3].period+=5;}
				else if((wasleft==0x00&&wasright==0x00)&&(ballx==paddlecenterx+1)){bxstate=keepleft;tasks[3].period-=5;}
				else if((wasleft==0x00&&wasright==0x00)&&(ballx==paddlecenterx-1)){bxstate=keepright;tasks[3].period-=5;}
				else if((wasleft==0x01||wasright==0x01)&&(ballx!=paddlecenterx+1&&ballx!=paddlecenterx&&ballx!=paddlecenterx-1)){bxstate=ballstart;score++;}
			//		bxstate=reset;

			}
			break;
		case keepleft:
			if(bally==1){bxstate=movexball;}
			else{
				if(ballx==8){bxstate=keepright;}//have to change it so it goes back to case movexball
					else if(ballx==1){pattern[1]=0x02;/*ballx=2;*/}
					else if(ballx==2){pattern[1]=0x04;/*ballx=3;*/}
					else if(ballx==3){pattern[1]=0x08;/*ballx=4;*/}
					else if(ballx==4){pattern[1]=0x10;/*ballx=5;*/}
					else if(ballx==5){pattern[1]=0x20;/*ballx=5;*/}
					else if(ballx==6){pattern[1]=0x40;/*ballx=7;*/}
					else if(ballx==7){pattern[1]=0x80;/*ballx=8;*/}
					ballx++;
					wasleft=0x01;
					wasright=0x00;
					}
				
		//	ballx++;
			break;
		case keepright:
			if(bally==1){bxstate=movexball;}
			else{
			if(ballx==1){bxstate=keepleft;}
				else if(ballx==8){pattern[1]=0x40;/*ballx=7;*/}
				else if(ballx==7){pattern[1]=0x20;/*ballx=6;*/}
				else if(ballx==6){pattern[1]=0x10;/*ballx=5;*/}
				else if(ballx==5){pattern[1]=0x08;/*ballx=4;*/}
				else if(ballx==4){pattern[1]=0x04;/*ballx=3;*/}
				else if(ballx==3){pattern[1]=0x02;/*ballx=2;*/}
				else if(ballx==2){pattern[1]=0x01;/*ballx=1;*/}
				ballx--;
				wasleft=0x00;
				wasright=0x01;
			
		}
		//	ballx--;

			break;
	}
return bxstate;
}

unsigned char button = 0x00;
enum gstates{initgame, menu, startgame, resetgame};
int game_tick(int gstate){
	button=(~PINA>>4)&0x01;
	lbutton=(~PINA>>5)&0x01;
	rbutton=(~PINA>>6)&0x01;	
     switch(gstate){	
	case initgame:
//		if(button==0x00){gstate=menu;}
//		else if(button==0x10){gstate=resetgame;}
		gstate=menu;
		break;
	case menu:
	//	transmit_data(0,1);
	//	transmit_data(0xFF,2);
		PORTB=0x19;
	//	PORTB=0xFF;
		if(lbutton&&!rbutton){gstate=startgame;AIBOOL=0x00;/*PORTB=0xFF;*/}
		else if(!lbutton&&rbutton){gstate=startgame;AIBOOL=0x01;}
		else{gstate=menu;}
		dontdisplay=0x01;
		break;
	case startgame:
	//	if(button==0x00){gstate=menu;}
	//	else if(button==0x10){gstate=resetgame;}
		PORTB=score;
		dontdisplay=0x00;
		gstate=startgame;
		break;
	case resetgame:
	//	for(int i=0;i<10;i++){
		pattern[0]=0x07;
		pattern[1]=0x10;
		pattern[2]=0x38;
		row[0]=0xFE;
		row[1]=0xFD;
		row[2]=0xEF;
		ballx=5;
		bally=2;
		wasleft=0;
		wasright=0;
		gstate=initgame;
		
		break;
	}
     return gstate;

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
	if(dontdisplay==0x00){
	transmit_data(temp_pattern,1);
	transmit_data(temp_row,2);
	transmit_data(0,1);
	transmit_data(0xFF,2);}
//	PORTC=0xFF;
//	PORTD=0xFB;
	return state;
}

int main(void) {
    DDRA=0x00; PORTA=0xFF;
    DDRB=0xFF; PORTA=0x00;
    DDRC=0xFF; PORTC=0x00;
    DDRD=0xFF; PORTD=0x00;
    A2D_init();
    srand(time(0));
    unsigned char temp2 = 0x00;
    tasks[temp2].state=RefreshADC;
    tasks[temp2].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&tick_ADC;
    ++temp2;
    tasks[temp2].state=start;
    tasks[temp2].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&tick_LEDS;
    ++temp2;
    tasks[temp2].state=moveball;
    tasks[temp2].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&moveball_tick;
    ++temp2;
    tasks[temp2].state=ballstart;
    tasks[temp2].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&movexball_tick;
    ++temp2;    
    tasks[temp2].state=startAI;
    tasks[temp].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&AI_tick;
    ++temp2;
    tasks[temp2].state=initgame;
    tasks[temp2].period=100;
    tasks[temp2].elapsedtime=0;
    tasks[temp2].TickFct=&game_tick;
    ++temp2;
    tasks[temp2].state=StartLED;
    tasks[temp2].period=2;
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
