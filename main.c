#include <tm4c123gh6pm.h>
#include <stdio.h>
#include <string.h>

void delay()
{
    int i;
    for (i = 0; i < 200000; i++);
}
void uart_tx(char data)
{
    while ((UART0_FR_R & 0x20) == 1)
        ;
    UART0_DR_R = data;
}
int sysctl_init(void)
{
    SYSCTL_RCGCGPIO_R = (1 << 0) | (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4); // A, B, C, D, E
    SYSCTL_RCGCI2C_R = (1 << 0);
    SYSCTL_RCGCUART_R = (1 << 0);

    SYSCTL_RCGCPWM_R |= (1 << 0);
    SYSCTL_RCC_R &= (~(1 << 20));

    SYSCTL_RCGCEEPROM_R |= (1 << 0);
    return 0;
}
int uart_init(void)
{
    GPIO_PORTA_AFSEL_R |= (1 << 0) | (1 << 1);
    GPIO_PORTA_PCTL_R |= (1 << 0) | (1 << 4);
    GPIO_PORTA_DEN_R |= (1 << 0) | (1 << 1);
    UART0_CTL_R |= (1 << 8) | (1 << 9);
    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;
    UART0_LCRH_R |= (1 << 5) | (1 << 6);
    UART0_CTL_R |= (1 << 8) | (1 << 9) | (1 << 0);
    return 0;
}
int kp_init(void)
{
    GPIO_PORTC_DIR_R |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    GPIO_PORTE_PDR_R |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
    GPIO_PORTC_DEN_R |= (1 << 4) | (1 << 5) | (1 << 6) | (1 << 7);
    GPIO_PORTE_DEN_R |= (1 << 1) | (1 << 2) | (1 << 3) | (1 << 4);
    return 0;
}
int modes_init(void)
{
    GPIO_PORTA_DIR_R |= (1 << 2) | (1 << 3) | (1 << 4);
    GPIO_PORTA_DEN_R |= (1 << 2) | (1 << 3) | (1 << 4);
    return 0;
}

int pwm_init(void)
{

    GPIO_PORTD_AFSEL_R |= (1 << 0);
    GPIO_PORTD_PCTL_R |= (1 << 2);
    GPIO_PORTD_DEN_R |= (1 << 0);

    PWM0_3_CTL_R &= ~(1 << 0);
    PWM0_3_CTL_R &= ~(1 << 1);
    PWM0_3_GENA_R |= 0x0000008C;
    //PWM0_3_LOAD_R = 200;
    //PWM0_3_CMPA_R = 0;
    PWM0_3_CTL_R = 1;
    PWM0_ENABLE_R |= (1 << 6);

    return 0;

}

unsigned char kp_scan(void)
{
    unsigned char keys[4][4] =
            { { '1', '2', '3', 'A' }, { '4', '5', '6', 'B' }, { '7', '8', '9',
                                                                'C' },
              { '*', '0', '#', 'D' } };

    int i = 0;
    for (i = 0; i < 4; i++)
    {
        GPIO_PORTC_DATA_R = (1 << (i + 4));

        if (GPIO_PORTE_DATA_R & 0x02)
        {
            return keys[i][0];
        }
        else if (GPIO_PORTE_DATA_R & 0x04)
        {
            return keys[i][1];
        }
        else if (GPIO_PORTE_DATA_R & 0x08)
        {
            return keys[i][2];
        }
        else if (GPIO_PORTE_DATA_R & 0x10)
        {
            return keys[i][3];
        }
    }
    return 0;
}

int play_tone(unsigned char input)
{
    int i;
    if (input == '1')
    {
        PWM0_3_LOAD_R = (250 / 261.6) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '2')
    {
        PWM0_3_LOAD_R = (250 / 277.2) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '3')
    {
        PWM0_3_LOAD_R = (250 / 293.7) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '4')
    {
        PWM0_3_LOAD_R = (250 / 311.1) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '5')
    {
        PWM0_3_LOAD_R = (250 / 329.6) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '6')
    {
        PWM0_3_LOAD_R = (250 / 370.0) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '7')
    {
        PWM0_3_LOAD_R = (250 / 392.0) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '8')
    {
        PWM0_3_LOAD_R = (250 / 415.3) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '9')
    {
        PWM0_3_LOAD_R = (250 / 440.0) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }
    if (input == '0')
    {
        PWM0_3_LOAD_R = (250 / 493.9) * 10000;
        PWM0_3_CMPA_R = PWM0_3_LOAD_R / 2;
        for (i = 0; i < 200000; i++)
            ;
        PWM0_3_CMPA_R = 0;
    }

}

