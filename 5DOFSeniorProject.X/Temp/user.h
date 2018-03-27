/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/

/* TODO Application specific user parameters used in user.c may go here */
#define MICROSTICK_LED0_PIN _LATA0

static inline void LED0_ON()       {MICROSTICK_LED0_PIN=1;}
static inline void LED0_OFF()      {MICROSTICK_LED0_PIN=0;}
static inline void LED0_TOGGLE()   {MICROSTICK_LED0_PIN=~MICROSTICK_LED0_PIN;}

extern unsigned long timer1Counter;
extern unsigned char timer1Flag;

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
