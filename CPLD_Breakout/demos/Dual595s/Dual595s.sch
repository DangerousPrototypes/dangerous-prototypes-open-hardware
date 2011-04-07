<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_7" />
        <signal name="XLXN_1(7:0)" />
        <signal name="XLXN_2(7:0)" />
        <signal name="XLXN_12" />
        <signal name="XLXN_3" />
        <signal name="XLXN_5" />
        <signal name="XLXN_6" />
        <signal name="XLXN_8" />
        <signal name="XLXN_1(7)" />
        <signal name="XLXN_18(7:0)" />
        <signal name="XLXN_19(7:0)" />
        <signal name="XLXN_21" />
        <signal name="XLXN_22" />
        <signal name="SER" />
        <signal name="XLXN_29(7:0)" />
        <signal name="XLXN_30(7:0)" />
        <signal name="XLXN_32" />
        <signal name="XLXN_34" />
        <signal name="XLXN_35" />
        <signal name="XLXN_36" />
        <signal name="XLXN_37" />
        <signal name="OEn" />
        <signal name="RCLK" />
        <signal name="XLXN_31" />
        <signal name="SRCLRn" />
        <signal name="XLXN_40" />
        <signal name="SRCLK" />
        <port polarity="Input" name="SER" />
        <port polarity="Output" name="XLXN_29(7:0)" />
        <port polarity="Output" name="XLXN_30(7:0)" />
        <port polarity="Input" name="OEn" />
        <port polarity="Input" name="RCLK" />
        <port polarity="Input" name="SRCLRn" />
        <port polarity="Input" name="SRCLK" />
        <blockdef name="sr8ce">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <rect width="256" x="64" y="-384" height="320" />
            <line x2="64" y1="-320" y2="-320" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="192" y1="-64" y2="-32" x1="192" />
            <line x2="64" y1="-32" y2="-32" x1="192" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <line x2="64" y1="-192" y2="-192" x1="0" />
            <rect width="64" x="320" y="-268" height="24" />
        </blockdef>
        <blockdef name="fd8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="64" y1="-256" y2="-256" x1="0" />
            <line x2="320" y1="-256" y2="-256" x1="384" />
            <line x2="80" y1="-112" y2="-128" x1="64" />
            <line x2="64" y1="-128" y2="-144" x1="80" />
            <rect width="64" x="320" y="-268" height="24" />
            <rect width="64" x="0" y="-268" height="24" />
            <rect width="256" x="64" y="-320" height="256" />
        </blockdef>
        <blockdef name="obufe8">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-96" y2="-96" x1="0" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <rect width="64" x="0" y="-44" height="24" />
            <rect width="96" x="128" y="-44" height="24" />
            <line x2="64" y1="-96" y2="-96" x1="96" />
            <line x2="96" y1="-48" y2="-96" x1="96" />
            <line x2="64" y1="-64" y2="0" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="128" y1="0" y2="-32" x1="64" />
        </blockdef>
        <blockdef name="ibuf">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="0" y2="-64" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
        </blockdef>
        <blockdef name="inv">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="160" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-64" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="0" x1="128" />
            <line x2="64" y1="0" y2="-64" x1="64" />
            <circle r="16" cx="144" cy="-32" />
        </blockdef>
        <blockdef name="vcc">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="32" y1="-64" y2="-64" x1="96" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="64" />
        </blockdef>
        <block symbolname="sr8ce" name="XLXI_4">
            <blockpin signalname="XLXN_6" name="C" />
            <blockpin signalname="XLXN_8" name="CE" />
            <blockpin signalname="XLXN_5" name="CLR" />
            <blockpin signalname="XLXN_1(7)" name="SLI" />
            <blockpin signalname="XLXN_2(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="fd8" name="XLXI_6">
            <blockpin signalname="XLXN_3" name="C" />
            <blockpin signalname="XLXN_2(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_19(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="sr8ce" name="XLXI_3">
            <blockpin signalname="XLXN_6" name="C" />
            <blockpin signalname="XLXN_8" name="CE" />
            <blockpin signalname="XLXN_5" name="CLR" />
            <blockpin signalname="XLXN_22" name="SLI" />
            <blockpin signalname="XLXN_1(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="fd8" name="XLXI_5">
            <blockpin signalname="XLXN_3" name="C" />
            <blockpin signalname="XLXN_1(7:0)" name="D(7:0)" />
            <blockpin signalname="XLXN_18(7:0)" name="Q(7:0)" />
        </block>
        <block symbolname="obufe8" name="XLXI_11">
            <blockpin signalname="XLXN_32" name="E" />
            <blockpin signalname="XLXN_18(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_30(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="obufe8" name="XLXI_12">
            <blockpin signalname="XLXN_32" name="E" />
            <blockpin signalname="XLXN_19(7:0)" name="I(7:0)" />
            <blockpin signalname="XLXN_29(7:0)" name="O(7:0)" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="SER" name="I" />
            <blockpin signalname="XLXN_22" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_19">
            <blockpin signalname="XLXN_31" name="I" />
            <blockpin signalname="XLXN_32" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_13">
            <blockpin signalname="OEn" name="I" />
            <blockpin signalname="XLXN_31" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_18">
            <blockpin signalname="RCLK" name="I" />
            <blockpin signalname="XLXN_3" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_17">
            <blockpin signalname="SRCLRn" name="I" />
            <blockpin signalname="XLXN_40" name="O" />
        </block>
        <block symbolname="inv" name="XLXI_21">
            <blockpin signalname="XLXN_40" name="I" />
            <blockpin signalname="XLXN_5" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_16">
            <blockpin signalname="SRCLK" name="I" />
            <blockpin signalname="XLXN_6" name="O" />
        </block>
        <block symbolname="vcc" name="XLXI_28">
            <blockpin signalname="XLXN_8" name="P" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="1360" y="1872" name="XLXI_4" orien="R0" />
        <instance x="2016" y="1872" name="XLXI_6" orien="R0" />
        <branch name="XLXN_1(7:0)">
            <wire x2="1824" y1="1056" y2="1056" x1="1744" />
            <wire x2="2032" y1="1056" y2="1056" x1="1824" />
        </branch>
        <branch name="XLXN_2(7:0)">
            <wire x2="2016" y1="1616" y2="1616" x1="1744" />
        </branch>
        <instance x="1360" y="1312" name="XLXI_3" orien="R0" />
        <instance x="2032" y="1312" name="XLXI_5" orien="R0" />
        <branch name="XLXN_3">
            <wire x2="1888" y1="656" y2="656" x1="768" />
            <wire x2="1888" y1="656" y2="1184" x1="1888" />
            <wire x2="2032" y1="1184" y2="1184" x1="1888" />
            <wire x2="1888" y1="1184" y2="1744" x1="1888" />
            <wire x2="2016" y1="1744" y2="1744" x1="1888" />
        </branch>
        <branch name="XLXN_5">
            <wire x2="1168" y1="784" y2="784" x1="1024" />
            <wire x2="1168" y1="784" y2="1280" x1="1168" />
            <wire x2="1360" y1="1280" y2="1280" x1="1168" />
            <wire x2="1168" y1="1280" y2="1840" x1="1168" />
            <wire x2="1360" y1="1840" y2="1840" x1="1168" />
        </branch>
        <branch name="XLXN_6">
            <wire x2="1088" y1="896" y2="896" x1="768" />
            <wire x2="1088" y1="896" y2="1184" x1="1088" />
            <wire x2="1360" y1="1184" y2="1184" x1="1088" />
            <wire x2="1088" y1="1184" y2="1744" x1="1088" />
            <wire x2="1360" y1="1744" y2="1744" x1="1088" />
        </branch>
        <branch name="XLXN_8">
            <wire x2="1008" y1="1120" y2="1120" x1="768" />
            <wire x2="1360" y1="1120" y2="1120" x1="1008" />
            <wire x2="1008" y1="1120" y2="1680" x1="1008" />
            <wire x2="1360" y1="1680" y2="1680" x1="1008" />
        </branch>
        <branch name="XLXN_1(7)">
            <wire x2="1824" y1="1376" y2="1376" x1="1248" />
            <wire x2="1248" y1="1376" y2="1552" x1="1248" />
            <wire x2="1360" y1="1552" y2="1552" x1="1248" />
            <wire x2="1824" y1="1152" y2="1376" x1="1824" />
        </branch>
        <instance x="2528" y="1088" name="XLXI_11" orien="R0" />
        <instance x="2496" y="1648" name="XLXI_12" orien="R0" />
        <branch name="XLXN_18(7:0)">
            <wire x2="2528" y1="1056" y2="1056" x1="2416" />
        </branch>
        <branch name="XLXN_19(7:0)">
            <wire x2="2496" y1="1616" y2="1616" x1="2400" />
        </branch>
        <instance x="544" y="1024" name="XLXI_14" orien="R0" />
        <branch name="XLXN_22">
            <wire x2="1360" y1="992" y2="992" x1="768" />
        </branch>
        <branch name="SER">
            <wire x2="544" y1="992" y2="992" x1="512" />
        </branch>
        <iomarker fontsize="28" x="512" y="992" name="SER" orien="R180" />
        <branch name="XLXN_29(7:0)">
            <wire x2="2752" y1="1616" y2="1616" x1="2720" />
        </branch>
        <iomarker fontsize="28" x="2752" y="1616" name="XLXN_29(7:0)" orien="R0" />
        <branch name="XLXN_30(7:0)">
            <wire x2="2784" y1="1056" y2="1056" x1="2752" />
        </branch>
        <iomarker fontsize="28" x="2784" y="1056" name="XLXN_30(7:0)" orien="R0" />
        <bustap x2="1824" y1="1056" y2="1152" x1="1824" />
        <branch name="XLXN_32">
            <wire x2="2448" y1="528" y2="528" x1="1008" />
            <wire x2="2448" y1="528" y2="992" x1="2448" />
            <wire x2="2448" y1="992" y2="1552" x1="2448" />
            <wire x2="2496" y1="1552" y2="1552" x1="2448" />
            <wire x2="2528" y1="992" y2="992" x1="2448" />
        </branch>
        <branch name="OEn">
            <wire x2="544" y1="528" y2="528" x1="528" />
        </branch>
        <branch name="RCLK">
            <wire x2="544" y1="656" y2="656" x1="528" />
        </branch>
        <instance x="784" y="560" name="XLXI_19" orien="R0" />
        <branch name="XLXN_31">
            <wire x2="784" y1="528" y2="528" x1="768" />
        </branch>
        <instance x="544" y="560" name="XLXI_13" orien="R0" />
        <instance x="544" y="688" name="XLXI_18" orien="R0" />
        <instance x="544" y="816" name="XLXI_17" orien="R0" />
        <branch name="SRCLRn">
            <wire x2="544" y1="784" y2="784" x1="512" />
        </branch>
        <branch name="XLXN_40">
            <wire x2="800" y1="784" y2="784" x1="768" />
        </branch>
        <instance x="800" y="816" name="XLXI_21" orien="R0" />
        <iomarker fontsize="28" x="528" y="528" name="OEn" orien="R180" />
        <iomarker fontsize="28" x="528" y="656" name="RCLK" orien="R180" />
        <iomarker fontsize="28" x="512" y="784" name="SRCLRn" orien="R180" />
        <branch name="SRCLK">
            <wire x2="544" y1="896" y2="896" x1="512" />
        </branch>
        <instance x="544" y="928" name="XLXI_16" orien="R0" />
        <iomarker fontsize="28" x="512" y="896" name="SRCLK" orien="R180" />
        <instance x="704" y="1120" name="XLXI_28" orien="R0" />
    </sheet>
</drawing>