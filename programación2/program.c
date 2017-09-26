//........................PROGRAMA AUREBOT.....................................

// INGENIERIA DE TELECOMUNICACION
// DISPOSITIVOS ELECTRONICOS Y FOTONICOS

//INCLUIMOS LAS LIBRERIAS NECESARIAS

#include </lib/aurebot.h>
#include </lib/flex_lcd.C>       //para la pantalla
#include </lib/cny70.h>          //para configurar y leer los sensores CNY70
#include </lib/servos.h>         //para configurar y mover los servos 
#include </lib/barra_leds.h>     //para configurar y usar la barra de led
#include </lib/motores.h>        //para los motores
#include </lib/bumper.h>         //para los bumpers
#include </lib/ldr.h>            //para los LDR
#include <TONES.C>               //para generar sonidos

//DEFINIMOS LOS PINS DEL CHIP DEL AUREBOT QUE UTILIZAREMOS

#define iniciox 0b1
#define inicioy 0b1
#define IR PIN_A0
#define LDRI PIN_A1
#define LDRD PIN_A2
#define BD PIN_A3
#define BI PIN_A5
#define LUCES PIN_E0
#define INTERMITENTES PIN_E1
#define ALT PIN_E2

//DEFINIMOS LAS FRECUENCIAS Y DURACION DE LAS NOTAS MUSICALES

#define DO 522
#define DO_S 554
#define RE 588
#define RE_S 622
#define MI 660
#define FA 698
#define FA_S 740 
#define SOL 784
#define SOL_S 830
#define LA 880
#define LA_S 930
#define SI 988


#define semicorchea 125
#define corchea 250
#define negra 500
#define blanca 1000

//Funcion para configurar el ADC para la entrada de la fuente
void analogico_configurar()
{
   //Configuramos el ADC
   //Entrada A3 y A2 ANALOGICA y rango 0-Vdd
   setup_adc_ports(AN0_TO_AN1|VSS_VDD );     
   //Reloj interno
   setup_adc(ADC_CLOCK_INTERNAL );
}

void tunel(){
   
   float izqldr=0, derldr=0;
   
   printf(lcd_putc,"Buscador\rde luz");
   delay_ms(1000);
   
      //Cargamos los valores de los LDR      
      izqldr=leeradc(LDRI);
      derldr=leeradc(LDRD);
      
      //Pintamos sus valores en la pantalla LCD, analogicos.
     
      printf(lcd_putc,"D-%f",derldr);
      lcd_gotoxy(iniciox,2);
      printf(lcd_putc,"I-%f",izqldr);
      motores_patras();
   if(leeradc(LDRI)>128)
   {
         Output_high(LUCES);

   }
   else{
         delay_ms(5000);
         Output_low(LUCES);

   }

      
      //Si la diferencia entre ambos es mayor a un numero determinado
      /*if (abs(izqldr-derldr)>75)
      {
         //Y es el lado derecho el iluminado.. vamos a la derecha
         if (izqldr>derldr)
         {  
            motores_paderecha();
            delay_ms(500);
         } else {  //Sino, iremos a la izquierda
           motores_paizda();
           delay_ms(500);
            
         }
      } else { //Caso de que la diferencia de ambos no cumpla, avanza.
         motores_parar();
         motores_palante();
         
      }*/
   
}

   //FASE 2: APARCAMIENTO

void aparcar(){

   lcd_gotoxy(1,2);
   printf(lcd_putc,"Aparcamiento");
   while((input (LDRD)==0))
   motores_parar();
   motores_palante();                    
   delay_ms(500);
   motores_parar();
}
//FASE 3: BUMPERS
void bumpers(){

   if((input(BD)==0 &&(input(BI)==0))){
      motores_parar();
      motores_palante();
      generate_tone(SOL, blanca);  //Sonido marcha atras
        generate_tone(SOL, blanca);  //Sonido marcha atras
        generate_tone(SOL, blanca);  //Sonido marcha atras
      delay_ms(3000);
      motores_paizda();
      delay_ms(3000);
      motores_patras();
      delay_ms(3000);
      motores_paderecha();
      delay_ms(3000);
      motores_patras();
      delay_ms(3000);
   }else {
      motores_patras();
      delay_ms(3000);
   }

}


