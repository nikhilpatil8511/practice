
#ifndef T_DEVICE_INIT_H
#define T_DEVICE_INIT_H

#define RET_RAM_BEG   0xFEE00000
#define RET_RAM_END   0xFEE07FFF

#define protected_write(preg,pstatus,reg,value)   do{\
                                                  (preg)=0xa5u;\
                                                  (reg)=(value);\
                                                  (reg)=~(value);\
                                                  (reg)=(value);\
                                                  }while((pstatus)==1u)

#endif