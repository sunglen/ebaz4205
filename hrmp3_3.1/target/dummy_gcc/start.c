/*
 *		ダミーターゲットのスタートアップモジュール
 *
 *  $Id: start.c 391 2019-07-10 06:14:58Z ertl-hiro $
 */

extern void	_kernel_initialize_sections(void);
extern void sta_ker(void);

int
main(void)
{
	_kernel_initialize_sections();
	sta_ker();
	return(0);
}
