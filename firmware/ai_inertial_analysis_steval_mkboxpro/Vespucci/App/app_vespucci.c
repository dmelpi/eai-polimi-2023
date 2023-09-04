/**
 ******************************************************************************
 * File Name          : app_vespucci.c
 * Description        : This file provides code for the configuration
 *                      of the STMicroelectronics.X-CUBE-VESPUCCI.0.0.36 instances.
 ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
 ******************************************************************************
 */

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_vespucci.h"
#include "mlc_conf.h"
#include "main.h"
#include <stdio.h>
#include <ctype.h>

/* Definitions ---------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/

// Sensor.
uint8_t mems_event_detected;                                        // Set to "1" upon interrupt from FIFO.
float32_t sensor_acc_sensitivity;                                   // Sensitivity.

// Pre-processing.
pre_processing_data_t pre_processing_data;                          // Pre-processing data.

// Processing variables.
char command_buffer_static[COMMAND_BUFFER_SIZE] = {0};
char *command_buffer_ptr = &command_buffer_static[0];
char *command_buffer_write_ptr = &command_buffer_static[0];
uint32_t command_buffer_size = 0;
bool command_received = false;
char buffer_to_write[PRINTED_BUFFER_SIZE] = {0};                    // Buffer to be printed (it will contain the telemetries).
ai_type_t default_ai = MLC;                                         // Selected use-case.
int mcu_inference = 0;                                              // Flag when the application MCU is started.
int mlc_inference = 0;                                              // Flag when the application MLC is started.
int ispu_inference = 0;                                             // Flag when the application ISPU is started.
uint32_t mlc_register = 1;                                          // MLC Output Register number.

// Time measurement.
int32_t start_time;
int32_t stop_time;
int32_t time;

// MLC configuration
ucf_line_t* mlc_conf = &default_mlc_conf[0];
uint32_t mlc_conf_size = sizeof(default_mlc_conf)/sizeof(ucf_line_t);

/* Functions -----------------------------------------------------------------*/

/*
 * Initialization (sensor, pre-processing pipeline, AI-processing pipeline).
 */
int32_t MX_Vespucci_Init(void) {
	int32_t ret = 0;

	// Initializing USB.
	MX_USB_Device_Init();

	// USB initialization timeout (required to stabilize the USB peripheral voltage and to open the terminal).
	HAL_Delay(500);

#if 0
	// Sensor initialization timeout (required for sensor boot and to open the terminal).
	HAL_Delay(100);
#endif

	// Initializing sensor.
	sensor_init();

	// Initializing pre-processing.
	pre_processing_init(&pre_processing_data);

	// Initializing AI-processing.
	ai_init();

	// Initializing PnPL.
	pnpl_init();

	// Resetting command buffer.
	memset((char *) command_buffer_static, 0, COMMAND_BUFFER_SIZE);
	command_buffer_ptr = &command_buffer_static[0];
	command_buffer_write_ptr = &command_buffer_static[0];
	command_buffer_size = 0;
	command_received = false;

	// Printing commands format.
	PRINT("Start/Stop commands\r\n"
		"----------------------------------------------------------------------\r\n"
		"MCU: \r\n"
		"Start: {\"ai_application_mcu*start\":\"\"}\r\n"
		"Stop: {\"ai_application_mcu*stop\":\"\"}\r\n"
		"MLC: \r\n"
		"Start: {\"ai_application_mlc*start\":\"\"}\r\n"
		"Stop: {\"ai_application_mlc*stop\":\"\"}\r\n"
		"{\"ai_application_mlc*load_ucf\":{\"arguments\":{\"ucf_content\": \"ucf_file\"}}}\r\n"
		"ISPU: \r\n"
		"Start: {\"ai_application_ispu*start\":\"\"}\r\n"
		"Stop: {\"ai_application_ispu*stop\":\"\"}\r\n"
		"{\"ai_application_ispu*load_ucf\":{\"arguments\":{\"ucf_content\": \"ispu_file\"}}}\r\n"
		"----------------------------------------------------------------------\r\n"
		"Enter a command:\r\n");

	if (default_ai == MLC) {
		// Acquiring the MLC configuration and load the registers.
		load_mlc_configuration((ucf_line_t*) &default_mlc_conf, mlc_conf_size);
	}

/*
	if (default_ai == ISPU) {
		// Acquiring the ISPU configuration and load the registers.
		load_ispu_configuration((ucf_line_ext_t*)&ispu_conf, sizeof(ispu_conf) / sizeof(ucf_line_ext_t));
	}
*/

	// Start sending the MCU, MLC or ISPU telemetries.
	if (mcu_inference == 0 && default_ai == MCU) {

		// Initializing sensor.
		sensor_init();

		// Set the FIFO to Continuous/Stream Mode.
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_STREAM_MODE));
		// Initializing MLC inference.
		mcu_inference = 1;

	} else if (mlc_inference == 0 && default_ai == MLC) {

		// Initializing MLC inference.
		mlc_inference = 1;
	}
