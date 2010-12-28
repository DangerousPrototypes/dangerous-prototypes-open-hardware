<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="acr2" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="FT_nSRST_IN" />
        <signal name="FT_TDO" />
        <signal name="FT_RTCK" />
        <signal name="FT_JTAG_BUF" />
        <signal name="FT_TMS" />
        <signal name="FT_TCK" />
        <signal name="FT_DBGRQ" />
        <signal name="FT_nSRST_BUF" />
        <signal name="FT_nSRST_OUT" />
        <signal name="FT_nTRST" />
        <signal name="nSRST" />
        <signal name="nTRST" />
        <signal name="TDO" />
        <signal name="RTCK" />
        <signal name="FT_TDI" />
        <signal name="TDI" />
        <signal name="TCK" />
        <signal name="DBGRQ" />
        <signal name="TMS" />
        <signal name="XLXN_39" />
        <signal name="XLXN_41" />
        <signal name="XLXN_43" />
        <signal name="XLXN_44" />
        <signal name="XLXN_45" />
        <signal name="XLXN_47" />
        <signal name="XLXN_48" />
        <signal name="XLXN_50" />
        <signal name="XLXN_52" />
        <signal name="XLXN_54" />
        <signal name="XLXN_55" />
        <signal name="XLXN_57" />
        <signal name="XLXN_59" />
        <signal name="XLXN_61" />
        <signal name="FT_nTRST_BUF" />
        <port polarity="Output" name="FT_nSRST_IN" />
        <port polarity="Output" name="FT_TDO" />
        <port polarity="Output" name="FT_RTCK" />
        <port polarity="Input" name="FT_JTAG_BUF" />
        <port polarity="Input" name="FT_TMS" />
        <port polarity="Input" name="FT_TCK" />
        <port polarity="Input" name="FT_DBGRQ" />
        <port polarity="Input" name="FT_nSRST_BUF" />
        <port polarity="Input" name="FT_nSRST_OUT" />
        <port polarity="Input" name="FT_nTRST" />
        <port polarity="BiDirectional" name="nSRST" />
        <port polarity="Output" name="nTRST" />
        <port polarity="Input" name="TDO" />
        <port polarity="Input" name="RTCK" />
        <port polarity="Input" name="FT_TDI" />
        <port polarity="Output" name="TDI" />
        <port polarity="Output" name="TCK" />
        <port polarity="Output" name="DBGRQ" />
        <port polarity="Output" name="TMS" />
        <port polarity="Input" name="FT_nTRST_BUF" />
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
        <block symbolname="ibuf" name="XLXI_41">
            <blockpin signalname="RTCK" name="I" />
            <blockpin signalname="XLXN_55" name="O" />
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
        <block symbolname="ibuf" name="XLXI_49">
            <blockpin signalname="nSRST" name="I" />
            <blockpin signalname="XLXN_50" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_48">
            <blockpin signalname="XLXN_48" name="I" />
            <blockpin signalname="XLXN_47" name="T" />
            <blockpin signalname="nSRST" name="O" />
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
        <block symbolname="ibuf" name="XLXI_34">
            <blockpin signalname="FT_nTRST" name="I" />
            <blockpin signalname="XLXN_52" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_40">
            <blockpin signalname="TDO" name="I" />
            <blockpin signalname="XLXN_54" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_8">
            <blockpin signalname="XLXN_54" name="I" />
            <blockpin signalname="FT_TDO" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_11">
            <blockpin signalname="XLXN_55" name="I" />
            <blockpin signalname="FT_RTCK" name="O" />
        </block>
        <block symbolname="obuft" name="XLXI_50">
            <blockpin signalname="XLXN_52" name="I" />
            <blockpin signalname="XLXN_61" name="T" />
            <blockpin signalname="nTRST" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_51">
            <blockpin signalname="FT_nTRST_BUF" name="I" />
            <blockpin signalname="XLXN_61" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="FT_nSRST_IN">
            <wire x2="464" y1="672" y2="672" x1="272" />
        </branch>
        <branch name="FT_TDO">
            <wire x2="480" y1="944" y2="944" x1="272" />
        </branch>
        <branch name="FT_RTCK">
            <wire x2="464" y1="1056" y2="1056" x1="272" />
            <wire x2="480" y1="1056" y2="1056" x1="464" />
        </branch>
        <branch name="FT_JTAG_BUF">
            <wire x2="448" y1="128" y2="128" x1="288" />
        </branch>
        <branch name="FT_TMS">
            <wire x2="448" y1="256" y2="256" x1="288" />
        </branch>
        <branch name="FT_TCK">
            <wire x2="448" y1="320" y2="320" x1="288" />
        </branch>
        <branch name="FT_DBGRQ">
            <wire x2="448" y1="384" y2="384" x1="288" />
        </branch>
        <branch name="FT_nSRST_BUF">
            <wire x2="464" y1="512" y2="512" x1="288" />
        </branch>
        <branch name="FT_nSRST_OUT">
            <wire x2="464" y1="576" y2="576" x1="288" />
        </branch>
        <branch name="FT_nTRST">
            <wire x2="496" y1="848" y2="848" x1="272" />
            <wire x2="512" y1="848" y2="848" x1="496" />
        </branch>
        <instance x="960" y="1024" name="XLXI_41" orien="R180" />
        <branch name="nSRST">
            <wire x2="960" y1="576" y2="576" x1="944" />
            <wire x2="1024" y1="576" y2="576" x1="960" />
            <wire x2="960" y1="576" y2="672" x1="960" />
            <wire x2="960" y1="672" y2="672" x1="944" />
        </branch>
        <branch name="nTRST">
            <wire x2="1104" y1="848" y2="848" x1="1024" />
        </branch>
        <branch name="TDO">
            <wire x2="976" y1="944" y2="944" x1="960" />
            <wire x2="992" y1="944" y2="944" x1="976" />
        </branch>
        <branch name="RTCK">
            <wire x2="992" y1="1056" y2="1056" x1="960" />
        </branch>
        <branch name="FT_TDI">
            <wire x2="448" y1="192" y2="192" x1="256" />
        </branch>
        <instance x="704" y="416" name="XLXI_46" orien="R0" />
        <branch name="TDI">
            <wire x2="960" y1="192" y2="192" x1="928" />
        </branch>
        <branch name="TCK">
            <wire x2="960" y1="320" y2="320" x1="928" />
        </branch>
        <branch name="DBGRQ">
            <wire x2="960" y1="384" y2="384" x1="928" />
        </branch>
        <branch name="TMS">
            <wire x2="960" y1="256" y2="256" x1="928" />
        </branch>
        <instance x="944" y="640" name="XLXI_49" orien="R180" />
        <instance x="720" y="608" name="XLXI_48" orien="R0" />
        <branch name="XLXN_39">
            <wire x2="704" y1="128" y2="128" x1="672" />
        </branch>
        <instance x="448" y="160" name="XLXI_28" orien="R0" />
        <branch name="XLXN_41">
            <wire x2="704" y1="192" y2="192" x1="672" />
        </branch>
        <instance x="448" y="224" name="XLXI_27" orien="R0" />
        <branch name="XLXN_43">
            <wire x2="704" y1="256" y2="256" x1="672" />
        </branch>
        <instance x="448" y="288" name="XLXI_29" orien="R0" />
        <branch name="XLXN_44">
            <wire x2="704" y1="320" y2="320" x1="672" />
        </branch>
        <instance x="448" y="352" name="XLXI_30" orien="R0" />
        <branch name="XLXN_45">
            <wire x2="704" y1="384" y2="384" x1="672" />
        </branch>
        <instance x="448" y="416" name="XLXI_31" orien="R0" />
        <branch name="XLXN_47">
            <wire x2="720" y1="512" y2="512" x1="688" />
        </branch>
        <instance x="464" y="544" name="XLXI_32" orien="R0" />
        <branch name="XLXN_48">
            <wire x2="720" y1="576" y2="576" x1="688" />
        </branch>
        <instance x="464" y="608" name="XLXI_33" orien="R0" />
        <branch name="XLXN_50">
            <wire x2="720" y1="672" y2="672" x1="688" />
        </branch>
        <instance x="688" y="640" name="XLXI_7" orien="R180" />
        <instance x="960" y="912" name="XLXI_40" orien="R180" />
        <branch name="XLXN_54">
            <wire x2="736" y1="944" y2="944" x1="704" />
        </branch>
        <instance x="704" y="912" name="XLXI_8" orien="R180" />
        <branch name="XLXN_55">
            <wire x2="736" y1="1056" y2="1056" x1="704" />
        </branch>
        <instance x="704" y="1024" name="XLXI_11" orien="R180" />
        <iomarker fontsize="28" x="1024" y="576" name="nSRST" orien="R0" />
        <iomarker fontsize="28" x="992" y="944" name="TDO" orien="R0" />
        <iomarker fontsize="28" x="992" y="1056" name="RTCK" orien="R0" />
        <iomarker fontsize="28" x="960" y="192" name="TDI" orien="R0" />
        <iomarker fontsize="28" x="960" y="320" name="TCK" orien="R0" />
        <iomarker fontsize="28" x="960" y="384" name="DBGRQ" orien="R0" />
        <iomarker fontsize="28" x="960" y="256" name="TMS" orien="R0" />
        <iomarker fontsize="28" x="288" y="128" name="FT_JTAG_BUF" orien="R180" />
        <iomarker fontsize="28" x="256" y="192" name="FT_TDI" orien="R180" />
        <iomarker fontsize="28" x="288" y="256" name="FT_TMS" orien="R180" />
        <iomarker fontsize="28" x="288" y="320" name="FT_TCK" orien="R180" />
        <iomarker fontsize="28" x="288" y="384" name="FT_DBGRQ" orien="R180" />
        <iomarker fontsize="28" x="288" y="512" name="FT_nSRST_BUF" orien="R180" />
        <iomarker fontsize="28" x="288" y="576" name="FT_nSRST_OUT" orien="R180" />
        <iomarker fontsize="28" x="272" y="672" name="FT_nSRST_IN" orien="R180" />
        <iomarker fontsize="28" x="272" y="944" name="FT_TDO" orien="R180" />
        <iomarker fontsize="28" x="272" y="1056" name="FT_RTCK" orien="R180" />
        <iomarker fontsize="28" x="1104" y="848" name="nTRST" orien="R0" />
        <instance x="800" y="880" name="XLXI_50" orien="R0" />
        <branch name="XLXN_52">
            <wire x2="800" y1="848" y2="848" x1="736" />
        </branch>
        <instance x="512" y="880" name="XLXI_34" orien="R0" />
        <iomarker fontsize="28" x="272" y="848" name="FT_nTRST" orien="R180" />
        <branch name="XLXN_61">
            <wire x2="800" y1="784" y2="784" x1="736" />
        </branch>
        <instance x="512" y="816" name="XLXI_51" orien="R0" />
        <branch name="FT_nTRST_BUF">
            <wire x2="496" y1="784" y2="784" x1="272" />
            <wire x2="512" y1="784" y2="784" x1="496" />
        </branch>
        <iomarker fontsize="28" x="272" y="784" name="FT_nTRST_BUF" orien="R180" />
    </sheet>
</drawing>