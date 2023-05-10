// 递归下降扫描与线性扫描

/*objdump or windbg
Disassembly of section .text:

00401000 <.text>:
  401000:       50                      push   %eax
  401001:       eb 04                   jmp    0x401007
  401003:       6d                      insl   (%dx),%es:(%edi)
  401004:       73 67                   jae    0x40106d
  401006:       00 68 03                add    %ch,0x3(%eax)
  401009:       10 40 00                adc    %al,0x0(%eax)
  40100c:       cc                      int3
  40100d:       cc                      int3
  40100e:       cc                      int3
  40100f:       cc                      int3
*/

/*IDA 
.text:00401000 asm_code:                               ; CODE XREF: _main+5↓p
.text:00401000                                         ; DATA XREF: _main↓o
.text:00401000                 push    eax
.text:00401001                 jmp     short loc_401007
.text:00401001 ; ---------------------------------------------------------------------------
.text:00401003 unk_401003      db  6Dh ; m             ; DATA XREF: .text:loc_401007↓o
.text:00401004                 db  73h ; s
.text:00401005                 db  67h ; g
.text:00401006                 db    0
.text:00401007 ; ---------------------------------------------------------------------------
.text:00401007
.text:00401007 loc_401007:                             ; CODE XREF: .text:00401001↑j
.text:00401007                 push    offset unk_401003
.text:0040100C                 int     3               ; Trap to Debugger
.text:0040100D                 int     3               ; Trap to Debugger
.text:0040100E                 int     3               ; Trap to Debugger
.text:0040100F                 int     3               ; Trap to Debugger

*/


#include <iostream>

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char asm_code[] = {0x50,0xEB,0x04,0x6D,0x73,
0x67,0x00,0x68,0x03,0x10,0x40,00};

int main(int argc, char* argv[]) {
  // char*直接转函数指针不行,多做一层转换就可以了(先转void*)
  void* ptr = (void*)asm_code;
  using ftype = void (*)(void);
  ftype t = (ftype)ptr;
  t();
  return 0;
}
