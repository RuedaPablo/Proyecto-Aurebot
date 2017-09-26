/*AUREBOT 2014 - MANOLO*/
/*DISPOSITIVOS ELECTRONICOS Y FOTONICOS*/
/*INGENIERIA TELECOMUNICACIONES*/

// Incluimos las librerías, definiciones, configuraciones y funciones del aurebot.
#include <../lib/aurebot.h> 
#include <../lib/flex_lcd.C> 
 
//Incluimos otras librerías que vayamos a usar 
#include <../lib/cny70.h> //Para configurar y leer los sensores CNY70 
#include <../lib/servos.h> //Para configurar y mover los servos 
#include <../lib/barra_leds.h> //Para configurar y usar la barra de led 
#include <../lib/motores.h> 
#include <../lib/bumper.h> 
 
//Definimos los pines del AUREBOT
#define iniciox 0b1 
#define inicioy 0b1 
#define IR PIN_E2      //Receptor Infrarrojo
#define LDRD PIN_A1    //LDR derecho
#define LDRI PIN_E1    //LDR izquierdo
#define BD PIN_A3      //Bumper frontal derecho
#define BI PIN_A5      //Bumper frontal izquierdo
#define BLD PIN_E0     //Bumper lateral derecho
#define BLI PIN_A2     //Bumper lateral izquierdo
#define VENT PIN_A0    //Ventilador



/*MODO 1 (Manolo explorador): Dirección mediante bumpers. El aurebot avanza hacia adelante hasta
que choqua con los bumpers. Si choca con solo uno de estos, realiza un pequeño giro para cambiar la 
trayectoria y continua avanzando. Si choca con los dos a la vez, realiza un movimiento más 
amplio destinado a esquivar un objeto de gran tamaño. Los bumpers laterales tienen por funcion
permitir al robot estar siempre en contacto con el suelo; cuando este no detecta suelo da media
vuelta antes de reemprender la marcha. Cuando los bumpers frontales chocan contra algún obstáculo,
se encenderá el led que corresponde al bumper que choca.*/

void dirigir_bumpers(){ 
 
   int n2=0; 
 
   while (n2==0) { 
      lcd_gotoxy(iniciox,inicioy); 
      printf(lcd_putc," "); 
      lcd_gotoxy(iniciox,inicioy); 
      printf(lcd_putc,"Manolo explorador"); 
       delay_ms(200); 
 
         //if(input(BD)==0 && input(BI)==0){ 
         if(!(input(BD) || input(BI))){ 
            lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy);
            printf(lcd_putc,"Bumpers delanteros"); 
 
                motores_parar(); 
                motores_patras(); 
                   delay_ms(2000);
 
                motores_parar(); 
                motores_paizda();
                   delay_ms(3000);
                motores_parar();
                motores_palante();
          } 

         else if(input(BI)==0){ 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc,"Bumper derecho  "); 
             lcd_gotoxy(1,2); 
             printf(lcd_putc," ");
 
                motores_parar();
                motores_patras();
                   delay_ms(1250);
 
                motores_parar();
                motores_paderecha();
                   delay_ms(1500);
                motores_parar();
                motores_palante(); 
          }

         else if(input(BD)==0){ 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," "); 
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc,"Bumper izquierdo  "); 
 
                motores_parar();
                motores_patras();
                   delay_ms(1250);
 
                motores_parar(); 
                motores_paizda(); 
                   delay_ms(1500); 
                motores_parar(); 
                motores_palante(); 
          }
          
         else if(input(BLI)==0){
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc,"Bumper lat izdo   "); 
             lcd_gotoxy(1,2); 
             printf(lcd_putc," ");
 
                motores_parar();
                motores_patras();
                   delay_ms(4000);
 
                motores_parar();
                motores_paizda();
                   delay_ms(3000);
                motores_parar();
                motores_palante(); 
          }

         else if(input(BLD)==0){
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," "); 
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc,"Bumper lat dcho  "); 
 
                motores_parar();
                motores_patras();
                   delay_ms(4000);
 
                motores_parar(); 
                motores_paderecha(); 
                   delay_ms(3000); 
                motores_parar(); 
                motores_palante(); 
          }
          
       
          if (input(IR)==0){
                motores_parar ();
                
             lcd_gotoxy(iniciox,inicioy);
             printf(lcd_putc," ");
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," MODO 1 "); 
             lcd_gotoxy(1,2); 
             printf(lcd_putc," FINALIZADO   "); 
                delay_ms(3000); 
 
             n2=1;
          }
          
          
          else{
                motores_palante(); 
               continue;
          }
 
    } 
}


 
/*MODO 2 (Manolo seguidor de luz): El Aurebot sigue la luz. El aurebot se mantiene andando
en linea recta mientras oscuridad, cuando detecta la luz solo en alguna de sus LDR gira
hacia el lado en que detecta la luz. Si hay luz total, se mantiene parado*/

