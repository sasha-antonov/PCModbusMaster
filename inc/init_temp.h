
// глобальные переменные библиотеки modbus master
struct modbus_temporary
{
	uint16_t rxtimer; //для определения конца пакета от SLAVE - сравнивается с DELAY
	uint16_t rxcnt;	// счетчик байт принятых от SLAVE
	uint16_t rxgap;	// флаг прихода пакета от SLAVE
	uint16_t nvic_byte_tr; // счет передаваемых байт MASTERом
	uint16_t tr_len; // счет передаваемых байт MASTERом
	uint8_t buffer[256]; // буффер где хранятся принимаемые/передаваемые данные + расчет CRC
};

