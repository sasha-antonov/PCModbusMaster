#include <windows.h>
#include <iostream>
using namespace std;

#include "type.h"
#include "init_temp.h"
#include "head_func.h"
#include "modbus_temp.h"

// typedef void *HANDLE; указатель на пустую структуру
extern HANDLE hPort; // структура для управления com-port (h_port - адрес)
//LPCTSTR sPortName = L"COM1";
extern DCB dcbSerialParams;

extern struct modbus_temporary modbus_m;
extern uint8_t f_port;

void WriteComPort(uint8_t* buf, uint16_t len) {

  DWORD dwSize = len + 1;
  DWORD dwBytesWritten;
  buf[0] = 1;
  
  if(f_port == 0) {
	  f_port = 1;

      hPort = CreateFile("COM4", GENERIC_READ | GENERIC_WRITE, 0, 0,
	  OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);

	  if(hPort == INVALID_HANDLE_VALUE) {
		if(GetLastError() == ERROR_FILE_NOT_FOUND) {
		  cout << "serial port does not exist \n";
		} else {
		  cout << "other error \n";
		}
	  }

	  dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
	  if(!GetCommState(hPort, &dcbSerialParams)) {
		cout << "getting state error\n";
	  }
	  dcbSerialParams.BaudRate = CBR_9600;
	  dcbSerialParams.ByteSize = 8;
	  dcbSerialParams.StopBits = ONESTOPBIT;
	  dcbSerialParams.Parity = NOPARITY;

	  if(!SetCommState(hPort, &dcbSerialParams)) {
		cout << "error setting serial port state \n"; 
	  }
  }
 
  WriteFile(hPort, buf, dwSize, &dwBytesWritten, NULL); 
} 

void ReadComPort(void) { 
  DWORD iSize; 
  char sReceivedChar; 
  modbus_m.rxcnt = 0;

  while(modbus_m.rxgap != 1) // ждем ответа - ответный пакет приходит = modbus_m.rxgap=1
  {
	  ReadFile(hPort, &sReceivedChar, 1, &iSize, 0); 
	  modbus_m.buffer[modbus_m.rxcnt] = sReceivedChar;
	  modbus_m.rxcnt = modbus_m.rxcnt + iSize;
	  if(modbus_m.rxcnt > 2) {
		  
		  if(modbus_m.buffer[1] == 3) {
			if(modbus_m.rxcnt > 4) {
			  if(modbus_m.rxcnt == (modbus_m.buffer[2] + 5)) {
				  modbus_m.rxgap = 1;		
			  }
			}	  
		  }

		  if(modbus_m.buffer[1] == 6) {
			  if(modbus_m.rxcnt == 8) {
				modbus_m.rxgap = 1;		
			  }
		  }

		  if(modbus_m.buffer[1] == 16) {
			  if(modbus_m.rxcnt == 8) {
				modbus_m.rxgap = 1;		
			  }
		  }
	  }
  }
}
