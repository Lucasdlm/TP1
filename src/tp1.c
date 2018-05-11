/*==================[inclusions]=============================================*/

//#include "blinky.h"   // <= own header (optional)
#include "sapi.h"       // <= sAPI header
#include "tp1.h"

#ifdef TP1_4

#define TICKRATE_MS 1
#define LED_TOGGLE_MS 500

#endif

#ifdef TP1_5

#define TICKRATE_MS 1
#define LED_TOGGLE_MS 500

#endif

#ifdef TP1_6

#define TICKRATE_MS 1
#define LED_TOGGLE_MS 500

#endif

/* FUNCION que se ejecuta cada vez que ocurre un Tick. */
void myTickHook( void *ptr ){

   static bool_t ledState = OFF;

   gpioMap_t led = (gpioMap_t)ptr;

   if( ledState ){
      ledState = OFF;
   }
   else{
      ledState = ON;
   }
   gpioWrite( led, ledState );
}


/* FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE RESET. */
int main(void){

	/* Inicializar la placa */
   boardConfig();

#ifdef TP1_1
   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

      /* Prendo el led azul */
      gpioWrite( LEDB, ON );

      delay(1000);

      /* Apago el led azul */
      gpioWrite( LEDB, OFF );

      delay(500);

   }

#endif // TP1_1

#ifdef TP1_2

   gpioConfig( GPIO0, GPIO_INPUT );

   gpioConfig( GPIO1, GPIO_OUTPUT );

   /* Variable para almacenar el valor de tecla leido */
   bool_t valor;

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {

         valor = !gpioRead( TEC1 );
         gpioWrite( LEDB, valor );

         valor = !gpioRead( TEC2 );
         gpioWrite( LED1, valor );

         valor = !gpioRead( TEC3 );
         gpioWrite( LED2, valor );

         valor = !gpioRead( TEC4 );
         gpioWrite( LED3, valor );

         valor = !gpioRead( GPIO0 );
         gpioWrite( GPIO1, valor );

      }
#endif // TP1_2

#ifdef TP1_3

   tickConfig( 50 );

   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(1000);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(1000);
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(1000);
   }
#endif // TP1_3

#ifdef TP1_4

   tickConfig(TICKRATE_MS);

   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(LED_TOGGLE_MS);

   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(LED_TOGGLE_MS);
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(LED_TOGGLE_MS);
   }
#endif // TP1_4

#ifdef TP1_5

   tickConfig(TICKRATE_MS);

   tickCallbackSet( myTickHook, (void*)LEDR );
   delay(LED_TOGGLE_MS);

   DEBUG_PRINT_ENABLE;
   /* UART for debug messages. */
   debugPrintConfigUart( UART_USB, 115200 );
   debugPrintString("DEBUG c/sAPI\r\n" );
   debugPrintString( "LED Toggle\n" );


   /* ------------- REPETIR POR SIEMPRE ------------- */
   while(1) {
      tickCallbackSet( myTickHook, (void*)LEDG );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
      tickCallbackSet( myTickHook, (void*)LEDB );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
      tickCallbackSet( myTickHook, (void*)LED1 );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
      tickCallbackSet( myTickHook, (void*)LED2 );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
      tickCallbackSet( myTickHook, (void*)LED3 );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
      tickCallbackSet( myTickHook, (void*)LEDR );
      delay(LED_TOGGLE_MS);
      debugPrintString( "LED Toggle\n" );
   }
#endif // TP1_5

#ifdef TP1_6

      gpioConfig( GPIO0, GPIO_INPUT );
      gpioConfig( GPIO1, GPIO_OUTPUT );

      /* Variable para almacenar el valor de tecla leido */
      bool_t valor;

      tickConfig( TICKRATE_MS );

      /* The DEBUG* functions are sAPI debug print functions.
     Code that uses the DEBUG* functions will have their I/O routed to
     the sAPI DEBUG UART. */
      DEBUG_PRINT_ENABLE;
      /* UART for debug messages. */
      debugPrintConfigUart( UART_USB, 115200 );
      debugPrintString( "DEBUG c/sAPI\r\n" );

      int LED = LEDR;

      /* ------------- REPETIR POR SIEMPRE ------------- */
         while(1) {
        	 valor = !gpioRead( TEC1 );
        	 if(valor){
        		 for(LED = LEDR; LED <= LED3+1; LED++){
        			 tickCallbackSet( myTickHook, (void*)LED );
        			 debugPrintString( "LED Toggle because of TEC1\n" );
        			 delay(LED_TOGGLE_MS);
        		 }
        	 }
        	 valor = !gpioRead( TEC2 );
        	 if(valor){
        		 for(LED = LEDR; LED <= LED3; LED++){
        			 tickCallbackSet( myTickHook, (void*)LED );
        			 debugPrintString( "LED Toggle because of TEC2\n" );
        			 delay(LED_TOGGLE_MS);
        		 }
        	 }
        	 valor = !gpioRead( TEC3 );
        	 if(valor){
        		 for(LED = LEDR; LED == LED3+1; LED++){
        			 tickCallbackSet( myTickHook, (void*)LED );
        			 debugPrintString( "LED Toggle because of TEC3\n" );
        			 delay(LED_TOGGLE_MS);
        		 }
        	 }
        	 valor = !gpioRead( TEC4 );
        	 if(valor){
        		 for(LED = LEDR; LED == LED3; LED++){
        			 tickCallbackSet( myTickHook, (void*)LED );
        			 debugPrintString( "LED Toggle because of TEC4\n" );
        			 delay(LED_TOGGLE_MS);
        		 }
        	 }
        	 valor = !gpioRead( GPIO0 );
        	 if(valor){
        		 for(LED = LEDR; LED <= LED3+1; LED++){
        			 tickCallbackSet( myTickHook, (void*)LED );
        			 debugPrintString( "LED Toggle because of GPIO0\n" );
        			 delay(LED_TOGGLE_MS);
        		 }
        	 }
         }


#endif // TP1_6

   /* NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa no es llamado
      por ningun S.O. */
   return 0 ;
}

/*==================[end of file]============================================*/
