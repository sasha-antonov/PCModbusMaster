#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

// ������ ������ ��������� - ���������	����� ����������, �����	modbus ������ ������ ���������� ��� ������, 
// ��������� �� ��� ������ � ������ ��������� ������ (sizeof())
void command_3(uint8_t adr_device, uint16_t adr_group, uint8_t* group, uint16_t size)
{

	uint16_t N_reg;
	uint16_t N_reg_h;
	uint16_t N_reg_l;
	uint16_t reg;
	uint16_t reg_h;
	uint16_t reg_l;
	uint16_t crc;
	uint16_t crc_h;
	uint16_t crc_l;

	modbus_m.buffer[0] = adr_device; //����� ������� ��� �������� �������
	modbus_m.buffer[1] = 3;	// ���� �������

	reg = adr_group; // ����� ������ �������� - �� ���� ��� �������� � �������
	reg_h = reg/256; 
	reg_l = reg & 0x00ff;

	modbus_m.buffer[2] = (uint8_t)reg_h;
	modbus_m.buffer[3] = (uint8_t)reg_l;

	N_reg = size/2;	// ���������� ��������� - �� ���� ��� �������� � ������� /2	�.�. ������� = 2 �����
	N_reg_h = N_reg/256;
	N_reg_l = N_reg & 0x00ff;

	modbus_m.buffer[4] = (uint8_t)N_reg_h;
	modbus_m.buffer[5] = (uint8_t)N_reg_l;

	// ������ CRC16 ��� ������������ ������
	crc = crc16(modbus_m.buffer, 6);	// ����������� CRC16
	crc_h = crc >> 8;
	crc_l = crc & 0x00ff;

	modbus_m.buffer[6] = (uint8_t)crc_h;
	modbus_m.buffer[7] = (uint8_t)crc_l;

	// ���������� ���� ��� ��������
	modbus_m.tr_len = 7;
}