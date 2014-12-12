#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

// ������ ������ ��������� - ���������	����� ����������, �����	modbus ������ ������ ���������� ��� ������, 
// ��������� �� ��� ������ � ������ ��������� ������ (sizeof())
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

	// ����� ������� ��� ���������
	modbus_m.buffer[0] = adr_device;
	modbus_m.buffer[1] = 16; // ���� �������

	// ����� ������ ������ ��������� ����������� �� �������
	reg = adr_group;
	reg_h = reg/256;
	reg_l = reg & 0x00ff;

	modbus_m.buffer[2] = (uint8_t)reg_h;
	modbus_m.buffer[3] = (uint8_t)reg_l;

	// ���������� ��������� ����������� �� ������� /2	�.�. ������� = 2 �����
	N_reg = size/2;	
	N_reg_h = N_reg/256;
	N_reg_l = N_reg & 0x00ff;

	modbus_m.buffer[4] = (uint8_t)N_reg_h;
	modbus_m.buffer[5] = (uint8_t)N_reg_l;
	modbus_m.buffer[6] = (uint8_t)N_reg * 2;
	
	// ���������� � ��������� ��� ����� �������� � SLAVE �� ���������
	adr_reg = group; // ���������� ����� �������� - ��������� �� 1 ����	���������, ������� �� �������
	// ��� ���� ���� ��������� ������������ �������� �� ���������
	for(i=0; i<modbus_m.buffer[6]; i = i + 2)
	{
		modbus_m.buffer[7 + i + 1] = *adr_reg; // ������������ ��������
		modbus_m.buffer[7 + i ] = *(adr_reg + 1);
		adr_reg = adr_reg + 2; // ������ ���� � ������ ����������� �� ��� � ��� ������
	}

	// ������ CRC16 ��� ������������ ������
	crc = crc16(modbus_m.buffer, modbus_m.buffer[6] + 7);	// ����������� CRC16
	crc_h = crc >> 8;
	crc_l = crc & 0x00ff;

	modbus_m.buffer[modbus_m.buffer[6] + 7] = (uint8_t)crc_h;
	modbus_m.buffer[modbus_m.buffer[6] + 8] = (uint8_t)crc_l;

	// ���������� ���� ��� ��������
	modbus_m.tr_len = modbus_m.buffer[6] + 9;
}