#define ID_Control 0x0
#define DLC_Control  8

#define CAN_TO_REAL_Control_FreigabeWZS2(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_FreigabeWZS2(x) ( uint8_t)(((x) - 0) / 1)

#define SET_Control_FreigabeWZS2_Raw(buf,val) {\
   buf[2] |= (uint8_t)((val) >> 0) << 6;\
}

#define SET_Control_FreigabeWZS2(buf,val) \
   SET_Control_FreigabeWZS2_Raw(buf,REAL_TO_CAN_Control_FreigabeWZS2(val))

#define GET_Control_FreigabeWZS2_Raw(buf) (0\
   | ((( uint8_t)(buf[2] >> 6) & 0x3) << 0) \
)

#define GET_Control_FreigabeWZS2(buf) \
   CAN_TO_REAL_Control_FreigabeWZS2(GET_Control_FreigabeWZS2_Raw(buf))

#define CAN_TO_REAL_Control_Sollgeschwindigkeit(x)           ( (x) * 0.1 + 0)
#define REAL_TO_CAN_Control_Sollgeschwindigkeit(x) (uint16_t)(((x) - 0) / 0.1)

#define SET_Control_Sollgeschwindigkeit_Raw(buf,val) {\
   buf[6] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_Sollgeschwindigkeit(buf,val) \
   SET_Control_Sollgeschwindigkeit_Raw(buf,REAL_TO_CAN_Control_Sollgeschwindigkeit(val))

#define GET_Control_Sollgeschwindigkeit_Raw(buf) (0\
   | ((( uint8_t)(buf[6] >> 0) & 0xff) << 0) \
)

#define GET_Control_Sollgeschwindigkeit(buf) \
   CAN_TO_REAL_Control_Sollgeschwindigkeit(GET_Control_Sollgeschwindigkeit_Raw(buf))

#define CAN_TO_REAL_Control_Sollarbeitsergebnis(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_Sollarbeitsergebnis(x) (uint16_t)(((x) - 0) / 1)

#define SET_Control_Sollarbeitsergebnis_Raw(buf,val) {\
   buf[5] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_Sollarbeitsergebnis(buf,val) \
   SET_Control_Sollarbeitsergebnis_Raw(buf,REAL_TO_CAN_Control_Sollarbeitsergebnis(val))

#define GET_Control_Sollarbeitsergebnis_Raw(buf) (0\
   | ((( uint8_t)(buf[5] >> 0) & 0xff) << 0) \
)

#define GET_Control_Sollarbeitsergebnis(buf) \
   CAN_TO_REAL_Control_Sollarbeitsergebnis(GET_Control_Sollarbeitsergebnis_Raw(buf))

#define CAN_TO_REAL_Control_Sollkraft(x)           ( (x) * 150 + 0)
#define REAL_TO_CAN_Control_Sollkraft(x) (uint16_t)(((x) - 0) / 150)

#define SET_Control_Sollkraft_Raw(buf,val) {\
   buf[4] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_Sollkraft(buf,val) \
   SET_Control_Sollkraft_Raw(buf,REAL_TO_CAN_Control_Sollkraft(val))

#define GET_Control_Sollkraft_Raw(buf) (0\
   | ((( uint8_t)(buf[4] >> 0) & 0xff) << 0) \
)

#define GET_Control_Sollkraft(buf) \
   CAN_TO_REAL_Control_Sollkraft(GET_Control_Sollkraft_Raw(buf))

#define CAN_TO_REAL_Control_Geschwindigkeitsbereich(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_Geschwindigkeitsbereich(x) (uint16_t)(((x) - 0) / 1)

#define SET_Control_Geschwindigkeitsbereich_Raw(buf,val) {\
   buf[3] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_Geschwindigkeitsbereich(buf,val) \
   SET_Control_Geschwindigkeitsbereich_Raw(buf,REAL_TO_CAN_Control_Geschwindigkeitsbereich(val))

#define GET_Control_Geschwindigkeitsbereich_Raw(buf) (0\
   | ((( uint8_t)(buf[3] >> 0) & 0xff) << 0) \
)

