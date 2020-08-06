LIBRARY IEEE;
USE IEEE.STD_LOGIC_1164.ALL;

ENTITY display IS
	PORT (	A		: IN STD_LOGIC;
			B		: IN STD_LOGIC;
			C		: IN STD_LOGIC;
			D		: IN STD_LOGIC;
			S_A		: OUT STD_LOGIC;
			S_B		: OUT STD_LOGIC;
			S_C		: OUT STD_LOGIC;
			S_D		: OUT STD_LOGIC;
			S_E		: OUT STD_LOGIC;
			S_F		: OUT STD_LOGIC;
			S_G		: OUT STD_LOGIC;
			S_Dp	: OUT STD_LOGIC);
END display;

ARCHITECTURE data_flow OF display IS
BEGIN
	S_A <= ((NOT B) AND (NOT D))	OR ((NOT A) AND C)						OR ((NOT A) AND B AND D)		OR (A AND (NOT B) AND (NOT C))	OR (A AND (NOT D))			OR (B AND C);
	S_B <= ((NOT A) AND (NOT B))	OR ((NOT A) AND (NOT C) AND (NOT D))	OR ((NOT A) AND C AND D)		OR ((NOT B) AND (NOT C))		OR (A AND (NOT C) AND D);
	S_C <= ((NOT A) AND  B)			OR (A AND (NOT B))						OR ((NOT C) AND D)				OR ((NOT A) AND (NOT C))		OR ((NOT A) AND D);
	S_D <= ((NOT B) AND (NOT D))	OR ((NOT B) AND C)						OR (B AND (NOT C) AND D)		OR (C AND (NOT D))				OR (A AND (NOT C));
	S_E <= ((NOT B) AND (NOT D))	OR (C AND (NOT D))						OR (A AND C)					OR (A AND B);
	S_F <= ((NOT C) AND (NOT D))	OR ((NOT A) AND B AND (NOT C))			OR (B AND (NOT D))				OR (A AND (NOT B))				OR (A AND C);
	S_G <= ((NOT B) AND C)			OR (A OR (NOT B))						OR ((NOT A) AND B AND (NOT C))	OR (C AND (NOT D))				OR (A AND D);
	S_Dp <= '1';

END data_flow;
