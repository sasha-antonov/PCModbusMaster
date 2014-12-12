#include <windows.h>
#include <iostream>
#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"
#include <stdlib.h> 

using namespace std;

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;

uint8_t error;

struct modbus_temporary modbus_m;

#pragma pack(push, 1)  
struct group_1_s group_1;
struct group_2_s group_2;
struct group_3_s group_3;
#pragma pack(pop)

// typedef void *HANDLE; ��������� �� ������ ���������
HANDLE hPort; // ��������� ��� ���������� com-port (h_port - �����)
//LPCTSTR sPortName = L"COM1";
DCB dcbSerialParams = {0};

uint8_t f_port = 0;

uint16_t head_modbus;
uint16_t i;

uint8_t* buffer;

int main()
{
	command_3(1, 0, (uint8_t*)&head_modbus, 2);	
	WriteComPort(modbus_m.buffer, modbus_m.tr_len);
	ReadComPort();
	error = check_ans();
	ans_command_3((uint8_t*)&head_modbus);
	
	buffer = (uint8_t*)malloc(head_modbus * 20);

	for(i = 0; i < head_modbus; i++) {
		command_3(1, 10000 + i*10, buffer + i*20, 20);	
		WriteComPort(modbus_m.buffer, modbus_m.tr_len);
		ReadComPort();
		error = check_ans();
		ans_command_3(buffer + i*20);
	}
	
	// ������ ������ ��������� - ���������	����� ����������, �����	modbus ������ ������ ���������� ��� ������, 
	// ��������� �� ��� ������ � ������ ��������� ������ (sizeof())
	command_3(1, GROUP_3_ADR, (uint8_t*)&group_3, sizeof(group_3));	
	// �������� usart ��� ��������
	
	WriteComPort(modbus_m.buffer, modbus_m.tr_len);
	ReadComPort();
	
	error = check_ans(); // �������� ������ - ��� ���������� � ������ - ���� ��������� ������ ��������� 1
	
	// �������� 3 - ��� ������ - ������ � ������ ���������� ���������� � ��������� ��������� modbus
	// ������ ������� ������������ ����� �� slave ��� command_3 ����������� ��� � ��������� � ������ ���������� 
	// �� ������� ��� ������ ������. ��������� ��������� �� ��������� � ����������� � ������� ���������� ������.
	ans_command_3((uint8_t*)&group_3); 

	
	// ������ ������ ��������� -  ���������	����� ����������, �����	modbus ������ ������ ���������� ��� ������, 
	// ��������� �� ��� ������ � ������ ��������� ������ (sizeof())
	command_16(1, GROUP_3_ADR, (uint8_t*)&group_3, sizeof(group_3));
	//!!! �������� �� USART
	
	WriteComPort(modbus_m.buffer, modbus_m.tr_len);
	ReadComPort();

	error = check_ans();
	
	// ������ ������ �������� -  ���������	����� ����������, �����	modbus ���������� ��� ������, 
	// ��������� �� ���
	command_6(1, GROUP_3_ADR, (uint8_t*)&group_3);
	//!!! �������� �� USART

	WriteComPort(modbus_m.buffer, modbus_m.tr_len);
	ReadComPort();

	error = check_ans();

	return 0;
}
