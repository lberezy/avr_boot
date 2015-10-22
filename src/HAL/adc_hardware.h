#ifndef ADC_H
#define ADC_H

#define BAT_ADC_PIN PA1
#define BAT_CONF_INPUT() do{DDRA &= ~_BV(BAT_ADC_PIN);} while(0)
#define ADC_INIT() do {ADMUX |=  _BV(REFS1) | _BV(REFS0) | _BV(ADLAR) | _BV(MUX0); ADCSRA |= _BV(ADEN);} while(0)
#define ADC_DO_SAMPLE() do{ADCSRA |= _BV(ADSC); while(ADCSRA & _BV(ADSC));} while(0)
#define BATTERY_LEVEL ADCH

#define BATTERY_LOW_LEVEL 110 //( ~255 * 1.1 V / 2.56 V)

#endif
