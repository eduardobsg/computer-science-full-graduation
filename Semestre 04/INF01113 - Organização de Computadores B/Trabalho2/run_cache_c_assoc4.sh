#!/bin/sh

# c) Investigar a influência do tamanho total da cache e do tamanho de bloco no desempenho da cache

# <tam cache> 1k, <nº conj.> 16, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_16_16_4_l.txt -cache:il1 il1:16:16:4:l -cache:il2 none -cache:dl1 dl1:16:16:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 2k, <nº conj.> 32, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_32_16_4_l.txt -cache:il1 il1:32:16:4:l -cache:il2 none -cache:dl1 dl1:32:16:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 4k, <nº conj.> 64, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_64_16_4_l.txt -cache:il1 il1:64:16:4:l -cache:il2 none -cache:dl1 dl1:64:16:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 8k, <nº conj.> 128, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_128_16_4_l.txt -cache:il1 il1:128:16:4:l -cache:il2 none -cache:dl1 dl1:128:16:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 16k, <nº conj.> 256, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_256_16_4_l.txt -cache:il1 il1:256:16:4:l -cache:il2 none -cache:dl1 dl1:256:16:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 32k, <nº conj.> 512, <tam bloc> 16, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_512_16_4_l.txt -cache:il1 il1:512:16:4:l -cache:il2 none -cache:dl1 dl1:512:16:4:l simplesim-3.0/benchmarks/crc.ss

####################################################################################

# <tam cache> 1k, <nº conj.> 8, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_8_32_4_l.txt -cache:il1 il1:8:32:4:l -cache:il2 none -cache:dl1 dl1:8:32:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 2k, <nº conj.> 16, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_16_32_4_l.txt -cache:il1 il1:16:32:4:l -cache:il2 none -cache:dl1 dl1:16:32:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 4k, <nº conj.> 32, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_32_32_4_l.txt -cache:il1 il1:32:32:4:l -cache:il2 none -cache:dl1 dl1:32:32:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 8k, <nº conj.> 64, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_64_32_4_l.txt -cache:il1 il1:64:32:4:l -cache:il2 none -cache:dl1 dl1:64:32:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 16k, <nº conj.> 128, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_128_32_4_l.txt -cache:il1 il1:128:32:4:l -cache:il2 none -cache:dl1 dl1:128:32:4:l simplesim-3.0/benchmarks/crc.ss

# <tam cache> 32k, <nº conj.> 256, <tam bloc> 32, <assoc.> 4, <política> LRU
simplesim-3.0/./sim-cache -redir:sim logs/c_256_32_4_l.txt -cache:il1 il1:256:32:4:l -cache:il2 none -cache:dl1 dl1:256:32:4:l simplesim-3.0/benchmarks/crc.ss

