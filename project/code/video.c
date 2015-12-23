
#include "config.h"


int video(void)
{
	open_device();

	if (fd == -1) {
	 	
		printf("App->Error: open video device error!\n");
		return -1;
	} 

	init_device();
	start_capturing();

	return 1;

}

void unvideo(void)
{
	if (fd == -1)
	{
		return;
	}

    stop_capturing();
    uninit_device();
    close_device();

    return;
}

