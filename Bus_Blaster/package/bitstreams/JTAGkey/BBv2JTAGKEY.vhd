--------------------------------------------------------------------------------
-- Copyright (c) 1995-2010 Xilinx, Inc.  All rights reserved.
--------------------------------------------------------------------------------
--   ____  ____ 
--  /   /\/   / 
-- /___/  \  /    Vendor: Xilinx 
-- \   \   \/     Version : 12.1
--  \   \         Application : sch2hdl
--  /   /         Filename : BBv2JTAGKEY.vhf
-- /___/   /\     Timestamp : 12/28/2010 15:17:42
-- \   \  /  \ 
--  \___\/\___\ 
--
--Command: sch2hdl -intstyle ise -family acr2 -flat -suppress -vhdl E:/Work/dp-svn/trunk/BusBlasterv2/bitstreams/JTAGkey/BBv2JTAGKEY.vhf -w E:/Work/dp-svn/trunk/BusBlasterv2/bitstreams/JTAGkey/BBv2JTAGKEY.sch
--Design Name: BBv2JTAGKEY
--Device: acr2
--Purpose:
--    This vhdl netlist is translated from an ECS schematic. It can be 
--    synthesized and simulated, but it should not be modified. 
--

library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity OBUFT4_MXILINX_BBv2JTAGKEY is
   port ( I0 : in    std_logic; 
          I1 : in    std_logic; 
          I2 : in    std_logic; 
          I3 : in    std_logic; 
          T  : in    std_logic; 
          O0 : out   std_logic; 
          O1 : out   std_logic; 
          O2 : out   std_logic; 
          O3 : out   std_logic);
end OBUFT4_MXILINX_BBv2JTAGKEY;

architecture BEHAVIORAL of OBUFT4_MXILINX_BBv2JTAGKEY is
   attribute BOX_TYPE   : string ;
   component OBUFT
      port ( I : in    std_logic; 
             T : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of OBUFT : component is "BLACK_BOX";
   
begin
   I_36_37 : OBUFT
      port map (I=>I3,
                T=>T,
                O=>O3);
   
   I_36_38 : OBUFT
      port map (I=>I2,
                T=>T,
                O=>O2);
   
   I_36_39 : OBUFT
      port map (I=>I1,
                T=>T,
                O=>O1);
   
   I_36_40 : OBUFT
      port map (I=>I0,
                T=>T,
                O=>O0);
   
end BEHAVIORAL;



library ieee;
use ieee.std_logic_1164.ALL;
use ieee.numeric_std.ALL;
library UNISIM;
use UNISIM.Vcomponents.ALL;

entity BBv2JTAGKEY is
   port ( FT_DBGRQ     : in    std_logic; 
          FT_JTAG_BUF  : in    std_logic; 
          FT_nSRST_BUF : in    std_logic; 
          FT_nSRST_OUT : in    std_logic; 
          FT_nTRST     : in    std_logic; 
          FT_TCK       : in    std_logic; 
          FT_TDI       : in    std_logic; 
          FT_TMS       : in    std_logic; 
          RTCK         : in    std_logic; 
          TDO          : in    std_logic; 
          DBGRQ        : out   std_logic; 
          FT_nSRST_IN  : out   std_logic; 
          FT_RTCK      : out   std_logic; 
          FT_TDO       : out   std_logic; 
          nTRST        : out   std_logic; 
          TCK          : out   std_logic; 
          TDI          : out   std_logic; 
          TMS          : out   std_logic; 
          nSRST        : inout std_logic);
end BBv2JTAGKEY;

architecture BEHAVIORAL of BBv2JTAGKEY is
   attribute BOX_TYPE   : string ;
   attribute HU_SET     : string ;
   signal XLXN_39      : std_logic;
   signal XLXN_41      : std_logic;
   signal XLXN_43      : std_logic;
   signal XLXN_44      : std_logic;
   signal XLXN_45      : std_logic;
   signal XLXN_47      : std_logic;
   signal XLXN_48      : std_logic;
   signal XLXN_50      : std_logic;
   signal XLXN_52      : std_logic;
   signal XLXN_54      : std_logic;
   signal XLXN_55      : std_logic;
   component OBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of OBUF : component is "BLACK_BOX";
   
   component IBUF
      port ( I : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of IBUF : component is "BLACK_BOX";
   
   component OBUFT4_MXILINX_BBv2JTAGKEY
      port ( I0 : in    std_logic; 
             I1 : in    std_logic; 
             I2 : in    std_logic; 
             I3 : in    std_logic; 
             T  : in    std_logic; 
             O0 : out   std_logic; 
             O1 : out   std_logic; 
             O2 : out   std_logic; 
             O3 : out   std_logic);
   end component;
   
   component OBUFT
      port ( I : in    std_logic; 
             T : in    std_logic; 
             O : out   std_logic);
   end component;
   attribute BOX_TYPE of OBUFT : component is "BLACK_BOX";
   
   attribute HU_SET of XLXI_46 : label is "XLXI_46_0";
begin
   XLXI_7 : OBUF
      port map (I=>XLXN_50,
                O=>FT_nSRST_IN);
   
   XLXI_8 : OBUF
      port map (I=>XLXN_54,
                O=>FT_TDO);
   
   XLXI_11 : OBUF
      port map (I=>XLXN_55,
                O=>FT_RTCK);
   
   XLXI_27 : IBUF
      port map (I=>FT_TDI,
                O=>XLXN_41);
   
   XLXI_28 : IBUF
      port map (I=>FT_JTAG_BUF,
                O=>XLXN_39);
   
   XLXI_29 : IBUF
      port map (I=>FT_TMS,
                O=>XLXN_43);
   
   XLXI_30 : IBUF
      port map (I=>FT_TCK,
                O=>XLXN_44);
   
   XLXI_31 : IBUF
      port map (I=>FT_DBGRQ,
                O=>XLXN_45);
   
   XLXI_32 : IBUF
      port map (I=>FT_nSRST_BUF,
                O=>XLXN_47);
   
   XLXI_33 : IBUF
      port map (I=>FT_nSRST_OUT,
                O=>XLXN_48);
   
   XLXI_34 : IBUF
      port map (I=>FT_nTRST,
                O=>XLXN_52);
   
   XLXI_39 : OBUF
      port map (I=>XLXN_52,
                O=>nTRST);
   
   XLXI_40 : IBUF
      port map (I=>TDO,
                O=>XLXN_54);
   
   XLXI_41 : IBUF
      port map (I=>RTCK,
                O=>XLXN_55);
   
   XLXI_46 : OBUFT4_MXILINX_BBv2JTAGKEY
      port map (I0=>XLXN_41,
                I1=>XLXN_43,
                I2=>XLXN_44,
                I3=>XLXN_45,
                T=>XLXN_39,
                O0=>TDI,
                O1=>TMS,
                O2=>TCK,
                O3=>DBGRQ);
   
   XLXI_48 : OBUFT
      port map (I=>XLXN_48,
                T=>XLXN_47,
                O=>nSRST);
   
   XLXI_49 : IBUF
      port map (I=>nSRST,
                O=>XLXN_50);
   
end BEHAVIORAL;


