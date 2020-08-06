ENTITY display2 IS
	PORT (	A		: IN BIT;
			B		: IN BIT;
			C		: IN BIT;
			D		: IN BIT;
			S_A		: OUT BIT;
			S_B		: OUT BIT;
			S_C		: OUT BIT;
			S_D		: OUT BIT;
			S_E		: OUT BIT;
			S_F		: OUT BIT;
			S_G		: OUT BIT;
			S_Dp	: OUT BIT);
END display2;

ARCHITECTURE data_flow OF display2 IS
BEGIN
	S_A <= ((NOT B) AND (NOT D))	OR ((NOT A) AND C)						OR ((NOT A) AND B AND D)		OR (A AND (NOT B) AND (NOT C))	OR (A AND (NOT D))			OR (B AND C);
	S_B <= ((NOT A) AND (NOT B))	OR ((NOT A) AND (NOT C) AND (NOT D))	OR ((NOT A) AND C AND D)		OR ((NOT B) AND (NOT C))		OR (A AND (NOT C) AND D);
	S_C <= ((NOT A) AND  B)			OR (A AND (NOT B))						OR ((NOT C) AND D)				OR ((NOT A) AND (NOT C))		OR ((NOT A) AND D);
	S_D <= ((NOT B) AND (NOT D))	OR ((NOT B) AND C)						OR (B AND (NOT C) AND D)		OR (C AND (NOT D))				OR (A AND (NOT C));
	S_E <= ((NOT B) AND (NOT D))	OR (C AND (NOT D))						OR (A AND C)					OR (A AND B);
	S_F <= ((NOT C) AND (NOT D))	OR ((NOT A) AND B AND (NOT C))			OR (B AND (NOT D))				OR (A AND (NOT B))				OR (A AND C);
	S_G <= ((C AND (NOT D))			OR (A AND (NOT B))						OR ((NOT A) AND B AND (NOT C))	OR (A AND D));
	S_Dp <= '1';
END data_flow;
