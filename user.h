/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */
#define SPEAKER (PORTAbits.RA5)
extern unsigned long systick;

void InitApp(void);         /* I/O and Peripheral Initialization */
void init_uart();
void init_sonic_timer();
void start_sonic_timer();
unsigned int stop_sonic_timer();

void init_motor_timer();
void init_motor_enc_timer();

void beep(char tone);
void beep_message(char m);

void sys_delay_ms(unsigned long ticks);