/*
	else if (ispu_inference == 0 && default_ai == ISPU) {

		// Initializing ISPU inference.
		ispu_inference = 1;
	}
*/

	return BSP_ERROR_NONE;
}


/*
 * Processing data (reading commands from USB and sending telemetries to USB).
 */
int32_t MX_Vespucci_Process(void) {

	// Executing command.
	if (command_received) {
		pnpl_process(command_buffer_ptr);
		// Resetting command buffer.
		command_buffer_size = command_buffer_write_ptr - command_buffer_ptr;
		memset((char *) command_buffer_ptr, 0, command_buffer_size);
		command_buffer_write_ptr = command_buffer_ptr;
		command_buffer_size = 0;
		command_received = false;
	}

	// Sending MCU telemetries.
	if (mcu_inference == 1) {
		send_telemetries_mcu();
	}

	// Sending MLC telemetries.
	if (mlc_inference == 1) {
		send_telemetries_mlc();
	}

	// Sending ISPU telemetries.
	if (ispu_inference == 1) {
		//send_telemetries_ispu();
	}

	return BSP_ERROR_NONE;
}


/*
 * Callback to serve the interrupt from the FIFO of the sensor.
 */
void HAL_GPIO_EXTI_Rising_Callback(uint16_t GPIO_Pin)
{
	mems_event_detected = 1;
}


/*
 * PnPL initialization function.
 */
void pnpl_init(){

	/* IAiApplication and IController object which contains the vtbl */
	static IAi_Application_Mcu_t ai_app_mcu_obj;
	static IAi_Application_Mlc_t ai_app_mlc_obj;
	static IAi_Application_Ispu_t ai_app_ispu_obj;
	static IController_t controller_obj;

	PnPL_Components_Alloc();
	PnPL_Components_Init(ai_app_mcu_obj, ai_app_mlc_obj, ai_app_ispu_obj, controller_obj);
}


/*
 * PnPL parsing function.
 */
void pnpl_process(char *command) {

	PnPLCommand_t PnPLCommand;
	char *SerializedJSON;
	uint32_t size;

	// Parsing load/start/stop commands.
	PnPLParseCommand(command, &PnPLCommand);

	// Serializing a GET message.
	if (PnPLCommand.comm_type == PNPL_CMD_GET) {
		PnPLSerializeResponse(&PnPLCommand, &SerializedJSON, &size, 0);
	}
}


/*
 * Reading sensor, pre-processing raw-data, AI-processing, sending telemetries.
 */
