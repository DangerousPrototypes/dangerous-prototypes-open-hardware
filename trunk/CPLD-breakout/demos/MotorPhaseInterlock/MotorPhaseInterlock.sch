<?xml version="1.0" encoding="UTF-8"?>
<drawing version="7">
    <attr value="xbr" name="DeviceFamilyName">
        <trait delete="all:0" />
        <trait editname="all:0" />
        <trait edittrait="all:0" />
    </attr>
    <netlist>
        <signal name="XLXN_7" />
        <signal name="XLXN_309" />
        <signal name="XLXN_4" />
        <signal name="BPWM2">
            <attr value="P22" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="BPWM4">
            <attr value="P20" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="BPWM5">
            <attr value="P26" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="BPWM6">
            <attr value="P19" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN1">
            <attr value="P43" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN2">
            <attr value="P2" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN3">
            <attr value="P44" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN4">
            <attr value="P3" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN5">
            <attr value="P1" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="PWMIN6">
            <attr value="P4" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="BPWM1">
            <attr value="P28" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="XLXN_322" />
        <signal name="XLXN_1" />
        <signal name="XLXN_21" />
        <signal name="BPWM3">
            <attr value="P27" name="LOC">
                <trait verilog="all:0 wsynth:1" />
                <trait vhdl="all:0 wa:1 wd:1" />
            </attr>
        </signal>
        <signal name="XLXN_176" />
        <signal name="XLXN_23" />
        <signal name="XLXN_180" />
        <signal name="XLXN_181" />
        <signal name="XLXN_213" />
        <signal name="XLXN_331" />
        <signal name="XLXN_246" />
        <signal name="XLXN_333" />
        <signal name="XLXN_159" />
        <signal name="XLXN_335" />
        <signal name="XLXN_248" />
        <signal name="XLXN_252" />
        <signal name="XLXN_253" />
        <signal name="XLXN_254" />
        <port polarity="Output" name="BPWM2" />
        <port polarity="Output" name="BPWM4" />
        <port polarity="Output" name="BPWM5" />
        <port polarity="Output" name="BPWM6" />
        <port polarity="Input" name="PWMIN1" />
        <port polarity="Input" name="PWMIN2" />
        <port polarity="Input" name="PWMIN3" />
        <port polarity="Input" name="PWMIN4" />
        <port polarity="Input" name="PWMIN5" />
        <port polarity="Input" name="PWMIN6" />
        <port polarity="Output" name="BPWM1" />
        <port polarity="Output" name="BPWM3" />
        <blockdef name="xnor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="60" y1="-128" y2="-128" x1="0" />
            <arc ex="44" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <arc ex="64" ey="-144" sx="64" sy="-48" r="56" cx="32" cy="-96" />
            <line x2="64" y1="-144" y2="-144" x1="128" />
            <line x2="64" y1="-48" y2="-48" x1="128" />
            <arc ex="128" ey="-144" sx="208" sy="-96" r="88" cx="132" cy="-56" />
            <arc ex="208" ey="-96" sx="128" sy="-48" r="88" cx="132" cy="-136" />
            <circle r="8" cx="220" cy="-96" />
            <line x2="256" y1="-96" y2="-96" x1="228" />
            <line x2="60" y1="-28" y2="-28" x1="60" />
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
        <blockdef name="nor2">
            <timestamp>2000-1-1T10:10:10</timestamp>
            <line x2="64" y1="-64" y2="-64" x1="0" />
            <line x2="64" y1="-128" y2="-128" x1="0" />
            <line x2="216" y1="-96" y2="-96" x1="256" />
            <circle r="12" cx="204" cy="-96" />
            <arc ex="192" ey="-96" sx="112" sy="-48" r="88" cx="116" cy="-136" />
            <arc ex="112" ey="-144" sx="192" sy="-96" r="88" cx="116" cy="-56" />
            <arc ex="48" ey="-144" sx="48" sy="-48" r="56" cx="16" cy="-96" />
            <line x2="48" y1="-48" y2="-48" x1="112" />
            <line x2="48" y1="-144" y2="-144" x1="112" />
        </blockdef>
        <block symbolname="xnor2" name="XLXI_2">
            <blockpin signalname="XLXN_246" name="I0" />
            <blockpin signalname="XLXN_252" name="I1" />
            <blockpin signalname="XLXN_1" name="O" />
        </block>
        <block symbolname="xnor2" name="XLXI_4">
            <blockpin signalname="XLXN_248" name="I0" />
            <blockpin signalname="XLXN_254" name="I1" />
            <blockpin signalname="XLXN_4" name="O" />
        </block>
        <block symbolname="xnor2" name="XLXI_3">
            <blockpin signalname="XLXN_159" name="I0" />
            <blockpin signalname="XLXN_253" name="I1" />
            <blockpin signalname="XLXN_7" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_14">
            <blockpin signalname="PWMIN2" name="I" />
            <blockpin signalname="XLXN_246" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_15">
            <blockpin signalname="PWMIN3" name="I" />
            <blockpin signalname="XLXN_253" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_16">
            <blockpin signalname="PWMIN4" name="I" />
            <blockpin signalname="XLXN_159" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_17">
            <blockpin signalname="PWMIN5" name="I" />
            <blockpin signalname="XLXN_254" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_18">
            <blockpin signalname="PWMIN6" name="I" />
            <blockpin signalname="XLXN_248" name="O" />
        </block>
        <block symbolname="ibuf" name="XLXI_13">
            <blockpin signalname="PWMIN1" name="I" />
            <blockpin signalname="XLXN_252" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_141">
            <blockpin signalname="XLXN_246" name="I0" />
            <blockpin signalname="XLXN_1" name="I1" />
            <blockpin signalname="XLXN_21" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_143">
            <blockpin signalname="XLXN_159" name="I0" />
            <blockpin signalname="XLXN_7" name="I1" />
            <blockpin signalname="XLXN_23" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_144">
            <blockpin signalname="XLXN_4" name="I0" />
            <blockpin signalname="XLXN_254" name="I1" />
            <blockpin signalname="XLXN_180" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_145">
            <blockpin signalname="XLXN_248" name="I0" />
            <blockpin signalname="XLXN_4" name="I1" />
            <blockpin signalname="XLXN_181" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_142">
            <blockpin signalname="XLXN_7" name="I0" />
            <blockpin signalname="XLXN_253" name="I1" />
            <blockpin signalname="XLXN_176" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_19">
            <blockpin signalname="XLXN_213" name="I" />
            <blockpin signalname="BPWM1" name="O" />
        </block>
        <block symbolname="nor2" name="XLXI_140">
            <blockpin signalname="XLXN_1" name="I0" />
            <blockpin signalname="XLXN_252" name="I1" />
            <blockpin signalname="XLXN_213" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_20">
            <blockpin signalname="XLXN_21" name="I" />
            <blockpin signalname="BPWM2" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_21">
            <blockpin signalname="XLXN_176" name="I" />
            <blockpin signalname="BPWM3" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_22">
            <blockpin signalname="XLXN_23" name="I" />
            <blockpin signalname="BPWM4" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_23">
            <blockpin signalname="XLXN_180" name="I" />
            <blockpin signalname="BPWM5" name="O" />
        </block>
        <block symbolname="obuf" name="XLXI_24">
            <blockpin signalname="XLXN_181" name="I" />
            <blockpin signalname="BPWM6" name="O" />
        </block>
    </netlist>
    <sheet sheetnum="1" width="3520" height="2720">
        <branch name="XLXN_7">
            <wire x2="1792" y1="1424" y2="1424" x1="1728" />
            <wire x2="1792" y1="1424" y2="1472" x1="1792" />
            <wire x2="2368" y1="1472" y2="1472" x1="1792" />
            <wire x2="1792" y1="1360" y2="1424" x1="1792" />
            <wire x2="2368" y1="1360" y2="1360" x1="1792" />
        </branch>
        <branch name="XLXN_4">
            <wire x2="1808" y1="1776" y2="1776" x1="1744" />
            <wire x2="1808" y1="1776" y2="1840" x1="1808" />
            <wire x2="2368" y1="1840" y2="1840" x1="1808" />
            <wire x2="2368" y1="1712" y2="1712" x1="1808" />
            <wire x2="1808" y1="1712" y2="1776" x1="1808" />
        </branch>
        <branch name="BPWM2">
            <wire x2="2944" y1="1152" y2="1152" x1="2880" />
        </branch>
        <branch name="BPWM4">
            <wire x2="2944" y1="1504" y2="1504" x1="2880" />
        </branch>
        <branch name="BPWM5">
            <wire x2="2944" y1="1680" y2="1680" x1="2880" />
        </branch>
        <branch name="BPWM6">
            <wire x2="2944" y1="1872" y2="1872" x1="2880" />
        </branch>
        <branch name="PWMIN1">
            <wire x2="544" y1="928" y2="928" x1="496" />
        </branch>
        <branch name="PWMIN2">
            <wire x2="528" y1="1184" y2="1184" x1="496" />
        </branch>
        <branch name="PWMIN3">
            <wire x2="528" y1="1296" y2="1296" x1="496" />
        </branch>
        <branch name="PWMIN4">
            <wire x2="528" y1="1536" y2="1536" x1="496" />
        </branch>
        <branch name="PWMIN5">
            <wire x2="528" y1="1648" y2="1648" x1="496" />
        </branch>
        <branch name="PWMIN6">
            <wire x2="528" y1="1904" y2="1904" x1="496" />
        </branch>
        <branch name="BPWM1">
            <wire x2="2944" y1="960" y2="960" x1="2880" />
        </branch>
        <branch name="XLXN_1">
            <wire x2="1792" y1="1056" y2="1056" x1="1744" />
            <wire x2="1792" y1="1056" y2="1120" x1="1792" />
            <wire x2="2368" y1="1120" y2="1120" x1="1792" />
            <wire x2="2352" y1="992" y2="992" x1="1792" />
            <wire x2="1792" y1="992" y2="1056" x1="1792" />
        </branch>
        <branch name="XLXN_21">
            <wire x2="2656" y1="1152" y2="1152" x1="2624" />
        </branch>
        <branch name="BPWM3">
            <wire x2="2944" y1="1328" y2="1328" x1="2880" />
        </branch>
        <branch name="XLXN_176">
            <wire x2="2656" y1="1328" y2="1328" x1="2624" />
        </branch>
        <branch name="XLXN_23">
            <wire x2="2656" y1="1504" y2="1504" x1="2624" />
        </branch>
        <branch name="XLXN_180">
            <wire x2="2656" y1="1680" y2="1680" x1="2624" />
        </branch>
        <branch name="XLXN_181">
            <wire x2="2656" y1="1872" y2="1872" x1="2624" />
        </branch>
        <branch name="XLXN_213">
            <wire x2="2656" y1="960" y2="960" x1="2608" />
        </branch>
        <branch name="XLXN_246">
            <wire x2="1440" y1="1184" y2="1184" x1="752" />
            <wire x2="2368" y1="1184" y2="1184" x1="1440" />
            <wire x2="1488" y1="1088" y2="1088" x1="1440" />
            <wire x2="1440" y1="1088" y2="1184" x1="1440" />
        </branch>
        <branch name="XLXN_159">
            <wire x2="1440" y1="1536" y2="1536" x1="752" />
            <wire x2="2368" y1="1536" y2="1536" x1="1440" />
            <wire x2="1472" y1="1456" y2="1456" x1="1440" />
            <wire x2="1440" y1="1456" y2="1536" x1="1440" />
        </branch>
        <branch name="XLXN_248">
            <wire x2="1440" y1="1904" y2="1904" x1="752" />
            <wire x2="2368" y1="1904" y2="1904" x1="1440" />
            <wire x2="1488" y1="1808" y2="1808" x1="1440" />
            <wire x2="1440" y1="1808" y2="1904" x1="1440" />
        </branch>
        <branch name="XLXN_252">
            <wire x2="1440" y1="928" y2="928" x1="768" />
            <wire x2="1440" y1="928" y2="1024" x1="1440" />
            <wire x2="1488" y1="1024" y2="1024" x1="1440" />
            <wire x2="2352" y1="928" y2="928" x1="1440" />
        </branch>
        <branch name="XLXN_253">
            <wire x2="1440" y1="1296" y2="1296" x1="752" />
            <wire x2="1440" y1="1296" y2="1392" x1="1440" />
            <wire x2="1472" y1="1392" y2="1392" x1="1440" />
            <wire x2="2368" y1="1296" y2="1296" x1="1440" />
        </branch>
        <branch name="XLXN_254">
            <wire x2="1440" y1="1648" y2="1648" x1="752" />
            <wire x2="1440" y1="1648" y2="1744" x1="1440" />
            <wire x2="1488" y1="1744" y2="1744" x1="1440" />
            <wire x2="2368" y1="1648" y2="1648" x1="1440" />
        </branch>
        <instance x="1488" y="1152" name="XLXI_2" orien="R0" />
        <instance x="1488" y="1872" name="XLXI_4" orien="R0" />
        <instance x="1472" y="1520" name="XLXI_3" orien="R0" />
        <instance x="528" y="1216" name="XLXI_14" orien="R0" />
        <instance x="528" y="1328" name="XLXI_15" orien="R0" />
        <instance x="528" y="1568" name="XLXI_16" orien="R0" />
        <instance x="528" y="1680" name="XLXI_17" orien="R0" />
        <instance x="528" y="1936" name="XLXI_18" orien="R0" />
        <instance x="544" y="960" name="XLXI_13" orien="R0" />
        <instance x="2368" y="1248" name="XLXI_141" orien="R0" />
        <instance x="2368" y="1600" name="XLXI_143" orien="R0" />
        <instance x="2368" y="1776" name="XLXI_144" orien="R0" />
        <instance x="2368" y="1968" name="XLXI_145" orien="R0" />
        <instance x="2368" y="1424" name="XLXI_142" orien="R0" />
        <instance x="2656" y="992" name="XLXI_19" orien="R0" />
        <instance x="2352" y="1056" name="XLXI_140" orien="R0" />
        <instance x="2656" y="1184" name="XLXI_20" orien="R0" />
        <instance x="2656" y="1360" name="XLXI_21" orien="R0" />
        <instance x="2656" y="1536" name="XLXI_22" orien="R0" />
        <instance x="2656" y="1712" name="XLXI_23" orien="R0" />
        <instance x="2656" y="1904" name="XLXI_24" orien="R0" />
        <iomarker fontsize="28" x="496" y="1184" name="PWMIN2" orien="R180" />
        <iomarker fontsize="28" x="496" y="1296" name="PWMIN3" orien="R180" />
        <iomarker fontsize="28" x="496" y="1536" name="PWMIN4" orien="R180" />
        <iomarker fontsize="28" x="496" y="1648" name="PWMIN5" orien="R180" />
        <iomarker fontsize="28" x="496" y="1904" name="PWMIN6" orien="R180" />
        <iomarker fontsize="28" x="496" y="928" name="PWMIN1" orien="R180" />
        <iomarker fontsize="28" x="2944" y="1872" name="BPWM6" orien="R0" />
        <iomarker fontsize="28" x="2944" y="1680" name="BPWM5" orien="R0" />
        <iomarker fontsize="28" x="2944" y="1504" name="BPWM4" orien="R0" />
        <iomarker fontsize="28" x="2944" y="1328" name="BPWM3" orien="R0" />
        <iomarker fontsize="28" x="2944" y="1152" name="BPWM2" orien="R0" />
        <iomarker fontsize="28" x="2944" y="960" name="BPWM1" orien="R0" />
    </sheet>
</drawing>