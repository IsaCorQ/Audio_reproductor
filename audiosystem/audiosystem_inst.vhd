	component audiosystem is
		port (
			clk_clk             : in    std_logic                    := 'X'; -- clk
			reset_reset_n       : in    std_logic                    := 'X'; -- reset_n
			audio_clk_clk       : out   std_logic;                           -- clk
			min2_export         : out   std_logic_vector(6 downto 0);        -- export
			min1_export         : out   std_logic_vector(6 downto 0);        -- export
			seg1_export         : out   std_logic_vector(6 downto 0);        -- export
			seg2_export         : out   std_logic_vector(6 downto 0);        -- export
			filt1_sw_export     : in    std_logic                    := 'X'; -- export
			filt2_sw_export     : in    std_logic                    := 'X'; -- export
			audioconfig_SDAT    : inout std_logic                    := 'X'; -- SDAT
			audioconfig_SCLK    : out   std_logic;                           -- SCLK
			audio_ADCDAT        : in    std_logic                    := 'X'; -- ADCDAT
			audio_ADCLRCK       : in    std_logic                    := 'X'; -- ADCLRCK
			audio_BCLK          : in    std_logic                    := 'X'; -- BCLK
			audio_DACDAT        : out   std_logic;                           -- DACDAT
			audio_DACLRCK       : in    std_logic                    := 'X'; -- DACLRCK
			pausa_sw_export     : in    std_logic                    := 'X'; -- export
			siguiente_sw_export : in    std_logic                    := 'X'; -- export
			anterior_sw_export  : in    std_logic                    := 'X'  -- export
		);
	end component audiosystem;

	u0 : component audiosystem
		port map (
			clk_clk             => CONNECTED_TO_clk_clk,             --          clk.clk
			reset_reset_n       => CONNECTED_TO_reset_reset_n,       --        reset.reset_n
			audio_clk_clk       => CONNECTED_TO_audio_clk_clk,       --    audio_clk.clk
			min2_export         => CONNECTED_TO_min2_export,         --         min2.export
			min1_export         => CONNECTED_TO_min1_export,         --         min1.export
			seg1_export         => CONNECTED_TO_seg1_export,         --         seg1.export
			seg2_export         => CONNECTED_TO_seg2_export,         --         seg2.export
			filt1_sw_export     => CONNECTED_TO_filt1_sw_export,     --     filt1_sw.export
			filt2_sw_export     => CONNECTED_TO_filt2_sw_export,     --     filt2_sw.export
			audioconfig_SDAT    => CONNECTED_TO_audioconfig_SDAT,    --  audioconfig.SDAT
			audioconfig_SCLK    => CONNECTED_TO_audioconfig_SCLK,    --             .SCLK
			audio_ADCDAT        => CONNECTED_TO_audio_ADCDAT,        --        audio.ADCDAT
			audio_ADCLRCK       => CONNECTED_TO_audio_ADCLRCK,       --             .ADCLRCK
			audio_BCLK          => CONNECTED_TO_audio_BCLK,          --             .BCLK
			audio_DACDAT        => CONNECTED_TO_audio_DACDAT,        --             .DACDAT
			audio_DACLRCK       => CONNECTED_TO_audio_DACLRCK,       --             .DACLRCK
			pausa_sw_export     => CONNECTED_TO_pausa_sw_export,     --     pausa_sw.export
			siguiente_sw_export => CONNECTED_TO_siguiente_sw_export, -- siguiente_sw.export
			anterior_sw_export  => CONNECTED_TO_anterior_sw_export   --  anterior_sw.export
		);

