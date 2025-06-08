
module audiosystem (
	anterior_sw_export,
	audio_ADCDAT,
	audio_ADCLRCK,
	audio_BCLK,
	audio_DACDAT,
	audio_DACLRCK,
	audio_clk_clk,
	audioconfig_SDAT,
	audioconfig_SCLK,
	clk_clk,
	filt1_sw_export,
	filt2_sw_export,
	min1_export,
	min2_export,
	pausa_sw_export,
	reset_reset_n,
	seg1_export,
	seg2_export,
	siguiente_sw_export);	

	input		anterior_sw_export;
	input		audio_ADCDAT;
	input		audio_ADCLRCK;
	input		audio_BCLK;
	output		audio_DACDAT;
	input		audio_DACLRCK;
	output		audio_clk_clk;
	inout		audioconfig_SDAT;
	output		audioconfig_SCLK;
	input		clk_clk;
	input		filt1_sw_export;
	input		filt2_sw_export;
	output	[6:0]	min1_export;
	output	[6:0]	min2_export;
	input		pausa_sw_export;
	input		reset_reset_n;
	output	[6:0]	seg1_export;
	output	[6:0]	seg2_export;
	input		siguiente_sw_export;
endmodule
