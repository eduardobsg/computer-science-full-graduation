#include "../include/libsisop.h"

int yield(void *arg) {
	printf("\nyield\n");
	mproc_yield();
	return 0;
}



int main (int argc, char *argv[]) {
	int i=5;
	libsisop_init();	
	
	int k=0;
	
	int p1 = mproc_create(yield,&i);
	int p2 = mproc_create(yield,&i);
	int p3 = mproc_create(yield,&i);
	int p4 = mproc_create(yield,&i);
	int p5 = mproc_create(yield,&i);
	int p6 = mproc_create(yield,&i);
	int p7 = mproc_create(yield,&i);
	int p8 = mproc_create(yield,&i);
	int p9 = mproc_create(yield,&i);
	int p10 = mproc_create(yield,&i);
	int p11 = mproc_create(yield,&i);
	int p12 = mproc_create(yield,&i);
	int p13 = mproc_create(yield,&i);
	int p14 = mproc_create(yield,&i);
	int p15 = mproc_create(yield,&i);
	int p16 = mproc_create(yield,&i);
	int p17 = mproc_create(yield,&i);
	int p18 = mproc_create(yield,&i);
	int p19 = mproc_create(yield,&i);
	int p20 = mproc_create(yield,&i);
	int p21 = mproc_create(yield,&i);
	int p22 = mproc_create(yield,&i);
	int p23 = mproc_create(yield,&i);
	int p24 = mproc_create(yield,&i);
	int p25 = mproc_create(yield,&i);
	int p26 = mproc_create(yield,&i);
	int p27 = mproc_create(yield,&i);
	int p28 = mproc_create(yield,&i);
	int p29 = mproc_create(yield,&i);
	int p30 = mproc_create(yield,&i);
	int p31 = mproc_create(yield,&i);
	int p32 = mproc_create(yield,&i);
	int p33 = mproc_create(yield,&i);
	int p34 = mproc_create(yield,&i);
	int p35 = mproc_create(yield,&i);
	int p36 = mproc_create(yield,&i);
	int p37 = mproc_create(yield,&i);
	int p38 = mproc_create(yield,&i);
	int p39 = mproc_create(yield,&i);
	int p40 = mproc_create(yield,&i);
	int p41 = mproc_create(yield,&i);
	int p42 = mproc_create(yield,&i);
	int p43 = mproc_create(yield,&i);
	int p44 = mproc_create(yield,&i);
	int p45 = mproc_create(yield,&i);
	int p46 = mproc_create(yield,&i);
	int p47 = mproc_create(yield,&i);
	int p48 = mproc_create(yield,&i);
	int p49 = mproc_create(yield,&i);
	int p50 = mproc_create(yield,&i);
	int p51 = mproc_create(yield,&i);
	int p52 = mproc_create(yield,&i);
	int p53 = mproc_create(yield,&i);
	int p54 = mproc_create(yield,&i);
	int p55 = mproc_create(yield,&i);
	int p56 = mproc_create(yield,&i);
	int p57 = mproc_create(yield,&i);
	int p58 = mproc_create(yield,&i);
	int p59 = mproc_create(yield,&i);
	int p60 = mproc_create(yield,&i);
	int p61 = mproc_create(yield,&i);
	int p62 = mproc_create(yield,&i);
	int p63 = mproc_create(yield,&i);
	int p64 = mproc_create(yield,&i);
	int p65 = mproc_create(yield,&i);
	int p66 = mproc_create(yield,&i);
	int p67 = mproc_create(yield,&i);
	int p68 = mproc_create(yield,&i);
	int p69 = mproc_create(yield,&i);
	int p70 = mproc_create(yield,&i);
	int p71 = mproc_create(yield,&i);
	int p72 = mproc_create(yield,&i);
	int p73 = mproc_create(yield,&i);
	int p74 = mproc_create(yield,&i);
	int p75 = mproc_create(yield,&i);
	int p76 = mproc_create(yield,&i);
	int p77 = mproc_create(yield,&i);
	int p78 = mproc_create(yield,&i);
	int p79 = mproc_create(yield,&i);
	int p80 = mproc_create(yield,&i);
	int p81 = mproc_create(yield,&i);
	int p82 = mproc_create(yield,&i);
	int p83 = mproc_create(yield,&i);
	int p84 = mproc_create(yield,&i);
	int p85 = mproc_create(yield,&i);
	int p86 = mproc_create(yield,&i);
	int p87 = mproc_create(yield,&i);
	int p88 = mproc_create(yield,&i);
	int p89 = mproc_create(yield,&i);
	int p90 = mproc_create(yield,&i);
	int p91 = mproc_create(yield,&i);
	int p92 = mproc_create(yield,&i);
	int p93 = mproc_create(yield,&i);
	int p94 = mproc_create(yield,&i);
	int p95 = mproc_create(yield,&i);
	int p96 = mproc_create(yield,&i);
	int p97 = mproc_create(yield,&i);
	int p98 = mproc_create(yield,&i);
	int p99 = mproc_create(yield,&i);
	int p100 = mproc_create(yield,&i);
	int p101 = mproc_create(yield,&i);
	int p102 = mproc_create(yield,&i);
	int p103 = mproc_create(yield,&i);
	int p104 = mproc_create(yield,&i);
	int p105 = mproc_create(yield,&i);
	int p106 = mproc_create(yield,&i);
	int p107 = mproc_create(yield,&i);
	int p108 = mproc_create(yield,&i);
	int p109 = mproc_create(yield,&i);
	int p110 = mproc_create(yield,&i);
	int p111 = mproc_create(yield,&i);
	int p112 = mproc_create(yield,&i);
	int p113 = mproc_create(yield,&i);
	int p114 = mproc_create(yield,&i);
	int p115 = mproc_create(yield,&i);
	int p116 = mproc_create(yield,&i);
	int p117 = mproc_create(yield,&i);
	int p118 = mproc_create(yield,&i);
	int p119 = mproc_create(yield,&i);
	int p120 = mproc_create(yield,&i);
	int p121 = mproc_create(yield,&i);
	int p122 = mproc_create(yield,&i);
	int p123 = mproc_create(yield,&i);
	int p124 = mproc_create(yield,&i);
	int p125 = mproc_create(yield,&i);
	int p126 = mproc_create(yield,&i);
	int p127 = mproc_create(yield,&i);


	mproc_yield();
	
	return 0;
}
