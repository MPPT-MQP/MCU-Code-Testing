/*
 *  ======== INA740.h ========
 *  INA740 Interface
 */
#ifndef ti_sensors_INA740__include
#define ti_sensors_INA740__include 1

#include <stdint.h>

/* support C++ sources */
#ifdef __cplusplus
extern "C" {
#endif

#define INA740_config_register 0x00U
#define INA740_config_register_rst_NormalOperation 0x0000U
#define INA740_config_register_rst_SystemReset 0x8000U
#define INA740_config_register_rstacc_NormalOperation 0x0000U
#define INA740_config_register_rstacc_ClearENERGYandCHARGEregisters 0x4000U
#define INA740_config_register_reserved0_ENABLE 0x0020U
#define INA740_config_register_reserved0_DISABLE 0x0000U
#define INA740_config_register_reserved1_ENABLE 0x0010U
#define INA740_config_register_reserved1_DISABLE 0x0000U
#define INA740_adc_config_register 0x01U
#define INA740_adc_config_register_mode_Shutdown0 0x0000U
#define INA740_adc_config_register_mode_Triggeredbusvoltagesingleshot 0x1000U
#define INA740_adc_config_register_mode_Triggeredtemperaturesingleshot 0x4000U
#define INA740_adc_config_register_mode_Triggeredtemperatureandbusvoltagesingleshot 0x5000U
#define INA740_adc_config_register_mode_Triggeredtemperatureandcurrentsingleshot 0x6000U
#define INA740_adc_config_register_mode_Triggeredtemperaturecurrentandbusvoltagesingleshot 0x7000U
#define INA740_adc_config_register_mode_Shutdown1 0x8000U
#define INA740_adc_config_register_mode_Continuousbusvoltageonly 0x9000U
#define INA740_adc_config_register_mode_Continuoustemperatureonly 0xC000U
#define INA740_adc_config_register_mode_Continuousbusvoltageandtemperature 0xD000U
#define INA740_adc_config_register_mode_Continuoustemperatureandcurrent 0xE000U
#define INA740_adc_config_register_mode_Continuoustemperaturecurrentandbusvoltage 0xF000U
#define INA740_adc_config_register_vbusct_50us 0x0000U
#define INA740_adc_config_register_vbusct_84us 0x0200U
#define INA740_adc_config_register_vbusct_150us 0x0400U
#define INA740_adc_config_register_vbusct_280us 0x0600U
#define INA740_adc_config_register_vbusct_540us 0x0800U
#define INA740_adc_config_register_vbusct_1052us 0x0A00U
#define INA740_adc_config_register_vbusct_2074us 0x0C00U
#define INA740_adc_config_register_vbusct_4120us 0x0E00U
#define INA740_adc_config_register_vsenct_50us 0x0000U
#define INA740_adc_config_register_vsenct_84us 0x0040U
#define INA740_adc_config_register_vsenct_150us 0x0080U
#define INA740_adc_config_register_vsenct_280us 0x00C0U
#define INA740_adc_config_register_vsenct_540us 0x0100U
#define INA740_adc_config_register_vsenct_1052us 0x0140U
#define INA740_adc_config_register_vsenct_2074us 0x0180U
#define INA740_adc_config_register_vsenct_4120us 0x01C0U
#define INA740_adc_config_register_tct_50us 0x0000U
#define INA740_adc_config_register_tct_84us 0x0008U
#define INA740_adc_config_register_tct_150us 0x0010U
#define INA740_adc_config_register_tct_280us 0x0018U
#define INA740_adc_config_register_tct_540us 0x0020U
#define INA740_adc_config_register_tct_1052us 0x0028U
#define INA740_adc_config_register_tct_2074us 0x0030U
#define INA740_adc_config_register_tct_4120us 0x0038U
#define INA740_adc_config_register_avg_1 0x0000U
#define INA740_adc_config_register_avg_4 0x0001U
#define INA740_adc_config_register_avg_16 0x0002U
#define INA740_adc_config_register_avg_64 0x0003U
#define INA740_adc_config_register_avg_128 0x0004U
#define INA740_adc_config_register_avg_256 0x0005U
#define INA740_adc_config_register_avg_512 0x0006U
#define INA740_adc_config_register_avg_1024 0x0007U
#define INA740_vbus_register 0x05U
#define INA740_dietemp_register 0x06U
#define INA740_current_register 0x07U
#define INA740_power_register 0x08U
#define INA740_energy_register 0x09U
#define INA740_charge_register 0x0AU
#define INA740_alert_diag_register 0x0BU
#define INA740_alert_diag_register_alatch_Transparent 0x0000U
#define INA740_alert_diag_register_alatch_Latched 0x8000U
#define INA740_alert_diag_register_cnvr_DisableconversionreadyflagonALERTpin 0x0000U
#define INA740_alert_diag_register_cnvr_EnablesconversionreadyflagonALERTpin 0x4000U
#define INA740_alert_diag_register_slowalert_ALERTcomparisononnonaveragedADCvalue 0x0000U
#define INA740_alert_diag_register_slowalert_ALERTcomparisononaveragedvalue 0x2000U
#define INA740_alert_diag_register_apol_Normalactivelowopendrain 0x0000U
#define INA740_alert_diag_register_apol_Invertedactivehighopendrain 0x1000U
#define INA740_alert_diag_register_energyof_ENABLE 0x0800U
#define INA740_alert_diag_register_energyof_DISABLE 0x0000U
#define INA740_alert_diag_register_chargeof_ENABLE 0x0400U
#define INA740_alert_diag_register_chargeof_DISABLE 0x0000U
#define INA740_alert_diag_register_mathof_ENABLE 0x0200U
#define INA740_alert_diag_register_mathof_DISABLE 0x0000U
#define INA740_alert_diag_register_reserved0_ENABLE 0x0100U
#define INA740_alert_diag_register_reserved0_DISABLE 0x0000U
#define INA740_alert_diag_register_tmpol_ENABLE 0x0080U
#define INA740_alert_diag_register_tmpol_DISABLE 0x0000U
#define INA740_alert_diag_register_currentol_ENABLE 0x0040U
#define INA740_alert_diag_register_currentol_DISABLE 0x0000U
#define INA740_alert_diag_register_currentul_ENABLE 0x0020U
#define INA740_alert_diag_register_currentul_DISABLE 0x0000U
#define INA740_alert_diag_register_busol_ENABLE 0x0010U
#define INA740_alert_diag_register_busol_DISABLE 0x0000U
#define INA740_alert_diag_register_busul_ENABLE 0x0008U
#define INA740_alert_diag_register_busul_DISABLE 0x0000U
#define INA740_alert_diag_register_pol_ENABLE 0x0004U
#define INA740_alert_diag_register_pol_DISABLE 0x0000U
#define INA740_alert_diag_register_cnvrf_ENABLE 0x0002U
#define INA740_alert_diag_register_cnvrf_DISABLE 0x0000U
#define INA740_alert_diag_register_memstat_ENABLE 0x0001U
#define INA740_alert_diag_register_memstat_DISABLE 0x0000U
#define INA740_col_register 0x0CU
#define INA740_cul_register 0x0DU
#define INA740_bovl_register 0x0EU
#define INA740_bovl_register_reserved0_ENABLE 0x8000U
#define INA740_bovl_register_reserved0_DISABLE 0x0000U
#define INA740_buvl_register 0x0FU
#define INA740_buvl_register_reserved0_ENABLE 0x8000U
#define INA740_buvl_register_reserved0_DISABLE 0x0000U
#define INA740_temp_limit_register 0x10U
#define INA740_pwr_limit_register 0x11U
#define INA740_manufacturer_id_register 0x3EU


/*
 *  ======== INA740_State ========
 *  Initial configuration state for a INA740 sensor
 */
typedef struct INA740_State {
    uint16_t configRegister;
    uint16_t adcConfigRegister;
    uint16_t alertDiagRegister;
    uint16_t colRegister;
    uint16_t culRegister;
    uint16_t bovlRegister;
    uint16_t buvlRegister;
    uint16_t tempLimitRegister;
    uint16_t pwrLimitRegister;


    uint8_t busId;   /* I2C bus id */
    uint8_t devAddr; /* Sensor's I2C address on the bus */

    uint16_t osWait; /* One shot conversion time (in ms)  */
} INA740_State;

/*
 *  ======== INA740_Handle ========
 *  First argument to all INA740 methods
 */
typedef INA740_State *INA740_Handle;

/*
 *  ======== INA740_writeReg ========
  * Write register
  */
extern void INA740_writeReg(INA740_Handle sensor, uint8_t regAddr, uint16_t value);

/*
 *  ======== INA740_config ========
 *  Configure device with current settings
 */
extern void INA740_config(INA740_Handle sensor);

/*
 *  ======== INA740_readReg ========
 *  Read register
 */
extern uint64_t INA740_readReg(INA740_Handle sensor, uint8_t regAddr);

/*
 *  ======== INA740_getVBUS_V ========
 *  Get VBUS value (V)
 */
extern float INA740_getVBUS_V(INA740_Handle sensor);

/*
 *  ======== INA740_getDIETEMP_C ========
 *  Get DIETMEP value (C)
 */
extern float INA740_getDIETEMP_C(INA740_Handle sensor);

/*
 *  ======== INA740_getDIETEMP_F ========
 *  Get DIETMEP value (F)
 */
extern float INA740_getDIETEMP_F(INA740_Handle sensor);

/*
 *  ======== INA740_getCURRENT_A ========
 *  Get CURRENT value (A)
 */
extern float INA740_getCURRENT_A(INA740_Handle sensor);

/*
 *  ======== INA740_getPOWER_W ========
 *  Get POWER value (W)
 */
extern float INA740_getPOWER_W(INA740_Handle sensor);

/*
 *  ======== INA740_getENERGY_J ========
 *  Get ENERGY value (J)
 */
extern double INA740_getENERGY_J(INA740_Handle sensor);

/*
 *  ======== INA740_getCHARGE_C ========
 *  Get CHARGE value (C)
 */
extern double INA740_getCHARGE_C(INA740_Handle sensor);

/* support C++ sources */
#ifdef __cplusplus
}
#endif

#endif
