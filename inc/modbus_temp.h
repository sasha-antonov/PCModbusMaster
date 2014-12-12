#pragma once

#define DELAY 40 // определяет задержку конца прихода пакета от SLAVE

#define GROUP_1_ADR 0 // адреса первой группы переменных
#define GROUP_2_ADR 100	// адреса второй группы переменных
#define GROUP_3_ADR 1000	// и т.д. ...

// Структуры = группы переменных для записи чтения
struct group_1_s
{
	uint16_t x1;
	uint16_t x2;
	uint16_t x3;
	uint16_t x4;
};

struct group_2_s
{
	uint16_t x5;
	uint16_t x6;
	uint16_t x7;
	uint16_t x8;
};

#pragma pack(push, 1) 
struct group_3_s
{
	uint16_t number_contr;
	uint16_t direct_port;
	
	uint16_t time_rec;
	uint16_t time_rec_port_1;
	uint16_t time_rec_port_2;
	uint16_t time_rec_port_3;
	
	uint16_t time_test_buf;
	uint16_t time_busy_rec;
	uint32_t time_del_data_port;
	
	uint16_t test4b;
};
#pragma pack(pop)

// объявляем как глобальные
extern struct group_1_s group_1;
extern struct group_2_s group_2;
extern struct group_3_s group_3;

