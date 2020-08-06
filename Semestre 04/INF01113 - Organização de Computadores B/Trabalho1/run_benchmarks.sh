#!/bin/sh

#Predição de desvio
#MM benchmark
simplesim-3.0/./sim-outorder -bpred nottaken 	-redir:sim logs/mm_nottaken.txt 	simplesim-3.0/benchmarks/mm.ss
simplesim-3.0/./sim-outorder -bpred bimod 		-redir:sim logs/mm_bimod.txt 		simplesim-3.0/benchmarks/mm.ss
simplesim-3.0/./sim-outorder -bpred perfect   	-redir:sim logs/mm_perfect.txt 		simplesim-3.0/benchmarks/mm.ss

#CRC benchmark
simplesim-3.0/./sim-outorder -bpred nottaken 	-redir:sim logs/crc_nottaken.txt 	simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-outorder -bpred bimod 		-redir:sim logs/crc_bimod.txt 		simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-outorder -bpred perfect 	-redir:sim logs/crc_perfect.txt 	simplesim-3.0/benchmarks/crc.ss

#GO benchmark
simplesim-3.0/./sim-outorder -bpred nottaken 	-redir:sim logs/go_nottaken.txt 	simplesim-3.0/benchmarks/go.ss 1 8 
simplesim-3.0/./sim-outorder -bpred bimod 		-redir:sim logs/go_bimod.txt 		simplesim-3.0/benchmarks/go.ss 1 8
simplesim-3.0/./sim-outorder -bpred perfect 	-redir:sim logs/go_perfect.txt 		simplesim-3.0/benchmarks/go.ss 1 8

#Superescalaridade
#MM benchmark
simplesim-3.0/./sim-outorder -res:ialu 1  -redir:sim logs/mm_alu1.txt	simplesim-3.0/benchmarks/mm.ss
simplesim-3.0/./sim-outorder -res:ialu 2  -redir:sim logs/mm_alu2.txt	simplesim-3.0/benchmarks/mm.ss
simplesim-3.0/./sim-outorder -res:ialu 4  -redir:sim logs/mm_alu4.txt	simplesim-3.0/benchmarks/mm.ss

#CRC benchmark
simplesim-3.0/./sim-outorder -res:ialu 1  -redir:sim logs/crc_alu1.txt 	simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-outorder -res:ialu 2  -redir:sim logs/crc_alu2.txt 	simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-outorder -res:ialu 4  -redir:sim logs/crc_alu4.txt 	simplesim-3.0/benchmarks/crc.ss

#GO benchmark
simplesim-3.0/./sim-outorder -res:ialu 1  -redir:sim logs/go_alu1.txt	simplesim-3.0/benchmarks/go.ss 1 8 
simplesim-3.0/./sim-outorder -res:ialu 2  -redir:sim logs/go_alu2.txt	simplesim-3.0/benchmarks/go.ss 1 8
simplesim-3.0/./sim-outorder -res:ialu 4  -redir:sim logs/go_alu4.txt	simplesim-3.0/benchmarks/go.ss 1 8