int32_t send_telemetries_mcu(){

	// Interrupt from FIFO
	if(mems_event_detected == 1){
		mems_event_detected = 0;

		// Debugging FIFO status.
		//debug_fifo_status();

		// Time measurement.
		//int32_t time_elapsed = 0;
		//int32_t time_elapsed2 = 0;
		//int32_t post_FIFO_read;
		//int32_t pre_FIFO_read;

		// Processing variables.
		int32_t ret = 0;
		tridimensional_data_t acc_sample_array[INPUT_BUFFER_SIZE];                                      // Sensor accelerometer
		float32_t pre_processing_output_array[INPUT_BUFFER_SIZE/2];                                     // Buffer containing the pre-processed output samples, ready for AI processing
		float32_t ai_output_array[2];                                                                   // Buffer containing the results from the AI processing
		int16_t acc_sample[3];                                                                          // Data bytes of sensor FIFO

		// pre_FIFO_read = BSP_GetTick();

		// Getting data from the sensor.
		for(int jj=0;jj<INPUT_BUFFER_SIZE;jj++){

			// Reading samples from the FIFO.
			CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Data_Word(SENSOR_0, MOTION_ACCELERO, acc_sample));

			// Conversion from [mg] to [g].
			acc_sample_array[jj].x = ((float)acc_sample[0])*sensor_acc_sensitivity*0.001;
			acc_sample_array[jj].y = ((float)acc_sample[1])*sensor_acc_sensitivity*0.001;
			acc_sample_array[jj].z = ((float)acc_sample[2])*sensor_acc_sensitivity*0.001;
		}

		// Pre-processing.
		pre_processing_process(acc_sample_array, INPUT_BUFFER_SIZE, pre_processing_output_array, AI_NETWORK_IN_1_SIZE, &pre_processing_data);

		// AI-processing.
		aiProcess(pre_processing_output_array, ai_output_array);

		// Getting neural network prediction.
		int label_id = (int) ai_output_array[0];
		float accuracy = ai_output_array[1];

		// Creating PnPL telemetry message.
		char *telemetry = NULL;
		uint32_t size = 100;
		ai_application_mcu_create_telemetry(label_id, accuracy, &telemetry, &size);

		// Checking null pointer exception.
		if (telemetry) {
			// Appending the new line character to the telemetry message.
			char *ch = "\r\n";
			strcat(telemetry, ch);

			// Printing telemetry message.
			PRINT(telemetry);

			// Clearing telemetry message.
			json_free_serialized_string(telemetry);
		}

		// Time measurement.
		// post_FIFO_read = BSP_GetTick();
		// time_elapsed = post_FIFO_read - pre_FIFO_read;
	}

	return BSP_ERROR_NONE;
}


/*
 * Sending MLC register outputs.
 */
int32_t send_telemetries_mlc() {
	uint8_t mlc_output_reg[8] = {0};
	read_mlc_output(mlc_output_reg);

	// Creating PnPL telemetry message.
	char *telemetry = NULL;
	uint32_t size = 128;
	ai_application_mlc_create_telemetry((int)mlc_output_reg[mlc_register], &telemetry, &size);

	// Checking null pointer exception.
	if(telemetry)
	{
		// Appending the new line character to the telemetry message.
		char *ch = "\r\n";
		strcat(telemetry, ch);

		// Printing telemetry message.
		PRINT(telemetry);

		// Clearing telemetry message.
		json_free_serialized_string(telemetry);
	}
	return BSP_ERROR_NONE;
}


/*
 * Debugging FIFO status.
 */
int32_t debug_fifo_status(void) {
	int32_t ret = 0;
	MY_LSM6DSV16X_Fifo_Status_t reg;
	char buffer[INPUT_BUFFER_SIZE];
	uint16_t samples = 0;

	CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Get_All_Status(SENSOR_0, &reg));

	if (reg.FifoWatermark)
	{
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Get_Num_Samples(SENSOR_0, &samples));
	}

	PRINT(buffer, "WTM, OVR, FULL, CBDR, OVRL : %d, %d, %d, %d, %d SAMPLES: %u\r\n\r\n", reg.FifoWatermark, reg.FifoOverrun, reg.FifoFull, reg.CounterBdr, reg.FifoOverrunLatched, samples);

	return BSP_ERROR_NONE;
}


/*
 * Parsing of the UCF file content for MLC.
 */
void parse_ucf_mlc(const char* ucf_content, ucf_line_t* mlc_configuration, uint32_t size) {

	uint32_t ucf_lines = size / COMPRESSED_UCF_LINE_WIDTH;
	uint32_t i;
	uint8_t ucf_reg[2] = {0};
	uint8_t ucf_data[2] = {0};
	uint8_t reg;
	uint8_t data;

	for (i = 0; i < ucf_lines; i++) {
		/* Write command */
		ucf_reg[0] = *(ucf_content++);
		ucf_reg[1] = *(ucf_content++);
		reg = (uint8_t) strtol((const char *) ucf_reg, NULL, 16);

		ucf_data[0] = *(ucf_content++);
		ucf_data[1] = *(ucf_content++);
		data = (uint8_t) strtol((const char *) ucf_data, NULL, 16);

		//(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, reg, data);
		mlc_configuration[i].address = reg;
		mlc_configuration[i].data = data;
	}
}


