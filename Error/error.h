#ifndef __ERROR_H__
#define __ERROR_H__

enum MERROR
{
	SUCCESS = 0,
	// ��д bug
	READ_FAILED,
	SAVE_FAILED,

	// �ļ�����·��bug
	FILE_EXTENISON_ILLEGALITY,

	// ͼ��ƥ��bug
	IMAGE_NO_COMPARE,
	IMAGE_FORMAT_NOMATCH,

	// �ն���bug
	CMATRIX_EMPTY,

	// ����bug
	ERROR_ARG,

	// ͼ��ȡ��bug
	GET_IMAGE_BLOCK_FAILED

};

#endif // !__ERROR_H__
