/* Obter os nomes das disciplinas de quatro créditos, que, em 2002, foram ministradas por um professor do departamento 'Informática'.
Resolver com: */

/* 1. Produto cartesiano na cláusula FROM (lista de tabelas separadas por vírgula) */
/*
select distinct disciplina.nomedisc from disciplina, depto, profturma, professor
where 	disciplina.creditosdisc = 4
	AND professor.codprof = profturma.codprof
	AND disciplina.numdisc = profturma.numdisc
	AND (profturma.anosem = 20021 OR profturma.anosem = 20022)
	AND disciplina.coddepto = profturma.coddepto
	AND professor.coddepto = depto.coddepto
	AND depto.nomedepto = 'Informática'
*/

/* 2. Sintaxe explícita para junções */
select distinct disciplina.nomedisc 
from 	depto
		natural join
	professor
		natural join
	profturma
		natural join
	disciplina
where	disciplina.creditosdisc = 4
	AND (profturma.anosem = 20021 OR profturma.anosem = 20022)
	AND depto.nomedepto = 'Informática'


/* 3. Consulta estilo cálculo relacional, isto é, com EXISTS ou IN. */