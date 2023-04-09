// IO_STATUS_BLOCK and printf
#include"phnt/phnt_windows.h"
#include"phnt/phnt.h"
#include <cstdio>
//https://github.com/n00bes/inline-syscall
#include "inline_syscall.hpp"
int main( ) {

    NTSTATUS Status;
    HANDLE hHandle;
    IO_STATUS_BLOCK IoBlock;

    Status = inline_syscall::init( );
    printf( "inline_syscall::init( ): %x\n", Status );

    hHandle = CreateFileA(
        "test.txt",
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_WRITE | FILE_SHARE_READ,
        NULL,
        CREATE_ALWAYS,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );
    
    BYTE* pog = new BYTE[ 512 ];
    memset( pog, 0x69, 512 );

    // 把stub拷贝过来直接调用
    Status = inline_syscall::invoke<NTSTATUS>(
        "NtWriteFile",
        hHandle,
        0,
        0,
        0,
        &IoBlock,
        pog,
        512,
        0,
        0
        );
    printf( "inline_syscall::invoke( ): %x\n", Status );

    CloseHandle( hHandle );

    inline_syscall::unload( );
}