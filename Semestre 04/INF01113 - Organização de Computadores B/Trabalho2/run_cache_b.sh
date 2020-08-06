#!/bin/sh

# b) Investigar a influência da variação do tamanho do bloco no desempenho da cache

# <nº conj.> 1024, <tam bloc> 1, <assoc.> 1, <política> LRU
#simplesim-3.0/./sim-cache -redir:sim logs/b_1024_1_1_l.txt -cache:il1 il1:1024:1:1:l -cache:il2 none -cache:dl1 dl1:1024:1:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 512, <tam bloc> 2, <assoc.> 1, <política> LRU
#simplesim-3.0/./sim-cache -redir:sim logs/b_512_2_1_l.txt -cache:il1 il1:512:2:1:l -cache:il2 none -cache:dl1 dl1:512:2:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 256, <tam bloc> 4, <assoc.> 1, <política> LRU
#simplesim-3.0/./sim-cache -redir:sim logs/b_256_4_1_l.txt -cache:il1 il1:256:4:1:l -cache:il2 none -cache:dl1 dl1:256:4:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 128, <tam bloc> 8, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_128_8_1_l.txt -cache:il1 il1:128:8:1:l -cache:il2 none -cache:dl1 dl1:128:8:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 64, <tam bloc> 16, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_64_16_1_l.txt -cache:il1 il1:64:16:1:l -cache:il2 none -cache:dl1 dl1:64:16:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 32, <tam bloc> 32, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_32_32_1_l.txt -cache:il1 il1:32:32:1:l -cache:il2 none -cache:dl1 dl1:32:32:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 16, <tam bloc> 64, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_16_64_1_l.txt -cache:il1 il1:16:64:1:l -cache:il2 none -cache:dl1 dl1:16:64:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 8, <tam bloc> 128, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_8_128_1_l.txt -cache:il1 il1:8:128:1:l -cache:il2 none -cache:dl1 dl1:8:128:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 4, <tam bloc> 256, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_4_256_1_l.txt -cache:il1 il1:4:256:1:l -cache:il2 none -cache:dl1 dl1:4:256:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 2, <tam bloc> 512, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_2_512_1_l.txt -cache:il1 il1:2:512:1:l -cache:il2 none -cache:dl1 dl1:2:512:1:l simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 1, <tam bloc> 1024, <assoc.> 1, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/b_1_1024_1_l.txt -cache:il1 il1:1:1024:1:l -cache:il2 none -cache:dl1 dl1:1:1024:1:l simplesim-3.0/benchmarks/crc.ss
