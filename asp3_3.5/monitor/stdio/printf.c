/*
 *  TOPPERS/JSP Kernel
 *      Toyohashi Open Platform for Embedded Real-Time Systems/
 *      Just Standard Profile Kernel
 * 
 *  Copyright (C) 2000-2003 by Embedded and Real-Time Systems Laboratory
 *                              Toyohashi Univ. of Technology, JAPAN
 *  Copyright (C) 2003-2005 by Ryosuke Takeuchi
  *                     GJ Business Division RICOH COMPANY,LTD. JAPAN
 * 
 *  上記著作権者は，以下の (1)〜(4) の条件か，Free Software Foundation 
 *  によって公表されている GNU General Public License の Version 2 に記
 *  述されている条件を満たす場合に限り，本ソフトウェア（本ソフトウェア
 *  を改変したものを含む．以下同じ）を使用・複製・改変・再配布（以下，
 *  利用と呼ぶ）することを無償で許諾する．
 *  (1) 本ソフトウェアをソースコードの形で利用する場合には，上記の著作
 *      権表示，この利用条件および下記の無保証規定が，そのままの形でソー
 *      スコード中に含まれていること．
 *  (2) 本ソフトウェアを，ライブラリ形式など，他のソフトウェア開発に使
 *      用できる形で再配布する場合には，再配布に伴うドキュメント（利用
 *      者マニュアルなど）に，上記の著作権表示，この利用条件および下記
 *      の無保証規定を掲載すること．
 *  (3) 本ソフトウェアを，機器に組み込むなど，他のソフトウェア開発に使
 *      用できない形で再配布する場合には，次のいずれかの条件を満たすこ
 *      と．
 *    (a) 再配布に伴うドキュメント（利用者マニュアルなど）に，上記の著
 *        作権表示，この利用条件および下記の無保証規定を掲載すること．
 *    (b) 再配布の形態を，別に定める方法によって，TOPPERSプロジェクトに
 *        報告すること．
 *  (4) 本ソフトウェアの利用により直接的または間接的に生じるいかなる損
 *      害からも，上記著作権者およびTOPPERSプロジェクトを免責すること．
 * 
 *  本ソフトウェアは，無保証で提供されているものである．上記著作権者お
 *  よびTOPPERSプロジェクトは，本ソフトウェアに関して，その適用可能性も
 *  含めて，いかなる保証も行わない．また，本ソフトウェアの利用により直
 *  接的または間接的に生じたいかなる損害に関しても，その責任を負わない．
 * 
 *  @(#) $Id: printf.c,v 1.6 2008/03/16 09:01:38 roi Exp $
 */

/*
 *	printf代用プログラム
 */

#include <itron.h>
#include <stdarg.h>
#include <stdio.h>

/*
 *  数値を文字列に変換
 */
static int
convert(unsigned long val, int radix, const char *radchar, int width, int minus, int padzero,
        void (*putsub)(char c, char **p), char ** putbuf)
{
	char	buf[12];
	int	i, j;
	int count = 0;

	i = 0;
	do {
		buf[i++] = radchar[val % radix];
		val /= radix;
	} while (val != 0);

	width -= minus;
	if (minus > 0 && padzero > 0) {
		putsub('-', putbuf);
		count++;
	}
	for (j = i; j < width; j++) {
		putsub((char)(padzero > 0 ? '0' : ' '), putbuf);
		count++;
	}
	if (minus > 0 && padzero <= 0) {
		putsub('-', putbuf);
		count++;
	}
	while (i > 0) {
		putsub(buf[--i], putbuf);
		count++;
	}
	return count;
}

/*
 *  ログ情報フォーマット用ライブラリ関数
 */
static char const raddec[] = "0123456789";
static char const radhex[] = "0123456789abcdef";
static char const radHEX[] = "0123456789ABCDEF";

int _setformat (void (*putsub)(char c, char **p), char ** putbuf, const char * format, va_list ap)
{
	int	c;
	int count = 0;
	int	width;
	int	padzero;
	long	val;
	char const	*str;

	while ((c = *format++) != '\0') {
		if (c != '%') {
			putsub((char) c, putbuf);
			count++;
			continue;
		}

		width = padzero = 0;
		if ((c = *format++) == '0') {
			padzero = 1;
			c = *format++;
		}
		while ('0' <= c && c <= '9') {
			width = width*10 + c - '0';
			c = *format++;
		}
		switch (c) {
		case 'l':						/* long */
			c = *format++;
			switch (c) {
			case 'd':					/* long 10進整数 */
			case 'i':					/* long 8,10,16進整数 */
				val = (long) va_arg(ap, long);
				if (val >= 0)
					count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				else
					count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
				break;
			case 'u':					/* unsigned long 10進整数 */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'o':					/* unsigned long 8進整数 */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'x':					/* unsigned long 16進整数 */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
				break;
			case 'X':					/* unsigned long 大文字16進整数 */
				val = (long) va_arg(ap, unsigned long);
				count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
				break;
			case '\0':
				format--;
				break;
			}
			break;

		case 'h':						/* short */
			c = *format++;
			switch (c) {
			case 'd':					/* short 8進整数 */
			case 'i':					/* short 8,10,16進整数 */
				val = (long) ((short)va_arg(ap, int));
				if (val >= 0)
					count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				else
					count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
				break;
			case 'u':					/* unsigned short 10進整数 */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'o':					/* unsigned short 8進整数 */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
				break;
			case 'x':					/* unsigned short 16進整数 */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
				break;
			case 'X':					/* unsigned short 大文字16進整数 */
				val = (long) ((unsigned short)va_arg(ap, unsigned int));
				count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
				break;
			case '\0':
				format--;
				break;
			}
			break;
		case 'd':						/* int 10進整数 */
		case 'i':						/* int 8,10,16進整数 */
			val = (long) va_arg(ap, int);
			if (val >= 0)
				count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
			else
				count += convert(-val, 10, raddec, width, 1, padzero, putsub, putbuf);
			break;
		case 'u':						/* unsigned int 10進整数 */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 10, raddec, width, 0, padzero, putsub, putbuf);
			break;
		case 'o':						/* unsigned int 8進整数 */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 8, raddec, width, 0, padzero, putsub, putbuf);
			break;
		case 'x':						/* unsigned int 16進整数 */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 16, radhex, width, 0, padzero, putsub, putbuf);
			break;
		case 'X':						/* unsigned int 大文字16進整数 */
			val = (long) va_arg(ap, unsigned int);
			count += convert(val, 16, radHEX, width, 0, padzero, putsub, putbuf);
			break;

		case 'c':						/* 1バイト文字 */
			c = (int) va_arg(ap, unsigned int);
			putsub((char)(int)c, putbuf);
			count++;
			break;
		case 's':						/* 文字列 */
			str = (char const *) va_arg(ap, VP_INT);
			while ((c = *str++) != '\0') {
				putsub((char) c, putbuf);
				count++;
				width--;
			}
			while(width > 0){
				putsub(' ', putbuf);
				count++;
				width--;
			}
			break;
		case '%':
			putsub('%', putbuf);
			count++;
			break;
		case '\0':
			format--;
			break;
		}
	}
	return count;
}

static void putzi (char c, char ** p)
{
    putchar(c);
}

int printf (const char * format, ...)
{
    va_list args;
    va_start(args, format);
    return (_setformat(putzi, NULL, format, args));
}