/*
 * Parsing of the UCF file content for ISPU.
 */
void parse_ucf_ispu(const char* ucf_content, ucf_line_ext_t* ispu_configuration, uint32_t size){

	uint32_t ucf_lines = size / COMPRESSED_UCF_LINE_WIDTH;
	uint32_t i;
	uint8_t ucf_reg[2] = {0};
	uint8_t ucf_data[2] = {0};
	uint8_t reg;
	uint8_t data;

	for (i = 0; i < ucf_lines; i++) {
		if (*ucf_content == 'W' || *ucf_content == 'w') {
			/* Wait command */
			ucf_content++;
			const char *ptr_save = NULL;
			ptr_save = strchr(ucf_content, '!') + 1;
			char* token = strtok((char *)ucf_content, "!");
			uint8_t delay_ms = atoi(token);
			// Increment the pointer to the next character after '!'.
			ucf_content = ptr_save;

			ispu_configuration[i].op = MEMS_UCF_OP_DELAY;
			ispu_configuration[i].address = 0;
			ispu_configuration[i].data = delay_ms;

		} else {
			/* Write command */
			ucf_reg[0] = *(ucf_content++);
			ucf_reg[1] = *(ucf_content++);
			reg = (uint8_t) strtol((const char *) ucf_reg, NULL, 16);

			ucf_data[0] = *(ucf_content++);
			ucf_data[1] = *(ucf_content++);
			data = (uint8_t) strtol((const char *) ucf_data, NULL, 16);

			ispu_configuration[i].op = MEMS_UCF_OP_WRITE;
			ispu_configuration[i].address = reg;
			ispu_configuration[i].data = data;
		}
	}
}


/*
* Programming the registers inside the MLC.
*/
void load_mlc_configuration(ucf_line_t* mlc_configuration, uint32_t ucf_number_of_lines) {
	// Iterating over each line in the configuration until NULL is reached.
	for (uint32_t i = 0; i < ucf_number_of_lines; i++) {
		CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, mlc_configuration[i].address, mlc_configuration[i].data);
	}
}


/*
 * Reading the content of the MLC output registers.
 */
void read_mlc_output(uint8_t* mlc_output_reg){

	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, LSM6DSV16X_FUNC_CFG_ACCESS, 0x80);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, LSM6DSV16X_MLC1_SRC, &mlc_output_reg[1]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, LSM6DSV16X_MLC2_SRC, &mlc_output_reg[2]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, LSM6DSV16X_MLC3_SRC, &mlc_output_reg[3]);
	(void)CUSTOM_MOTION_SENSOR_Read_Register(SENSOR_0, LSM6DSV16X_MLC4_SRC, &mlc_output_reg[4]);
	(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, LSM6DSV16X_FUNC_CFG_ACCESS, 0x00);
}


/*
 * Sending ISPU register outputs.
 */
/*
int32_t send_telemetries_ispu() {
	uint8_t ispu_output_reg[4] = {0};
	read_ispu_output(ispu_output_reg);

	// Creating PnPL telemetry message.
	char *telemetry = NULL;
	uint32_t size = 100;
	ai_application_ispu_create_telemetry((int)*ispu_output_reg, &telemetry, &size);

	// Checking null pointer exception.
	if(telemetry)
	{
		// Appending the new line character to the telemetry message.
		char *ch = "\r\n";
		strcat(telemetry, ch);

		// Printing telemetry message.
		PRINT(telemetry);

		// Clearing telemetry message.
		json_free_serialized_string(telemetry);
	}
	return BSP_ERROR_NONE;
}
*/


/*
 * Programming the registers inside the ISPU (used in the Init function, only at the beginning).
 */
#if 1
void load_ispu_configuration(ucf_line_ext_t* ispu_configuration, uint32_t ucf_number_of_lines) {
	// Iterating over each line in the configuration until NULL is reached.
	for (uint32_t i = 0; i < ucf_number_of_lines; i++) {
		if (ispu_configuration[i].op == MEMS_UCF_OP_WRITE) {
			//CUSTOM_ISPU_MOTION_SENSOR_Write_Register(SENSOR_ISPU, ispu_configuration[i].address, ispu_configuration[i].data);
		} else if (ispu_configuration[i].op == MEMS_UCF_OP_DELAY) {
			HAL_Delay(ispu_configuration[i].data);
		}
	}
}
#else
void load_ispu_configuration(ucf_line_ext_t* ispu_configuration) {
	int i;
	size_t len = len_ucf_ispu((ucf_line_ext_t**)&ispu_configuration);
	for(i=0;i<len;i++){
		if (ispu_configuration[i].op == MEMS_UCF_OP_WRITE){
			(void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(SENSOR_ISPU, ispu_configuration[i].address, ispu_configuration[i].data);
		}
		else if (ispu_configuration[i].op == MEMS_UCF_OP_DELAY){
			HAL_Delay(ispu_configuration[i].data);
		}
	}
}
#endif


/*
 * Reading the content of the ISPU output registers.
 */
/*
void read_ispu_output(uint8_t* ispu_output_reg) {
	(void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(SENSOR_ISPU, ISM330IS_FUNC_CFG_ACCESS, 0x80);
	(void)CUSTOM_ISPU_MOTION_SENSOR_Read_Register(SENSOR_ISPU, ISM330IS_ISPU_DOUT_06_L , &ispu_output_reg[0]);
	(void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(SENSOR_ISPU, ISM330IS_FUNC_CFG_ACCESS, 0x00);
}
*/


/*
 * Initialization (sensor).
 */
int32_t sensor_init() {
	int32_t ret = 0;

	CHECK_BSP_FUNCTION(CUSTOM_MOTION_SENSOR_Init(SENSOR_0, MOTION_ACCELERO));                                       // Sensor initialization
	CHECK_BSP_FUNCTION(CUSTOM_MOTION_SENSOR_SetOutputDataRate(SENSOR_0, MOTION_ACCELERO, SENSOR_ODR));              // Sensor ODR
	CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_BDR(SENSOR_0, MOTION_ACCELERO, SENSOR_ODR));                // FIFO ODR (Note: all APIs with "MY" are implemented in the MEMS_integration.c file, not in the X-CUBE-MEMS1 pack)
	CHECK_BSP_FUNCTION(CUSTOM_MOTION_SENSOR_SetFullScale(SENSOR_0, MOTION_ACCELERO, SENSOR_FS));                    // Sensor Full Scale

/*
	if(default_ai==ISPU){
		// Initializing ISPU sensor.
		CHECK_BSP_FUNCTION(CUSTOM_ISPU_MOTION_SENSOR_Init(SENSOR_ISPU, MOTION_ACCELERO));                               // Sensor ISPU initialization
	}
*/

	// Getting sensor sensitivity.
	CHECK_BSP_FUNCTION(CUSTOM_MOTION_SENSOR_GetSensitivity(SENSOR_0, MOTION_ACCELERO, &sensor_acc_sensitivity));

	// Initializing sensor FIFO.
	// Sensor FIFO init.
	if (INPUT_BUFFER_SIZE == 512){
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(SENSOR_0, ENABLE));                      // Interrupt set at FIFO_FULL (all FIFO used)
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT1(SENSOR_0, DISABLE));
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT1(SENSOR_0, ENABLE));
	} else {
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_INT1_FIFO_Full(SENSOR_0, DISABLE));
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Watermark_Level(SENSOR_0, INPUT_BUFFER_SIZE));          // Set the Watermark level to INPUT_BUFFER_SIZE
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Watermark_Set_INT1(SENSOR_0, ENABLE));                      // Enable the Watermark Interrupt
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Overrun_Set_INT1(SENSOR_0, ENABLE));
		CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Stop_On_Fth(SENSOR_0,  ENABLE));                        // Limit the FIFO depth to the Watermark level
	}
	CHECK_BSP_FUNCTION(MY_CUSTOM_MOTION_SENSOR_FIFO_Set_Mode(SENSOR_0,  LSM6DSV16X_BYPASS_MODE));                   // Set the FIFO to Bypass Mode

	return BSP_ERROR_NONE;
}