int play_note(unsigned char input, int *mode)
{
    int i = 0;

    if (input == 'A')
    {
        GPIO_PORTA_DATA_R |= (1 << 2);
        GPIO_PORTA_DATA_R &= ~(1 << 3);
        GPIO_PORTA_DATA_R &= ~(1 << 4);
        *mode = 1;
    }
    if (input == 'B')
    {
        GPIO_PORTA_DATA_R &= ~(1 << 2);
        GPIO_PORTA_DATA_R |= (1 << 3);
        GPIO_PORTA_DATA_R &= ~(1 << 4);
        *mode = 2;
    }
    if (input == 'C')
    {
        GPIO_PORTA_DATA_R &= ~(1 << 2);
        GPIO_PORTA_DATA_R &= ~(1 << 3);
        GPIO_PORTA_DATA_R |= (1 << 4);
        *mode = 3;
    }

    if (*mode == 1 || *mode == 2)
    {
        play_tone(input);
    }
    return 0;
}

int eeprom_init(void)
{

    GPIO_PORTB_AFSEL_R |= (1 << 2) | (1 << 3);
    GPIO_PORTB_DEN_R |= (1 << 2) | (1 << 3); // SCL, SDA
    GPIO_PORTB_DIR_R |= (1 << 2) | (1 << 3);

    GPIO_PORTB_ODR_R |= (1 << 3);

    GPIO_PORTB_PCTL_R |= (1 << 13) | (1 << 12) | (1 << 9) | (1 << 8);

    GPIO_PORTB_PUR_R |= (1 << 2) | (1 << 3);

    //GPIO_PORTB_PCTL_R |= GPIO_PCTL_PB2_I2C0SCL | GPIO_PCTL_PB3_I2C0SDA;

    I2C0_MCR_R |= (1 << 4);

    I2C0_MTPR_R |= (9 << 0);

    return 0;
}

int busy_eeprom(void)
{
    while(I2C0_MCS_R & 1);
    return I2C0_MCS_R & 0xE;
}

int write_eeprom(unsigned char data, unsigned char conditions)
{
    //I2C0_MSA_R = (0xA0);
    I2C0_MSA_R &= ~(1 << 0);

    I2C0_MDR_R = data;
    I2C0_MCS_R = conditions;

    delay();
    while ((I2C0_MCS_R & (1 << 0)) != 0);

    if (I2C0_MCS_R & (1 << 1) != 0)
    {
        GPIO_PORTA_DATA_R |= (1 << 2);
        GPIO_PORTA_DATA_R |= (1 << 3);
        GPIO_PORTA_DATA_R |= (1 << 4);
        return -1;
    }
    return 0;
}

int read_eeprom(unsigned char conditions)
{

    I2C0_MSA_R |= (1 << 0);

    //I2C0_MDR_R = data;
    I2C0_MCS_R = conditions;

    delay();
    while ((I2C0_MCS_R & (1 << 0)) != 0);

    if (I2C0_MCS_R & (1 << 1) != 0)
    {
        GPIO_PORTA_DATA_R |= (1 << 2);
        GPIO_PORTA_DATA_R |= (1 << 3);
        GPIO_PORTA_DATA_R |= (1 << 4);
        return -1;
    }
    char one = 0x01;
    char two = I2C0_MDR_R;
    uart_tx(two & (1 << 3));
    return 0;
}

int main(void)
{
    sysctl_init();
    uart_init();
    pwm_init();
    kp_init();
    modes_init();

    //eeprom_init();

    unsigned char input;
    int mode = 0;

    unsigned char notes[50];

    while (1)
    {
        input = kp_scan();
        uart_tx(input);
        play_note(input, &mode);
        if (mode == 2)
        {
            if (input != 'A' && input != 'B' && input != 'C' && input != 'D')
            {
                strncat(notes, &input, 1);
            }
        }
        if (mode == 3)
        {
            int z;
            for (z = 0; z < strlen(notes); z++)
            {
                uart_tx(notes[z]);
                play_tone(notes[z]);
                delay();
            }
        }
        delay();
    }
}
