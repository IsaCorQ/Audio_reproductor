
module audioplay (
	clk_clk,
	filtro1_sw_export,
	filtro2_sw_export,
	memory_mem_a,
	memory_mem_ba,
	memory_mem_ck,
	memory_mem_ck_n,
	memory_mem_cke,
	memory_mem_cs_n,
	memory_mem_ras_n,
	memory_mem_cas_n,
	memory_mem_we_n,
	memory_mem_reset_n,
	memory_mem_dq,
	memory_mem_dqs,
	memory_mem_dqs_n,
	memory_mem_odt,
	memory_mem_dm,
	memory_oct_rzqin,
	min1_export,
	min2_export,
	reset_reset_n,
	seg1_export,
	seg2_export,
	rst_export);	

	input		clk_clk;
	input		filtro1_sw_export;
	input		filtro2_sw_export;
	output	[12:0]	memory_mem_a;
	output	[2:0]	memory_mem_ba;
	output		memory_mem_ck;
	output		memory_mem_ck_n;
	output		memory_mem_cke;
	output		memory_mem_cs_n;
	output		memory_mem_ras_n;
	output		memory_mem_cas_n;
	output		memory_mem_we_n;
	output		memory_mem_reset_n;
	inout	[7:0]	memory_mem_dq;
	inout		memory_mem_dqs;
	inout		memory_mem_dqs_n;
	output		memory_mem_odt;
	output		memory_mem_dm;
	input		memory_oct_rzqin;
	output	[6:0]	min1_export;
	output	[6:0]	min2_export;
	input		reset_reset_n;
	output	[6:0]	seg1_export;
	output	[6:0]	seg2_export;
	input		rst_export;
endmodule
