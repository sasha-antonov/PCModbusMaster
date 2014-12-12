#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

// запись одного регистра -  принимает	адрес устройства, адрес	modbus переменной для чтения, 
// указатель на нее
void command_6(uint8_t adr_device, uint16_t adr_reg, uint8_t* group)
{
	uint16_t reg;
	uint16_t reg_h;
	uint16_t reg_l;
	uint16_t crc;
	uint16_t crc_h;
	uint16_t crc_l;
	uint8_t* adr;

	// адрес девайса для сообщения
	modbus_m.buffer[0] = adr_device;
	modbus_m.buffer[1] = 6;	// сама команда

	// адрес начала группы регистров принимается из функции
	reg = adr_reg;
	reg_h = reg/256;
	reg_l = reg & 0x00ff;

	modbus_m.buffer[2] = reg_h;
	modbus_m.buffer[3] = reg_l;

	// физический адрес регистра - указатель на байт переменной, берется из функции
	adr = group;
	
	// записываем из переменной значения в буфер сообщения для передачи	- 2 байта одного регистра
	modbus_m.buffer[4] = *(adr + 1);
	modbus_m.buffer[5] = *(adr); 

	// расчет CRC16 для передаваемых данных
	crc = crc16(modbus_m.buffer, 6);	// высчитываем CRC16
	crc_h = crc >> 8;
	crc_l = crc & 0x00ff;

	modbus_m.buffer[6] = crc_h;
	modbus_m.buffer[7] = crc_l;

	// количество байт для передачи
	modbus_m.tr_len = modbus_m.buffer[6] + 9;
}