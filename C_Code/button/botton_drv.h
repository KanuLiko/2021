#ifndef _BUTTON_DRV_H_
#define _BUTTON_DRV_H_
struct button_operations{
	int count;
	void (*init) (int which);
	int （*read) (int which);
};
#endif