void seguir_luz(){

   int n2=0; 
   lcd_gotoxy(iniciox,inicioy);
   
    while(n2==0){ 
 
       if(input(LDRD)==0 && input(LDRI)==0){
             lcd_gotoxy(iniciox,inicioy);
             printf(lcd_putc," ");
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc,"  LUZ TOTAL  "); 
         motores_parar();
       }
       
       if(input(LDRD)==0){
        lcd_gotoxy(iniciox,inicioy);
             printf(lcd_putc," ");
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," LUZ DERECHA ");
          motores_paizda();
       } 
 
       if(input(LDRI)==0){
        lcd_gotoxy(iniciox,inicioy);
             printf(lcd_putc," ");
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," LUZ IZQUIERDA ");
          motores_paderecha();
       } 
 
       if(input(LDRD)==1 && input(LDRI)==1){
        lcd_gotoxy(iniciox,inicioy);
             printf(lcd_putc," ");
             lcd_gotoxy(1,2); 
             printf(lcd_putc," "); 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," OSCURIDAD TOTAL"); 
          motores_palante();
       }
 
       if(input(IR)==0){
         motores_parar();
         n2=1;
      }
      
      else{ 
          continue; 
       } 
 
    } 
}



/*MODO 3 (Manolo bombero): Cuando el Aurebot ha sido guiado previamente por luz hasta donde se encuentra una vela, este modo
se encargará de apagarla mediante la activación del ventilador previamente instalado.*/

void bombero_luz(){

   int n2=0; 
   lcd_gotoxy(iniciox,inicioy);
   
    while(n2==0){
               motores_parar();
               output_high(VENT);
               delay_ms(5000);
               lcd_gotoxy(iniciox,inicioy); 
               printf(lcd_putc,"  Encendido  ");
               lcd_gotoxy(1,2);
               printf(lcd_putc," ");
               
               if(input(IR)==0){
                  motores_parar();
                  output_low(VENT);
                  lcd_gotoxy(iniciox,inicioy);
                  printf(lcd_putc,"  Apagado  ");
                  n2=1;
               }
    } 
}


//Función principal del programa
void main(){ 

   int n2=0,n3=0,n4=0,n5=0,n6=0;
    
    aure_configurar(); 
    usb_cdc_init(); 
    usb_init(); 
    lcd_init();
    delay_ms(200);
 
    lcd_gotoxy(iniciox,inicioy); 
    printf(lcd_putc," Manolo OK "); 
    lcd_gotoxy(iniciox,inicioy); 
    delay_ms(500); 
    printf(lcd_putc," "); 
    
   //Hasta aqui, la configuracion del Aurebot 
 
    while(1){ 
       usb_task();  
       if(usb_cdc_connected()){} //Si el usb conectado, no se hace nada 
       
       else{ 
             delay_ms(500); 
          lcd_gotoxy(iniciox,inicioy); 
          printf(lcd_putc," "); 
 
 
         while(!input(PULSADOR)){ //Sistema parado hasta pulsar D 
             lcd_gotoxy(iniciox,inicioy); 
             printf(lcd_putc," Pulsar D "); 
             lcd_gotoxy(iniciox,inicioy); 
          } 
 
 
         while(n2==0){ 
            lcd_gotoxy(iniciox,inicioy); 
            printf(lcd_putc," ");
            
             if(input(IR)==0){ 
               lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc,"Recibe datos"); 
                   delay_ms(2000); 
                n2=1;
             } 
             
             else if(input(IR)==1){
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc,"No recibe"); 
            }  
          }
          } 
 
         while(n3==0){ 
                lcd_gotoxy(iniciox,inicioy);
                printf(lcd_putc," Pulsar mando     ");
                
             if(input(IR)==0){
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," Modo 1       "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," Bumpers     ");
                delay_ms(3000);
                dirigir_bumpers(); 
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," "); 
                n3=1; 
             }
          } 
           
          
          while(n4==0){
                lcd_gotoxy(iniciox,inicioy);
                printf(lcd_putc," Pulsar mando     ");
                
             if(input(IR)==0){
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," Modo 2       "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," Seguidor Luz     ");
                delay_ms(3000);
                seguir_luz(); 
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," "); 
                n4=1; 
             }
          } 


         
         while(n5==0){
                lcd_gotoxy(iniciox,inicioy);
                printf(lcd_putc," Pulsar mando      ");
                
             if(input(IR)==0){ 
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," Modo 3     "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," Bombero     ");
                delay_ms(3000);
                bombero_luz();
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," "); 
                lcd_gotoxy(1,2); 
                printf(lcd_putc," "); 
                n5=1;
             }
            
            if(n5==0){
               continue;
            }
         }
         
          while(n6==0){         
             if(input(IR)==0){ 
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," ");
                lcd_gotoxy(1,2); 
                printf(lcd_putc," FIN  !!MANOLO!! "); 
                lcd_gotoxy(iniciox,inicioy); 
                printf(lcd_putc," ");
                lcd_gotoxy(1,2);
                printf(lcd_putc," "); 
                n6=1; 
             }
          }
          
       } 
   }
