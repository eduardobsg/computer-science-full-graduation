#!/bin/sh

# a) Investigar a influência do tipo de mapeamento empregado (direto, associativo por conjunto e totalmente associativo) e da política de reposição no desempenho da cache

# <nº conj.> 32, <tam bloc> 32, <assoc.> 1
simplesim-3.0/./sim-cache -redir:sim logs/a_32_32_1_l.txt -cache:il1 il1:32:32:1:l -cache:il2 none -cache:dl1 dl1:32:32:1:l simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_32_32_1_r.txt -cache:il1 il1:32:32:1:r -cache:il2 none -cache:dl1 dl1:32:32:1:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_32_32_1_f.txt -cache:il1 il1:32:32:1:f -cache:il2 none -cache:dl1 dl1:32:32:1:f simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 16, <tam bloc> 32, <assoc.> 2
simplesim-3.0/./sim-cache -redir:sim logs/a_16_32_2_l.txt -cache:il1 il1:16:32:2:l -cache:il2 none -cache:dl1 dl1:16:32:2:l simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_16_32_2_r.txt -cache:il1 il1:16:32:2:r -cache:il2 none -cache:dl1 dl1:16:32:2:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_16_32_2_f.txt -cache:il1 il1:16:32:2:f -cache:il2 none -cache:dl1 dl1:16:32:2:f simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 8, <tam bloc> 32, <assoc.> 4
simplesim-3.0/./sim-cache -redir:sim logs/a_8_32_4_l.txt -cache:il1 il1:8:32:4:l -cache:il2 none -cache:dl1 dl1:8:32:4:l simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_8_32_4_r.txt -cache:il1 il1:8:32:4:r -cache:il2 none -cache:dl1 dl1:8:32:4:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_8_32_4_f.txt -cache:il1 il1:8:32:4:f -cache:il2 none -cache:dl1 dl1:8:32:4:f simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 4, <tam bloc> 32, <assoc.> 8
simplesim-3.0/./sim-cache -redir:sim logs/a_4_32_8_l.txt -cache:il1 il1:4:32:8:l -cache:il2 none -cache:dl1 dl1:4:32:8:l simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_4_32_8_r.txt -cache:il1 il1:4:32:8:r -cache:il2 none -cache:dl1 dl1:4:32:8:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_4_32_8_f.txt -cache:il1 il1:4:32:8:f -cache:il2 none -cache:dl1 dl1:4:32:8:f simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 2, <tam bloc> 32, <assoc.> 16
simplesim-3.0/./sim-cache -redir:sim logs/a_2_32_16_l.txt -cache:il1 il1:2:32:16:l -cache:il2 none -cache:dl1 dl1:2:32:16:l simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_2_32_16_r.txt -cache:il1 il1:2:32:16:r -cache:il2 none -cache:dl1 dl1:2:32:16:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_2_32_16_f.txt -cache:il1 il1:2:32:16:f -cache:il2 none -cache:dl1 dl1:2:32:16:f simplesim-3.0/benchmarks/crc.ss

# <nº conj.> 1, <tam bloc> 32, <assoc.> 32
simplesim-3.0/./sim-cache -redir:sim logs/a_1_32_32_l.txt -cache:il1 il1:1:32:32:l -cache:il2 none -cache:dl1 dl1:1:32:32:l simplesim-3.0/benchmarks/crc.ss 
simplesim-3.0/./sim-cache -redir:sim logs/a_1_32_32_r.txt -cache:il1 il1:1:32:32:r -cache:il2 none -cache:dl1 dl1:1:32:32:r simplesim-3.0/benchmarks/crc.ss
simplesim-3.0/./sim-cache -redir:sim logs/a_1_32_32_f.txt -cache:il1 il1:1:32:32:f -cache:il2 none -cache:dl1 dl1:1:32:32:f simplesim-3.0/benchmarks/crc.ss