/*
 * Extracting the numebr of lines from the .ucf file.
 */
uint32_t get_ucf_number_of_lines(int32_t ucf_content_size, const char *ucf_content) {
	uint32_t ucf_number_of_lines = 0;
	uint32_t i;

	for (i = 0; i < ucf_content_size; i++) {
		ucf_number_of_lines += (ucf_content[i] == '\n' ? 1 : 0);
	}

	return ucf_number_of_lines;
}


/*
 * Filling MLC configuration structure from UCF file.
 */
void fill_mlc_configuration(const char* ucf_content, ucf_line_t* mlc_configuration) {

    const char* delimiters = "\n ";
    char *token;
    uint32_t i = 0;
    uint8_t addr, data;

    // Parsing UCF file.
    char *start = strstr(ucf_content, "Ac ");
    char *input = (char *) calloc(strlen(start) + 1, sizeof(char));
    strcpy(input, start);
    token = strtok(input, delimiters);
    while (token != NULL) {
        // Extracting the Ac characters at the beginning of the token.
        char cmd_char[2];
        strcpy(cmd_char, token);
        if (strcmp(cmd_char, "Ac") == 0) {
            // Extracting the first hexadecimal value after "Ac".
            char* hex_address = strtok(NULL, delimiters);
            // Extracting the second hexadecimal value after "Ac".
            char* hex_data = strtok(NULL, delimiters);
            // Converting into uint8_t type.
            addr = (uint8_t) strtol(hex_address, NULL, 16);
            data = (uint8_t) strtol(hex_data, NULL, 16);
            // Filling MLC configuration structure.
            mlc_configuration[i].address = addr;
            mlc_configuration[i].data = data;
        }
        // Going on with the next token.
        token = strtok(NULL, delimiters);
        i++;
    }
    free(token);
}


/*
 * Getting MLC register from UCF file.
 */
void get_mlc_register(const char* ucf_content, uint32_t *mlc_register) {

	char *start = strstr(ucf_content, "<MLC");
    if (start == NULL) {
        return;
    }
    start += 4;   // skip "<MLC"
    char *end = strstr(start, "_SRC>");
    if (end == NULL) {
        return;
    }
    int len = end - start;
    char *mlc_str = (char *) calloc(len + 1, sizeof(char));
    strncpy(mlc_str, start, len);
    mlc_str[len] = '\0';
    *mlc_register = atoi(mlc_str);
}


#if 0
/*
 * Load the compressed ucf file content in the ISPU registers.
 */
void load_compressed_ucf(const char *p_ucf, uint32_t size)
{
	uint32_t ucf_lines = size / COMPRESSED_UCF_LINE_WIDTH;
	uint32_t i;
	uint8_t ucf_reg[2] = {0};
	uint8_t ucf_data[2] = {0};
	uint8_t reg;
	uint8_t data;

	for (i = 0; i < ucf_lines; i++) {
		if (*p_ucf == 'W' || *p_ucf == 'w') {
			/* Wait command */
			p_ucf++;
			const char *ptr_save = NULL;
			ptr_save = strchr(p_ucf, '!') + 1;
			char* token = strtok((char *)p_ucf, "!");
			uint16_t delay_ms = atoi(token);
			// Increment the pointer to the next character after '!'
			p_ucf = ptr_save;

			// Implement delay function for the specified milliseconds
			HAL_Delay(delay_ms);

		} else {
			/* Write command */
			ucf_reg[0] = *(p_ucf++);
			ucf_reg[1] = *(p_ucf++);
			reg = (uint8_t) strtol((const char *) ucf_reg, NULL, 16);

			ucf_data[0] = *(p_ucf++);
			ucf_data[1] = *(p_ucf++);
			data = (uint8_t) strtol((const char *) ucf_data, NULL, 16);

			// Implement sensor register write function
			if (default_ai == ISPU) {
				(void)CUSTOM_ISPU_MOTION_SENSOR_Write_Register(SENSOR_ISPU, reg, data);
			} else if (default_ai == MLC) {
				(void)CUSTOM_MOTION_SENSOR_Write_Register(SENSOR_0, reg, data);
			}
		}
	}
}


/*
 * Helper function to remove spaces from a string.
 */
