
// ���������� ���������� ���������� modbus master
struct modbus_temporary
{
	uint16_t rxtimer; //��� ����������� ����� ������ �� SLAVE - ������������ � DELAY
	uint16_t rxcnt;	// ������� ���� �������� �� SLAVE
	uint16_t rxgap;	// ���� ������� ������ �� SLAVE
	uint16_t nvic_byte_tr; // ���� ������������ ���� MASTER��
	uint16_t tr_len; // ���� ������������ ���� MASTER��
	uint8_t buffer[256]; // ������ ��� �������� �����������/������������ ������ + ������ CRC
};

