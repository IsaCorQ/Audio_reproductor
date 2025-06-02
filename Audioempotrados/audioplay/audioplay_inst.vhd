	component audioplay is
		port (
			anterior_btn_export                              : in    std_logic                     := 'X';             -- export
			audio_0_external_interface_BCLK                  : in    std_logic                     := 'X';             -- BCLK
			audio_0_external_interface_DACDAT                : out   std_logic;                                        -- DACDAT
			audio_0_external_interface_DACLRCK               : in    std_logic                     := 'X';             -- DACLRCK
			audio_and_video_config_0_external_interface_SDAT : inout std_logic                     := 'X';             -- SDAT
			audio_and_video_config_0_external_interface_SCLK : out   std_logic;                                        -- SCLK
			clk_clk                                          : in    std_logic                     := 'X';             -- clk
			filtro1_sw_export                                : in    std_logic                     := 'X';             -- export
			filtro2_sw_export                                : in    std_logic                     := 'X';             -- export
			memory_mem_a                                     : out   std_logic_vector(12 downto 0);                    -- mem_a
			memory_mem_ba                                    : out   std_logic_vector(2 downto 0);                     -- mem_ba
			memory_mem_ck                                    : out   std_logic;                                        -- mem_ck
			memory_mem_ck_n                                  : out   std_logic;                                        -- mem_ck_n
			memory_mem_cke                                   : out   std_logic;                                        -- mem_cke
			memory_mem_cs_n                                  : out   std_logic;                                        -- mem_cs_n
			memory_mem_ras_n                                 : out   std_logic;                                        -- mem_ras_n
			memory_mem_cas_n                                 : out   std_logic;                                        -- mem_cas_n
			memory_mem_we_n                                  : out   std_logic;                                        -- mem_we_n
			memory_mem_reset_n                               : out   std_logic;                                        -- mem_reset_n
			memory_mem_dq                                    : inout std_logic_vector(7 downto 0)  := (others => 'X'); -- mem_dq
			memory_mem_dqs                                   : inout std_logic                     := 'X';             -- mem_dqs
			memory_mem_dqs_n                                 : inout std_logic                     := 'X';             -- mem_dqs_n
			memory_mem_odt                                   : out   std_logic;                                        -- mem_odt
			memory_mem_dm                                    : out   std_logic;                                        -- mem_dm
			memory_oct_rzqin                                 : in    std_logic                     := 'X';             -- oct_rzqin
			min1_export                                      : out   std_logic_vector(6 downto 0);                     -- export
			min2_export                                      : out   std_logic_vector(6 downto 0);                     -- export
			pausa_sw_export                                  : in    std_logic                     := 'X';             -- export
			reset_reset_n                                    : in    std_logic                     := 'X';             -- reset_n
			rst_export                                       : in    std_logic                     := 'X';             -- export
			seg1_export                                      : out   std_logic_vector(6 downto 0);                     -- export
			seg2_export                                      : out   std_logic_vector(6 downto 0);                     -- export
			siguiente_btn_export                             : in    std_logic                     := 'X';             -- export
			audio_pll_0_audio_clk_clk                        : out   std_logic                                         -- clk
		);
	end component audioplay;

	u0 : component audioplay
		port map (
			anterior_btn_export                              => CONNECTED_TO_anterior_btn_export,                              --                                anterior_btn.export
			audio_0_external_interface_BCLK                  => CONNECTED_TO_audio_0_external_interface_BCLK,                  --                  audio_0_external_interface.BCLK
			audio_0_external_interface_DACDAT                => CONNECTED_TO_audio_0_external_interface_DACDAT,                --                                            .DACDAT
			audio_0_external_interface_DACLRCK               => CONNECTED_TO_audio_0_external_interface_DACLRCK,               --                                            .DACLRCK
			audio_and_video_config_0_external_interface_SDAT => CONNECTED_TO_audio_and_video_config_0_external_interface_SDAT, -- audio_and_video_config_0_external_interface.SDAT
			audio_and_video_config_0_external_interface_SCLK => CONNECTED_TO_audio_and_video_config_0_external_interface_SCLK, --                                            .SCLK
			clk_clk                                          => CONNECTED_TO_clk_clk,                                          --                                         clk.clk
			filtro1_sw_export                                => CONNECTED_TO_filtro1_sw_export,                                --                                  filtro1_sw.export
			filtro2_sw_export                                => CONNECTED_TO_filtro2_sw_export,                                --                                  filtro2_sw.export
			memory_mem_a                                     => CONNECTED_TO_memory_mem_a,                                     --                                      memory.mem_a
			memory_mem_ba                                    => CONNECTED_TO_memory_mem_ba,                                    --                                            .mem_ba
			memory_mem_ck                                    => CONNECTED_TO_memory_mem_ck,                                    --                                            .mem_ck
			memory_mem_ck_n                                  => CONNECTED_TO_memory_mem_ck_n,                                  --                                            .mem_ck_n
			memory_mem_cke                                   => CONNECTED_TO_memory_mem_cke,                                   --                                            .mem_cke
			memory_mem_cs_n                                  => CONNECTED_TO_memory_mem_cs_n,                                  --                                            .mem_cs_n
			memory_mem_ras_n                                 => CONNECTED_TO_memory_mem_ras_n,                                 --                                            .mem_ras_n
			memory_mem_cas_n                                 => CONNECTED_TO_memory_mem_cas_n,                                 --                                            .mem_cas_n
			memory_mem_we_n                                  => CONNECTED_TO_memory_mem_we_n,                                  --                                            .mem_we_n
			memory_mem_reset_n                               => CONNECTED_TO_memory_mem_reset_n,                               --                                            .mem_reset_n
			memory_mem_dq                                    => CONNECTED_TO_memory_mem_dq,                                    --                                            .mem_dq
			memory_mem_dqs                                   => CONNECTED_TO_memory_mem_dqs,                                   --                                            .mem_dqs
			memory_mem_dqs_n                                 => CONNECTED_TO_memory_mem_dqs_n,                                 --                                            .mem_dqs_n
			memory_mem_odt                                   => CONNECTED_TO_memory_mem_odt,                                   --                                            .mem_odt
			memory_mem_dm                                    => CONNECTED_TO_memory_mem_dm,                                    --                                            .mem_dm
			memory_oct_rzqin                                 => CONNECTED_TO_memory_oct_rzqin,                                 --                                            .oct_rzqin
			min1_export                                      => CONNECTED_TO_min1_export,                                      --                                        min1.export
			min2_export                                      => CONNECTED_TO_min2_export,                                      --                                        min2.export
			pausa_sw_export                                  => CONNECTED_TO_pausa_sw_export,                                  --                                    pausa_sw.export
			reset_reset_n                                    => CONNECTED_TO_reset_reset_n,                                    --                                       reset.reset_n
			rst_export                                       => CONNECTED_TO_rst_export,                                       --                                         rst.export
			seg1_export                                      => CONNECTED_TO_seg1_export,                                      --                                        seg1.export
			seg2_export                                      => CONNECTED_TO_seg2_export,                                      --                                        seg2.export
			siguiente_btn_export                             => CONNECTED_TO_siguiente_btn_export,                             --                               siguiente_btn.export
			audio_pll_0_audio_clk_clk                        => CONNECTED_TO_audio_pll_0_audio_clk_clk                         --                       audio_pll_0_audio_clk.clk
		);

