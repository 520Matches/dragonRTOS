#ifndef __DRAGON_ERROR_H
#define __DRAGON_ERROR_H

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

// |----|----|----|----|----|
// |----|----|----|----|----|
// |----|----|----|----|----|
// |----|----|----|----|----|

#define E_OK	(0)

#define E_APP		(0x01000000)
#define E_KERNEL	(0x02000000)


#define E_DEVICE	(0x010000)
#define E_PROTOCOL	(0x020000)
#define E_STRUCT	(0x030000)

#define E_GPIO		(0x0100)
#define E_UART		(0x0200)
#define E_I2C		(0x0300)
#define E_SPI		(0x0400)
#define E_TIMER		(0x0500)
#define E_ADC		(0x0600)
#define E_WTD		(0x0700)
#define E_PWM		(0x0800)




#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif
