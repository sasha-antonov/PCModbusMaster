#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

extern struct modbus_temporary modbus_m;

void ans_command_3(uint8_t* group)
{
	//uint8_t temp = 0;
	uint8_t i;	

	// ������������ ������ �� ��������� ������ � ��������� ����������
	for(i=0; i<modbus_m.buffer[2]; i=i+2)
	{
		// � ���s���������� ��������� �� 1 ���� �������� ���������� ���� �� ��������� ���������
		*(group + i) = modbus_m.buffer[3 + i + 1];
		*(group + 1 + i) = modbus_m.buffer[3 + i]; // �� �� ����� ������ �� ������ ������
		//temp = temp + 2; // ������ ���� ����������� �� 2  � ��� �� �� ����� ��� ���� ��������� � ���������
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
}

