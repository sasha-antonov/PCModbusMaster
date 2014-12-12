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

	// � ������ ��� ������� - ������
	if(modbus_m.buffer[1] == 131)
	{
		// ���������� ���� � ������� ������
		modbus_m.rxgap = 0;
		// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
		// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
		modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
		modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
		modbus_m.rxgap = 0;
		return 1; // ��������� ������ �� ������	
	}
	
	// � ������ ��� ������� - ������
	if(modbus_m.buffer[1] == 144)
	{
		// ���������� ���� � ������� ������
		modbus_m.rxgap = 0;
		// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
		// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
		modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
		modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
		modbus_m.rxgap = 0;
		return 1; // ��������� ������ �� ������		
	}

	// � ������ ��� ������� - ������
	if(modbus_m.buffer[1] == 32778)
	{
		// ���������� ���� � ������� ������
		modbus_m.rxgap = 0;
		// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
		// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
		modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
		modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
		//!!!
		//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
		modbus_m.rxgap = 0;
		return 1; // ��������� ������ �� ������		
	}
	
	// ���� ����� �� ������� 3
	if(modbus_m.buffer[1] == 3)
	{
		// ����������� ������������ CRC
		crc = crc16(modbus_m.buffer, modbus_m.buffer[2] + 3);	// ����������� CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[modbus_m.buffer[2] + 3]) | (crc_l != modbus_m.buffer[modbus_m.buffer[2] + 4])) // ��������� ����������� �����, ������ -1 ������ ��� �� ����� � ��� ��� ���������� -1
		{
			// ���������� ���� � ������� ������
			modbus_m.rxgap = 0;
			// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
			// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
			modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
			modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
			modbus_m.rxgap = 0;
			return 1; // ��������� ������ �� ������	���� CRC �� �����	
		}
		// ������ else ����� �.�. ����� ����� ��� ���������� ���������� ��� ��������� ������ �� command_3 (ans_command_3)
		// � ������ ��� ����� ��������� ���������� �� ������ �� USART, � � command_6 � command_16 ��� ����������
		// ������������ � ���� ������� � ��������� ��������� ������ ��� ������� ���
		else
		{
			return 0; // ��������� 0 ��� �����
		}
	}
	
	if(modbus_m.buffer[1] == 16)
	{
		// ����������� ������������ CRC
		crc = crc16(modbus_m.buffer, 6);	// ����������� CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[6]) | (crc_l != modbus_m.buffer[7])) // ��������� ����������� �����, ������ -1 ������ ��� �� ����� � ��� ��� ���������� -1
		{
			// ���������� ���� � ������� ������
			modbus_m.rxgap = 0;
			// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
			// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
			modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
			modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
			modbus_m.rxgap = 0;
			return 1; // ��������� ������ �� ������		
		}
	}
	
	if(modbus_m.buffer[1] == 6)
	{
		// ����������� ������������ CRC
		crc = crc16(modbus_m.buffer, 6);	// ����������� CRC16
		crc_h = crc >> 8;
		crc_l = crc & 0x00ff;
		if( (crc_h != modbus_m.buffer[6]) | (crc_l != modbus_m.buffer[7])) // ��������� ����������� �����, ������ -1 ������ ��� �� ����� � ��� ��� ���������� -1
		{
			// ���������� ���� � ������� ������
			modbus_m.rxgap = 0;
			// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
			// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
			modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
			modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
			//!!!
			//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
			modbus_m.rxgap = 0;
			return 1; // ��������� ������ �� ������		
		}
	}
	// ���������� ���� � ������� ������
	modbus_m.rxgap = 0;
	// ������ ��������� ���������� ����� �������� ������ check_ans() ����� ������ 16 � 6, � ��� �� �����
	// ��������� ������ ans_command_3() �� SLAVE �� ������� 3
	modbus_m.rxtimer = 0; // ���������� �����, ���������� �� ����������� ����� ������ �� SLAVE
	modbus_m.rxcnt = 0;	// ���������� �������, �������� ���� �� SLAVE
	//!!!
	//USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);	// ���������� ���������� �� ������ USART
	modbus_m.rxgap = 0;
	return 0;
}