#ifndef __ERROR_H__
#define __ERROR_H__

enum MERROR
{
	SUCCESS = 0,
	// 读写 bug
	READ_FAILED,
	SAVE_FAILED,

	// 文件名和路径bug
	FILE_EXTENISON_ILLEGALITY,

	// 图像匹配bug
	IMAGE_NO_COMPARE,
	IMAGE_FORMAT_NOMATCH,

	// 空对象bug
	CMATRIX_EMPTY,

	// 参数bug
	ERROR_ARG,

	// 图像取块bug
	GET_IMAGE_BLOCK_FAILED

};

#endif // !__ERROR_H__
