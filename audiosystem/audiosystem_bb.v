
module audiosystem (
	clk_clk,
	reset_reset_n,
	audio_clk_clk,
	min2_export,
	min1_export,
	seg1_export,
	seg2_export,
	filt1_sw_export,
	filt2_sw_export,
	audioconfig_SDAT,
	audioconfig_SCLK,
	audio_ADCDAT,
	audio_ADCLRCK,
	audio_BCLK,
	audio_DACDAT,
	audio_DACLRCK,
	pausa_sw_export,
	siguiente_sw_export,
	anterior_sw_export);	

	input		clk_clk;
	input		reset_reset_n;
	output		audio_clk_clk;
	output	[6:0]	min2_export;
	output	[6:0]	min1_export;
	output	[6:0]	seg1_export;
	output	[6:0]	seg2_export;
	input		filt1_sw_export;
	input		filt2_sw_export;
	inout		audioconfig_SDAT;
	output		audioconfig_SCLK;
	input		audio_ADCDAT;
	input		audio_ADCLRCK;
	input		audio_BCLK;
	output		audio_DACDAT;
	input		audio_DACLRCK;
	input		pausa_sw_export;
	input		siguiente_sw_export;
	input		anterior_sw_export;
endmodule