#define GET_Control_Geschwindigkeitsbereich(buf) \
   CAN_TO_REAL_Control_Geschwindigkeitsbereich(GET_Control_Geschwindigkeitsbereich_Raw(buf))

#define CAN_TO_REAL_Control_FreigabeWZS1(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_FreigabeWZS1(x) (uint16_t)(((x) - 0) / 1)

#define SET_Control_FreigabeWZS1_Raw(buf,val) {\
   buf[3] |= (uint8_t)((val) >> 0) << 0;\
   buf[4] |= (uint8_t)((val) >> 8) << 0;\
}

#define SET_Control_FreigabeWZS1(buf,val) \
   SET_Control_FreigabeWZS1_Raw(buf,REAL_TO_CAN_Control_FreigabeWZS1(val))

#define GET_Control_FreigabeWZS1_Raw(buf) (0\
   | ((( uint8_t)(buf[3] >> 0) & 0xff) << 0) \
   | (((uint16_t)(buf[4] >> 0) & 0xff) << 8) \
)

#define GET_Control_FreigabeWZS1(buf) \
   CAN_TO_REAL_Control_FreigabeWZS1(GET_Control_FreigabeWZS1_Raw(buf))

#define CAN_TO_REAL_Control_Regelmodus(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_Regelmodus(x) (uint16_t)(((x) - 0) / 1)

#define SET_Control_Regelmodus_Raw(buf,val) {\
   buf[1] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_Regelmodus(buf,val) \
   SET_Control_Regelmodus_Raw(buf,REAL_TO_CAN_Control_Regelmodus(val))

#define GET_Control_Regelmodus_Raw(buf) (0\
   | ((( uint8_t)(buf[1] >> 0) & 0xff) << 0) \
)

#define GET_Control_Regelmodus(buf) \
   CAN_TO_REAL_Control_Regelmodus(GET_Control_Regelmodus_Raw(buf))

#define CAN_TO_REAL_Control_StartStop(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_Control_StartStop(x) (uint16_t)(((x) - 0) / 1)

#define SET_Control_StartStop_Raw(buf,val) {\
   buf[0] |= (uint8_t)((val) >> 0) << 0;\
}

#define SET_Control_StartStop(buf,val) \
   SET_Control_StartStop_Raw(buf,REAL_TO_CAN_Control_StartStop(val))

#define GET_Control_StartStop_Raw(buf) (0\
   | ((( uint8_t)(buf[0] >> 0) & 0xff) << 0) \
)

#define GET_Control_StartStop(buf) \
   CAN_TO_REAL_Control_StartStop(GET_Control_StartStop_Raw(buf))

#define ID_GenApp_Control_Message 0x8cff6492
#define DLC_GenApp_Control_Message  8

#define CAN_TO_REAL_GenApp_Control_Message_I_max_recharge(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_GenApp_Control_Message_I_max_recharge(x) (uint32_t)(((x) - 0) / 1)

#define SET_GenApp_Control_Message_I_max_recharge_Raw(buf,val) {\
   buf[7] |= (uint8_t)((val) >> 0) << 0;\
   buf[6] |= (uint8_t)((val) >> 8) << 0;\
}

#define SET_GenApp_Control_Message_I_max_recharge(buf,val) \
   SET_GenApp_Control_Message_I_max_recharge_Raw(buf,REAL_TO_CAN_GenApp_Control_Message_I_max_recharge(val))

#define GET_GenApp_Control_Message_I_max_recharge_Raw(buf) (0\
   | ((( uint8_t)(buf[7] >> 0) & 0xff) << 0) \
   | (((uint16_t)(buf[6] >> 0) & 0xff) << 8) \
)

#define GET_GenApp_Control_Message_I_max_recharge(buf) \
   CAN_TO_REAL_GenApp_Control_Message_I_max_recharge(GET_GenApp_Control_Message_I_max_recharge_Raw(buf))

#define CAN_TO_REAL_GenApp_Control_Message_I_max_discharge(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_GenApp_Control_Message_I_max_discharge(x) (uint32_t)(((x) - 0) / 1)

