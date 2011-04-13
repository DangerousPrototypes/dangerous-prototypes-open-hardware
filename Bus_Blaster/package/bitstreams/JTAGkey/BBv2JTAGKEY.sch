<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="acr2" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="ACBUS6" />
        <signal name="ACBUS7" />
        <signal name="FT_nSRST_IN" />
        <signal name="FT_nSRST_BUF" />
        <signal name="FT_nSRST_OUT" />
        <signal name="nSRST" />
        <signal name="XLXN_47" />
        <signal name="XLXN_48" />
        <signal name="XLXN_50" />
        <signal name="FT_nTRST" />
        <signal name="nTRST" />
        <signal name="XLXN_52" />
        <signal name="XLXN_61" />
        <signal name="FT_nTRST_BUF" />
        <signal name="FT_TDO" />
        <signal name="FT_RTCK" />
        <signal name="TDO" />
        <signal name="RTCK" />
        <signal name="XLXN_54" />
        <signal name="XLXN_55" />
        <signal name="XLXN_62" />
        <signal name="XLXN_63" />
        <signal name="FT_DBGACK" />
        <signal name="FT_TARGET_PRESENT" />
        <signal name="DBGACK" />
        <signal name="TARGET_PRESENT" />
        <signal name="FT_JTAG_BUF" />
        <signal name="FT_TMS" />
        <signal name="FT_TCK" />
        <signal name="FT_DBGRQ" />
        <signal name="FT_TDI" />
        <signal name="TDI" />
        <signal name="TCK" />
        <signal name="DBGRQ" />
        <signal name="TMS" />
        <signal name="XLXN_41" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_39" />
        <signal name="XLXN_64" />
        <port polarity="Input" name="ACBUS6" />
        <port polarity="Input" name="ACBUS7" />
        <port polarity="Output" name="FT_nSRST_IN" />
        <port polarity="Input" name="FT_nSRST_BUF" />
        <port polarity="Input" name="FT_nSRST_OUT" />
        <port polarity="BiDirectional" name="nSRST" />
        <port polarity="Input" name="FT_nTRST" />
        <port polarity="Output" name="nTRST" />
        <port polarity="Input" name="FT_nTRST_BUF" />
        <port polarity="Output" name="FT_TDO" />
        <port polarity="Output" name="FT_RTCK" />
        <port polarity="Input" name="TDO" />
        <port polarity="Input" name="RTCK" />
        <port polarity="Output" name="FT_DBGACK" />
        <port polarity="Output" name="FT_TARGET_PRESENT" />
        <port polarity="Input" name="DBGACK" />
        <port polarity="Input" name="TARGET_PRESENT" />
        <port polarity="Input" name="FT_JTAG_BUF" />
        <port polarity="Input" name="FT_TMS" />
        <port polarity="Input" name="FT_TCK" />
        <port polarity="Input" name="FT_DBGRQ" />
        <port polarity="Input" name="FT_TDI" />
        <port polarity="Output" name="TDI" />
        <port polarity="Output" name="TCK" />
        <port polarity="Output" name="DBGRQ" />
        <port polarity="Output" name="TMS" />
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
        <blockdef name="obuft4">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-288" y2="-288" x1="0" />
            <line x2="64" y1="-256" y2="-192" x1="64" />
            <line x2="64" y1="-224" y2="-256" x1="128" />
            <line x2="128" y1="-192" y2="-224" x1="64" />
            <line x2="64" y1="-192" y2="-128" x1="64" />
            <line x2="64" y1="-160" y2="-192" x1="128" />
            <line x2="128" y1="-128" y2="-160" x1="64" />
            <line x2="64" y1="-224" y2="-224" x1="0" />
            <line x2="128" y1="-224" y2="-224" x1="224" />
            <line x2="64" y1="-160" y2="-160" x1="0" />
            <line x2="128" y1="-160" y2="-160" x1="224" />
            <line x2="64" y1="-64" y2="0" x1="64" />
            <line x2="64" y1="-32" y2="-64" x1="128" />
            <line x2="128" y1="0" y2="-32" x1="64" />
            <line x2="64" y1="-32" y2="-32" x1="0" />
            <line x2="128" y1="-32" y2="-32" x1="224" />
            <line x2="128" y1="-96" y2="-96" x1="224" />
            <line x2="64" y1="-96" y2="-96" x1="0" />
            <line x2="64" y1="-128" y2="-64" x1="64" />
            <line x2="64" y1="-96" y2="-128" x1="128" />
            <line x2="128" y1="-64" y2="-96" x1="64" />
            <line x2="64" y1="-288" y2="-288" x1="96" />
            <line x2="96" y1="-240" y2="-288" x1="96" />
            <line x2="96" y1="-176" y2="-208" x1="96" />
            <line x2="96" y1="-112" y2="-144" x1="96" />
            <line x2="96" y1="-48" y2="-80" x1="96" />
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
        <block symbolname="ibuf" name="XLXI_56">
            <blockpin signalname="ACBUS6" name="I" />
            <blockpin name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_57">
            <blockpin signalname="ACBUS7" name="I" />
            <blockpin name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_49">
            <blockpin signalname="nSRST" name="I" />
            <blockpin signalname="XLXN_50" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_48">
            <blockpin signalname="XLXN_48" name="I" />
            <blockpin signalname="XLXN_47" name="T" />
            <blockpin signalname="nSRST" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_32">
            <blockpin signalname="FT_nSRST_BUF" name="I" />
            <blockpin signalname="XLXN_47" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_33">
            <blockpin signalname="FT_nSRST_OUT" name="I" />
            <blockpin signalname="XLXN_48" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_7">
            <blockpin signalname="XLXN_50" name="I" />
            <blockpin signalname="FT_nSRST_IN" name="O" />
        </block>
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
            <blockpin signalname="FT_nTRST_BUF" name="I" />
            <blockpin signalname="XLXN_61" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_106">
            <blockpin signalname="FT_nTRST_BUF" name="O" />
        </block>
        <block symbolname="pullup" name="XLXI_107">
            <blockpin signalname="FT_nSRST_BUF" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_41">
            <blockpin signalname="RTCK" name="I" />
            <blockpin signalname="XLXN_55" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_11">
            <blockpin signalname="XLXN_55" name="I" />
            <blockpin signalname="FT_RTCK" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_52">
            <blockpin signalname="XLXN_63" name="I" />
            <blockpin signalname="FT_DBGACK" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_53">
            <blockpin signalname="XLXN_62" name="I" />
            <blockpin signalname="FT_TARGET_PRESENT" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_54">
            <blockpin signalname="TARGET_PRESENT" name="I" />
            <blockpin signalname="XLXN_62" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_55">
            <blockpin signalname="DBGACK" name="I" />
            <blockpin signalname="XLXN_63" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_8">
            <blockpin signalname="XLXN_54" name="I" />
            <blockpin signalname="FT_TDO" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_40">
            <blockpin signalname="TDO" name="I" />
            <blockpin signalname="XLXN_54" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_28">
            <blockpin signalname="FT_JTAG_BUF" name="I" />
            <blockpin signalname="XLXN_39" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_27">
            <blockpin signalname="FT_TDI" name="I" />
            <blockpin signalname="XLXN_41" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_29">
            <blockpin signalname="FT_TMS" name="I" />
            <blockpin signalname="XLXN_43" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_30">
            <blockpin signalname="FT_TCK" name="I" />
            <blockpin signalname="XLXN_44" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_31">
            <blockpin signalname="FT_DBGRQ" name="I" />
            <blockpin signalname="XLXN_45" name="O" />
        </block>
        <block symbolname="obuft4" name="XLXI_46">
            <blockpin signalname="XLXN_41" name="I0" />
            <blockpin signalname="XLXN_43" name="I1" />
            <blockpin signalname="XLXN_44" name="I2" />
            <blockpin signalname="XLXN_45" name="I3" />
            <blockpin signalname="XLXN_39" name="T" />
            <blockpin signalname="TDI" name="O0" />
            <blockpin signalname="TMS" name="O1" />
            <blockpin signalname="TCK" name="O2" />
            <blockpin signalname="DBGRQ" name="O3" />
        </block>
        <block symbolname="pullup" name="XLXI_172">
            <blockpin signalname="FT_JTAG_BUF" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <instance x="496" y="1568" name="XLXI_56" orien="R0" />
        <instance x="496" y="1680" name="XLXI_57" orien="R0" />
        <branch name="ACBUS6">
            <wire x2="496" y1="1536" y2="1536" x1="464" />
        </branch>
        <iomarker fontsize="28" x="464" y="1536" name="ACBUS6" orien="R180" />
        <branch name="ACBUS7">
            <wire x2="496" y1="1648" y2="1648" x1="464" />
        </branch>
        <iomarker fontsize="28" x="464" y="1648" name="ACBUS7" orien="R180" />
        <branch name="FT_nSRST_IN">
            <wire x2="2176" y1="992" y2="992" x1="1984" />
        </branch>
        <branch name="FT_nSRST_BUF">
            <wire x2="2096" y1="832" y2="832" x1="2000" />
            <wire x2="2176" y1="832" y2="832" x1="2096" />
            <wire x2="2096" y1="752" y2="832" x1="2096" />
        </branch>
        <branch name="FT_nSRST_OUT">
            <wire x2="2176" y1="896" y2="896" x1="2000" />
        </branch>
        <branch name="nSRST">
            <wire x2="2672" y1="896" y2="896" x1="2656" />
            <wire x2="2736" y1="896" y2="896" x1="2672" />
            <wire x2="2672" y1="896" y2="992" x1="2672" />
            <wire x2="2672" y1="992" y2="992" x1="2656" />
        </branch>
        <instance x="2656" y="960" name="XLXI_49" orien="R180" />
        <instance x="2432" y="928" name="XLXI_48" orien="R0" />
        <branch name="XLXN_47">
            <wire x2="2432" y1="832" y2="832" x1="2400" />
        </branch>
        <instance x="2176" y="864" name="XLXI_32" orien="R0" />
        <branch name="XLXN_48">
            <wire x2="2432" y1="896" y2="896" x1="2400" />
        </branch>
        <instance x="2176" y="928" name="XLXI_33" orien="R0" />
        <branch name="XLXN_50">
            <wire x2="2432" y1="992" y2="992" x1="2400" />
        </branch>
        <instance x="2400" y="960" name="XLXI_7" orien="R180" />
        <iomarker fontsize="28" x="2736" y="896" name="nSRST" orien="R0" />
        <iomarker fontsize="28" x="2000" y="832" name="FT_nSRST_BUF" orien="R180" />
        <iomarker fontsize="28" x="2000" y="896" name="FT_nSRST_OUT" orien="R180" />
        <iomarker fontsize="28" x="1984" y="992" name="FT_nSRST_IN" orien="R180" />
        <branch name="FT_nTRST">
            <wire x2="2112" y1="432" y2="432" x1="1888" />
            <wire x2="2128" y1="432" y2="432" x1="2112" />
        </branch>
        <branch name="nTRST">
            <wire x2="2720" y1="432" y2="432" x1="2640" />
        </branch>
        <instance x="2416" y="464" name="XLXI_50" orien="R0" />
        <branch name="XLXN_52">
            <wire x2="2416" y1="432" y2="432" x1="2352" />
        </branch>
        <instance x="2128" y="464" name="XLXI_34" orien="R0" />
        <branch name="XLXN_61">
            <wire x2="2416" y1="368" y2="368" x1="2352" />
        </branch>
        <instance x="2128" y="400" name="XLXI_51" orien="R0" />
        <branch name="FT_nTRST_BUF">
            <wire x2="2048" y1="368" y2="368" x1="1888" />
            <wire x2="2128" y1="368" y2="368" x1="2048" />
            <wire x2="2048" y1="256" y2="368" x1="2048" />
        </branch>
        <iomarker fontsize="28" x="2720" y="432" name="nTRST" orien="R0" />
        <iomarker fontsize="28" x="1888" y="432" name="FT_nTRST" orien="R180" />
        <iomarker fontsize="28" x="1888" y="368" name="FT_nTRST_BUF" orien="R180" />
        <instance x="944" y="896" name="XLXI_41" orien="R180" />
        <instance x="688" y="896" name="XLXI_11" orien="R180" />
        <instance x="688" y="992" name="XLXI_52" orien="R180" />
        <instance x="688" y="1104" name="XLXI_53" orien="R180" />
        <instance x="944" y="1104" name="XLXI_54" orien="R180" />
        <instance x="944" y="992" name="XLXI_55" orien="R180" />
        <instance x="688" y="784" name="XLXI_8" orien="R180" />
        <instance x="944" y="784" name="XLXI_40" orien="R180" />
        <branch name="FT_TDO">
            <wire x2="464" y1="816" y2="816" x1="256" />
        </branch>
        <branch name="FT_RTCK">
            <wire x2="448" y1="928" y2="928" x1="256" />
            <wire x2="464" y1="928" y2="928" x1="448" />
        </branch>
        <branch name="TDO">
            <wire x2="960" y1="816" y2="816" x1="944" />
            <wire x2="976" y1="816" y2="816" x1="960" />
        </branch>
        <branch name="RTCK">
            <wire x2="976" y1="928" y2="928" x1="944" />
        </branch>
        <branch name="XLXN_54">
            <wire x2="720" y1="816" y2="816" x1="688" />
        </branch>
        <branch name="XLXN_55">
            <wire x2="720" y1="928" y2="928" x1="688" />
        </branch>
        <branch name="XLXN_62">
            <wire x2="720" y1="1136" y2="1136" x1="688" />
        </branch>
        <branch name="XLXN_63">
            <wire x2="720" y1="1024" y2="1024" x1="688" />
        </branch>
        <branch name="FT_DBGACK">
            <wire x2="464" y1="1024" y2="1024" x1="432" />
        </branch>
        <branch name="FT_TARGET_PRESENT">
            <wire x2="464" y1="1136" y2="1136" x1="432" />
        </branch>
        <branch name="DBGACK">
            <wire x2="976" y1="1024" y2="1024" x1="944" />
        </branch>
        <branch name="TARGET_PRESENT">
            <wire x2="976" y1="1136" y2="1136" x1="944" />
        </branch>
        <iomarker fontsize="28" x="256" y="928" name="FT_RTCK" orien="R180" />
        <iomarker fontsize="28" x="976" y="816" name="TDO" orien="R0" />
        <iomarker fontsize="28" x="976" y="928" name="RTCK" orien="R0" />
        <iomarker fontsize="28" x="256" y="816" name="FT_TDO" orien="R180" />
        <iomarker fontsize="28" x="432" y="1024" name="FT_DBGACK" orien="R180" />
        <iomarker fontsize="28" x="432" y="1136" name="FT_TARGET_PRESENT" orien="R180" />
        <iomarker fontsize="28" x="976" y="1024" name="DBGACK" orien="R0" />
        <iomarker fontsize="28" x="976" y="1136" name="TARGET_PRESENT" orien="R0" />
        <branch name="FT_JTAG_BUF">
            <wire x2="384" y1="288" y2="288" x1="320" />
            <wire x2="480" y1="288" y2="288" x1="384" />
            <wire x2="384" y1="224" y2="288" x1="384" />
        </branch>
        <branch name="FT_TMS">
            <wire x2="480" y1="416" y2="416" x1="320" />
        </branch>
        <branch name="FT_TCK">
            <wire x2="480" y1="480" y2="480" x1="320" />
        </branch>
        <branch name="FT_DBGRQ">
            <wire x2="480" y1="544" y2="544" x1="320" />
        </branch>
        <branch name="FT_TDI">
            <wire x2="480" y1="352" y2="352" x1="288" />
        </branch>
        <branch name="TDI">
            <wire x2="976" y1="352" y2="352" x1="960" />
            <wire x2="992" y1="352" y2="352" x1="976" />
        </branch>
        <branch name="TCK">
            <wire x2="976" y1="480" y2="480" x1="960" />
            <wire x2="992" y1="480" y2="480" x1="976" />
        </branch>
        <branch name="DBGRQ">
            <wire x2="976" y1="544" y2="544" x1="960" />
            <wire x2="992" y1="544" y2="544" x1="976" />
        </branch>
        <branch name="TMS">
            <wire x2="976" y1="416" y2="416" x1="960" />
            <wire x2="992" y1="416" y2="416" x1="976" />
        </branch>
        <instance x="480" y="320" name="XLXI_28" orien="R0" />
        <branch name="XLXN_41">
            <wire x2="720" y1="352" y2="352" x1="704" />
            <wire x2="736" y1="352" y2="352" x1="720" />
        </branch>
        <instance x="480" y="384" name="XLXI_27" orien="R0" />
        <branch name="XLXN_43">
            <wire x2="720" y1="416" y2="416" x1="704" />
            <wire x2="736" y1="416" y2="416" x1="720" />
        </branch>
        <instance x="480" y="448" name="XLXI_29" orien="R0" />
        <branch name="XLXN_44">
            <wire x2="720" y1="480" y2="480" x1="704" />
            <wire x2="736" y1="480" y2="480" x1="720" />
        </branch>
        <instance x="480" y="512" name="XLXI_30" orien="R0" />
        <branch name="XLXN_45">
            <wire x2="720" y1="544" y2="544" x1="704" />
            <wire x2="736" y1="544" y2="544" x1="720" />
        </branch>
        <instance x="480" y="576" name="XLXI_31" orien="R0" />
        <branch name="XLXN_39">
            <wire x2="720" y1="288" y2="288" x1="704" />
            <wire x2="736" y1="288" y2="288" x1="720" />
        </branch>
        <instance x="736" y="576" name="XLXI_46" orien="R0" />
        <iomarker fontsize="28" x="992" y="352" name="TDI" orien="R0" />
        <iomarker fontsize="28" x="992" y="480" name="TCK" orien="R0" />
        <iomarker fontsize="28" x="992" y="544" name="DBGRQ" orien="R0" />
        <iomarker fontsize="28" x="992" y="416" name="TMS" orien="R0" />
        <iomarker fontsize="28" x="320" y="288" name="FT_JTAG_BUF" orien="R180" />
        <iomarker fontsize="28" x="288" y="352" name="FT_TDI" orien="R180" />
        <iomarker fontsize="28" x="320" y="416" name="FT_TMS" orien="R180" />
        <iomarker fontsize="28" x="320" y="480" name="FT_TCK" orien="R180" />
        <iomarker fontsize="28" x="320" y="544" name="FT_DBGRQ" orien="R180" />
        <instance x="320" y="224" name="XLXI_172" orien="R0" />
        <instance x="1984" y="256" name="XLXI_106" orien="R0" />
        <instance x="2032" y="752" name="XLXI_107" orien="R0" />
    </sheet>
</drawing>