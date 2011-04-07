<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_1(7:0)" />
        <signal name="XLXN_22" />
        <signal name="XLXN_23" />
        <signal name="XLXN_27" />
        <signal name="XLXN_44(7:0)" />
        <signal name="XLXN_49" />
        <signal name="XLXN_50" />
        <signal name="XLXN_56(7:0)" />
        <signal name="XLXN_60" />
        <signal name="XLXN_61" />
        <signal name="XLXN_86(7:0)" />
        <signal name="Zero" />
        <signal name="XLXN_120(7)" />
        <signal name="XLXN_120(6)" />
        <signal name="XLXN_120(5)" />
        <signal name="XLXN_120(4)" />
        <signal name="XLXN_120(3)" />
        <signal name="XLXN_120(2)" />
        <signal name="XLXN_120(1)" />
        <signal name="XLXN_120(0)" />
        <signal name="XLXN_62(7:0)" />
        <signal name="Equal" />
        <signal name="PWM" />
        <signal name="XLXN_25" />
        <signal name="XLXN_6(7:0)" />
        <signal name="XLXN_7" />
        <signal name="DutyCycle(7:0)" />
        <signal name="Strobe" />
        <signal name="XLXN_120(7:0)" />
        <signal name="XLXN_121(7:0)" />
        <signal name="XLXN_122" />
        <signal name="XLXN_135(7:0)" />
        <signal name="XLXN_136" />
        <signal name="XLXN_137" />
        <signal name="XLXN_140" />
        <signal name="XLXN_5" />
        <signal name="XLXN_4" />
        <signal name="Clock" />
        <signal name="Enable" />
        <signal name="Clear" />
        <signal name="XLXN_139" />
        <signal name="XLXN_147(7:0)" />
        <signal name="XLXN_149(7:0)" />
        <port polarity="Output" name="PWM" />
        <port polarity="Input" name="DutyCycle(7:0)" />
        <port polarity="Input" name="Strobe" />
        <port polarity="Input" name="Clock" />
        <port polarity="Input" name="Enable" />
        <port polarity="Input" name="Clear" />
        <blockdef name="cb8ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="64" x="320" y="-268" height="24" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
        </blockdef>
        <blockdef name="ld8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="64" x="0" y="-268" height="24" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="comp8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="320" y1="-224" y2="-224" x1="384" />
            <rect width="64" x="0" y="-332" height="24" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <rect width="64" x="0" y="-140" height="24" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="ibuf8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="96" x="128" y="-44" height="24" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="64" x="0" y="-44" height="24" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="obuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
        </blockdef>
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="ftcp">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-352" y2="-352" x1="192" />
            <line x2="192" y1="-320" y2="-352" x1="192" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="64" y1="-352" y2="-352" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <rect width="256" x="64" y="-320" height="256" />
        </blockdef>
        <blockdef name="gnd">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-96" x1="64" />
            <line x2="64" y1="-64" y2="-80" x1="64" />
            <line x2="40" y1="-64" y2="-64" x1="88" />
            <line x2="60" y1="-32" y2="-32" x1="68" />
            <line x2="52" y1="-48" y2="-48" x1="76" />
            <line x2="64" y1="-64" y2="-96" x1="64" />
        </blockdef>
        <blockdef name="xnor8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <arc ex="48" ey="-336" sx="48" sy="-240" r="56" cx="16" cy="-288" />
            <arc ex="64" ey="-336" sx="64" sy="-240" r="56" cx="32" cy="-288" />
            <line x2="48" y1="-128" y2="-128" x1="0" />
            <line x2="48" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="60" y1="-320" y2="-320" x1="0" />
            <line x2="48" y1="-384" y2="-384" x1="0" />
            <arc ex="208" ey="-288" sx="128" sy="-240" r="88" cx="132" cy="-328" />
            <arc ex="128" ey="-336" sx="208" sy="-288" r="88" cx="132" cy="-248" />
            <line x2="64" y1="-240" y2="-240" x1="128" />
            <line x2="64" y1="-336" y2="-336" x1="128" />
            <line x2="48" y1="-64" y2="-64" x1="0" />
            <line x2="48" y1="-448" y2="-448" x1="0" />
            <line x2="48" y1="-512" y2="-512" x1="0" />
            <line x2="48" y1="-64" y2="-240" x1="48" />
            <line x2="48" y1="-336" y2="-512" x1="48" />
            <circle r="8" cx="220" cy="-288" />
            <line x2="256" y1="-288" y2="-288" x1="228" />
        </blockdef>
        <block symbolname="comp8" name="XLXI_3">
            <blockpin signalname="XLXN_120(7:0)" name="A(7:0)" />
            <blockpin signalname="XLXN_121(7:0)" name="B(7:0)" />
            <blockpin signalname="Equal" name="EQ" />
        </block>
        <block symbolname="ftcp" name="XLXI_30">
            <blockpin signalname="XLXN_140" name="C" />
            <blockpin signalname="Equal" name="CLR" />
            <blockpin signalname="Zero" name="PRE" />
            <blockpin signalname="XLXN_140" name="T" />
            <blockpin signalname="XLXN_25" name="Q" />
        </block>
        <block symbolname="obuf" name="XLXI_6">
            <blockpin signalname="XLXN_25" name="I" />
            <blockpin signalname="PWM" name="O" />
        </block>
        <block symbolname="ibuf8" name="XLXI_5">
            <blockpin signalname="DutyCycle(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_6(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="ibuf" name="XLXI_9">
            <blockpin signalname="Strobe" name="I" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="ld8" name="XLXI_2">
            <blockpin signalname="XLXN_6(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_7" name="G" />
            <blockpin signalname="XLXN_121(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="gnd" name="XLXI_67">
            <blockpin signalname="XLXN_140" name="G" />
        </block>
        <block symbolname="ibuf" name="XLXI_7">
            <blockpin signalname="Enable" name="I" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_8">
            <blockpin signalname="Clock" name="I" />
            <blockpin signalname="XLXN_5" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_66">
            <blockpin signalname="Clear" name="I" />
            <blockpin signalname="XLXN_139" name="O" />
        </block>
        <block symbolname="cb8ce" name="XLXI_1">
            <blockpin signalname="XLXN_5" name="C" />
            <blockpin signalname="XLXN_4" name="CE" />
            <blockpin signalname="XLXN_139" name="CLR" />
            <blockpin name="CEO" />
            <blockpin signalname="XLXN_120(7:0)" name="Q(7:0)" />
            <blockpin name="TC" />
        </block>
        <block symbolname="xnor8" name="XLXI_72">
            <blockpin signalname="XLXN_120(0)" name="I0" />
            <blockpin signalname="XLXN_120(1)" name="I1" />
            <blockpin signalname="XLXN_120(2)" name="I2" />
            <blockpin signalname="XLXN_120(3)" name="I3" />
            <blockpin signalname="XLXN_120(4)" name="I4" />
            <blockpin signalname="XLXN_120(5)" name="I5" />
            <blockpin signalname="XLXN_120(6)" name="I6" />
            <blockpin signalname="XLXN_120(7)" name="I7" />
            <blockpin signalname="Zero" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_120(7)">
            <wire x2="1776" y1="576" y2="576" x1="1616" />
        </branch>
        <branch name="XLXN_120(6)">
            <wire x2="1776" y1="640" y2="640" x1="1616" />
        </branch>
        <branch name="XLXN_120(5)">
            <wire x2="1776" y1="704" y2="704" x1="1616" />
        </branch>
        <branch name="XLXN_120(4)">
            <wire x2="1776" y1="768" y2="768" x1="1616" />
        </branch>
        <branch name="XLXN_120(3)">
            <wire x2="1776" y1="832" y2="832" x1="1616" />
        </branch>
        <branch name="XLXN_120(2)">
            <wire x2="1776" y1="896" y2="896" x1="1616" />
        </branch>
        <branch name="XLXN_120(1)">
            <wire x2="1776" y1="960" y2="960" x1="1616" />
        </branch>
        <branch name="XLXN_120(0)">
            <wire x2="1776" y1="1024" y2="1024" x1="1616" />
        </branch>
        <branch name="Equal">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2256" y="1392" type="branch" />
            <wire x2="2256" y1="1392" y2="1392" x1="1952" />
            <wire x2="2384" y1="1392" y2="1392" x1="2256" />
            <wire x2="2384" y1="1232" y2="1392" x1="2384" />
        </branch>
        <branch name="PWM">
            <wire x2="3088" y1="1008" y2="1008" x1="3056" />
        </branch>
        <branch name="XLXN_25">
            <wire x2="2832" y1="1008" y2="1008" x1="2768" />
        </branch>
        <bustap x2="1616" y1="576" y2="576" x1="1520" />
        <bustap x2="1616" y1="640" y2="640" x1="1520" />
        <bustap x2="1616" y1="704" y2="704" x1="1520" />
        <bustap x2="1616" y1="768" y2="768" x1="1520" />
        <bustap x2="1616" y1="832" y2="832" x1="1520" />
        <bustap x2="1616" y1="896" y2="896" x1="1520" />
        <bustap x2="1616" y1="960" y2="960" x1="1520" />
        <bustap x2="1616" y1="1024" y2="1024" x1="1520" />
        <branch name="XLXN_6(7:0)">
            <wire x2="944" y1="1648" y2="1648" x1="880" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="944" y1="1776" y2="1776" x1="880" />
        </branch>
        <branch name="DutyCycle(7:0)">
            <wire x2="656" y1="1648" y2="1648" x1="624" />
        </branch>
        <branch name="Strobe">
            <wire x2="656" y1="1776" y2="1776" x1="624" />
        </branch>
        <instance x="656" y="1680" name="XLXI_5" orien="R0" />
        <instance x="656" y="1808" name="XLXI_9" orien="R0" />
        <instance x="944" y="1904" name="XLXI_2" orien="R0" />
        <iomarker fontsize="28" x="624" y="1648" name="DutyCycle(7:0)" orien="R180" />
        <iomarker fontsize="28" x="624" y="1776" name="Strobe" orien="R180" />
        <branch name="Zero">
            <attrtext style="alignment:SOFT-BCENTER" attrname="Name" x="2176" y="800" type="branch" />
            <wire x2="2176" y1="800" y2="800" x1="2032" />
            <wire x2="2384" y1="800" y2="800" x1="2176" />
            <wire x2="2384" y1="800" y2="912" x1="2384" />
        </branch>
        <branch name="XLXN_121(7:0)">
            <wire x2="1520" y1="1648" y2="1648" x1="1328" />
            <wire x2="1568" y1="1488" y2="1488" x1="1520" />
            <wire x2="1520" y1="1488" y2="1648" x1="1520" />
        </branch>
        <instance x="2384" y="1264" name="XLXI_30" orien="R0" />
        <instance x="2832" y="1040" name="XLXI_6" orien="R0" />
        <iomarker fontsize="28" x="3088" y="1008" name="PWM" orien="R0" />
        <instance x="2208" y="1312" name="XLXI_67" orien="R0" />
        <branch name="XLXN_140">
            <wire x2="2384" y1="1008" y2="1008" x1="2272" />
            <wire x2="2272" y1="1008" y2="1136" x1="2272" />
            <wire x2="2272" y1="1136" y2="1184" x1="2272" />
            <wire x2="2384" y1="1136" y2="1136" x1="2272" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="944" y1="1280" y2="1280" x1="848" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="944" y1="1216" y2="1216" x1="848" />
        </branch>
        <branch name="Clock">
            <wire x2="624" y1="1280" y2="1280" x1="592" />
        </branch>
        <branch name="Enable">
            <wire x2="624" y1="1216" y2="1216" x1="592" />
        </branch>
        <branch name="Clear">
            <wire x2="624" y1="1376" y2="1376" x1="592" />
        </branch>
        <branch name="XLXN_139">
            <wire x2="944" y1="1376" y2="1376" x1="848" />
        </branch>
        <instance x="624" y="1248" name="XLXI_7" orien="R0" />
        <instance x="624" y="1312" name="XLXI_8" orien="R0" />
        <instance x="624" y="1408" name="XLXI_66" orien="R0" />
        <instance x="944" y="1408" name="XLXI_1" orien="R0" />
        <iomarker fontsize="28" x="592" y="1216" name="Enable" orien="R180" />
        <iomarker fontsize="28" x="592" y="1280" name="Clock" orien="R180" />
        <iomarker fontsize="28" x="592" y="1376" name="Clear" orien="R180" />
        <instance x="1776" y="1088" name="XLXI_72" orien="R0" />
        <instance x="1568" y="1616" name="XLXI_3" orien="R0" />
        <branch name="XLXN_120(7:0)">
            <wire x2="1520" y1="1152" y2="1152" x1="1328" />
            <wire x2="1520" y1="1152" y2="1296" x1="1520" />
            <wire x2="1568" y1="1296" y2="1296" x1="1520" />
            <wire x2="1520" y1="576" y2="640" x1="1520" />
            <wire x2="1520" y1="640" y2="704" x1="1520" />
            <wire x2="1520" y1="704" y2="768" x1="1520" />
            <wire x2="1520" y1="768" y2="832" x1="1520" />
            <wire x2="1520" y1="832" y2="896" x1="1520" />
            <wire x2="1520" y1="896" y2="960" x1="1520" />
            <wire x2="1520" y1="960" y2="1024" x1="1520" />
            <wire x2="1520" y1="1024" y2="1152" x1="1520" />
        </branch>
    </sheet>
</drawing>