void main(){
   char Flag=0;                           // Flag que cambia cada NInts interrupciones
   int n;
   aure_configurar();
   usb_cdc_init();
   usb_init();
   lcd_init();
   delay_ms(200);
   //Configuracion de la interrupcion, indicandole que solo se active cuando
   //el bit cambia de bajo a alto.
   enable_interrupts(INT_EXT);
   ext_int_edge(0,L_TO_H);
    //Configuracion del timer0 con desbordamiento con prescaler 16.
    setup_counters(RTCC_INTERNAL,RTCC_DIV_16);// TIMER0: Clock Interno, Presescaler 16
    setup_timer_1(T1_DISABLED);                // para una RTCC cada 0.08 milisegundos
    setup_timer_2(T2_DISABLED,0,1);            // -> 5.24 Segundos = 60 RTCC
    setup_comparator(NC_NC_NC_NC);
    setup_vref(FALSE);
    enable_interrupts(INT_RTCC);               // Habilito Interrupcion RTCC
     
    analogico_configurar();
    lcd_gotoxy(iniciox,inicioy);
    printf(lcd_putc,"Sistema ok "); //Mensaje de inicializacion correcta
    delay_ms(500);
    
        
   set_timer0(0);
   Flag=0;
   
   while(input(IR)){
        lcd_gotoxy(iniciox,inicioy);
        printf(lcd_putc,"Esperando\r modo"); //Mensaje indicando que se pulse ?·
        lcd_gotoxy(iniciox,inicioy);
   }
   generate_tone(E_NOTE[3],500);
   
   delay_ms(500);
   
   //Mientras la opcion no sean 5 ticks, seguimos trabajando.
   while(n!=5)
   {
        // Si usamos el USB
        usb_task();
        //Fijamos el timer0 a 0 para que empiece a contar
        set_timer0(0);
        Flag=0; //El indicador de cuando desborda el timer las veces especificadas
        n=0;
        while(Flag==0) //Espera mientras no se pulse ?·
        {
            //Hasta que no pasen entre 5-6 segundos para escoger.
            if(!input(IR)){
               n++;
               delay_ms(500);
            }
            //Muestra en el LCD la opcion deseada hasta el momento.
            if(n==0){
              
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"Elegir modo: ");
               lcd_gotoxy(iniciox,2);
               printf(lcd_putc,"5 para salir. ");
            }else if(n==1){
               
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"Modo: "); 
               lcd_gotoxy(iniciox,2);
               printf(lcd_putc,"Tunel ");
            }else if(n==2){
               
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"Modo: "); 
               lcd_gotoxy(iniciox,2);
               printf(lcd_putc,"Aparcar");
            }else if(n==3){
               
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"Modo: "); 
               lcd_gotoxy(iniciox,2);
               printf(lcd_putc,"Bumpers ");
            }else if(n==4){
               
               lcd_gotoxy(iniciox,inicioy);
               printf(lcd_putc,"Modo: "); 
               lcd_gotoxy(iniciox,2);
               printf(lcd_putc,"Salir ");
                 
        }
        
        
        /* Muestra la eleccion deseada.*/
        lcd_gotoxy(iniciox,inicioy);
        printf(lcd_putc,"Has elegido: %u ",n); //Mensaje indicando que se pulse ?·
        lcd_gotoxy(iniciox,inicioy);
        delay_ms(2000);
        
        //Seg? la opcion deseada se activa el modo.
        if(n==0){
            //Si la eleccion es 0, pedimos un nuevo intento.
           
            lcd_gotoxy(iniciox,inicioy);
            printf(lcd_putc,"Vuelve a ");
            lcd_gotoxy(iniciox,2);
            printf(lcd_putc,"intentarlo. ");
            delay_ms(2000);
        }else if(n==1){
            tunel();
        }else if(n==2){
            aparcar();
        }else if(n==3){
            bumpers();
        }else if (n==4){
            
         lcd_gotoxy(iniciox,inicioy);
         printf(lcd_putc,"ERROR: "); 
         lcd_gotoxy(iniciox,2);
         printf(lcd_putc,"404 ");          
      }
   }
   
   lcd_gotoxy(iniciox,inicioy);
   printf(lcd_putc,"Programa "); //Mensaje indicando que se pulse ?·
   lcd_gotoxy(iniciox,2);
   printf(lcd_putc,"finalizado. ");
   return;
}
}
