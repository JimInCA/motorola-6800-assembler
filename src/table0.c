
#include "table.h"

struct oper table[] = {
"aba",  INH,    27,     2,
"adca", GEN,    137,    2,
"adcb", GEN,    201,    2,
"adda", GEN,    139,    2,
"addb", GEN,    203,    2,
"anda", GEN,    132,    2,
"andb", GEN,    196,    2,
"asl",  GRP2,   104,    6,
"asla", INH,    72,     2,
"aslb", INH,    88,     2,
"asr",  GRP2,   103,    6,
"asra", INH,    71,     2,
"asrb", INH,    87,     2,
"bcc",  REL,    36,     4,
"bcs",  REL,    37,     4,
"beq",  REL,    39,     4,
"bge",  REL,    44,     4,
"bgt",  REL,    46,     4,
"bhi",  REL,    34,     4,
"bhs",  REL,    36,     4,
"bita", GEN,    133,    2,
"bitb", GEN,    197,    2,
"ble",  REL,    47,     4,
"blo",  REL,    37,     4,
"bls",  REL,    35,     4,
"blt",  REL,    45,     4,
"bmi",  REL,    43,     4,
"bne",  REL,    38,     4,
"bpl",  REL,    42,     4,
"bra",  REL,    32,     4,
"bsr",  REL,    141,    8,
"bvc",  REL,    40,     4,
"bvs",  REL,    41,     4,
"cba",  INH,    17,     2,
"clc",  INH,    12,     2,
"cli",  INH,    14,     2,
"clr",  GRP2,   111,    6,
"clra", INH,    79,     2,
"clrb", INH,    95,     2,
"clv",  INH,    10,     2,
"cmpa", GEN,    129,    2,
"cmpb", GEN,    193,    2,
"com",  GRP2,   99,     6,
"coma", INH,    67,     2,
"comb", INH,    83,     2,
"cpx",  LONGIMM,140,    3,
"daa",  INH,    25,     2,
"dec",  GRP2,   106,    6,
"deca", INH,    74,     2,
"decb", INH,    90,     2,
"des",  INH,    52,     4,
"dex",  INH,    9,      4,
"eora", GEN,    136,    2,
"eorb", GEN,    200,    2,
"inc",  GRP2,   108,    6,
"inca", INH,    76,     2,
"incb", INH,    92,     2,
"ins",  INH,    49,     4,
"inx",  INH,    8,      4,
"jmp",  GRP2,   110,    3,
"jsr",  NOIMM,  0x8D,   7,
"ldaa", GEN,    134,    2,
"ldab", GEN,    198,    2,
"lds",  LONGIMM,142,    3,
"ldx",  LONGIMM,206,    3,
"lsl",  GRP2,   104,    6,
"lsla", INH,    72,     2,
"lslb", INH,    88,     2,
"lsr",  GRP2,   100,    6,
"lsra", INH,    68,     2,
"lsrb", INH,    84,     2,
"neg",  GRP2,   96,     6,
"nega", INH,    64,     2,
"negb", INH,    80,     2,
"nop",  INH,    1,      2,
"oraa", GEN,    138,    2,
"orab", GEN,    202,    2,
"psha", INH,    54,     4,
"pshb", INH,    55,     4,
"pula", INH,    50,     4,
"pulb", INH,    51,     4,
"rol",  GRP2,   105,    6,
"rola", INH,    73,     2,
"rolb", INH,    89,     2,
"ror",  GRP2,   102,    6,
"rora", INH,    70,     2,
"rorb", INH,    86,     2,
"rti",  INH,    59,     10,
"rts",  INH,    57,     5,
"sba",  INH,    16,     2,
"sbca", GEN,    130,    2,
"sbcb", GEN,    194,    2,
"sec",  INH,    13,     2,
"sei",  INH,    15,     2,
"sev",  INH,    11,     2,
"staa", NOIMM,  135,    3,
"stab", NOIMM,  199,    3,
"sts",  NOIMM,  143,    4,
"stx",  NOIMM,  207,    4,
"suba", GEN,    128,    2,
"subb", GEN,    192,    2,
"subd", LONGIMM,131,    3,
"swi",  INH,    63,     12,
"tab",  INH,    22,     2,
"tap",  INH,    6,      2,
"tba",  INH,    23,     2,
"tpa",  INH,    7,      2,
"tst",  GRP2,   109,    6,
"tsta", INH,    77,     2,
"tstb", INH,    93,     2,
"tsx",  INH,    48,     4,
"txs",  INH,    53,     4,
"wai",  INH,    62,     9
};

int sizeof_table(void)
{
	return sizeof(table);
}
