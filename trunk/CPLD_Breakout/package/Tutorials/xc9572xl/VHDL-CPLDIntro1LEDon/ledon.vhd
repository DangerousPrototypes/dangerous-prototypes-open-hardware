library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity light_LED is    Port (  clock_in : in  STD_LOGIC:='0';			                      
                              LED_pin : out  STD_LOGIC:='0');
end light_LED;

architecture Behavioral of light_LED is
begin	

process(clock_in)
begin

LED_pin <= clock_in;					

end process;

end Behavioral;