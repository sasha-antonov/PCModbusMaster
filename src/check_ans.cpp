#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

uint8_t check_ans(void)
{
	extern struct modbus_temporary modbus_m;
	uint16_t crc;
	uint16_t crc_l;
	uint16_t crc_h;

	// в ответе код команды - ошибка
	if(modbus_m.buffer[1] == 131)
	{
		// сбрасываем флаг о приходе пакета
		modbus_m.rxgap = 0;
		// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
		// обработки ответа ans_command_3() от SLAVE по команде 3
		modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
		modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
		modbus_m.rxgap = 0;
		return 1; // возращаем сигнал об ошибке	
	}
	
	// в ответе код команды - ошибка
	if(modbus_m.buffer[1] == 144)
	{
		// сбрасываем флаг о приходе пакета
		modbus_m.rxgap = 0;
		// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
		// обработки ответа ans_command_3() от SLAVE по команде 3
		modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
		modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
		modbus_m.rxgap = 0;
		return 1; // возращаем сигнал об ошибке		
	}

	// в ответе код команды - ошибка
	if(modbus_m.buffer[1] == 32778)
	{
		// сбрасываем флаг о приходе пакета
		modbus_m.rxgap = 0;
		// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
		// обработки ответа ans_command_3() от SLAVE по команде 3
		modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
		modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
		modbus_m.rxgap = 0;
		return 1; // возращаем сигнал об ошибке		
	}
	
	// если ответ от команды 3
	if(modbus_m.buffer[1] == 3)
	{
		// определение правильности CRC
		crc = crc16(modbus_m.buffer, modbus_m.buffer[2] + 3);	// высчитываем CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[modbus_m.buffer[2] + 3]) | (crc_l != modbus_m.buffer[modbus_m.buffer[2] + 4])) // сравнение контрольной суммы, только -1 потому что до этого у нас уже выполнялся -1
		{
			// сбрасываем флаг о приходе пакета
			modbus_m.rxgap = 0;
			// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
			// обработки ответа ans_command_3() от SLAVE по команде 3
			modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
			modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
			modbus_m.rxgap = 0;
			return 1; // возращаем сигнал об ошибке	если CRC не верен	
		}
		// данный else нужен т.к. далее будет еще перезапись переменных при обработке ответа от command_3 (ans_command_3)
		// и только там будет разрешено прерывание по приему от USART, а в command_6 и command_16 это разрешение
		// присутствует в этой функции и обработки сообщения ответа как таковой нет
		else
		{
			return 0; // возращаем 0 все верно
		}
	}
	
	if(modbus_m.buffer[1] == 16)
	{
		// определение правильности CRC
		crc = crc16(modbus_m.buffer, 6);	// высчитываем CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[6]) | (crc_l != modbus_m.buffer[7])) // сравнение контрольной суммы, только -1 потому что до этого у нас уже выполнялся -1
		{
			// сбрасываем флаг о приходе пакета
			modbus_m.rxgap = 0;
			// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
			// обработки ответа ans_command_3() от SLAVE по команде 3
			modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
			modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
			modbus_m.rxgap = 0;
			return 1; // возращаем сигнал об ошибке		
		}
	}
	
	if(modbus_m.buffer[1] == 6)
	{
		// определение правильности CRC
		crc = crc16(modbus_m.buffer, 6);	// высчитываем CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[6]) | (crc_l != modbus_m.buffer[7])) // сравнение контрольной суммы, только -1 потому что до этого у нас уже выполнялся -1
		{
			// сбрасываем флаг о приходе пакета
			modbus_m.rxgap = 0;
			// данная настройка происходит после контроля ответа check_ans() после команд 16 и 6, а так же после
			// обработки ответа ans_command_3() от SLAVE по команде 3
			modbus_m.rxtimer = 0; // сбрасываем время, отвечающее за определение конца пакета от SLAVE
			modbus_m.rxcnt = 0;	// сбрасываем счетчик, принятых байт от SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// разрешение прерывания по приему USART
			modbus_m.rxgap = 0;
			return 1; // возращаем сигнал об ошибке		
		}
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
	return 0;
}