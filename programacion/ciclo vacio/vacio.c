/*
          _____                    _____                    _____                    _____
         /\    \                  /\    \                  /\    \                  /\    \
        /::\    \                /::\____\                /::\    \                /::\    \
       /::::\    \              /:::/    /               /::::\    \              /::::\    \
      /::::::\    \            /:::/    /               /::::::\    \            /::::::\    \
     /:::/\:::\    \          /:::/    /               /:::/\:::\    \          /:::/\:::\    \
    /:::/__\:::\    \        /:::/    /               /:::/__\:::\    \        /:::/__\:::\    \
   /::::\   \:::\    \      /:::/    /               /::::\   \:::\    \      /::::\   \:::\    \
  /::::::\   \:::\    \    /:::/    /      _____    /::::::\   \:::\    \    /::::::\   \:::\    \
 /:::/\:::\   \:::\    \  /:::/____/      /\    \  /:::/\:::\   \:::\____\  /:::/\:::\   \:::\    \
/:::/  \:::\   \:::\____\|:::|    /      /::\____\/:::/  \:::\   \:::|    |/:::/__\:::\   \:::\____\
\::/    \:::\  /:::/    /|:::|____\     /:::/    /\::/   |::::\  /:::|____|\:::\   \:::\   \::/    /
 \/____/ \:::\/:::/    /  \:::\    \   /:::/    /  \/____|:::::\/:::/    /  \:::\   \:::\   \/____/
          \::::::/    /    \:::\    \ /:::/    /         |:::::::::/    /    \:::\   \:::\    \
           \::::/    /      \:::\    /:::/    /          |::|\::::/    /      \:::\   \:::\____\
           /:::/    /        \:::\__/:::/    /           |::| \::/____/        \:::\   \::/    /
          /:::/    /          \::::::::/    /            |::|  ~|               \:::\   \/____/
         /:::/    /            \::::::/    /             |::|   |                \:::\    \
        /:::/    /              \::::/    /              \::|   |                 \:::\____\
        \::/    /                \::/____/                \:|   |                  \::/    /
         \/____/                  ~~                       \|___|                   \/____/

   Programa de ejemplo para la AureBoard
  

   - El programa configura el puerto Serie por USB.
      
   - Cada programa deberá ir en su carpeta al mismo nivel de la carpeta lib




   A.U.R.E. 2011
*/

#include <../lib/aurebot.h>
//#include <../lib/bumper.h>
#include <../lib/motores.h>
#include <../lib/flex_lcd.C>
//#include <../lib/ldr.h>

#define iniciox 0b1
#define inicioy 0b1
#define DER PIN_A3
#define IZQ PIN_A1

//Rutina principal
void main()
{
  aure_configurar();
  usb_cdc_init();
  usb_init();
  lcd_init();
  delay_ms(200);
  
  lcd_gotoxy(iniciox,inicioy);
  printf(lcd_putc,"Sistema ok ");
  lcd_gotoxy(iniciox,inicioy);
  delay_ms(500);
  printf(lcd_putc,"                   ");
  
  while(1)
  {
  
     if(usb_cdc_connected()){}
     else
     {
           delay_ms(500);
           lcd_gotoxy(iniciox,inicioy);
           printf(lcd_putc,"                   ");
           motores_parar();
           
           while(!input(PULSADOR)){
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"pulsar D ");
               lcd_gotoxy(iniciox,inicioy);
           }
                               
           lcd_gotoxy(iniciox,inicioy);
           printf(lcd_putc,"                   ");
           delay_ms(500);
                   
           while(1)
           {
           //////////////////////////////////////////////////////////////////////
           //El codigo que se programe va aquí dentro////////////////////////////
           //////////////////////////////////////////////////////////////////////
           //Nuestros motores están cambiados////
           if(input(DER)==0&&input(IZQ)==0){
           motores_palante();
           }
           if(input(DER)==0&&input(IZQ)==1){
           motores_parar();
           }
           if(input(DER)==1&&input(IZQ)==0){
           motores_parar();
           }
           if(input(DER)==1&&input(IZQ)==1){
           motores_patras();
           }
           if(input(PULSADOR)){break;}  
           }
     }                    
              
  }
 }
   
 