#define SET_GenApp_Control_Message_I_max_discharge_Raw(buf,val) {\
   buf[5] |= (uint8_t)((val) >> 0) << 0;\
   buf[4] |= (uint8_t)((val) >> 8) << 0;\
}

#define SET_GenApp_Control_Message_I_max_discharge(buf,val) \
   SET_GenApp_Control_Message_I_max_discharge_Raw(buf,REAL_TO_CAN_GenApp_Control_Message_I_max_discharge(val))

#define GET_GenApp_Control_Message_I_max_discharge_Raw(buf) (0\
   | ((( uint8_t)(buf[5] >> 0) & 0xff) << 0) \
   | (((uint16_t)(buf[4] >> 0) & 0xff) << 8) \
)

#define GET_GenApp_Control_Message_I_max_discharge(buf) \
   CAN_TO_REAL_GenApp_Control_Message_I_max_discharge(GET_GenApp_Control_Message_I_max_discharge_Raw(buf))

#define CAN_TO_REAL_GenApp_Control_Message_V_target(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_GenApp_Control_Message_V_target(x) (uint32_t)(((x) - 0) / 1)

#define SET_GenApp_Control_Message_V_target_Raw(buf,val) {\
   buf[3] |= (uint8_t)((val) >> 0) << 0;\
   buf[2] |= (uint8_t)((val) >> 8) << 0;\
}

#define SET_GenApp_Control_Message_V_target(buf,val) \
   SET_GenApp_Control_Message_V_target_Raw(buf,REAL_TO_CAN_GenApp_Control_Message_V_target(val))

#define GET_GenApp_Control_Message_V_target_Raw(buf) (0\
   | ((( uint8_t)(buf[3] >> 0) & 0xff) << 0) \
   | (((uint16_t)(buf[2] >> 0) & 0xff) << 8) \
)

#define GET_GenApp_Control_Message_V_target(buf) \
   CAN_TO_REAL_GenApp_Control_Message_V_target(GET_GenApp_Control_Message_V_target_Raw(buf))

#define CAN_TO_REAL_GenApp_Control_Message_Enable(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_GenApp_Control_Message_Enable(x) ( uint8_t)(((x) - 0) / 1)

#define SET_GenApp_Control_Message_Enable_Raw(buf,val) {\
   buf[1] |= (uint8_t)((val) >> 0) << 1;\
}

#define SET_GenApp_Control_Message_Enable(buf,val) \
   SET_GenApp_Control_Message_Enable_Raw(buf,REAL_TO_CAN_GenApp_Control_Message_Enable(val))

#define GET_GenApp_Control_Message_Enable_Raw(buf) (0\
   | ((( uint8_t)(buf[1] >> 1) & 0x7f) << 0) \
)

#define GET_GenApp_Control_Message_Enable(buf) \
   CAN_TO_REAL_GenApp_Control_Message_Enable(GET_GenApp_Control_Message_Enable_Raw(buf))

#define CAN_TO_REAL_GenApp_Control_Message_E_Stop(x)           ( (x) * 1 + 0)
#define REAL_TO_CAN_GenApp_Control_Message_E_Stop(x) ( uint8_t)(((x) - 0) / 1)

#define SET_GenApp_Control_Message_E_Stop_Raw(buf,val) {\
   buf[0] |= (uint8_t)((val) >> 0) << 4;\
}

#define SET_GenApp_Control_Message_E_Stop(buf,val) \
   SET_GenApp_Control_Message_E_Stop_Raw(buf,REAL_TO_CAN_GenApp_Control_Message_E_Stop(val))

#define GET_GenApp_Control_Message_E_Stop_Raw(buf) (0\
   | ((( uint8_t)(buf[0] >> 4) & 0xf) << 0) \
)

#define GET_GenApp_Control_Message_E_Stop(buf) \
   CAN_TO_REAL_GenApp_Control_Message_E_Stop(GET_GenApp_Control_Message_E_Stop_Raw(buf))

