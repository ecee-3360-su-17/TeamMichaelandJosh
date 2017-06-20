#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> //libraries necessary for blink function
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <driverlib/gpio.h>
#include <driverlib/sysctl.h>

extern int fib(int b);
int pattern;
int n;
void blink();

int main(void) {

int a;
int i;

   a = fib(7);

  for(i=0;i<2;i++){

      if(i==0){
          n=a/10;
          if(n==0)
              continue;
            blink();


      }
      else if(i==1){

        n=a%10;
        blink();

    }
  }


    return 0;
}

int convert_to_morse(char n){ //what about if n is more than 1 digit this is sketch

    switch(n){
    case 0:
        return 0b11111;
        break;
    case 1:
        return 0b01111;
                break;
    case 2:
        return 0b00111;
                break;
    case 3:
        return 0b00011;
        break;
    case 4:
        return 0b00001;
        break;
    case 5:
        return 0b00000;
        break;
    case 6:
        return 0b10000;
        break;

    case 7:
        return  0b11000;
        break;
    case 8:
        return 0b11100;
        break;
    case 9:
        return 0b11110;
        break;
    default:
       break;




    }

}
void blink(){
    int i;

    volatile uint32_t ui32Loop;
    int state;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); //Enable GPIO port corresponding to LED
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3); //set direction as an output

    for(i=0;i<=4;i++){
        pattern = convert_to_morse(n);
        state = (pattern >> 4-i) & 0b1;
        if(state == 1){

            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //turn on LED
            for(ui32Loop = 0; ui32Loop < 4800000; ui32Loop++) //acts as delay
                    {
                    }
            GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0); //turn LED off
            for(ui32Loop = 0; ui32Loop < 1200000; ui32Loop++) //acts as delay
                    {
                    }
               }       else if(state==0){ //short blink

                        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, GPIO_PIN_3); //turn on LED
                        for(ui32Loop = 0; ui32Loop < 1600000; ui32Loop++) //acts as delay
                            {
                            }
                        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x0); //turn LED off
                        for(ui32Loop = 0; ui32Loop < 1200000; ui32Loop++)
                        { //acts as delay
                        }
                    }
    }
    for(i =0; i < 1000000; i++)//long pause between digits
            {
            }
}

