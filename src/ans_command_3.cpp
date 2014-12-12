#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

void ans_command_3(uint8_t* group)
{
	//uint8_t temp = 0;
	uint8_t i;	

	// переписываем данные из принятого пакета в структуру переменных
	for(i=0; i<modbus_m.buffer[2]; i=i+2)
	{
		// в разsменнованый указатель на 1 байт струтуры записываем байт из принятого сообщения
		*(group + i) = modbus_m.buffer[3 + i + 1];
		*(group + 1 + i) = modbus_m.buffer[3 + i]; // то же самое делаем со вторым байтом
		//temp = temp + 2; // номера байт увеличиваем на 2  и все то же самое для всех регистров в сообщение
	}
	// сбрасываем флаг о приходе пакета
	modbus_m.rxgap = 0;
	// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
	// обработки ответа ans_command_3() от SLAVE по команде 3
	modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
	modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
	
	//!!!
	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
	modbus_m.rxgap = 0;
}

