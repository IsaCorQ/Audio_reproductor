	component audiosystem is
		port (
			anterior_sw_export   : in    std_logic                     := 'X';             -- export
			audio_ADCDAT         : in    std_logic                     := 'X';             -- ADCDAT
			audio_ADCLRCK        : in    std_logic                     := 'X';             -- ADCLRCK
			audio_BCLK           : in    std_logic                     := 'X';             -- BCLK
			audio_DACDAT         : out   std_logic;                                        -- DACDAT
			audio_DACLRCK        : in    std_logic                     := 'X';             -- DACLRCK
			audio_clk_clk        : out   std_logic;                                        -- clk
			audioconfig_SDAT     : inout std_logic                     := 'X';             -- SDAT
			audioconfig_SCLK     : out   std_logic;                                        -- SCLK
			clk_clk              : in    std_logic                     := 'X';             -- clk
			filt1_sw_export      : in    std_logic                     := 'X';             -- export
			filt2_sw_export      : in    std_logic                     := 'X';             -- export
			memory_mem_a         : out   std_logic_vector(12 downto 0);                    -- mem_a
			memory_mem_ba        : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck        : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n      : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke       : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n      : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n     : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n     : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n      : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n   : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq        : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- mem_dq
			memory_mem_dqs       : inout std_logic                     := 'X';             -- mem_dqs
			memory_mem_dqs_n     : inout std_logic                     := 'X';             -- mem_dqs_n
			memory_mem_odt       : out   std_logic;                                        -- mem_odt
			memory_mem_dm        : out   std_logic;                                        -- mem_dm
			memory_oct_rzqin     : in    std_logic                     := 'X';             -- oct_rzqin
			min1_export          : out   std_logic_vector(6 downto 0);                     -- export
			min2_export          : out   std_logic_vector(6 downto 0);                     -- export
			pausa_sw_export      : in    std_logic                     := 'X';             -- export
			reset_reset_n        : in    std_logic                     := 'X';             -- reset_n
			seg1_export          : out   std_logic_vector(6 downto 0);                     -- export
			seg2_export          : out   std_logic_vector(6 downto 0);                     -- export
			siguiente_sw_export  : in    std_logic                     := 'X';             -- export
			vga_controller_CLK   : out   std_logic;                                        -- CLK
			vga_controller_HS    : out   std_logic;                                        -- HS
			vga_controller_VS    : out   std_logic;                                        -- VS
			vga_controller_BLANK : out   std_logic;                                        -- BLANK
			vga_controller_SYNC  : out   std_logic;                                        -- SYNC
			vga_controller_R     : out   std_logic_vector(7 downto 0);                     -- R
			vga_controller_G     : out   std_logic_vector(7 downto 0);                     -- G
			vga_controller_B     : out   std_logic_vector(7 downto 0)                      -- B
		);
	end component audiosystem;

	u0 : component audiosystem
		port map (
			anterior_sw_export   => CONNECTED_TO_anterior_sw_export,   --    anterior_sw.export
			audio_ADCDAT         => CONNECTED_TO_audio_ADCDAT,         --          audio.ADCDAT
			audio_ADCLRCK        => CONNECTED_TO_audio_ADCLRCK,        --               .ADCLRCK
			audio_BCLK           => CONNECTED_TO_audio_BCLK,           --               .BCLK
			audio_DACDAT         => CONNECTED_TO_audio_DACDAT,         --               .DACDAT
			audio_DACLRCK        => CONNECTED_TO_audio_DACLRCK,        --               .DACLRCK
			audio_clk_clk        => CONNECTED_TO_audio_clk_clk,        --      audio_clk.clk
			audioconfig_SDAT     => CONNECTED_TO_audioconfig_SDAT,     --    audioconfig.SDAT
			audioconfig_SCLK     => CONNECTED_TO_audioconfig_SCLK,     --               .SCLK
			clk_clk              => CONNECTED_TO_clk_clk,              --            clk.clk
			filt1_sw_export      => CONNECTED_TO_filt1_sw_export,      --       filt1_sw.export
			filt2_sw_export      => CONNECTED_TO_filt2_sw_export,      --       filt2_sw.export
			memory_mem_a         => CONNECTED_TO_memory_mem_a,         --         memory.mem_a
			memory_mem_ba        => CONNECTED_TO_memory_mem_ba,        --               .mem_ba
			memory_mem_ck        => CONNECTED_TO_memory_mem_ck,        --               .mem_ck
			memory_mem_ck_n      => CONNECTED_TO_memory_mem_ck_n,      --               .mem_ck_n
			memory_mem_cke       => CONNECTED_TO_memory_mem_cke,       --               .mem_cke
			memory_mem_cs_n      => CONNECTED_TO_memory_mem_cs_n,      --               .mem_cs_n
			memory_mem_ras_n     => CONNECTED_TO_memory_mem_ras_n,     --               .mem_ras_n
			memory_mem_cas_n     => CONNECTED_TO_memory_mem_cas_n,     --               .mem_cas_n
			memory_mem_we_n      => CONNECTED_TO_memory_mem_we_n,      --               .mem_we_n
			memory_mem_reset_n   => CONNECTED_TO_memory_mem_reset_n,   --               .mem_reset_n
			memory_mem_dq        => CONNECTED_TO_memory_mem_dq,        --               .mem_dq
			memory_mem_dqs       => CONNECTED_TO_memory_mem_dqs,       --               .mem_dqs
			memory_mem_dqs_n     => CONNECTED_TO_memory_mem_dqs_n,     --               .mem_dqs_n
			memory_mem_odt       => CONNECTED_TO_memory_mem_odt,       --               .mem_odt
			memory_mem_dm        => CONNECTED_TO_memory_mem_dm,        --               .mem_dm
			memory_oct_rzqin     => CONNECTED_TO_memory_oct_rzqin,     --               .oct_rzqin
			min1_export          => CONNECTED_TO_min1_export,          --           min1.export
			min2_export          => CONNECTED_TO_min2_export,          --           min2.export
			pausa_sw_export      => CONNECTED_TO_pausa_sw_export,      --       pausa_sw.export
			reset_reset_n        => CONNECTED_TO_reset_reset_n,        --          reset.reset_n
			seg1_export          => CONNECTED_TO_seg1_export,          --           seg1.export
			seg2_export          => CONNECTED_TO_seg2_export,          --           seg2.export
			siguiente_sw_export  => CONNECTED_TO_siguiente_sw_export,  --   siguiente_sw.export
			vga_controller_CLK   => CONNECTED_TO_vga_controller_CLK,   -- vga_controller.CLK
			vga_controller_HS    => CONNECTED_TO_vga_controller_HS,    --               .HS
			vga_controller_VS    => CONNECTED_TO_vga_controller_VS,    --               .VS
			vga_controller_BLANK => CONNECTED_TO_vga_controller_BLANK, --               .BLANK
			vga_controller_SYNC  => CONNECTED_TO_vga_controller_SYNC,  --               .SYNC
			vga_controller_R     => CONNECTED_TO_vga_controller_R,     --               .R
			vga_controller_G     => CONNECTED_TO_vga_controller_G,     --               .G
			vga_controller_B     => CONNECTED_TO_vga_controller_B      --               .B
		);

