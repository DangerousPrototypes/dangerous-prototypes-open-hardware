library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity light_LED is    Port (                    
                              LED : out  STD_LOGIC:='0');
end light_LED;

architecture Behavioral of light_LED is
begin

LED <= '1';					

end Behavioral;