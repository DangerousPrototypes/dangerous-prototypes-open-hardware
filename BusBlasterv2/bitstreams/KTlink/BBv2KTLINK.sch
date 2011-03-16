<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_463" />
        <signal name="XLXN_465" />
        <signal name="FT_nTRST" />
        <signal name="nTRST" />
        <signal name="XLXN_52" />
        <signal name="XLXN_61" />
        <signal name="ACBUS2" />
        <signal name="XLXN_50" />
        <signal name="XLXN_48" />
        <signal name="XLXN_47" />
        <signal name="nSRST" />
        <signal name="FT_nSRST_OUT" />
        <signal name="ACBUS3" />
        <signal name="FT_nSRST_IN" />
        <signal name="XLXN_55" />
        <signal name="RTCK" />
        <signal name="FT_RTCK" />
        <signal name="TCK" />
        <signal name="FT_TCK" />
        <signal name="XLXN_261" />
        <signal name="XLXN_262" />
        <signal name="ACBUS6" />
        <signal name="TDI" />
        <signal name="ACBUS5" />
        <signal name="XLXN_266" />
        <signal name="XLXN_267" />
        <signal name="FT_TMS" />
        <signal name="XLXN_491" />
        <signal name="TMS" />
        <signal name="XLXN_435" />
        <signal name="XLXN_439" />
        <signal name="XLXN_440" />
        <signal name="ADBUS5" />
        <signal name="XLXN_444" />
        <signal name="TDO" />
        <signal name="FT_TDO" />
        <signal name="XLXN_437" />
        <signal name="ACBUS4" />
        <signal name="XLXN_442" />
        <signal name="XLXN_443" />
        <signal name="FT_TDI" />
        <signal name="XLXN_506" />
        <port polarity="Input" name="FT_nTRST" />
        <port polarity="Output" name="nTRST" />
        <port polarity="Input" name="ACBUS2" />
        <port polarity="BiDirectional" name="nSRST" />
        <port polarity="Input" name="FT_nSRST_OUT" />
        <port polarity="Input" name="ACBUS3" />
        <port polarity="Output" name="FT_nSRST_IN" />
        <port polarity="Input" name="RTCK" />
        <port polarity="Output" name="FT_RTCK" />
        <port polarity="Output" name="TCK" />
        <port polarity="Input" name="FT_TCK" />
        <port polarity="Input" name="ACBUS6" />
        <port polarity="Output" name="TDI" />
        <port polarity="Input" name="ACBUS5" />
        <port polarity="Input" name="FT_TMS" />
        <port polarity="BiDirectional" name="TMS" />
        <port polarity="Input" name="ADBUS5" />
        <port polarity="Input" name="TDO" />
        <port polarity="Output" name="FT_TDO" />
        <port polarity="Input" name="ACBUS4" />
        <port polarity="Input" name="FT_TDI" />
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
        <blockdef name="obuft">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-96" y2="-96" x1="0" />
            <line x2="64" y1="-96" y2="-96" x1="96" />
            <line x2="96" y1="-48" y2="-96" x1="96" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="64" y1="-64" y2="0" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="128" y1="0" y2="-32" x1="64" />
        </blockdef>
        <blockdef name="pullup">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-108" y2="-128" x1="64" />
            <line x2="64" y1="-104" y2="-108" x1="80" />
            <line x2="80" y1="-88" y2="-104" x1="48" />
            <line x2="48" y1="-72" y2="-88" x1="80" />
            <line x2="80" y1="-56" y2="-72" x1="48" />
            <line x2="48" y1="-48" y2="-56" x1="64" />
            <line x2="64" y1="-32" y2="-48" x1="64" />
            <line x2="64" y1="-56" y2="-48" x1="48" />
            <line x2="48" y1="-72" y2="-56" x1="80" />
            <line x2="80" y1="-88" y2="-72" x1="48" />
            <line x2="48" y1="-104" y2="-88" x1="80" />
            <line x2="80" y1="-108" y2="-104" x1="64" />
            <line x2="64" y1="0" y2="-32" x1="64" />
            <line x2="32" y1="-128" y2="-128" x1="96" />
        </blockdef>
        <blockdef name="m2_1">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="96" y1="-64" y2="-192" x1="96" />
            <line x2="96" y1="-96" y2="-64" x1="256" />
            <line x2="256" y1="-160" y2="-96" x1="256" />
            <line x2="256" y1="-192" y2="-160" x1="96" />
            <line x2="96" y1="-32" y2="-32" x1="176" />
            <line x2="176" y1="-80" y2="-32" x1="176" />
            <line x2="96" y1="-32" y2="-32" x1="0" />
            <line x2="256" y1="-128" y2="-128" x1="320" />
            <line x2="96" y1="-96" y2="-96" x1="0" />
            <line x2="96" y1="-160" y2="-160" x1="0" />
        </blockdef>
        <block symbolname="obuft" name="XLXI_50">
            <blockpin signalname="XLXN_52" name="I" />
            <blockpin signalname="XLXN_61" name="T" />
            <blockpin signalname="nTRST" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_34">
            <blockpin signalname="FT_nTRST" name="I" />
            <blockpin signalname="XLXN_52" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_51">
            <blockpin signalname="ACBUS2" name="I" />
            <blockpin signalname="XLXN_61" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_106">
            <blockpin signalname="ACBUS2" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_107">
            <blockpin signalname="ACBUS3" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_7">
            <blockpin signalname="XLXN_50" name="I" />
            <blockpin signalname="FT_nSRST_IN" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_33">
            <blockpin signalname="FT_nSRST_OUT" name="I" />
            <blockpin signalname="XLXN_48" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_32">
            <blockpin signalname="ACBUS3" name="I" />
            <blockpin signalname="XLXN_47" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_48">
            <blockpin signalname="XLXN_48" name="I" />
            <blockpin signalname="XLXN_47" name="T" />
            <blockpin signalname="nSRST" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_49">
            <blockpin signalname="nSRST" name="I" />
            <blockpin signalname="XLXN_50" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_11">
            <blockpin signalname="XLXN_55" name="I" />
            <blockpin signalname="FT_RTCK" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_41">
            <blockpin signalname="RTCK" name="I" />
            <blockpin signalname="XLXN_55" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_30">
            <blockpin signalname="FT_TCK" name="I" />
            <blockpin signalname="XLXN_261" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_347">
            <blockpin signalname="XLXN_261" name="I" />
            <blockpin signalname="XLXN_262" name="T" />
            <blockpin signalname="TCK" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_350">
            <blockpin signalname="ACBUS6" name="I" />
            <blockpin signalname="XLXN_262" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_351">
            <blockpin signalname="ACBUS5" name="I" />
            <blockpin signalname="XLXN_266" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_352">
            <blockpin signalname="FT_TDI" name="I" />
            <blockpin signalname="XLXN_506" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_498">
            <blockpin signalname="ACBUS5" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_349">
            <blockpin signalname="XLXN_435" name="I" />
            <blockpin signalname="XLXN_437" name="T" />
            <blockpin signalname="TMS" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_348">
            <blockpin signalname="XLXN_506" name="I" />
            <blockpin signalname="XLXN_266" name="T" />
            <blockpin signalname="TDI" name="O" />
        </block>
        <block symbolname="m2_1" name="XLXI_516">
            <blockpin signalname="XLXN_506" name="D0" />
            <blockpin signalname="XLXN_439" name="D1" />
            <blockpin signalname="XLXN_440" name="S0" />
            <blockpin signalname="XLXN_435" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_354">
            <blockpin signalname="FT_TMS" name="I" />
            <blockpin signalname="XLXN_439" name="O" />
        </block>
        <block symbolname="m2_1" name="XLXI_517">
            <blockpin signalname="XLXN_442" name="D0" />
            <blockpin signalname="XLXN_443" name="D1" />
            <blockpin signalname="XLXN_440" name="S0" />
            <blockpin signalname="XLXN_444" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_523">
            <blockpin signalname="XLXN_444" name="I" />
            <blockpin signalname="FT_TDO" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_496">
            <blockpin signalname="ACBUS6" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_522">
            <blockpin signalname="TDO" name="I" />
            <blockpin signalname="XLXN_443" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_521">
            <blockpin signalname="TMS" name="I" />
            <blockpin signalname="XLXN_442" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_532">
            <blockpin signalname="ACBUS4" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_353">
            <blockpin signalname="ACBUS4" name="I" />
            <blockpin signalname="XLXN_437" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_520">
            <blockpin signalname="ADBUS5" name="I" />
            <blockpin signalname="XLXN_440" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="FT_nTRST">
            <wire x2="2416" y1="432" y2="432" x1="2176" />
        </branch>
        <branch name="nTRST">
            <wire x2="3008" y1="432" y2="432" x1="2928" />
        </branch>
        <instance x="2704" y="464" name="XLXI_50" orien="R0" />
        <branch name="XLXN_52">
            <wire x2="2704" y1="432" y2="432" x1="2640" />
        </branch>
        <instance x="2416" y="464" name="XLXI_34" orien="R0" />
        <branch name="XLXN_61">
            <wire x2="2688" y1="368" y2="368" x1="2640" />
            <wire x2="2704" y1="368" y2="368" x1="2688" />
        </branch>
        <instance x="2416" y="400" name="XLXI_51" orien="R0" />
        <branch name="ACBUS2">
            <wire x2="2336" y1="368" y2="368" x1="2176" />
            <wire x2="2416" y1="368" y2="368" x1="2336" />
        </branch>
        <instance x="2288" y="704" name="XLXI_107" orien="R0" />
        <instance x="2656" y="912" name="XLXI_7" orien="R180" />
        <instance x="2432" y="880" name="XLXI_33" orien="R0" />
        <instance x="2432" y="816" name="XLXI_32" orien="R0" />
        <instance x="2688" y="880" name="XLXI_48" orien="R0" />
        <instance x="2912" y="912" name="XLXI_49" orien="R180" />
        <instance x="2656" y="1104" name="XLXI_11" orien="R180" />
        <instance x="2912" y="1104" name="XLXI_41" orien="R180" />
        <branch name="XLXN_50">
            <wire x2="2688" y1="944" y2="944" x1="2656" />
        </branch>
        <branch name="XLXN_48">
            <wire x2="2688" y1="848" y2="848" x1="2656" />
        </branch>
        <branch name="XLXN_47">
            <wire x2="2688" y1="784" y2="784" x1="2656" />
        </branch>
        <branch name="nSRST">
            <wire x2="2928" y1="848" y2="848" x1="2912" />
            <wire x2="2992" y1="848" y2="848" x1="2928" />
            <wire x2="2928" y1="848" y2="944" x1="2928" />
            <wire x2="2928" y1="944" y2="944" x1="2912" />
        </branch>
        <branch name="FT_nSRST_OUT">
            <wire x2="2432" y1="848" y2="848" x1="2256" />
        </branch>
        <branch name="ACBUS3">
            <wire x2="2352" y1="784" y2="784" x1="2256" />
            <wire x2="2432" y1="784" y2="784" x1="2352" />
            <wire x2="2352" y1="704" y2="784" x1="2352" />
        </branch>
        <branch name="FT_nSRST_IN">
            <wire x2="2432" y1="944" y2="944" x1="2240" />
        </branch>
        <branch name="XLXN_55">
            <wire x2="2688" y1="1136" y2="1136" x1="2656" />
        </branch>
        <branch name="RTCK">
            <wire x2="2928" y1="1136" y2="1136" x1="2912" />
            <wire x2="3008" y1="1136" y2="1136" x1="2928" />
        </branch>
        <branch name="FT_RTCK">
            <wire x2="2432" y1="1136" y2="1136" x1="2224" />
        </branch>
        <branch name="TCK">
            <wire x2="1152" y1="384" y2="384" x1="1136" />
            <wire x2="1632" y1="384" y2="384" x1="1152" />
        </branch>
        <branch name="FT_TCK">
            <wire x2="544" y1="384" y2="384" x1="432" />
            <wire x2="560" y1="384" y2="384" x1="544" />
        </branch>
        <instance x="560" y="416" name="XLXI_30" orien="R0" />
        <instance x="912" y="416" name="XLXI_347" orien="R0" />
        <branch name="XLXN_261">
            <wire x2="912" y1="384" y2="384" x1="784" />
        </branch>
        <instance x="560" y="352" name="XLXI_350" orien="R0" />
        <branch name="XLXN_262">
            <wire x2="912" y1="320" y2="320" x1="784" />
        </branch>
        <branch name="ACBUS6">
            <wire x2="528" y1="320" y2="320" x1="448" />
            <wire x2="560" y1="320" y2="320" x1="528" />
            <wire x2="528" y1="272" y2="320" x1="528" />
        </branch>
        <branch name="TDI">
            <wire x2="1168" y1="720" y2="720" x1="1152" />
            <wire x2="1648" y1="720" y2="720" x1="1168" />
        </branch>
        <branch name="ACBUS5">
            <wire x2="544" y1="656" y2="656" x1="432" />
            <wire x2="576" y1="656" y2="656" x1="544" />
            <wire x2="544" y1="608" y2="656" x1="544" />
        </branch>
        <branch name="XLXN_266">
            <wire x2="928" y1="656" y2="656" x1="800" />
        </branch>
        <instance x="576" y="688" name="XLXI_351" orien="R0" />
        <instance x="576" y="752" name="XLXI_352" orien="R0" />
        <instance x="480" y="608" name="XLXI_498" orien="R0" />
        <branch name="FT_TMS">
            <wire x2="560" y1="1120" y2="1120" x1="432" />
        </branch>
        <branch name="TMS">
            <wire x2="1568" y1="1520" y2="1520" x1="1456" />
            <wire x2="1568" y1="1088" y2="1088" x1="1504" />
            <wire x2="1568" y1="1088" y2="1520" x1="1568" />
            <wire x2="1664" y1="1088" y2="1088" x1="1568" />
        </branch>
        <instance x="1280" y="1120" name="XLXI_349" orien="R0" />
        <branch name="XLXN_435">
            <wire x2="1280" y1="1088" y2="1088" x1="1216" />
        </branch>
        <instance x="928" y="752" name="XLXI_348" orien="R0" />
        <instance x="896" y="1216" name="XLXI_516" orien="R0" />
        <instance x="560" y="1152" name="XLXI_354" orien="R0" />
        <branch name="XLXN_439">
            <wire x2="896" y1="1120" y2="1120" x1="784" />
        </branch>
        <branch name="XLXN_440">
            <wire x2="896" y1="1232" y2="1232" x1="784" />
            <wire x2="1120" y1="1232" y2="1232" x1="896" />
            <wire x2="1120" y1="1232" y2="1392" x1="1120" />
            <wire x2="896" y1="1184" y2="1232" x1="896" />
        </branch>
        <branch name="ADBUS5">
            <wire x2="560" y1="1232" y2="1232" x1="448" />
        </branch>
        <text style="fontsize:40;fontname:Arial" x="1608" y="1160">TMS/SWDIO</text>
        <instance x="1120" y="1360" name="XLXI_517" orien="R180" />
        <branch name="XLXN_444">
            <wire x2="784" y1="1488" y2="1488" x1="768" />
            <wire x2="800" y1="1488" y2="1488" x1="784" />
        </branch>
        <instance x="768" y="1456" name="XLXI_523" orien="R180" />
        <branch name="TDO">
            <wire x2="1472" y1="1600" y2="1600" x1="1456" />
            <wire x2="1632" y1="1600" y2="1600" x1="1472" />
        </branch>
        <branch name="FT_TDO">
            <wire x2="528" y1="1488" y2="1488" x1="432" />
            <wire x2="544" y1="1488" y2="1488" x1="528" />
        </branch>
        <branch name="XLXN_437">
            <wire x2="1280" y1="1008" y2="1008" x1="784" />
            <wire x2="1280" y1="1008" y2="1024" x1="1280" />
        </branch>
        <branch name="ACBUS4">
            <wire x2="496" y1="1008" y2="1008" x1="448" />
            <wire x2="560" y1="1008" y2="1008" x1="496" />
            <wire x2="496" y1="944" y2="1008" x1="496" />
        </branch>
        <instance x="464" y="272" name="XLXI_496" orien="R0" />
        <branch name="XLXN_442">
            <wire x2="1232" y1="1520" y2="1520" x1="1120" />
        </branch>
        <instance x="1456" y="1568" name="XLXI_522" orien="R180" />
        <branch name="XLXN_443">
            <wire x2="1136" y1="1456" y2="1456" x1="1120" />
            <wire x2="1136" y1="1456" y2="1600" x1="1136" />
            <wire x2="1232" y1="1600" y2="1600" x1="1136" />
        </branch>
        <instance x="1456" y="1488" name="XLXI_521" orien="R180" />
        <instance x="432" y="944" name="XLXI_532" orien="R0" />
        <instance x="560" y="1040" name="XLXI_353" orien="R0" />
        <instance x="560" y="1264" name="XLXI_520" orien="R0" />
        <text style="fontsize:40;fontname:Arial" x="1532" y="448">TCK/SWCLK</text>
        <iomarker fontsize="28" x="3008" y="432" name="nTRST" orien="R0" />
        <iomarker fontsize="28" x="2176" y="432" name="FT_nTRST" orien="R180" />
        <iomarker fontsize="28" x="2176" y="368" name="ACBUS2" orien="R180" />
        <iomarker fontsize="28" x="2240" y="944" name="FT_nSRST_IN" orien="R180" />
        <iomarker fontsize="28" x="2256" y="848" name="FT_nSRST_OUT" orien="R180" />
        <iomarker fontsize="28" x="2256" y="784" name="ACBUS3" orien="R180" />
        <iomarker fontsize="28" x="2992" y="848" name="nSRST" orien="R0" />
        <iomarker fontsize="28" x="2224" y="1136" name="FT_RTCK" orien="R180" />
        <iomarker fontsize="28" x="432" y="656" name="ACBUS5" orien="R180" />
        <iomarker fontsize="28" x="432" y="1120" name="FT_TMS" orien="R180" />
        <iomarker fontsize="28" x="448" y="1232" name="ADBUS5" orien="R180" />
        <iomarker fontsize="28" x="448" y="1008" name="ACBUS4" orien="R180" />
        <iomarker fontsize="28" x="1664" y="1088" name="TMS" orien="R0" />
        <iomarker fontsize="28" x="1632" y="1600" name="TDO" orien="R0" />
        <iomarker fontsize="28" x="1648" y="720" name="TDI" orien="R0" />
        <iomarker fontsize="28" x="1632" y="384" name="TCK" orien="R0" />
        <iomarker fontsize="28" x="432" y="1488" name="FT_TDO" orien="R180" />
        <iomarker fontsize="28" x="3008" y="1136" name="RTCK" orien="R0" />
        <iomarker fontsize="28" x="432" y="384" name="FT_TCK" orien="R180" />
        <iomarker fontsize="28" x="448" y="320" name="ACBUS6" orien="R180" />
        <instance x="2272" y="368" name="XLXI_106" orien="R0" />
        <branch name="FT_TDI">
            <wire x2="560" y1="720" y2="720" x1="448" />
            <wire x2="576" y1="720" y2="720" x1="560" />
        </branch>
        <iomarker fontsize="28" x="448" y="720" name="FT_TDI" orien="R180" />
        <branch name="XLXN_506">
            <wire x2="816" y1="720" y2="720" x1="800" />
            <wire x2="928" y1="720" y2="720" x1="816" />
            <wire x2="816" y1="720" y2="1056" x1="816" />
            <wire x2="896" y1="1056" y2="1056" x1="816" />
        </branch>
    </sheet>
</drawing>