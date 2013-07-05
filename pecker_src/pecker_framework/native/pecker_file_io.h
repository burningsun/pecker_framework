/*
 * pecker_file_io.h
 *
 *  Created on: 2012-11-14
 *      Author: 李镇城  （ cut / cutxyz）
 *		e-mail: cut-12345@hotmail.com
 *              501931049@qq.com
 */

#ifndef PECKER_FILE_IO_H_
#define PECKER_FILE_IO_H_

#include "../pecker_reference.h"

PECKER_BEGIN

//file rw mode
// 0
#define PF_FILE_NO_EXISTS			0
//(1<<0)
#define PF_FILE_EXISTS					1
//(1<<1)
#define	PF_FILE_READ_ONLY			2
//(1<<2)
#define PF_FILE_WRITE_ONLY		4
//(1<<3)
#define PF_FILE_RW							8

//file open mode
#define PFO_OPEN_NONE				0
//(1<<0)
#define PFO_OPEN_EXISTS				1
//(1<<1)
#define PFO_OPEN_CREATE			2
//(1<<2)
#define PFO_OPEN_READ				4
//(1<<3)
#define PFO_OPEN_WRITE				8
//(1<<4)
#define PFO_OPEN_APPEND			16
//(1<<5)
#define PFO_OPEN_BINARY			32
//(1<<6)
#define PFO_OPEN_TEXT					64

#define PFO_OPEN_EX_BIT				7

//file open result
#define PRST_OK 								PEK_STATUS_OK
#define PRST_FAIL								PEK_STATUS_FAIL
#define PRST_OPENS						2
#define PRST_NOT_OPEN				3

typedef enum enumFILE_ORIGIN
{
	FILE_SEEK_SET  =  0,
	FILE_SEEK_CUR = 1,
	FILE_SEEK_END = 2
}FILE_ORIGIN;

// 文件操作类
class pecker_file_io_base
{
private:
	
public:
	static HResult set_install_apkfile_path(const Char* pstr_path,nSize path_length);
	static const const_string_chars& get_install_apkfile_path();
	static Handle get_private_apkfile_manager();
	static Boolean is_file_exists(const Char* pstr_path,nSize path_length);
	static HFlag get_file_rw_mode(const Char* pstr_path,nSize path_length);

protected:
	Handle _M_hFile;

public:
	pecker_file_io_base();
	virtual ~pecker_file_io_base();

	virtual HResult open(const Char* pstr_path,nSize path_length, HFlag nOpenType);
	virtual Bytes& read_to_memery(Bytes& memery_buffer,UInt origin = FILE_SEEK_SET,Long offset = 0);
	virtual nSize write_to_file(const const_bytes&  memery_buffer,UInt origin = FILE_SEEK_SET,Long offset = 0);
	virtual nSize get_file_size();
	virtual HResult close();

};
PECKER_END

#endif /* PECKER_FILE_IO_H_ */
