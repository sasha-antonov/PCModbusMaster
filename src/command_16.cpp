#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

// запись группы регистров - принимает	адрес устройства, адрес	modbus начала группы переменных для чтения, 
// указатель на эту группу и размер структуры группы (sizeof())
void command_16(uint8_t adr_device, uint16_t adr_group, uint8_t* group, uint16_t size)
{
	uint8_t* adr_reg;
	uint8_t i;
	uint16_t N_reg;
	uint16_t N_reg_h;
	uint16_t N_reg_l;
	uint16_t reg;
	uint16_t reg_h;
	uint16_t reg_l;
	uint16_t crc;
	uint16_t crc_h;
	uint16_t crc_l;

	// адрес девайса для сообщения
	modbus_m.buffer[0] = adr_device;
	modbus_m.buffer[1] = 16; // сама команда

	// адрес начала группы регистров принимается из функции
	reg = adr_group;
	reg_h = reg/256;
	reg_l = reg & 0x00ff;

	modbus_m.buffer[2] = (uint8_t)reg_h;
	modbus_m.buffer[3] = (uint8_t)reg_l;

	// количество регистров принимается из функции /2	т.к. регистр = 2 байта
	N_reg = size/2;	
	N_reg_h = N_reg/256;
	N_reg_l = N_reg & 0x00ff;

	modbus_m.buffer[4] = (uint8_t)N_reg_h;
	modbus_m.buffer[5] = (uint8_t)N_reg_l;
	modbus_m.buffer[6] = (uint8_t)N_reg * 2;
	
	// записываем в сообщение что нужно записать в SLAVE из структуры
	adr_reg = group; // физический адрес регистра - указатель на 1 байт	структуры, берется из функции
	// для всех байт регистров переписываем значения из структуры
	for(i=0; i<modbus_m.buffer[6]; i = i + 2)
	{
		modbus_m.buffer[7 + i + 1] = *adr_reg; // переписываем побайтно
		modbus_m.buffer[7 + i ] = *(adr_reg + 1);
		adr_reg = adr_reg + 2; // номера байт в адресе увеличиваем на два и все заново
	}

	// расчет CRC16 для передаваемых данных
	crc = crc16(modbus_m.buffer, modbus_m.buffer[6] + 7);	// высчитываем CRC16
	crc_h = crc >> 8;
	crc_l = crc & 0x00ff;

	modbus_m.buffer[modbus_m.buffer[6] + 7] = (uint8_t)crc_h;
	modbus_m.buffer[modbus_m.buffer[6] + 8] = (uint8_t)crc_l;

	// количество байт для передачи
	modbus_m.tr_len = modbus_m.buffer[6] + 9;
}