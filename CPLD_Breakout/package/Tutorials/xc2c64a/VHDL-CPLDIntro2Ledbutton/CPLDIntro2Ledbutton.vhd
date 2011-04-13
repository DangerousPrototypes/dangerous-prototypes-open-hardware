library IEEE;
use IEEE.STD_LOGIC_1164.ALL;
use IEEE.STD_LOGIC_ARITH.ALL;
use IEEE.STD_LOGIC_UNSIGNED.ALL;

entity light_LED_PB is Port (BUTTON: in  STD_LOGIC:='1';
										LED : out  STD_LOGIC:='0');
end light_LED_PB;

architecture Behavioral of light_LED_PB is
begin

LED <= BUTTON;

end Behavioral;