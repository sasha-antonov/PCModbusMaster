void command_3(uint8_t adr_device, uint16_t adr_group, uint8_t* group, uint16_t size);
uint16_t crc16(uint8_t *adr_buffer, uint32_t byte_cnt);
uint8_t check_ans(void);
void ans_command_3(uint8_t* group);
void command_16(uint8_t adr_device, uint16_t adr_group, uint8_t* group, uint16_t size);
void command_6(uint8_t adr_device, uint16_t data_reg, uint8_t* group);
void WriteComPort(uint8_t* buf, uint16_t len);
void ReadComPort(void);