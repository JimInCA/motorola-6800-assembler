/*
 *	MC6800/02 specific processing
 */

#ifndef _DO0_H_
#define _DO0_H_

void localinit(void);
void do_op(int opcode /* base opcode */, int class /* mnemonic class */);
void do_gen(int op, int mode);
void do_indexed(int op);

#endif // _DO0_H_

