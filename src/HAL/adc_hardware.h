#ifndef ADC_H
#define ADC_H

#define BAT_ADC_PIN PA1
#define BAT_CONF_INPUT() do{DDRA &= ~_BV(BAT_ADC_PIN);} while(0)
#define
#endif
