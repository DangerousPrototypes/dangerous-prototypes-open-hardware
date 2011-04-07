<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_4" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_1(7:0)" />
        <signal name="XLXN_2(7:0)" />
        <signal name="XLXN_3(7:0)" />
        <signal name="XLXN_9(7:0)" />
        <signal name="XLXN_19(7:0)" />
        <signal name="XLXN_20" />
        <signal name="XLXN_23" />
        <signal name="XLXN_24" />
        <signal name="XLXN_25" />
        <signal name="XLXN_26" />
        <signal name="XLXN_27" />
        <signal name="XLXN_28" />
        <signal name="XLXN_10(7:0)" />
        <signal name="XLXN_17(7:0)" />
        <signal name="XLXN_18" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="XLXN_36" />
        <signal name="XLXN_39" />
        <signal name="XLXN_40" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_46" />
        <port polarity="Output" name="XLXN_19(7:0)" />
        <port polarity="Input" name="XLXN_17(7:0)" />
        <port polarity="Input" name="XLXN_18" />
        <port polarity="Input" name="XLXN_21" />
        <port polarity="Input" name="XLXN_22" />
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
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="obuf8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="64" x="0" y="-44" height="24" />
            <rect width="96" x="128" y="-44" height="24" />
        </blockdef>
        <blockdef name="fd8ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="64" x="0" y="-268" height="24" />
            <rect width="256" x="64" y="-320" height="256" />
        </blockdef>
        <block symbolname="obuf8" name="XLXI_8">
            <blockpin signalname="XLXN_9(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_19(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="fd8ce" name="XLXI_16">
            <blockpin signalname="XLXN_24" name="C" />
            <blockpin signalname="XLXN_23" name="CE" />
            <blockpin signalname="XLXN_25" name="CLR" />
            <blockpin signalname="XLXN_10(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_1(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="fd8ce" name="XLXI_17">
            <blockpin signalname="XLXN_24" name="C" />
            <blockpin signalname="XLXN_23" name="CE" />
            <blockpin signalname="XLXN_25" name="CLR" />
            <blockpin signalname="XLXN_1(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_2(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="fd8ce" name="XLXI_18">
            <blockpin signalname="XLXN_24" name="C" />
            <blockpin signalname="XLXN_23" name="CE" />
            <blockpin signalname="XLXN_25" name="CLR" />
            <blockpin signalname="XLXN_2(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_3(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="fd8ce" name="XLXI_19">
            <blockpin signalname="XLXN_24" name="C" />
            <blockpin signalname="XLXN_23" name="CE" />
            <blockpin signalname="XLXN_25" name="CLR" />
            <blockpin signalname="XLXN_3(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_9(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="ibuf8" name="XLXI_6">
            <blockpin signalname="XLXN_17(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_10(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="ibuf" name="XLXI_21">
            <blockpin signalname="XLXN_22" name="I" />
            <blockpin signalname="XLXN_25" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_20">
            <blockpin signalname="XLXN_21" name="I" />
            <blockpin signalname="XLXN_24" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_7">
            <blockpin signalname="XLXN_18" name="I" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_1(7:0)">
            <wire x2="1264" y1="1264" y2="1264" x1="1104" />
        </branch>
        <branch name="XLXN_2(7:0)">
            <wire x2="1808" y1="1264" y2="1264" x1="1648" />
        </branch>
        <branch name="XLXN_3(7:0)">
            <wire x2="2336" y1="1264" y2="1264" x1="2192" />
        </branch>
        <branch name="XLXN_9(7:0)">
            <wire x2="2816" y1="1264" y2="1264" x1="2720" />
        </branch>
        <branch name="XLXN_19(7:0)">
            <wire x2="3200" y1="1264" y2="1264" x1="3040" />
        </branch>
        <iomarker fontsize="28" x="3200" y="1264" name="XLXN_19(7:0)" orien="R0" />
        <branch name="XLXN_25">
            <wire x2="720" y1="1920" y2="1920" x1="480" />
            <wire x2="1264" y1="1920" y2="1920" x1="720" />
            <wire x2="1808" y1="1920" y2="1920" x1="1264" />
            <wire x2="2336" y1="1920" y2="1920" x1="1808" />
            <wire x2="720" y1="1488" y2="1920" x1="720" />
            <wire x2="1264" y1="1488" y2="1920" x1="1264" />
            <wire x2="1808" y1="1488" y2="1920" x1="1808" />
            <wire x2="2336" y1="1488" y2="1920" x1="2336" />
        </branch>
        <branch name="XLXN_10(7:0)">
            <wire x2="720" y1="1264" y2="1264" x1="480" />
        </branch>
        <instance x="256" y="1296" name="XLXI_6" orien="R0" />
        <branch name="XLXN_17(7:0)">
            <wire x2="256" y1="1264" y2="1264" x1="224" />
        </branch>
        <branch name="XLXN_18">
            <wire x2="256" y1="1600" y2="1600" x1="224" />
        </branch>
        <instance x="256" y="1952" name="XLXI_21" orien="R0" />
        <instance x="256" y="1792" name="XLXI_20" orien="R0" />
        <instance x="256" y="1632" name="XLXI_7" orien="R0" />
        <branch name="XLXN_21">
            <wire x2="256" y1="1760" y2="1760" x1="224" />
        </branch>
        <branch name="XLXN_22">
            <wire x2="256" y1="1920" y2="1920" x1="224" />
        </branch>
        <iomarker fontsize="28" x="224" y="1264" name="XLXN_17(7:0)" orien="R180" />
        <iomarker fontsize="28" x="224" y="1600" name="XLXN_18" orien="R180" />
        <iomarker fontsize="28" x="224" y="1760" name="XLXN_21" orien="R180" />
        <iomarker fontsize="28" x="224" y="1920" name="XLXN_22" orien="R180" />
        <instance x="720" y="1520" name="XLXI_16" orien="R0" />
        <instance x="1264" y="1520" name="XLXI_17" orien="R0" />
        <instance x="1808" y="1520" name="XLXI_18" orien="R0" />
        <branch name="XLXN_23">
            <wire x2="592" y1="1600" y2="1600" x1="480" />
            <wire x2="1136" y1="1600" y2="1600" x1="592" />
            <wire x2="1680" y1="1600" y2="1600" x1="1136" />
            <wire x2="2208" y1="1600" y2="1600" x1="1680" />
            <wire x2="720" y1="1328" y2="1328" x1="592" />
            <wire x2="592" y1="1328" y2="1600" x1="592" />
            <wire x2="1264" y1="1328" y2="1328" x1="1136" />
            <wire x2="1136" y1="1328" y2="1600" x1="1136" />
            <wire x2="1808" y1="1328" y2="1328" x1="1680" />
            <wire x2="1680" y1="1328" y2="1600" x1="1680" />
            <wire x2="2208" y1="1328" y2="1600" x1="2208" />
            <wire x2="2336" y1="1328" y2="1328" x1="2208" />
        </branch>
        <branch name="XLXN_24">
            <wire x2="656" y1="1760" y2="1760" x1="480" />
            <wire x2="1200" y1="1760" y2="1760" x1="656" />
            <wire x2="1744" y1="1760" y2="1760" x1="1200" />
            <wire x2="2272" y1="1760" y2="1760" x1="1744" />
            <wire x2="720" y1="1392" y2="1392" x1="656" />
            <wire x2="656" y1="1392" y2="1760" x1="656" />
            <wire x2="1264" y1="1392" y2="1392" x1="1200" />
            <wire x2="1200" y1="1392" y2="1760" x1="1200" />
            <wire x2="1808" y1="1392" y2="1392" x1="1744" />
            <wire x2="1744" y1="1392" y2="1760" x1="1744" />
            <wire x2="2336" y1="1392" y2="1392" x1="2272" />
            <wire x2="2272" y1="1392" y2="1760" x1="2272" />
        </branch>
        <instance x="2336" y="1520" name="XLXI_19" orien="R0" />
        <instance x="2816" y="1296" name="XLXI_8" orien="R0" />
    </sheet>
</drawing>