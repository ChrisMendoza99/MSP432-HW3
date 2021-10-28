//By: Christopher Mendoza

#include "msp.h"
#include "lcdLib_432.h"

double gas = 0.0;
double MAX = 5.0;
int cost;

void update()
{
    lcdClear();
    lcdSetText("Total Gas: ", 0, 0);
    lcdSetDouble(gas, 12, 0);


}
void reset()
{
    P5->OUT &= ~BIT2;
    P5->OUT &= ~BIT1;
    P5->OUT &= ~BIT0;
    lcdSetText("Select Octane",1,0);
    lcdSetText("87  89  93", 2, 1);
}

void pressed()
{
    update();
    gas = 0;
    while(gas < MAX)
    {
        if((P2->IN & BIT6) == 0)
        {
            delay_ms(100);
            gas+=0.100;
            update();

        }
    }
    while(gas > MAX)
         {
             if((P2->IN & BIT6) == 0){}
             else
             {
                 delay_ms(100);
                 gas+=0.100;
                 update();

             }
             if(P2->IN & BIT7)
             {
                 return;
             }
         }




}


void GPIOInit()
{
    /*Input PORTS*/
    P2->DIR |= 0x07;
    P2->REN |= 0xF8;
    P2->OUT |= 0xFF;
    P2->OUT &= ~0x07;
    /*LED Ports*/
    P5->DIR = 0x07;
    P5->OUT |= 0x07;
    P5->OUT &= ~0x07;
}

int main(void)
{
    WDT_A->CTL = WDT_A_CTL_PW | WDT_A_CTL_HOLD;     // stop watchdog timer
    /*InitStage*/
    GPIOInit();
    /*LCD greetings*/
    lcdInit();
    lcdClear();
    lcdSetText("Select Octane",1,0);
    lcdSetText("87  89  93", 2, 1);


    while(1)
    {
        if(P2->IN & 0x08){}
        else
        {
            P5->OUT |= BIT0;
            lcdClear();
            lcdSetText("87 selected",0,0);
            delay_ms(3000);
            pressed();
        }

        if(P2->IN & 0x10){}
        else
        {
            P5->OUT |= BIT1;
            lcdClear();
            lcdSetText("89 selected",0,0);
            delay_ms(3000);
            pressed();
        }
        if(P2->IN & 0x20){}
        else
        {
            P5->OUT |= BIT2;
            lcdClear();
            lcdSetText("93 selected",0,0);
            delay_ms(3000);
            pressed();
        }
        if(P2->IN & 0x80){}
        else
        {
            lcdClear();
             lcdSetText("Have a Good Day", 0, 0);
             delay_ms(3000);
             lcdClear();
             reset();
        }

    }


}




