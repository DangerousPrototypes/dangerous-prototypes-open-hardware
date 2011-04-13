<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xc9500xl" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_9" />
        <signal name="XLXN_11" />
        <signal name="XLXN_1" />
        <signal name="XLXN_2" />
        <signal name="XLXN_3" />
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_7" />
        <signal name="XLXN_8" />
        <signal name="XLXN_12" />
        <signal name="XLXN_13" />
        <signal name="XLXN_14" />
        <signal name="XLXN_15" />
        <signal name="XLXN_53" />
        <signal name="XLXN_16" />
        <signal name="Address_0" />
        <signal name="Address_1" />
        <signal name="Address_2" />
        <signal name="Strobe" />
        <signal name="Data" />
        <signal name="Dout_7" />
        <signal name="Dout_6" />
        <signal name="Dout_5" />
        <signal name="Dout_4" />
        <signal name="Dout_3" />
        <signal name="Dout_2" />
        <signal name="Dout_1" />
        <signal name="Dout_0" />
        <signal name="XLXN_68" />
        <signal name="XLXN_31" />
        <signal name="XLXN_26" />
        <signal name="XLXN_33" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="XLXN_38" />
        <signal name="XLXN_39" />
        <signal name="Clear" />
        <port polarity="Input" name="Address_0" />
        <port polarity="Input" name="Address_1" />
        <port polarity="Input" name="Address_2" />
        <port polarity="Input" name="Strobe" />
        <port polarity="Input" name="Data" />
        <port polarity="Output" name="Dout_7" />
        <port polarity="Output" name="Dout_6" />
        <port polarity="Output" name="Dout_5" />
        <port polarity="Output" name="Dout_4" />
        <port polarity="Output" name="Dout_3" />
        <port polarity="Output" name="Dout_2" />
        <port polarity="Output" name="Dout_1" />
        <port polarity="Output" name="Dout_0" />
        <port polarity="Input" name="Clear" />
        <blockdef name="d3_8e">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-576" y2="-576" x1="0" />
            <line x2="64" y1="-512" y2="-512" x1="0" />
            <line x2="64" y1="-448" y2="-448" x1="0" />
            <line x2="320" y1="-576" y2="-576" x1="384" />
            <line x2="320" y1="-512" y2="-512" x1="384" />
            <line x2="320" y1="-448" y2="-448" x1="384" />
            <line x2="320" y1="-384" y2="-384" x1="384" />
            <line x2="320" y1="-320" y2="-320" x1="384" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="320" y1="-192" y2="-192" x1="384" />
            <line x2="320" y1="-128" y2="-128" x1="384" />
            <rect width="256" x="64" y="-640" height="576" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
        </blockdef>
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
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
        <blockdef name="ldc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <rect width="256" x="64" y="-320" height="256" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
        </blockdef>
        <block symbolname="d3_8e" name="XLXI_1">
            <blockpin signalname="XLXN_12" name="A0" />
            <blockpin signalname="XLXN_13" name="A1" />
            <blockpin signalname="XLXN_14" name="A2" />
            <blockpin signalname="XLXN_15" name="E" />
            <blockpin signalname="XLXN_1" name="D0" />
            <blockpin signalname="XLXN_2" name="D1" />
            <blockpin signalname="XLXN_3" name="D2" />
            <blockpin signalname="XLXN_4" name="D3" />
            <blockpin signalname="XLXN_5" name="D4" />
            <blockpin signalname="XLXN_6" name="D5" />
            <blockpin signalname="XLXN_7" name="D6" />
            <blockpin signalname="XLXN_8" name="D7" />
        </block>
        <block symbolname="ibuf" name="XLXI_10">
            <blockpin signalname="Address_0" name="I" />
            <blockpin signalname="XLXN_12" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_11">
            <blockpin signalname="Address_1" name="I" />
            <blockpin signalname="XLXN_13" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_12">
            <blockpin signalname="Address_2" name="I" />
            <blockpin signalname="XLXN_14" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_13">
            <blockpin signalname="Strobe" name="I" />
            <blockpin signalname="XLXN_15" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="Data" name="I" />
            <blockpin signalname="XLXN_16" name="O" />
        </block>
        <block symbolname="ldc" name="XLXI_23">
            <blockpin signalname="XLXN_1" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_39" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_24">
            <blockpin signalname="XLXN_2" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_38" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_25">
            <blockpin signalname="XLXN_3" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_37" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_26">
            <blockpin signalname="XLXN_4" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_26" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_27">
            <blockpin signalname="XLXN_5" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_36" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_28">
            <blockpin signalname="XLXN_6" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_35" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_29">
            <blockpin signalname="XLXN_7" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_34" name="Q" />
        </block>
        <block symbolname="ldc" name="XLXI_30">
            <blockpin signalname="XLXN_8" name="G" />
            <blockpin signalname="XLXN_31" name="CLR" />
            <blockpin signalname="XLXN_16" name="D" />
            <blockpin signalname="XLXN_33" name="Q" />
        </block>
        <block symbolname="obuf" name="XLXI_15">
            <blockpin signalname="XLXN_39" name="I" />
            <blockpin signalname="Dout_0" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_16">
            <blockpin signalname="XLXN_38" name="I" />
            <blockpin signalname="Dout_1" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_17">
            <blockpin signalname="XLXN_37" name="I" />
            <blockpin signalname="Dout_2" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_18">
            <blockpin signalname="XLXN_26" name="I" />
            <blockpin signalname="Dout_3" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_19">
            <blockpin signalname="XLXN_36" name="I" />
            <blockpin signalname="Dout_4" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_20">
            <blockpin signalname="XLXN_35" name="I" />
            <blockpin signalname="Dout_5" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_21">
            <blockpin signalname="XLXN_34" name="I" />
            <blockpin signalname="Dout_6" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_22">
            <blockpin signalname="XLXN_33" name="I" />
            <blockpin signalname="Dout_7" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_31">
            <blockpin signalname="Clear" name="I" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_1">
            <wire x2="1408" y1="1184" y2="1184" x1="1168" />
            <wire x2="1408" y1="272" y2="1184" x1="1408" />
            <wire x2="2032" y1="272" y2="272" x1="1408" />
        </branch>
        <branch name="XLXN_2">
            <wire x2="1488" y1="1248" y2="1248" x1="1168" />
            <wire x2="1488" y1="592" y2="1248" x1="1488" />
            <wire x2="2032" y1="592" y2="592" x1="1488" />
        </branch>
        <branch name="XLXN_3">
            <wire x2="1568" y1="1312" y2="1312" x1="1168" />
            <wire x2="1568" y1="912" y2="1312" x1="1568" />
            <wire x2="2032" y1="912" y2="912" x1="1568" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1648" y1="1376" y2="1376" x1="1168" />
            <wire x2="1648" y1="1232" y2="1376" x1="1648" />
            <wire x2="2032" y1="1232" y2="1232" x1="1648" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="1648" y1="1440" y2="1440" x1="1168" />
            <wire x2="1648" y1="1440" y2="1552" x1="1648" />
            <wire x2="2032" y1="1552" y2="1552" x1="1648" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1568" y1="1504" y2="1504" x1="1168" />
            <wire x2="1568" y1="1504" y2="1872" x1="1568" />
            <wire x2="2032" y1="1872" y2="1872" x1="1568" />
        </branch>
        <branch name="XLXN_7">
            <wire x2="1488" y1="1568" y2="1568" x1="1168" />
            <wire x2="1488" y1="1568" y2="2192" x1="1488" />
            <wire x2="2032" y1="2192" y2="2192" x1="1488" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1408" y1="1632" y2="1632" x1="1168" />
            <wire x2="1408" y1="1632" y2="2512" x1="1408" />
            <wire x2="2032" y1="2512" y2="2512" x1="1408" />
        </branch>
        <branch name="XLXN_12">
            <wire x2="784" y1="1184" y2="1184" x1="736" />
        </branch>
        <branch name="XLXN_13">
            <wire x2="784" y1="1248" y2="1248" x1="736" />
        </branch>
        <branch name="XLXN_14">
            <wire x2="784" y1="1312" y2="1312" x1="736" />
        </branch>
        <branch name="XLXN_15">
            <wire x2="784" y1="1632" y2="1632" x1="736" />
        </branch>
        <branch name="XLXN_16">
            <wire x2="1792" y1="2384" y2="2384" x1="752" />
            <wire x2="2032" y1="2384" y2="2384" x1="1792" />
            <wire x2="2032" y1="144" y2="144" x1="1792" />
            <wire x2="1792" y1="144" y2="464" x1="1792" />
            <wire x2="2032" y1="464" y2="464" x1="1792" />
            <wire x2="1792" y1="464" y2="784" x1="1792" />
            <wire x2="2032" y1="784" y2="784" x1="1792" />
            <wire x2="1792" y1="784" y2="1104" x1="1792" />
            <wire x2="2032" y1="1104" y2="1104" x1="1792" />
            <wire x2="1792" y1="1104" y2="1424" x1="1792" />
            <wire x2="2032" y1="1424" y2="1424" x1="1792" />
            <wire x2="1792" y1="1424" y2="1744" x1="1792" />
            <wire x2="2032" y1="1744" y2="1744" x1="1792" />
            <wire x2="1792" y1="1744" y2="2064" x1="1792" />
            <wire x2="2032" y1="2064" y2="2064" x1="1792" />
            <wire x2="1792" y1="2064" y2="2384" x1="1792" />
        </branch>
        <branch name="Address_0">
            <wire x2="512" y1="1184" y2="1184" x1="480" />
        </branch>
        <branch name="Address_1">
            <wire x2="512" y1="1248" y2="1248" x1="480" />
        </branch>
        <branch name="Address_2">
            <wire x2="512" y1="1312" y2="1312" x1="480" />
        </branch>
        <branch name="Strobe">
            <wire x2="512" y1="1632" y2="1632" x1="480" />
        </branch>
        <branch name="Data">
            <wire x2="528" y1="2384" y2="2384" x1="496" />
        </branch>
        <branch name="Dout_7">
            <wire x2="2848" y1="2384" y2="2384" x1="2768" />
        </branch>
        <branch name="Dout_6">
            <wire x2="2848" y1="2064" y2="2064" x1="2768" />
        </branch>
        <branch name="Dout_5">
            <wire x2="2848" y1="1744" y2="1744" x1="2768" />
        </branch>
        <branch name="Dout_4">
            <wire x2="2848" y1="1424" y2="1424" x1="2768" />
        </branch>
        <branch name="Dout_3">
            <wire x2="2848" y1="1104" y2="1104" x1="2768" />
        </branch>
        <branch name="Dout_2">
            <wire x2="2848" y1="784" y2="784" x1="2768" />
        </branch>
        <branch name="Dout_1">
            <wire x2="2848" y1="464" y2="464" x1="2768" />
        </branch>
        <branch name="Dout_0">
            <wire x2="2848" y1="144" y2="144" x1="2768" />
        </branch>
        <branch name="XLXN_31">
            <wire x2="1888" y1="2608" y2="2608" x1="752" />
            <wire x2="2032" y1="2608" y2="2608" x1="1888" />
            <wire x2="2032" y1="368" y2="368" x1="1888" />
            <wire x2="1888" y1="368" y2="688" x1="1888" />
            <wire x2="2032" y1="688" y2="688" x1="1888" />
            <wire x2="1888" y1="688" y2="1008" x1="1888" />
            <wire x2="2032" y1="1008" y2="1008" x1="1888" />
            <wire x2="1888" y1="1008" y2="1328" x1="1888" />
            <wire x2="2032" y1="1328" y2="1328" x1="1888" />
            <wire x2="1888" y1="1328" y2="1648" x1="1888" />
            <wire x2="2032" y1="1648" y2="1648" x1="1888" />
            <wire x2="1888" y1="1648" y2="1968" x1="1888" />
            <wire x2="2032" y1="1968" y2="1968" x1="1888" />
            <wire x2="1888" y1="1968" y2="2288" x1="1888" />
            <wire x2="1888" y1="2288" y2="2608" x1="1888" />
            <wire x2="2032" y1="2288" y2="2288" x1="1888" />
        </branch>
        <branch name="XLXN_26">
            <wire x2="2544" y1="1104" y2="1104" x1="2416" />
        </branch>
        <branch name="XLXN_33">
            <wire x2="2544" y1="2384" y2="2384" x1="2416" />
        </branch>
        <branch name="XLXN_34">
            <wire x2="2544" y1="2064" y2="2064" x1="2416" />
        </branch>
        <branch name="XLXN_35">
            <wire x2="2544" y1="1744" y2="1744" x1="2416" />
        </branch>
        <branch name="XLXN_36">
            <wire x2="2544" y1="1424" y2="1424" x1="2416" />
        </branch>
        <branch name="XLXN_37">
            <wire x2="2544" y1="784" y2="784" x1="2416" />
        </branch>
        <branch name="XLXN_38">
            <wire x2="2544" y1="464" y2="464" x1="2416" />
        </branch>
        <branch name="XLXN_39">
            <wire x2="2544" y1="144" y2="144" x1="2416" />
        </branch>
        <branch name="Clear">
            <wire x2="528" y1="2608" y2="2608" x1="496" />
        </branch>
        <instance x="784" y="1760" name="XLXI_1" orien="R0" />
        <instance x="512" y="1216" name="XLXI_10" orien="R0" />
        <instance x="512" y="1280" name="XLXI_11" orien="R0" />
        <instance x="512" y="1344" name="XLXI_12" orien="R0" />
        <instance x="512" y="1664" name="XLXI_13" orien="R0" />
        <instance x="528" y="2416" name="XLXI_14" orien="R0" />
        <instance x="2032" y="400" name="XLXI_23" orien="R0" />
        <instance x="2032" y="720" name="XLXI_24" orien="R0" />
        <instance x="2032" y="1040" name="XLXI_25" orien="R0" />
        <instance x="2032" y="1360" name="XLXI_26" orien="R0" />
        <instance x="2032" y="1680" name="XLXI_27" orien="R0" />
        <instance x="2032" y="2000" name="XLXI_28" orien="R0" />
        <instance x="2032" y="2320" name="XLXI_29" orien="R0" />
        <instance x="2032" y="2640" name="XLXI_30" orien="R0" />
        <instance x="2544" y="176" name="XLXI_15" orien="R0" />
        <instance x="2544" y="496" name="XLXI_16" orien="R0" />
        <instance x="2544" y="816" name="XLXI_17" orien="R0" />
        <instance x="2544" y="1136" name="XLXI_18" orien="R0" />
        <instance x="2544" y="1456" name="XLXI_19" orien="R0" />
        <instance x="2544" y="1776" name="XLXI_20" orien="R0" />
        <instance x="2544" y="2096" name="XLXI_21" orien="R0" />
        <instance x="2544" y="2416" name="XLXI_22" orien="R0" />
        <instance x="528" y="2640" name="XLXI_31" orien="R0" />
        <iomarker fontsize="28" x="480" y="1184" name="Address_0" orien="R180" />
        <iomarker fontsize="28" x="480" y="1248" name="Address_1" orien="R180" />
        <iomarker fontsize="28" x="480" y="1312" name="Address_2" orien="R180" />
        <iomarker fontsize="28" x="480" y="1632" name="Strobe" orien="R180" />
        <iomarker fontsize="28" x="496" y="2384" name="Data" orien="R180" />
        <iomarker fontsize="28" x="2848" y="464" name="Dout_1" orien="R0" />
        <iomarker fontsize="28" x="2848" y="144" name="Dout_0" orien="R0" />
        <iomarker fontsize="28" x="2848" y="784" name="Dout_2" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1104" name="Dout_3" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1424" name="Dout_4" orien="R0" />
        <iomarker fontsize="28" x="2848" y="1744" name="Dout_5" orien="R0" />
        <iomarker fontsize="28" x="2848" y="2064" name="Dout_6" orien="R0" />
        <iomarker fontsize="28" x="2848" y="2384" name="Dout_7" orien="R0" />
        <iomarker fontsize="28" x="496" y="2608" name="Clear" orien="R180" />
    </sheet>
</drawing>