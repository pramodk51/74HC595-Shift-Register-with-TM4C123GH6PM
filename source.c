/*see NXP Datasheet (FOR FUNCTIONS)
 *GPIO_PIN_1=>DS
 *GPIO_PIN_2=STCP
 *GPIO_PIN_3=SHCP
 *
 *
 *
 */
#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "inc/tm4c123gh6pm.h"

int registers[8]={1,1,1,1,1,1,1,1};  //array of integers for writing it serially
int i,j,k,r,p;                           //index variables

void write_reg(){                                                        //this function writes the value of register[] to internal registers

      GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0<<2);     //clear pin2
      for( k=7;k>=0;k--)
       {
             GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0<<3);       //clear pin3
             GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,registers[k]<<1);
             GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,1<<3);      //set pin3  //shifted into 8-bit shift register(SHCP=High)
       }

      GPIOPinWrite(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,1<<2);            //shifted into 8-bit storage register(STCP=High)
       }


    int main(void)
  {

         SysCtlClockSet(SYSCTL_SYSDIV_25|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);     //source clock 8MHz (200/25)
         SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);                                            //enable peripheral portB
         GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);               //Pin configuration (pin 1,2,3 as output)

      while(1){

          for( i=0;i<8;i++){                                     //change the values in buffer
              registers[i]=0;
              SysCtlDelay(500000);
              write_reg();

                }

           for( j=7;j>=0;j--)                                       //reverse order
           {
            registers[j]=1;
            SysCtlDelay(500000);
            write_reg();

              }

           for( r=7;r>=0;r--)                                       //reverse order of pattern
            {
                registers[r]=0;
                SysCtlDelay(500000);
                write_reg();

                  }

          for( p=0;p<8;p++)                                       //reverse order
             {
                registers[p]=1;
                SysCtlDelay(500000);
                write_reg();

                  }


}

return 0;
}
