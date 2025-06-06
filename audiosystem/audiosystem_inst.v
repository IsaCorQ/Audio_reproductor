	audiosystem u0 (
		.clk_clk             (<connected-to-clk_clk>),             //          clk.clk
		.reset_reset_n       (<connected-to-reset_reset_n>),       //        reset.reset_n
		.audio_clk_clk       (<connected-to-audio_clk_clk>),       //    audio_clk.clk
		.min2_export         (<connected-to-min2_export>),         //         min2.export
		.min1_export         (<connected-to-min1_export>),         //         min1.export
		.seg1_export         (<connected-to-seg1_export>),         //         seg1.export
		.seg2_export         (<connected-to-seg2_export>),         //         seg2.export
		.filt1_sw_export     (<connected-to-filt1_sw_export>),     //     filt1_sw.export
		.filt2_sw_export     (<connected-to-filt2_sw_export>),     //     filt2_sw.export
		.audioconfig_SDAT    (<connected-to-audioconfig_SDAT>),    //  audioconfig.SDAT
		.audioconfig_SCLK    (<connected-to-audioconfig_SCLK>),    //             .SCLK
		.audio_ADCDAT        (<connected-to-audio_ADCDAT>),        //        audio.ADCDAT
		.audio_ADCLRCK       (<connected-to-audio_ADCLRCK>),       //             .ADCLRCK
		.audio_BCLK          (<connected-to-audio_BCLK>),          //             .BCLK
		.audio_DACDAT        (<connected-to-audio_DACDAT>),        //             .DACDAT
		.audio_DACLRCK       (<connected-to-audio_DACLRCK>),       //             .DACLRCK
		.pausa_sw_export     (<connected-to-pausa_sw_export>),     //     pausa_sw.export
		.siguiente_sw_export (<connected-to-siguiente_sw_export>), // siguiente_sw.export
		.anterior_sw_export  (<connected-to-anterior_sw_export>)   //  anterior_sw.export
	);

