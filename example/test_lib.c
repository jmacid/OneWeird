

#ifndef F_CPU
    #define F_CPU 16000000
#endif 
#include <avr/io.h>
#include <util/delay.h>


#include "..\One-Weird.h"

/////////////////////////////////////////////////////////////////////////////////////////////////
void get_lasered_ROM_code(unsigned char *rom_code, unsigned char *family_code, OneWeird ds);
/////////////////////////////////////////////////////////////////////////////////////////////////

OneWeird ds;

unsigned char low_Temp, high_Temp;
unsigned char rom_code[6], family_code;


int main(void)
{
    DDRB |= (1 << SENSOR_PORT) | (1 << LED_PORT) | (1 << SAMPLE_PORT); 
    PORTB &= ~(1 << SAMPLE_PORT);

    for(;;)
    {
        _delay_ms(100);        
        //PORTB |= (1 << LED_PORT);
        //   // toggle PD5
        // _delay_ms(250);  // delay in ms, valor maximo = 260/F_CPU in MHz
        // PORTB &= ~(1 << LED_PORT);
        // _delay_ms(250);

        // // test init
        // if(oneWire_initilization() == true)
        //  PORTB |= (1 << LED_PORT);
        
        // _delay_ms(500);        
  //       PORTB |= (1 << LED_PORT);
  //       // test write slot
  //       oneWire_write_slot(0);
  //       _delay_us(1);

  //       oneWire_write_slot(1);
  //       _delay_us(1);

  //       oneWire_write_slot(1);
  //       _delay_us(1);

  //       PORTB &= ~(1 << LED_PORT);

        
        ////////////////////////////////////////////////////////////////////////////////////////////////
        ds.oneWire_initilization();
        ds.oneWire_write_command(0xCC);
        ds.oneWire_write_command(0x44);        
        _delay_ms(500);
        _delay_ms(500);

        ds.oneWire_initilization();
        ds.oneWire_write_command(0xCC);
        PORTB |= (1 << LED_PORT);
        ds.oneWire_write_command(0xBE);
        PORTB &= ~(1 << LED_PORT);

        //oneWire_write_command(0xBE);
        //oneWire_write_slot(1);
        //oneWire_write_slot(0);
        //_delay_us(1);
        //oneWire_write_slot(0);

        
        _delay_us(10);
        PORTB |= (1 << LED_PORT);   
        
        low_Temp = ds.oneWire_read_byte();
        high_Temp = ds.oneWire_read_byte();

        PORTB &= ~(1 << LED_PORT);

        ////////////////////////////////////////////////////////////////////////////////////////////////


        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);
        // oneWire_read_slot();
        // _delay_us(1);

  //    oneWire_initilization();
        // oneWire_write_command(0x33);
         
        // PORTB |= (1 << LED_PORT);    
  //    for(i = 0; i < 16; i++ )
  //    {
  //        oneWire_read_slot();
  //        _delay_us(1);
  //    } 
  //    PORTB &= ~(1 << LED_PORT);
  //    _delay_ms(1);   

      // ds.oneWire_initilization();
      // ds.oneWire_write_command(0x33);  
             
      // crc_read = ds.oneWire_read_byte();   
      // rom_code1 = ds.oneWire_read_byte();
      // rom_code2 = ds.oneWire_read_byte();
      // rom_code3 = ds.oneWire_read_byte();
      // rom_code4 = ds.oneWire_read_byte();
      // rom_code5 = ds.oneWire_read_byte();
      // family_code = ds.oneWire_read_byte();

      get_lasered_ROM_code(&rom_code[0], &family_code,ds);

    }

    return 0;  // the program executed successfully
}

void get_lasered_ROM_code(unsigned char *rom_code, unsigned char *family_code, OneWeird ds)
{
  ds.oneWire_initilization();
  ds.oneWire_write_command(0x33); 

  *family_code = ds.oneWire_read_byte(); 
  *(rom_code + 0) = ds.oneWire_read_byte();
  *(rom_code + 1) = ds.oneWire_read_byte();
  *(rom_code + 2) = ds.oneWire_read_byte();
  *(rom_code + 3) = ds.oneWire_read_byte();
  *(rom_code + 4) = ds.oneWire_read_byte();
  *(rom_code + 5) = ds.oneWire_read_byte();
  ds.oneWire_read_byte(); // 1 byte CRC
}