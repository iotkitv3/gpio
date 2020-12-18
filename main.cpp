/** Mittels DigitalOut kann eine Positive Spannung an einem Pin erzeugt werden.
*/
#include "mbed.h"

DigitalOut led1( LED1 );
DigitalOut led2( LED2 );
DigitalOut led3( LED3 );
DigitalOut led4( LED4 );

// Wartezeit
#define WAIT_TIME     500

int main()
{
    while(1) 
    {
        // kurze Schreibweise, operator= ist ueberschrieben
        led1 = 1;
        led2 = 0;
        led3 = 0;
        led4 = 0; 
        thread_sleep_for( WAIT_TIME );
        
        // Aufruf der Methode
        led1.write( 0 );
        led2.write( 1 );
        led3.write( 0 );
        led4.write( 0 ); 
        thread_sleep_for( WAIT_TIME );
        
        led1 = 0;
        led2 = 0;
        led3 = 1;
        led4 = 0; 
        thread_sleep_for( WAIT_TIME );
        
        led1 = 0;
        led2 = 0;
        led3 = 0;
        led4 = 1; 
        thread_sleep_for( WAIT_TIME );        
                
    }
}  