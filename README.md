GPIO
----
***

> [⇧ **Home**](https://github.com/iotkitv4/intro)

Allzweckeingabe/-ausgabe (engl. GPIO - General Purpose Input/Output) ist ein allgemeiner Kontaktstift (Pin) an einem Mikrocontroller, dessen Verhalten, unabhängig, ob als Eingabe- oder Ausgabekontakt, durch logische Programmierung frei bestimmbar ist. GPIO-Kontakten ist kein Zweck vorgegeben, sie sind daher standardmäßig unbelegt.

Mittels folgender Grundklassen kann den GPIO Pins ein Zweck vorgegeben werden:

* [DigitalOut](#DigitalOut) -  Pin zwischen 0 (0 Volt) und 1 (3.3 Volt) hin und her schalten.
* [DigitalIn](#DigitalIn)  - liefert je nach Spannung: 0 Volt eine 0 oder 3.3 - 5 Volt eine 1.
* [AnalogIn](#AnalogIn)    - Umsetzung eines Analogssignals in einen Wert.
* [PwmOut](#pwmout---pulsweitenmodulation) -  Pulsweitenmodulation für die Erzeugung einer elektrische Spannung zwischen Ground (0 Volt) und 3.3 Volt.

Standard Pins sind mit **D0 - D15**, **A0 - A5** (analog Arduino) oder **PTxx** gekennzeichnet. **RX/TX**, **SDA,SCL** und **SS, MOSI, MISO, SLCK** sind Pins für Bussysteme. 
Daneben sind  Pin mit Ground (**GND**) und +5 Volt (**+5V**) vorhanden um die Verkabelung von externen Sensoren und Aktoren zu vereinfachen.

**Weitere Beispiele**

* [Encoder Switch](#encoder-switch) - zählt die Impulse am Encoder und schaltet einen Zähler vor und zurück.
* [Übungen](#Übungen)

## DigitalOut
***

> [⇧ **Nach oben**](#gpio)

![](images/DigitalOut.png)

Sinnbildliche Darstellung für den Anschluss eines LEDs. Der Name des Pins ist entsprechend Anzupassen.

- - -

Mittels DigitalOut kann ein Pin zwischen 0 (0 Volt) und 1 (3.3 Volt) hin und her geschaltet werden.

**Definition**

	DigitalOut led1( <GPIO-Pin Name> );
	
**Ansteuerung**

On

	led1 = 1;
	led1.write( 1 );

Off
	
	led1 = 0;
	led1.write( 0 );
	
Beide Varianten bei On/Off geben das gleiche Ergebnis. Die LED wird ein- und ausgeschaltet. Die erste Variante verwendet [Operator Overloading von C++] und die zweite die Methode `write`.

### Anwendungen 

*   Ansteuerung von LEDs, z.B. für Taschenlampe, [Kultpfunzel](http://kultpfunzel.ch/) , [Fernsehsimulator,](http://www.pearl.ch/ch-a-NC5312-3110.shtml) [Kleidung](http://www.get-a-led.de/led-t-shirts/led-kleidung-stereo-mc/), Statusanzeigen etc.
*   2 DigitalOut für die Richtungsbestimmung bei Motoren
*   4 DigitalOut für die Ansteuerung von Schrittmotoren

Siehe auch: [mbed Handbook](https://os.mbed.com/docs/mbed-os/latest/apis/digitalout.html) und [YouTube Tutorial](https://www.youtube.com/watch?v=kP_zHbC_5eM)

### Beispiel(e)

Das Beispiel [DigitalOut](main.cpp) steuert die LEDs 1 - 4 nacheinnander an.

## DigitalIn
***

> [⇧ **Nach oben**](#gpio)

![](images/DigitalIn.png)

Schematische Darstellung: Anschluss eines Buttons
- - -

DigitalIn liest den Status eines Pins (als Input Bezeichnet) aus.

DigitalIn liefert je nach Spannung: 0 Volt eine 0 oder 3.3 - 5 Volt eine 1.

Damit Eindeutig zwischen 0 und 1 unterschieden werden kann, wird in der Regel mit PullUp Widerständen gearbeitet. Dies kann durch den internen PullUp Widerstand (zweiter Parameter bei DigitalIn, Default = ON).

### Anwendungen 

*   Externer Feedback, z.B. Taster.
*   Sensoren welche bei Eintreten eines Ereignisses zwischen 0 und 1 umschalten, z.B. Bewegungsmelder

**Siehe auch:** [mbed Handbook](https://os.mbed.com/docs/mbed-os/latest/apis/digitalin.html) und [YouTube Tutorial](https://www.youtube.com/watch?v=XmWqP8laxxk)

### Beispiel(e)

Das Beispiel frägt den Taster vom Button ab.

<details><summary>main.cpp</summary>  

    /** DigitalIn liest den Status eines Pins aus.
    */
    #include "mbed.h"

    DigitalIn button1( BUTTON1 );
    DigitalOut led1( LED2 );

    // Wartezeit
    #define WAIT_TIME    1000   

    int main()
    {
        while   ( 1 ) 
        {
            led1 = 0;
            if  ( button1 == 0 ) 
            {
                led1 = 1;
                thread_sleep_for( WAIT_TIME );
            }

        }
    }
</p></details>

## AnalogIn
***

> [⇧ **Nach oben**](#gpio)

![](images/AnalogIn.png)

Sinnbildliche Darstellung eines Analogen Signals
- - -

Ein Analogsignal ist ein Signals mit stufenlosem und unterbrechungsfreiem Verlauf

In der Elektronik erfolgt die Umsetzung eines elektrischen Analogsignals in ein nutzbares Digitalsignal mittels Analog-Digital-Umsetzern (ADU), die umgekehrte Richtung erfolgt mittels Digital-Analog-Umsetzern (DAU).

Die Pins A0 - A5 haben integrierte Analog-Digital-Umsetzer. AnalogIn macht sich das zunutze und liefert die aktuelle analoge Spannung in Prozent (0.0 - 1.0) oder als short (0 - 65535).

### Anwendungen

*   Auslesen eines Sensorwertes, z.B. Lichtintensität
*   Zusammen mit einen [Potentiometer](http://de.wikipedia.org/wiki/Potentiometer) um einen Schwellenwert für ein Ereignis, z.B. für das Anschalten des Lichtes, oder um die Geschwindigkeit für einen Motor einzustellen.

**Siehe auch:** [mbed Handbook](https://os.mbed.com/docs/mbed-os/latest/apis/analogin.html) und [YouTube Tutorial](https://www.youtube.com/watch?v=LLXJ3KE1XZw)

### Beispiel(e)

Das Beispiel frägt den Hallsensor (zur Ermittelung des Nord- oder Südpols eines Magneten) ab und bringt bei entsprechendem Pol die LED 1 zum leuchten.

<details><summary>main.cpp</summary>  

    /** Liest die analoge Spannung an einem Pin.
        Hier das Poti an A0
    */
    #include <mbed.h>

    AnalogIn hallSensor( A3 );
    DigitalOut led1( LED1 );

    // Wartezeit
    #define WAIT_TIME    1000      

    int main()
    {
        while   ( 1 )
        {
            printf("Hall %f\n", hallSensor.read() );
            if  ( hallSensor.read() < 0.5f )          // in Prozent
                led1 = 1;
            else
                led1 = 0;
                
            thread_sleep_for( WAIT_TIME );
        }     
    }
</p></details>

## PwmOut - Pulsweitenmodulation
***

> [⇧ **Nach oben**](#gpio)

![](images/PWMOut.png)

Sinnbildliche Darstellung eines PWM Signals

- - -

[Pulsweitenmodulation](http://de.wikipedia.org/wiki/Pulsweitenmodulation) (kurz PWM), ist eine Modulationsart, bei der die elektrische Spannung zwischen Ground (0 Volt) und 3.3 Volt wechselt.

Die relative Länge des Pulses wird Tastgrad (englisch duty cycle) genannt.

Der Abstand zwischen dem Startpunkt zwei aufeinanderfolgender Pulse wird "Periode" genannt.

PwmOut kann nur mit Pins verwendet werden, welche mit PWM bezeichnet sind.

### Anwendungen 

*   Licht dimmen
*   Motoren Geschwindigkeit regeln
*   Töne erzeugen

Siehe auch: [mbed Handbook](https://os.mbed.com/docs/mbed-os/latest/apis/pwmout.html) und [YouTube Tutorial](https://www.youtube.com/watch?v=J5lsM1k-r-g&list=PLWy-YwxbAu8FDpD2saP1p6IFHgvbzODyc&index=3)

### Beispiel(e)

Das Beispiel PWMOut dimmt die LED 4 langsam auf.

<details><summary>main.cpp</summary>  

    /** Pulsweitenmodulation
    */
    #include "mbed.h"

    PwmOut led( LED4 );

    int main()
    {
        for ( float i  = 0.0; i < 1.0f; i += 0.01f )
        {
            led = i;
            thread_sleep_for ( 100 );
        }
    }
</p></details>


Das Beispiel PwmOutPeriod (nur IoTKitV3 Shield) emuliert eine Polizeisierene mit dem Buzzer (Summer).


<details><summary>main.cpp</summary>  

    /** Pulsweitenmodulation - Generieren eines x Hz Tones mittels PWM
    *  Dip Switch SW4 aktivieren (nach oben)
    */
    #include "mbed.h"

    PwmOut speaker( D12 );

    int main()
    {
        while   ( 1 ) 
        {
            // Polizei Sirene
            speaker.period( 1.0 / 3969.0 );      // 3969 = Tonfrequenz in Hz
            speaker = 0.5f;
            thread_sleep_for ( 500 );
            speaker.period( 1.0 / 2800.0 );
            thread_sleep_for ( 500 );
        }
    }
</p></details>

## Encoder Switch
***

> [⇧ **Nach oben**](#gpio)

Ein Encoder Switch - zählt die Impulse am Encoder und schaltet einen Zähler vor und zurück

### Anwendungen

* Wert hoch- und runterzählen, z.B. um einen Motor zu Steuern, eine Lautstärke einzustellen etc.

### Beispiel(e)

* Das Beispiel EncoderSwitch (nur IoTKitV3 Board) gibt die Anzahl Pulse auf dem Display aus.

<details><summary>main.cpp</summary>  

    /** EncoderSwitch - zaehlt die Impulse am Encoder und schalter Zaehler vor und zurueck
    */
    #include "mbed.h"
    #include "QEI.h"
    #include "OLEDDisplay.h"

    OLEDDisplay oled( MBED_CONF_IOTKIT_OLED_RST, MBED_CONF_IOTKIT_OLED_SDA, MBED_CONF_IOTKIT_OLED_SCL );

    //Use X4 encoding.
    //QEI wheel(p29, p30, NC, 624, QEI::X4_ENCODING);
    //Use X2 encoding by default.
    QEI wheel (MBED_CONF_IOTKIT_BUTTON2, MBED_CONF_IOTKIT_BUTTON3, NC, 624);
    
    int main() 
    {
        int value, old = 0;
        oled.clear();
        oled.printf( "Encoder Test\n" );
    
        while(1)
        {
            oled.cursor( 1, 0 );
            value = wheel.getPulses(); 
            if  ( value != old )
                oled.printf("Pulses: %6i\n", value );
            old = value;
            thread_sleep_for( 100 );
        }
    }
</p></details>

## Übungen
***

> [⇧ **Nach oben**](#gpio)

### DigitalIn, DigitalOut, if, wait

Schreibt ein Programm welches eine der vier LED's bei Druck einer Taste 3 lang Sekunden aufleuchten lässt.

* Anwendung: Licht Treppenhaus.

<details><summary>Lösung</summary>  

    /** 1. LED x Sekunden aufleuchten bei Tastendruck (if, wait)
    */
    
    #include "mbed.h"
    
    DigitalIn   button1( MBED_CONF_IOTKIT_BUTTON1 );        // User Button
    DigitalOut  led( MBED_CONF_IOTKIT_LED1 );     			// 1. LED
    
    int main()
    {
        while ( true ) 
        {
            if  ( button1 == 0 )        // Button gedrueckt
            {
                led = 1;
                thread_sleep_for ( 3000 );
                led = 0;
            }
        }
    }
</p></details>


### DigitalOut, for Verschachtelt, wait, Array's

Erstellt eine Array welche die 4 LED anhand einer Pseudo Melodie aufleuchten lässt.

* Anwendung: Fernseher Simulation um Einbrecher abzuschrecken.

<details><summary>Lösung</summary> 

    /** 4.4 Melodie visualisieren (for Verschachtelt, wait, Array's)
    */
    #include "mbed.h"

    DigitalOut led[] =  { DigitalOut( MBED_CONF_IOTKIT_LED1 ), DigitalOut( MBED_CONF_IOTKIT_LED2 ), DigitalOut( MBED_CONF_IOTKIT_LED3 ), DigitalOut( MBED_CONF_IOTKIT_LED4 ) };

    int m[15][4] = {
                    { 1, 0, 0, 1 },
                    { 1, 1, 1, 1 },
                    { 1, 1, 0, 0 },
                    { 0, 1, 0, 1 },
                    { 1, 1, 1, 1 },
                    { 1, 1, 0, 1 },
                    { 1, 0, 0, 1 },
                    { 1, 1, 0, 1 },
                    { 1, 0, 1, 1 },
                    { 0, 0, 0, 1 },
                    { 1, 0, 0, 1 },
                    { 1, 1, 0, 0 },
                    { 1, 0, 0, 1 },
                    { 1, 0, 0, 1 },
                    { 1, 0, 0, 1 }
                };
                    

    int main()
    {
        while (true) 
        {
            // row
            for ( int r = 0; r < 14; r++ )
            {
                // column
                for ( int c = 0; c < 4; c++ )
                    led[c] = m[r] [c];
                thread_sleep_for( 200 );
            }
        }
    }
</p></details>

### Adaptieren bestehender Beispiele - Melodie abspielen

BBaut das [Using a Speaker for Audio Output Beispiel](https://os.mbed.com/users/4180_1/notebook/using-a-speaker-for-audio-output/) auf den Summer um.

* Anwendung: Türglocke, Alarmanlage, Polizeihorn. 

<details><summary>Lösung</summary>  

    /** 4.5 Melodie abspielen
    */
    #include "mbed.h"

    // speaker sound effect demo using PWM hardware output
    PwmOut speaker( MBED_CONF_IOTKIT_BUZZER );

    int main()
    {
        int i;
        // generate a 500Hz tone using PWM hardware output
        speaker.period(1.0/500.0); // 500hz period
        speaker =0.5; //50% duty cycle - max volume
        thread_sleep_for(3000);
        speaker=0.0; // turn off audio
        thread_sleep_for(2000);

        // generate a short 150Hz tone using PWM hardware output
        // something like this can be used for a button click effect for feedback
        for (i=0; i<10; i++) 
        {
            speaker.period(1.0/150.0); // 500hz period
            speaker =0.25; //25% duty cycle - mid range volume
            thread_sleep_for( 20 );
            speaker=0.0; // turn off audio
            thread_sleep_for( 500 );
        }

        // sweep up in frequency by changing the PWM period
        for (i=0; i<8000; i=i+100) 
        {
            speaker.period(1.0/float(i));
            speaker=0.25;
            thread_sleep_for( 100 );
        }
        thread_sleep_for( 2000 );

        // two tone police siren effect -  two periods or two frequencies
        // increase volume - by changing the PWM duty cycle
        for (i=0; i<26; i=i+2) 
        {
            speaker.period(1.0/969.0);
            speaker = float(i)/50.0;
            thread_sleep_for( 500 );
            speaker.period(1.0/800.0);
            thread_sleep_for( 500 );
        }
        // decrease volume
        for (i=25; i>=0; i=i-2) 
        {
            speaker.period(1.0/969.0);
            speaker = float(i)/50.0;
            thread_sleep_for( 500 );
            speaker.period(1.0/800.0);
            thread_sleep_for( 500 );
        }
        speaker =0.0;
        thread_sleep_for( 2000 );
    }
</p></details>

