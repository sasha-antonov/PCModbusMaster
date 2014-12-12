#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

// ������ ������ �������� -  ���������	����� ����������, �����	modbus ���������� ��� ������, 
// ��������� �� ���
void command_6(uint8_t adr_device, uint16_t adr_reg, uint8_t* group)
{
	uint16_t reg;
	uint16_t reg_h;
	uint16_t reg_l;
	uint16_t crc;
	uint16_t crc_h;
	uint16_t crc_l;
	uint8_t* adr;

	// ����� ������� ��� ���������
	modbus_m.buffer[0] = adr_device;
	modbus_m.buffer[1] = 6;	// ���� �������

	// ����� ������ ������ ��������� ����������� �� �������
	reg = adr_reg;
	reg_h = reg/256;
	reg_l = reg & 0x00ff;

	modbus_m.buffer[2] = reg_h;
	modbus_m.buffer[3] = reg_l;

	// ���������� ����� �������� - ��������� �� ���� ����������, ������� �� �������
	adr = group;
	
	// ���������� �� ���������� �������� � ����� ��������� ��� ��������	- 2 ����� ������ ��������
	modbus_m.buffer[4] = *(adr + 1);
	modbus_m.buffer[5] = *(adr); 

	// ������ CRC16 ��� ������������ ������
	crc = crc16(modbus_m.buffer, 6);	// ����������� CRC16
	crc_h = crc >> 8;
	crc_l = crc & 0x00ff;

	modbus_m.buffer[6] = crc_h;
	modbus_m.buffer[7] = crc_l;

	// ���������� ���� ��� ��������
	modbus_m.tr_len = modbus_m.buffer[6] + 9;
}