void remove_spaces(char* str) {
	int len = strlen(str);
	int i, j;
	for (i = 0, j = 0; i < len; i++) {
		if (!isspace((unsigned char)str[i])) {
			str[j++] = str[i];
		}
	}
	str[j] = '\0';
}


/*
 * Compress the command+ucf such that it occupies less space in memory.
 */
char* compress(char* compressed_lines, const char *p_ucf) {
	int line_count = 0;
	int i = 0;
	int flag = 0;

	// Copy the lines before "Ac" prefix until \"ucf_content\":\"
	while (p_ucf[i] != 'A' || p_ucf[i + 1] != 'c') {
		if(flag == 1){
			i++;
		}
		else{
			compressed_lines[line_count++] = p_ucf[i++];
		}
		if (strncmp(&p_ucf[i], "\"ucf_content\":\"", 15) == 0) {
			memcpy(&compressed_lines[line_count], &p_ucf[i], 15);
			i += 15; // Skip "ucf_content":" prefix
			line_count += 15;
			flag = 1;
		}
	}

	flag = 0;

	// UCF Content handling
	// Remove "Ac" and spaces, and concatenate the lines without wrapping
	while (p_ucf[i] != '\0') {
		if (p_ucf[i] == 'A' && p_ucf[i + 1] == 'c') {
			i += 2; // Skip "Ac " prefix
		} else if (p_ucf[i] == ' ') {
			i++;    // Skip spaces
		} else if (p_ucf[i] == '\n' || p_ucf[i] == '\r' || p_ucf[i] == '\\' || p_ucf[i] == 'n') {
			i++;    // Skip newlines
		} else if (strncmp(&p_ucf[i], "WAIT", 4) == 0) {
			compressed_lines[line_count++] = 'W';
			// Start at the character after "WAIT "
			i += 4;
			while(p_ucf[i] != '\n' && p_ucf[i] != '\r' && p_ucf[i] != '\\' && p_ucf[i] != 'n'){
				compressed_lines[line_count++] = p_ucf[i++];
			}
			compressed_lines[line_count++] = '!'; //terminator for atoi (delay)
		} else if(p_ucf[i] == 'u' && p_ucf[i + 1] == '0' && p_ucf[i + 2] == '0' && p_ucf[i + 3] == '0' && p_ucf[i + 4] == '0'){
			i += 5;
		} else {
			compressed_lines[line_count++] = p_ucf[i++];
		}
	}
	compressed_lines[line_count] = '\0'; // Null-terminate the modified lines

	return compressed_lines;
}


/*
 * Check whether the command is valid.
 */
command_t is_valid_command(char* command, uint32_t command_size) {

	if (strstr(command, MCU_START_CMD_STR) ||
		strstr(command, MCU_STOP_CMD_STR) ||
		strstr(command, MLC_START_CMD_STR) ||
		strstr(command, MLC_STOP_CMD_STR) ||
		strstr(command, ISPU_START_CMD_STR) ||
		strstr(command, ISPU_STOP_CMD_STR) ||
		strstr(command, SWITCH_BANK_CMD_STR)) {
		return VALID_CMD;
	}
}

	if (strstr(command, MLC_LOAD_UCF_CMD_STR)) {
		return MLC_LOAD_UCF_CMD;
	}

	if (strstr(command, ISPU_LOAD_UCF_CMD_STR)) {
		return ISPU_LOAD_UCF_CMD;
	}

	return INVALID_CMD;
}

/*
 * Check if a command contains the given key; if this is the case return true
 * and store value, otherwise return false.
 *
 * E.g.: "{"ai_application_mlc*load_ucf":{"arguments":{"ucf_content_size":5391,"ucf_content":"..."}}}"
 */
bool get_parameter_uint32_t(char* command, char* key, uint32_t* value, uint32_t* lenght) {
	char* start_ptr = strstr(command, key);
	if (start_ptr) {
		start_ptr += strlen(key);
		char* end_ptr = strchr(start_ptr, ',');
		if (end_ptr) {
			start_ptr += 2;
			*end_ptr = '\0';
			*value = atoi(start_ptr);
			*end_ptr = ',';
			*lenght = end_ptr - start_ptr;
			return true;
		}
	}
	return false;
}
#endif
