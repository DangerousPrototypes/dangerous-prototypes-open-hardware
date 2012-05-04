 Line  Address  Opcode        Label                      Disassembly              

     1   0000    EFBE _entry               GOTO _startup                          
     2   0002    F001                      NOP                                    
     3   0004    0012                      RETURN 0                               
     4   0006    FFFF                      NOP                                    
     5   0008    EF04 High_ISR             GOTO Remapped_High_ISR                 
     6   000A    F004                      NOP                                    
     7   000C    0012                      RETURN 0                               
     8   000E    4F4E                      DCFSNZ 0x4e, F, BANKED                 
     9   0010    4D45                      DCFSNZ 0x45, W, BANKED                 
    10   0012    0053                                                             
    11   0014    0000                      NOP                                    
    12   0016    FF00                      NOP                                    
    13   0018    EF0C Low_ISR              GOTO Remapped_Low_ISR                  
    14   001A    F004                      NOP                                    
    15   001C    0012                      RETURN 0                               
    16   001E    0002                                                             
    17   0020    000E                      TBLWT*-                                
    18   0022    0000                      NOP                                    
    19   0024    00C3                                                             
    20   0026    0000                      NOP                                    
    21   0028    0009                      TBLRD*+                                
    22   002A    0000                      NOP                                    
    23   002C    021F                      MULWF 0x1f, ACCESS                     
    24   002E    0000                      NOP                                    
    25   0030    00CC                                                             
    26   0032    0000                      NOP                                    
    27   0034    0001                                                             
    28   0036    0000                      NOP                                    
    29   0038    CFD9 main                 MOVFF FSR2, POSTINC1                   
    30   003A    FFE6                      NOP                                    
    31   003C    CFE1                      MOVFF FSR1L, FSR2                      
    32   003E    FFD9                      NOP                                    
    33   0040    52E6                      MOVF POSTINC1, F, ACCESS               
    34   0042    ECCB                      CALL initCDC, 0                        
    35   0044    F00C                      NOP                                    
    36   0046    D864                      RCALL SetupBoard                       
    37   0048    0E04                      MOVLW 0x4                              
    38   004A    6EE6                      MOVWF POSTINC1, ACCESS                 
    39   004C    6AE6                      CLRF POSTINC1, ACCESS                  
    40   004E    0ECD                      MOVLW 0xcd                             
    41   0050    6EE6                      MOVWF POSTINC1, ACCESS                 
    42   0052    0E01                      MOVLW 0x1                              
    43   0054    6EE6                      MOVWF POSTINC1, ACCESS                 
    44   0056    0E00                      MOVLW 0                                
    45   0058    6EE6                      MOVWF POSTINC1, ACCESS                 
    46   005A    0E8A                      MOVLW 0x8a                             
    47   005C    6EE6                      MOVWF POSTINC1, ACCESS                 
    48   005E    0E01                      MOVLW 0x1                              
    49   0060    6EE6                      MOVWF POSTINC1, ACCESS                 
    50   0062    0E00                      MOVLW 0                                
    51   0064    6EE6                      MOVWF POSTINC1, ACCESS                 
    52   0066    0E78                      MOVLW 0x78                             
    53   0068    6EE6                      MOVWF POSTINC1, ACCESS                 
    54   006A    0E01                      MOVLW 0x1                              
    55   006C    6EE6                      MOVWF POSTINC1, ACCESS                 
    56   006E    0E00                      MOVLW 0                                
    57   0070    6EE6                      MOVWF POSTINC1, ACCESS                 
    58   0072    EC0F                      CALL usb_init, 0                       
    59   0074    F004                      NOP                                    
    60   0076    6E10                      MOVWF __tmp_0, ACCESS                  
    61   0078    0E0B                      MOVLW 0xb                              
    62   007A    5EE1                      SUBWF FSR1L, F, ACCESS                 
    63   007C    5010                      MOVF __tmp_0, W, ACCESS                
    64   007E    EC59                      CALL usb_start, 0                      
    65   0080    F004                      NOP                                    
    66   0082    0E4B                      MOVLW 0x4b                             
    67   0084    1260                      IORWF UIE, F, ACCESS                   
    68   0086    84A0                      BSF PIE2, 0x2, ACCESS                  
    69   0088    0E20                      MOVLW 0x20                             
    70   008A    0100                      MOVLB 0                                
    71   008C    5D95                      SUBWF usb_device_state, W, BANKED      
    72   008E    E3FC                      BNC 0x88                               
    73   0090    0E56                      MOVLW 0x56                             
    74   0092    6EE6                      MOVWF POSTINC1, ACCESS                 
    75   0094    0E20                      MOVLW 0x20                             
    76   0096    6EE6                      MOVWF POSTINC1, ACCESS                 
    77   0098    EC7B                      CALL usb_register_sof_handler, 0       
    78   009A    F00B                      NOP                                    
    79   009C    52E5                      MOVF POSTDEC1, F, ACCESS               
    80   009E    52E5                      MOVF POSTDEC1, F, ACCESS               
    81   00A0    CFD9                      MOVFF FSR2, POSTINC1                   
    82   00A2    FFE6                      NOP                                    
    83   00A4    CFDA                      MOVFF FSR2H, POSTINC1                  
    84   00A6    FFE6                      NOP                                    
    85   00A8    ECA0                      CALL poll_getc_cdc, 0                  
    86   00AA    F010                      NOP                                    
    87   00AC    52E5                      MOVF POSTDEC1, F, ACCESS               
    88   00AE    52E5                      MOVF POSTDEC1, F, ACCESS               
    89   00B0    0900                      IORLW 0                                
    90   00B2    E005                      BZ 0xbe                                
    91   00B4    CFDF                      MOVFF INDF2, POSTINC1                  
    92   00B6    FFE6                      NOP                                    
    93   00B8    EC58                      CALL putc_cdc, 0                       
    94   00BA    F010                      NOP                                    
    95   00BC    52E5                      MOVF POSTDEC1, F, ACCESS               
    96   00BE    CFD9                      MOVFF FSR2, POSTINC1                   
    97   00C0    FFE6                      NOP                                    
    98   00C2    CFDA                      MOVFF FSR2H, POSTINC1                  
    99   00C4    FFE6                      NOP                                    
   100   00C6    ECDF                      CALL peek_getc_cdc, 0                  
   101   00C8    F010                      NOP                                    
   102   00CA    52E5                      MOVF POSTDEC1, F, ACCESS               
   103   00CC    52E5                      MOVF POSTDEC1, F, ACCESS               
   104   00CE    0900                      IORLW 0                                
   105   00D0    E008                      BZ 0xe2                                
   106   00D2    EC81                      CALL getc_cdc, 0                       
   107   00D4    F010                      NOP                                    
   108   00D6    6EDF                      MOVWF INDF2, ACCESS                    
   109   00D8    CFDF                      MOVFF INDF2, POSTINC1                  
   110   00DA    FFE6                      NOP                                    
   111   00DC    EC58                      CALL putc_cdc, 0                       
   112   00DE    F010                      NOP                                    
   113   00E0    52E5                      MOVF POSTDEC1, F, ACCESS               
   114   00E2    CFD9                      MOVFF FSR2, POSTINC1                   
   115   00E4    FFE6                      NOP                                    
   116   00E6    CFDA                      MOVFF FSR2H, POSTINC1                  
   117   00E8    FFE6                      NOP                                    
   118   00EA    ECA0                      CALL poll_getc_cdc, 0                  
   119   00EC    F010                      NOP                                    
   120   00EE    52E5                      MOVF POSTDEC1, F, ACCESS               
   121   00F0    52E5                      MOVF POSTDEC1, F, ACCESS               
   122   00F2    0900                      IORLW 0                                
   123   00F4    E007                      BZ 0x104                               
   124   00F6    CFDF                      MOVFF INDF2, POSTINC1                  
   125   00F8    FFE6                      NOP                                    
   126   00FA    EC58                      CALL putc_cdc, 0                       
   127   00FC    F010                      NOP                                    
   128   00FE    52E5                      MOVF POSTDEC1, F, ACCESS               
   129   0100    EC10                      CALL CDC_Flush_In_Now, 0               
   130   0102    F010                      NOP                                    
   131   0104    D7CD                      BRA 0xa0                               
   132   0106    52E5                      MOVF POSTDEC1, F, ACCESS               
   133   0108    52E5                      MOVF POSTDEC1, F, ACCESS               
   134   010A    CFE7                      MOVFF INDF1, FSR2                      
   135   010C    FFD9                      NOP                                    
   136   010E    0012                      RETURN 0                               
   137   0110    0012 SetupBoard           RETURN 0                               
   138   0112    0012 USBSuspend           RETURN 0                               
   139   0114    CFDA InterruptHandlerHigh MOVFF FSR2H, PREINC1                   
   140   0116    FFE4                      NOP                                    
   141   0118    CFE2                      MOVFF FSR1H, FSR2H                     
   142   011A    FFDA                      NOP                                    
   143   011C    CFE9                      MOVFF FSR0L, PREINC1                   
   144   011E    FFE4                      NOP                                    
   145   0120    CFEA                      MOVFF FSR0H, PREINC1                   
   146   0122    FFE4                      NOP                                    
   147   0124    52E6                      MOVF POSTINC1, F, ACCESS               
   148   0126    EC0A                      CALL usb_handler, 0                    
   149   0128    F005                      NOP                                    
   150   012A    94A1                      BCF PIR2, 0x2, ACCESS                  
   151   012C    52E5                      MOVF POSTDEC1, F, ACCESS               
   152   012E    CFE5                      MOVFF POSTDEC1, FSR0H                  
   153   0130    FFEA                      NOP                                    
   154   0132    CFE5                      MOVFF POSTDEC1, FSR0L                  
   155   0134    FFE9                      NOP                                    
   156   0136    CFE5                      MOVFF POSTDEC1, FSR2H                  
   157   0138    FFDA                      NOP                                    
   158   013A    0011                      RETFIE 0x1                             
   159   013C    CFD8 InterruptHandlerLow  MOVFF STATUS, PREINC1                  
   160   013E    FFE4                      NOP                                    
   161   0140    CFE0                      MOVFF BSR, PREINC1                     
   162   0142    FFE4                      NOP                                    
   163   0144    6EE4                      MOVWF PREINC1, ACCESS                  
   164   0146    CFDA                      MOVFF FSR2H, PREINC1                   
   165   0148    FFE4                      NOP                                    
   166   014A    CFE2                      MOVFF FSR1H, FSR2H                     
   167   014C    FFDA                      NOP                                    
   168   014E    CFE9                      MOVFF FSR0L, PREINC1                   
   169   0150    FFE4                      NOP                                    
   170   0152    CFEA                      MOVFF FSR0H, PREINC1                   
   171   0154    FFE4                      NOP                                    
   172   0156    52E6                      MOVF POSTINC1, F, ACCESS               
   173   0158    EC0A                      CALL usb_handler, 0                    
   174   015A    F005                      NOP                                    
   175   015C    94A1                      BCF PIR2, 0x2, ACCESS                  
   176   015E    52E5                      MOVF POSTDEC1, F, ACCESS               
   177   0160    CFE5                      MOVFF POSTDEC1, FSR0H                  
   178   0162    FFEA                      NOP                                    
   179   0164    CFE5                      MOVFF POSTDEC1, FSR0L                  
   180   0166    FFE9                      NOP                                    
   181   0168    CFE5                      MOVFF POSTDEC1, FSR2H                  
   182   016A    FFDA                      NOP                                    
   183   016C    50E5                      MOVF POSTDEC1, W, ACCESS               
   184   016E    CFE5                      MOVFF POSTDEC1, BSR                    
   185   0170    FFE0                      NOP                                    
   186   0172    CFE5                      MOVFF POSTDEC1, STATUS                 
   187   0174    FFD8                      NOP                                    
   188   0176    0010                      RETFIE 0                               
   189   0178    0112                                                             
   190   017A    0200                      MULWF RecvdByte, ACCESS                
   191   017C    0002                                                             
   192   017E    0800                      SUBLW 0                                
   193   0180    04D8                      DECF STATUS, W, ACCESS                 
   194   0182    000A                      TBLRD*-                                
   195   0184    0002                                                             
   196   0186    0201                      MULWF 0x1, ACCESS                      
   197   0188    0103                      MOVLB 0x3                              
   198   018A    0209                      MULWF 0x9, ACCESS                      
   199   018C    0043                                                             
   200   018E    0102                      MOVLB 0x2                              
   201   0190    8000                      BSF RecvdByte, 0, ACCESS               
   202   0192    0964                      IORLW 0x64                             
   203   0194    0004                      CLRWDT                                 
   204   0196    0100                      MOVLB 0                                
   205   0198    0202                      MULWF reply_len, ACCESS                
   206   019A    0001                                                             
   207   019C    2405                      ADDWF 0x5, W, ACCESS                   
   208   019E    1000                      IORWF RecvdByte, W, ACCESS             
   209   01A0    0401                      DECF 0x1, W, ACCESS                    
   210   01A2    0224                      MULWF 0x24, ACCESS                     
   211   01A4    0502                      DECF reply_len, W, BANKED              
   212   01A6    0624                      DECF 0x24, F, ACCESS                   
   213   01A8    0100                      MOVLB 0                                
   214   01AA    2405                      ADDWF 0x5, W, ACCESS                   
   215   01AC    0101                      MOVLB 0x1                              
   216   01AE    0701                      DECF 0x1, F, BANKED                    
   217   01B0    8105                      BSF 0x5, 0, BANKED                     
   218   01B2    0A03                      XORLW 0x3                              
   219   01B4    4000                      RRNCF RecvdByte, W, ACCESS             
   220   01B6    0409                      DECF 0x9, W, ACCESS                    
   221   01B8    0001                                                             
   222   01BA    0A02                      XORLW 0x2                              
   223   01BC    0000                      NOP                                    
   224   01BE    0700                      DECF RecvdByte, F, BANKED              
   225   01C0    0205                      MULWF 0x5, ACCESS                      
   226   01C2    2002                      ADDWFC reply_len, W, ACCESS            
   227   01C4    0000                      NOP                                    
   228   01C6    0507                      DECF 0x7, W, BANKED                    
   229   01C8    0282                      MULWF PORTC, ACCESS                    
   230   01CA    0020                                                             
   231   01CC    0400                      DECF RecvdByte, W, ACCESS              
   232   01CE    0903                      IORLW 0x3                              
   233   01D0    2A04                      INCF dwBaudrem, F, ACCESS              
   234   01D2    4403                      RLNCF dir, W, ACCESS                   
   235   01D4    6100                      CPFSLT RecvdByte, BANKED               
   236   01D6    6E00                      MOVWF RecvdByte, ACCESS                
   237   01D8    6700                      TSTFSZ RecvdByte, BANKED               
   238   01DA    6500                      CPFSGT RecvdByte, BANKED               
   239   01DC    7200                      BTG RecvdByte, 0x1, ACCESS             
   240   01DE    6F00                      MOVWF RecvdByte, BANKED                
   241   01E0    7500                      BTG RecvdByte, 0x2, BANKED             
   242   01E2    7300                      BTG RecvdByte, 0x1, BANKED             
   243   01E4    2000                      ADDWFC RecvdByte, W, ACCESS            
   244   01E6    5000                      MOVF RecvdByte, W, ACCESS              
   245   01E8    7200                      BTG RecvdByte, 0x1, ACCESS             
   246   01EA    6F00                      MOVWF RecvdByte, BANKED                
   247   01EC    7400                      BTG RecvdByte, 0x2, ACCESS             
   248   01EE    6F00                      MOVWF RecvdByte, BANKED                
   249   01F0    7400                      BTG RecvdByte, 0x2, ACCESS             
   250   01F2    7900                      BTG RecvdByte, 0x4, BANKED             
   251   01F4    7000                      BTG RecvdByte, 0, ACCESS               
   252   01F6    6500                      CPFSGT RecvdByte, BANKED               
   253   01F8    7300                      BTG RecvdByte, 0x1, BANKED             
   254   01FA    1200                      IORWF RecvdByte, F, ACCESS             
   255   01FC    4303                      RRNCF dir, F, BANKED                   
   256   01FE    4400                      RLNCF RecvdByte, W, ACCESS             
   257   0200    4300                      RRNCF RecvdByte, F, BANKED             
   258   0202    2000                      ADDWFC RecvdByte, W, ACCESS            
   259   0204    5400                      SUBFWB RecvdByte, W, ACCESS            
   260   0206    6500                      CPFSGT RecvdByte, BANKED               
   261   0208    7300                      BTG RecvdByte, 0x1, BANKED             
   262   020A    7400                      BTG RecvdByte, 0x2, ACCESS             
   263   020C    1200                      IORWF RecvdByte, F, ACCESS             
   264   020E    3003                      RRCF dir, W, ACCESS                    
   265   0210    3000                      RRCF RecvdByte, W, ACCESS              
   266   0212    3000                      RRCF RecvdByte, W, ACCESS              
   267   0214    3000                      RRCF RecvdByte, W, ACCESS              
   268   0216    3000                      RRCF RecvdByte, W, ACCESS              
   269   0218    3000                      RRCF RecvdByte, W, ACCESS              
   270   021A    3000                      RRCF RecvdByte, W, ACCESS              
   271   021C    3100                      RRCF RecvdByte, W, BANKED              
   272   021E    0000                      NOP                                    
   273   0220    0E1E _do_cinit            MOVLW 0x1e                             
   274   0222    6EF6                      MOVWF TBLPTRL, ACCESS                  
   275   0224    0E00                      MOVLW 0                                
   276   0226    6EF7                      MOVWF TBLPTRH, ACCESS                  
   277   0228    0E00                      MOVLW 0                                
   278   022A    6EF8                      MOVWF TBLPTRU, ACCESS                  
   279   022C    0100                      MOVLB 0                                
   280   022E    0009                      TBLRD*+                                
   281   0230    50F5                      MOVF TABLAT, W, ACCESS                 
   282   0232    6FBE                      MOVWF curr_entry, BANKED               
   283   0234    0009                      TBLRD*+                                
   284   0236    50F5                      MOVF TABLAT, W, ACCESS                 
   285   0238    6FBF                      MOVWF 0xbf, BANKED                     
   286   023A    E103                      BNZ 0x242                              
   287   023C    67BE                      TSTFSZ curr_entry, BANKED              
   288   023E    D001                      BRA 0x242                              
   289   0240    D03D                      BRA 0x2bc                              
   290   0242    0009                      TBLRD*+                                
   291   0244    50F5                      MOVF TABLAT, W, ACCESS                 
   292   0246    6FB9                      MOVWF prom, BANKED                     
   293   0248    0009                      TBLRD*+                                
   294   024A    50F5                      MOVF TABLAT, W, ACCESS                 
   295   024C    6FBA                      MOVWF 0xba, BANKED                     
   296   024E    0009                      TBLRD*+                                
   297   0250    50F5                      MOVF TABLAT, W, ACCESS                 
   298   0252    6FBB                      MOVWF 0xbb, BANKED                     
   299   0254    0009                      TBLRD*+                                
   300   0256    0009                      TBLRD*+                                
   301   0258    50F5                      MOVF TABLAT, W, ACCESS                 
   302   025A    6EE9                      MOVWF FSR0L, ACCESS                    
   303   025C    0009                      TBLRD*+                                
   304   025E    50F5                      MOVF TABLAT, W, ACCESS                 
   305   0260    6EEA                      MOVWF FSR0H, ACCESS                    
   306   0262    0009                      TBLRD*+                                
   307   0264    0009                      TBLRD*+                                
   308   0266    0009                      TBLRD*+                                
   309   0268    50F5                      MOVF TABLAT, W, ACCESS                 
   310   026A    6FBC                      MOVWF curr_byte, BANKED                
   311   026C    0009                      TBLRD*+                                
   312   026E    50F5                      MOVF TABLAT, W, ACCESS                 
   313   0270    6FBD                      MOVWF 0xbd, BANKED                     
   314   0272    0009                      TBLRD*+                                
   315   0274    0009                      TBLRD*+                                
   316   0276    CFF6                      MOVFF TBLPTRL, data_ptr                
   317   0278    F0C0                      NOP                                    
   318   027A    CFF7                      MOVFF TBLPTRH, 0xc1                    
   319   027C    F0C1                      NOP                                    
   320   027E    CFF8                      MOVFF TBLPTRU, 0xc2                    
   321   0280    F0C2                      NOP                                    
   322   0282    C0B9                      MOVFF prom, TBLPTRL                    
   323   0284    FFF6                      NOP                                    
   324   0286    C0BA                      MOVFF 0xba, TBLPTRH                    
   325   0288    FFF7                      NOP                                    
   326   028A    C0BB                      MOVFF 0xbb, TBLPTRU                    
   327   028C    FFF8                      NOP                                    
   328   028E    0100                      MOVLB 0                                
   329   0290    53BC                      MOVF curr_byte, F, BANKED              
   330   0292    E102                      BNZ 0x298                              
   331   0294    53BD                      MOVF 0xbd, F, BANKED                   
   332   0296    E007                      BZ 0x2a6                               
   333   0298    0009                      TBLRD*+                                
   334   029A    50F5                      MOVF TABLAT, W, ACCESS                 
   335   029C    6EEE                      MOVWF POSTINC0, ACCESS                 
   336   029E    07BC                      DECF curr_byte, F, BANKED              
   337   02A0    E2F8                      BC 0x292                               
   338   02A2    07BD                      DECF 0xbd, F, BANKED                   
   339   02A4    D7F9                      BRA 0x298                              
   340   02A6    C0C0                      MOVFF data_ptr, TBLPTRL                
   341   02A8    FFF6                      NOP                                    
   342   02AA    C0C1                      MOVFF 0xc1, TBLPTRH                    
   343   02AC    FFF7                      NOP                                    
   344   02AE    C0C2                      MOVFF 0xc2, TBLPTRU                    
   345   02B0    FFF8                      NOP                                    
   346   02B2    0100                      MOVLB 0                                
   347   02B4    07BE                      DECF curr_entry, F, BANKED             
   348   02B6    0E00                      MOVLW 0                                
   349   02B8    5BBF                      SUBWFB 0xbf, F, BANKED                 
   350   02BA    D7BF                      BRA 0x23a                              
   351   02BC    0012                      RETURN 0                               
   352   02BE    CFD9 memcpy               MOVFF FSR2, POSTINC1                   
   353   02C0    FFE6                      NOP                                    
   354   02C2    CFDA                      MOVFF FSR2H, POSTINC1                  
   355   02C4    FFE6                      NOP                                    
   356   02C6    0EFA                      MOVLW 0xfa                             
   357   02C8    CFE3                      MOVFF PLUSW1, FSR2                     
   358   02CA    FFD9                      NOP                                    
   359   02CC    0EFB                      MOVLW 0xfb                             
   360   02CE    CFE3                      MOVFF PLUSW1, FSR2H                    
   361   02D0    FFDA                      NOP                                    
   362   02D2    0EFC                      MOVLW 0xfc                             
   363   02D4    CFE3                      MOVFF PLUSW1, FSR0L                    
   364   02D6    FFE9                      NOP                                    
   365   02D8    0EFD                      MOVLW 0xfd                             
   366   02DA    CFE3                      MOVFF PLUSW1, FSR0H                    
   367   02DC    FFEA                      NOP                                    
   368   02DE    CFE9                      MOVFF FSR0L, PRODL                     
   369   02E0    FFF3                      NOP                                    
   370   02E2    CFEA                      MOVFF FSR0H, PRODH                     
   371   02E4    FFF4                      NOP                                    
   372   02E6    0EF8 jLoop                MOVLW 0xf8                             
   373   02E8    50E3                      MOVF PLUSW1, W, ACCESS                 
   374   02EA    E103                      BNZ _4jContinue                        
   375   02EC    0EF9                      MOVLW 0xf9                             
   376   02EE    50E3                      MOVF PLUSW1, W, ACCESS                 
   377   02F0    E008                      BZ jEnd                                
   378   02F2    0EF8 _4jContinue          MOVLW 0xf8                             
   379   02F4    06E3                      DECF PLUSW1, F, ACCESS                 
   380   02F6    E202                      BC _5jEnd                              
   381   02F8    0EF9                      MOVLW 0xf9                             
   382   02FA    06E3                      DECF PLUSW1, F, ACCESS                 
   383   02FC    CFDE _5jEnd               MOVFF POSTINC2, POSTINC0               
   384   02FE    FFEE                      NOP                                    
   385   0300    D7F2                      BRA jLoop                              
   386   0302    0EFF jEnd                 MOVLW 0xff                             
   387   0304    CFE3                      MOVFF PLUSW1, FSR2H                    
   388   0306    FFDA                      NOP                                    
   389   0308    52E5                      MOVF POSTDEC1, F, ACCESS               
   390   030A    0EFF                      MOVLW 0xff                             
   391   030C    CFE3                      MOVFF PLUSW1, FSR2                     
   392   030E    FFD9                      NOP                                    
   393   0310    52E5                      MOVF POSTDEC1, F, ACCESS               
   394   0312    0012                      RETURN 0                               
   395   0314    6A03 FXD3232U             CLRF dir, ACCESS                       
   396   0316    6A02                      CLRF reply_len, ACCESS                 
   397   0318    6A01                      CLRF 0x1, ACCESS                       
   398   031A    6A00                      CLRF RecvdByte, ACCESS                 
   399   031C    0E20                      MOVLW 0x20                             
   400   031E    6EE7                      MOVWF INDF1, ACCESS                    
   401   0320    90D8                      BCF STATUS, 0, ACCESS                  
   402   0322    3604                      RLCF dwBaudrem, F, ACCESS              
   403   0324    3605                      RLCF 0x5, F, ACCESS                    
   404   0326    3606                      RLCF pUEP, F, ACCESS                   
   405   0328    3607                      RLCF 0x7, F, ACCESS                    
   406   032A    3600                      RLCF RecvdByte, F, ACCESS              
   407   032C    3601                      RLCF 0x1, F, ACCESS                    
   408   032E    3602                      RLCF reply_len, F, ACCESS              
   409   0330    3603                      RLCF dir, F, ACCESS                    
   410   0332    5009                      MOVF 0x9, W, ACCESS                    
   411   0334    5C00                      SUBWF RecvdByte, W, ACCESS             
   412   0336    500A                      MOVF 0xa, W, ACCESS                    
   413   0338    5801                      SUBWFB 0x1, W, ACCESS                  
   414   033A    500B                      MOVF 0xb, W, ACCESS                    
   415   033C    5802                      SUBWFB reply_len, W, ACCESS            
   416   033E    500C                      MOVF 0xc, W, ACCESS                    
   417   0340    5803                      SUBWFB dir, W, ACCESS                  
   418   0342    E309                      BNC 0x356                              
   419   0344    5009                      MOVF 0x9, W, ACCESS                    
   420   0346    5E00                      SUBWF RecvdByte, F, ACCESS             
   421   0348    500A                      MOVF 0xa, W, ACCESS                    
   422   034A    5A01                      SUBWFB 0x1, F, ACCESS                  
   423   034C    500B                      MOVF 0xb, W, ACCESS                    
   424   034E    5A02                      SUBWFB reply_len, F, ACCESS            
   425   0350    500C                      MOVF 0xc, W, ACCESS                    
   426   0352    5A03                      SUBWFB dir, F, ACCESS                  
   427   0354    2A04                      INCF dwBaudrem, F, ACCESS              
   428   0356    2EE7                      DECFSZ INDF1, F, ACCESS                
   429   0358    D7E4                      BRA 0x322                              
   430   035A    0012                      RETURN 0                               
   431   035C    0E00 __zero_memory        MOVLW 0                                
   432   035E    6EF3                      MOVWF PRODL, ACCESS                    
   433   0360    EE00                      LFSR 0, 0                              
   434   0362    F000                      NOP                                    
   435   0364    0E03                      MOVLW 0x3                              
   436   0366    D801                      RCALL zero_block                       
   437   0368    0012                      RETURN 0                               
   438   036A    60EA zero_block           CPFSLT FSR0H, ACCESS                   
   439   036C    D002                      BRA compare_l                          
   440   036E    6AEE                      CLRF POSTINC0, ACCESS                  
   441   0370    D7FC                      BRA zero_block                         
   442   0372    50F3 compare_l            MOVF PRODL, W, ACCESS                  
   443   0374    60E9 loop_l               CPFSLT FSR0L, ACCESS                   
   444   0376    0012                      RETURN 0                               
   445   0378    6AEE                      CLRF POSTINC0, ACCESS                  
   446   037A    D7FC                      BRA loop_l                             
   447   037C    EE11 _startup             LFSR 0x1, 0x100                        
   448   037E    F000                      NOP                                    
   449   0380    EE21                      LFSR 0x2, 0x100                        
   450   0382    F000                      NOP                                    
   451   0384    6AF8                      CLRF TBLPTRU, ACCESS                   
   452   0386    9C0F                      BCF 0xf, 0x6, ACCESS                   
   453   0388    EC10                      CALL _do_cinit, 0                      
   454   038A    F001                      NOP                                    
   455   038C    EC03                      CALL __init, 0                         
   456   038E    F004                      NOP                                    
   457   0390    EC1C                      CALL main, 0                           
   458   0392    F000                      NOP                                    
   459   0394    D7FB                      BRA 0x38c                              
   460   0396    0012                      RETURN 0                               
   461   0398    FFFF                      NOP                                    
   462   039A    FFFF                      NOP                                    
   463   039C    FFFF                      NOP                                    
   464   039E    FFFF                      NOP                                    
   465   03A0    FFFF                      NOP                                    
   466   03A2    FFFF                      NOP                                    
   467   03A4    FFFF                      NOP                                    
   468   03A6    FFFF                      NOP                                    
   469   03A8    FFFF                      NOP                                    
   470   03AA    FFFF                      NOP                                    
   471   03AC    FFFF                      NOP                                    
   472   03AE    FFFF                      NOP                                    
   473   03B0    FFFF                      NOP                                    
   474   03B2    FFFF                      NOP                                    
   475   03B4    FFFF                      NOP                                    
   476   03B6    FFFF                      NOP                                    
   477   03B8    FFFF                      NOP                                    
   478   03BA    FFFF                      NOP                                    
   479   03BC    FFFF                      NOP                                    
   480   03BE    FFFF                      NOP                                    
   481   03C0    FFFF                      NOP                                    
   482   03C2    FFFF                      NOP                                    
   483   03C4    FFFF                      NOP                                    
   484   03C6    FFFF                      NOP                                    
   485   03C8    FFFF                      NOP                                    
   486   03CA    FFFF                      NOP                                    
   487   03CC    FFFF                      NOP                                    
   488   03CE    FFFF                      NOP                                    
   489   03D0    FFFF                      NOP                                    
   490   03D2    FFFF                      NOP                                    
   491   03D4    FFFF                      NOP                                    
   492   03D6    FFFF                      NOP                                    
   493   03D8    FFFF                      NOP                                    
   494   03DA    FFFF                      NOP                                    
   495   03DC    FFFF                      NOP                                    
   496   03DE    FFFF                      NOP                                    
   497   03E0    FFFF                      NOP                                    
   498   03E2    FFFF                      NOP                                    
   499   03E4    FFFF                      NOP                                    
   500   03E6    FFFF                      NOP                                    
   501   03E8    FFFF                      NOP                                    
   502   03EA    FFFF                      NOP                                    
   503   03EC    FFFF                      NOP                                    
   504   03EE    FFFF                      NOP                                    
   505   03F0    FFFF                      NOP                                    
   506   03F2    FFFF                      NOP                                    
   507   03F4    FFFF                      NOP                                    
   508   03F6    FFFF                      NOP                                    
   509   03F8    FFFF                      NOP                                    
   510   03FA    FFFF                      NOP                                    
   511   03FC    FFFF                      NOP                                    
   512   03FE    FFFF                      NOP                                    
   513   0400    FFFF                      NOP                                    
   514   0402    FFFF                      NOP                                    
   515   0404    FFFF                      NOP                                    
   516   0406    FFFF                      NOP                                    
   517   0408    FFFF                      NOP                                    
   518   040A    FFFF                      NOP                                    
   519   040C    FFFF                      NOP                                    
   520   040E    FFFF                      NOP                                    
   521   0410    FFFF                      NOP                                    
   522   0412    FFFF                      NOP                                    
   523   0414    FFFF                      NOP                                    
   524   0416    FFFF                      NOP                                    
   525   0418    FFFF                      NOP                                    
   526   041A    FFFF                      NOP                                    
   527   041C    FFFF                      NOP                                    
   528   041E    FFFF                      NOP                                    
   529   0420    FFFF                      NOP                                    
   530   0422    FFFF                      NOP                                    
   531   0424    FFFF                      NOP                                    
   532   0426    FFFF                      NOP                                    
   533   0428    FFFF                      NOP                                    
   534   042A    FFFF                      NOP                                    
   535   042C    FFFF                      NOP                                    
   536   042E    FFFF                      NOP                                    
   537   0430    FFFF                      NOP                                    
   538   0432    FFFF                      NOP                                    
   539   0434    FFFF                      NOP                                    
   540   0436    FFFF                      NOP                                    
   541   0438    FFFF                      NOP                                    
   542   043A    FFFF                      NOP                                    
   543   043C    FFFF                      NOP                                    
   544   043E    FFFF                      NOP                                    
   545   0440    FFFF                      NOP                                    
   546   0442    FFFF                      NOP                                    
   547   0444    FFFF                      NOP                                    
   548   0446    FFFF                      NOP                                    
   549   0448    FFFF                      NOP                                    
   550   044A    FFFF                      NOP                                    
   551   044C    FFFF                      NOP                                    
   552   044E    FFFF                      NOP                                    
   553   0450    FFFF                      NOP                                    
   554   0452    FFFF                      NOP                                    
   555   0454    FFFF                      NOP                                    
   556   0456    FFFF                      NOP                                    
   557   0458    FFFF                      NOP                                    
   558   045A    FFFF                      NOP                                    
   559   045C    FFFF                      NOP                                    
   560   045E    FFFF                      NOP                                    
   561   0460    FFFF                      NOP                                    
   562   0462    FFFF                      NOP                                    
   563   0464    FFFF                      NOP                                    
   564   0466    FFFF                      NOP                                    
   565   0468    FFFF                      NOP                                    
   566   046A    FFFF                      NOP                                    
   567   046C    FFFF                      NOP                                    
   568   046E    FFFF                      NOP                                    
   569   0470    FFFF                      NOP                                    
   570   0472    FFFF                      NOP                                    
   571   0474    FFFF                      NOP                                    
   572   0476    FFFF                      NOP                                    
   573   0478    FFFF                      NOP                                    
   574   047A    FFFF                      NOP                                    
   575   047C    FFFF                      NOP                                    
   576   047E    FFFF                      NOP                                    
   577   0480    FFFF                      NOP                                    
   578   0482    FFFF                      NOP                                    
   579   0484    FFFF                      NOP                                    
   580   0486    FFFF                      NOP                                    
   581   0488    FFFF                      NOP                                    
   582   048A    FFFF                      NOP                                    
   583   048C    FFFF                      NOP                                    
   584   048E    FFFF                      NOP                                    
   585   0490    FFFF                      NOP                                    
   586   0492    FFFF                      NOP                                    
   587   0494    FFFF                      NOP                                    
   588   0496    FFFF                      NOP                                    
   589   0498    FFFF                      NOP                                    
   590   049A    FFFF                      NOP                                    
   591   049C    FFFF                      NOP                                    
   592   049E    FFFF                      NOP                                    
   593   04A0    FFFF                      NOP                                    
   594   04A2    FFFF                      NOP                                    
   595   04A4    FFFF                      NOP                                    
   596   04A6    FFFF                      NOP                                    
   597   04A8    FFFF                      NOP                                    
   598   04AA    FFFF                      NOP                                    
   599   04AC    FFFF                      NOP                                    
   600   04AE    FFFF                      NOP                                    
   601   04B0    FFFF                      NOP                                    
   602   04B2    FFFF                      NOP                                    
   603   04B4    FFFF                      NOP                                    
   604   04B6    FFFF                      NOP                                    
   605   04B8    FFFF                      NOP                                    
   606   04BA    FFFF                      NOP                                    
   607   04BC    FFFF                      NOP                                    
   608   04BE    FFFF                      NOP                                    
   609   04C0    FFFF                      NOP                                    
   610   04C2    FFFF                      NOP                                    
   611   04C4    FFFF                      NOP                                    
   612   04C6    FFFF                      NOP                                    
   613   04C8    FFFF                      NOP                                    
   614   04CA    FFFF                      NOP                                    
   615   04CC    FFFF                      NOP                                    
   616   04CE    FFFF                      NOP                                    
   617   04D0    FFFF                      NOP                                    
   618   04D2    FFFF                      NOP                                    
   619   04D4    FFFF                      NOP                                    
   620   04D6    FFFF                      NOP                                    
   621   04D8    FFFF                      NOP                                    
   622   04DA    FFFF                      NOP                                    
   623   04DC    FFFF                      NOP                                    
   624   04DE    FFFF                      NOP                                    
   625   04E0    FFFF                      NOP                                    
   626   04E2    FFFF                      NOP                                    
   627   04E4    FFFF                      NOP                                    
   628   04E6    FFFF                      NOP                                    
   629   04E8    FFFF                      NOP                                    
   630   04EA    FFFF                      NOP                                    
   631   04EC    FFFF                      NOP                                    
   632   04EE    FFFF                      NOP                                    
   633   04F0    FFFF                      NOP                                    
   634   04F2    FFFF                      NOP                                    
   635   04F4    FFFF                      NOP                                    
   636   04F6    FFFF                      NOP                                    
   637   04F8    FFFF                      NOP                                    
   638   04FA    FFFF                      NOP                                    
   639   04FC    FFFF                      NOP                                    
   640   04FE    FFFF                      NOP                                    
   641   0500    FFFF                      NOP                                    
   642   0502    FFFF                      NOP                                    
   643   0504    FFFF                      NOP                                    
   644   0506    FFFF                      NOP                                    
   645   0508    FFFF                      NOP                                    
   646   050A    FFFF                      NOP                                    
   647   050C    FFFF                      NOP                                    
   648   050E    FFFF                      NOP                                    
   649   0510    FFFF                      NOP                                    
   650   0512    FFFF                      NOP                                    
   651   0514    FFFF                      NOP                                    
   652   0516    FFFF                      NOP                                    
   653   0518    FFFF                      NOP                                    
   654   051A    FFFF                      NOP                                    
   655   051C    FFFF                      NOP                                    
   656   051E    FFFF                      NOP                                    
   657   0520    FFFF                      NOP                                    
   658   0522    FFFF                      NOP                                    
   659   0524    FFFF                      NOP                                    
   660   0526    FFFF                      NOP                                    
   661   0528    FFFF                      NOP                                    
   662   052A    FFFF                      NOP                                    
   663   052C    FFFF                      NOP                                    
   664   052E    FFFF                      NOP                                    
   665   0530    FFFF                      NOP                                    
   666   0532    FFFF                      NOP                                    
   667   0534    FFFF                      NOP                                    
   668   0536    FFFF                      NOP                                    
   669   0538    FFFF                      NOP                                    
   670   053A    FFFF                      NOP                                    
   671   053C    FFFF                      NOP                                    
   672   053E    FFFF                      NOP                                    
   673   0540    FFFF                      NOP                                    
   674   0542    FFFF                      NOP                                    
   675   0544    FFFF                      NOP                                    
   676   0546    FFFF                      NOP                                    
   677   0548    FFFF                      NOP                                    
   678   054A    FFFF                      NOP                                    
   679   054C    FFFF                      NOP                                    
   680   054E    FFFF                      NOP                                    
   681   0550    FFFF                      NOP                                    
   682   0552    FFFF                      NOP                                    
   683   0554    FFFF                      NOP                                    
   684   0556    FFFF                      NOP                                    
   685   0558    FFFF                      NOP                                    
   686   055A    FFFF                      NOP                                    
   687   055C    FFFF                      NOP                                    
   688   055E    FFFF                      NOP                                    
   689   0560    FFFF                      NOP                                    
   690   0562    FFFF                      NOP                                    
   691   0564    FFFF                      NOP                                    
   692   0566    FFFF                      NOP                                    
   693   0568    FFFF                      NOP                                    
   694   056A    FFFF                      NOP                                    
   695   056C    FFFF                      NOP                                    
   696   056E    FFFF                      NOP                                    
   697   0570    FFFF                      NOP                                    
   698   0572    FFFF                      NOP                                    
   699   0574    FFFF                      NOP                                    
   700   0576    FFFF                      NOP                                    
   701   0578    FFFF                      NOP                                    
   702   057A    FFFF                      NOP                                    
   703   057C    FFFF                      NOP                                    
   704   057E    FFFF                      NOP                                    
   705   0580    FFFF                      NOP                                    
   706   0582    FFFF                      NOP                                    
   707   0584    FFFF                      NOP                                    
   708   0586    FFFF                      NOP                                    
   709   0588    FFFF                      NOP                                    
   710   058A    FFFF                      NOP                                    
   711   058C    FFFF                      NOP                                    
   712   058E    FFFF                      NOP                                    
   713   0590    FFFF                      NOP                                    
   714   0592    FFFF                      NOP                                    
   715   0594    FFFF                      NOP                                    
   716   0596    FFFF                      NOP                                    
   717   0598    FFFF                      NOP                                    
   718   059A    FFFF                      NOP                                    
   719   059C    FFFF                      NOP                                    
   720   059E    FFFF                      NOP                                    
   721   05A0    FFFF                      NOP                                    
   722   05A2    FFFF                      NOP                                    
   723   05A4    FFFF                      NOP                                    
   724   05A6    FFFF                      NOP                                    
   725   05A8    FFFF                      NOP                                    
   726   05AA    FFFF                      NOP                                    
   727   05AC    FFFF                      NOP                                    
   728   05AE    FFFF                      NOP                                    
   729   05B0    FFFF                      NOP                                    
   730   05B2    FFFF                      NOP                                    
   731   05B4    FFFF                      NOP                                    
   732   05B6    FFFF                      NOP                                    
   733   05B8    FFFF                      NOP                                    
   734   05BA    FFFF                      NOP                                    
   735   05BC    FFFF                      NOP                                    
   736   05BE    FFFF                      NOP                                    
   737   05C0    FFFF                      NOP                                    
   738   05C2    FFFF                      NOP                                    
   739   05C4    FFFF                      NOP                                    
   740   05C6    FFFF                      NOP                                    
   741   05C8    FFFF                      NOP                                    
   742   05CA    FFFF                      NOP                                    
   743   05CC    FFFF                      NOP                                    
   744   05CE    FFFF                      NOP                                    
   745   05D0    FFFF                      NOP                                    
   746   05D2    FFFF                      NOP                                    
   747   05D4    FFFF                      NOP                                    
   748   05D6    FFFF                      NOP                                    
   749   05D8    FFFF                      NOP                                    
   750   05DA    FFFF                      NOP                                    
   751   05DC    FFFF                      NOP                                    
   752   05DE    FFFF                      NOP                                    
   753   05E0    FFFF                      NOP                                    
   754   05E2    FFFF                      NOP                                    
   755   05E4    FFFF                      NOP                                    
   756   05E6    FFFF                      NOP                                    
   757   05E8    FFFF                      NOP                                    
   758   05EA    FFFF                      NOP                                    
   759   05EC    FFFF                      NOP                                    
   760   05EE    FFFF                      NOP                                    
   761   05F0    FFFF                      NOP                                    
   762   05F2    FFFF                      NOP                                    
   763   05F4    FFFF                      NOP                                    
   764   05F6    FFFF                      NOP                                    
   765   05F8    FFFF                      NOP                                    
   766   05FA    FFFF                      NOP                                    
   767   05FC    FFFF                      NOP                                    
   768   05FE    FFFF                      NOP                                    
   769   0600    FFFF                      NOP                                    
   770   0602    FFFF                      NOP                                    
   771   0604    FFFF                      NOP                                    
   772   0606    FFFF                      NOP                                    
   773   0608    FFFF                      NOP                                    
   774   060A    FFFF                      NOP                                    
   775   060C    FFFF                      NOP                                    
   776   060E    FFFF                      NOP                                    
   777   0610    FFFF                      NOP                                    
   778   0612    FFFF                      NOP                                    
   779   0614    FFFF                      NOP                                    
   780   0616    FFFF                      NOP                                    
   781   0618    FFFF                      NOP                                    
   782   061A    FFFF                      NOP                                    
   783   061C    FFFF                      NOP                                    
   784   061E    FFFF                      NOP                                    
   785   0620    FFFF                      NOP                                    
   786   0622    FFFF                      NOP                                    
   787   0624    FFFF                      NOP                                    
   788   0626    FFFF                      NOP                                    
   789   0628    FFFF                      NOP                                    
   790   062A    FFFF                      NOP                                    
   791   062C    FFFF                      NOP                                    
   792   062E    FFFF                      NOP                                    
   793   0630    FFFF                      NOP                                    
   794   0632    FFFF                      NOP                                    
   795   0634    FFFF                      NOP                                    
   796   0636    FFFF                      NOP                                    
   797   0638    FFFF                      NOP                                    
   798   063A    FFFF                      NOP                                    
   799   063C    FFFF                      NOP                                    
   800   063E    FFFF                      NOP                                    
   801   0640    FFFF                      NOP                                    
   802   0642    FFFF                      NOP                                    
   803   0644    FFFF                      NOP                                    
   804   0646    FFFF                      NOP                                    
   805   0648    FFFF                      NOP                                    
   806   064A    FFFF                      NOP                                    
   807   064C    FFFF                      NOP                                    
   808   064E    FFFF                      NOP                                    
   809   0650    FFFF                      NOP                                    
   810   0652    FFFF                      NOP                                    
   811   0654    FFFF                      NOP                                    
   812   0656    FFFF                      NOP                                    
   813   0658    FFFF                      NOP                                    
   814   065A    FFFF                      NOP                                    
   815   065C    FFFF                      NOP                                    
   816   065E    FFFF                      NOP                                    
   817   0660    FFFF                      NOP                                    
   818   0662    FFFF                      NOP                                    
   819   0664    FFFF                      NOP                                    
   820   0666    FFFF                      NOP                                    
   821   0668    FFFF                      NOP                                    
   822   066A    FFFF                      NOP                                    
   823   066C    FFFF                      NOP                                    
   824   066E    FFFF                      NOP                                    
   825   0670    FFFF                      NOP                                    
   826   0672    FFFF                      NOP                                    
   827   0674    FFFF                      NOP                                    
   828   0676    FFFF                      NOP                                    
   829   0678    FFFF                      NOP                                    
   830   067A    FFFF                      NOP                                    
   831   067C    FFFF                      NOP                                    
   832   067E    FFFF                      NOP                                    
   833   0680    FFFF                      NOP                                    
   834   0682    FFFF                      NOP                                    
   835   0684    FFFF                      NOP                                    
   836   0686    FFFF                      NOP                                    
   837   0688    FFFF                      NOP                                    
   838   068A    FFFF                      NOP                                    
   839   068C    FFFF                      NOP                                    
   840   068E    FFFF                      NOP                                    
   841   0690    FFFF                      NOP                                    
   842   0692    FFFF                      NOP                                    
   843   0694    FFFF                      NOP                                    
   844   0696    FFFF                      NOP                                    
   845   0698    FFFF                      NOP                                    
   846   069A    FFFF                      NOP                                    
   847   069C    FFFF                      NOP                                    
   848   069E    FFFF                      NOP                                    
   849   06A0    FFFF                      NOP                                    
   850   06A2    FFFF                      NOP                                    
   851   06A4    FFFF                      NOP                                    
   852   06A6    FFFF                      NOP                                    
   853   06A8    FFFF                      NOP                                    
   854   06AA    FFFF                      NOP                                    
   855   06AC    FFFF                      NOP                                    
   856   06AE    FFFF                      NOP                                    
   857   06B0    FFFF                      NOP                                    
   858   06B2    FFFF                      NOP                                    
   859   06B4    FFFF                      NOP                                    
   860   06B6    FFFF                      NOP                                    
   861   06B8    FFFF                      NOP                                    
   862   06BA    FFFF                      NOP                                    
   863   06BC    FFFF                      NOP                                    
   864   06BE    FFFF                      NOP                                    
   865   06C0    FFFF                      NOP                                    
   866   06C2    FFFF                      NOP                                    
   867   06C4    FFFF                      NOP                                    
   868   06C6    FFFF                      NOP                                    
   869   06C8    FFFF                      NOP                                    
   870   06CA    FFFF                      NOP                                    
   871   06CC    FFFF                      NOP                                    
   872   06CE    FFFF                      NOP                                    
   873   06D0    FFFF                      NOP                                    
   874   06D2    FFFF                      NOP                                    
   875   06D4    FFFF                      NOP                                    
   876   06D6    FFFF                      NOP                                    
   877   06D8    FFFF                      NOP                                    
   878   06DA    FFFF                      NOP                                    
   879   06DC    FFFF                      NOP                                    
   880   06DE    FFFF                      NOP                                    
   881   06E0    FFFF                      NOP                                    
   882   06E2    FFFF                      NOP                                    
   883   06E4    FFFF                      NOP                                    
   884   06E6    FFFF                      NOP                                    
   885   06E8    FFFF                      NOP                                    
   886   06EA    FFFF                      NOP                                    
   887   06EC    FFFF                      NOP                                    
   888   06EE    FFFF                      NOP                                    
   889   06F0    FFFF                      NOP                                    
   890   06F2    FFFF                      NOP                                    
   891   06F4    FFFF                      NOP                                    
   892   06F6    FFFF                      NOP                                    
   893   06F8    FFFF                      NOP                                    
   894   06FA    FFFF                      NOP                                    
   895   06FC    FFFF                      NOP                                    
   896   06FE    FFFF                      NOP                                    
   897   0700    FFFF                      NOP                                    
   898   0702    FFFF                      NOP                                    
   899   0704    FFFF                      NOP                                    
   900   0706    FFFF                      NOP                                    
   901   0708    FFFF                      NOP                                    
   902   070A    FFFF                      NOP                                    
   903   070C    FFFF                      NOP                                    
   904   070E    FFFF                      NOP                                    
   905   0710    FFFF                      NOP                                    
   906   0712    FFFF                      NOP                                    
   907   0714    FFFF                      NOP                                    
   908   0716    FFFF                      NOP                                    
   909   0718    FFFF                      NOP                                    
   910   071A    FFFF                      NOP                                    
   911   071C    FFFF                      NOP                                    
   912   071E    FFFF                      NOP                                    
   913   0720    FFFF                      NOP                                    
   914   0722    FFFF                      NOP                                    
   915   0724    FFFF                      NOP                                    
   916   0726    FFFF                      NOP                                    
   917   0728    FFFF                      NOP                                    
   918   072A    FFFF                      NOP                                    
   919   072C    FFFF                      NOP                                    
   920   072E    FFFF                      NOP                                    
   921   0730    FFFF                      NOP                                    
   922   0732    FFFF                      NOP                                    
   923   0734    FFFF                      NOP                                    
   924   0736    FFFF                      NOP                                    
   925   0738    FFFF                      NOP                                    
   926   073A    FFFF                      NOP                                    
   927   073C    FFFF                      NOP                                    
   928   073E    FFFF                      NOP                                    
   929   0740    FFFF                      NOP                                    
   930   0742    FFFF                      NOP                                    
   931   0744    FFFF                      NOP                                    
   932   0746    FFFF                      NOP                                    
   933   0748    FFFF                      NOP                                    
   934   074A    FFFF                      NOP                                    
   935   074C    FFFF                      NOP                                    
   936   074E    FFFF                      NOP                                    
   937   0750    FFFF                      NOP                                    
   938   0752    FFFF                      NOP                                    
   939   0754    FFFF                      NOP                                    
   940   0756    FFFF                      NOP                                    
   941   0758    FFFF                      NOP                                    
   942   075A    FFFF                      NOP                                    
   943   075C    FFFF                      NOP                                    
   944   075E    FFFF                      NOP                                    
   945   0760    FFFF                      NOP                                    
   946   0762    FFFF                      NOP                                    
   947   0764    FFFF                      NOP                                    
   948   0766    FFFF                      NOP                                    
   949   0768    FFFF                      NOP                                    
   950   076A    FFFF                      NOP                                    
   951   076C    FFFF                      NOP                                    
   952   076E    FFFF                      NOP                                    
   953   0770    FFFF                      NOP                                    
   954   0772    FFFF                      NOP                                    
   955   0774    FFFF                      NOP                                    
   956   0776    FFFF                      NOP                                    
   957   0778    FFFF                      NOP                                    
   958   077A    FFFF                      NOP                                    
   959   077C    FFFF                      NOP                                    
   960   077E    FFFF                      NOP                                    
   961   0780    FFFF                      NOP                                    
   962   0782    FFFF                      NOP                                    
   963   0784    FFFF                      NOP                                    
   964   0786    FFFF                      NOP                                    
   965   0788    FFFF                      NOP                                    
   966   078A    FFFF                      NOP                                    
   967   078C    FFFF                      NOP                                    
   968   078E    FFFF                      NOP                                    
   969   0790    FFFF                      NOP                                    
   970   0792    FFFF                      NOP                                    
   971   0794    FFFF                      NOP                                    
   972   0796    FFFF                      NOP                                    
   973   0798    FFFF                      NOP                                    
   974   079A    FFFF                      NOP                                    
   975   079C    FFFF                      NOP                                    
   976   079E    FFFF                      NOP                                    
   977   07A0    FFFF                      NOP                                    
   978   07A2    FFFF                      NOP                                    
   979   07A4    FFFF                      NOP                                    
   980   07A6    FFFF                      NOP                                    
   981   07A8    FFFF                      NOP                                    
   982   07AA    FFFF                      NOP                                    
   983   07AC    FFFF                      NOP                                    
   984   07AE    FFFF                      NOP                                    
   985   07B0    FFFF                      NOP                                    
   986   07B2    FFFF                      NOP                                    
   987   07B4    FFFF                      NOP                                    
   988   07B6    FFFF                      NOP                                    
   989   07B8    FFFF                      NOP                                    
   990   07BA    FFFF                      NOP                                    
   991   07BC    FFFF                      NOP                                    
   992   07BE    FFFF                      NOP                                    
   993   07C0    FFFF                      NOP                                    
   994   07C2    FFFF                      NOP                                    
   995   07C4    FFFF                      NOP                                    
   996   07C6    FFFF                      NOP                                    
   997   07C8    FFFF                      NOP                                    
   998   07CA    FFFF                      NOP                                    
   999   07CC    FFFF                      NOP                                    
  1000   07CE    FFFF                      NOP                                    
  1001   07D0    FFFF                      NOP                                    
  1002   07D2    FFFF                      NOP                                    
  1003   07D4    FFFF                      NOP                                    
  1004   07D6    FFFF                      NOP                                    
  1005   07D8    FFFF                      NOP                                    
  1006   07DA    FFFF                      NOP                                    
  1007   07DC    FFFF                      NOP                                    
  1008   07DE    FFFF                      NOP                                    
  1009   07E0    FFFF                      NOP                                    
  1010   07E2    FFFF                      NOP                                    
  1011   07E4    FFFF                      NOP                                    
  1012   07E6    FFFF                      NOP                                    
  1013   07E8    FFFF                      NOP                                    
  1014   07EA    FFFF                      NOP                                    
  1015   07EC    FFFF                      NOP                                    
  1016   07EE    FFFF                      NOP                                    
  1017   07F0    FFFF                      NOP                                    
  1018   07F2    FFFF                      NOP                                    
  1019   07F4    FFFF                      NOP                                    
  1020   07F6    FFFF                      NOP                                    
  1021   07F8    FFFF                      NOP                                    
  1022   07FA    FFFF                      NOP                                    
  1023   07FC    FFFF                      NOP                                    
  1024   07FE    FFFF                      NOP                                    
  1025   0800    EFBE _reset               GOTO _startup                          
  1026   0802    F001                      NOP                                    
  1027   0804    0012                      RETURN 0                               
  1028   0806    0012 __init               RETURN 0                               
  1029   0808    EF8A Remapped_High_ISR    GOTO InterruptHandlerHigh              
  1030   080A    F000                      NOP                                    
  1031   080C    0012                      RETURN 0                               
  1032   080E    FFFF                      NOP                                    
  1033   0810    FFFF                      NOP                                    
  1034   0812    FFFF                      NOP                                    
  1035   0814    FFFF                      NOP                                    
  1036   0816    FFFF                      NOP                                    
  1037   0818    EF9E Remapped_Low_ISR     GOTO InterruptHandlerLow               
  1038   081A    F000                      NOP                                    
  1039   081C    0012                      RETURN 0                               
  1040   081E    CFD9 usb_init             MOVFF FSR2, POSTINC1                   
  1041   0820    FFE6                      NOP                                    
  1042   0822    CFE1                      MOVFF FSR1L, FSR2                      
  1043   0824    FFD9                      NOP                                    
  1044   0826    0EFC                      MOVLW 0xfc                             
  1045   0828    CFDB                      MOVFF PLUSW2, usb_device_descriptor    
  1046   082A    F060                      NOP                                    
  1047   082C    0EFD                      MOVLW 0xfd                             
  1048   082E    CFDB                      MOVFF PLUSW2, 0x61                     
  1049   0830    F061                      NOP                                    
  1050   0832    0EFE                      MOVLW 0xfe                             
  1051   0834    CFDB                      MOVFF PLUSW2, 0x62                     
  1052   0836    F062                      NOP                                    
  1053   0838    0EF9                      MOVLW 0xf9                             
  1054   083A    CFDB                      MOVFF PLUSW2, usb_config_descriptor    
  1055   083C    F063                      NOP                                    
  1056   083E    0EFA                      MOVLW 0xfa                             
  1057   0840    CFDB                      MOVFF PLUSW2, 0x64                     
  1058   0842    F064                      NOP                                    
  1059   0844    0EFB                      MOVLW 0xfb                             
  1060   0846    CFDB                      MOVFF PLUSW2, 0x65                     
  1061   0848    F065                      NOP                                    
  1062   084A    0EF6                      MOVLW 0xf6                             
  1063   084C    CFDB                      MOVFF PLUSW2, usb_string_descriptor    
  1064   084E    F066                      NOP                                    
  1065   0850    0EF7                      MOVLW 0xf7                             
  1066   0852    CFDB                      MOVFF PLUSW2, 0x67                     
  1067   0854    F067                      NOP                                    
  1068   0856    0EF8                      MOVLW 0xf8                             
  1069   0858    CFDB                      MOVFF PLUSW2, 0x68                     
  1070   085A    F068                      NOP                                    
  1071   085C    0EF4                      MOVLW 0xf4                             
  1072   085E    CFDB                      MOVFF PLUSW2, usb_num_string_descriptors
  1073   0860    F069                      NOP                                    
  1074   0862    0EF5                      MOVLW 0xf5                             
  1075   0864    CFDB                      MOVFF PLUSW2, 0x6a                     
  1076   0866    F06A                      NOP                                    
  1077   0868    0100                      MOVLB 0                                
  1078   086A    6B6B                      CLRF sof_handler, BANKED               
  1079   086C    6B6C                      CLRF 0x6c, BANKED                      
  1080   086E    6B6D                      CLRF class_setup_handler, BANKED       
  1081   0870    6B6E                      CLRF 0x6e, BANKED                      
  1082   0872    6B6F                      CLRF vendor_setup_handler, BANKED      
  1083   0874    6B70                      CLRF 0x70, BANKED                      
  1084   0876    0E00                      MOVLW 0                                
  1085   0878    6EE6                      MOVWF POSTINC1, ACCESS                 
  1086   087A    6AE6                      CLRF POSTINC1, ACCESS                  
  1087   087C    6EE6                      MOVWF POSTINC1, ACCESS                 
  1088   087E    6AE6                      CLRF POSTINC1, ACCESS                  
  1089   0880    ECA5                      CALL usb_set_in_handler, 0             
  1090   0882    F00B                      NOP                                    
  1091   0884    52E5                      MOVF POSTDEC1, F, ACCESS               
  1092   0886    52E5                      MOVF POSTDEC1, F, ACCESS               
  1093   0888    52E5                      MOVF POSTDEC1, F, ACCESS               
  1094   088A    52E5                      MOVF POSTDEC1, F, ACCESS               
  1095   088C    0E00                      MOVLW 0                                
  1096   088E    6EE6                      MOVWF POSTINC1, ACCESS                 
  1097   0890    6AE6                      CLRF POSTINC1, ACCESS                  
  1098   0892    6EE6                      MOVWF POSTINC1, ACCESS                 
  1099   0894    6AE6                      CLRF POSTINC1, ACCESS                  
  1100   0896    ECC3                      CALL usb_set_out_handler, 0            
  1101   0898    F00B                      NOP                                    
  1102   089A    52E5                      MOVF POSTDEC1, F, ACCESS               
  1103   089C    52E5                      MOVF POSTDEC1, F, ACCESS               
  1104   089E    52E5                      MOVF POSTDEC1, F, ACCESS               
  1105   08A0    52E5                      MOVF POSTDEC1, F, ACCESS               
  1106   08A2    D820                      RCALL ClearUSBtoDefault                
  1107   08A4    0E14                      MOVLW 0x14                             
  1108   08A6    6E61                      MOVWF UCFG, ACCESS                     
  1109   08A8    9864                      BCF UCON, 0x4, ACCESS                  
  1110   08AA    52E5                      MOVF POSTDEC1, F, ACCESS               
  1111   08AC    CFE7                      MOVFF INDF1, FSR2                      
  1112   08AE    FFD9                      NOP                                    
  1113   08B0    0012                      RETURN 0                               
  1114   08B2    8664 usb_start            BSF UCON, 0x3, ACCESS                  
  1115   08B4    0100                      MOVLB 0                                
  1116   08B6    0E01                      MOVLW 0x1                              
  1117   08B8    6F95                      MOVWF usb_device_state, BANKED         
  1118   08BA    BA64                      BTFSC UCON, 0x5, ACCESS                
  1119   08BC    D7FE                      BRA 0x8ba                              
  1120   08BE    0100                      MOVLB 0                                
  1121   08C0    0E04                      MOVLW 0x4                              
  1122   08C2    6F95                      MOVWF usb_device_state, BANKED         
  1123   08C4    0012                      RETURN 0                               
  1124   08C6    010F usb_handle_error     MOVLB 0xf                              
  1125   08C8    6B5F                      CLRF 0x5f, BANKED                      
  1126   08CA    0012                      RETURN 0                               
  1127   08CC    9662 usb_handle_reset     BCF UIR, 0x3, ACCESS                   
  1128   08CE    0100                      MOVLB 0                                
  1129   08D0    6B93                      CLRF usb_current_cfg, BANKED           
  1130   08D2    6B94                      CLRF 0x94, BANKED                      
  1131   08D4    0E04                      MOVLW 0x4                              
  1132   08D6    6F95                      MOVWF usb_device_state, BANKED         
  1133   08D8    6B96                      CLRF usb_addr_pending, BANKED          
  1134   08DA    B662                      BTFSC UIR, 0x3, ACCESS                 
  1135   08DC    D7F7                      BRA usb_handle_reset                   
  1136   08DE    D802                      RCALL ClearUSBtoDefault                
  1137   08E0    9864                      BCF UCON, 0x4, ACCESS                  
  1138   08E2    0012                      RETURN 0                               
  1139   08E4    CFD9 ClearUSBtoDefault    MOVFF FSR2, POSTINC1                   
  1140   08E6    FFE6                      NOP                                    
  1141   08E8    CFE1                      MOVFF FSR1L, FSR2                      
  1142   08EA    FFD9                      NOP                                    
  1143   08EC    0E02                      MOVLW 0x2                              
  1144   08EE    26E1                      ADDWF FSR1L, F, ACCESS                 
  1145   08F0    0100                      MOVLB 0                                
  1146   08F2    6B6B                      CLRF sof_handler, BANKED               
  1147   08F4    6B6C                      CLRF 0x6c, BANKED                      
  1148   08F6    6B6D                      CLRF class_setup_handler, BANKED       
  1149   08F8    6B6E                      CLRF 0x6e, BANKED                      
  1150   08FA    6B6F                      CLRF vendor_setup_handler, BANKED      
  1151   08FC    6B70                      CLRF 0x70, BANKED                      
  1152   08FE    010F                      MOVLB 0xf                              
  1153   0900    6B5C                      CLRF 0x5c, BANKED                      
  1154   0902    8C64                      BSF UCON, 0x6, ACCESS                  
  1155   0904    9C64                      BCF UCON, 0x6, ACCESS                  
  1156   0906    6B5F                      CLRF 0x5f, BANKED                      
  1157   0908    6ADE                      CLRF POSTINC2, ACCESS                  
  1158   090A    6ADD                      CLRF POSTDEC2, ACCESS                  
  1159   090C    CFDE                      MOVFF POSTINC2, __tmp_0                
  1160   090E    F010                      NOP                                    
  1161   0910    CFDD                      MOVFF POSTDEC2, 0x11                   
  1162   0912    F011                      NOP                                    
  1163   0914    90D8                      BCF STATUS, 0, ACCESS                  
  1164   0916    5011                      MOVF 0x11, W, ACCESS                   
  1165   0918    E604                      BN 0x922                               
  1166   091A    0E08                      MOVLW 0x8                              
  1167   091C    5C10                      SUBWF __tmp_0, W, ACCESS               
  1168   091E    0E00                      MOVLW 0                                
  1169   0920    5811                      SUBWFB 0x11, W, ACCESS                 
  1170   0922    E232                      BC 0x988                               
  1171   0924    CFDE                      MOVFF POSTINC2, FSR0L                  
  1172   0926    FFE9                      NOP                                    
  1173   0928    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1174   092A    FFEA                      NOP                                    
  1175   092C    90D8                      BCF STATUS, 0, ACCESS                  
  1176   092E    36E9                      RLCF FSR0L, F, ACCESS                  
  1177   0930    36EA                      RLCF FSR0H, F, ACCESS                  
  1178   0932    90D8                      BCF STATUS, 0, ACCESS                  
  1179   0934    36E9                      RLCF FSR0L, F, ACCESS                  
  1180   0936    36EA                      RLCF FSR0H, F, ACCESS                  
  1181   0938    0E71                      MOVLW 0x71                             
  1182   093A    26E9                      ADDWF FSR0L, F, ACCESS                 
  1183   093C    0E00                      MOVLW 0                                
  1184   093E    22EA                      ADDWFC FSR0H, F, ACCESS                
  1185   0940    0E02                      MOVLW 0x2                              
  1186   0942    26E9                      ADDWF FSR0L, F, ACCESS                 
  1187   0944    0E00                      MOVLW 0                                
  1188   0946    22EA                      ADDWFC FSR0H, F, ACCESS                
  1189   0948    6AEE                      CLRF POSTINC0, ACCESS                  
  1190   094A    6AED                      CLRF POSTDEC0, ACCESS                  
  1191   094C    CFDE                      MOVFF POSTINC2, FSR0L                  
  1192   094E    FFE9                      NOP                                    
  1193   0950    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1194   0952    FFEA                      NOP                                    
  1195   0954    90D8                      BCF STATUS, 0, ACCESS                  
  1196   0956    36E9                      RLCF FSR0L, F, ACCESS                  
  1197   0958    36EA                      RLCF FSR0H, F, ACCESS                  
  1198   095A    90D8                      BCF STATUS, 0, ACCESS                  
  1199   095C    36E9                      RLCF FSR0L, F, ACCESS                  
  1200   095E    36EA                      RLCF FSR0H, F, ACCESS                  
  1201   0960    0E71                      MOVLW 0x71                             
  1202   0962    26E9                      ADDWF FSR0L, F, ACCESS                 
  1203   0964    0E00                      MOVLW 0                                
  1204   0966    22EA                      ADDWFC FSR0H, F, ACCESS                
  1205   0968    6AEE                      CLRF POSTINC0, ACCESS                  
  1206   096A    6AED                      CLRF POSTDEC0, ACCESS                  
  1207   096C    CFDE                      MOVFF POSTINC2, FSR0L                  
  1208   096E    FFE9                      NOP                                    
  1209   0970    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1210   0972    FFEA                      NOP                                    
  1211   0974    0E53                      MOVLW 0x53                             
  1212   0976    26E9                      ADDWF FSR0L, F, ACCESS                 
  1213   0978    0E0F                      MOVLW 0xf                              
  1214   097A    22EA                      ADDWFC FSR0H, F, ACCESS                
  1215   097C    6AEF                      CLRF INDF0, ACCESS                     
  1216   097E    2ADF                      INCF INDF2, F, ACCESS                  
  1217   0980    0E01                      MOVLW 0x1                              
  1218   0982    E301                      BNC 0x986                              
  1219   0984    2ADB                      INCF PLUSW2, F, ACCESS                 
  1220   0986    D7C2                      BRA 0x90c                              
  1221   0988    6ADE                      CLRF POSTINC2, ACCESS                  
  1222   098A    6ADD                      CLRF POSTDEC2, ACCESS                  
  1223   098C    CFDE                      MOVFF POSTINC2, __tmp_0                
  1224   098E    F010                      NOP                                    
  1225   0990    CFDD                      MOVFF POSTDEC2, 0x11                   
  1226   0992    F011                      NOP                                    
  1227   0994    90D8                      BCF STATUS, 0, ACCESS                  
  1228   0996    5011                      MOVF 0x11, W, ACCESS                   
  1229   0998    E604                      BN 0x9a2                               
  1230   099A    0E06                      MOVLW 0x6                              
  1231   099C    5C10                      SUBWF __tmp_0, W, ACCESS               
  1232   099E    0E00                      MOVLW 0                                
  1233   09A0    5811                      SUBWFB 0x11, W, ACCESS                 
  1234   09A2    E214                      BC 0x9cc                               
  1235   09A4    CFDE                      MOVFF POSTINC2, FSR0L                  
  1236   09A6    FFE9                      NOP                                    
  1237   09A8    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1238   09AA    FFEA                      NOP                                    
  1239   09AC    90D8                      BCF STATUS, 0, ACCESS                  
  1240   09AE    36E9                      RLCF FSR0L, F, ACCESS                  
  1241   09B0    36EA                      RLCF FSR0H, F, ACCESS                  
  1242   09B2    90D8                      BCF STATUS, 0, ACCESS                  
  1243   09B4    36E9                      RLCF FSR0L, F, ACCESS                  
  1244   09B6    36EA                      RLCF FSR0H, F, ACCESS                  
  1245   09B8    0E00                      MOVLW 0                                
  1246   09BA    26E9                      ADDWF FSR0L, F, ACCESS                 
  1247   09BC    0E02                      MOVLW 0x2                              
  1248   09BE    22EA                      ADDWFC FSR0H, F, ACCESS                
  1249   09C0    6AEF                      CLRF INDF0, ACCESS                     
  1250   09C2    2ADF                      INCF INDF2, F, ACCESS                  
  1251   09C4    0E01                      MOVLW 0x1                              
  1252   09C6    E301                      BNC 0x9ca                              
  1253   09C8    2ADB                      INCF PLUSW2, F, ACCESS                 
  1254   09CA    D7E0                      BRA 0x98c                              
  1255   09CC    010F                      MOVLB 0xf                              
  1256   09CE    0E16                      MOVLW 0x16                             
  1257   09D0    6F53                      MOVWF 0x53, BANKED                     
  1258   09D2    0100                      MOVLB 0                                
  1259   09D4    6B91                      CLRF usb_device_status, BANKED         
  1260   09D6    6B92                      CLRF 0x92, BANKED                      
  1261   09D8    6B95                      CLRF usb_device_state, BANKED          
  1262   09DA    6B93                      CLRF usb_current_cfg, BANKED           
  1263   09DC    6B94                      CLRF 0x94, BANKED                      
  1264   09DE    6B96                      CLRF usb_addr_pending, BANKED          
  1265   09E0    0102                      MOVLB 0x2                              
  1266   09E2    0E08                      MOVLW 0x8                              
  1267   09E4    6F01                      MOVWF 0x1, BANKED                      
  1268   09E6    0E40                      MOVLW 0x40                             
  1269   09E8    6F02                      MOVWF reply_len, BANKED                
  1270   09EA    0E02                      MOVLW 0x2                              
  1271   09EC    6F03                      MOVWF dir, BANKED                      
  1272   09EE    0E88                      MOVLW 0x88                             
  1273   09F0    6F00                      MOVWF RecvdByte, BANKED                
  1274   09F2    6B05                      CLRF 0x5, BANKED                       
  1275   09F4    0E48                      MOVLW 0x48                             
  1276   09F6    6F06                      MOVWF pUEP, BANKED                     
  1277   09F8    0E02                      MOVLW 0x2                              
  1278   09FA    6F07                      MOVWF 0x7, BANKED                      
  1279   09FC    0E48                      MOVLW 0x48                             
  1280   09FE    6F04                      MOVWF dwBaudrem, BANKED                
  1281   0A00    0E02                      MOVLW 0x2                              
  1282   0A02    5CE1                      SUBWF FSR1L, W, ACCESS                 
  1283   0A04    E202                      BC 0xa0a                               
  1284   0A06    6AE1                      CLRF FSR1L, ACCESS                     
  1285   0A08    52E5                      MOVF POSTDEC1, F, ACCESS               
  1286   0A0A    6EE1                      MOVWF FSR1L, ACCESS                    
  1287   0A0C    52E5                      MOVF POSTDEC1, F, ACCESS               
  1288   0A0E    CFE7                      MOVFF INDF1, FSR2                      
  1289   0A10    FFD9                      NOP                                    
  1290   0A12    0012                      RETURN 0                               
  1291   0A14    A862 usb_handler          BTFSS UIR, 0x4, ACCESS                 
  1292   0A16    D003                      BRA 0xa1e                              
  1293   0A18    EC89                      CALL USBSuspend, 0                     
  1294   0A1A    F000                      NOP                                    
  1295   0A1C    9862                      BCF UIR, 0x4, ACCESS                   
  1296   0A1E    A062                      BTFSS UIR, 0, ACCESS                   
  1297   0A20    D002                      BRA 0xa26                              
  1298   0A22    DF54                      RCALL usb_handle_reset                 
  1299   0A24    9062                      BCF UIR, 0, ACCESS                     
  1300   0A26    A262                      BTFSS UIR, 0x1, ACCESS                 
  1301   0A28    D003                      BRA 0xa30                              
  1302   0A2A    010F                      MOVLB 0xf                              
  1303   0A2C    6B5F                      CLRF 0x5f, BANKED                      
  1304   0A2E    9262                      BCF UIR, 0x1, ACCESS                   
  1305   0A30    BA62                      BTFSC UIR, 0x5, ACCESS                 
  1306   0A32    9A62                      BCF UIR, 0x5, ACCESS                   
  1307   0A34    AC62                      BTFSS UIR, 0x6, ACCESS                 
  1308   0A36    D00C                      BRA 0xa50                              
  1309   0A38    0100                      MOVLB 0                                
  1310   0A3A    516B                      MOVF sof_handler, W, BANKED            
  1311   0A3C    116C                      IORWF 0x6c, W, BANKED                  
  1312   0A3E    E007                      BZ 0xa4e                               
  1313   0A40    D005                      BRA 0xa4c                              
  1314   0A42    C06C                      MOVFF 0x6c, PCLATH                     
  1315   0A44    FFFA                      NOP                                    
  1316   0A46    0100                      MOVLB 0                                
  1317   0A48    516B                      MOVF sof_handler, W, BANKED            
  1318   0A4A    6EF9                      MOVWF PCL, ACCESS                      
  1319   0A4C    DFFA                      RCALL 0xa42                            
  1320   0A4E    9C62                      BCF UIR, 0x6, ACCESS                   
  1321   0A50    A662                      BTFSS UIR, 0x3, ACCESS                 
  1322   0A52    D009                      BRA 0xa66                              
  1323   0A54    5063                      MOVF USTAT, W, ACCESS                  
  1324   0A56    40E8                      RRNCF WREG, W, ACCESS                  
  1325   0A58    40E8                      RRNCF WREG, W, ACCESS                  
  1326   0A5A    40E8                      RRNCF WREG, W, ACCESS                  
  1327   0A5C    0B1F                      ANDLW 0x1f                             
  1328   0A5E    0B0F                      ANDLW 0xf                              
  1329   0A60    E101                      BNZ 0xa64                              
  1330   0A62    D802                      RCALL usb_handle_transaction           
  1331   0A64    9662                      BCF UIR, 0x3, ACCESS                   
  1332   0A66    0012                      RETURN 0                               
  1333   0A68    0100 usb_handle_transaction MOVLB 0                                
  1334   0A6A    6BA1                      CLRF usbrequesterrorflag, BANKED       
  1335   0A6C    CF63                      MOVFF USTAT, trn_status                
  1336   0A6E    F097                      NOP                                    
  1337   0A70    5197                      MOVF trn_status, W, BANKED             
  1338   0A72    0BFC                      ANDLW 0xfc                             
  1339   0A74    42E8                      RRNCF WREG, F, ACCESS                  
  1340   0A76    42E8                      RRNCF WREG, F, ACCESS                  
  1341   0A78    0D04                      MULLW 0x4                              
  1342   0A7A    CFF3                      MOVFF PRODL, EP0_Outbdp                
  1343   0A7C    F098                      NOP                                    
  1344   0A7E    CFF4                      MOVFF PRODH, 0x99                      
  1345   0A80    F099                      NOP                                    
  1346   0A82    0E00                      MOVLW 0                                
  1347   0A84    2798                      ADDWF EP0_Outbdp, F, BANKED            
  1348   0A86    0E02                      MOVLW 0x2                              
  1349   0A88    2399                      ADDWFC 0x99, F, BANKED                 
  1350   0A8A    0E04                      MOVLW 0x4                              
  1351   0A8C    1197                      IORWF trn_status, W, BANKED            
  1352   0A8E    0BFC                      ANDLW 0xfc                             
  1353   0A90    42E8                      RRNCF WREG, F, ACCESS                  
  1354   0A92    42E8                      RRNCF WREG, F, ACCESS                  
  1355   0A94    0D04                      MULLW 0x4                              
  1356   0A96    CFF3                      MOVFF PRODL, EP0_Inbdp                 
  1357   0A98    F09A                      NOP                                    
  1358   0A9A    CFF4                      MOVFF PRODH, 0x9b                      
  1359   0A9C    F09B                      NOP                                    
  1360   0A9E    0E00                      MOVLW 0                                
  1361   0AA0    279A                      ADDWF EP0_Inbdp, F, BANKED             
  1362   0AA2    0E02                      MOVLW 0x2                              
  1363   0AA4    239B                      ADDWFC 0x9b, F, BANKED                 
  1364   0AA6    C098                      MOVFF EP0_Outbdp, FSR0L                
  1365   0AA8    FFE9                      NOP                                    
  1366   0AAA    C099                      MOVFF 0x99, FSR0H                      
  1367   0AAC    FFEA                      NOP                                    
  1368   0AAE    50EF                      MOVF INDF0, W, ACCESS                  
  1369   0AB0    0B3C                      ANDLW 0x3c                             
  1370   0AB2    0A24                      XORLW 0x24                             
  1371   0AB4    E00A                      BZ 0xaca                               
  1372   0AB6    0A20                      XORLW 0x20                             
  1373   0AB8    E005                      BZ 0xac4                               
  1374   0ABA    0A30                      XORLW 0x30                             
  1375   0ABC    E001                      BZ 0xac0                               
  1376   0ABE    D008                      BRA 0xad0                              
  1377   0AC0    D808                      RCALL usb_handle_setup                 
  1378   0AC2    D006                      BRA 0xad0                              
  1379   0AC4    EC46                      CALL usb_handle_out, 0                 
  1380   0AC6    F00B                      NOP                                    
  1381   0AC8    D003                      BRA 0xad0                              
  1382   0ACA    EC19                      CALL usb_handle_in, 0                  
  1383   0ACC    F00B                      NOP                                    
  1384   0ACE    D000                      BRA 0xad0                              
  1385   0AD0    0012                      RETURN 0                               
  1386   0AD2    C09A usb_handle_setup     MOVFF EP0_Inbdp, FSR0L                 
  1387   0AD4    FFE9                      NOP                                    
  1388   0AD6    C09B                      MOVFF 0x9b, FSR0H                      
  1389   0AD8    FFEA                      NOP                                    
  1390   0ADA    0E08                      MOVLW 0x8                              
  1391   0ADC    6EEF                      MOVWF INDF0, ACCESS                    
  1392   0ADE    9864                      BCF UCON, 0x4, ACCESS                  
  1393   0AE0    C098                      MOVFF EP0_Outbdp, FSR0L                
  1394   0AE2    FFE9                      NOP                                    
  1395   0AE4    C099                      MOVFF 0x99, FSR0H                      
  1396   0AE6    FFEA                      NOP                                    
  1397   0AE8    0E02                      MOVLW 0x2                              
  1398   0AEA    26E9                      ADDWF FSR0L, F, ACCESS                 
  1399   0AEC    0E00                      MOVLW 0                                
  1400   0AEE    22EA                      ADDWFC FSR0H, F, ACCESS                
  1401   0AF0    50EE                      MOVF POSTINC0, W, ACCESS               
  1402   0AF2    CFEF                      MOVFF INDF0, FSR0H                     
  1403   0AF4    FFEA                      NOP                                    
  1404   0AF6    6EE9                      MOVWF FSR0L, ACCESS                    
  1405   0AF8    50EF                      MOVF INDF0, W, ACCESS                  
  1406   0AFA    0B60                      ANDLW 0x60                             
  1407   0AFC    0A40                      XORLW 0x40                             
  1408   0AFE    E042                      BZ 0xb84                               
  1409   0B00    0A60                      XORLW 0x60                             
  1410   0B02    E034                      BZ 0xb6c                               
  1411   0B04    0A20                      XORLW 0x20                             
  1412   0B06    E001                      BZ 0xb0a                               
  1413   0B08    D049                      BRA 0xb9c                              
  1414   0B0A    C098                      MOVFF EP0_Outbdp, FSR0L                
  1415   0B0C    FFE9                      NOP                                    
  1416   0B0E    C099                      MOVFF 0x99, FSR0H                      
  1417   0B10    FFEA                      NOP                                    
  1418   0B12    0E02                      MOVLW 0x2                              
  1419   0B14    26E9                      ADDWF FSR0L, F, ACCESS                 
  1420   0B16    0E00                      MOVLW 0                                
  1421   0B18    22EA                      ADDWFC FSR0H, F, ACCESS                
  1422   0B1A    50EE                      MOVF POSTINC0, W, ACCESS               
  1423   0B1C    CFEF                      MOVFF INDF0, FSR0H                     
  1424   0B1E    FFEA                      NOP                                    
  1425   0B20    6EE9                      MOVWF FSR0L, ACCESS                    
  1426   0B22    50EF                      MOVF INDF0, W, ACCESS                  
  1427   0B24    0B03                      ANDLW 0x3                              
  1428   0B26    0A02                      XORLW 0x2                              
  1429   0B28    E015                      BZ 0xb54                               
  1430   0B2A    0A03                      XORLW 0x3                              
  1431   0B2C    E00B                      BZ 0xb44                               
  1432   0B2E    0A01                      XORLW 0x1                              
  1433   0B30    E001                      BZ 0xb34                               
  1434   0B32    D019                      BRA 0xb66                              
  1435   0B34    C098                      MOVFF EP0_Outbdp, POSTINC1             
  1436   0B36    FFE6                      NOP                                    
  1437   0B38    C099                      MOVFF 0x99, POSTINC1                   
  1438   0B3A    FFE6                      NOP                                    
  1439   0B3C    D87C                      RCALL usb_handle_StandardDeviceRequest 
  1440   0B3E    52E5                      MOVF POSTDEC1, F, ACCESS               
  1441   0B40    52E5                      MOVF POSTDEC1, F, ACCESS               
  1442   0B42    D013                      BRA 0xb6a                              
  1443   0B44    C098                      MOVFF EP0_Outbdp, POSTINC1             
  1444   0B46    FFE6                      NOP                                    
  1445   0B48    C099                      MOVFF 0x99, POSTINC1                   
  1446   0B4A    FFE6                      NOP                                    
  1447   0B4C    DB80                      RCALL usb_handle_StandardInterfaceRequest
  1448   0B4E    52E5                      MOVF POSTDEC1, F, ACCESS               
  1449   0B50    52E5                      MOVF POSTDEC1, F, ACCESS               
  1450   0B52    D00B                      BRA 0xb6a                              
  1451   0B54    C098                      MOVFF EP0_Outbdp, POSTINC1             
  1452   0B56    FFE6                      NOP                                    
  1453   0B58    C099                      MOVFF 0x99, POSTINC1                   
  1454   0B5A    FFE6                      NOP                                    
  1455   0B5C    ECC4                      CALL usb_handle_StandardEndpointRequest, 0
  1456   0B5E    F009                      NOP                                    
  1457   0B60    52E5                      MOVF POSTDEC1, F, ACCESS               
  1458   0B62    52E5                      MOVF POSTDEC1, F, ACCESS               
  1459   0B64    D002                      BRA 0xb6a                              
  1460   0B66    EC05                      CALL usb_RequestError, 0               
  1461   0B68    F00C                      NOP                                    
  1462   0B6A    D01A                      BRA 0xba0                              
  1463   0B6C    0100                      MOVLB 0                                
  1464   0B6E    516D                      MOVF class_setup_handler, W, BANKED    
  1465   0B70    116E                      IORWF 0x6e, W, BANKED                  
  1466   0B72    E007                      BZ 0xb82                               
  1467   0B74    D005                      BRA 0xb80                              
  1468   0B76    C06E                      MOVFF 0x6e, PCLATH                     
  1469   0B78    FFFA                      NOP                                    
  1470   0B7A    0100                      MOVLB 0                                
  1471   0B7C    516D                      MOVF class_setup_handler, W, BANKED    
  1472   0B7E    6EF9                      MOVWF PCL, ACCESS                      
  1473   0B80    DFFA                      RCALL 0xb76                            
  1474   0B82    D00E                      BRA 0xba0                              
  1475   0B84    0100                      MOVLB 0                                
  1476   0B86    516F                      MOVF vendor_setup_handler, W, BANKED   
  1477   0B88    1170                      IORWF 0x70, W, BANKED                  
  1478   0B8A    E007                      BZ 0xb9a                               
  1479   0B8C    D005                      BRA 0xb98                              
  1480   0B8E    C06E                      MOVFF 0x6e, PCLATH                     
  1481   0B90    FFFA                      NOP                                    
  1482   0B92    0100                      MOVLB 0                                
  1483   0B94    516D                      MOVF class_setup_handler, W, BANKED    
  1484   0B96    6EF9                      MOVWF PCL, ACCESS                      
  1485   0B98    DFFA                      RCALL 0xb8e                            
  1486   0B9A    D002                      BRA 0xba0                              
  1487   0B9C    EC05                      CALL usb_RequestError, 0               
  1488   0B9E    F00C                      NOP                                    
  1489   0BA0    C098                      MOVFF EP0_Outbdp, FSR0L                
  1490   0BA2    FFE9                      NOP                                    
  1491   0BA4    C099                      MOVFF 0x99, FSR0H                      
  1492   0BA6    FFEA                      NOP                                    
  1493   0BA8    52EE                      MOVF POSTINC0, F, ACCESS               
  1494   0BAA    0E08                      MOVLW 0x8                              
  1495   0BAC    6EEF                      MOVWF INDF0, ACCESS                    
  1496   0BAE    C098                      MOVFF EP0_Outbdp, FSR0L                
  1497   0BB0    FFE9                      NOP                                    
  1498   0BB2    C099                      MOVFF 0x99, FSR0H                      
  1499   0BB4    FFEA                      NOP                                    
  1500   0BB6    0E02                      MOVLW 0x2                              
  1501   0BB8    26E9                      ADDWF FSR0L, F, ACCESS                 
  1502   0BBA    0E00                      MOVLW 0                                
  1503   0BBC    22EA                      ADDWFC FSR0H, F, ACCESS                
  1504   0BBE    50EE                      MOVF POSTINC0, W, ACCESS               
  1505   0BC0    CFEF                      MOVFF INDF0, FSR0H                     
  1506   0BC2    FFEA                      NOP                                    
  1507   0BC4    6EE9                      MOVWF FSR0L, ACCESS                    
  1508   0BC6    50EF                      MOVF INDF0, W, ACCESS                  
  1509   0BC8    0B80                      ANDLW 0x80                             
  1510   0BCA    E124                      BNZ 0xc14                              
  1511   0BCC    C098                      MOVFF EP0_Outbdp, FSR0L                
  1512   0BCE    FFE9                      NOP                                    
  1513   0BD0    C099                      MOVFF 0x99, FSR0H                      
  1514   0BD2    FFEA                      NOP                                    
  1515   0BD4    0E02                      MOVLW 0x2                              
  1516   0BD6    26E9                      ADDWF FSR0L, F, ACCESS                 
  1517   0BD8    0E00                      MOVLW 0                                
  1518   0BDA    22EA                      ADDWFC FSR0H, F, ACCESS                
  1519   0BDC    50EE                      MOVF POSTINC0, W, ACCESS               
  1520   0BDE    CFEF                      MOVFF INDF0, FSR0H                     
  1521   0BE0    FFEA                      NOP                                    
  1522   0BE2    6EE9                      MOVWF FSR0L, ACCESS                    
  1523   0BE4    0E06                      MOVLW 0x6                              
  1524   0BE6    26E9                      ADDWF FSR0L, F, ACCESS                 
  1525   0BE8    0E00                      MOVLW 0                                
  1526   0BEA    22EA                      ADDWFC FSR0H, F, ACCESS                
  1527   0BEC    50EF                      MOVF INDF0, W, ACCESS                  
  1528   0BEE    E114                      BNZ 0xc18                              
  1529   0BF0    C098                      MOVFF EP0_Outbdp, FSR0L                
  1530   0BF2    FFE9                      NOP                                    
  1531   0BF4    C099                      MOVFF 0x99, FSR0H                      
  1532   0BF6    FFEA                      NOP                                    
  1533   0BF8    0E02                      MOVLW 0x2                              
  1534   0BFA    26E9                      ADDWF FSR0L, F, ACCESS                 
  1535   0BFC    0E00                      MOVLW 0                                
  1536   0BFE    22EA                      ADDWFC FSR0H, F, ACCESS                
  1537   0C00    50EE                      MOVF POSTINC0, W, ACCESS               
  1538   0C02    CFEF                      MOVFF INDF0, FSR0H                     
  1539   0C04    FFEA                      NOP                                    
  1540   0C06    6EE9                      MOVWF FSR0L, ACCESS                    
  1541   0C08    0E07                      MOVLW 0x7                              
  1542   0C0A    26E9                      ADDWF FSR0L, F, ACCESS                 
  1543   0C0C    0E00                      MOVLW 0                                
  1544   0C0E    22EA                      ADDWFC FSR0H, F, ACCESS                
  1545   0C10    50EF                      MOVF INDF0, W, ACCESS                  
  1546   0C12    E102                      BNZ 0xc18                              
  1547   0C14    0E00                      MOVLW 0                                
  1548   0C16    D001                      BRA 0xc1a                              
  1549   0C18    0E01                      MOVLW 0x1                              
  1550   0C1A    0900                      IORLW 0                                
  1551   0C1C    E002                      BZ 0xc22                               
  1552   0C1E    0EC8                      MOVLW 0xc8                             
  1553   0C20    D001                      BRA 0xc24                              
  1554   0C22    0E88                      MOVLW 0x88                             
  1555   0C24    6EE6                      MOVWF POSTINC1, ACCESS                 
  1556   0C26    C098                      MOVFF EP0_Outbdp, FSR0L                
  1557   0C28    FFE9                      NOP                                    
  1558   0C2A    C099                      MOVFF 0x99, FSR0H                      
  1559   0C2C    FFEA                      NOP                                    
  1560   0C2E    52E5                      MOVF POSTDEC1, F, ACCESS               
  1561   0C30    50E7                      MOVF INDF1, W, ACCESS                  
  1562   0C32    6EEF                      MOVWF INDF0, ACCESS                    
  1563   0C34    0012                      RETURN 0                               
  1564   0C36    CFD9 usb_handle_StandardDeviceRequest MOVFF FSR2, POSTINC1                   
  1565   0C38    FFE6                      NOP                                    
  1566   0C3A    CFE1                      MOVFF FSR1L, FSR2                      
  1567   0C3C    FFD9                      NOP                                    
  1568   0C3E    0E04                      MOVLW 0x4                              
  1569   0C40    26E1                      ADDWF FSR1L, F, ACCESS                 
  1570   0C42    0EFD                      MOVLW 0xfd                             
  1571   0C44    CFDB                      MOVFF PLUSW2, FSR0L                    
  1572   0C46    FFE9                      NOP                                    
  1573   0C48    0EFE                      MOVLW 0xfe                             
  1574   0C4A    CFDB                      MOVFF PLUSW2, FSR0H                    
  1575   0C4C    FFEA                      NOP                                    
  1576   0C4E    0E02                      MOVLW 0x2                              
  1577   0C50    26E9                      ADDWF FSR0L, F, ACCESS                 
  1578   0C52    0E00                      MOVLW 0                                
  1579   0C54    22EA                      ADDWFC FSR0H, F, ACCESS                
  1580   0C56    CFEE                      MOVFF POSTINC0, POSTINC2               
  1581   0C58    FFDE                      NOP                                    
  1582   0C5A    CFED                      MOVFF POSTDEC0, POSTDEC2               
  1583   0C5C    FFDD                      NOP                                    
  1584   0C5E    CFDE                      MOVFF POSTINC2, FSR0L                  
  1585   0C60    FFE9                      NOP                                    
  1586   0C62    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1587   0C64    FFEA                      NOP                                    
  1588   0C66    0E01                      MOVLW 0x1                              
  1589   0C68    26E9                      ADDWF FSR0L, F, ACCESS                 
  1590   0C6A    0E00                      MOVLW 0                                
  1591   0C6C    22EA                      ADDWFC FSR0H, F, ACCESS                
  1592   0C6E    50EF                      MOVF INDF0, W, ACCESS                  
  1593   0C70    0A07                      XORLW 0x7                              
  1594   0C72    E101                      BNZ 0xc76                              
  1595   0C74    D2E1                      BRA 0x1238                             
  1596   0C76    0A0E                      XORLW 0xe                              
  1597   0C78    E101                      BNZ 0xc7c                              
  1598   0C7A    D2B2                      BRA 0x11e0                             
  1599   0C7C    0A01                      XORLW 0x1                              
  1600   0C7E    E101                      BNZ 0xc82                              
  1601   0C80    D29A                      BRA 0x11b6                             
  1602   0C82    0A0E                      XORLW 0xe                              
  1603   0C84    E101                      BNZ 0xc88                              
  1604   0C86    D09F                      BRA 0xdc6                              
  1605   0C88    0A03                      XORLW 0x3                              
  1606   0C8A    E064                      BZ 0xd54                               
  1607   0C8C    0A06                      XORLW 0x6                              
  1608   0C8E    E04B                      BZ 0xd26                               
  1609   0C90    0A02                      XORLW 0x2                              
  1610   0C92    E032                      BZ 0xcf8                               
  1611   0C94    0A01                      XORLW 0x1                              
  1612   0C96    E001                      BZ 0xc9a                               
  1613   0C98    D2CF                      BRA 0x1238                             
  1614   0C9A    0100                      MOVLB 0                                
  1615   0C9C    5191                      MOVF usb_device_status, W, BANKED      
  1616   0C9E    6EE6                      MOVWF POSTINC1, ACCESS                 
  1617   0CA0    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  1618   0CA2    FFE9                      NOP                                    
  1619   0CA4    C09B                      MOVFF 0x9b, FSR0H                      
  1620   0CA6    FFEA                      NOP                                    
  1621   0CA8    0E02                      MOVLW 0x2                              
  1622   0CAA    26E9                      ADDWF FSR0L, F, ACCESS                 
  1623   0CAC    0E00                      MOVLW 0                                
  1624   0CAE    22EA                      ADDWFC FSR0H, F, ACCESS                
  1625   0CB0    50EE                      MOVF POSTINC0, W, ACCESS               
  1626   0CB2    CFEF                      MOVFF INDF0, FSR0H                     
  1627   0CB4    FFEA                      NOP                                    
  1628   0CB6    6EE9                      MOVWF FSR0L, ACCESS                    
  1629   0CB8    52E5                      MOVF POSTDEC1, F, ACCESS               
  1630   0CBA    50E7                      MOVF INDF1, W, ACCESS                  
  1631   0CBC    6EEF                      MOVWF INDF0, ACCESS                    
  1632   0CBE    C092                      MOVFF 0x92, __tmp_0                    
  1633   0CC0    F010                      NOP                                    
  1634   0CC2    6A11                      CLRF 0x11, ACCESS                      
  1635   0CC4    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  1636   0CC6    FFE9                      NOP                                    
  1637   0CC8    C09B                      MOVFF 0x9b, FSR0H                      
  1638   0CCA    FFEA                      NOP                                    
  1639   0CCC    0E02                      MOVLW 0x2                              
  1640   0CCE    26E9                      ADDWF FSR0L, F, ACCESS                 
  1641   0CD0    0E00                      MOVLW 0                                
  1642   0CD2    22EA                      ADDWFC FSR0H, F, ACCESS                
  1643   0CD4    50EE                      MOVF POSTINC0, W, ACCESS               
  1644   0CD6    CFEF                      MOVFF INDF0, FSR0H                     
  1645   0CD8    FFEA                      NOP                                    
  1646   0CDA    6EE9                      MOVWF FSR0L, ACCESS                    
  1647   0CDC    0E01                      MOVLW 0x1                              
  1648   0CDE    26E9                      ADDWF FSR0L, F, ACCESS                 
  1649   0CE0    0E00                      MOVLW 0                                
  1650   0CE2    22EA                      ADDWFC FSR0H, F, ACCESS                
  1651   0CE4    C010                      MOVFF __tmp_0, INDF0                   
  1652   0CE6    FFEF                      NOP                                    
  1653   0CE8    0E02                      MOVLW 0x2                              
  1654   0CEA    6EE6                      MOVWF POSTINC1, ACCESS                 
  1655   0CEC    6AE6                      CLRF POSTINC1, ACCESS                  
  1656   0CEE    ECE5                      CALL usb_ack_dat1, 0                   
  1657   0CF0    F00B                      NOP                                    
  1658   0CF2    52E5                      MOVF POSTDEC1, F, ACCESS               
  1659   0CF4    52E5                      MOVF POSTDEC1, F, ACCESS               
  1660   0CF6    D2A1                      BRA 0x123a                             
  1661   0CF8    CFDE                      MOVFF POSTINC2, FSR0L                  
  1662   0CFA    FFE9                      NOP                                    
  1663   0CFC    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1664   0CFE    FFEA                      NOP                                    
  1665   0D00    0E02                      MOVLW 0x2                              
  1666   0D02    26E9                      ADDWF FSR0L, F, ACCESS                 
  1667   0D04    0E00                      MOVLW 0                                
  1668   0D06    22EA                      ADDWFC FSR0H, F, ACCESS                
  1669   0D08    04EF                      DECF INDF0, W, ACCESS                  
  1670   0D0A    E10A                      BNZ 0xd20                              
  1671   0D0C    0100                      MOVLB 0                                
  1672   0D0E    9391                      BCF usb_device_status, 0x1, BANKED     
  1673   0D10    0E00                      MOVLW 0                                
  1674   0D12    6EE6                      MOVWF POSTINC1, ACCESS                 
  1675   0D14    6AE6                      CLRF POSTINC1, ACCESS                  
  1676   0D16    ECE5                      CALL usb_ack_dat1, 0                   
  1677   0D18    F00B                      NOP                                    
  1678   0D1A    52E5                      MOVF POSTDEC1, F, ACCESS               
  1679   0D1C    52E5                      MOVF POSTDEC1, F, ACCESS               
  1680   0D1E    D002                      BRA 0xd24                              
  1681   0D20    EC05                      CALL usb_RequestError, 0               
  1682   0D22    F00C                      NOP                                    
  1683   0D24    D28A                      BRA 0x123a                             
  1684   0D26    CFDE                      MOVFF POSTINC2, FSR0L                  
  1685   0D28    FFE9                      NOP                                    
  1686   0D2A    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1687   0D2C    FFEA                      NOP                                    
  1688   0D2E    0E02                      MOVLW 0x2                              
  1689   0D30    26E9                      ADDWF FSR0L, F, ACCESS                 
  1690   0D32    0E00                      MOVLW 0                                
  1691   0D34    22EA                      ADDWFC FSR0H, F, ACCESS                
  1692   0D36    04EF                      DECF INDF0, W, ACCESS                  
  1693   0D38    E10A                      BNZ 0xd4e                              
  1694   0D3A    0100                      MOVLB 0                                
  1695   0D3C    8391                      BSF usb_device_status, 0x1, BANKED     
  1696   0D3E    0E00                      MOVLW 0                                
  1697   0D40    6EE6                      MOVWF POSTINC1, ACCESS                 
  1698   0D42    6AE6                      CLRF POSTINC1, ACCESS                  
  1699   0D44    ECE5                      CALL usb_ack_dat1, 0                   
  1700   0D46    F00B                      NOP                                    
  1701   0D48    52E5                      MOVF POSTDEC1, F, ACCESS               
  1702   0D4A    52E5                      MOVF POSTDEC1, F, ACCESS               
  1703   0D4C    D002                      BRA 0xd52                              
  1704   0D4E    EC05                      CALL usb_RequestError, 0               
  1705   0D50    F00C                      NOP                                    
  1706   0D52    D273                      BRA 0x123a                             
  1707   0D54    CFDE                      MOVFF POSTINC2, FSR0L                  
  1708   0D56    FFE9                      NOP                                    
  1709   0D58    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1710   0D5A    FFEA                      NOP                                    
  1711   0D5C    0E03                      MOVLW 0x3                              
  1712   0D5E    26E9                      ADDWF FSR0L, F, ACCESS                 
  1713   0D60    0E00                      MOVLW 0                                
  1714   0D62    22EA                      ADDWFC FSR0H, F, ACCESS                
  1715   0D64    50EF                      MOVF INDF0, W, ACCESS                  
  1716   0D66    E12C                      BNZ 0xdc0                              
  1717   0D68    0E7F                      MOVLW 0x7f                             
  1718   0D6A    6E10                      MOVWF __tmp_0, ACCESS                  
  1719   0D6C    CFDE                      MOVFF POSTINC2, FSR0L                  
  1720   0D6E    FFE9                      NOP                                    
  1721   0D70    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1722   0D72    FFEA                      NOP                                    
  1723   0D74    0E02                      MOVLW 0x2                              
  1724   0D76    26E9                      ADDWF FSR0L, F, ACCESS                 
  1725   0D78    0E00                      MOVLW 0                                
  1726   0D7A    22EA                      ADDWFC FSR0H, F, ACCESS                
  1727   0D7C    50EF                      MOVF INDF0, W, ACCESS                  
  1728   0D7E    5C10                      SUBWF __tmp_0, W, ACCESS               
  1729   0D80    E31F                      BNC 0xdc0                              
  1730   0D82    CFDE                      MOVFF POSTINC2, FSR0L                  
  1731   0D84    FFE9                      NOP                                    
  1732   0D86    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1733   0D88    FFEA                      NOP                                    
  1734   0D8A    0E02                      MOVLW 0x2                              
  1735   0D8C    26E9                      ADDWF FSR0L, F, ACCESS                 
  1736   0D8E    0E00                      MOVLW 0                                
  1737   0D90    22EA                      ADDWFC FSR0H, F, ACCESS                
  1738   0D92    CFEF                      MOVFF INDF0, usb_addr_pending          
  1739   0D94    F096                      NOP                                    
  1740   0D96    0E18                      MOVLW 0x18                             
  1741   0D98    6EE6                      MOVWF POSTINC1, ACCESS                 
  1742   0D9A    0E18                      MOVLW 0x18                             
  1743   0D9C    6EE6                      MOVWF POSTINC1, ACCESS                 
  1744   0D9E    0E00                      MOVLW 0                                
  1745   0DA0    6EE6                      MOVWF POSTINC1, ACCESS                 
  1746   0DA2    6AE6                      CLRF POSTINC1, ACCESS                  
  1747   0DA4    ECA5                      CALL usb_set_in_handler, 0             
  1748   0DA6    F00B                      NOP                                    
  1749   0DA8    52E5                      MOVF POSTDEC1, F, ACCESS               
  1750   0DAA    52E5                      MOVF POSTDEC1, F, ACCESS               
  1751   0DAC    52E5                      MOVF POSTDEC1, F, ACCESS               
  1752   0DAE    52E5                      MOVF POSTDEC1, F, ACCESS               
  1753   0DB0    0E00                      MOVLW 0                                
  1754   0DB2    6EE6                      MOVWF POSTINC1, ACCESS                 
  1755   0DB4    6AE6                      CLRF POSTINC1, ACCESS                  
  1756   0DB6    ECE5                      CALL usb_ack_dat1, 0                   
  1757   0DB8    F00B                      NOP                                    
  1758   0DBA    52E5                      MOVF POSTDEC1, F, ACCESS               
  1759   0DBC    52E5                      MOVF POSTDEC1, F, ACCESS               
  1760   0DBE    D002                      BRA 0xdc4                              
  1761   0DC0    EC05                      CALL usb_RequestError, 0               
  1762   0DC2    F00C                      NOP                                    
  1763   0DC4    D23A                      BRA 0x123a                             
  1764   0DC6    CFDE                      MOVFF POSTINC2, FSR0L                  
  1765   0DC8    FFE9                      NOP                                    
  1766   0DCA    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1767   0DCC    FFEA                      NOP                                    
  1768   0DCE    0E03                      MOVLW 0x3                              
  1769   0DD0    26E9                      ADDWF FSR0L, F, ACCESS                 
  1770   0DD2    0E00                      MOVLW 0                                
  1771   0DD4    22EA                      ADDWFC FSR0H, F, ACCESS                
  1772   0DD6    50EF                      MOVF INDF0, W, ACCESS                  
  1773   0DD8    0A04                      XORLW 0x4                              
  1774   0DDA    E101                      BNZ 0xdde                              
  1775   0DDC    D1D6                      BRA 0x118a                             
  1776   0DDE    0A01                      XORLW 0x1                              
  1777   0DE0    E101                      BNZ 0xde4                              
  1778   0DE2    D1D3                      BRA 0x118a                             
  1779   0DE4    0A06                      XORLW 0x6                              
  1780   0DE6    E101                      BNZ 0xdea                              
  1781   0DE8    D143                      BRA 0x1070                             
  1782   0DEA    0A01                      XORLW 0x1                              
  1783   0DEC    E03E                      BZ 0xe6a                               
  1784   0DEE    0A03                      XORLW 0x3                              
  1785   0DF0    E001                      BZ 0xdf4                               
  1786   0DF2    D1CB                      BRA 0x118a                             
  1787   0DF4    C060                      MOVFF usb_device_descriptor, usb_rom_ptr
  1788   0DF6    F09C                      NOP                                    
  1789   0DF8    C061                      MOVFF 0x61, 0x9d                       
  1790   0DFA    F09D                      NOP                                    
  1791   0DFC    C062                      MOVFF 0x62, 0x9e                       
  1792   0DFE    F09E                      NOP                                    
  1793   0E00    C060                      MOVFF usb_device_descriptor, TBLPTRL   
  1794   0E02    FFF6                      NOP                                    
  1795   0E04    C061                      MOVFF 0x61, TBLPTRH                    
  1796   0E06    FFF7                      NOP                                    
  1797   0E08    C062                      MOVFF 0x62, TBLPTRU                    
  1798   0E0A    FFF8                      NOP                                    
  1799   0E0C    0008                      TBLRD*                                 
  1800   0E0E    50F5                      MOVF TABLAT, W, ACCESS                 
  1801   0E10    0100                      MOVLB 0                                
  1802   0E12    6F9F                      MOVWF usb_rom_len, BANKED              
  1803   0E14    6BA0                      CLRF 0xa0, BANKED                      
  1804   0E16    CFDE                      MOVFF POSTINC2, FSR0L                  
  1805   0E18    FFE9                      NOP                                    
  1806   0E1A    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1807   0E1C    FFEA                      NOP                                    
  1808   0E1E    0E07                      MOVLW 0x7                              
  1809   0E20    26E9                      ADDWF FSR0L, F, ACCESS                 
  1810   0E22    0E00                      MOVLW 0                                
  1811   0E24    22EA                      ADDWFC FSR0H, F, ACCESS                
  1812   0E26    50EF                      MOVF INDF0, W, ACCESS                  
  1813   0E28    E11F                      BNZ 0xe68                              
  1814   0E2A    CFDE                      MOVFF POSTINC2, FSR0L                  
  1815   0E2C    FFE9                      NOP                                    
  1816   0E2E    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1817   0E30    FFEA                      NOP                                    
  1818   0E32    0E06                      MOVLW 0x6                              
  1819   0E34    26E9                      ADDWF FSR0L, F, ACCESS                 
  1820   0E36    0E00                      MOVLW 0                                
  1821   0E38    22EA                      ADDWFC FSR0H, F, ACCESS                
  1822   0E3A    CFEF                      MOVFF INDF0, __tmp_0                   
  1823   0E3C    F010                      NOP                                    
  1824   0E3E    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  1825   0E40    FFF6                      NOP                                    
  1826   0E42    C09D                      MOVFF 0x9d, TBLPTRH                    
  1827   0E44    FFF7                      NOP                                    
  1828   0E46    C09E                      MOVFF 0x9e, TBLPTRU                    
  1829   0E48    FFF8                      NOP                                    
  1830   0E4A    0008                      TBLRD*                                 
  1831   0E4C    50F5                      MOVF TABLAT, W, ACCESS                 
  1832   0E4E    5C10                      SUBWF __tmp_0, W, ACCESS               
  1833   0E50    E20B                      BC 0xe68                               
  1834   0E52    CFDE                      MOVFF POSTINC2, FSR0L                  
  1835   0E54    FFE9                      NOP                                    
  1836   0E56    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1837   0E58    FFEA                      NOP                                    
  1838   0E5A    0E06                      MOVLW 0x6                              
  1839   0E5C    26E9                      ADDWF FSR0L, F, ACCESS                 
  1840   0E5E    0E00                      MOVLW 0                                
  1841   0E60    22EA                      ADDWFC FSR0H, F, ACCESS                
  1842   0E62    50EF                      MOVF INDF0, W, ACCESS                  
  1843   0E64    6F9F                      MOVWF usb_rom_len, BANKED              
  1844   0E66    6BA0                      CLRF 0xa0, BANKED                      
  1845   0E68    D193                      BRA 0x1190                             
  1846   0E6A    CFDE                      MOVFF POSTINC2, FSR0L                  
  1847   0E6C    FFE9                      NOP                                    
  1848   0E6E    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1849   0E70    FFEA                      NOP                                    
  1850   0E72    0E02                      MOVLW 0x2                              
  1851   0E74    26E9                      ADDWF FSR0L, F, ACCESS                 
  1852   0E76    0E00                      MOVLW 0                                
  1853   0E78    22EA                      ADDWFC FSR0H, F, ACCESS                
  1854   0E7A    CFEF                      MOVFF INDF0, __tmp_0                   
  1855   0E7C    F010                      NOP                                    
  1856   0E7E    C060                      MOVFF usb_device_descriptor, TBLPTRL   
  1857   0E80    FFF6                      NOP                                    
  1858   0E82    C061                      MOVFF 0x61, TBLPTRH                    
  1859   0E84    FFF7                      NOP                                    
  1860   0E86    C062                      MOVFF 0x62, TBLPTRU                    
  1861   0E88    FFF8                      NOP                                    
  1862   0E8A    0E11                      MOVLW 0x11                             
  1863   0E8C    26F6                      ADDWF TBLPTRL, F, ACCESS               
  1864   0E8E    0E00                      MOVLW 0                                
  1865   0E90    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  1866   0E92    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  1867   0E94    0008                      TBLRD*                                 
  1868   0E96    50F5                      MOVF TABLAT, W, ACCESS                 
  1869   0E98    5C10                      SUBWF __tmp_0, W, ACCESS               
  1870   0E9A    E304                      BNC 0xea4                              
  1871   0E9C    0100                      MOVLB 0                                
  1872   0E9E    0E01                      MOVLW 0x1                              
  1873   0EA0    6FA1                      MOVWF usbrequesterrorflag, BANKED      
  1874   0EA2    D176                      BRA 0x1190                             
  1875   0EA4    C063                      MOVFF usb_config_descriptor, usb_rom_ptr
  1876   0EA6    F09C                      NOP                                    
  1877   0EA8    C064                      MOVFF 0x64, 0x9d                       
  1878   0EAA    F09D                      NOP                                    
  1879   0EAC    C065                      MOVFF 0x65, 0x9e                       
  1880   0EAE    F09E                      NOP                                    
  1881   0EB0    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  1882   0EB2    FFF6                      NOP                                    
  1883   0EB4    C09D                      MOVFF 0x9d, TBLPTRH                    
  1884   0EB6    FFF7                      NOP                                    
  1885   0EB8    C09E                      MOVFF 0x9e, TBLPTRU                    
  1886   0EBA    FFF8                      NOP                                    
  1887   0EBC    0E03                      MOVLW 0x3                              
  1888   0EBE    26F6                      ADDWF TBLPTRL, F, ACCESS               
  1889   0EC0    0E00                      MOVLW 0                                
  1890   0EC2    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  1891   0EC4    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  1892   0EC6    0008                      TBLRD*                                 
  1893   0EC8    50F5                      MOVF TABLAT, W, ACCESS                 
  1894   0ECA    6E10                      MOVWF __tmp_0, ACCESS                  
  1895   0ECC    6A11                      CLRF 0x11, ACCESS                      
  1896   0ECE    C010                      MOVFF __tmp_0, 0x11                    
  1897   0ED0    F011                      NOP                                    
  1898   0ED2    6A10                      CLRF __tmp_0, ACCESS                   
  1899   0ED4    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  1900   0ED6    FFF6                      NOP                                    
  1901   0ED8    C09D                      MOVFF 0x9d, TBLPTRH                    
  1902   0EDA    FFF7                      NOP                                    
  1903   0EDC    C09E                      MOVFF 0x9e, TBLPTRU                    
  1904   0EDE    FFF8                      NOP                                    
  1905   0EE0    0E02                      MOVLW 0x2                              
  1906   0EE2    26F6                      ADDWF TBLPTRL, F, ACCESS               
  1907   0EE4    0E00                      MOVLW 0                                
  1908   0EE6    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  1909   0EE8    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  1910   0EEA    0008                      TBLRD*                                 
  1911   0EEC    50F5                      MOVF TABLAT, W, ACCESS                 
  1912   0EEE    0100                      MOVLB 0                                
  1913   0EF0    2410                      ADDWF __tmp_0, W, ACCESS               
  1914   0EF2    6F9F                      MOVWF usb_rom_len, BANKED              
  1915   0EF4    0E00                      MOVLW 0                                
  1916   0EF6    2011                      ADDWFC 0x11, W, ACCESS                 
  1917   0EF8    6FA0                      MOVWF 0xa0, BANKED                     
  1918   0EFA    0E02                      MOVLW 0x2                              
  1919   0EFC    6ADB                      CLRF PLUSW2, ACCESS                    
  1920   0EFE    0E03                      MOVLW 0x3                              
  1921   0F00    6ADB                      CLRF PLUSW2, ACCESS                    
  1922   0F02    0E02                      MOVLW 0x2                              
  1923   0F04    CFDB                      MOVFF PLUSW2, __tmp_0                  
  1924   0F06    F010                      NOP                                    
  1925   0F08    0E03                      MOVLW 0x3                              
  1926   0F0A    CFDB                      MOVFF PLUSW2, 0x11                     
  1927   0F0C    F011                      NOP                                    
  1928   0F0E    CFDE                      MOVFF POSTINC2, FSR0L                  
  1929   0F10    FFE9                      NOP                                    
  1930   0F12    CFDD                      MOVFF POSTDEC2, FSR0H                  
  1931   0F14    FFEA                      NOP                                    
  1932   0F16    0E02                      MOVLW 0x2                              
  1933   0F18    26E9                      ADDWF FSR0L, F, ACCESS                 
  1934   0F1A    0E00                      MOVLW 0                                
  1935   0F1C    22EA                      ADDWFC FSR0H, F, ACCESS                
  1936   0F1E    50EF                      MOVF INDF0, W, ACCESS                  
  1937   0F20    0100                      MOVLB 0                                
  1938   0F22    AE11                      BTFSS 0x11, 0x7, ACCESS                
  1939   0F24    D002                      BRA 0xf2a                              
  1940   0F26    90D8                      BCF STATUS, 0, ACCESS                  
  1941   0F28    D003                      BRA 0xf30                              
  1942   0F2A    5C10                      SUBWF __tmp_0, W, ACCESS               
  1943   0F2C    0E00                      MOVLW 0                                
  1944   0F2E    5811                      SUBWFB 0x11, W, ACCESS                 
  1945   0F30    E236                      BC 0xf9e                               
  1946   0F32    C09F                      MOVFF usb_rom_len, __tmp_0             
  1947   0F34    F010                      NOP                                    
  1948   0F36    C0A0                      MOVFF 0xa0, 0x11                       
  1949   0F38    F011                      NOP                                    
  1950   0F3A    6A12                      CLRF 0x12, ACCESS                      
  1951   0F3C    5010                      MOVF __tmp_0, W, ACCESS                
  1952   0F3E    0100                      MOVLB 0                                
  1953   0F40    279C                      ADDWF usb_rom_ptr, F, BANKED           
  1954   0F42    5011                      MOVF 0x11, W, ACCESS                   
  1955   0F44    239D                      ADDWFC 0x9d, F, BANKED                 
  1956   0F46    5012                      MOVF 0x12, W, ACCESS                   
  1957   0F48    239E                      ADDWFC 0x9e, F, BANKED                 
  1958   0F4A    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  1959   0F4C    FFF6                      NOP                                    
  1960   0F4E    C09D                      MOVFF 0x9d, TBLPTRH                    
  1961   0F50    FFF7                      NOP                                    
  1962   0F52    C09E                      MOVFF 0x9e, TBLPTRU                    
  1963   0F54    FFF8                      NOP                                    
  1964   0F56    0E03                      MOVLW 0x3                              
  1965   0F58    26F6                      ADDWF TBLPTRL, F, ACCESS               
  1966   0F5A    0E00                      MOVLW 0                                
  1967   0F5C    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  1968   0F5E    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  1969   0F60    0008                      TBLRD*                                 
  1970   0F62    50F5                      MOVF TABLAT, W, ACCESS                 
  1971   0F64    6E10                      MOVWF __tmp_0, ACCESS                  
  1972   0F66    6A11                      CLRF 0x11, ACCESS                      
  1973   0F68    C010                      MOVFF __tmp_0, 0x11                    
  1974   0F6A    F011                      NOP                                    
  1975   0F6C    6A10                      CLRF __tmp_0, ACCESS                   
  1976   0F6E    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  1977   0F70    FFF6                      NOP                                    
  1978   0F72    C09D                      MOVFF 0x9d, TBLPTRH                    
  1979   0F74    FFF7                      NOP                                    
  1980   0F76    C09E                      MOVFF 0x9e, TBLPTRU                    
  1981   0F78    FFF8                      NOP                                    
  1982   0F7A    0E02                      MOVLW 0x2                              
  1983   0F7C    26F6                      ADDWF TBLPTRL, F, ACCESS               
  1984   0F7E    0E00                      MOVLW 0                                
  1985   0F80    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  1986   0F82    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  1987   0F84    0008                      TBLRD*                                 
  1988   0F86    50F5                      MOVF TABLAT, W, ACCESS                 
  1989   0F88    2410                      ADDWF __tmp_0, W, ACCESS               
  1990   0F8A    6F9F                      MOVWF usb_rom_len, BANKED              
  1991   0F8C    0E00                      MOVLW 0                                
  1992   0F8E    2011                      ADDWFC 0x11, W, ACCESS                 
  1993   0F90    6FA0                      MOVWF 0xa0, BANKED                     
  1994   0F92    0E02                      MOVLW 0x2                              
  1995   0F94    2ADB                      INCF PLUSW2, F, ACCESS                 
  1996   0F96    0E03                      MOVLW 0x3                              
  1997   0F98    E301                      BNC 0xf9c                              
  1998   0F9A    2ADB                      INCF PLUSW2, F, ACCESS                 
  1999   0F9C    D7B2                      BRA 0xf02                              
  2000   0F9E    CFDE                      MOVFF POSTINC2, FSR0L                  
  2001   0FA0    FFE9                      NOP                                    
  2002   0FA2    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2003   0FA4    FFEA                      NOP                                    
  2004   0FA6    0E07                      MOVLW 0x7                              
  2005   0FA8    26E9                      ADDWF FSR0L, F, ACCESS                 
  2006   0FAA    0E00                      MOVLW 0                                
  2007   0FAC    22EA                      ADDWFC FSR0H, F, ACCESS                
  2008   0FAE    CFEF                      MOVFF INDF0, __tmp_0                   
  2009   0FB0    F010                      NOP                                    
  2010   0FB2    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2011   0FB4    FFF6                      NOP                                    
  2012   0FB6    C09D                      MOVFF 0x9d, TBLPTRH                    
  2013   0FB8    FFF7                      NOP                                    
  2014   0FBA    C09E                      MOVFF 0x9e, TBLPTRU                    
  2015   0FBC    FFF8                      NOP                                    
  2016   0FBE    0E03                      MOVLW 0x3                              
  2017   0FC0    26F6                      ADDWF TBLPTRL, F, ACCESS               
  2018   0FC2    0E00                      MOVLW 0                                
  2019   0FC4    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  2020   0FC6    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  2021   0FC8    0008                      TBLRD*                                 
  2022   0FCA    50F5                      MOVF TABLAT, W, ACCESS                 
  2023   0FCC    5C10                      SUBWF __tmp_0, W, ACCESS               
  2024   0FCE    E332                      BNC 0x1034                             
  2025   0FD0    CFDE                      MOVFF POSTINC2, FSR0L                  
  2026   0FD2    FFE9                      NOP                                    
  2027   0FD4    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2028   0FD6    FFEA                      NOP                                    
  2029   0FD8    0E07                      MOVLW 0x7                              
  2030   0FDA    26E9                      ADDWF FSR0L, F, ACCESS                 
  2031   0FDC    0E00                      MOVLW 0                                
  2032   0FDE    22EA                      ADDWFC FSR0H, F, ACCESS                
  2033   0FE0    CFEF                      MOVFF INDF0, 0x11                      
  2034   0FE2    F011                      NOP                                    
  2035   0FE4    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2036   0FE6    FFF6                      NOP                                    
  2037   0FE8    C09D                      MOVFF 0x9d, TBLPTRH                    
  2038   0FEA    FFF7                      NOP                                    
  2039   0FEC    C09E                      MOVFF 0x9e, TBLPTRU                    
  2040   0FEE    FFF8                      NOP                                    
  2041   0FF0    0E03                      MOVLW 0x3                              
  2042   0FF2    26F6                      ADDWF TBLPTRL, F, ACCESS               
  2043   0FF4    0E00                      MOVLW 0                                
  2044   0FF6    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  2045   0FF8    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  2046   0FFA    0008                      TBLRD*                                 
  2047   0FFC    50F5                      MOVF TABLAT, W, ACCESS                 
  2048   0FFE    5C11                      SUBWF 0x11, W, ACCESS                  
  2049   1000    E136                      BNZ 0x106e                             
  2050   1002    CFDE                      MOVFF POSTINC2, FSR0L                  
  2051   1004    FFE9                      NOP                                    
  2052   1006    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2053   1008    FFEA                      NOP                                    
  2054   100A    0E06                      MOVLW 0x6                              
  2055   100C    26E9                      ADDWF FSR0L, F, ACCESS                 
  2056   100E    0E00                      MOVLW 0                                
  2057   1010    22EA                      ADDWFC FSR0H, F, ACCESS                
  2058   1012    CFEF                      MOVFF INDF0, 0x12                      
  2059   1014    F012                      NOP                                    
  2060   1016    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2061   1018    FFF6                      NOP                                    
  2062   101A    C09D                      MOVFF 0x9d, TBLPTRH                    
  2063   101C    FFF7                      NOP                                    
  2064   101E    C09E                      MOVFF 0x9e, TBLPTRU                    
  2065   1020    FFF8                      NOP                                    
  2066   1022    0E02                      MOVLW 0x2                              
  2067   1024    26F6                      ADDWF TBLPTRL, F, ACCESS               
  2068   1026    0E00                      MOVLW 0                                
  2069   1028    22F7                      ADDWFC TBLPTRH, F, ACCESS              
  2070   102A    22F8                      ADDWFC TBLPTRU, F, ACCESS              
  2071   102C    0008                      TBLRD*                                 
  2072   102E    50F5                      MOVF TABLAT, W, ACCESS                 
  2073   1030    5C12                      SUBWF 0x12, W, ACCESS                  
  2074   1032    E21D                      BC 0x106e                              
  2075   1034    CFDE                      MOVFF POSTINC2, FSR0L                  
  2076   1036    FFE9                      NOP                                    
  2077   1038    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2078   103A    FFEA                      NOP                                    
  2079   103C    0E07                      MOVLW 0x7                              
  2080   103E    26E9                      ADDWF FSR0L, F, ACCESS                 
  2081   1040    0E00                      MOVLW 0                                
  2082   1042    22EA                      ADDWFC FSR0H, F, ACCESS                
  2083   1044    50EF                      MOVF INDF0, W, ACCESS                  
  2084   1046    6E10                      MOVWF __tmp_0, ACCESS                  
  2085   1048    6A11                      CLRF 0x11, ACCESS                      
  2086   104A    C010                      MOVFF __tmp_0, 0x11                    
  2087   104C    F011                      NOP                                    
  2088   104E    6A10                      CLRF __tmp_0, ACCESS                   
  2089   1050    CFDE                      MOVFF POSTINC2, FSR0L                  
  2090   1052    FFE9                      NOP                                    
  2091   1054    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2092   1056    FFEA                      NOP                                    
  2093   1058    0E06                      MOVLW 0x6                              
  2094   105A    26E9                      ADDWF FSR0L, F, ACCESS                 
  2095   105C    0E00                      MOVLW 0                                
  2096   105E    22EA                      ADDWFC FSR0H, F, ACCESS                
  2097   1060    50EF                      MOVF INDF0, W, ACCESS                  
  2098   1062    0100                      MOVLB 0                                
  2099   1064    2410                      ADDWF __tmp_0, W, ACCESS               
  2100   1066    6F9F                      MOVWF usb_rom_len, BANKED              
  2101   1068    0E00                      MOVLW 0                                
  2102   106A    2011                      ADDWFC 0x11, W, ACCESS                 
  2103   106C    6FA0                      MOVWF 0xa0, BANKED                     
  2104   106E    D090                      BRA 0x1190                             
  2105   1070    CFDE                      MOVFF POSTINC2, FSR0L                  
  2106   1072    FFE9                      NOP                                    
  2107   1074    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2108   1076    FFEA                      NOP                                    
  2109   1078    0E02                      MOVLW 0x2                              
  2110   107A    26E9                      ADDWF FSR0L, F, ACCESS                 
  2111   107C    0E00                      MOVLW 0                                
  2112   107E    22EA                      ADDWFC FSR0H, F, ACCESS                
  2113   1080    50EF                      MOVF INDF0, W, ACCESS                  
  2114   1082    6E10                      MOVWF __tmp_0, ACCESS                  
  2115   1084    6A11                      CLRF 0x11, ACCESS                      
  2116   1086    0100                      MOVLB 0                                
  2117   1088    5011                      MOVF 0x11, W, ACCESS                   
  2118   108A    196A                      XORWF 0x6a, W, BANKED                  
  2119   108C    AEE8                      BTFSS WREG, 0x7, ACCESS                
  2120   108E    D002                      BRA 0x1094                             
  2121   1090    356A                      RLCF 0x6a, W, BANKED                   
  2122   1092    D004                      BRA 0x109c                             
  2123   1094    5169                      MOVF usb_num_string_descriptors, W, BANKED
  2124   1096    5C10                      SUBWF __tmp_0, W, ACCESS               
  2125   1098    516A                      MOVF 0x6a, W, BANKED                   
  2126   109A    5811                      SUBWFB 0x11, W, ACCESS                 
  2127   109C    E303                      BNC 0x10a4                             
  2128   109E    0E01                      MOVLW 0x1                              
  2129   10A0    6FA1                      MOVWF usbrequesterrorflag, BANKED      
  2130   10A2    D076                      BRA 0x1190                             
  2131   10A4    C066                      MOVFF usb_string_descriptor, usb_rom_ptr
  2132   10A6    F09C                      NOP                                    
  2133   10A8    C067                      MOVFF 0x67, 0x9d                       
  2134   10AA    F09D                      NOP                                    
  2135   10AC    C068                      MOVFF 0x68, 0x9e                       
  2136   10AE    F09E                      NOP                                    
  2137   10B0    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2138   10B2    FFF6                      NOP                                    
  2139   10B4    C09D                      MOVFF 0x9d, TBLPTRH                    
  2140   10B6    FFF7                      NOP                                    
  2141   10B8    C09E                      MOVFF 0x9e, TBLPTRU                    
  2142   10BA    FFF8                      NOP                                    
  2143   10BC    0008                      TBLRD*                                 
  2144   10BE    50F5                      MOVF TABLAT, W, ACCESS                 
  2145   10C0    6F9F                      MOVWF usb_rom_len, BANKED              
  2146   10C2    6BA0                      CLRF 0xa0, BANKED                      
  2147   10C4    0E02                      MOVLW 0x2                              
  2148   10C6    6ADB                      CLRF PLUSW2, ACCESS                    
  2149   10C8    0E03                      MOVLW 0x3                              
  2150   10CA    6ADB                      CLRF PLUSW2, ACCESS                    
  2151   10CC    0E02                      MOVLW 0x2                              
  2152   10CE    CFDB                      MOVFF PLUSW2, __tmp_0                  
  2153   10D0    F010                      NOP                                    
  2154   10D2    0E03                      MOVLW 0x3                              
  2155   10D4    CFDB                      MOVFF PLUSW2, 0x11                     
  2156   10D6    F011                      NOP                                    
  2157   10D8    CFDE                      MOVFF POSTINC2, FSR0L                  
  2158   10DA    FFE9                      NOP                                    
  2159   10DC    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2160   10DE    FFEA                      NOP                                    
  2161   10E0    0E02                      MOVLW 0x2                              
  2162   10E2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2163   10E4    0E00                      MOVLW 0                                
  2164   10E6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2165   10E8    50EF                      MOVF INDF0, W, ACCESS                  
  2166   10EA    0100                      MOVLB 0                                
  2167   10EC    AE11                      BTFSS 0x11, 0x7, ACCESS                
  2168   10EE    D002                      BRA 0x10f4                             
  2169   10F0    90D8                      BCF STATUS, 0, ACCESS                  
  2170   10F2    D003                      BRA 0x10fa                             
  2171   10F4    5C10                      SUBWF __tmp_0, W, ACCESS               
  2172   10F6    0E00                      MOVLW 0                                
  2173   10F8    5811                      SUBWFB 0x11, W, ACCESS                 
  2174   10FA    E21C                      BC 0x1134                              
  2175   10FC    C09F                      MOVFF usb_rom_len, __tmp_0             
  2176   10FE    F010                      NOP                                    
  2177   1100    C0A0                      MOVFF 0xa0, 0x11                       
  2178   1102    F011                      NOP                                    
  2179   1104    6A12                      CLRF 0x12, ACCESS                      
  2180   1106    5010                      MOVF __tmp_0, W, ACCESS                
  2181   1108    0100                      MOVLB 0                                
  2182   110A    279C                      ADDWF usb_rom_ptr, F, BANKED           
  2183   110C    5011                      MOVF 0x11, W, ACCESS                   
  2184   110E    239D                      ADDWFC 0x9d, F, BANKED                 
  2185   1110    5012                      MOVF 0x12, W, ACCESS                   
  2186   1112    239E                      ADDWFC 0x9e, F, BANKED                 
  2187   1114    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2188   1116    FFF6                      NOP                                    
  2189   1118    C09D                      MOVFF 0x9d, TBLPTRH                    
  2190   111A    FFF7                      NOP                                    
  2191   111C    C09E                      MOVFF 0x9e, TBLPTRU                    
  2192   111E    FFF8                      NOP                                    
  2193   1120    0008                      TBLRD*                                 
  2194   1122    50F5                      MOVF TABLAT, W, ACCESS                 
  2195   1124    6F9F                      MOVWF usb_rom_len, BANKED              
  2196   1126    6BA0                      CLRF 0xa0, BANKED                      
  2197   1128    0E02                      MOVLW 0x2                              
  2198   112A    2ADB                      INCF PLUSW2, F, ACCESS                 
  2199   112C    0E03                      MOVLW 0x3                              
  2200   112E    E301                      BNC 0x1132                             
  2201   1130    2ADB                      INCF PLUSW2, F, ACCESS                 
  2202   1132    D7CC                      BRA 0x10cc                             
  2203   1134    CFDE                      MOVFF POSTINC2, FSR0L                  
  2204   1136    FFE9                      NOP                                    
  2205   1138    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2206   113A    FFEA                      NOP                                    
  2207   113C    0E07                      MOVLW 0x7                              
  2208   113E    26E9                      ADDWF FSR0L, F, ACCESS                 
  2209   1140    0E00                      MOVLW 0                                
  2210   1142    22EA                      ADDWFC FSR0H, F, ACCESS                
  2211   1144    50EF                      MOVF INDF0, W, ACCESS                  
  2212   1146    E120                      BNZ 0x1188                             
  2213   1148    CFDE                      MOVFF POSTINC2, FSR0L                  
  2214   114A    FFE9                      NOP                                    
  2215   114C    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2216   114E    FFEA                      NOP                                    
  2217   1150    0E06                      MOVLW 0x6                              
  2218   1152    26E9                      ADDWF FSR0L, F, ACCESS                 
  2219   1154    0E00                      MOVLW 0                                
  2220   1156    22EA                      ADDWFC FSR0H, F, ACCESS                
  2221   1158    CFEF                      MOVFF INDF0, __tmp_0                   
  2222   115A    F010                      NOP                                    
  2223   115C    C09C                      MOVFF usb_rom_ptr, TBLPTRL             
  2224   115E    FFF6                      NOP                                    
  2225   1160    C09D                      MOVFF 0x9d, TBLPTRH                    
  2226   1162    FFF7                      NOP                                    
  2227   1164    C09E                      MOVFF 0x9e, TBLPTRU                    
  2228   1166    FFF8                      NOP                                    
  2229   1168    0008                      TBLRD*                                 
  2230   116A    50F5                      MOVF TABLAT, W, ACCESS                 
  2231   116C    5C10                      SUBWF __tmp_0, W, ACCESS               
  2232   116E    E20C                      BC 0x1188                              
  2233   1170    CFDE                      MOVFF POSTINC2, FSR0L                  
  2234   1172    FFE9                      NOP                                    
  2235   1174    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2236   1176    FFEA                      NOP                                    
  2237   1178    0E06                      MOVLW 0x6                              
  2238   117A    26E9                      ADDWF FSR0L, F, ACCESS                 
  2239   117C    0E00                      MOVLW 0                                
  2240   117E    22EA                      ADDWFC FSR0H, F, ACCESS                
  2241   1180    50EF                      MOVF INDF0, W, ACCESS                  
  2242   1182    0100                      MOVLB 0                                
  2243   1184    6F9F                      MOVWF usb_rom_len, BANKED              
  2244   1186    6BA0                      CLRF 0xa0, BANKED                      
  2245   1188    D003                      BRA 0x1190                             
  2246   118A    0100                      MOVLB 0                                
  2247   118C    0E01                      MOVLW 0x1                              
  2248   118E    6FA1                      MOVWF usbrequesterrorflag, BANKED      
  2249   1190    0100                      MOVLB 0                                
  2250   1192    51A1                      MOVF usbrequesterrorflag, W, BANKED    
  2251   1194    E10E                      BNZ 0x11b2                             
  2252   1196    DB56                      RCALL usb_send_rom                     
  2253   1198    0E44                      MOVLW 0x44                             
  2254   119A    6EE6                      MOVWF POSTINC1, ACCESS                 
  2255   119C    0E18                      MOVLW 0x18                             
  2256   119E    6EE6                      MOVWF POSTINC1, ACCESS                 
  2257   11A0    0E00                      MOVLW 0                                
  2258   11A2    6EE6                      MOVWF POSTINC1, ACCESS                 
  2259   11A4    6AE6                      CLRF POSTINC1, ACCESS                  
  2260   11A6    DAD1                      RCALL usb_set_in_handler               
  2261   11A8    52E5                      MOVF POSTDEC1, F, ACCESS               
  2262   11AA    52E5                      MOVF POSTDEC1, F, ACCESS               
  2263   11AC    52E5                      MOVF POSTDEC1, F, ACCESS               
  2264   11AE    52E5                      MOVF POSTDEC1, F, ACCESS               
  2265   11B0    D001                      BRA 0x11b4                             
  2266   11B2    DB2B                      RCALL usb_RequestError                 
  2267   11B4    D042                      BRA 0x123a                             
  2268   11B6    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2269   11B8    FFE9                      NOP                                    
  2270   11BA    C09B                      MOVFF 0x9b, FSR0H                      
  2271   11BC    FFEA                      NOP                                    
  2272   11BE    0E02                      MOVLW 0x2                              
  2273   11C0    26E9                      ADDWF FSR0L, F, ACCESS                 
  2274   11C2    0E00                      MOVLW 0                                
  2275   11C4    22EA                      ADDWFC FSR0H, F, ACCESS                
  2276   11C6    50EE                      MOVF POSTINC0, W, ACCESS               
  2277   11C8    CFEF                      MOVFF INDF0, FSR0H                     
  2278   11CA    FFEA                      NOP                                    
  2279   11CC    6EE9                      MOVWF FSR0L, ACCESS                    
  2280   11CE    C093                      MOVFF usb_current_cfg, INDF0           
  2281   11D0    FFEF                      NOP                                    
  2282   11D2    0E01                      MOVLW 0x1                              
  2283   11D4    6EE6                      MOVWF POSTINC1, ACCESS                 
  2284   11D6    6AE6                      CLRF POSTINC1, ACCESS                  
  2285   11D8    DAF8                      RCALL usb_ack_dat1                     
  2286   11DA    52E5                      MOVF POSTDEC1, F, ACCESS               
  2287   11DC    52E5                      MOVF POSTDEC1, F, ACCESS               
  2288   11DE    D02D                      BRA 0x123a                             
  2289   11E0    0E01                      MOVLW 0x1                              
  2290   11E2    6E10                      MOVWF __tmp_0, ACCESS                  
  2291   11E4    CFDE                      MOVFF POSTINC2, FSR0L                  
  2292   11E6    FFE9                      NOP                                    
  2293   11E8    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2294   11EA    FFEA                      NOP                                    
  2295   11EC    0E02                      MOVLW 0x2                              
  2296   11EE    26E9                      ADDWF FSR0L, F, ACCESS                 
  2297   11F0    0E00                      MOVLW 0                                
  2298   11F2    22EA                      ADDWFC FSR0H, F, ACCESS                
  2299   11F4    50EF                      MOVF INDF0, W, ACCESS                  
  2300   11F6    5C10                      SUBWF __tmp_0, W, ACCESS               
  2301   11F8    E31D                      BNC 0x1234                             
  2302   11FA    CFDE                      MOVFF POSTINC2, FSR0L                  
  2303   11FC    FFE9                      NOP                                    
  2304   11FE    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2305   1200    FFEA                      NOP                                    
  2306   1202    0E02                      MOVLW 0x2                              
  2307   1204    26E9                      ADDWF FSR0L, F, ACCESS                 
  2308   1206    0E00                      MOVLW 0                                
  2309   1208    22EA                      ADDWFC FSR0H, F, ACCESS                
  2310   120A    50EF                      MOVF INDF0, W, ACCESS                  
  2311   120C    0100                      MOVLB 0                                
  2312   120E    6F93                      MOVWF usb_current_cfg, BANKED          
  2313   1210    6B94                      CLRF 0x94, BANKED                      
  2314   1212    5193                      MOVF usb_current_cfg, W, BANKED        
  2315   1214    1194                      IORWF 0x94, W, BANKED                  
  2316   1216    E005                      BZ 0x1222                              
  2317   1218    0E20                      MOVLW 0x20                             
  2318   121A    6F95                      MOVWF usb_device_state, BANKED         
  2319   121C    ECE1                      CALL user_configured_init, 0           
  2320   121E    F00C                      NOP                                    
  2321   1220    D002                      BRA 0x1226                             
  2322   1222    0E10                      MOVLW 0x10                             
  2323   1224    6F95                      MOVWF usb_device_state, BANKED         
  2324   1226    0E00                      MOVLW 0                                
  2325   1228    6EE6                      MOVWF POSTINC1, ACCESS                 
  2326   122A    6AE6                      CLRF POSTINC1, ACCESS                  
  2327   122C    DACE                      RCALL usb_ack_dat1                     
  2328   122E    52E5                      MOVF POSTDEC1, F, ACCESS               
  2329   1230    52E5                      MOVF POSTDEC1, F, ACCESS               
  2330   1232    D001                      BRA 0x1236                             
  2331   1234    DAEA                      RCALL usb_RequestError                 
  2332   1236    D001                      BRA 0x123a                             
  2333   1238    DAE8                      RCALL usb_RequestError                 
  2334   123A    0E04                      MOVLW 0x4                              
  2335   123C    5CE1                      SUBWF FSR1L, W, ACCESS                 
  2336   123E    E202                      BC 0x1244                              
  2337   1240    6AE1                      CLRF FSR1L, ACCESS                     
  2338   1242    52E5                      MOVF POSTDEC1, F, ACCESS               
  2339   1244    6EE1                      MOVWF FSR1L, ACCESS                    
  2340   1246    52E5                      MOVF POSTDEC1, F, ACCESS               
  2341   1248    CFE7                      MOVFF INDF1, FSR2                      
  2342   124A    FFD9                      NOP                                    
  2343   124C    0012                      RETURN 0                               
  2344   124E    CFD9 usb_handle_StandardInterfaceRequest MOVFF FSR2, POSTINC1                   
  2345   1250    FFE6                      NOP                                    
  2346   1252    CFE1                      MOVFF FSR1L, FSR2                      
  2347   1254    FFD9                      NOP                                    
  2348   1256    0E02                      MOVLW 0x2                              
  2349   1258    26E1                      ADDWF FSR1L, F, ACCESS                 
  2350   125A    0EFD                      MOVLW 0xfd                             
  2351   125C    CFDB                      MOVFF PLUSW2, FSR0L                    
  2352   125E    FFE9                      NOP                                    
  2353   1260    0EFE                      MOVLW 0xfe                             
  2354   1262    CFDB                      MOVFF PLUSW2, FSR0H                    
  2355   1264    FFEA                      NOP                                    
  2356   1266    0E02                      MOVLW 0x2                              
  2357   1268    26E9                      ADDWF FSR0L, F, ACCESS                 
  2358   126A    0E00                      MOVLW 0                                
  2359   126C    22EA                      ADDWFC FSR0H, F, ACCESS                
  2360   126E    CFEE                      MOVFF POSTINC0, POSTINC2               
  2361   1270    FFDE                      NOP                                    
  2362   1272    CFED                      MOVFF POSTDEC0, POSTDEC2               
  2363   1274    FFDD                      NOP                                    
  2364   1276    CFDE                      MOVFF POSTINC2, FSR0L                  
  2365   1278    FFE9                      NOP                                    
  2366   127A    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2367   127C    FFEA                      NOP                                    
  2368   127E    0E01                      MOVLW 0x1                              
  2369   1280    26E9                      ADDWF FSR0L, F, ACCESS                 
  2370   1282    0E00                      MOVLW 0                                
  2371   1284    22EA                      ADDWFC FSR0H, F, ACCESS                
  2372   1286    50EF                      MOVF INDF0, W, ACCESS                  
  2373   1288    0A01                      XORLW 0x1                              
  2374   128A    E073                      BZ 0x1372                              
  2375   128C    0A02                      XORLW 0x2                              
  2376   128E    E071                      BZ 0x1372                              
  2377   1290    0A08                      XORLW 0x8                              
  2378   1292    E04E                      BZ 0x1330                              
  2379   1294    0A01                      XORLW 0x1                              
  2380   1296    E028                      BZ 0x12e8                              
  2381   1298    0A0A                      XORLW 0xa                              
  2382   129A    E001                      BZ 0x129e                              
  2383   129C    D06A                      BRA 0x1372                             
  2384   129E    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2385   12A0    FFE9                      NOP                                    
  2386   12A2    C09B                      MOVFF 0x9b, FSR0H                      
  2387   12A4    FFEA                      NOP                                    
  2388   12A6    0E02                      MOVLW 0x2                              
  2389   12A8    26E9                      ADDWF FSR0L, F, ACCESS                 
  2390   12AA    0E00                      MOVLW 0                                
  2391   12AC    22EA                      ADDWFC FSR0H, F, ACCESS                
  2392   12AE    50EE                      MOVF POSTINC0, W, ACCESS               
  2393   12B0    CFEF                      MOVFF INDF0, FSR0H                     
  2394   12B2    FFEA                      NOP                                    
  2395   12B4    6EE9                      MOVWF FSR0L, ACCESS                    
  2396   12B6    6AEF                      CLRF INDF0, ACCESS                     
  2397   12B8    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2398   12BA    FFE9                      NOP                                    
  2399   12BC    C09B                      MOVFF 0x9b, FSR0H                      
  2400   12BE    FFEA                      NOP                                    
  2401   12C0    0E02                      MOVLW 0x2                              
  2402   12C2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2403   12C4    0E00                      MOVLW 0                                
  2404   12C6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2405   12C8    50EE                      MOVF POSTINC0, W, ACCESS               
  2406   12CA    CFEF                      MOVFF INDF0, FSR0H                     
  2407   12CC    FFEA                      NOP                                    
  2408   12CE    6EE9                      MOVWF FSR0L, ACCESS                    
  2409   12D0    0E01                      MOVLW 0x1                              
  2410   12D2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2411   12D4    0E00                      MOVLW 0                                
  2412   12D6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2413   12D8    6AEF                      CLRF INDF0, ACCESS                     
  2414   12DA    0E02                      MOVLW 0x2                              
  2415   12DC    6EE6                      MOVWF POSTINC1, ACCESS                 
  2416   12DE    6AE6                      CLRF POSTINC1, ACCESS                  
  2417   12E0    DA74                      RCALL usb_ack_dat1                     
  2418   12E2    52E5                      MOVF POSTDEC1, F, ACCESS               
  2419   12E4    52E5                      MOVF POSTDEC1, F, ACCESS               
  2420   12E6    D046                      BRA 0x1374                             
  2421   12E8    0E02                      MOVLW 0x2                              
  2422   12EA    6E10                      MOVWF __tmp_0, ACCESS                  
  2423   12EC    CFDE                      MOVFF POSTINC2, FSR0L                  
  2424   12EE    FFE9                      NOP                                    
  2425   12F0    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2426   12F2    FFEA                      NOP                                    
  2427   12F4    0E04                      MOVLW 0x4                              
  2428   12F6    26E9                      ADDWF FSR0L, F, ACCESS                 
  2429   12F8    0E00                      MOVLW 0                                
  2430   12FA    22EA                      ADDWFC FSR0H, F, ACCESS                
  2431   12FC    50EF                      MOVF INDF0, W, ACCESS                  
  2432   12FE    80D8                      BSF STATUS, 0, ACCESS                  
  2433   1300    5410                      SUBFWB __tmp_0, W, ACCESS              
  2434   1302    E214                      BC 0x132c                              
  2435   1304    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2436   1306    FFE9                      NOP                                    
  2437   1308    C09B                      MOVFF 0x9b, FSR0H                      
  2438   130A    FFEA                      NOP                                    
  2439   130C    0E02                      MOVLW 0x2                              
  2440   130E    26E9                      ADDWF FSR0L, F, ACCESS                 
  2441   1310    0E00                      MOVLW 0                                
  2442   1312    22EA                      ADDWFC FSR0H, F, ACCESS                
  2443   1314    50EE                      MOVF POSTINC0, W, ACCESS               
  2444   1316    CFEF                      MOVFF INDF0, FSR0H                     
  2445   1318    FFEA                      NOP                                    
  2446   131A    6EE9                      MOVWF FSR0L, ACCESS                    
  2447   131C    6AEF                      CLRF INDF0, ACCESS                     
  2448   131E    0E01                      MOVLW 0x1                              
  2449   1320    6EE6                      MOVWF POSTINC1, ACCESS                 
  2450   1322    6AE6                      CLRF POSTINC1, ACCESS                  
  2451   1324    DA52                      RCALL usb_ack_dat1                     
  2452   1326    52E5                      MOVF POSTDEC1, F, ACCESS               
  2453   1328    52E5                      MOVF POSTDEC1, F, ACCESS               
  2454   132A    D001                      BRA 0x132e                             
  2455   132C    DA6E                      RCALL usb_RequestError                 
  2456   132E    D022                      BRA 0x1374                             
  2457   1330    0E02                      MOVLW 0x2                              
  2458   1332    6E10                      MOVWF __tmp_0, ACCESS                  
  2459   1334    CFDE                      MOVFF POSTINC2, FSR0L                  
  2460   1336    FFE9                      NOP                                    
  2461   1338    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2462   133A    FFEA                      NOP                                    
  2463   133C    0E04                      MOVLW 0x4                              
  2464   133E    26E9                      ADDWF FSR0L, F, ACCESS                 
  2465   1340    0E00                      MOVLW 0                                
  2466   1342    22EA                      ADDWFC FSR0H, F, ACCESS                
  2467   1344    50EF                      MOVF INDF0, W, ACCESS                  
  2468   1346    80D8                      BSF STATUS, 0, ACCESS                  
  2469   1348    5410                      SUBFWB __tmp_0, W, ACCESS              
  2470   134A    E211                      BC 0x136e                              
  2471   134C    CFDE                      MOVFF POSTINC2, FSR0L                  
  2472   134E    FFE9                      NOP                                    
  2473   1350    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2474   1352    FFEA                      NOP                                    
  2475   1354    0E02                      MOVLW 0x2                              
  2476   1356    26E9                      ADDWF FSR0L, F, ACCESS                 
  2477   1358    0E00                      MOVLW 0                                
  2478   135A    22EA                      ADDWFC FSR0H, F, ACCESS                
  2479   135C    50EF                      MOVF INDF0, W, ACCESS                  
  2480   135E    E107                      BNZ 0x136e                             
  2481   1360    0E00                      MOVLW 0                                
  2482   1362    6EE6                      MOVWF POSTINC1, ACCESS                 
  2483   1364    6AE6                      CLRF POSTINC1, ACCESS                  
  2484   1366    DA31                      RCALL usb_ack_dat1                     
  2485   1368    52E5                      MOVF POSTDEC1, F, ACCESS               
  2486   136A    52E5                      MOVF POSTDEC1, F, ACCESS               
  2487   136C    D001                      BRA 0x1370                             
  2488   136E    DA4D                      RCALL usb_RequestError                 
  2489   1370    D001                      BRA 0x1374                             
  2490   1372    DA4B                      RCALL usb_RequestError                 
  2491   1374    0E02                      MOVLW 0x2                              
  2492   1376    5CE1                      SUBWF FSR1L, W, ACCESS                 
  2493   1378    E202                      BC 0x137e                              
  2494   137A    6AE1                      CLRF FSR1L, ACCESS                     
  2495   137C    52E5                      MOVF POSTDEC1, F, ACCESS               
  2496   137E    6EE1                      MOVWF FSR1L, ACCESS                    
  2497   1380    52E5                      MOVF POSTDEC1, F, ACCESS               
  2498   1382    CFE7                      MOVFF INDF1, FSR2                      
  2499   1384    FFD9                      NOP                                    
  2500   1386    0012                      RETURN 0                               
  2501   1388    CFD9 usb_handle_StandardEndpointRequest MOVFF FSR2, POSTINC1                   
  2502   138A    FFE6                      NOP                                    
  2503   138C    CFE1                      MOVFF FSR1L, FSR2                      
  2504   138E    FFD9                      NOP                                    
  2505   1390    0E08                      MOVLW 0x8                              
  2506   1392    26E1                      ADDWF FSR1L, F, ACCESS                 
  2507   1394    0EFD                      MOVLW 0xfd                             
  2508   1396    CFDB                      MOVFF PLUSW2, FSR0L                    
  2509   1398    FFE9                      NOP                                    
  2510   139A    0EFE                      MOVLW 0xfe                             
  2511   139C    CFDB                      MOVFF PLUSW2, FSR0H                    
  2512   139E    FFEA                      NOP                                    
  2513   13A0    0E02                      MOVLW 0x2                              
  2514   13A2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2515   13A4    0E00                      MOVLW 0                                
  2516   13A6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2517   13A8    CFEE                      MOVFF POSTINC0, POSTINC2               
  2518   13AA    FFDE                      NOP                                    
  2519   13AC    CFED                      MOVFF POSTDEC0, POSTDEC2               
  2520   13AE    FFDD                      NOP                                    
  2521   13B0    CFDE                      MOVFF POSTINC2, FSR0L                  
  2522   13B2    FFE9                      NOP                                    
  2523   13B4    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2524   13B6    FFEA                      NOP                                    
  2525   13B8    0E01                      MOVLW 0x1                              
  2526   13BA    26E9                      ADDWF FSR0L, F, ACCESS                 
  2527   13BC    0E00                      MOVLW 0                                
  2528   13BE    22EA                      ADDWFC FSR0H, F, ACCESS                
  2529   13C0    50EF                      MOVF INDF0, W, ACCESS                  
  2530   13C2    0A0C                      XORLW 0xc                              
  2531   13C4    E101                      BNZ 0x13c8                             
  2532   13C6    D12A                      BRA 0x161c                             
  2533   13C8    0A0F                      XORLW 0xf                              
  2534   13CA    E101                      BNZ 0x13ce                             
  2535   13CC    D0E6                      BRA 0x159a                             
  2536   13CE    0A02                      XORLW 0x2                              
  2537   13D0    E072                      BZ 0x14b6                              
  2538   13D2    0A01                      XORLW 0x1                              
  2539   13D4    E001                      BZ 0x13d8                              
  2540   13D6    D122                      BRA 0x161c                             
  2541   13D8    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2542   13DA    FFE9                      NOP                                    
  2543   13DC    C09B                      MOVFF 0x9b, FSR0H                      
  2544   13DE    FFEA                      NOP                                    
  2545   13E0    0E02                      MOVLW 0x2                              
  2546   13E2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2547   13E4    0E00                      MOVLW 0                                
  2548   13E6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2549   13E8    50EE                      MOVF POSTINC0, W, ACCESS               
  2550   13EA    CFEF                      MOVFF INDF0, FSR0H                     
  2551   13EC    FFEA                      NOP                                    
  2552   13EE    6EE9                      MOVWF FSR0L, ACCESS                    
  2553   13F0    6AEF                      CLRF INDF0, ACCESS                     
  2554   13F2    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2555   13F4    FFE9                      NOP                                    
  2556   13F6    C09B                      MOVFF 0x9b, FSR0H                      
  2557   13F8    FFEA                      NOP                                    
  2558   13FA    0E02                      MOVLW 0x2                              
  2559   13FC    26E9                      ADDWF FSR0L, F, ACCESS                 
  2560   13FE    0E00                      MOVLW 0                                
  2561   1400    22EA                      ADDWFC FSR0H, F, ACCESS                
  2562   1402    50EE                      MOVF POSTINC0, W, ACCESS               
  2563   1404    CFEF                      MOVFF INDF0, FSR0H                     
  2564   1406    FFEA                      NOP                                    
  2565   1408    6EE9                      MOVWF FSR0L, ACCESS                    
  2566   140A    0E01                      MOVLW 0x1                              
  2567   140C    26E9                      ADDWF FSR0L, F, ACCESS                 
  2568   140E    0E00                      MOVLW 0                                
  2569   1410    22EA                      ADDWFC FSR0H, F, ACCESS                
  2570   1412    6AEF                      CLRF INDF0, ACCESS                     
  2571   1414    CFDE                      MOVFF POSTINC2, FSR0L                  
  2572   1416    FFE9                      NOP                                    
  2573   1418    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2574   141A    FFEA                      NOP                                    
  2575   141C    0E04                      MOVLW 0x4                              
  2576   141E    26E9                      ADDWF FSR0L, F, ACCESS                 
  2577   1420    0E00                      MOVLW 0                                
  2578   1422    22EA                      ADDWFC FSR0H, F, ACCESS                
  2579   1424    50EF                      MOVF INDF0, W, ACCESS                  
  2580   1426    0B0F                      ANDLW 0xf                              
  2581   1428    6EE7                      MOVWF INDF1, ACCESS                    
  2582   142A    0E02                      MOVLW 0x2                              
  2583   142C    CFE7                      MOVFF INDF1, PLUSW2                    
  2584   142E    FFDB                      NOP                                    
  2585   1430    CFDE                      MOVFF POSTINC2, FSR0L                  
  2586   1432    FFE9                      NOP                                    
  2587   1434    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2588   1436    FFEA                      NOP                                    
  2589   1438    0E04                      MOVLW 0x4                              
  2590   143A    26E9                      ADDWF FSR0L, F, ACCESS                 
  2591   143C    0E00                      MOVLW 0                                
  2592   143E    22EA                      ADDWFC FSR0H, F, ACCESS                
  2593   1440    50EF                      MOVF INDF0, W, ACCESS                  
  2594   1442    44E8                      RLNCF WREG, W, ACCESS                  
  2595   1444    0B01                      ANDLW 0x1                              
  2596   1446    6EE7                      MOVWF INDF1, ACCESS                    
  2597   1448    0E03                      MOVLW 0x3                              
  2598   144A    CFE7                      MOVFF INDF1, PLUSW2                    
  2599   144C    FFDB                      NOP                                    
  2600   144E    CFDB                      MOVFF PLUSW2, POSTINC1                 
  2601   1450    FFE6                      NOP                                    
  2602   1452    0E02                      MOVLW 0x2                              
  2603   1454    50DB                      MOVF PLUSW2, W, ACCESS                 
  2604   1456    24E8                      ADDWF WREG, W, ACCESS                  
  2605   1458    52E5                      MOVF POSTDEC1, F, ACCESS               
  2606   145A    24E7                      ADDWF INDF1, W, ACCESS                 
  2607   145C    0D04                      MULLW 0x4                              
  2608   145E    CFF3                      MOVFF PRODL, __tmp_0                   
  2609   1460    F010                      NOP                                    
  2610   1462    CFF4                      MOVFF PRODH, 0x11                      
  2611   1464    F011                      NOP                                    
  2612   1466    0E00                      MOVLW 0                                
  2613   1468    2610                      ADDWF __tmp_0, F, ACCESS               
  2614   146A    0E02                      MOVLW 0x2                              
  2615   146C    2211                      ADDWFC 0x11, F, ACCESS                 
  2616   146E    0E04                      MOVLW 0x4                              
  2617   1470    C010                      MOVFF __tmp_0, PLUSW2                  
  2618   1472    FFDB                      NOP                                    
  2619   1474    0E05                      MOVLW 0x5                              
  2620   1476    C011                      MOVFF 0x11, PLUSW2                     
  2621   1478    FFDB                      NOP                                    
  2622   147A    0E04                      MOVLW 0x4                              
  2623   147C    CFDB                      MOVFF PLUSW2, FSR0L                    
  2624   147E    FFE9                      NOP                                    
  2625   1480    0E05                      MOVLW 0x5                              
  2626   1482    CFDB                      MOVFF PLUSW2, FSR0H                    
  2627   1484    FFEA                      NOP                                    
  2628   1486    94EF                      BCF INDF0, 0x2, ACCESS                 
  2629   1488    50EF                      MOVF INDF0, W, ACCESS                  
  2630   148A    E00E                      BZ 0x14a8                              
  2631   148C    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  2632   148E    FFE9                      NOP                                    
  2633   1490    C09B                      MOVFF 0x9b, FSR0H                      
  2634   1492    FFEA                      NOP                                    
  2635   1494    0E02                      MOVLW 0x2                              
  2636   1496    26E9                      ADDWF FSR0L, F, ACCESS                 
  2637   1498    0E00                      MOVLW 0                                
  2638   149A    22EA                      ADDWFC FSR0H, F, ACCESS                
  2639   149C    50EE                      MOVF POSTINC0, W, ACCESS               
  2640   149E    CFEF                      MOVFF INDF0, FSR0H                     
  2641   14A0    FFEA                      NOP                                    
  2642   14A2    6EE9                      MOVWF FSR0L, ACCESS                    
  2643   14A4    0E01                      MOVLW 0x1                              
  2644   14A6    6EEF                      MOVWF INDF0, ACCESS                    
  2645   14A8    0E02                      MOVLW 0x2                              
  2646   14AA    6EE6                      MOVWF POSTINC1, ACCESS                 
  2647   14AC    6AE6                      CLRF POSTINC1, ACCESS                  
  2648   14AE    D98D                      RCALL usb_ack_dat1                     
  2649   14B0    52E5                      MOVF POSTDEC1, F, ACCESS               
  2650   14B2    52E5                      MOVF POSTDEC1, F, ACCESS               
  2651   14B4    D0B4                      BRA 0x161e                             
  2652   14B6    CFDE                      MOVFF POSTINC2, FSR0L                  
  2653   14B8    FFE9                      NOP                                    
  2654   14BA    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2655   14BC    FFEA                      NOP                                    
  2656   14BE    0E04                      MOVLW 0x4                              
  2657   14C0    26E9                      ADDWF FSR0L, F, ACCESS                 
  2658   14C2    0E00                      MOVLW 0                                
  2659   14C4    22EA                      ADDWFC FSR0H, F, ACCESS                
  2660   14C6    50EF                      MOVF INDF0, W, ACCESS                  
  2661   14C8    0B0F                      ANDLW 0xf                              
  2662   14CA    6EE7                      MOVWF INDF1, ACCESS                    
  2663   14CC    0E02                      MOVLW 0x2                              
  2664   14CE    CFE7                      MOVFF INDF1, PLUSW2                    
  2665   14D0    FFDB                      NOP                                    
  2666   14D2    50D9                      MOVF FSR2, W, ACCESS                   
  2667   14D4    0F06                      ADDLW 0x6                              
  2668   14D6    6EE9                      MOVWF FSR0L, ACCESS                    
  2669   14D8    CFDA                      MOVFF FSR2H, FSR0H                     
  2670   14DA    FFEA                      NOP                                    
  2671   14DC    0E53                      MOVLW 0x53                             
  2672   14DE    6EEE                      MOVWF POSTINC0, ACCESS                 
  2673   14E0    0E0F                      MOVLW 0xf                              
  2674   14E2    6EED                      MOVWF POSTDEC0, ACCESS                 
  2675   14E4    0E02                      MOVLW 0x2                              
  2676   14E6    50DB                      MOVF PLUSW2, W, ACCESS                 
  2677   14E8    6E10                      MOVWF __tmp_0, ACCESS                  
  2678   14EA    6A11                      CLRF 0x11, ACCESS                      
  2679   14EC    50D9                      MOVF FSR2, W, ACCESS                   
  2680   14EE    0F06                      ADDLW 0x6                              
  2681   14F0    6EE9                      MOVWF FSR0L, ACCESS                    
  2682   14F2    CFDA                      MOVFF FSR2H, FSR0H                     
  2683   14F4    FFEA                      NOP                                    
  2684   14F6    5010                      MOVF __tmp_0, W, ACCESS                
  2685   14F8    26EE                      ADDWF POSTINC0, F, ACCESS              
  2686   14FA    5011                      MOVF 0x11, W, ACCESS                   
  2687   14FC    22ED                      ADDWFC POSTDEC0, F, ACCESS             
  2688   14FE    0E06                      MOVLW 0x6                              
  2689   1500    CFDB                      MOVFF PLUSW2, FSR0L                    
  2690   1502    FFE9                      NOP                                    
  2691   1504    0E07                      MOVLW 0x7                              
  2692   1506    CFDB                      MOVFF PLUSW2, FSR0H                    
  2693   1508    FFEA                      NOP                                    
  2694   150A    90EF                      BCF INDF0, 0, ACCESS                   
  2695   150C    CFDE                      MOVFF POSTINC2, FSR0L                  
  2696   150E    FFE9                      NOP                                    
  2697   1510    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2698   1512    FFEA                      NOP                                    
  2699   1514    0E04                      MOVLW 0x4                              
  2700   1516    26E9                      ADDWF FSR0L, F, ACCESS                 
  2701   1518    0E00                      MOVLW 0                                
  2702   151A    22EA                      ADDWFC FSR0H, F, ACCESS                
  2703   151C    50EF                      MOVF INDF0, W, ACCESS                  
  2704   151E    44E8                      RLNCF WREG, W, ACCESS                  
  2705   1520    0B01                      ANDLW 0x1                              
  2706   1522    6EE7                      MOVWF INDF1, ACCESS                    
  2707   1524    0E03                      MOVLW 0x3                              
  2708   1526    CFE7                      MOVFF INDF1, PLUSW2                    
  2709   1528    FFDB                      NOP                                    
  2710   152A    CFDB                      MOVFF PLUSW2, POSTINC1                 
  2711   152C    FFE6                      NOP                                    
  2712   152E    0E02                      MOVLW 0x2                              
  2713   1530    50DB                      MOVF PLUSW2, W, ACCESS                 
  2714   1532    24E8                      ADDWF WREG, W, ACCESS                  
  2715   1534    52E5                      MOVF POSTDEC1, F, ACCESS               
  2716   1536    24E7                      ADDWF INDF1, W, ACCESS                 
  2717   1538    0D04                      MULLW 0x4                              
  2718   153A    CFF3                      MOVFF PRODL, __tmp_0                   
  2719   153C    F010                      NOP                                    
  2720   153E    CFF4                      MOVFF PRODH, 0x11                      
  2721   1540    F011                      NOP                                    
  2722   1542    0E00                      MOVLW 0                                
  2723   1544    2610                      ADDWF __tmp_0, F, ACCESS               
  2724   1546    0E02                      MOVLW 0x2                              
  2725   1548    2211                      ADDWFC 0x11, F, ACCESS                 
  2726   154A    0E04                      MOVLW 0x4                              
  2727   154C    C010                      MOVFF __tmp_0, PLUSW2                  
  2728   154E    FFDB                      NOP                                    
  2729   1550    0E05                      MOVLW 0x5                              
  2730   1552    C011                      MOVFF 0x11, PLUSW2                     
  2731   1554    FFDB                      NOP                                    
  2732   1556    0E04                      MOVLW 0x4                              
  2733   1558    CFDB                      MOVFF PLUSW2, FSR0L                    
  2734   155A    FFE9                      NOP                                    
  2735   155C    0E05                      MOVLW 0x5                              
  2736   155E    CFDB                      MOVFF PLUSW2, FSR0H                    
  2737   1560    FFEA                      NOP                                    
  2738   1562    94EF                      BCF INDF0, 0x2, ACCESS                 
  2739   1564    0E03                      MOVLW 0x3                              
  2740   1566    50DB                      MOVF PLUSW2, W, ACCESS                 
  2741   1568    E007                      BZ 0x1578                              
  2742   156A    0E04                      MOVLW 0x4                              
  2743   156C    CFDB                      MOVFF PLUSW2, FSR0L                    
  2744   156E    FFE9                      NOP                                    
  2745   1570    0E05                      MOVLW 0x5                              
  2746   1572    CFDB                      MOVFF PLUSW2, FSR0H                    
  2747   1574    FFEA                      NOP                                    
  2748   1576    8CEF                      BSF INDF0, 0x6, ACCESS                 
  2749   1578    0E03                      MOVLW 0x3                              
  2750   157A    50DB                      MOVF PLUSW2, W, ACCESS                 
  2751   157C    E107                      BNZ 0x158c                             
  2752   157E    0E04                      MOVLW 0x4                              
  2753   1580    CFDB                      MOVFF PLUSW2, FSR0L                    
  2754   1582    FFE9                      NOP                                    
  2755   1584    0E05                      MOVLW 0x5                              
  2756   1586    CFDB                      MOVFF PLUSW2, FSR0H                    
  2757   1588    FFEA                      NOP                                    
  2758   158A    9CEF                      BCF INDF0, 0x6, ACCESS                 
  2759   158C    0E00                      MOVLW 0                                
  2760   158E    6EE6                      MOVWF POSTINC1, ACCESS                 
  2761   1590    6AE6                      CLRF POSTINC1, ACCESS                  
  2762   1592    D91B                      RCALL usb_ack_dat1                     
  2763   1594    52E5                      MOVF POSTDEC1, F, ACCESS               
  2764   1596    52E5                      MOVF POSTDEC1, F, ACCESS               
  2765   1598    D042                      BRA 0x161e                             
  2766   159A    CFDE                      MOVFF POSTINC2, FSR0L                  
  2767   159C    FFE9                      NOP                                    
  2768   159E    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2769   15A0    FFEA                      NOP                                    
  2770   15A2    0E04                      MOVLW 0x4                              
  2771   15A4    26E9                      ADDWF FSR0L, F, ACCESS                 
  2772   15A6    0E00                      MOVLW 0                                
  2773   15A8    22EA                      ADDWFC FSR0H, F, ACCESS                
  2774   15AA    50EF                      MOVF INDF0, W, ACCESS                  
  2775   15AC    0B0F                      ANDLW 0xf                              
  2776   15AE    6EE7                      MOVWF INDF1, ACCESS                    
  2777   15B0    0E02                      MOVLW 0x2                              
  2778   15B2    CFE7                      MOVFF INDF1, PLUSW2                    
  2779   15B4    FFDB                      NOP                                    
  2780   15B6    CFDE                      MOVFF POSTINC2, FSR0L                  
  2781   15B8    FFE9                      NOP                                    
  2782   15BA    CFDD                      MOVFF POSTDEC2, FSR0H                  
  2783   15BC    FFEA                      NOP                                    
  2784   15BE    0E04                      MOVLW 0x4                              
  2785   15C0    26E9                      ADDWF FSR0L, F, ACCESS                 
  2786   15C2    0E00                      MOVLW 0                                
  2787   15C4    22EA                      ADDWFC FSR0H, F, ACCESS                
  2788   15C6    50EF                      MOVF INDF0, W, ACCESS                  
  2789   15C8    44E8                      RLNCF WREG, W, ACCESS                  
  2790   15CA    0B01                      ANDLW 0x1                              
  2791   15CC    6EE7                      MOVWF INDF1, ACCESS                    
  2792   15CE    0E03                      MOVLW 0x3                              
  2793   15D0    CFE7                      MOVFF INDF1, PLUSW2                    
  2794   15D2    FFDB                      NOP                                    
  2795   15D4    CFDB                      MOVFF PLUSW2, POSTINC1                 
  2796   15D6    FFE6                      NOP                                    
  2797   15D8    0E02                      MOVLW 0x2                              
  2798   15DA    50DB                      MOVF PLUSW2, W, ACCESS                 
  2799   15DC    24E8                      ADDWF WREG, W, ACCESS                  
  2800   15DE    52E5                      MOVF POSTDEC1, F, ACCESS               
  2801   15E0    24E7                      ADDWF INDF1, W, ACCESS                 
  2802   15E2    0D04                      MULLW 0x4                              
  2803   15E4    CFF3                      MOVFF PRODL, __tmp_0                   
  2804   15E6    F010                      NOP                                    
  2805   15E8    CFF4                      MOVFF PRODH, 0x11                      
  2806   15EA    F011                      NOP                                    
  2807   15EC    0E00                      MOVLW 0                                
  2808   15EE    2610                      ADDWF __tmp_0, F, ACCESS               
  2809   15F0    0E02                      MOVLW 0x2                              
  2810   15F2    2211                      ADDWFC 0x11, F, ACCESS                 
  2811   15F4    0E04                      MOVLW 0x4                              
  2812   15F6    C010                      MOVFF __tmp_0, PLUSW2                  
  2813   15F8    FFDB                      NOP                                    
  2814   15FA    0E05                      MOVLW 0x5                              
  2815   15FC    C011                      MOVFF 0x11, PLUSW2                     
  2816   15FE    FFDB                      NOP                                    
  2817   1600    0E04                      MOVLW 0x4                              
  2818   1602    CFDB                      MOVFF PLUSW2, FSR0L                    
  2819   1604    FFE9                      NOP                                    
  2820   1606    0E05                      MOVLW 0x5                              
  2821   1608    CFDB                      MOVFF PLUSW2, FSR0H                    
  2822   160A    FFEA                      NOP                                    
  2823   160C    84EF                      BSF INDF0, 0x2, ACCESS                 
  2824   160E    0E00                      MOVLW 0                                
  2825   1610    6EE6                      MOVWF POSTINC1, ACCESS                 
  2826   1612    6AE6                      CLRF POSTINC1, ACCESS                  
  2827   1614    D8DA                      RCALL usb_ack_dat1                     
  2828   1616    52E5                      MOVF POSTDEC1, F, ACCESS               
  2829   1618    52E5                      MOVF POSTDEC1, F, ACCESS               
  2830   161A    D001                      BRA 0x161e                             
  2831   161C    D8F6                      RCALL usb_RequestError                 
  2832   161E    0E08                      MOVLW 0x8                              
  2833   1620    5CE1                      SUBWF FSR1L, W, ACCESS                 
  2834   1622    E202                      BC 0x1628                              
  2835   1624    6AE1                      CLRF FSR1L, ACCESS                     
  2836   1626    52E5                      MOVF POSTDEC1, F, ACCESS               
  2837   1628    6EE1                      MOVWF FSR1L, ACCESS                    
  2838   162A    52E5                      MOVF POSTDEC1, F, ACCESS               
  2839   162C    CFE7                      MOVFF INDF1, FSR2                      
  2840   162E    FFD9                      NOP                                    
  2841   1630    0012                      RETURN 0                               
  2842   1632    0100 usb_handle_in        MOVLB 0                                
  2843   1634    5197                      MOVF trn_status, W, BANKED             
  2844   1636    40E8                      RRNCF WREG, W, ACCESS                  
  2845   1638    40E8                      RRNCF WREG, W, ACCESS                  
  2846   163A    40E8                      RRNCF WREG, W, ACCESS                  
  2847   163C    0B1F                      ANDLW 0x1f                             
  2848   163E    0B0F                      ANDLW 0xf                              
  2849   1640    0D04                      MULLW 0x4                              
  2850   1642    CFF3                      MOVFF PRODL, FSR0L                     
  2851   1644    FFE9                      NOP                                    
  2852   1646    CFF4                      MOVFF PRODH, FSR0H                     
  2853   1648    FFEA                      NOP                                    
  2854   164A    0E71                      MOVLW 0x71                             
  2855   164C    26E9                      ADDWF FSR0L, F, ACCESS                 
  2856   164E    0E00                      MOVLW 0                                
  2857   1650    22EA                      ADDWFC FSR0H, F, ACCESS                
  2858   1652    50EE                      MOVF POSTINC0, W, ACCESS               
  2859   1654    10ED                      IORWF POSTDEC0, W, ACCESS              
  2860   1656    E019                      BZ 0x168a                              
  2861   1658    5197                      MOVF trn_status, W, BANKED             
  2862   165A    40E8                      RRNCF WREG, W, ACCESS                  
  2863   165C    40E8                      RRNCF WREG, W, ACCESS                  
  2864   165E    40E8                      RRNCF WREG, W, ACCESS                  
  2865   1660    0B1F                      ANDLW 0x1f                             
  2866   1662    0B0F                      ANDLW 0xf                              
  2867   1664    0D04                      MULLW 0x4                              
  2868   1666    CFF3                      MOVFF PRODL, FSR0L                     
  2869   1668    FFE9                      NOP                                    
  2870   166A    CFF4                      MOVFF PRODH, FSR0H                     
  2871   166C    FFEA                      NOP                                    
  2872   166E    0E71                      MOVLW 0x71                             
  2873   1670    26E9                      ADDWF FSR0L, F, ACCESS                 
  2874   1672    0E00                      MOVLW 0                                
  2875   1674    22EA                      ADDWFC FSR0H, F, ACCESS                
  2876   1676    CFEE                      MOVFF POSTINC0, __tmp_0                
  2877   1678    F010                      NOP                                    
  2878   167A    CFEF                      MOVFF INDF0, 0x11                      
  2879   167C    F011                      NOP                                    
  2880   167E    D004                      BRA 0x1688                             
  2881   1680    C011                      MOVFF 0x11, PCLATH                     
  2882   1682    FFFA                      NOP                                    
  2883   1684    5010                      MOVF __tmp_0, W, ACCESS                
  2884   1686    6EF9                      MOVWF PCL, ACCESS                      
  2885   1688    DFFB                      RCALL 0x1680                           
  2886   168A    0012                      RETURN 0                               
  2887   168C    0100 usb_handle_out       MOVLB 0                                
  2888   168E    5197                      MOVF trn_status, W, BANKED             
  2889   1690    40E8                      RRNCF WREG, W, ACCESS                  
  2890   1692    40E8                      RRNCF WREG, W, ACCESS                  
  2891   1694    40E8                      RRNCF WREG, W, ACCESS                  
  2892   1696    0B1F                      ANDLW 0x1f                             
  2893   1698    0B0F                      ANDLW 0xf                              
  2894   169A    0D04                      MULLW 0x4                              
  2895   169C    CFF3                      MOVFF PRODL, FSR0L                     
  2896   169E    FFE9                      NOP                                    
  2897   16A0    CFF4                      MOVFF PRODH, FSR0H                     
  2898   16A2    FFEA                      NOP                                    
  2899   16A4    0E71                      MOVLW 0x71                             
  2900   16A6    26E9                      ADDWF FSR0L, F, ACCESS                 
  2901   16A8    0E00                      MOVLW 0                                
  2902   16AA    22EA                      ADDWFC FSR0H, F, ACCESS                
  2903   16AC    0E02                      MOVLW 0x2                              
  2904   16AE    26E9                      ADDWF FSR0L, F, ACCESS                 
  2905   16B0    0E00                      MOVLW 0                                
  2906   16B2    22EA                      ADDWFC FSR0H, F, ACCESS                
  2907   16B4    50EE                      MOVF POSTINC0, W, ACCESS               
  2908   16B6    10ED                      IORWF POSTDEC0, W, ACCESS              
  2909   16B8    E01D                      BZ 0x16f4                              
  2910   16BA    5197                      MOVF trn_status, W, BANKED             
  2911   16BC    40E8                      RRNCF WREG, W, ACCESS                  
  2912   16BE    40E8                      RRNCF WREG, W, ACCESS                  
  2913   16C0    40E8                      RRNCF WREG, W, ACCESS                  
  2914   16C2    0B1F                      ANDLW 0x1f                             
  2915   16C4    0B0F                      ANDLW 0xf                              
  2916   16C6    0D04                      MULLW 0x4                              
  2917   16C8    CFF3                      MOVFF PRODL, FSR0L                     
  2918   16CA    FFE9                      NOP                                    
  2919   16CC    CFF4                      MOVFF PRODH, FSR0H                     
  2920   16CE    FFEA                      NOP                                    
  2921   16D0    0E71                      MOVLW 0x71                             
  2922   16D2    26E9                      ADDWF FSR0L, F, ACCESS                 
  2923   16D4    0E00                      MOVLW 0                                
  2924   16D6    22EA                      ADDWFC FSR0H, F, ACCESS                
  2925   16D8    0E02                      MOVLW 0x2                              
  2926   16DA    26E9                      ADDWF FSR0L, F, ACCESS                 
  2927   16DC    0E00                      MOVLW 0                                
  2928   16DE    22EA                      ADDWFC FSR0H, F, ACCESS                
  2929   16E0    CFEE                      MOVFF POSTINC0, __tmp_0                
  2930   16E2    F010                      NOP                                    
  2931   16E4    CFEF                      MOVFF INDF0, 0x11                      
  2932   16E6    F011                      NOP                                    
  2933   16E8    D004                      BRA 0x16f2                             
  2934   16EA    C011                      MOVFF 0x11, PCLATH                     
  2935   16EC    FFFA                      NOP                                    
  2936   16EE    5010                      MOVF __tmp_0, W, ACCESS                
  2937   16F0    6EF9                      MOVWF PCL, ACCESS                      
  2938   16F2    DFFB                      RCALL 0x16ea                           
  2939   16F4    0012                      RETURN 0                               
  2940   16F6    CFD9 usb_register_sof_handler MOVFF FSR2, POSTINC1                   
  2941   16F8    FFE6                      NOP                                    
  2942   16FA    CFE1                      MOVFF FSR1L, FSR2                      
  2943   16FC    FFD9                      NOP                                    
  2944   16FE    0EFD                      MOVLW 0xfd                             
  2945   1700    CFDB                      MOVFF PLUSW2, sof_handler              
  2946   1702    F06B                      NOP                                    
  2947   1704    0EFE                      MOVLW 0xfe                             
  2948   1706    CFDB                      MOVFF PLUSW2, 0x6c                     
  2949   1708    F06C                      NOP                                    
  2950   170A    52E5                      MOVF POSTDEC1, F, ACCESS               
  2951   170C    CFE7                      MOVFF INDF1, FSR2                      
  2952   170E    FFD9                      NOP                                    
  2953   1710    0012                      RETURN 0                               
  2954   1712    CFD9 usb_register_class_setup_handler MOVFF FSR2, POSTINC1                   
  2955   1714    FFE6                      NOP                                    
  2956   1716    CFE1                      MOVFF FSR1L, FSR2                      
  2957   1718    FFD9                      NOP                                    
  2958   171A    0EFD                      MOVLW 0xfd                             
  2959   171C    CFDB                      MOVFF PLUSW2, class_setup_handler      
  2960   171E    F06D                      NOP                                    
  2961   1720    0EFE                      MOVLW 0xfe                             
  2962   1722    CFDB                      MOVFF PLUSW2, 0x6e                     
  2963   1724    F06E                      NOP                                    
  2964   1726    52E5                      MOVF POSTDEC1, F, ACCESS               
  2965   1728    CFE7                      MOVFF INDF1, FSR2                      
  2966   172A    FFD9                      NOP                                    
  2967   172C    0012                      RETURN 0                               
  2968   172E    CFD9 usb_register_vendor_setup_handler MOVFF FSR2, POSTINC1                   
  2969   1730    FFE6                      NOP                                    
  2970   1732    CFE1                      MOVFF FSR1L, FSR2                      
  2971   1734    FFD9                      NOP                                    
  2972   1736    0EFD                      MOVLW 0xfd                             
  2973   1738    CFDB                      MOVFF PLUSW2, vendor_setup_handler     
  2974   173A    F06F                      NOP                                    
  2975   173C    0EFE                      MOVLW 0xfe                             
  2976   173E    CFDB                      MOVFF PLUSW2, 0x70                     
  2977   1740    F070                      NOP                                    
  2978   1742    52E5                      MOVF POSTDEC1, F, ACCESS               
  2979   1744    CFE7                      MOVFF INDF1, FSR2                      
  2980   1746    FFD9                      NOP                                    
  2981   1748    0012                      RETURN 0                               
  2982   174A    CFD9 usb_set_in_handler   MOVFF FSR2, POSTINC1                   
  2983   174C    FFE6                      NOP                                    
  2984   174E    CFE1                      MOVFF FSR1L, FSR2                      
  2985   1750    FFD9                      NOP                                    
  2986   1752    0EFD                      MOVLW 0xfd                             
  2987   1754    CFDB                      MOVFF PLUSW2, FSR0L                    
  2988   1756    FFE9                      NOP                                    
  2989   1758    0EFE                      MOVLW 0xfe                             
  2990   175A    CFDB                      MOVFF PLUSW2, FSR0H                    
  2991   175C    FFEA                      NOP                                    
  2992   175E    90D8                      BCF STATUS, 0, ACCESS                  
  2993   1760    36E9                      RLCF FSR0L, F, ACCESS                  
  2994   1762    36EA                      RLCF FSR0H, F, ACCESS                  
  2995   1764    90D8                      BCF STATUS, 0, ACCESS                  
  2996   1766    36E9                      RLCF FSR0L, F, ACCESS                  
  2997   1768    36EA                      RLCF FSR0H, F, ACCESS                  
  2998   176A    0E71                      MOVLW 0x71                             
  2999   176C    26E9                      ADDWF FSR0L, F, ACCESS                 
  3000   176E    0E00                      MOVLW 0                                
  3001   1770    22EA                      ADDWFC FSR0H, F, ACCESS                
  3002   1772    0EFB                      MOVLW 0xfb                             
  3003   1774    CFDB                      MOVFF PLUSW2, POSTINC0                 
  3004   1776    FFEE                      NOP                                    
  3005   1778    0EFC                      MOVLW 0xfc                             
  3006   177A    CFDB                      MOVFF PLUSW2, POSTDEC0                 
  3007   177C    FFED                      NOP                                    
  3008   177E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3009   1780    CFE7                      MOVFF INDF1, FSR2                      
  3010   1782    FFD9                      NOP                                    
  3011   1784    0012                      RETURN 0                               
  3012   1786    CFD9 usb_set_out_handler  MOVFF FSR2, POSTINC1                   
  3013   1788    FFE6                      NOP                                    
  3014   178A    CFE1                      MOVFF FSR1L, FSR2                      
  3015   178C    FFD9                      NOP                                    
  3016   178E    0EFD                      MOVLW 0xfd                             
  3017   1790    CFDB                      MOVFF PLUSW2, FSR0L                    
  3018   1792    FFE9                      NOP                                    
  3019   1794    0EFE                      MOVLW 0xfe                             
  3020   1796    CFDB                      MOVFF PLUSW2, FSR0H                    
  3021   1798    FFEA                      NOP                                    
  3022   179A    90D8                      BCF STATUS, 0, ACCESS                  
  3023   179C    36E9                      RLCF FSR0L, F, ACCESS                  
  3024   179E    36EA                      RLCF FSR0H, F, ACCESS                  
  3025   17A0    90D8                      BCF STATUS, 0, ACCESS                  
  3026   17A2    36E9                      RLCF FSR0L, F, ACCESS                  
  3027   17A4    36EA                      RLCF FSR0H, F, ACCESS                  
  3028   17A6    0E71                      MOVLW 0x71                             
  3029   17A8    26E9                      ADDWF FSR0L, F, ACCESS                 
  3030   17AA    0E00                      MOVLW 0                                
  3031   17AC    22EA                      ADDWFC FSR0H, F, ACCESS                
  3032   17AE    0E02                      MOVLW 0x2                              
  3033   17B0    26E9                      ADDWF FSR0L, F, ACCESS                 
  3034   17B2    0E00                      MOVLW 0                                
  3035   17B4    22EA                      ADDWFC FSR0H, F, ACCESS                
  3036   17B6    0EFB                      MOVLW 0xfb                             
  3037   17B8    CFDB                      MOVFF PLUSW2, POSTINC0                 
  3038   17BA    FFEE                      NOP                                    
  3039   17BC    0EFC                      MOVLW 0xfc                             
  3040   17BE    CFDB                      MOVFF PLUSW2, POSTDEC0                 
  3041   17C0    FFED                      NOP                                    
  3042   17C2    52E5                      MOVF POSTDEC1, F, ACCESS               
  3043   17C4    CFE7                      MOVFF INDF1, FSR2                      
  3044   17C6    FFD9                      NOP                                    
  3045   17C8    0012                      RETURN 0                               
  3046   17CA    CFD9 usb_ack_dat1         MOVFF FSR2, POSTINC1                   
  3047   17CC    FFE6                      NOP                                    
  3048   17CE    CFE1                      MOVFF FSR1L, FSR2                      
  3049   17D0    FFD9                      NOP                                    
  3050   17D2    0EFF                      MOVLW 0xff                             
  3051   17D4    6EE7                      MOVWF INDF1, ACCESS                    
  3052   17D6    0EFD                      MOVLW 0xfd                             
  3053   17D8    CFDB                      MOVFF PLUSW2, __tmp_0                  
  3054   17DA    F010                      NOP                                    
  3055   17DC    0EFE                      MOVLW 0xfe                             
  3056   17DE    CFDB                      MOVFF PLUSW2, 0x11                     
  3057   17E0    F011                      NOP                                    
  3058   17E2    50E7                      MOVF INDF1, W, ACCESS                  
  3059   17E4    1610                      ANDWF __tmp_0, F, ACCESS               
  3060   17E6    6A11                      CLRF 0x11, ACCESS                      
  3061   17E8    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3062   17EA    FFE9                      NOP                                    
  3063   17EC    C09B                      MOVFF 0x9b, FSR0H                      
  3064   17EE    FFEA                      NOP                                    
  3065   17F0    52EE                      MOVF POSTINC0, F, ACCESS               
  3066   17F2    C010                      MOVFF __tmp_0, INDF0                   
  3067   17F4    FFEF                      NOP                                    
  3068   17F6    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3069   17F8    FFE9                      NOP                                    
  3070   17FA    C09B                      MOVFF 0x9b, FSR0H                      
  3071   17FC    FFEA                      NOP                                    
  3072   17FE    0EC8                      MOVLW 0xc8                             
  3073   1800    6EEF                      MOVWF INDF0, ACCESS                    
  3074   1802    52E5                      MOVF POSTDEC1, F, ACCESS               
  3075   1804    CFE7                      MOVFF INDF1, FSR2                      
  3076   1806    FFD9                      NOP                                    
  3077   1808    0012                      RETURN 0                               
  3078   180A    0102 usb_RequestError     MOVLB 0x2                              
  3079   180C    0E08                      MOVLW 0x8                              
  3080   180E    6F01                      MOVWF 0x1, BANKED                      
  3081   1810    0E84                      MOVLW 0x84                             
  3082   1812    6F04                      MOVWF dwBaudrem, BANKED                
  3083   1814    6F00                      MOVWF RecvdByte, BANKED                
  3084   1816    0012                      RETURN 0                               
  3085   1818    0100 usb_set_address      MOVLB 0                                
  3086   181A    5196                      MOVF usb_addr_pending, W, BANKED       
  3087   181C    E103                      BNZ 0x1824                             
  3088   181E    0E04                      MOVLW 0x4                              
  3089   1820    6F95                      MOVWF usb_device_state, BANKED         
  3090   1822    D002                      BRA 0x1828                             
  3091   1824    0E10                      MOVLW 0x10                             
  3092   1826    6F95                      MOVWF usb_device_state, BANKED         
  3093   1828    C096                      MOVFF usb_addr_pending, UADDR          
  3094   182A    FF5C                      NOP                                    
  3095   182C    6996                      SETF usb_addr_pending, BANKED          
  3096   182E    0E00                      MOVLW 0                                
  3097   1830    6EE6                      MOVWF POSTINC1, ACCESS                 
  3098   1832    6AE6                      CLRF POSTINC1, ACCESS                  
  3099   1834    6EE6                      MOVWF POSTINC1, ACCESS                 
  3100   1836    6AE6                      CLRF POSTINC1, ACCESS                  
  3101   1838    DF88                      RCALL usb_set_in_handler               
  3102   183A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3103   183C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3104   183E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3105   1840    52E5                      MOVF POSTDEC1, F, ACCESS               
  3106   1842    0012                      RETURN 0                               
  3107   1844    CFD9 usb_send_rom         MOVFF FSR2, POSTINC1                   
  3108   1846    FFE6                      NOP                                    
  3109   1848    CFE1                      MOVFF FSR1L, FSR2                      
  3110   184A    FFD9                      NOP                                    
  3111   184C    0E04                      MOVLW 0x4                              
  3112   184E    26E1                      ADDWF FSR1L, F, ACCESS                 
  3113   1850    0100                      MOVLB 0                                
  3114   1852    519F                      MOVF usb_rom_len, W, BANKED            
  3115   1854    11A0                      IORWF 0xa0, W, BANKED                  
  3116   1856    E056                      BZ 0x1904                              
  3117   1858    0E08                      MOVLW 0x8                              
  3118   185A    5D9F                      SUBWF usb_rom_len, W, BANKED           
  3119   185C    0E00                      MOVLW 0                                
  3120   185E    59A0                      SUBWFB 0xa0, W, BANKED                 
  3121   1860    E205                      BC 0x186c                              
  3122   1862    C09F                      MOVFF usb_rom_len, __tmp_0             
  3123   1864    F010                      NOP                                    
  3124   1866    C0A0                      MOVFF 0xa0, 0x11                       
  3125   1868    F011                      NOP                                    
  3126   186A    D003                      BRA 0x1872                             
  3127   186C    0E08                      MOVLW 0x8                              
  3128   186E    6E10                      MOVWF __tmp_0, ACCESS                  
  3129   1870    6A11                      CLRF 0x11, ACCESS                      
  3130   1872    0E02                      MOVLW 0x2                              
  3131   1874    C010                      MOVFF __tmp_0, PLUSW2                  
  3132   1876    FFDB                      NOP                                    
  3133   1878    0E03                      MOVLW 0x3                              
  3134   187A    C011                      MOVFF 0x11, PLUSW2                     
  3135   187C    FFDB                      NOP                                    
  3136   187E    6ADE                      CLRF POSTINC2, ACCESS                  
  3137   1880    6ADD                      CLRF POSTDEC2, ACCESS                  
  3138   1882    CFDE                      MOVFF POSTINC2, __tmp_0                
  3139   1884    F010                      NOP                                    
  3140   1886    CFDD                      MOVFF POSTDEC2, 0x11                   
  3141   1888    F011                      NOP                                    
  3142   188A    0E02                      MOVLW 0x2                              
  3143   188C    CFDB                      MOVFF PLUSW2, 0x12                     
  3144   188E    F012                      NOP                                    
  3145   1890    0E03                      MOVLW 0x3                              
  3146   1892    CFDB                      MOVFF PLUSW2, 0x13                     
  3147   1894    F013                      NOP                                    
  3148   1896    5012                      MOVF 0x12, W, ACCESS                   
  3149   1898    5C10                      SUBWF __tmp_0, W, ACCESS               
  3150   189A    5013                      MOVF 0x13, W, ACCESS                   
  3151   189C    5811                      SUBWFB 0x11, W, ACCESS                 
  3152   189E    E231                      BC 0x1902                              
  3153   18A0    CFDE                      MOVFF POSTINC2, 0x12                   
  3154   18A2    F012                      NOP                                    
  3155   18A4    CFDD                      MOVFF POSTDEC2, 0x13                   
  3156   18A6    F013                      NOP                                    
  3157   18A8    6A14                      CLRF 0x14, ACCESS                      
  3158   18AA    519C                      MOVF usb_rom_ptr, W, BANKED            
  3159   18AC    2412                      ADDWF 0x12, W, ACCESS                  
  3160   18AE    6EF3                      MOVWF PRODL, ACCESS                    
  3161   18B0    519D                      MOVF 0x9d, W, BANKED                   
  3162   18B2    2013                      ADDWFC 0x13, W, ACCESS                 
  3163   18B4    6EF4                      MOVWF PRODH, ACCESS                    
  3164   18B6    519E                      MOVF 0x9e, W, BANKED                   
  3165   18B8    2014                      ADDWFC 0x14, W, ACCESS                 
  3166   18BA    6EF8                      MOVWF TBLPTRU, ACCESS                  
  3167   18BC    CFF4                      MOVFF PRODH, TBLPTRH                   
  3168   18BE    FFF7                      NOP                                    
  3169   18C0    CFF3                      MOVFF PRODL, TBLPTRL                   
  3170   18C2    FFF6                      NOP                                    
  3171   18C4    0008                      TBLRD*                                 
  3172   18C6    50F5                      MOVF TABLAT, W, ACCESS                 
  3173   18C8    6EE6                      MOVWF POSTINC1, ACCESS                 
  3174   18CA    CFDE                      MOVFF POSTINC2, __tmp_0                
  3175   18CC    F010                      NOP                                    
  3176   18CE    CFDD                      MOVFF POSTDEC2, 0x11                   
  3177   18D0    F011                      NOP                                    
  3178   18D2    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3179   18D4    FFE9                      NOP                                    
  3180   18D6    C09B                      MOVFF 0x9b, FSR0H                      
  3181   18D8    FFEA                      NOP                                    
  3182   18DA    0E02                      MOVLW 0x2                              
  3183   18DC    26E9                      ADDWF FSR0L, F, ACCESS                 
  3184   18DE    0E00                      MOVLW 0                                
  3185   18E0    22EA                      ADDWFC FSR0H, F, ACCESS                
  3186   18E2    5010                      MOVF __tmp_0, W, ACCESS                
  3187   18E4    24EE                      ADDWF POSTINC0, W, ACCESS              
  3188   18E6    6EE7                      MOVWF INDF1, ACCESS                    
  3189   18E8    5011                      MOVF 0x11, W, ACCESS                   
  3190   18EA    20EE                      ADDWFC POSTINC0, W, ACCESS             
  3191   18EC    6EEA                      MOVWF FSR0H, ACCESS                    
  3192   18EE    CFE7                      MOVFF INDF1, FSR0L                     
  3193   18F0    FFE9                      NOP                                    
  3194   18F2    52E5                      MOVF POSTDEC1, F, ACCESS               
  3195   18F4    50E7                      MOVF INDF1, W, ACCESS                  
  3196   18F6    6EEF                      MOVWF INDF0, ACCESS                    
  3197   18F8    2ADF                      INCF INDF2, F, ACCESS                  
  3198   18FA    0E01                      MOVLW 0x1                              
  3199   18FC    E301                      BNC 0x1900                             
  3200   18FE    2ADB                      INCF PLUSW2, F, ACCESS                 
  3201   1900    D7C0                      BRA 0x1882                             
  3202   1902    D00E                      BRA 0x1920                             
  3203   1904    0E02                      MOVLW 0x2                              
  3204   1906    6ADB                      CLRF PLUSW2, ACCESS                    
  3205   1908    0E03                      MOVLW 0x3                              
  3206   190A    6ADB                      CLRF PLUSW2, ACCESS                    
  3207   190C    0E00                      MOVLW 0                                
  3208   190E    6EE6                      MOVWF POSTINC1, ACCESS                 
  3209   1910    6AE6                      CLRF POSTINC1, ACCESS                  
  3210   1912    6EE6                      MOVWF POSTINC1, ACCESS                 
  3211   1914    6AE6                      CLRF POSTINC1, ACCESS                  
  3212   1916    DF19                      RCALL usb_set_in_handler               
  3213   1918    52E5                      MOVF POSTDEC1, F, ACCESS               
  3214   191A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3215   191C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3216   191E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3217   1920    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3218   1922    FFE9                      NOP                                    
  3219   1924    C09B                      MOVFF 0x9b, FSR0H                      
  3220   1926    FFEA                      NOP                                    
  3221   1928    52EE                      MOVF POSTINC0, F, ACCESS               
  3222   192A    0E02                      MOVLW 0x2                              
  3223   192C    CFDB                      MOVFF PLUSW2, INDF0                    
  3224   192E    FFEF                      NOP                                    
  3225   1930    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3226   1932    FFE9                      NOP                                    
  3227   1934    C09B                      MOVFF 0x9b, FSR0H                      
  3228   1936    FFEA                      NOP                                    
  3229   1938    50EF                      MOVF INDF0, W, ACCESS                  
  3230   193A    0A40                      XORLW 0x40                             
  3231   193C    0B40                      ANDLW 0x40                             
  3232   193E    0980                      IORLW 0x80                             
  3233   1940    0908                      IORLW 0x8                              
  3234   1942    6EE6                      MOVWF POSTINC1, ACCESS                 
  3235   1944    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3236   1946    FFE9                      NOP                                    
  3237   1948    C09B                      MOVFF 0x9b, FSR0H                      
  3238   194A    FFEA                      NOP                                    
  3239   194C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3240   194E    50E7                      MOVF INDF1, W, ACCESS                  
  3241   1950    6EEF                      MOVWF INDF0, ACCESS                    
  3242   1952    0E02                      MOVLW 0x2                              
  3243   1954    CFDB                      MOVFF PLUSW2, __tmp_0                  
  3244   1956    F010                      NOP                                    
  3245   1958    0E03                      MOVLW 0x3                              
  3246   195A    CFDB                      MOVFF PLUSW2, 0x11                     
  3247   195C    F011                      NOP                                    
  3248   195E    6A12                      CLRF 0x12, ACCESS                      
  3249   1960    5010                      MOVF __tmp_0, W, ACCESS                
  3250   1962    0100                      MOVLB 0                                
  3251   1964    279C                      ADDWF usb_rom_ptr, F, BANKED           
  3252   1966    5011                      MOVF 0x11, W, ACCESS                   
  3253   1968    239D                      ADDWFC 0x9d, F, BANKED                 
  3254   196A    5012                      MOVF 0x12, W, ACCESS                   
  3255   196C    239E                      ADDWFC 0x9e, F, BANKED                 
  3256   196E    0E02                      MOVLW 0x2                              
  3257   1970    CFDB                      MOVFF PLUSW2, pUEP                     
  3258   1972    F006                      NOP                                    
  3259   1974    0E03                      MOVLW 0x3                              
  3260   1976    CFDB                      MOVFF PLUSW2, 0x7                      
  3261   1978    F007                      NOP                                    
  3262   197A    5006                      MOVF pUEP, W, ACCESS                   
  3263   197C    5F9F                      SUBWF usb_rom_len, F, BANKED           
  3264   197E    5007                      MOVF 0x7, W, ACCESS                    
  3265   1980    5BA0                      SUBWFB 0xa0, F, BANKED                 
  3266   1982    0E04                      MOVLW 0x4                              
  3267   1984    5CE1                      SUBWF FSR1L, W, ACCESS                 
  3268   1986    E202                      BC 0x198c                              
  3269   1988    6AE1                      CLRF FSR1L, ACCESS                     
  3270   198A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3271   198C    6EE1                      MOVWF FSR1L, ACCESS                    
  3272   198E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3273   1990    CFE7                      MOVFF INDF1, FSR2                      
  3274   1992    FFD9                      NOP                                    
  3275   1994    0012                      RETURN 0                               
  3276   1996    0100 initCDC              MOVLB 0                                
  3277   1998    6BA2                      CLRF linecodeing, BANKED               
  3278   199A    0EC2                      MOVLW 0xc2                             
  3279   199C    6FA3                      MOVWF 0xa3, BANKED                     
  3280   199E    0E01                      MOVLW 0x1                              
  3281   19A0    6FA4                      MOVWF 0xa4, BANKED                     
  3282   19A2    6BA5                      CLRF 0xa5, BANKED                      
  3283   19A4    6BA6                      CLRF 0xa6, BANKED                      
  3284   19A6    6BA7                      CLRF 0xa7, BANKED                      
  3285   19A8    0E08                      MOVLW 0x8                              
  3286   19AA    6FA8                      MOVWF 0xa8, BANKED                     
  3287   19AC    91A9                      BCF cls, 0, BANKED                     
  3288   19AE    93A9                      BCF cls, 0x1, BANKED                   
  3289   19B0    0EC4                      MOVLW 0xc4                             
  3290   19B2    6EE6                      MOVWF POSTINC1, ACCESS                 
  3291   19B4    0E1A                      MOVLW 0x1a                             
  3292   19B6    6EE6                      MOVWF POSTINC1, ACCESS                 
  3293   19B8    EC89                      CALL usb_register_class_setup_handler, 0
  3294   19BA    F00B                      NOP                                    
  3295   19BC    52E5                      MOVF POSTDEC1, F, ACCESS               
  3296   19BE    52E5                      MOVF POSTDEC1, F, ACCESS               
  3297   19C0    0012                      RETURN 0                               
  3298   19C2    0E00 user_configured_init MOVLW 0                                
  3299   19C4    6EE6                      MOVWF POSTINC1, ACCESS                 
  3300   19C6    6AE6                      CLRF POSTINC1, ACCESS                  
  3301   19C8    0E01                      MOVLW 0x1                              
  3302   19CA    6EE6                      MOVWF POSTINC1, ACCESS                 
  3303   19CC    6AE6                      CLRF POSTINC1, ACCESS                  
  3304   19CE    ECA5                      CALL usb_set_in_handler, 0             
  3305   19D0    F00B                      NOP                                    
  3306   19D2    52E5                      MOVF POSTDEC1, F, ACCESS               
  3307   19D4    52E5                      MOVF POSTDEC1, F, ACCESS               
  3308   19D6    52E5                      MOVF POSTDEC1, F, ACCESS               
  3309   19D8    52E5                      MOVF POSTDEC1, F, ACCESS               
  3310   19DA    0E00                      MOVLW 0                                
  3311   19DC    6EE6                      MOVWF POSTINC1, ACCESS                 
  3312   19DE    6AE6                      CLRF POSTINC1, ACCESS                  
  3313   19E0    0E02                      MOVLW 0x2                              
  3314   19E2    6EE6                      MOVWF POSTINC1, ACCESS                 
  3315   19E4    6AE6                      CLRF POSTINC1, ACCESS                  
  3316   19E6    ECA5                      CALL usb_set_in_handler, 0             
  3317   19E8    F00B                      NOP                                    
  3318   19EA    52E5                      MOVF POSTDEC1, F, ACCESS               
  3319   19EC    52E5                      MOVF POSTDEC1, F, ACCESS               
  3320   19EE    52E5                      MOVF POSTDEC1, F, ACCESS               
  3321   19F0    52E5                      MOVF POSTDEC1, F, ACCESS               
  3322   19F2    0E00                      MOVLW 0                                
  3323   19F4    6EE6                      MOVWF POSTINC1, ACCESS                 
  3324   19F6    6AE6                      CLRF POSTINC1, ACCESS                  
  3325   19F8    0E02                      MOVLW 0x2                              
  3326   19FA    6EE6                      MOVWF POSTINC1, ACCESS                 
  3327   19FC    6AE6                      CLRF POSTINC1, ACCESS                  
  3328   19FE    ECC3                      CALL usb_set_out_handler, 0            
  3329   1A00    F00B                      NOP                                    
  3330   1A02    52E5                      MOVF POSTDEC1, F, ACCESS               
  3331   1A04    52E5                      MOVF POSTDEC1, F, ACCESS               
  3332   1A06    52E5                      MOVF POSTDEC1, F, ACCESS               
  3333   1A08    52E5                      MOVF POSTDEC1, F, ACCESS               
  3334   1A0A    010F                      MOVLB 0xf                              
  3335   1A0C    0E1A                      MOVLW 0x1a                             
  3336   1A0E    6F54                      MOVWF 0x54, BANKED                     
  3337   1A10    0E1E                      MOVLW 0x1e                             
  3338   1A12    6F55                      MOVWF 0x55, BANKED                     
  3339   1A14    0102                      MOVLB 0x2                              
  3340   1A16    6B0D                      CLRF 0xd, BANKED                       
  3341   1A18    0E50                      MOVLW 0x50                             
  3342   1A1A    6F0E                      MOVWF 0xe, BANKED                      
  3343   1A1C    0E02                      MOVLW 0x2                              
  3344   1A1E    6F0F                      MOVWF 0xf, BANKED                      
  3345   1A20    0E48                      MOVLW 0x48                             
  3346   1A22    6F0C                      MOVWF 0xc, BANKED                      
  3347   1A24    0EC4                      MOVLW 0xc4                             
  3348   1A26    6EE6                      MOVWF POSTINC1, ACCESS                 
  3349   1A28    0E1A                      MOVLW 0x1a                             
  3350   1A2A    6EE6                      MOVWF POSTINC1, ACCESS                 
  3351   1A2C    EC89                      CALL usb_register_class_setup_handler, 0
  3352   1A2E    F00B                      NOP                                    
  3353   1A30    52E5                      MOVF POSTDEC1, F, ACCESS               
  3354   1A32    52E5                      MOVF POSTDEC1, F, ACCESS               
  3355   1A34    0100                      MOVLB 0                                
  3356   1A36    6BB8                      CLRF cdc_trf_state, BANKED             
  3357   1A38    0E10                      MOVLW 0x10                             
  3358   1A3A    6FB3                      MOVWF CDC_Outbdp, BANKED               
  3359   1A3C    0E02                      MOVLW 0x2                              
  3360   1A3E    6FB4                      MOVWF 0xb4, BANKED                     
  3361   1A40    0E14                      MOVLW 0x14                             
  3362   1A42    6FB5                      MOVWF CDC_Inbdp, BANKED                
  3363   1A44    0E02                      MOVLW 0x2                              
  3364   1A46    6FB6                      MOVWF 0xb6, BANKED                     
  3365   1A48    69AD                      SETF IsInBufferA, BANKED               
  3366   1A4A    0E80                      MOVLW 0x80                             
  3367   1A4C    6FAF                      MOVWF InPtr, BANKED                    
  3368   1A4E    0E02                      MOVLW 0x2                              
  3369   1A50    6FB0                      MOVWF 0xb0, BANKED                     
  3370   1A52    6BAB                      CLRF cdc_In_len, BANKED                
  3371   1A54    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  3372   1A56    FFE9                      NOP                                    
  3373   1A58    C0B6                      MOVFF 0xb6, FSR0H                      
  3374   1A5A    FFEA                      NOP                                    
  3375   1A5C    0E02                      MOVLW 0x2                              
  3376   1A5E    26E9                      ADDWF FSR0L, F, ACCESS                 
  3377   1A60    0E00                      MOVLW 0                                
  3378   1A62    22EA                      ADDWFC FSR0H, F, ACCESS                
  3379   1A64    0E80                      MOVLW 0x80                             
  3380   1A66    6EEE                      MOVWF POSTINC0, ACCESS                 
  3381   1A68    0E02                      MOVLW 0x2                              
  3382   1A6A    6EED                      MOVWF POSTDEC0, ACCESS                 
  3383   1A6C    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  3384   1A6E    FFE9                      NOP                                    
  3385   1A70    C0B6                      MOVFF 0xb6, FSR0H                      
  3386   1A72    FFEA                      NOP                                    
  3387   1A74    52EE                      MOVF POSTINC0, F, ACCESS               
  3388   1A76    6AEF                      CLRF INDF0, ACCESS                     
  3389   1A78    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  3390   1A7A    FFE9                      NOP                                    
  3391   1A7C    C0B6                      MOVFF 0xb6, FSR0H                      
  3392   1A7E    FFEA                      NOP                                    
  3393   1A80    0E48                      MOVLW 0x48                             
  3394   1A82    6EEF                      MOVWF INDF0, ACCESS                    
  3395   1A84    6BAC                      CLRF cdc_Out_len, BANKED               
  3396   1A86    69AE                      SETF IsOutBufferA, BANKED              
  3397   1A88    0EC0                      MOVLW 0xc0                             
  3398   1A8A    6FB1                      MOVWF OutPtr, BANKED                   
  3399   1A8C    0E02                      MOVLW 0x2                              
  3400   1A8E    6FB2                      MOVWF 0xb2, BANKED                     
  3401   1A90    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3402   1A92    FFE9                      NOP                                    
  3403   1A94    C0B4                      MOVFF 0xb4, FSR0H                      
  3404   1A96    FFEA                      NOP                                    
  3405   1A98    52EE                      MOVF POSTINC0, F, ACCESS               
  3406   1A9A    0E20                      MOVLW 0x20                             
  3407   1A9C    6EEF                      MOVWF INDF0, ACCESS                    
  3408   1A9E    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3409   1AA0    FFE9                      NOP                                    
  3410   1AA2    C0B4                      MOVFF 0xb4, FSR0H                      
  3411   1AA4    FFEA                      NOP                                    
  3412   1AA6    0E02                      MOVLW 0x2                              
  3413   1AA8    26E9                      ADDWF FSR0L, F, ACCESS                 
  3414   1AAA    0E00                      MOVLW 0                                
  3415   1AAC    22EA                      ADDWFC FSR0H, F, ACCESS                
  3416   1AAE    0EC0                      MOVLW 0xc0                             
  3417   1AB0    6EEE                      MOVWF POSTINC0, ACCESS                 
  3418   1AB2    0E02                      MOVLW 0x2                              
  3419   1AB4    6EED                      MOVWF POSTDEC0, ACCESS                 
  3420   1AB6    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3421   1AB8    FFE9                      NOP                                    
  3422   1ABA    C0B4                      MOVFF 0xb4, FSR0H                      
  3423   1ABC    FFEA                      NOP                                    
  3424   1ABE    0E88                      MOVLW 0x88                             
  3425   1AC0    6EEF                      MOVWF INDF0, ACCESS                    
  3426   1AC2    0012                      RETURN 0                               
  3427   1AC4    CFD9 cdc_setup            MOVFF FSR2, POSTINC1                   
  3428   1AC6    FFE6                      NOP                                    
  3429   1AC8    CFE1                      MOVFF FSR1L, FSR2                      
  3430   1ACA    FFD9                      NOP                                    
  3431   1ACC    0E04                      MOVLW 0x4                              
  3432   1ACE    26E1                      ADDWF FSR1L, F, ACCESS                 
  3433   1AD0    C098                      MOVFF EP0_Outbdp, FSR0L                
  3434   1AD2    FFE9                      NOP                                    
  3435   1AD4    C099                      MOVFF 0x99, FSR0H                      
  3436   1AD6    FFEA                      NOP                                    
  3437   1AD8    0E02                      MOVLW 0x2                              
  3438   1ADA    26E9                      ADDWF FSR0L, F, ACCESS                 
  3439   1ADC    0E00                      MOVLW 0                                
  3440   1ADE    22EA                      ADDWFC FSR0H, F, ACCESS                
  3441   1AE0    CFEE                      MOVFF POSTINC0, POSTINC2               
  3442   1AE2    FFDE                      NOP                                    
  3443   1AE4    CFED                      MOVFF POSTDEC0, POSTDEC2               
  3444   1AE6    FFDD                      NOP                                    
  3445   1AE8    CFDE                      MOVFF POSTINC2, FSR0L                  
  3446   1AEA    FFE9                      NOP                                    
  3447   1AEC    CFDD                      MOVFF POSTDEC2, FSR0H                  
  3448   1AEE    FFEA                      NOP                                    
  3449   1AF0    50EF                      MOVF INDF0, W, ACCESS                  
  3450   1AF2    0B63                      ANDLW 0x63                             
  3451   1AF4    0A21                      XORLW 0x21                             
  3452   1AF6    E001                      BZ 0x1afa                              
  3453   1AF8    D0BB                      BRA 0x1c70                             
  3454   1AFA    CFDE                      MOVFF POSTINC2, FSR0L                  
  3455   1AFC    FFE9                      NOP                                    
  3456   1AFE    CFDD                      MOVFF POSTDEC2, FSR0H                  
  3457   1B00    FFEA                      NOP                                    
  3458   1B02    0E01                      MOVLW 0x1                              
  3459   1B04    26E9                      ADDWF FSR0L, F, ACCESS                 
  3460   1B06    0E00                      MOVLW 0                                
  3461   1B08    22EA                      ADDWFC FSR0H, F, ACCESS                
  3462   1B0A    50EF                      MOVF INDF0, W, ACCESS                  
  3463   1B0C    0A23                      XORLW 0x23                             
  3464   1B0E    E101                      BNZ 0x1b12                             
  3465   1B10    D0AC                      BRA 0x1c6a                             
  3466   1B12    0A01                      XORLW 0x1                              
  3467   1B14    E101                      BNZ 0x1b18                             
  3468   1B16    D085                      BRA 0x1c22                             
  3469   1B18    0A03                      XORLW 0x3                              
  3470   1B1A    E02E                      BZ 0x1b78                              
  3471   1B1C    0A01                      XORLW 0x1                              
  3472   1B1E    E01E                      BZ 0x1b5c                              
  3473   1B20    0A22                      XORLW 0x22                             
  3474   1B22    E019                      BZ 0x1b56                              
  3475   1B24    0A01                      XORLW 0x1                              
  3476   1B26    E017                      BZ 0x1b56                              
  3477   1B28    0A07                      XORLW 0x7                              
  3478   1B2A    E015                      BZ 0x1b56                              
  3479   1B2C    0A05                      XORLW 0x5                              
  3480   1B2E    E00B                      BZ 0x1b46                              
  3481   1B30    0A01                      XORLW 0x1                              
  3482   1B32    E001                      BZ 0x1b36                              
  3483   1B34    D09A                      BRA 0x1c6a                             
  3484   1B36    0E00                      MOVLW 0                                
  3485   1B38    6EE6                      MOVWF POSTINC1, ACCESS                 
  3486   1B3A    6AE6                      CLRF POSTINC1, ACCESS                  
  3487   1B3C    ECE5                      CALL usb_ack_dat1, 0                   
  3488   1B3E    F00B                      NOP                                    
  3489   1B40    52E5                      MOVF POSTDEC1, F, ACCESS               
  3490   1B42    52E5                      MOVF POSTDEC1, F, ACCESS               
  3491   1B44    D094                      BRA 0x1c6e                             
  3492   1B46    0E00                      MOVLW 0                                
  3493   1B48    6EE6                      MOVWF POSTINC1, ACCESS                 
  3494   1B4A    6AE6                      CLRF POSTINC1, ACCESS                  
  3495   1B4C    ECE5                      CALL usb_ack_dat1, 0                   
  3496   1B4E    F00B                      NOP                                    
  3497   1B50    52E5                      MOVF POSTDEC1, F, ACCESS               
  3498   1B52    52E5                      MOVF POSTDEC1, F, ACCESS               
  3499   1B54    D08C                      BRA 0x1c6e                             
  3500   1B56    EC05                      CALL usb_RequestError, 0               
  3501   1B58    F00C                      NOP                                    
  3502   1B5A    D089                      BRA 0x1c6e                             
  3503   1B5C    0EA0                      MOVLW 0xa0                             
  3504   1B5E    6EE6                      MOVWF POSTINC1, ACCESS                 
  3505   1B60    0E1C                      MOVLW 0x1c                             
  3506   1B62    6EE6                      MOVWF POSTINC1, ACCESS                 
  3507   1B64    0E00                      MOVLW 0                                
  3508   1B66    6EE6                      MOVWF POSTINC1, ACCESS                 
  3509   1B68    6AE6                      CLRF POSTINC1, ACCESS                  
  3510   1B6A    ECC3                      CALL usb_set_out_handler, 0            
  3511   1B6C    F00B                      NOP                                    
  3512   1B6E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3513   1B70    52E5                      MOVF POSTDEC1, F, ACCESS               
  3514   1B72    52E5                      MOVF POSTDEC1, F, ACCESS               
  3515   1B74    52E5                      MOVF POSTDEC1, F, ACCESS               
  3516   1B76    D07B                      BRA 0x1c6e                             
  3517   1B78    CFDE                      MOVFF POSTINC2, FSR0L                  
  3518   1B7A    FFE9                      NOP                                    
  3519   1B7C    CFDD                      MOVFF POSTDEC2, FSR0H                  
  3520   1B7E    FFEA                      NOP                                    
  3521   1B80    0E06                      MOVLW 0x6                              
  3522   1B82    26E9                      ADDWF FSR0L, F, ACCESS                 
  3523   1B84    0E00                      MOVLW 0                                
  3524   1B86    22EA                      ADDWFC FSR0H, F, ACCESS                
  3525   1B88    0E02                      MOVLW 0x2                              
  3526   1B8A    CFEE                      MOVFF POSTINC0, PLUSW2                 
  3527   1B8C    FFDB                      NOP                                    
  3528   1B8E    0E03                      MOVLW 0x3                              
  3529   1B90    CFED                      MOVFF POSTDEC0, PLUSW2                 
  3530   1B92    FFDB                      NOP                                    
  3531   1B94    0E02                      MOVLW 0x2                              
  3532   1B96    CFDB                      MOVFF PLUSW2, __tmp_0                  
  3533   1B98    F010                      NOP                                    
  3534   1B9A    0E03                      MOVLW 0x3                              
  3535   1B9C    CFDB                      MOVFF PLUSW2, 0x11                     
  3536   1B9E    F011                      NOP                                    
  3537   1BA0    0E07                      MOVLW 0x7                              
  3538   1BA2    80D8                      BSF STATUS, 0, ACCESS                  
  3539   1BA4    5410                      SUBFWB __tmp_0, W, ACCESS              
  3540   1BA6    0E00                      MOVLW 0                                
  3541   1BA8    5411                      SUBFWB 0x11, W, ACCESS                 
  3542   1BAA    E207                      BC 0x1bba                              
  3543   1BAC    0E07                      MOVLW 0x7                              
  3544   1BAE    6EF3                      MOVWF PRODL, ACCESS                    
  3545   1BB0    0E02                      MOVLW 0x2                              
  3546   1BB2    CFF3                      MOVFF PRODL, PLUSW2                    
  3547   1BB4    FFDB                      NOP                                    
  3548   1BB6    0E03                      MOVLW 0x3                              
  3549   1BB8    6ADB                      CLRF PLUSW2, ACCESS                    
  3550   1BBA    0E02                      MOVLW 0x2                              
  3551   1BBC    CFDB                      MOVFF PLUSW2, POSTINC1                 
  3552   1BBE    FFE6                      NOP                                    
  3553   1BC0    0E03                      MOVLW 0x3                              
  3554   1BC2    CFDB                      MOVFF PLUSW2, POSTINC1                 
  3555   1BC4    FFE6                      NOP                                    
  3556   1BC6    0EA2                      MOVLW 0xa2                             
  3557   1BC8    6EE6                      MOVWF POSTINC1, ACCESS                 
  3558   1BCA    0E00                      MOVLW 0                                
  3559   1BCC    6EE6                      MOVWF POSTINC1, ACCESS                 
  3560   1BCE    C09A                      MOVFF EP0_Inbdp, FSR0L                 
  3561   1BD0    FFE9                      NOP                                    
  3562   1BD2    C09B                      MOVFF 0x9b, FSR0H                      
  3563   1BD4    FFEA                      NOP                                    
  3564   1BD6    0E02                      MOVLW 0x2                              
  3565   1BD8    26E9                      ADDWF FSR0L, F, ACCESS                 
  3566   1BDA    0E00                      MOVLW 0                                
  3567   1BDC    22EA                      ADDWFC FSR0H, F, ACCESS                
  3568   1BDE    CFEE                      MOVFF POSTINC0, POSTINC1               
  3569   1BE0    FFE6                      NOP                                    
  3570   1BE2    CFEF                      MOVFF INDF0, POSTINC1                  
  3571   1BE4    FFE6                      NOP                                    
  3572   1BE6    EC5F                      CALL memcpy, 0                         
  3573   1BE8    F001                      NOP                                    
  3574   1BEA    6E10                      MOVWF __tmp_0, ACCESS                  
  3575   1BEC    0E06                      MOVLW 0x6                              
  3576   1BEE    5EE1                      SUBWF FSR1L, F, ACCESS                 
  3577   1BF0    5010                      MOVF __tmp_0, W, ACCESS                
  3578   1BF2    0E02                      MOVLW 0x2                              
  3579   1BF4    CFDB                      MOVFF PLUSW2, POSTINC1                 
  3580   1BF6    FFE6                      NOP                                    
  3581   1BF8    0E03                      MOVLW 0x3                              
  3582   1BFA    CFDB                      MOVFF PLUSW2, POSTINC1                 
  3583   1BFC    FFE6                      NOP                                    
  3584   1BFE    ECE5                      CALL usb_ack_dat1, 0                   
  3585   1C00    F00B                      NOP                                    
  3586   1C02    52E5                      MOVF POSTDEC1, F, ACCESS               
  3587   1C04    52E5                      MOVF POSTDEC1, F, ACCESS               
  3588   1C06    0E88                      MOVLW 0x88                             
  3589   1C08    6EE6                      MOVWF POSTINC1, ACCESS                 
  3590   1C0A    0E1C                      MOVLW 0x1c                             
  3591   1C0C    6EE6                      MOVWF POSTINC1, ACCESS                 
  3592   1C0E    0E00                      MOVLW 0                                
  3593   1C10    6EE6                      MOVWF POSTINC1, ACCESS                 
  3594   1C12    6AE6                      CLRF POSTINC1, ACCESS                  
  3595   1C14    ECA5                      CALL usb_set_in_handler, 0             
  3596   1C16    F00B                      NOP                                    
  3597   1C18    52E5                      MOVF POSTDEC1, F, ACCESS               
  3598   1C1A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3599   1C1C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3600   1C1E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3601   1C20    D026                      BRA 0x1c6e                             
  3602   1C22    CFDE                      MOVFF POSTINC2, FSR0L                  
  3603   1C24    FFE9                      NOP                                    
  3604   1C26    CFDD                      MOVFF POSTDEC2, FSR0H                  
  3605   1C28    FFEA                      NOP                                    
  3606   1C2A    0E02                      MOVLW 0x2                              
  3607   1C2C    26E9                      ADDWF FSR0L, F, ACCESS                 
  3608   1C2E    0E00                      MOVLW 0                                
  3609   1C30    22EA                      ADDWFC FSR0H, F, ACCESS                
  3610   1C32    CFEE                      MOVFF POSTINC0, cls                    
  3611   1C34    F0A9                      NOP                                    
  3612   1C36    CFED                      MOVFF POSTDEC0, 0xaa                   
  3613   1C38    F0AA                      NOP                                    
  3614   1C3A    0E78                      MOVLW 0x78                             
  3615   1C3C    6EE6                      MOVWF POSTINC1, ACCESS                 
  3616   1C3E    0E1E                      MOVLW 0x1e                             
  3617   1C40    6EE6                      MOVWF POSTINC1, ACCESS                 
  3618   1C42    0E00                      MOVLW 0                                
  3619   1C44    6EE6                      MOVWF POSTINC1, ACCESS                 
  3620   1C46    6AE6                      CLRF POSTINC1, ACCESS                  
  3621   1C48    ECA5                      CALL usb_set_in_handler, 0             
  3622   1C4A    F00B                      NOP                                    
  3623   1C4C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3624   1C4E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3625   1C50    52E5                      MOVF POSTDEC1, F, ACCESS               
  3626   1C52    52E5                      MOVF POSTDEC1, F, ACCESS               
  3627   1C54    0E00                      MOVLW 0                                
  3628   1C56    6EE6                      MOVWF POSTINC1, ACCESS                 
  3629   1C58    6AE6                      CLRF POSTINC1, ACCESS                  
  3630   1C5A    ECE5                      CALL usb_ack_dat1, 0                   
  3631   1C5C    F00B                      NOP                                    
  3632   1C5E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3633   1C60    52E5                      MOVF POSTDEC1, F, ACCESS               
  3634   1C62    0100                      MOVLB 0                                
  3635   1C64    0E01                      MOVLW 0x1                              
  3636   1C66    6FC8                      MOVWF LineStateUpdated, BANKED         
  3637   1C68    D002                      BRA 0x1c6e                             
  3638   1C6A    EC05                      CALL usb_RequestError, 0               
  3639   1C6C    F00C                      NOP                                    
  3640   1C6E    D002                      BRA 0x1c74                             
  3641   1C70    EC05                      CALL usb_RequestError, 0               
  3642   1C72    F00C                      NOP                                    
  3643   1C74    0E04                      MOVLW 0x4                              
  3644   1C76    5CE1                      SUBWF FSR1L, W, ACCESS                 
  3645   1C78    E202                      BC 0x1c7e                              
  3646   1C7A    6AE1                      CLRF FSR1L, ACCESS                     
  3647   1C7C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3648   1C7E    6EE1                      MOVWF FSR1L, ACCESS                    
  3649   1C80    52E5                      MOVF POSTDEC1, F, ACCESS               
  3650   1C82    CFE7                      MOVFF INDF1, FSR2                      
  3651   1C84    FFD9                      NOP                                    
  3652   1C86    0012                      RETURN 0                               
  3653   1C88    0E00 cdc_get_line_coding  MOVLW 0                                
  3654   1C8A    6EE6                      MOVWF POSTINC1, ACCESS                 
  3655   1C8C    6AE6                      CLRF POSTINC1, ACCESS                  
  3656   1C8E    6EE6                      MOVWF POSTINC1, ACCESS                 
  3657   1C90    6AE6                      CLRF POSTINC1, ACCESS                  
  3658   1C92    ECA5                      CALL usb_set_in_handler, 0             
  3659   1C94    F00B                      NOP                                    
  3660   1C96    52E5                      MOVF POSTDEC1, F, ACCESS               
  3661   1C98    52E5                      MOVF POSTDEC1, F, ACCESS               
  3662   1C9A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3663   1C9C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3664   1C9E    0012                      RETURN 0                               
  3665   1CA0    CFD9 cdc_set_line_coding_data MOVFF FSR2, POSTINC1                   
  3666   1CA2    FFE6                      NOP                                    
  3667   1CA4    CFE1                      MOVFF FSR1L, FSR2                      
  3668   1CA6    FFD9                      NOP                                    
  3669   1CA8    0E08                      MOVLW 0x8                              
  3670   1CAA    26E1                      ADDWF FSR1L, F, ACCESS                 
  3671   1CAC    0E07                      MOVLW 0x7                              
  3672   1CAE    6EE6                      MOVWF POSTINC1, ACCESS                 
  3673   1CB0    6AE6                      CLRF POSTINC1, ACCESS                  
  3674   1CB2    C098                      MOVFF EP0_Outbdp, FSR0L                
  3675   1CB4    FFE9                      NOP                                    
  3676   1CB6    C099                      MOVFF 0x99, FSR0H                      
  3677   1CB8    FFEA                      NOP                                    
  3678   1CBA    0E02                      MOVLW 0x2                              
  3679   1CBC    26E9                      ADDWF FSR0L, F, ACCESS                 
  3680   1CBE    0E00                      MOVLW 0                                
  3681   1CC0    22EA                      ADDWFC FSR0H, F, ACCESS                
  3682   1CC2    CFEE                      MOVFF POSTINC0, POSTINC1               
  3683   1CC4    FFE6                      NOP                                    
  3684   1CC6    CFEF                      MOVFF INDF0, POSTINC1                  
  3685   1CC8    FFE6                      NOP                                    
  3686   1CCA    0EA2                      MOVLW 0xa2                             
  3687   1CCC    6EE6                      MOVWF POSTINC1, ACCESS                 
  3688   1CCE    0E00                      MOVLW 0                                
  3689   1CD0    6EE6                      MOVWF POSTINC1, ACCESS                 
  3690   1CD2    EC5F                      CALL memcpy, 0                         
  3691   1CD4    F001                      NOP                                    
  3692   1CD6    6E10                      MOVWF __tmp_0, ACCESS                  
  3693   1CD8    0E06                      MOVLW 0x6                              
  3694   1CDA    5EE1                      SUBWF FSR1L, F, ACCESS                 
  3695   1CDC    5010                      MOVF __tmp_0, W, ACCESS                
  3696   1CDE    6A10                      CLRF __tmp_0, ACCESS                   
  3697   1CE0    0E1B                      MOVLW 0x1b                             
  3698   1CE2    6E11                      MOVWF 0x11, ACCESS                     
  3699   1CE4    0EB7                      MOVLW 0xb7                             
  3700   1CE6    6E12                      MOVWF 0x12, ACCESS                     
  3701   1CE8    6A13                      CLRF 0x13, ACCESS                      
  3702   1CEA    C010                      MOVFF __tmp_0, dwBaudrem               
  3703   1CEC    F004                      NOP                                    
  3704   1CEE    C011                      MOVFF 0x11, 0x5                        
  3705   1CF0    F005                      NOP                                    
  3706   1CF2    C012                      MOVFF 0x12, pUEP                       
  3707   1CF4    F006                      NOP                                    
  3708   1CF6    C013                      MOVFF 0x13, 0x7                        
  3709   1CF8    F007                      NOP                                    
  3710   1CFA    C0A2                      MOVFF linecodeing, 0x9                 
  3711   1CFC    F009                      NOP                                    
  3712   1CFE    C0A3                      MOVFF 0xa3, 0xa                        
  3713   1D00    F00A                      NOP                                    
  3714   1D02    C0A4                      MOVFF 0xa4, 0xb                        
  3715   1D04    F00B                      NOP                                    
  3716   1D06    C0A5                      MOVFF 0xa5, 0xc                        
  3717   1D08    F00C                      NOP                                    
  3718   1D0A    EC8A                      CALL FXD3232U, 0                       
  3719   1D0C    F001                      NOP                                    
  3720   1D0E    C004                      MOVFF dwBaudrem, POSTINC2              
  3721   1D10    FFDE                      NOP                                    
  3722   1D12    C005                      MOVFF 0x5, POSTINC2                    
  3723   1D14    FFDE                      NOP                                    
  3724   1D16    C006                      MOVFF pUEP, POSTINC2                   
  3725   1D18    FFDE                      NOP                                    
  3726   1D1A    C007                      MOVFF 0x7, POSTDEC2                    
  3727   1D1C    FFDD                      NOP                                    
  3728   1D1E    52DD                      MOVF POSTDEC2, F, ACCESS               
  3729   1D20    52DD                      MOVF POSTDEC2, F, ACCESS               
  3730   1D22    C0A2                      MOVFF linecodeing, 0x9                 
  3731   1D24    F009                      NOP                                    
  3732   1D26    C0A3                      MOVFF 0xa3, 0xa                        
  3733   1D28    F00A                      NOP                                    
  3734   1D2A    C0A4                      MOVFF 0xa4, 0xb                        
  3735   1D2C    F00B                      NOP                                    
  3736   1D2E    C0A5                      MOVFF 0xa5, 0xc                        
  3737   1D30    F00C                      NOP                                    
  3738   1D32    6A04                      CLRF dwBaudrem, ACCESS                 
  3739   1D34    0E1B                      MOVLW 0x1b                             
  3740   1D36    6E05                      MOVWF 0x5, ACCESS                      
  3741   1D38    0EB7                      MOVLW 0xb7                             
  3742   1D3A    6E06                      MOVWF pUEP, ACCESS                     
  3743   1D3C    6A07                      CLRF 0x7, ACCESS                       
  3744   1D3E    EC8A                      CALL FXD3232U, 0                       
  3745   1D40    F001                      NOP                                    
  3746   1D42    0E04                      MOVLW 0x4                              
  3747   1D44    C000                      MOVFF RecvdByte, PLUSW2                
  3748   1D46    FFDB                      NOP                                    
  3749   1D48    0E05                      MOVLW 0x5                              
  3750   1D4A    C001                      MOVFF 0x1, PLUSW2                      
  3751   1D4C    FFDB                      NOP                                    
  3752   1D4E    0E06                      MOVLW 0x6                              
  3753   1D50    C002                      MOVFF reply_len, PLUSW2                
  3754   1D52    FFDB                      NOP                                    
  3755   1D54    0E07                      MOVLW 0x7                              
  3756   1D56    C003                      MOVFF dir, PLUSW2                      
  3757   1D58    FFDB                      NOP                                    
  3758   1D5A    0E04                      MOVLW 0x4                              
  3759   1D5C    CFDB                      MOVFF PLUSW2, __tmp_0                  
  3760   1D5E    F010                      NOP                                    
  3761   1D60    0E05                      MOVLW 0x5                              
  3762   1D62    CFDB                      MOVFF PLUSW2, 0x11                     
  3763   1D64    F011                      NOP                                    
  3764   1D66    0E06                      MOVLW 0x6                              
  3765   1D68    CFDB                      MOVFF PLUSW2, 0x12                     
  3766   1D6A    F012                      NOP                                    
  3767   1D6C    0E07                      MOVLW 0x7                              
  3768   1D6E    CFDB                      MOVFF PLUSW2, 0x13                     
  3769   1D70    F013                      NOP                                    
  3770   1D72    0E01                      MOVLW 0x1                              
  3771   1D74    0B1F                      ANDLW 0x1f                             
  3772   1D76    E007                      BZ 0x1d86                              
  3773   1D78    90D8                      BCF STATUS, 0, ACCESS                  
  3774   1D7A    3610                      RLCF __tmp_0, F, ACCESS                
  3775   1D7C    3611                      RLCF 0x11, F, ACCESS                   
  3776   1D7E    3612                      RLCF 0x12, F, ACCESS                   
  3777   1D80    3613                      RLCF 0x13, F, ACCESS                   
  3778   1D82    06E8                      DECF WREG, F, ACCESS                   
  3779   1D84    E1F9                      BNZ 0x1d78                             
  3780   1D86    0100                      MOVLB 0                                
  3781   1D88    51A2                      MOVF linecodeing, W, BANKED            
  3782   1D8A    5C10                      SUBWF __tmp_0, W, ACCESS               
  3783   1D8C    51A3                      MOVF 0xa3, W, BANKED                   
  3784   1D8E    5811                      SUBWFB 0x11, W, ACCESS                 
  3785   1D90    51A4                      MOVF 0xa4, W, BANKED                   
  3786   1D92    5812                      SUBWFB 0x12, W, ACCESS                 
  3787   1D94    51A5                      MOVF 0xa5, W, BANKED                   
  3788   1D96    5813                      SUBWFB 0x13, W, ACCESS                 
  3789   1D98    E209                      BC 0x1dac                              
  3790   1D9A    CFD9                      MOVFF FSR2, FSR0L                      
  3791   1D9C    FFE9                      NOP                                    
  3792   1D9E    CFDA                      MOVFF FSR2H, FSR0H                     
  3793   1DA0    FFEA                      NOP                                    
  3794   1DA2    06EE                      DECF POSTINC0, F, ACCESS               
  3795   1DA4    0E00                      MOVLW 0                                
  3796   1DA6    5AEE                      SUBWFB POSTINC0, F, ACCESS             
  3797   1DA8    5AEE                      SUBWFB POSTINC0, F, ACCESS             
  3798   1DAA    5AEE                      SUBWFB POSTINC0, F, ACCESS             
  3799   1DAC    CFD9                      MOVFF FSR2, FSR0L                      
  3800   1DAE    FFE9                      NOP                                    
  3801   1DB0    CFDA                      MOVFF FSR2H, FSR0H                     
  3802   1DB2    FFEA                      NOP                                    
  3803   1DB4    CFEE                      MOVFF POSTINC0, __tmp_0                
  3804   1DB6    F010                      NOP                                    
  3805   1DB8    CFEE                      MOVFF POSTINC0, 0x11                   
  3806   1DBA    F011                      NOP                                    
  3807   1DBC    CFEE                      MOVFF POSTINC0, 0x12                   
  3808   1DBE    F012                      NOP                                    
  3809   1DC0    CFEF                      MOVFF INDF0, 0x13                      
  3810   1DC2    F013                      NOP                                    
  3811   1DC4    5010                      MOVF __tmp_0, W, ACCESS                
  3812   1DC6    6EAF                      MOVWF SPBRG, ACCESS                    
  3813   1DC8    CFD9                      MOVFF FSR2, FSR0L                      
  3814   1DCA    FFE9                      NOP                                    
  3815   1DCC    CFDA                      MOVFF FSR2H, FSR0H                     
  3816   1DCE    FFEA                      NOP                                    
  3817   1DD0    CFEE                      MOVFF POSTINC0, __tmp_0                
  3818   1DD2    F010                      NOP                                    
  3819   1DD4    CFEE                      MOVFF POSTINC0, 0x11                   
  3820   1DD6    F011                      NOP                                    
  3821   1DD8    CFEE                      MOVFF POSTINC0, 0x12                   
  3822   1DDA    F012                      NOP                                    
  3823   1DDC    CFEF                      MOVFF INDF0, 0x13                      
  3824   1DDE    F013                      NOP                                    
  3825   1DE0    0E08                      MOVLW 0x8                              
  3826   1DE2    90D8                      BCF STATUS, 0, ACCESS                  
  3827   1DE4    3213                      RRCF 0x13, F, ACCESS                   
  3828   1DE6    3212                      RRCF 0x12, F, ACCESS                   
  3829   1DE8    3211                      RRCF 0x11, F, ACCESS                   
  3830   1DEA    3210                      RRCF __tmp_0, F, ACCESS                
  3831   1DEC    06E8                      DECF WREG, F, ACCESS                   
  3832   1DEE    E1F9                      BNZ 0x1de2                             
  3833   1DF0    5010                      MOVF __tmp_0, W, ACCESS                
  3834   1DF2    6EB0                      MOVWF SPBRGH, ACCESS                   
  3835   1DF4    0E00                      MOVLW 0                                
  3836   1DF6    6EE6                      MOVWF POSTINC1, ACCESS                 
  3837   1DF8    6AE6                      CLRF POSTINC1, ACCESS                  
  3838   1DFA    6EE6                      MOVWF POSTINC1, ACCESS                 
  3839   1DFC    6AE6                      CLRF POSTINC1, ACCESS                  
  3840   1DFE    ECC3                      CALL usb_set_out_handler, 0            
  3841   1E00    F00B                      NOP                                    
  3842   1E02    52E5                      MOVF POSTDEC1, F, ACCESS               
  3843   1E04    52E5                      MOVF POSTDEC1, F, ACCESS               
  3844   1E06    52E5                      MOVF POSTDEC1, F, ACCESS               
  3845   1E08    52E5                      MOVF POSTDEC1, F, ACCESS               
  3846   1E0A    0E60                      MOVLW 0x60                             
  3847   1E0C    6EE6                      MOVWF POSTINC1, ACCESS                 
  3848   1E0E    0E1E                      MOVLW 0x1e                             
  3849   1E10    6EE6                      MOVWF POSTINC1, ACCESS                 
  3850   1E12    0E00                      MOVLW 0                                
  3851   1E14    6EE6                      MOVWF POSTINC1, ACCESS                 
  3852   1E16    6AE6                      CLRF POSTINC1, ACCESS                  
  3853   1E18    ECA5                      CALL usb_set_in_handler, 0             
  3854   1E1A    F00B                      NOP                                    
  3855   1E1C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3856   1E1E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3857   1E20    52E5                      MOVF POSTDEC1, F, ACCESS               
  3858   1E22    52E5                      MOVF POSTDEC1, F, ACCESS               
  3859   1E24    0E00                      MOVLW 0                                
  3860   1E26    6EE6                      MOVWF POSTINC1, ACCESS                 
  3861   1E28    6AE6                      CLRF POSTINC1, ACCESS                  
  3862   1E2A    ECE5                      CALL usb_ack_dat1, 0                   
  3863   1E2C    F00B                      NOP                                    
  3864   1E2E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3865   1E30    52E5                      MOVF POSTDEC1, F, ACCESS               
  3866   1E32    C098                      MOVFF EP0_Outbdp, FSR0L                
  3867   1E34    FFE9                      NOP                                    
  3868   1E36    C099                      MOVFF 0x99, FSR0H                      
  3869   1E38    FFEA                      NOP                                    
  3870   1E3A    52EE                      MOVF POSTINC0, F, ACCESS               
  3871   1E3C    0E08                      MOVLW 0x8                              
  3872   1E3E    6EEF                      MOVWF INDF0, ACCESS                    
  3873   1E40    C098                      MOVFF EP0_Outbdp, FSR0L                
  3874   1E42    FFE9                      NOP                                    
  3875   1E44    C099                      MOVFF 0x99, FSR0H                      
  3876   1E46    FFEA                      NOP                                    
  3877   1E48    0E88                      MOVLW 0x88                             
  3878   1E4A    6EEF                      MOVWF INDF0, ACCESS                    
  3879   1E4C    0E08                      MOVLW 0x8                              
  3880   1E4E    5CE1                      SUBWF FSR1L, W, ACCESS                 
  3881   1E50    E202                      BC 0x1e56                              
  3882   1E52    6AE1                      CLRF FSR1L, ACCESS                     
  3883   1E54    52E5                      MOVF POSTDEC1, F, ACCESS               
  3884   1E56    6EE1                      MOVWF FSR1L, ACCESS                    
  3885   1E58    52E5                      MOVF POSTDEC1, F, ACCESS               
  3886   1E5A    CFE7                      MOVFF INDF1, FSR2                      
  3887   1E5C    FFD9                      NOP                                    
  3888   1E5E    0012                      RETURN 0                               
  3889   1E60    0E00 cdc_set_line_coding_status MOVLW 0                                
  3890   1E62    6EE6                      MOVWF POSTINC1, ACCESS                 
  3891   1E64    6AE6                      CLRF POSTINC1, ACCESS                  
  3892   1E66    6EE6                      MOVWF POSTINC1, ACCESS                 
  3893   1E68    6AE6                      CLRF POSTINC1, ACCESS                  
  3894   1E6A    ECA5                      CALL usb_set_in_handler, 0             
  3895   1E6C    F00B                      NOP                                    
  3896   1E6E    52E5                      MOVF POSTDEC1, F, ACCESS               
  3897   1E70    52E5                      MOVF POSTDEC1, F, ACCESS               
  3898   1E72    52E5                      MOVF POSTDEC1, F, ACCESS               
  3899   1E74    52E5                      MOVF POSTDEC1, F, ACCESS               
  3900   1E76    0012                      RETURN 0                               
  3901   1E78    0E00 cdc_set_control_line_state_status MOVLW 0                                
  3902   1E7A    6EE6                      MOVWF POSTINC1, ACCESS                 
  3903   1E7C    6AE6                      CLRF POSTINC1, ACCESS                  
  3904   1E7E    6EE6                      MOVWF POSTINC1, ACCESS                 
  3905   1E80    6AE6                      CLRF POSTINC1, ACCESS                  
  3906   1E82    ECA5                      CALL usb_set_in_handler, 0             
  3907   1E84    F00B                      NOP                                    
  3908   1E86    52E5                      MOVF POSTDEC1, F, ACCESS               
  3909   1E88    52E5                      MOVF POSTDEC1, F, ACCESS               
  3910   1E8A    52E5                      MOVF POSTDEC1, F, ACCESS               
  3911   1E8C    52E5                      MOVF POSTDEC1, F, ACCESS               
  3912   1E8E    0012                      RETURN 0                               
  3913   1E90    C0B3 WaitOutReady         MOVFF CDC_Outbdp, FSR0L                
  3914   1E92    FFE9                      NOP                                    
  3915   1E94    C0B4                      MOVFF 0xb4, FSR0H                      
  3916   1E96    FFEA                      NOP                                    
  3917   1E98    50EF                      MOVF INDF0, W, ACCESS                  
  3918   1E9A    0B80                      ANDLW 0x80                             
  3919   1E9C    E001                      BZ 0x1ea0                              
  3920   1E9E    D7F8                      BRA WaitOutReady                       
  3921   1EA0    0012                      RETURN 0                               
  3922   1EA2    C0B5 WaitInReady          MOVFF CDC_Inbdp, FSR0L                 
  3923   1EA4    FFE9                      NOP                                    
  3924   1EA6    C0B6                      MOVFF 0xb6, FSR0H                      
  3925   1EA8    FFEA                      NOP                                    
  3926   1EAA    50EF                      MOVF INDF0, W, ACCESS                  
  3927   1EAC    0B80                      ANDLW 0x80                             
  3928   1EAE    E001                      BZ 0x1eb2                              
  3929   1EB0    D7F8                      BRA WaitInReady                        
  3930   1EB2    0012                      RETURN 0                               
  3931   1EB4    C0B3 getOutReady          MOVFF CDC_Outbdp, FSR0L                
  3932   1EB6    FFE9                      NOP                                    
  3933   1EB8    C0B4                      MOVFF 0xb4, FSR0H                      
  3934   1EBA    FFEA                      NOP                                    
  3935   1EBC    50EF                      MOVF INDF0, W, ACCESS                  
  3936   1EBE    0B80                      ANDLW 0x80                             
  3937   1EC0    E002                      BZ 0x1ec6                              
  3938   1EC2    0E00                      MOVLW 0                                
  3939   1EC4    D001                      BRA 0x1ec8                             
  3940   1EC6    0E01                      MOVLW 0x1                              
  3941   1EC8    D000                      BRA 0x1eca                             
  3942   1ECA    0012                      RETURN 0                               
  3943   1ECC    C0B5 getInReady           MOVFF CDC_Inbdp, FSR0L                 
  3944   1ECE    FFE9                      NOP                                    
  3945   1ED0    C0B6                      MOVFF 0xb6, FSR0H                      
  3946   1ED2    FFEA                      NOP                                    
  3947   1ED4    50EF                      MOVF INDF0, W, ACCESS                  
  3948   1ED6    0B80                      ANDLW 0x80                             
  3949   1ED8    E002                      BZ 0x1ede                              
  3950   1EDA    0E00                      MOVLW 0                                
  3951   1EDC    D001                      BRA 0x1ee0                             
  3952   1EDE    0E01                      MOVLW 0x1                              
  3953   1EE0    D000                      BRA 0x1ee2                             
  3954   1EE2    0012                      RETURN 0                               
  3955   1EE4    0100 getda_cdc            MOVLB 0                                
  3956   1EE6    6BB7                      CLRF CDCFunctionError, BANKED          
  3957   1EE8    DFD3                      RCALL WaitOutReady                     
  3958   1EEA    0100                      MOVLB 0                                
  3959   1EEC    A1AE                      BTFSS IsOutBufferA, 0, BANKED          
  3960   1EEE    D011                      BRA 0x1f12                             
  3961   1EF0    0EC0                      MOVLW 0xc0                             
  3962   1EF2    6FB1                      MOVWF OutPtr, BANKED                   
  3963   1EF4    0E02                      MOVLW 0x2                              
  3964   1EF6    6FB2                      MOVWF 0xb2, BANKED                     
  3965   1EF8    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3966   1EFA    FFE9                      NOP                                    
  3967   1EFC    C0B4                      MOVFF 0xb4, FSR0H                      
  3968   1EFE    FFEA                      NOP                                    
  3969   1F00    0E02                      MOVLW 0x2                              
  3970   1F02    26E9                      ADDWF FSR0L, F, ACCESS                 
  3971   1F04    0E00                      MOVLW 0                                
  3972   1F06    22EA                      ADDWFC FSR0H, F, ACCESS                
  3973   1F08    0EE0                      MOVLW 0xe0                             
  3974   1F0A    6EEE                      MOVWF POSTINC0, ACCESS                 
  3975   1F0C    0E02                      MOVLW 0x2                              
  3976   1F0E    6EED                      MOVWF POSTDEC0, ACCESS                 
  3977   1F10    D010                      BRA 0x1f32                             
  3978   1F12    0EE0                      MOVLW 0xe0                             
  3979   1F14    6FB1                      MOVWF OutPtr, BANKED                   
  3980   1F16    0E02                      MOVLW 0x2                              
  3981   1F18    6FB2                      MOVWF 0xb2, BANKED                     
  3982   1F1A    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3983   1F1C    FFE9                      NOP                                    
  3984   1F1E    C0B4                      MOVFF 0xb4, FSR0H                      
  3985   1F20    FFEA                      NOP                                    
  3986   1F22    0E02                      MOVLW 0x2                              
  3987   1F24    26E9                      ADDWF FSR0L, F, ACCESS                 
  3988   1F26    0E00                      MOVLW 0                                
  3989   1F28    22EA                      ADDWFC FSR0H, F, ACCESS                
  3990   1F2A    0EC0                      MOVLW 0xc0                             
  3991   1F2C    6EEE                      MOVWF POSTINC0, ACCESS                 
  3992   1F2E    0E02                      MOVLW 0x2                              
  3993   1F30    6EED                      MOVWF POSTDEC0, ACCESS                 
  3994   1F32    1FAE                      COMF IsOutBufferA, F, BANKED           
  3995   1F34    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  3996   1F36    FFE9                      NOP                                    
  3997   1F38    C0B4                      MOVFF 0xb4, FSR0H                      
  3998   1F3A    FFEA                      NOP                                    
  3999   1F3C    52EE                      MOVF POSTINC0, F, ACCESS               
  4000   1F3E    CFEF                      MOVFF INDF0, cdc_Out_len               
  4001   1F40    F0AC                      NOP                                    
  4002   1F42    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  4003   1F44    FFE9                      NOP                                    
  4004   1F46    C0B4                      MOVFF 0xb4, FSR0H                      
  4005   1F48    FFEA                      NOP                                    
  4006   1F4A    52EE                      MOVF POSTINC0, F, ACCESS               
  4007   1F4C    0E20                      MOVLW 0x20                             
  4008   1F4E    6EEF                      MOVWF INDF0, ACCESS                    
  4009   1F50    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  4010   1F52    FFE9                      NOP                                    
  4011   1F54    C0B4                      MOVFF 0xb4, FSR0H                      
  4012   1F56    FFEA                      NOP                                    
  4013   1F58    50EF                      MOVF INDF0, W, ACCESS                  
  4014   1F5A    0A40                      XORLW 0x40                             
  4015   1F5C    0B40                      ANDLW 0x40                             
  4016   1F5E    0980                      IORLW 0x80                             
  4017   1F60    0908                      IORLW 0x8                              
  4018   1F62    6EE6                      MOVWF POSTINC1, ACCESS                 
  4019   1F64    C0B3                      MOVFF CDC_Outbdp, FSR0L                
  4020   1F66    FFE9                      NOP                                    
  4021   1F68    C0B4                      MOVFF 0xb4, FSR0H                      
  4022   1F6A    FFEA                      NOP                                    
  4023   1F6C    52E5                      MOVF POSTDEC1, F, ACCESS               
  4024   1F6E    50E7                      MOVF INDF1, W, ACCESS                  
  4025   1F70    6EEF                      MOVWF INDF0, ACCESS                    
  4026   1F72    51AC                      MOVF cdc_Out_len, W, BANKED            
  4027   1F74    D000                      BRA 0x1f76                             
  4028   1F76    0012                      RETURN 0                               
  4029   1F78    CFD9 putda_cdc            MOVFF FSR2, POSTINC1                   
  4030   1F7A    FFE6                      NOP                                    
  4031   1F7C    CFE1                      MOVFF FSR1L, FSR2                      
  4032   1F7E    FFD9                      NOP                                    
  4033   1F80    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4034   1F82    FFE9                      NOP                                    
  4035   1F84    C0B6                      MOVFF 0xb6, FSR0H                      
  4036   1F86    FFEA                      NOP                                    
  4037   1F88    50EF                      MOVF INDF0, W, ACCESS                  
  4038   1F8A    0B80                      ANDLW 0x80                             
  4039   1F8C    E001                      BZ 0x1f90                              
  4040   1F8E    D7F8                      BRA 0x1f80                             
  4041   1F90    0100                      MOVLB 0                                
  4042   1F92    51AD                      MOVF IsInBufferA, W, BANKED            
  4043   1F94    E011                      BZ 0x1fb8                              
  4044   1F96    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4045   1F98    FFE9                      NOP                                    
  4046   1F9A    C0B6                      MOVFF 0xb6, FSR0H                      
  4047   1F9C    FFEA                      NOP                                    
  4048   1F9E    0E02                      MOVLW 0x2                              
  4049   1FA0    26E9                      ADDWF FSR0L, F, ACCESS                 
  4050   1FA2    0E00                      MOVLW 0                                
  4051   1FA4    22EA                      ADDWFC FSR0H, F, ACCESS                
  4052   1FA6    0E80                      MOVLW 0x80                             
  4053   1FA8    6EEE                      MOVWF POSTINC0, ACCESS                 
  4054   1FAA    0E02                      MOVLW 0x2                              
  4055   1FAC    6EED                      MOVWF POSTDEC0, ACCESS                 
  4056   1FAE    0EA0                      MOVLW 0xa0                             
  4057   1FB0    6FAF                      MOVWF InPtr, BANKED                    
  4058   1FB2    0E02                      MOVLW 0x2                              
  4059   1FB4    6FB0                      MOVWF 0xb0, BANKED                     
  4060   1FB6    D010                      BRA 0x1fd8                             
  4061   1FB8    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4062   1FBA    FFE9                      NOP                                    
  4063   1FBC    C0B6                      MOVFF 0xb6, FSR0H                      
  4064   1FBE    FFEA                      NOP                                    
  4065   1FC0    0E02                      MOVLW 0x2                              
  4066   1FC2    26E9                      ADDWF FSR0L, F, ACCESS                 
  4067   1FC4    0E00                      MOVLW 0                                
  4068   1FC6    22EA                      ADDWFC FSR0H, F, ACCESS                
  4069   1FC8    0EA0                      MOVLW 0xa0                             
  4070   1FCA    6EEE                      MOVWF POSTINC0, ACCESS                 
  4071   1FCC    0E02                      MOVLW 0x2                              
  4072   1FCE    6EED                      MOVWF POSTDEC0, ACCESS                 
  4073   1FD0    0E80                      MOVLW 0x80                             
  4074   1FD2    6FAF                      MOVWF InPtr, BANKED                    
  4075   1FD4    0E02                      MOVLW 0x2                              
  4076   1FD6    6FB0                      MOVWF 0xb0, BANKED                     
  4077   1FD8    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4078   1FDA    FFE9                      NOP                                    
  4079   1FDC    C0B6                      MOVFF 0xb6, FSR0H                      
  4080   1FDE    FFEA                      NOP                                    
  4081   1FE0    52EE                      MOVF POSTINC0, F, ACCESS               
  4082   1FE2    0EFE                      MOVLW 0xfe                             
  4083   1FE4    CFDB                      MOVFF PLUSW2, INDF0                    
  4084   1FE6    FFEF                      NOP                                    
  4085   1FE8    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4086   1FEA    FFE9                      NOP                                    
  4087   1FEC    C0B6                      MOVFF 0xb6, FSR0H                      
  4088   1FEE    FFEA                      NOP                                    
  4089   1FF0    50EF                      MOVF INDF0, W, ACCESS                  
  4090   1FF2    0A40                      XORLW 0x40                             
  4091   1FF4    0B40                      ANDLW 0x40                             
  4092   1FF6    0980                      IORLW 0x80                             
  4093   1FF8    0908                      IORLW 0x8                              
  4094   1FFA    6EE6                      MOVWF POSTINC1, ACCESS                 
  4095   1FFC    C0B5                      MOVFF CDC_Inbdp, FSR0L                 
  4096   1FFE    FFE9                      NOP                                    
  4097   2000    C0B6                      MOVFF 0xb6, FSR0H                      
  4098   2002    FFEA                      NOP                                    
  4099   2004    52E5                      MOVF POSTDEC1, F, ACCESS               
  4100   2006    50E7                      MOVF INDF1, W, ACCESS                  
  4101   2008    6EEF                      MOVWF INDF0, ACCESS                    
  4102   200A    1FAD                      COMF IsInBufferA, F, BANKED            
  4103   200C    0E00                      MOVLW 0                                
  4104   200E    D000                      BRA 0x2010                             
  4105   2010    52E5                      MOVF POSTDEC1, F, ACCESS               
  4106   2012    CFE7                      MOVFF INDF1, FSR2                      
  4107   2014    FFD9                      NOP                                    
  4108   2016    0012                      RETURN 0                               
  4109   2018    6AE6 SendZLP              CLRF POSTINC1, ACCESS                  
  4110   201A    DFAE                      RCALL putda_cdc                        
  4111   201C    52E5                      MOVF POSTDEC1, F, ACCESS               
  4112   201E    0012                      RETURN 0                               
  4113   2020    0100 CDC_Flush_In_Now     MOVLB 0                                
  4114   2022    51AB                      MOVF cdc_In_len, W, BANKED             
  4115   2024    0800                      SUBLW 0                                
  4116   2026    E216                      BC 0x2054                              
  4117   2028    DF51                      RCALL getInReady                       
  4118   202A    0900                      IORLW 0                                
  4119   202C    E101                      BNZ 0x2030                             
  4120   202E    D7FC                      BRA 0x2028                             
  4121   2030    C0AB                      MOVFF cdc_In_len, POSTINC1             
  4122   2032    FFE6                      NOP                                    
  4123   2034    DFA1                      RCALL putda_cdc                        
  4124   2036    52E5                      MOVF POSTDEC1, F, ACCESS               
  4125   2038    0E20                      MOVLW 0x20                             
  4126   203A    0100                      MOVLB 0                                
  4127   203C    5DAB                      SUBWF cdc_In_len, W, BANKED            
  4128   203E    E104                      BNZ 0x2048                             
  4129   2040    0100                      MOVLB 0                                
  4130   2042    0E01                      MOVLW 0x1                              
  4131   2044    6FCA                      MOVWF ZLPpending, BANKED               
  4132   2046    D002                      BRA 0x204c                             
  4133   2048    0100                      MOVLB 0                                
  4134   204A    6BCA                      CLRF ZLPpending, BANKED                
  4135   204C    0100                      MOVLB 0                                
  4136   204E    6BAB                      CLRF cdc_In_len, BANKED                
  4137   2050    0100                      MOVLB 0                                
  4138   2052    6BC9                      CLRF cdc_timeout_count, BANKED         
  4139   2054    0012                      RETURN 0                               
  4140   2056    0E04 CDCFlushOnTimeout    MOVLW 0x4                              
  4141   2058    0100                      MOVLB 0                                
  4142   205A    5DC9                      SUBWF cdc_timeout_count, W, BANKED     
  4143   205C    E327                      BNC 0x20ac                             
  4144   205E    0100                      MOVLB 0                                
  4145   2060    51AB                      MOVF cdc_In_len, W, BANKED             
  4146   2062    0800                      SUBLW 0                                
  4147   2064    E219                      BC 0x2098                              
  4148   2066    0100                      MOVLB 0                                
  4149   2068    51CB                      MOVF lock, W, BANKED                   
  4150   206A    E115                      BNZ 0x2096                             
  4151   206C    DF2F                      RCALL getInReady                       
  4152   206E    0900                      IORLW 0                                
  4153   2070    E012                      BZ 0x2096                              
  4154   2072    C0AB                      MOVFF cdc_In_len, POSTINC1             
  4155   2074    FFE6                      NOP                                    
  4156   2076    DF80                      RCALL putda_cdc                        
  4157   2078    52E5                      MOVF POSTDEC1, F, ACCESS               
  4158   207A    0E20                      MOVLW 0x20                             
  4159   207C    0100                      MOVLB 0                                
  4160   207E    5DAB                      SUBWF cdc_In_len, W, BANKED            
  4161   2080    E104                      BNZ 0x208a                             
  4162   2082    0100                      MOVLB 0                                
  4163   2084    0E01                      MOVLW 0x1                              
  4164   2086    6FCA                      MOVWF ZLPpending, BANKED               
  4165   2088    D002                      BRA 0x208e                             
  4166   208A    0100                      MOVLB 0                                
  4167   208C    6BCA                      CLRF ZLPpending, BANKED                
  4168   208E    0100                      MOVLB 0                                
  4169   2090    6BAB                      CLRF cdc_In_len, BANKED                
  4170   2092    0100                      MOVLB 0                                
  4171   2094    6BC9                      CLRF cdc_timeout_count, BANKED         
  4172   2096    D009                      BRA 0x20aa                             
  4173   2098    0100                      MOVLB 0                                
  4174   209A    51CA                      MOVF ZLPpending, W, BANKED             
  4175   209C    E006                      BZ 0x20aa                              
  4176   209E    6AE6                      CLRF POSTINC1, ACCESS                  
  4177   20A0    DF6B                      RCALL putda_cdc                        
  4178   20A2    52E5                      MOVF POSTDEC1, F, ACCESS               
  4179   20A4    0100                      MOVLB 0                                
  4180   20A6    6BCA                      CLRF ZLPpending, BANKED                
  4181   20A8    6BC9                      CLRF cdc_timeout_count, BANKED         
  4182   20AA    D001                      BRA 0x20ae                             
  4183   20AC    2BC9                      INCF cdc_timeout_count, F, BANKED      
  4184   20AE    0012                      RETURN 0                               
  4185   20B0    CFD9 putc_cdc             MOVFF FSR2, POSTINC1                   
  4186   20B2    FFE6                      NOP                                    
  4187   20B4    CFE1                      MOVFF FSR1L, FSR2                      
  4188   20B6    FFD9                      NOP                                    
  4189   20B8    0100                      MOVLB 0                                
  4190   20BA    0E01                      MOVLW 0x1                              
  4191   20BC    6FCB                      MOVWF lock, BANKED                     
  4192   20BE    0EFE                      MOVLW 0xfe                             
  4193   20C0    50DB                      MOVF PLUSW2, W, ACCESS                 
  4194   20C2    C0AF                      MOVFF InPtr, FSR0L                     
  4195   20C4    FFE9                      NOP                                    
  4196   20C6    C0B0                      MOVFF 0xb0, FSR0H                      
  4197   20C8    FFEA                      NOP                                    
  4198   20CA    6EEF                      MOVWF INDF0, ACCESS                    
  4199   20CC    0100                      MOVLB 0                                
  4200   20CE    2BAF                      INCF InPtr, F, BANKED                  
  4201   20D0    0E00                      MOVLW 0                                
  4202   20D2    23B0                      ADDWFC 0xb0, F, BANKED                 
  4203   20D4    2BAB                      INCF cdc_In_len, F, BANKED             
  4204   20D6    0100                      MOVLB 0                                
  4205   20D8    6BCA                      CLRF ZLPpending, BANKED                
  4206   20DA    0E20                      MOVLW 0x20                             
  4207   20DC    0100                      MOVLB 0                                
  4208   20DE    5DAB                      SUBWF cdc_In_len, W, BANKED            
  4209   20E0    E109                      BNZ 0x20f4                             
  4210   20E2    C0AB                      MOVFF cdc_In_len, POSTINC1             
  4211   20E4    FFE6                      NOP                                    
  4212   20E6    DF48                      RCALL putda_cdc                        
  4213   20E8    52E5                      MOVF POSTDEC1, F, ACCESS               
  4214   20EA    0100                      MOVLB 0                                
  4215   20EC    6BAB                      CLRF cdc_In_len, BANKED                
  4216   20EE    0100                      MOVLB 0                                
  4217   20F0    0E01                      MOVLW 0x1                              
  4218   20F2    6FCA                      MOVWF ZLPpending, BANKED               
  4219   20F4    0100                      MOVLB 0                                
  4220   20F6    6BCB                      CLRF lock, BANKED                      
  4221   20F8    6BC9                      CLRF cdc_timeout_count, BANKED         
  4222   20FA    52E5                      MOVF POSTDEC1, F, ACCESS               
  4223   20FC    CFE7                      MOVFF INDF1, FSR2                      
  4224   20FE    FFD9                      NOP                                    
  4225   2100    0012                      RETURN 0                               
  4226   2102    CFD9 getc_cdc             MOVFF FSR2, POSTINC1                   
  4227   2104    FFE6                      NOP                                    
  4228   2106    CFE1                      MOVFF FSR1L, FSR2                      
  4229   2108    FFD9                      NOP                                    
  4230   210A    52E6                      MOVF POSTINC1, F, ACCESS               
  4231   210C    6ADF                      CLRF INDF2, ACCESS                     
  4232   210E    0100                      MOVLB 0                                
  4233   2110    51AC                      MOVF cdc_Out_len, W, BANKED            
  4234   2112    E105                      BNZ 0x211e                             
  4235   2114    DEE7                      RCALL getda_cdc                        
  4236   2116    0100                      MOVLB 0                                
  4237   2118    6FAC                      MOVWF cdc_Out_len, BANKED              
  4238   211A    51AC                      MOVF cdc_Out_len, W, BANKED            
  4239   211C    E0FB                      BZ 0x2114                              
  4240   211E    C0B1                      MOVFF OutPtr, FSR0L                    
  4241   2120    FFE9                      NOP                                    
  4242   2122    C0B2                      MOVFF 0xb2, FSR0H                      
  4243   2124    FFEA                      NOP                                    
  4244   2126    CFEF                      MOVFF INDF0, INDF2                     
  4245   2128    FFDF                      NOP                                    
  4246   212A    2BB1                      INCF OutPtr, F, BANKED                 
  4247   212C    0E00                      MOVLW 0                                
  4248   212E    23B2                      ADDWFC 0xb2, F, BANKED                 
  4249   2130    07AC                      DECF cdc_Out_len, F, BANKED            
  4250   2132    50DF                      MOVF INDF2, W, ACCESS                  
  4251   2134    D000                      BRA 0x2136                             
  4252   2136    52E5                      MOVF POSTDEC1, F, ACCESS               
  4253   2138    52E5                      MOVF POSTDEC1, F, ACCESS               
  4254   213A    CFE7                      MOVFF INDF1, FSR2                      
  4255   213C    FFD9                      NOP                                    
  4256   213E    0012                      RETURN 0                               
  4257   2140    CFD9 poll_getc_cdc        MOVFF FSR2, POSTINC1                   
  4258   2142    FFE6                      NOP                                    
  4259   2144    CFE1                      MOVFF FSR1L, FSR2                      
  4260   2146    FFD9                      NOP                                    
  4261   2148    0100                      MOVLB 0                                
  4262   214A    51AC                      MOVF cdc_Out_len, W, BANKED            
  4263   214C    E015                      BZ 0x2178                              
  4264   214E    C0B1                      MOVFF OutPtr, FSR0L                    
  4265   2150    FFE9                      NOP                                    
  4266   2152    C0B2                      MOVFF 0xb2, FSR0H                      
  4267   2154    FFEA                      NOP                                    
  4268   2156    50EF                      MOVF INDF0, W, ACCESS                  
  4269   2158    6EE6                      MOVWF POSTINC1, ACCESS                 
  4270   215A    0EFD                      MOVLW 0xfd                             
  4271   215C    CFDB                      MOVFF PLUSW2, FSR0L                    
  4272   215E    FFE9                      NOP                                    
  4273   2160    0EFE                      MOVLW 0xfe                             
  4274   2162    CFDB                      MOVFF PLUSW2, FSR0H                    
  4275   2164    FFEA                      NOP                                    
  4276   2166    52E5                      MOVF POSTDEC1, F, ACCESS               
  4277   2168    50E7                      MOVF INDF1, W, ACCESS                  
  4278   216A    6EEF                      MOVWF INDF0, ACCESS                    
  4279   216C    2BB1                      INCF OutPtr, F, BANKED                 
  4280   216E    0E00                      MOVLW 0                                
  4281   2170    23B2                      ADDWFC 0xb2, F, BANKED                 
  4282   2172    07AC                      DECF cdc_Out_len, F, BANKED            
  4283   2174    0E01                      MOVLW 0x1                              
  4284   2176    D01F                      BRA 0x21b6                             
  4285   2178    DE9D                      RCALL getOutReady                      
  4286   217A    0900                      IORLW 0                                
  4287   217C    E01A                      BZ 0x21b2                              
  4288   217E    DEB2                      RCALL getda_cdc                        
  4289   2180    0100                      MOVLB 0                                
  4290   2182    6FAC                      MOVWF cdc_Out_len, BANKED              
  4291   2184    51AC                      MOVF cdc_Out_len, W, BANKED            
  4292   2186    E015                      BZ 0x21b2                              
  4293   2188    C0B1                      MOVFF OutPtr, FSR0L                    
  4294   218A    FFE9                      NOP                                    
  4295   218C    C0B2                      MOVFF 0xb2, FSR0H                      
  4296   218E    FFEA                      NOP                                    
  4297   2190    50EF                      MOVF INDF0, W, ACCESS                  
  4298   2192    6EE6                      MOVWF POSTINC1, ACCESS                 
  4299   2194    0EFD                      MOVLW 0xfd                             
  4300   2196    CFDB                      MOVFF PLUSW2, FSR0L                    
  4301   2198    FFE9                      NOP                                    
  4302   219A    0EFE                      MOVLW 0xfe                             
  4303   219C    CFDB                      MOVFF PLUSW2, FSR0H                    
  4304   219E    FFEA                      NOP                                    
  4305   21A0    52E5                      MOVF POSTDEC1, F, ACCESS               
  4306   21A2    50E7                      MOVF INDF1, W, ACCESS                  
  4307   21A4    6EEF                      MOVWF INDF0, ACCESS                    
  4308   21A6    2BB1                      INCF OutPtr, F, BANKED                 
  4309   21A8    0E00                      MOVLW 0                                
  4310   21AA    23B2                      ADDWFC 0xb2, F, BANKED                 
  4311   21AC    07AC                      DECF cdc_Out_len, F, BANKED            
  4312   21AE    0E01                      MOVLW 0x1                              
  4313   21B0    D002                      BRA 0x21b6                             
  4314   21B2    0E00                      MOVLW 0                                
  4315   21B4    D000                      BRA 0x21b6                             
  4316   21B6    52E5                      MOVF POSTDEC1, F, ACCESS               
  4317   21B8    CFE7                      MOVFF INDF1, FSR2                      
  4318   21BA    FFD9                      NOP                                    
  4319   21BC    0012                      RETURN 0                               
  4320   21BE    CFD9 peek_getc_cdc        MOVFF FSR2, POSTINC1                   
  4321   21C0    FFE6                      NOP                                    
  4322   21C2    CFE1                      MOVFF FSR1L, FSR2                      
  4323   21C4    FFD9                      NOP                                    
  4324   21C6    0100                      MOVLB 0                                
  4325   21C8    51AC                      MOVF cdc_Out_len, W, BANKED            
  4326   21CA    E011                      BZ 0x21ee                              
  4327   21CC    C0B1                      MOVFF OutPtr, FSR0L                    
  4328   21CE    FFE9                      NOP                                    
  4329   21D0    C0B2                      MOVFF 0xb2, FSR0H                      
  4330   21D2    FFEA                      NOP                                    
  4331   21D4    50EF                      MOVF INDF0, W, ACCESS                  
  4332   21D6    6EE6                      MOVWF POSTINC1, ACCESS                 
  4333   21D8    0EFD                      MOVLW 0xfd                             
  4334   21DA    CFDB                      MOVFF PLUSW2, FSR0L                    
  4335   21DC    FFE9                      NOP                                    
  4336   21DE    0EFE                      MOVLW 0xfe                             
  4337   21E0    CFDB                      MOVFF PLUSW2, FSR0H                    
  4338   21E2    FFEA                      NOP                                    
  4339   21E4    52E5                      MOVF POSTDEC1, F, ACCESS               
  4340   21E6    50E7                      MOVF INDF1, W, ACCESS                  
  4341   21E8    6EEF                      MOVWF INDF0, ACCESS                    
  4342   21EA    0E01                      MOVLW 0x1                              
  4343   21EC    D01B                      BRA 0x2224                             
  4344   21EE    DE62                      RCALL getOutReady                      
  4345   21F0    0900                      IORLW 0                                
  4346   21F2    E016                      BZ 0x2220                              
  4347   21F4    DE77                      RCALL getda_cdc                        
  4348   21F6    0100                      MOVLB 0                                
  4349   21F8    6FAC                      MOVWF cdc_Out_len, BANKED              
  4350   21FA    51AC                      MOVF cdc_Out_len, W, BANKED            
  4351   21FC    E011                      BZ 0x2220                              
  4352   21FE    C0B1                      MOVFF OutPtr, FSR0L                    
  4353   2200    FFE9                      NOP                                    
  4354   2202    C0B2                      MOVFF 0xb2, FSR0H                      
  4355   2204    FFEA                      NOP                                    
  4356   2206    50EF                      MOVF INDF0, W, ACCESS                  
  4357   2208    6EE6                      MOVWF POSTINC1, ACCESS                 
  4358   220A    0EFD                      MOVLW 0xfd                             
  4359   220C    CFDB                      MOVFF PLUSW2, FSR0L                    
  4360   220E    FFE9                      NOP                                    
  4361   2210    0EFE                      MOVLW 0xfe                             
  4362   2212    CFDB                      MOVFF PLUSW2, FSR0H                    
  4363   2214    FFEA                      NOP                                    
  4364   2216    52E5                      MOVF POSTDEC1, F, ACCESS               
  4365   2218    50E7                      MOVF INDF1, W, ACCESS                  
  4366   221A    6EEF                      MOVWF INDF0, ACCESS                    
  4367   221C    0E01                      MOVLW 0x1                              
  4368   221E    D002                      BRA 0x2224                             
  4369   2220    0E00                      MOVLW 0                                
  4370   2222    D000                      BRA 0x2224                             
  4371   2224    52E5                      MOVF POSTDEC1, F, ACCESS               
  4372   2226    CFE7                      MOVFF INDF1, FSR2                      
  4373   2228    FFD9                      NOP                                    
  4374   222A    0012                      RETURN 0                               
  4375   222C    FFFF                      NOP                                    
  4376   222E    FFFF                      NOP                                    
  4377   2230    FFFF                      NOP                                    
  4378   2232    FFFF                      NOP                                    
  4379   2234    FFFF                      NOP                                    
  4380   2236    FFFF                      NOP                                    
  4381   2238    FFFF                      NOP                                    
  4382   223A    FFFF                      NOP                                    
  4383   223C    FFFF                      NOP                                    
  4384   223E    FFFF                      NOP                                    
  4385   2240    FFFF                      NOP                                    
  4386   2242    FFFF                      NOP                                    
  4387   2244    FFFF                      NOP                                    
  4388   2246    FFFF                      NOP                                    
  4389   2248    FFFF                      NOP                                    
  4390   224A    FFFF                      NOP                                    
  4391   224C    FFFF                      NOP                                    
  4392   224E    FFFF                      NOP                                    
  4393   2250    FFFF                      NOP                                    
  4394   2252    FFFF                      NOP                                    
  4395   2254    FFFF                      NOP                                    
  4396   2256    FFFF                      NOP                                    
  4397   2258    FFFF                      NOP                                    
  4398   225A    FFFF                      NOP                                    
  4399   225C    FFFF                      NOP                                    
  4400   225E    FFFF                      NOP                                    
  4401   2260    FFFF                      NOP                                    
  4402   2262    FFFF                      NOP                                    
  4403   2264    FFFF                      NOP                                    
  4404   2266    FFFF                      NOP                                    
  4405   2268    FFFF                      NOP                                    
  4406   226A    FFFF                      NOP                                    
  4407   226C    FFFF                      NOP                                    
  4408   226E    FFFF                      NOP                                    
  4409   2270    FFFF                      NOP                                    
  4410   2272    FFFF                      NOP                                    
  4411   2274    FFFF                      NOP                                    
  4412   2276    FFFF                      NOP                                    
  4413   2278    FFFF                      NOP                                    
  4414   227A    FFFF                      NOP                                    
  4415   227C    FFFF                      NOP                                    
  4416   227E    FFFF                      NOP                                    
  4417   2280    FFFF                      NOP                                    
  4418   2282    FFFF                      NOP                                    
  4419   2284    FFFF                      NOP                                    
  4420   2286    FFFF                      NOP                                    
  4421   2288    FFFF                      NOP                                    
  4422   228A    FFFF                      NOP                                    
  4423   228C    FFFF                      NOP                                    
  4424   228E    FFFF                      NOP                                    
  4425   2290    FFFF                      NOP                                    
  4426   2292    FFFF                      NOP                                    
  4427   2294    FFFF                      NOP                                    
  4428   2296    FFFF                      NOP                                    
  4429   2298    FFFF                      NOP                                    
  4430   229A    FFFF                      NOP                                    
  4431   229C    FFFF                      NOP                                    
  4432   229E    FFFF                      NOP                                    
  4433   22A0    FFFF                      NOP                                    
  4434   22A2    FFFF                      NOP                                    
  4435   22A4    FFFF                      NOP                                    
  4436   22A6    FFFF                      NOP                                    
  4437   22A8    FFFF                      NOP                                    
  4438   22AA    FFFF                      NOP                                    
  4439   22AC    FFFF                      NOP                                    
  4440   22AE    FFFF                      NOP                                    
  4441   22B0    FFFF                      NOP                                    
  4442   22B2    FFFF                      NOP                                    
  4443   22B4    FFFF                      NOP                                    
  4444   22B6    FFFF                      NOP                                    
  4445   22B8    FFFF                      NOP                                    
  4446   22BA    FFFF                      NOP                                    
  4447   22BC    FFFF                      NOP                                    
  4448   22BE    FFFF                      NOP                                    
  4449   22C0    FFFF                      NOP                                    
  4450   22C2    FFFF                      NOP                                    
  4451   22C4    FFFF                      NOP                                    
  4452   22C6    FFFF                      NOP                                    
  4453   22C8    FFFF                      NOP                                    
  4454   22CA    FFFF                      NOP                                    
  4455   22CC    FFFF                      NOP                                    
  4456   22CE    FFFF                      NOP                                    
  4457   22D0    FFFF                      NOP                                    
  4458   22D2    FFFF                      NOP                                    
  4459   22D4    FFFF                      NOP                                    
  4460   22D6    FFFF                      NOP                                    
  4461   22D8    FFFF                      NOP                                    
  4462   22DA    FFFF                      NOP                                    
  4463   22DC    FFFF                      NOP                                    
  4464   22DE    FFFF                      NOP                                    
  4465   22E0    FFFF                      NOP                                    
  4466   22E2    FFFF                      NOP                                    
  4467   22E4    FFFF                      NOP                                    
  4468   22E6    FFFF                      NOP                                    
  4469   22E8    FFFF                      NOP                                    
  4470   22EA    FFFF                      NOP                                    
  4471   22EC    FFFF                      NOP                                    
  4472   22EE    FFFF                      NOP                                    
  4473   22F0    FFFF                      NOP                                    
  4474   22F2    FFFF                      NOP                                    
  4475   22F4    FFFF                      NOP                                    
  4476   22F6    FFFF                      NOP                                    
  4477   22F8    FFFF                      NOP                                    
  4478   22FA    FFFF                      NOP                                    
  4479   22FC    FFFF                      NOP                                    
  4480   22FE    FFFF                      NOP                                    
  4481   2300    FFFF                      NOP                                    
  4482   2302    FFFF                      NOP                                    
  4483   2304    FFFF                      NOP                                    
  4484   2306    FFFF                      NOP                                    
  4485   2308    FFFF                      NOP                                    
  4486   230A    FFFF                      NOP                                    
  4487   230C    FFFF                      NOP                                    
  4488   230E    FFFF                      NOP                                    
  4489   2310    FFFF                      NOP                                    
  4490   2312    FFFF                      NOP                                    
  4491   2314    FFFF                      NOP                                    
  4492   2316    FFFF                      NOP                                    
  4493   2318    FFFF                      NOP                                    
  4494   231A    FFFF                      NOP                                    
  4495   231C    FFFF                      NOP                                    
  4496   231E    FFFF                      NOP                                    
  4497   2320    FFFF                      NOP                                    
  4498   2322    FFFF                      NOP                                    
  4499   2324    FFFF                      NOP                                    
  4500   2326    FFFF                      NOP                                    
  4501   2328    FFFF                      NOP                                    
  4502   232A    FFFF                      NOP                                    
  4503   232C    FFFF                      NOP                                    
  4504   232E    FFFF                      NOP                                    
  4505   2330    FFFF                      NOP                                    
  4506   2332    FFFF                      NOP                                    
  4507   2334    FFFF                      NOP                                    
  4508   2336    FFFF                      NOP                                    
  4509   2338    FFFF                      NOP                                    
  4510   233A    FFFF                      NOP                                    
  4511   233C    FFFF                      NOP                                    
  4512   233E    FFFF                      NOP                                    
  4513   2340    FFFF                      NOP                                    
  4514   2342    FFFF                      NOP                                    
  4515   2344    FFFF                      NOP                                    
  4516   2346    FFFF                      NOP                                    
  4517   2348    FFFF                      NOP                                    
  4518   234A    FFFF                      NOP                                    
  4519   234C    FFFF                      NOP                                    
  4520   234E    FFFF                      NOP                                    
  4521   2350    FFFF                      NOP                                    
  4522   2352    FFFF                      NOP                                    
  4523   2354    FFFF                      NOP                                    
  4524   2356    FFFF                      NOP                                    
  4525   2358    FFFF                      NOP                                    
  4526   235A    FFFF                      NOP                                    
  4527   235C    FFFF                      NOP                                    
  4528   235E    FFFF                      NOP                                    
  4529   2360    FFFF                      NOP                                    
  4530   2362    FFFF                      NOP                                    
  4531   2364    FFFF                      NOP                                    
  4532   2366    FFFF                      NOP                                    
  4533   2368    FFFF                      NOP                                    
  4534   236A    FFFF                      NOP                                    
  4535   236C    FFFF                      NOP                                    
  4536   236E    FFFF                      NOP                                    
  4537   2370    FFFF                      NOP                                    
  4538   2372    FFFF                      NOP                                    
  4539   2374    FFFF                      NOP                                    
  4540   2376    FFFF                      NOP                                    
  4541   2378    FFFF                      NOP                                    
  4542   237A    FFFF                      NOP                                    
  4543   237C    FFFF                      NOP                                    
  4544   237E    FFFF                      NOP                                    
  4545   2380    FFFF                      NOP                                    
  4546   2382    FFFF                      NOP                                    
  4547   2384    FFFF                      NOP                                    
  4548   2386    FFFF                      NOP                                    
  4549   2388    FFFF                      NOP                                    
  4550   238A    FFFF                      NOP                                    
  4551   238C    FFFF                      NOP                                    
  4552   238E    FFFF                      NOP                                    
  4553   2390    FFFF                      NOP                                    
  4554   2392    FFFF                      NOP                                    
  4555   2394    FFFF                      NOP                                    
  4556   2396    FFFF                      NOP                                    
  4557   2398    FFFF                      NOP                                    
  4558   239A    FFFF                      NOP                                    
  4559   239C    FFFF                      NOP                                    
  4560   239E    FFFF                      NOP                                    
  4561   23A0    FFFF                      NOP                                    
  4562   23A2    FFFF                      NOP                                    
  4563   23A4    FFFF                      NOP                                    
  4564   23A6    FFFF                      NOP                                    
  4565   23A8    FFFF                      NOP                                    
  4566   23AA    FFFF                      NOP                                    
  4567   23AC    FFFF                      NOP                                    
  4568   23AE    FFFF                      NOP                                    
  4569   23B0    FFFF                      NOP                                    
  4570   23B2    FFFF                      NOP                                    
  4571   23B4    FFFF                      NOP                                    
  4572   23B6    FFFF                      NOP                                    
  4573   23B8    FFFF                      NOP                                    
  4574   23BA    FFFF                      NOP                                    
  4575   23BC    FFFF                      NOP                                    
  4576   23BE    FFFF                      NOP                                    
  4577   23C0    FFFF                      NOP                                    
  4578   23C2    FFFF                      NOP                                    
  4579   23C4    FFFF                      NOP                                    
  4580   23C6    FFFF                      NOP                                    
  4581   23C8    FFFF                      NOP                                    
  4582   23CA    FFFF                      NOP                                    
  4583   23CC    FFFF                      NOP                                    
  4584   23CE    FFFF                      NOP                                    
  4585   23D0    FFFF                      NOP                                    
  4586   23D2    FFFF                      NOP                                    
  4587   23D4    FFFF                      NOP                                    
  4588   23D6    FFFF                      NOP                                    
  4589   23D8    FFFF                      NOP                                    
  4590   23DA    FFFF                      NOP                                    
  4591   23DC    FFFF                      NOP                                    
  4592   23DE    FFFF                      NOP                                    
  4593   23E0    FFFF                      NOP                                    
  4594   23E2    FFFF                      NOP                                    
  4595   23E4    FFFF                      NOP                                    
  4596   23E6    FFFF                      NOP                                    
  4597   23E8    FFFF                      NOP                                    
  4598   23EA    FFFF                      NOP                                    
  4599   23EC    FFFF                      NOP                                    
  4600   23EE    FFFF                      NOP                                    
  4601   23F0    FFFF                      NOP                                    
  4602   23F2    FFFF                      NOP                                    
  4603   23F4    FFFF                      NOP                                    
  4604   23F6    FFFF                      NOP                                    
  4605   23F8    FFFF                      NOP                                    
  4606   23FA    FFFF                      NOP                                    
  4607   23FC    FFFF                      NOP                                    
  4608   23FE    FFFF                      NOP                                    
  4609   2400    FFFF                      NOP                                    
  4610   2402    FFFF                      NOP                                    
  4611   2404    FFFF                      NOP                                    
  4612   2406    FFFF                      NOP                                    
  4613   2408    FFFF                      NOP                                    
  4614   240A    FFFF                      NOP                                    
  4615   240C    FFFF                      NOP                                    
  4616   240E    FFFF                      NOP                                    
  4617   2410    FFFF                      NOP                                    
  4618   2412    FFFF                      NOP                                    
  4619   2414    FFFF                      NOP                                    
  4620   2416    FFFF                      NOP                                    
  4621   2418    FFFF                      NOP                                    
  4622   241A    FFFF                      NOP                                    
  4623   241C    FFFF                      NOP                                    
  4624   241E    FFFF                      NOP                                    
  4625   2420    FFFF                      NOP                                    
  4626   2422    FFFF                      NOP                                    
  4627   2424    FFFF                      NOP                                    
  4628   2426    FFFF                      NOP                                    
  4629   2428    FFFF                      NOP                                    
  4630   242A    FFFF                      NOP                                    
  4631   242C    FFFF                      NOP                                    
  4632   242E    FFFF                      NOP                                    
  4633   2430    FFFF                      NOP                                    
  4634   2432    FFFF                      NOP                                    
  4635   2434    FFFF                      NOP                                    
  4636   2436    FFFF                      NOP                                    
  4637   2438    FFFF                      NOP                                    
  4638   243A    FFFF                      NOP                                    
  4639   243C    FFFF                      NOP                                    
  4640   243E    FFFF                      NOP                                    
  4641   2440    FFFF                      NOP                                    
  4642   2442    FFFF                      NOP                                    
  4643   2444    FFFF                      NOP                                    
  4644   2446    FFFF                      NOP                                    
  4645   2448    FFFF                      NOP                                    
  4646   244A    FFFF                      NOP                                    
  4647   244C    FFFF                      NOP                                    
  4648   244E    FFFF                      NOP                                    
  4649   2450    FFFF                      NOP                                    
  4650   2452    FFFF                      NOP                                    
  4651   2454    FFFF                      NOP                                    
  4652   2456    FFFF                      NOP                                    
  4653   2458    FFFF                      NOP                                    
  4654   245A    FFFF                      NOP                                    
  4655   245C    FFFF                      NOP                                    
  4656   245E    FFFF                      NOP                                    
  4657   2460    FFFF                      NOP                                    
  4658   2462    FFFF                      NOP                                    
  4659   2464    FFFF                      NOP                                    
  4660   2466    FFFF                      NOP                                    
  4661   2468    FFFF                      NOP                                    
  4662   246A    FFFF                      NOP                                    
  4663   246C    FFFF                      NOP                                    
  4664   246E    FFFF                      NOP                                    
  4665   2470    FFFF                      NOP                                    
  4666   2472    FFFF                      NOP                                    
  4667   2474    FFFF                      NOP                                    
  4668   2476    FFFF                      NOP                                    
  4669   2478    FFFF                      NOP                                    
  4670   247A    FFFF                      NOP                                    
  4671   247C    FFFF                      NOP                                    
  4672   247E    FFFF                      NOP                                    
  4673   2480    FFFF                      NOP                                    
  4674   2482    FFFF                      NOP                                    
  4675   2484    FFFF                      NOP                                    
  4676   2486    FFFF                      NOP                                    
  4677   2488    FFFF                      NOP                                    
  4678   248A    FFFF                      NOP                                    
  4679   248C    FFFF                      NOP                                    
  4680   248E    FFFF                      NOP                                    
  4681   2490    FFFF                      NOP                                    
  4682   2492    FFFF                      NOP                                    
  4683   2494    FFFF                      NOP                                    
  4684   2496    FFFF                      NOP                                    
  4685   2498    FFFF                      NOP                                    
  4686   249A    FFFF                      NOP                                    
  4687   249C    FFFF                      NOP                                    
  4688   249E    FFFF                      NOP                                    
  4689   24A0    FFFF                      NOP                                    
  4690   24A2    FFFF                      NOP                                    
  4691   24A4    FFFF                      NOP                                    
  4692   24A6    FFFF                      NOP                                    
  4693   24A8    FFFF                      NOP                                    
  4694   24AA    FFFF                      NOP                                    
  4695   24AC    FFFF                      NOP                                    
  4696   24AE    FFFF                      NOP                                    
  4697   24B0    FFFF                      NOP                                    
  4698   24B2    FFFF                      NOP                                    
  4699   24B4    FFFF                      NOP                                    
  4700   24B6    FFFF                      NOP                                    
  4701   24B8    FFFF                      NOP                                    
  4702   24BA    FFFF                      NOP                                    
  4703   24BC    FFFF                      NOP                                    
  4704   24BE    FFFF                      NOP                                    
  4705   24C0    FFFF                      NOP                                    
  4706   24C2    FFFF                      NOP                                    
  4707   24C4    FFFF                      NOP                                    
  4708   24C6    FFFF                      NOP                                    
  4709   24C8    FFFF                      NOP                                    
  4710   24CA    FFFF                      NOP                                    
  4711   24CC    FFFF                      NOP                                    
  4712   24CE    FFFF                      NOP                                    
  4713   24D0    FFFF                      NOP                                    
  4714   24D2    FFFF                      NOP                                    
  4715   24D4    FFFF                      NOP                                    
  4716   24D6    FFFF                      NOP                                    
  4717   24D8    FFFF                      NOP                                    
  4718   24DA    FFFF                      NOP                                    
  4719   24DC    FFFF                      NOP                                    
  4720   24DE    FFFF                      NOP                                    
  4721   24E0    FFFF                      NOP                                    
  4722   24E2    FFFF                      NOP                                    
  4723   24E4    FFFF                      NOP                                    
  4724   24E6    FFFF                      NOP                                    
  4725   24E8    FFFF                      NOP                                    
  4726   24EA    FFFF                      NOP                                    
  4727   24EC    FFFF                      NOP                                    
  4728   24EE    FFFF                      NOP                                    
  4729   24F0    FFFF                      NOP                                    
  4730   24F2    FFFF                      NOP                                    
  4731   24F4    FFFF                      NOP                                    
  4732   24F6    FFFF                      NOP                                    
  4733   24F8    FFFF                      NOP                                    
  4734   24FA    FFFF                      NOP                                    
  4735   24FC    FFFF                      NOP                                    
  4736   24FE    FFFF                      NOP                                    
  4737   2500    FFFF                      NOP                                    
  4738   2502    FFFF                      NOP                                    
  4739   2504    FFFF                      NOP                                    
  4740   2506    FFFF                      NOP                                    
  4741   2508    FFFF                      NOP                                    
  4742   250A    FFFF                      NOP                                    
  4743   250C    FFFF                      NOP                                    
  4744   250E    FFFF                      NOP                                    
  4745   2510    FFFF                      NOP                                    
  4746   2512    FFFF                      NOP                                    
  4747   2514    FFFF                      NOP                                    
  4748   2516    FFFF                      NOP                                    
  4749   2518    FFFF                      NOP                                    
  4750   251A    FFFF                      NOP                                    
  4751   251C    FFFF                      NOP                                    
  4752   251E    FFFF                      NOP                                    
  4753   2520    FFFF                      NOP                                    
  4754   2522    FFFF                      NOP                                    
  4755   2524    FFFF                      NOP                                    
  4756   2526    FFFF                      NOP                                    
  4757   2528    FFFF                      NOP                                    
  4758   252A    FFFF                      NOP                                    
  4759   252C    FFFF                      NOP                                    
  4760   252E    FFFF                      NOP                                    
  4761   2530    FFFF                      NOP                                    
  4762   2532    FFFF                      NOP                                    
  4763   2534    FFFF                      NOP                                    
  4764   2536    FFFF                      NOP                                    
  4765   2538    FFFF                      NOP                                    
  4766   253A    FFFF                      NOP                                    
  4767   253C    FFFF                      NOP                                    
  4768   253E    FFFF                      NOP                                    
  4769   2540    FFFF                      NOP                                    
  4770   2542    FFFF                      NOP                                    
  4771   2544    FFFF                      NOP                                    
  4772   2546    FFFF                      NOP                                    
  4773   2548    FFFF                      NOP                                    
  4774   254A    FFFF                      NOP                                    
  4775   254C    FFFF                      NOP                                    
  4776   254E    FFFF                      NOP                                    
  4777   2550    FFFF                      NOP                                    
  4778   2552    FFFF                      NOP                                    
  4779   2554    FFFF                      NOP                                    
  4780   2556    FFFF                      NOP                                    
  4781   2558    FFFF                      NOP                                    
  4782   255A    FFFF                      NOP                                    
  4783   255C    FFFF                      NOP                                    
  4784   255E    FFFF                      NOP                                    
  4785   2560    FFFF                      NOP                                    
  4786   2562    FFFF                      NOP                                    
  4787   2564    FFFF                      NOP                                    
  4788   2566    FFFF                      NOP                                    
  4789   2568    FFFF                      NOP                                    
  4790   256A    FFFF                      NOP                                    
  4791   256C    FFFF                      NOP                                    
  4792   256E    FFFF                      NOP                                    
  4793   2570    FFFF                      NOP                                    
  4794   2572    FFFF                      NOP                                    
  4795   2574    FFFF                      NOP                                    
  4796   2576    FFFF                      NOP                                    
  4797   2578    FFFF                      NOP                                    
  4798   257A    FFFF                      NOP                                    
  4799   257C    FFFF                      NOP                                    
  4800   257E    FFFF                      NOP                                    
  4801   2580    FFFF                      NOP                                    
  4802   2582    FFFF                      NOP                                    
  4803   2584    FFFF                      NOP                                    
  4804   2586    FFFF                      NOP                                    
  4805   2588    FFFF                      NOP                                    
  4806   258A    FFFF                      NOP                                    
  4807   258C    FFFF                      NOP                                    
  4808   258E    FFFF                      NOP                                    
  4809   2590    FFFF                      NOP                                    
  4810   2592    FFFF                      NOP                                    
  4811   2594    FFFF                      NOP                                    
  4812   2596    FFFF                      NOP                                    
  4813   2598    FFFF                      NOP                                    
  4814   259A    FFFF                      NOP                                    
  4815   259C    FFFF                      NOP                                    
  4816   259E    FFFF                      NOP                                    
  4817   25A0    FFFF                      NOP                                    
  4818   25A2    FFFF                      NOP                                    
  4819   25A4    FFFF                      NOP                                    
  4820   25A6    FFFF                      NOP                                    
  4821   25A8    FFFF                      NOP                                    
  4822   25AA    FFFF                      NOP                                    
  4823   25AC    FFFF                      NOP                                    
  4824   25AE    FFFF                      NOP                                    
  4825   25B0    FFFF                      NOP                                    
  4826   25B2    FFFF                      NOP                                    
  4827   25B4    FFFF                      NOP                                    
  4828   25B6    FFFF                      NOP                                    
  4829   25B8    FFFF                      NOP                                    
  4830   25BA    FFFF                      NOP                                    
  4831   25BC    FFFF                      NOP                                    
  4832   25BE    FFFF                      NOP                                    
  4833   25C0    FFFF                      NOP                                    
  4834   25C2    FFFF                      NOP                                    
  4835   25C4    FFFF                      NOP                                    
  4836   25C6    FFFF                      NOP                                    
  4837   25C8    FFFF                      NOP                                    
  4838   25CA    FFFF                      NOP                                    
  4839   25CC    FFFF                      NOP                                    
  4840   25CE    FFFF                      NOP                                    
  4841   25D0    FFFF                      NOP                                    
  4842   25D2    FFFF                      NOP                                    
  4843   25D4    FFFF                      NOP                                    
  4844   25D6    FFFF                      NOP                                    
  4845   25D8    FFFF                      NOP                                    
  4846   25DA    FFFF                      NOP                                    
  4847   25DC    FFFF                      NOP                                    
  4848   25DE    FFFF                      NOP                                    
  4849   25E0    FFFF                      NOP                                    
  4850   25E2    FFFF                      NOP                                    
  4851   25E4    FFFF                      NOP                                    
  4852   25E6    FFFF                      NOP                                    
  4853   25E8    FFFF                      NOP                                    
  4854   25EA    FFFF                      NOP                                    
  4855   25EC    FFFF                      NOP                                    
  4856   25EE    FFFF                      NOP                                    
  4857   25F0    FFFF                      NOP                                    
  4858   25F2    FFFF                      NOP                                    
  4859   25F4    FFFF                      NOP                                    
  4860   25F6    FFFF                      NOP                                    
  4861   25F8    FFFF                      NOP                                    
  4862   25FA    FFFF                      NOP                                    
  4863   25FC    FFFF                      NOP                                    
  4864   25FE    FFFF                      NOP                                    
  4865   2600    FFFF                      NOP                                    
  4866   2602    FFFF                      NOP                                    
  4867   2604    FFFF                      NOP                                    
  4868   2606    FFFF                      NOP                                    
  4869   2608    FFFF                      NOP                                    
  4870   260A    FFFF                      NOP                                    
  4871   260C    FFFF                      NOP                                    
  4872   260E    FFFF                      NOP                                    
  4873   2610    FFFF                      NOP                                    
  4874   2612    FFFF                      NOP                                    
  4875   2614    FFFF                      NOP                                    
  4876   2616    FFFF                      NOP                                    
  4877   2618    FFFF                      NOP                                    
  4878   261A    FFFF                      NOP                                    
  4879   261C    FFFF                      NOP                                    
  4880   261E    FFFF                      NOP                                    
  4881   2620    FFFF                      NOP                                    
  4882   2622    FFFF                      NOP                                    
  4883   2624    FFFF                      NOP                                    
  4884   2626    FFFF                      NOP                                    
  4885   2628    FFFF                      NOP                                    
  4886   262A    FFFF                      NOP                                    
  4887   262C    FFFF                      NOP                                    
  4888   262E    FFFF                      NOP                                    
  4889   2630    FFFF                      NOP                                    
  4890   2632    FFFF                      NOP                                    
  4891   2634    FFFF                      NOP                                    
  4892   2636    FFFF                      NOP                                    
  4893   2638    FFFF                      NOP                                    
  4894   263A    FFFF                      NOP                                    
  4895   263C    FFFF                      NOP                                    
  4896   263E    FFFF                      NOP                                    
  4897   2640    FFFF                      NOP                                    
  4898   2642    FFFF                      NOP                                    
  4899   2644    FFFF                      NOP                                    
  4900   2646    FFFF                      NOP                                    
  4901   2648    FFFF                      NOP                                    
  4902   264A    FFFF                      NOP                                    
  4903   264C    FFFF                      NOP                                    
  4904   264E    FFFF                      NOP                                    
  4905   2650    FFFF                      NOP                                    
  4906   2652    FFFF                      NOP                                    
  4907   2654    FFFF                      NOP                                    
  4908   2656    FFFF                      NOP                                    
  4909   2658    FFFF                      NOP                                    
  4910   265A    FFFF                      NOP                                    
  4911   265C    FFFF                      NOP                                    
  4912   265E    FFFF                      NOP                                    
  4913   2660    FFFF                      NOP                                    
  4914   2662    FFFF                      NOP                                    
  4915   2664    FFFF                      NOP                                    
  4916   2666    FFFF                      NOP                                    
  4917   2668    FFFF                      NOP                                    
  4918   266A    FFFF                      NOP                                    
  4919   266C    FFFF                      NOP                                    
  4920   266E    FFFF                      NOP                                    
  4921   2670    FFFF                      NOP                                    
  4922   2672    FFFF                      NOP                                    
  4923   2674    FFFF                      NOP                                    
  4924   2676    FFFF                      NOP                                    
  4925   2678    FFFF                      NOP                                    
  4926   267A    FFFF                      NOP                                    
  4927   267C    FFFF                      NOP                                    
  4928   267E    FFFF                      NOP                                    
  4929   2680    FFFF                      NOP                                    
  4930   2682    FFFF                      NOP                                    
  4931   2684    FFFF                      NOP                                    
  4932   2686    FFFF                      NOP                                    
  4933   2688    FFFF                      NOP                                    
  4934   268A    FFFF                      NOP                                    
  4935   268C    FFFF                      NOP                                    
  4936   268E    FFFF                      NOP                                    
  4937   2690    FFFF                      NOP                                    
  4938   2692    FFFF                      NOP                                    
  4939   2694    FFFF                      NOP                                    
  4940   2696    FFFF                      NOP                                    
  4941   2698    FFFF                      NOP                                    
  4942   269A    FFFF                      NOP                                    
  4943   269C    FFFF                      NOP                                    
  4944   269E    FFFF                      NOP                                    
  4945   26A0    FFFF                      NOP                                    
  4946   26A2    FFFF                      NOP                                    
  4947   26A4    FFFF                      NOP                                    
  4948   26A6    FFFF                      NOP                                    
  4949   26A8    FFFF                      NOP                                    
  4950   26AA    FFFF                      NOP                                    
  4951   26AC    FFFF                      NOP                                    
  4952   26AE    FFFF                      NOP                                    
  4953   26B0    FFFF                      NOP                                    
  4954   26B2    FFFF                      NOP                                    
  4955   26B4    FFFF                      NOP                                    
  4956   26B6    FFFF                      NOP                                    
  4957   26B8    FFFF                      NOP                                    
  4958   26BA    FFFF                      NOP                                    
  4959   26BC    FFFF                      NOP                                    
  4960   26BE    FFFF                      NOP                                    
  4961   26C0    FFFF                      NOP                                    
  4962   26C2    FFFF                      NOP                                    
  4963   26C4    FFFF                      NOP                                    
  4964   26C6    FFFF                      NOP                                    
  4965   26C8    FFFF                      NOP                                    
  4966   26CA    FFFF                      NOP                                    
  4967   26CC    FFFF                      NOP                                    
  4968   26CE    FFFF                      NOP                                    
  4969   26D0    FFFF                      NOP                                    
  4970   26D2    FFFF                      NOP                                    
  4971   26D4    FFFF                      NOP                                    
  4972   26D6    FFFF                      NOP                                    
  4973   26D8    FFFF                      NOP                                    
  4974   26DA    FFFF                      NOP                                    
  4975   26DC    FFFF                      NOP                                    
  4976   26DE    FFFF                      NOP                                    
  4977   26E0    FFFF                      NOP                                    
  4978   26E2    FFFF                      NOP                                    
  4979   26E4    FFFF                      NOP                                    
  4980   26E6    FFFF                      NOP                                    
  4981   26E8    FFFF                      NOP                                    
  4982   26EA    FFFF                      NOP                                    
  4983   26EC    FFFF                      NOP                                    
  4984   26EE    FFFF                      NOP                                    
  4985   26F0    FFFF                      NOP                                    
  4986   26F2    FFFF                      NOP                                    
  4987   26F4    FFFF                      NOP                                    
  4988   26F6    FFFF                      NOP                                    
  4989   26F8    FFFF                      NOP                                    
  4990   26FA    FFFF                      NOP                                    
  4991   26FC    FFFF                      NOP                                    
  4992   26FE    FFFF                      NOP                                    
  4993   2700    FFFF                      NOP                                    
  4994   2702    FFFF                      NOP                                    
  4995   2704    FFFF                      NOP                                    
  4996   2706    FFFF                      NOP                                    
  4997   2708    FFFF                      NOP                                    
  4998   270A    FFFF                      NOP                                    
  4999   270C    FFFF                      NOP                                    
  5000   270E    FFFF                      NOP                                    
  5001   2710    FFFF                      NOP                                    
  5002   2712    FFFF                      NOP                                    
  5003   2714    FFFF                      NOP                                    
  5004   2716    FFFF                      NOP                                    
  5005   2718    FFFF                      NOP                                    
  5006   271A    FFFF                      NOP                                    
  5007   271C    FFFF                      NOP                                    
  5008   271E    FFFF                      NOP                                    
  5009   2720    FFFF                      NOP                                    
  5010   2722    FFFF                      NOP                                    
  5011   2724    FFFF                      NOP                                    
  5012   2726    FFFF                      NOP                                    
  5013   2728    FFFF                      NOP                                    
  5014   272A    FFFF                      NOP                                    
  5015   272C    FFFF                      NOP                                    
  5016   272E    FFFF                      NOP                                    
  5017   2730    FFFF                      NOP                                    
  5018   2732    FFFF                      NOP                                    
  5019   2734    FFFF                      NOP                                    
  5020   2736    FFFF                      NOP                                    
  5021   2738    FFFF                      NOP                                    
  5022   273A    FFFF                      NOP                                    
  5023   273C    FFFF                      NOP                                    
  5024   273E    FFFF                      NOP                                    
  5025   2740    FFFF                      NOP                                    
  5026   2742    FFFF                      NOP                                    
  5027   2744    FFFF                      NOP                                    
  5028   2746    FFFF                      NOP                                    
  5029   2748    FFFF                      NOP                                    
  5030   274A    FFFF                      NOP                                    
  5031   274C    FFFF                      NOP                                    
  5032   274E    FFFF                      NOP                                    
  5033   2750    FFFF                      NOP                                    
  5034   2752    FFFF                      NOP                                    
  5035   2754    FFFF                      NOP                                    
  5036   2756    FFFF                      NOP                                    
  5037   2758    FFFF                      NOP                                    
  5038   275A    FFFF                      NOP                                    
  5039   275C    FFFF                      NOP                                    
  5040   275E    FFFF                      NOP                                    
  5041   2760    FFFF                      NOP                                    
  5042   2762    FFFF                      NOP                                    
  5043   2764    FFFF                      NOP                                    
  5044   2766    FFFF                      NOP                                    
  5045   2768    FFFF                      NOP                                    
  5046   276A    FFFF                      NOP                                    
  5047   276C    FFFF                      NOP                                    
  5048   276E    FFFF                      NOP                                    
  5049   2770    FFFF                      NOP                                    
  5050   2772    FFFF                      NOP                                    
  5051   2774    FFFF                      NOP                                    
  5052   2776    FFFF                      NOP                                    
  5053   2778    FFFF                      NOP                                    
  5054   277A    FFFF                      NOP                                    
  5055   277C    FFFF                      NOP                                    
  5056   277E    FFFF                      NOP                                    
  5057   2780    FFFF                      NOP                                    
  5058   2782    FFFF                      NOP                                    
  5059   2784    FFFF                      NOP                                    
  5060   2786    FFFF                      NOP                                    
  5061   2788    FFFF                      NOP                                    
  5062   278A    FFFF                      NOP                                    
  5063   278C    FFFF                      NOP                                    
  5064   278E    FFFF                      NOP                                    
  5065   2790    FFFF                      NOP                                    
  5066   2792    FFFF                      NOP                                    
  5067   2794    FFFF                      NOP                                    
  5068   2796    FFFF                      NOP                                    
  5069   2798    FFFF                      NOP                                    
  5070   279A    FFFF                      NOP                                    
  5071   279C    FFFF                      NOP                                    
  5072   279E    FFFF                      NOP                                    
  5073   27A0    FFFF                      NOP                                    
  5074   27A2    FFFF                      NOP                                    
  5075   27A4    FFFF                      NOP                                    
  5076   27A6    FFFF                      NOP                                    
  5077   27A8    FFFF                      NOP                                    
  5078   27AA    FFFF                      NOP                                    
  5079   27AC    FFFF                      NOP                                    
  5080   27AE    FFFF                      NOP                                    
  5081   27B0    FFFF                      NOP                                    
  5082   27B2    FFFF                      NOP                                    
  5083   27B4    FFFF                      NOP                                    
  5084   27B6    FFFF                      NOP                                    
  5085   27B8    FFFF                      NOP                                    
  5086   27BA    FFFF                      NOP                                    
  5087   27BC    FFFF                      NOP                                    
  5088   27BE    FFFF                      NOP                                    
  5089   27C0    FFFF                      NOP                                    
  5090   27C2    FFFF                      NOP                                    
  5091   27C4    FFFF                      NOP                                    
  5092   27C6    FFFF                      NOP                                    
  5093   27C8    FFFF                      NOP                                    
  5094   27CA    FFFF                      NOP                                    
  5095   27CC    FFFF                      NOP                                    
  5096   27CE    FFFF                      NOP                                    
  5097   27D0    FFFF                      NOP                                    
  5098   27D2    FFFF                      NOP                                    
  5099   27D4    FFFF                      NOP                                    
  5100   27D6    FFFF                      NOP                                    
  5101   27D8    FFFF                      NOP                                    
  5102   27DA    FFFF                      NOP                                    
  5103   27DC    FFFF                      NOP                                    
  5104   27DE    FFFF                      NOP                                    
  5105   27E0    FFFF                      NOP                                    
  5106   27E2    FFFF                      NOP                                    
  5107   27E4    FFFF                      NOP                                    
  5108   27E6    FFFF                      NOP                                    
  5109   27E8    FFFF                      NOP                                    
  5110   27EA    FFFF                      NOP                                    
  5111   27EC    FFFF                      NOP                                    
  5112   27EE    FFFF                      NOP                                    
  5113   27F0    FFFF                      NOP                                    
  5114   27F2    FFFF                      NOP                                    
  5115   27F4    FFFF                      NOP                                    
  5116   27F6    FFFF                      NOP                                    
  5117   27F8    FFFF                      NOP                                    
  5118   27FA    FFFF                      NOP                                    
  5119   27FC    FFFF                      NOP                                    
  5120   27FE    FFFF                      NOP                                    
  5121   2800    FFFF                      NOP                                    
  5122   2802    FFFF                      NOP                                    
  5123   2804    FFFF                      NOP                                    
  5124   2806    FFFF                      NOP                                    
  5125   2808    FFFF                      NOP                                    
  5126   280A    FFFF                      NOP                                    
  5127   280C    FFFF                      NOP                                    
  5128   280E    FFFF                      NOP                                    
  5129   2810    FFFF                      NOP                                    
  5130   2812    FFFF                      NOP                                    
  5131   2814    FFFF                      NOP                                    
  5132   2816    FFFF                      NOP                                    
  5133   2818    FFFF                      NOP                                    
  5134   281A    FFFF                      NOP                                    
  5135   281C    FFFF                      NOP                                    
  5136   281E    FFFF                      NOP                                    
  5137   2820    FFFF                      NOP                                    
  5138   2822    FFFF                      NOP                                    
  5139   2824    FFFF                      NOP                                    
  5140   2826    FFFF                      NOP                                    
  5141   2828    FFFF                      NOP                                    
  5142   282A    FFFF                      NOP                                    
  5143   282C    FFFF                      NOP                                    
  5144   282E    FFFF                      NOP                                    
  5145   2830    FFFF                      NOP                                    
  5146   2832    FFFF                      NOP                                    
  5147   2834    FFFF                      NOP                                    
  5148   2836    FFFF                      NOP                                    
  5149   2838    FFFF                      NOP                                    
  5150   283A    FFFF                      NOP                                    
  5151   283C    FFFF                      NOP                                    
  5152   283E    FFFF                      NOP                                    
  5153   2840    FFFF                      NOP                                    
  5154   2842    FFFF                      NOP                                    
  5155   2844    FFFF                      NOP                                    
  5156   2846    FFFF                      NOP                                    
  5157   2848    FFFF                      NOP                                    
  5158   284A    FFFF                      NOP                                    
  5159   284C    FFFF                      NOP                                    
  5160   284E    FFFF                      NOP                                    
  5161   2850    FFFF                      NOP                                    
  5162   2852    FFFF                      NOP                                    
  5163   2854    FFFF                      NOP                                    
  5164   2856    FFFF                      NOP                                    
  5165   2858    FFFF                      NOP                                    
  5166   285A    FFFF                      NOP                                    
  5167   285C    FFFF                      NOP                                    
  5168   285E    FFFF                      NOP                                    
  5169   2860    FFFF                      NOP                                    
  5170   2862    FFFF                      NOP                                    
  5171   2864    FFFF                      NOP                                    
  5172   2866    FFFF                      NOP                                    
  5173   2868    FFFF                      NOP                                    
  5174   286A    FFFF                      NOP                                    
  5175   286C    FFFF                      NOP                                    
  5176   286E    FFFF                      NOP                                    
  5177   2870    FFFF                      NOP                                    
  5178   2872    FFFF                      NOP                                    
  5179   2874    FFFF                      NOP                                    
  5180   2876    FFFF                      NOP                                    
  5181   2878    FFFF                      NOP                                    
  5182   287A    FFFF                      NOP                                    
  5183   287C    FFFF                      NOP                                    
  5184   287E    FFFF                      NOP                                    
  5185   2880    FFFF                      NOP                                    
  5186   2882    FFFF                      NOP                                    
  5187   2884    FFFF                      NOP                                    
  5188   2886    FFFF                      NOP                                    
  5189   2888    FFFF                      NOP                                    
  5190   288A    FFFF                      NOP                                    
  5191   288C    FFFF                      NOP                                    
  5192   288E    FFFF                      NOP                                    
  5193   2890    FFFF                      NOP                                    
  5194   2892    FFFF                      NOP                                    
  5195   2894    FFFF                      NOP                                    
  5196   2896    FFFF                      NOP                                    
  5197   2898    FFFF                      NOP                                    
  5198   289A    FFFF                      NOP                                    
  5199   289C    FFFF                      NOP                                    
  5200   289E    FFFF                      NOP                                    
  5201   28A0    FFFF                      NOP                                    
  5202   28A2    FFFF                      NOP                                    
  5203   28A4    FFFF                      NOP                                    
  5204   28A6    FFFF                      NOP                                    
  5205   28A8    FFFF                      NOP                                    
  5206   28AA    FFFF                      NOP                                    
  5207   28AC    FFFF                      NOP                                    
  5208   28AE    FFFF                      NOP                                    
  5209   28B0    FFFF                      NOP                                    
  5210   28B2    FFFF                      NOP                                    
  5211   28B4    FFFF                      NOP                                    
  5212   28B6    FFFF                      NOP                                    
  5213   28B8    FFFF                      NOP                                    
  5214   28BA    FFFF                      NOP                                    
  5215   28BC    FFFF                      NOP                                    
  5216   28BE    FFFF                      NOP                                    
  5217   28C0    FFFF                      NOP                                    
  5218   28C2    FFFF                      NOP                                    
  5219   28C4    FFFF                      NOP                                    
  5220   28C6    FFFF                      NOP                                    
  5221   28C8    FFFF                      NOP                                    
  5222   28CA    FFFF                      NOP                                    
  5223   28CC    FFFF                      NOP                                    
  5224   28CE    FFFF                      NOP                                    
  5225   28D0    FFFF                      NOP                                    
  5226   28D2    FFFF                      NOP                                    
  5227   28D4    FFFF                      NOP                                    
  5228   28D6    FFFF                      NOP                                    
  5229   28D8    FFFF                      NOP                                    
  5230   28DA    FFFF                      NOP                                    
  5231   28DC    FFFF                      NOP                                    
  5232   28DE    FFFF                      NOP                                    
  5233   28E0    FFFF                      NOP                                    
  5234   28E2    FFFF                      NOP                                    
  5235   28E4    FFFF                      NOP                                    
  5236   28E6    FFFF                      NOP                                    
  5237   28E8    FFFF                      NOP                                    
  5238   28EA    FFFF                      NOP                                    
  5239   28EC    FFFF                      NOP                                    
  5240   28EE    FFFF                      NOP                                    
  5241   28F0    FFFF                      NOP                                    
  5242   28F2    FFFF                      NOP                                    
  5243   28F4    FFFF                      NOP                                    
  5244   28F6    FFFF                      NOP                                    
  5245   28F8    FFFF                      NOP                                    
  5246   28FA    FFFF                      NOP                                    
  5247   28FC    FFFF                      NOP                                    
  5248   28FE    FFFF                      NOP                                    
  5249   2900    FFFF                      NOP                                    
  5250   2902    FFFF                      NOP                                    
  5251   2904    FFFF                      NOP                                    
  5252   2906    FFFF                      NOP                                    
  5253   2908    FFFF                      NOP                                    
  5254   290A    FFFF                      NOP                                    
  5255   290C    FFFF                      NOP                                    
  5256   290E    FFFF                      NOP                                    
  5257   2910    FFFF                      NOP                                    
  5258   2912    FFFF                      NOP                                    
  5259   2914    FFFF                      NOP                                    
  5260   2916    FFFF                      NOP                                    
  5261   2918    FFFF                      NOP                                    
  5262   291A    FFFF                      NOP                                    
  5263   291C    FFFF                      NOP                                    
  5264   291E    FFFF                      NOP                                    
  5265   2920    FFFF                      NOP                                    
  5266   2922    FFFF                      NOP                                    
  5267   2924    FFFF                      NOP                                    
  5268   2926    FFFF                      NOP                                    
  5269   2928    FFFF                      NOP                                    
  5270   292A    FFFF                      NOP                                    
  5271   292C    FFFF                      NOP                                    
  5272   292E    FFFF                      NOP                                    
  5273   2930    FFFF                      NOP                                    
  5274   2932    FFFF                      NOP                                    
  5275   2934    FFFF                      NOP                                    
  5276   2936    FFFF                      NOP                                    
  5277   2938    FFFF                      NOP                                    
  5278   293A    FFFF                      NOP                                    
  5279   293C    FFFF                      NOP                                    
  5280   293E    FFFF                      NOP                                    
  5281   2940    FFFF                      NOP                                    
  5282   2942    FFFF                      NOP                                    
  5283   2944    FFFF                      NOP                                    
  5284   2946    FFFF                      NOP                                    
  5285   2948    FFFF                      NOP                                    
  5286   294A    FFFF                      NOP                                    
  5287   294C    FFFF                      NOP                                    
  5288   294E    FFFF                      NOP                                    
  5289   2950    FFFF                      NOP                                    
  5290   2952    FFFF                      NOP                                    
  5291   2954    FFFF                      NOP                                    
  5292   2956    FFFF                      NOP                                    
  5293   2958    FFFF                      NOP                                    
  5294   295A    FFFF                      NOP                                    
  5295   295C    FFFF                      NOP                                    
  5296   295E    FFFF                      NOP                                    
  5297   2960    FFFF                      NOP                                    
  5298   2962    FFFF                      NOP                                    
  5299   2964    FFFF                      NOP                                    
  5300   2966    FFFF                      NOP                                    
  5301   2968    FFFF                      NOP                                    
  5302   296A    FFFF                      NOP                                    
  5303   296C    FFFF                      NOP                                    
  5304   296E    FFFF                      NOP                                    
  5305   2970    FFFF                      NOP                                    
  5306   2972    FFFF                      NOP                                    
  5307   2974    FFFF                      NOP                                    
  5308   2976    FFFF                      NOP                                    
  5309   2978    FFFF                      NOP                                    
  5310   297A    FFFF                      NOP                                    
  5311   297C    FFFF                      NOP                                    
  5312   297E    FFFF                      NOP                                    
  5313   2980    FFFF                      NOP                                    
  5314   2982    FFFF                      NOP                                    
  5315   2984    FFFF                      NOP                                    
  5316   2986    FFFF                      NOP                                    
  5317   2988    FFFF                      NOP                                    
  5318   298A    FFFF                      NOP                                    
  5319   298C    FFFF                      NOP                                    
  5320   298E    FFFF                      NOP                                    
  5321   2990    FFFF                      NOP                                    
  5322   2992    FFFF                      NOP                                    
  5323   2994    FFFF                      NOP                                    
  5324   2996    FFFF                      NOP                                    
  5325   2998    FFFF                      NOP                                    
  5326   299A    FFFF                      NOP                                    
  5327   299C    FFFF                      NOP                                    
  5328   299E    FFFF                      NOP                                    
  5329   29A0    FFFF                      NOP                                    
  5330   29A2    FFFF                      NOP                                    
  5331   29A4    FFFF                      NOP                                    
  5332   29A6    FFFF                      NOP                                    
  5333   29A8    FFFF                      NOP                                    
  5334   29AA    FFFF                      NOP                                    
  5335   29AC    FFFF                      NOP                                    
  5336   29AE    FFFF                      NOP                                    
  5337   29B0    FFFF                      NOP                                    
  5338   29B2    FFFF                      NOP                                    
  5339   29B4    FFFF                      NOP                                    
  5340   29B6    FFFF                      NOP                                    
  5341   29B8    FFFF                      NOP                                    
  5342   29BA    FFFF                      NOP                                    
  5343   29BC    FFFF                      NOP                                    
  5344   29BE    FFFF                      NOP                                    
  5345   29C0    FFFF                      NOP                                    
  5346   29C2    FFFF                      NOP                                    
  5347   29C4    FFFF                      NOP                                    
  5348   29C6    FFFF                      NOP                                    
  5349   29C8    FFFF                      NOP                                    
  5350   29CA    FFFF                      NOP                                    
  5351   29CC    FFFF                      NOP                                    
  5352   29CE    FFFF                      NOP                                    
  5353   29D0    FFFF                      NOP                                    
  5354   29D2    FFFF                      NOP                                    
  5355   29D4    FFFF                      NOP                                    
  5356   29D6    FFFF                      NOP                                    
  5357   29D8    FFFF                      NOP                                    
  5358   29DA    FFFF                      NOP                                    
  5359   29DC    FFFF                      NOP                                    
  5360   29DE    FFFF                      NOP                                    
  5361   29E0    FFFF                      NOP                                    
  5362   29E2    FFFF                      NOP                                    
  5363   29E4    FFFF                      NOP                                    
  5364   29E6    FFFF                      NOP                                    
  5365   29E8    FFFF                      NOP                                    
  5366   29EA    FFFF                      NOP                                    
  5367   29EC    FFFF                      NOP                                    
  5368   29EE    FFFF                      NOP                                    
  5369   29F0    FFFF                      NOP                                    
  5370   29F2    FFFF                      NOP                                    
  5371   29F4    FFFF                      NOP                                    
  5372   29F6    FFFF                      NOP                                    
  5373   29F8    FFFF                      NOP                                    
  5374   29FA    FFFF                      NOP                                    
  5375   29FC    FFFF                      NOP                                    
  5376   29FE    FFFF                      NOP                                    
  5377   2A00    FFFF                      NOP                                    
  5378   2A02    FFFF                      NOP                                    
  5379   2A04    FFFF                      NOP                                    
  5380   2A06    FFFF                      NOP                                    
  5381   2A08    FFFF                      NOP                                    
  5382   2A0A    FFFF                      NOP                                    
  5383   2A0C    FFFF                      NOP                                    
  5384   2A0E    FFFF                      NOP                                    
  5385   2A10    FFFF                      NOP                                    
  5386   2A12    FFFF                      NOP                                    
  5387   2A14    FFFF                      NOP                                    
  5388   2A16    FFFF                      NOP                                    
  5389   2A18    FFFF                      NOP                                    
  5390   2A1A    FFFF                      NOP                                    
  5391   2A1C    FFFF                      NOP                                    
  5392   2A1E    FFFF                      NOP                                    
  5393   2A20    FFFF                      NOP                                    
  5394   2A22    FFFF                      NOP                                    
  5395   2A24    FFFF                      NOP                                    
  5396   2A26    FFFF                      NOP                                    
  5397   2A28    FFFF                      NOP                                    
  5398   2A2A    FFFF                      NOP                                    
  5399   2A2C    FFFF                      NOP                                    
  5400   2A2E    FFFF                      NOP                                    
  5401   2A30    FFFF                      NOP                                    
  5402   2A32    FFFF                      NOP                                    
  5403   2A34    FFFF                      NOP                                    
  5404   2A36    FFFF                      NOP                                    
  5405   2A38    FFFF                      NOP                                    
  5406   2A3A    FFFF                      NOP                                    
  5407   2A3C    FFFF                      NOP                                    
  5408   2A3E    FFFF                      NOP                                    
  5409   2A40    FFFF                      NOP                                    
  5410   2A42    FFFF                      NOP                                    
  5411   2A44    FFFF                      NOP                                    
  5412   2A46    FFFF                      NOP                                    
  5413   2A48    FFFF                      NOP                                    
  5414   2A4A    FFFF                      NOP                                    
  5415   2A4C    FFFF                      NOP                                    
  5416   2A4E    FFFF                      NOP                                    
  5417   2A50    FFFF                      NOP                                    
  5418   2A52    FFFF                      NOP                                    
  5419   2A54    FFFF                      NOP                                    
  5420   2A56    FFFF                      NOP                                    
  5421   2A58    FFFF                      NOP                                    
  5422   2A5A    FFFF                      NOP                                    
  5423   2A5C    FFFF                      NOP                                    
  5424   2A5E    FFFF                      NOP                                    
  5425   2A60    FFFF                      NOP                                    
  5426   2A62    FFFF                      NOP                                    
  5427   2A64    FFFF                      NOP                                    
  5428   2A66    FFFF                      NOP                                    
  5429   2A68    FFFF                      NOP                                    
  5430   2A6A    FFFF                      NOP                                    
  5431   2A6C    FFFF                      NOP                                    
  5432   2A6E    FFFF                      NOP                                    
  5433   2A70    FFFF                      NOP                                    
  5434   2A72    FFFF                      NOP                                    
  5435   2A74    FFFF                      NOP                                    
  5436   2A76    FFFF                      NOP                                    
  5437   2A78    FFFF                      NOP                                    
  5438   2A7A    FFFF                      NOP                                    
  5439   2A7C    FFFF                      NOP                                    
  5440   2A7E    FFFF                      NOP                                    
  5441   2A80    FFFF                      NOP                                    
  5442   2A82    FFFF                      NOP                                    
  5443   2A84    FFFF                      NOP                                    
  5444   2A86    FFFF                      NOP                                    
  5445   2A88    FFFF                      NOP                                    
  5446   2A8A    FFFF                      NOP                                    
  5447   2A8C    FFFF                      NOP                                    
  5448   2A8E    FFFF                      NOP                                    
  5449   2A90    FFFF                      NOP                                    
  5450   2A92    FFFF                      NOP                                    
  5451   2A94    FFFF                      NOP                                    
  5452   2A96    FFFF                      NOP                                    
  5453   2A98    FFFF                      NOP                                    
  5454   2A9A    FFFF                      NOP                                    
  5455   2A9C    FFFF                      NOP                                    
  5456   2A9E    FFFF                      NOP                                    
  5457   2AA0    FFFF                      NOP                                    
  5458   2AA2    FFFF                      NOP                                    
  5459   2AA4    FFFF                      NOP                                    
  5460   2AA6    FFFF                      NOP                                    
  5461   2AA8    FFFF                      NOP                                    
  5462   2AAA    FFFF                      NOP                                    
  5463   2AAC    FFFF                      NOP                                    
  5464   2AAE    FFFF                      NOP                                    
  5465   2AB0    FFFF                      NOP                                    
  5466   2AB2    FFFF                      NOP                                    
  5467   2AB4    FFFF                      NOP                                    
  5468   2AB6    FFFF                      NOP                                    
  5469   2AB8    FFFF                      NOP                                    
  5470   2ABA    FFFF                      NOP                                    
  5471   2ABC    FFFF                      NOP                                    
  5472   2ABE    FFFF                      NOP                                    
  5473   2AC0    FFFF                      NOP                                    
  5474   2AC2    FFFF                      NOP                                    
  5475   2AC4    FFFF                      NOP                                    
  5476   2AC6    FFFF                      NOP                                    
  5477   2AC8    FFFF                      NOP                                    
  5478   2ACA    FFFF                      NOP                                    
  5479   2ACC    FFFF                      NOP                                    
  5480   2ACE    FFFF                      NOP                                    
  5481   2AD0    FFFF                      NOP                                    
  5482   2AD2    FFFF                      NOP                                    
  5483   2AD4    FFFF                      NOP                                    
  5484   2AD6    FFFF                      NOP                                    
  5485   2AD8    FFFF                      NOP                                    
  5486   2ADA    FFFF                      NOP                                    
  5487   2ADC    FFFF                      NOP                                    
  5488   2ADE    FFFF                      NOP                                    
  5489   2AE0    FFFF                      NOP                                    
  5490   2AE2    FFFF                      NOP                                    
  5491   2AE4    FFFF                      NOP                                    
  5492   2AE6    FFFF                      NOP                                    
  5493   2AE8    FFFF                      NOP                                    
  5494   2AEA    FFFF                      NOP                                    
  5495   2AEC    FFFF                      NOP                                    
  5496   2AEE    FFFF                      NOP                                    
  5497   2AF0    FFFF                      NOP                                    
  5498   2AF2    FFFF                      NOP                                    
  5499   2AF4    FFFF                      NOP                                    
  5500   2AF6    FFFF                      NOP                                    
  5501   2AF8    FFFF                      NOP                                    
  5502   2AFA    FFFF                      NOP                                    
  5503   2AFC    FFFF                      NOP                                    
  5504   2AFE    FFFF                      NOP                                    
  5505   2B00    FFFF                      NOP                                    
  5506   2B02    FFFF                      NOP                                    
  5507   2B04    FFFF                      NOP                                    
  5508   2B06    FFFF                      NOP                                    
  5509   2B08    FFFF                      NOP                                    
  5510   2B0A    FFFF                      NOP                                    
  5511   2B0C    FFFF                      NOP                                    
  5512   2B0E    FFFF                      NOP                                    
  5513   2B10    FFFF                      NOP                                    
  5514   2B12    FFFF                      NOP                                    
  5515   2B14    FFFF                      NOP                                    
  5516   2B16    FFFF                      NOP                                    
  5517   2B18    FFFF                      NOP                                    
  5518   2B1A    FFFF                      NOP                                    
  5519   2B1C    FFFF                      NOP                                    
  5520   2B1E    FFFF                      NOP                                    
  5521   2B20    FFFF                      NOP                                    
  5522   2B22    FFFF                      NOP                                    
  5523   2B24    FFFF                      NOP                                    
  5524   2B26    FFFF                      NOP                                    
  5525   2B28    FFFF                      NOP                                    
  5526   2B2A    FFFF                      NOP                                    
  5527   2B2C    FFFF                      NOP                                    
  5528   2B2E    FFFF                      NOP                                    
  5529   2B30    FFFF                      NOP                                    
  5530   2B32    FFFF                      NOP                                    
  5531   2B34    FFFF                      NOP                                    
  5532   2B36    FFFF                      NOP                                    
  5533   2B38    FFFF                      NOP                                    
  5534   2B3A    FFFF                      NOP                                    
  5535   2B3C    FFFF                      NOP                                    
  5536   2B3E    FFFF                      NOP                                    
  5537   2B40    FFFF                      NOP                                    
  5538   2B42    FFFF                      NOP                                    
  5539   2B44    FFFF                      NOP                                    
  5540   2B46    FFFF                      NOP                                    
  5541   2B48    FFFF                      NOP                                    
  5542   2B4A    FFFF                      NOP                                    
  5543   2B4C    FFFF                      NOP                                    
  5544   2B4E    FFFF                      NOP                                    
  5545   2B50    FFFF                      NOP                                    
  5546   2B52    FFFF                      NOP                                    
  5547   2B54    FFFF                      NOP                                    
  5548   2B56    FFFF                      NOP                                    
  5549   2B58    FFFF                      NOP                                    
  5550   2B5A    FFFF                      NOP                                    
  5551   2B5C    FFFF                      NOP                                    
  5552   2B5E    FFFF                      NOP                                    
  5553   2B60    FFFF                      NOP                                    
  5554   2B62    FFFF                      NOP                                    
  5555   2B64    FFFF                      NOP                                    
  5556   2B66    FFFF                      NOP                                    
  5557   2B68    FFFF                      NOP                                    
  5558   2B6A    FFFF                      NOP                                    
  5559   2B6C    FFFF                      NOP                                    
  5560   2B6E    FFFF                      NOP                                    
  5561   2B70    FFFF                      NOP                                    
  5562   2B72    FFFF                      NOP                                    
  5563   2B74    FFFF                      NOP                                    
  5564   2B76    FFFF                      NOP                                    
  5565   2B78    FFFF                      NOP                                    
  5566   2B7A    FFFF                      NOP                                    
  5567   2B7C    FFFF                      NOP                                    
  5568   2B7E    FFFF                      NOP                                    
  5569   2B80    FFFF                      NOP                                    
  5570   2B82    FFFF                      NOP                                    
  5571   2B84    FFFF                      NOP                                    
  5572   2B86    FFFF                      NOP                                    
  5573   2B88    FFFF                      NOP                                    
  5574   2B8A    FFFF                      NOP                                    
  5575   2B8C    FFFF                      NOP                                    
  5576   2B8E    FFFF                      NOP                                    
  5577   2B90    FFFF                      NOP                                    
  5578   2B92    FFFF                      NOP                                    
  5579   2B94    FFFF                      NOP                                    
  5580   2B96    FFFF                      NOP                                    
  5581   2B98    FFFF                      NOP                                    
  5582   2B9A    FFFF                      NOP                                    
  5583   2B9C    FFFF                      NOP                                    
  5584   2B9E    FFFF                      NOP                                    
  5585   2BA0    FFFF                      NOP                                    
  5586   2BA2    FFFF                      NOP                                    
  5587   2BA4    FFFF                      NOP                                    
  5588   2BA6    FFFF                      NOP                                    
  5589   2BA8    FFFF                      NOP                                    
  5590   2BAA    FFFF                      NOP                                    
  5591   2BAC    FFFF                      NOP                                    
  5592   2BAE    FFFF                      NOP                                    
  5593   2BB0    FFFF                      NOP                                    
  5594   2BB2    FFFF                      NOP                                    
  5595   2BB4    FFFF                      NOP                                    
  5596   2BB6    FFFF                      NOP                                    
  5597   2BB8    FFFF                      NOP                                    
  5598   2BBA    FFFF                      NOP                                    
  5599   2BBC    FFFF                      NOP                                    
  5600   2BBE    FFFF                      NOP                                    
  5601   2BC0    FFFF                      NOP                                    
  5602   2BC2    FFFF                      NOP                                    
  5603   2BC4    FFFF                      NOP                                    
  5604   2BC6    FFFF                      NOP                                    
  5605   2BC8    FFFF                      NOP                                    
  5606   2BCA    FFFF                      NOP                                    
  5607   2BCC    FFFF                      NOP                                    
  5608   2BCE    FFFF                      NOP                                    
  5609   2BD0    FFFF                      NOP                                    
  5610   2BD2    FFFF                      NOP                                    
  5611   2BD4    FFFF                      NOP                                    
  5612   2BD6    FFFF                      NOP                                    
  5613   2BD8    FFFF                      NOP                                    
  5614   2BDA    FFFF                      NOP                                    
  5615   2BDC    FFFF                      NOP                                    
  5616   2BDE    FFFF                      NOP                                    
  5617   2BE0    FFFF                      NOP                                    
  5618   2BE2    FFFF                      NOP                                    
  5619   2BE4    FFFF                      NOP                                    
  5620   2BE6    FFFF                      NOP                                    
  5621   2BE8    FFFF                      NOP                                    
  5622   2BEA    FFFF                      NOP                                    
  5623   2BEC    FFFF                      NOP                                    
  5624   2BEE    FFFF                      NOP                                    
  5625   2BF0    FFFF                      NOP                                    
  5626   2BF2    FFFF                      NOP                                    
  5627   2BF4    FFFF                      NOP                                    
  5628   2BF6    FFFF                      NOP                                    
  5629   2BF8    FFFF                      NOP                                    
  5630   2BFA    FFFF                      NOP                                    
  5631   2BFC    FFFF                      NOP                                    
  5632   2BFE    FFFF                      NOP                                    
  5633   2C00    FFFF                      NOP                                    
  5634   2C02    FFFF                      NOP                                    
  5635   2C04    FFFF                      NOP                                    
  5636   2C06    FFFF                      NOP                                    
  5637   2C08    FFFF                      NOP                                    
  5638   2C0A    FFFF                      NOP                                    
  5639   2C0C    FFFF                      NOP                                    
  5640   2C0E    FFFF                      NOP                                    
  5641   2C10    FFFF                      NOP                                    
  5642   2C12    FFFF                      NOP                                    
  5643   2C14    FFFF                      NOP                                    
  5644   2C16    FFFF                      NOP                                    
  5645   2C18    FFFF                      NOP                                    
  5646   2C1A    FFFF                      NOP                                    
  5647   2C1C    FFFF                      NOP                                    
  5648   2C1E    FFFF                      NOP                                    
  5649   2C20    FFFF                      NOP                                    
  5650   2C22    FFFF                      NOP                                    
  5651   2C24    FFFF                      NOP                                    
  5652   2C26    FFFF                      NOP                                    
  5653   2C28    FFFF                      NOP                                    
  5654   2C2A    FFFF                      NOP                                    
  5655   2C2C    FFFF                      NOP                                    
  5656   2C2E    FFFF                      NOP                                    
  5657   2C30    FFFF                      NOP                                    
  5658   2C32    FFFF                      NOP                                    
  5659   2C34    FFFF                      NOP                                    
  5660   2C36    FFFF                      NOP                                    
  5661   2C38    FFFF                      NOP                                    
  5662   2C3A    FFFF                      NOP                                    
  5663   2C3C    FFFF                      NOP                                    
  5664   2C3E    FFFF                      NOP                                    
  5665   2C40    FFFF                      NOP                                    
  5666   2C42    FFFF                      NOP                                    
  5667   2C44    FFFF                      NOP                                    
  5668   2C46    FFFF                      NOP                                    
  5669   2C48    FFFF                      NOP                                    
  5670   2C4A    FFFF                      NOP                                    
  5671   2C4C    FFFF                      NOP                                    
  5672   2C4E    FFFF                      NOP                                    
  5673   2C50    FFFF                      NOP                                    
  5674   2C52    FFFF                      NOP                                    
  5675   2C54    FFFF                      NOP                                    
  5676   2C56    FFFF                      NOP                                    
  5677   2C58    FFFF                      NOP                                    
  5678   2C5A    FFFF                      NOP                                    
  5679   2C5C    FFFF                      NOP                                    
  5680   2C5E    FFFF                      NOP                                    
  5681   2C60    FFFF                      NOP                                    
  5682   2C62    FFFF                      NOP                                    
  5683   2C64    FFFF                      NOP                                    
  5684   2C66    FFFF                      NOP                                    
  5685   2C68    FFFF                      NOP                                    
  5686   2C6A    FFFF                      NOP                                    
  5687   2C6C    FFFF                      NOP                                    
  5688   2C6E    FFFF                      NOP                                    
  5689   2C70    FFFF                      NOP                                    
  5690   2C72    FFFF                      NOP                                    
  5691   2C74    FFFF                      NOP                                    
  5692   2C76    FFFF                      NOP                                    
  5693   2C78    FFFF                      NOP                                    
  5694   2C7A    FFFF                      NOP                                    
  5695   2C7C    FFFF                      NOP                                    
  5696   2C7E    FFFF                      NOP                                    
  5697   2C80    FFFF                      NOP                                    
  5698   2C82    FFFF                      NOP                                    
  5699   2C84    FFFF                      NOP                                    
  5700   2C86    FFFF                      NOP                                    
  5701   2C88    FFFF                      NOP                                    
  5702   2C8A    FFFF                      NOP                                    
  5703   2C8C    FFFF                      NOP                                    
  5704   2C8E    FFFF                      NOP                                    
  5705   2C90    FFFF                      NOP                                    
  5706   2C92    FFFF                      NOP                                    
  5707   2C94    FFFF                      NOP                                    
  5708   2C96    FFFF                      NOP                                    
  5709   2C98    FFFF                      NOP                                    
  5710   2C9A    FFFF                      NOP                                    
  5711   2C9C    FFFF                      NOP                                    
  5712   2C9E    FFFF                      NOP                                    
  5713   2CA0    FFFF                      NOP                                    
  5714   2CA2    FFFF                      NOP                                    
  5715   2CA4    FFFF                      NOP                                    
  5716   2CA6    FFFF                      NOP                                    
  5717   2CA8    FFFF                      NOP                                    
  5718   2CAA    FFFF                      NOP                                    
  5719   2CAC    FFFF                      NOP                                    
  5720   2CAE    FFFF                      NOP                                    
  5721   2CB0    FFFF                      NOP                                    
  5722   2CB2    FFFF                      NOP                                    
  5723   2CB4    FFFF                      NOP                                    
  5724   2CB6    FFFF                      NOP                                    
  5725   2CB8    FFFF                      NOP                                    
  5726   2CBA    FFFF                      NOP                                    
  5727   2CBC    FFFF                      NOP                                    
  5728   2CBE    FFFF                      NOP                                    
  5729   2CC0    FFFF                      NOP                                    
  5730   2CC2    FFFF                      NOP                                    
  5731   2CC4    FFFF                      NOP                                    
  5732   2CC6    FFFF                      NOP                                    
  5733   2CC8    FFFF                      NOP                                    
  5734   2CCA    FFFF                      NOP                                    
  5735   2CCC    FFFF                      NOP                                    
  5736   2CCE    FFFF                      NOP                                    
  5737   2CD0    FFFF                      NOP                                    
  5738   2CD2    FFFF                      NOP                                    
  5739   2CD4    FFFF                      NOP                                    
  5740   2CD6    FFFF                      NOP                                    
  5741   2CD8    FFFF                      NOP                                    
  5742   2CDA    FFFF                      NOP                                    
  5743   2CDC    FFFF                      NOP                                    
  5744   2CDE    FFFF                      NOP                                    
  5745   2CE0    FFFF                      NOP                                    
  5746   2CE2    FFFF                      NOP                                    
  5747   2CE4    FFFF                      NOP                                    
  5748   2CE6    FFFF                      NOP                                    
  5749   2CE8    FFFF                      NOP                                    
  5750   2CEA    FFFF                      NOP                                    
  5751   2CEC    FFFF                      NOP                                    
  5752   2CEE    FFFF                      NOP                                    
  5753   2CF0    FFFF                      NOP                                    
  5754   2CF2    FFFF                      NOP                                    
  5755   2CF4    FFFF                      NOP                                    
  5756   2CF6    FFFF                      NOP                                    
  5757   2CF8    FFFF                      NOP                                    
  5758   2CFA    FFFF                      NOP                                    
  5759   2CFC    FFFF                      NOP                                    
  5760   2CFE    FFFF                      NOP                                    
  5761   2D00    FFFF                      NOP                                    
  5762   2D02    FFFF                      NOP                                    
  5763   2D04    FFFF                      NOP                                    
  5764   2D06    FFFF                      NOP                                    
  5765   2D08    FFFF                      NOP                                    
  5766   2D0A    FFFF                      NOP                                    
  5767   2D0C    FFFF                      NOP                                    
  5768   2D0E    FFFF                      NOP                                    
  5769   2D10    FFFF                      NOP                                    
  5770   2D12    FFFF                      NOP                                    
  5771   2D14    FFFF                      NOP                                    
  5772   2D16    FFFF                      NOP                                    
  5773   2D18    FFFF                      NOP                                    
  5774   2D1A    FFFF                      NOP                                    
  5775   2D1C    FFFF                      NOP                                    
  5776   2D1E    FFFF                      NOP                                    
  5777   2D20    FFFF                      NOP                                    
  5778   2D22    FFFF                      NOP                                    
  5779   2D24    FFFF                      NOP                                    
  5780   2D26    FFFF                      NOP                                    
  5781   2D28    FFFF                      NOP                                    
  5782   2D2A    FFFF                      NOP                                    
  5783   2D2C    FFFF                      NOP                                    
  5784   2D2E    FFFF                      NOP                                    
  5785   2D30    FFFF                      NOP                                    
  5786   2D32    FFFF                      NOP                                    
  5787   2D34    FFFF                      NOP                                    
  5788   2D36    FFFF                      NOP                                    
  5789   2D38    FFFF                      NOP                                    
  5790   2D3A    FFFF                      NOP                                    
  5791   2D3C    FFFF                      NOP                                    
  5792   2D3E    FFFF                      NOP                                    
  5793   2D40    FFFF                      NOP                                    
  5794   2D42    FFFF                      NOP                                    
  5795   2D44    FFFF                      NOP                                    
  5796   2D46    FFFF                      NOP                                    
  5797   2D48    FFFF                      NOP                                    
  5798   2D4A    FFFF                      NOP                                    
  5799   2D4C    FFFF                      NOP                                    
  5800   2D4E    FFFF                      NOP                                    
  5801   2D50    FFFF                      NOP                                    
  5802   2D52    FFFF                      NOP                                    
  5803   2D54    FFFF                      NOP                                    
  5804   2D56    FFFF                      NOP                                    
  5805   2D58    FFFF                      NOP                                    
  5806   2D5A    FFFF                      NOP                                    
  5807   2D5C    FFFF                      NOP                                    
  5808   2D5E    FFFF                      NOP                                    
  5809   2D60    FFFF                      NOP                                    
  5810   2D62    FFFF                      NOP                                    
  5811   2D64    FFFF                      NOP                                    
  5812   2D66    FFFF                      NOP                                    
  5813   2D68    FFFF                      NOP                                    
  5814   2D6A    FFFF                      NOP                                    
  5815   2D6C    FFFF                      NOP                                    
  5816   2D6E    FFFF                      NOP                                    
  5817   2D70    FFFF                      NOP                                    
  5818   2D72    FFFF                      NOP                                    
  5819   2D74    FFFF                      NOP                                    
  5820   2D76    FFFF                      NOP                                    
  5821   2D78    FFFF                      NOP                                    
  5822   2D7A    FFFF                      NOP                                    
  5823   2D7C    FFFF                      NOP                                    
  5824   2D7E    FFFF                      NOP                                    
  5825   2D80    FFFF                      NOP                                    
  5826   2D82    FFFF                      NOP                                    
  5827   2D84    FFFF                      NOP                                    
  5828   2D86    FFFF                      NOP                                    
  5829   2D88    FFFF                      NOP                                    
  5830   2D8A    FFFF                      NOP                                    
  5831   2D8C    FFFF                      NOP                                    
  5832   2D8E    FFFF                      NOP                                    
  5833   2D90    FFFF                      NOP                                    
  5834   2D92    FFFF                      NOP                                    
  5835   2D94    FFFF                      NOP                                    
  5836   2D96    FFFF                      NOP                                    
  5837   2D98    FFFF                      NOP                                    
  5838   2D9A    FFFF                      NOP                                    
  5839   2D9C    FFFF                      NOP                                    
  5840   2D9E    FFFF                      NOP                                    
  5841   2DA0    FFFF                      NOP                                    
  5842   2DA2    FFFF                      NOP                                    
  5843   2DA4    FFFF                      NOP                                    
  5844   2DA6    FFFF                      NOP                                    
  5845   2DA8    FFFF                      NOP                                    
  5846   2DAA    FFFF                      NOP                                    
  5847   2DAC    FFFF                      NOP                                    
  5848   2DAE    FFFF                      NOP                                    
  5849   2DB0    FFFF                      NOP                                    
  5850   2DB2    FFFF                      NOP                                    
  5851   2DB4    FFFF                      NOP                                    
  5852   2DB6    FFFF                      NOP                                    
  5853   2DB8    FFFF                      NOP                                    
  5854   2DBA    FFFF                      NOP                                    
  5855   2DBC    FFFF                      NOP                                    
  5856   2DBE    FFFF                      NOP                                    
  5857   2DC0    FFFF                      NOP                                    
  5858   2DC2    FFFF                      NOP                                    
  5859   2DC4    FFFF                      NOP                                    
  5860   2DC6    FFFF                      NOP                                    
  5861   2DC8    FFFF                      NOP                                    
  5862   2DCA    FFFF                      NOP                                    
  5863   2DCC    FFFF                      NOP                                    
  5864   2DCE    FFFF                      NOP                                    
  5865   2DD0    FFFF                      NOP                                    
  5866   2DD2    FFFF                      NOP                                    
  5867   2DD4    FFFF                      NOP                                    
  5868   2DD6    FFFF                      NOP                                    
  5869   2DD8    FFFF                      NOP                                    
  5870   2DDA    FFFF                      NOP                                    
  5871   2DDC    FFFF                      NOP                                    
  5872   2DDE    FFFF                      NOP                                    
  5873   2DE0    FFFF                      NOP                                    
  5874   2DE2    FFFF                      NOP                                    
  5875   2DE4    FFFF                      NOP                                    
  5876   2DE6    FFFF                      NOP                                    
  5877   2DE8    FFFF                      NOP                                    
  5878   2DEA    FFFF                      NOP                                    
  5879   2DEC    FFFF                      NOP                                    
  5880   2DEE    FFFF                      NOP                                    
  5881   2DF0    FFFF                      NOP                                    
  5882   2DF2    FFFF                      NOP                                    
  5883   2DF4    FFFF                      NOP                                    
  5884   2DF6    FFFF                      NOP                                    
  5885   2DF8    FFFF                      NOP                                    
  5886   2DFA    FFFF                      NOP                                    
  5887   2DFC    FFFF                      NOP                                    
  5888   2DFE    FFFF                      NOP                                    
  5889   2E00    FFFF                      NOP                                    
  5890   2E02    FFFF                      NOP                                    
  5891   2E04    FFFF                      NOP                                    
  5892   2E06    FFFF                      NOP                                    
  5893   2E08    FFFF                      NOP                                    
  5894   2E0A    FFFF                      NOP                                    
  5895   2E0C    FFFF                      NOP                                    
  5896   2E0E    FFFF                      NOP                                    
  5897   2E10    FFFF                      NOP                                    
  5898   2E12    FFFF                      NOP                                    
  5899   2E14    FFFF                      NOP                                    
  5900   2E16    FFFF                      NOP                                    
  5901   2E18    FFFF                      NOP                                    
  5902   2E1A    FFFF                      NOP                                    
  5903   2E1C    FFFF                      NOP                                    
  5904   2E1E    FFFF                      NOP                                    
  5905   2E20    FFFF                      NOP                                    
  5906   2E22    FFFF                      NOP                                    
  5907   2E24    FFFF                      NOP                                    
  5908   2E26    FFFF                      NOP                                    
  5909   2E28    FFFF                      NOP                                    
  5910   2E2A    FFFF                      NOP                                    
  5911   2E2C    FFFF                      NOP                                    
  5912   2E2E    FFFF                      NOP                                    
  5913   2E30    FFFF                      NOP                                    
  5914   2E32    FFFF                      NOP                                    
  5915   2E34    FFFF                      NOP                                    
  5916   2E36    FFFF                      NOP                                    
  5917   2E38    FFFF                      NOP                                    
  5918   2E3A    FFFF                      NOP                                    
  5919   2E3C    FFFF                      NOP                                    
  5920   2E3E    FFFF                      NOP                                    
  5921   2E40    FFFF                      NOP                                    
  5922   2E42    FFFF                      NOP                                    
  5923   2E44    FFFF                      NOP                                    
  5924   2E46    FFFF                      NOP                                    
  5925   2E48    FFFF                      NOP                                    
  5926   2E4A    FFFF                      NOP                                    
  5927   2E4C    FFFF                      NOP                                    
  5928   2E4E    FFFF                      NOP                                    
  5929   2E50    FFFF                      NOP                                    
  5930   2E52    FFFF                      NOP                                    
  5931   2E54    FFFF                      NOP                                    
  5932   2E56    FFFF                      NOP                                    
  5933   2E58    FFFF                      NOP                                    
  5934   2E5A    FFFF                      NOP                                    
  5935   2E5C    FFFF                      NOP                                    
  5936   2E5E    FFFF                      NOP                                    
  5937   2E60    FFFF                      NOP                                    
  5938   2E62    FFFF                      NOP                                    
  5939   2E64    FFFF                      NOP                                    
  5940   2E66    FFFF                      NOP                                    
  5941   2E68    FFFF                      NOP                                    
  5942   2E6A    FFFF                      NOP                                    
  5943   2E6C    FFFF                      NOP                                    
  5944   2E6E    FFFF                      NOP                                    
  5945   2E70    FFFF                      NOP                                    
  5946   2E72    FFFF                      NOP                                    
  5947   2E74    FFFF                      NOP                                    
  5948   2E76    FFFF                      NOP                                    
  5949   2E78    FFFF                      NOP                                    
  5950   2E7A    FFFF                      NOP                                    
  5951   2E7C    FFFF                      NOP                                    
  5952   2E7E    FFFF                      NOP                                    
  5953   2E80    FFFF                      NOP                                    
  5954   2E82    FFFF                      NOP                                    
  5955   2E84    FFFF                      NOP                                    
  5956   2E86    FFFF                      NOP                                    
  5957   2E88    FFFF                      NOP                                    
  5958   2E8A    FFFF                      NOP                                    
  5959   2E8C    FFFF                      NOP                                    
  5960   2E8E    FFFF                      NOP                                    
  5961   2E90    FFFF                      NOP                                    
  5962   2E92    FFFF                      NOP                                    
  5963   2E94    FFFF                      NOP                                    
  5964   2E96    FFFF                      NOP                                    
  5965   2E98    FFFF                      NOP                                    
  5966   2E9A    FFFF                      NOP                                    
  5967   2E9C    FFFF                      NOP                                    
  5968   2E9E    FFFF                      NOP                                    
  5969   2EA0    FFFF                      NOP                                    
  5970   2EA2    FFFF                      NOP                                    
  5971   2EA4    FFFF                      NOP                                    
  5972   2EA6    FFFF                      NOP                                    
  5973   2EA8    FFFF                      NOP                                    
  5974   2EAA    FFFF                      NOP                                    
  5975   2EAC    FFFF                      NOP                                    
  5976   2EAE    FFFF                      NOP                                    
  5977   2EB0    FFFF                      NOP                                    
  5978   2EB2    FFFF                      NOP                                    
  5979   2EB4    FFFF                      NOP                                    
  5980   2EB6    FFFF                      NOP                                    
  5981   2EB8    FFFF                      NOP                                    
  5982   2EBA    FFFF                      NOP                                    
  5983   2EBC    FFFF                      NOP                                    
  5984   2EBE    FFFF                      NOP                                    
  5985   2EC0    FFFF                      NOP                                    
  5986   2EC2    FFFF                      NOP                                    
  5987   2EC4    FFFF                      NOP                                    
  5988   2EC6    FFFF                      NOP                                    
  5989   2EC8    FFFF                      NOP                                    
  5990   2ECA    FFFF                      NOP                                    
  5991   2ECC    FFFF                      NOP                                    
  5992   2ECE    FFFF                      NOP                                    
  5993   2ED0    FFFF                      NOP                                    
  5994   2ED2    FFFF                      NOP                                    
  5995   2ED4    FFFF                      NOP                                    
  5996   2ED6    FFFF                      NOP                                    
  5997   2ED8    FFFF                      NOP                                    
  5998   2EDA    FFFF                      NOP                                    
  5999   2EDC    FFFF                      NOP                                    
  6000   2EDE    FFFF                      NOP                                    
  6001   2EE0    FFFF                      NOP                                    
  6002   2EE2    FFFF                      NOP                                    
  6003   2EE4    FFFF                      NOP                                    
  6004   2EE6    FFFF                      NOP                                    
  6005   2EE8    FFFF                      NOP                                    
  6006   2EEA    FFFF                      NOP                                    
  6007   2EEC    FFFF                      NOP                                    
  6008   2EEE    FFFF                      NOP                                    
  6009   2EF0    FFFF                      NOP                                    
  6010   2EF2    FFFF                      NOP                                    
  6011   2EF4    FFFF                      NOP                                    
  6012   2EF6    FFFF                      NOP                                    
  6013   2EF8    FFFF                      NOP                                    
  6014   2EFA    FFFF                      NOP                                    
  6015   2EFC    FFFF                      NOP                                    
  6016   2EFE    FFFF                      NOP                                    
  6017   2F00    FFFF                      NOP                                    
  6018   2F02    FFFF                      NOP                                    
  6019   2F04    FFFF                      NOP                                    
  6020   2F06    FFFF                      NOP                                    
  6021   2F08    FFFF                      NOP                                    
  6022   2F0A    FFFF                      NOP                                    
  6023   2F0C    FFFF                      NOP                                    
  6024   2F0E    FFFF                      NOP                                    
  6025   2F10    FFFF                      NOP                                    
  6026   2F12    FFFF                      NOP                                    
  6027   2F14    FFFF                      NOP                                    
  6028   2F16    FFFF                      NOP                                    
  6029   2F18    FFFF                      NOP                                    
  6030   2F1A    FFFF                      NOP                                    
  6031   2F1C    FFFF                      NOP                                    
  6032   2F1E    FFFF                      NOP                                    
  6033   2F20    FFFF                      NOP                                    
  6034   2F22    FFFF                      NOP                                    
  6035   2F24    FFFF                      NOP                                    
  6036   2F26    FFFF                      NOP                                    
  6037   2F28    FFFF                      NOP                                    
  6038   2F2A    FFFF                      NOP                                    
  6039   2F2C    FFFF                      NOP                                    
  6040   2F2E    FFFF                      NOP                                    
  6041   2F30    FFFF                      NOP                                    
  6042   2F32    FFFF                      NOP                                    
  6043   2F34    FFFF                      NOP                                    
  6044   2F36    FFFF                      NOP                                    
  6045   2F38    FFFF                      NOP                                    
  6046   2F3A    FFFF                      NOP                                    
  6047   2F3C    FFFF                      NOP                                    
  6048   2F3E    FFFF                      NOP                                    
  6049   2F40    FFFF                      NOP                                    
  6050   2F42    FFFF                      NOP                                    
  6051   2F44    FFFF                      NOP                                    
  6052   2F46    FFFF                      NOP                                    
  6053   2F48    FFFF                      NOP                                    
  6054   2F4A    FFFF                      NOP                                    
  6055   2F4C    FFFF                      NOP                                    
  6056   2F4E    FFFF                      NOP                                    
  6057   2F50    FFFF                      NOP                                    
  6058   2F52    FFFF                      NOP                                    
  6059   2F54    FFFF                      NOP                                    
  6060   2F56    FFFF                      NOP                                    
  6061   2F58    FFFF                      NOP                                    
  6062   2F5A    FFFF                      NOP                                    
  6063   2F5C    FFFF                      NOP                                    
  6064   2F5E    FFFF                      NOP                                    
  6065   2F60    FFFF                      NOP                                    
  6066   2F62    FFFF                      NOP                                    
  6067   2F64    FFFF                      NOP                                    
  6068   2F66    FFFF                      NOP                                    
  6069   2F68    FFFF                      NOP                                    
  6070   2F6A    FFFF                      NOP                                    
  6071   2F6C    FFFF                      NOP                                    
  6072   2F6E    FFFF                      NOP                                    
  6073   2F70    FFFF                      NOP                                    
  6074   2F72    FFFF                      NOP                                    
  6075   2F74    FFFF                      NOP                                    
  6076   2F76    FFFF                      NOP                                    
  6077   2F78    FFFF                      NOP                                    
  6078   2F7A    FFFF                      NOP                                    
  6079   2F7C    FFFF                      NOP                                    
  6080   2F7E    FFFF                      NOP                                    
  6081   2F80    FFFF                      NOP                                    
  6082   2F82    FFFF                      NOP                                    
  6083   2F84    FFFF                      NOP                                    
  6084   2F86    FFFF                      NOP                                    
  6085   2F88    FFFF                      NOP                                    
  6086   2F8A    FFFF                      NOP                                    
  6087   2F8C    FFFF                      NOP                                    
  6088   2F8E    FFFF                      NOP                                    
  6089   2F90    FFFF                      NOP                                    
  6090   2F92    FFFF                      NOP                                    
  6091   2F94    FFFF                      NOP                                    
  6092   2F96    FFFF                      NOP                                    
  6093   2F98    FFFF                      NOP                                    
  6094   2F9A    FFFF                      NOP                                    
  6095   2F9C    FFFF                      NOP                                    
  6096   2F9E    FFFF                      NOP                                    
  6097   2FA0    FFFF                      NOP                                    
  6098   2FA2    FFFF                      NOP                                    
  6099   2FA4    FFFF                      NOP                                    
  6100   2FA6    FFFF                      NOP                                    
  6101   2FA8    FFFF                      NOP                                    
  6102   2FAA    FFFF                      NOP                                    
  6103   2FAC    FFFF                      NOP                                    
  6104   2FAE    FFFF                      NOP                                    
  6105   2FB0    FFFF                      NOP                                    
  6106   2FB2    FFFF                      NOP                                    
  6107   2FB4    FFFF                      NOP                                    
  6108   2FB6    FFFF                      NOP                                    
  6109   2FB8    FFFF                      NOP                                    
  6110   2FBA    FFFF                      NOP                                    
  6111   2FBC    FFFF                      NOP                                    
  6112   2FBE    FFFF                      NOP                                    
  6113   2FC0    FFFF                      NOP                                    
  6114   2FC2    FFFF                      NOP                                    
  6115   2FC4    FFFF                      NOP                                    
  6116   2FC6    FFFF                      NOP                                    
  6117   2FC8    FFFF                      NOP                                    
  6118   2FCA    FFFF                      NOP                                    
  6119   2FCC    FFFF                      NOP                                    
  6120   2FCE    FFFF                      NOP                                    
  6121   2FD0    FFFF                      NOP                                    
  6122   2FD2    FFFF                      NOP                                    
  6123   2FD4    FFFF                      NOP                                    
  6124   2FD6    FFFF                      NOP                                    
  6125   2FD8    FFFF                      NOP                                    
  6126   2FDA    FFFF                      NOP                                    
  6127   2FDC    FFFF                      NOP                                    
  6128   2FDE    FFFF                      NOP                                    
  6129   2FE0    FFFF                      NOP                                    
  6130   2FE2    FFFF                      NOP                                    
  6131   2FE4    FFFF                      NOP                                    
  6132   2FE6    FFFF                      NOP                                    
  6133   2FE8    FFFF                      NOP                                    
  6134   2FEA    FFFF                      NOP                                    
  6135   2FEC    FFFF                      NOP                                    
  6136   2FEE    FFFF                      NOP                                    
  6137   2FF0    FFFF                      NOP                                    
  6138   2FF2    FFFF                      NOP                                    
  6139   2FF4    FFFF                      NOP                                    
  6140   2FF6    FFFF                      NOP                                    
  6141   2FF8    FFFF                      NOP                                    
  6142   2FFA    FFFF                      NOP                                    
  6143   2FFC    FFFF                      NOP                                    
  6144   2FFE    FFFF                      NOP                                    
  6145   3000    FFFF                      NOP                                    
  6146   3002    FFFF                      NOP                                    
  6147   3004    FFFF                      NOP                                    
  6148   3006    FFFF                      NOP                                    
  6149   3008    FFFF                      NOP                                    
  6150   300A    FFFF                      NOP                                    
  6151   300C    FFFF                      NOP                                    
  6152   300E    FFFF                      NOP                                    
  6153   3010    FFFF                      NOP                                    
  6154   3012    FFFF                      NOP                                    
  6155   3014    FFFF                      NOP                                    
  6156   3016    FFFF                      NOP                                    
  6157   3018    FFFF                      NOP                                    
  6158   301A    FFFF                      NOP                                    
  6159   301C    FFFF                      NOP                                    
  6160   301E    FFFF                      NOP                                    
  6161   3020    FFFF                      NOP                                    
  6162   3022    FFFF                      NOP                                    
  6163   3024    FFFF                      NOP                                    
  6164   3026    FFFF                      NOP                                    
  6165   3028    FFFF                      NOP                                    
  6166   302A    FFFF                      NOP                                    
  6167   302C    FFFF                      NOP                                    
  6168   302E    FFFF                      NOP                                    
  6169   3030    FFFF                      NOP                                    
  6170   3032    FFFF                      NOP                                    
  6171   3034    FFFF                      NOP                                    
  6172   3036    FFFF                      NOP                                    
  6173   3038    FFFF                      NOP                                    
  6174   303A    FFFF                      NOP                                    
  6175   303C    FFFF                      NOP                                    
  6176   303E    FFFF                      NOP                                    
  6177   3040    FFFF                      NOP                                    
  6178   3042    FFFF                      NOP                                    
  6179   3044    FFFF                      NOP                                    
  6180   3046    FFFF                      NOP                                    
  6181   3048    FFFF                      NOP                                    
  6182   304A    FFFF                      NOP                                    
  6183   304C    FFFF                      NOP                                    
  6184   304E    FFFF                      NOP                                    
  6185   3050    FFFF                      NOP                                    
  6186   3052    FFFF                      NOP                                    
  6187   3054    FFFF                      NOP                                    
  6188   3056    FFFF                      NOP                                    
  6189   3058    FFFF                      NOP                                    
  6190   305A    FFFF                      NOP                                    
  6191   305C    FFFF                      NOP                                    
  6192   305E    FFFF                      NOP                                    
  6193   3060    FFFF                      NOP                                    
  6194   3062    FFFF                      NOP                                    
  6195   3064    FFFF                      NOP                                    
  6196   3066    FFFF                      NOP                                    
  6197   3068    FFFF                      NOP                                    
  6198   306A    FFFF                      NOP                                    
  6199   306C    FFFF                      NOP                                    
  6200   306E    FFFF                      NOP                                    
  6201   3070    FFFF                      NOP                                    
  6202   3072    FFFF                      NOP                                    
  6203   3074    FFFF                      NOP                                    
  6204   3076    FFFF                      NOP                                    
  6205   3078    FFFF                      NOP                                    
  6206   307A    FFFF                      NOP                                    
  6207   307C    FFFF                      NOP                                    
  6208   307E    FFFF                      NOP                                    
  6209   3080    FFFF                      NOP                                    
  6210   3082    FFFF                      NOP                                    
  6211   3084    FFFF                      NOP                                    
  6212   3086    FFFF                      NOP                                    
  6213   3088    FFFF                      NOP                                    
  6214   308A    FFFF                      NOP                                    
  6215   308C    FFFF                      NOP                                    
  6216   308E    FFFF                      NOP                                    
  6217   3090    FFFF                      NOP                                    
  6218   3092    FFFF                      NOP                                    
  6219   3094    FFFF                      NOP                                    
  6220   3096    FFFF                      NOP                                    
  6221   3098    FFFF                      NOP                                    
  6222   309A    FFFF                      NOP                                    
  6223   309C    FFFF                      NOP                                    
  6224   309E    FFFF                      NOP                                    
  6225   30A0    FFFF                      NOP                                    
  6226   30A2    FFFF                      NOP                                    
  6227   30A4    FFFF                      NOP                                    
  6228   30A6    FFFF                      NOP                                    
  6229   30A8    FFFF                      NOP                                    
  6230   30AA    FFFF                      NOP                                    
  6231   30AC    FFFF                      NOP                                    
  6232   30AE    FFFF                      NOP                                    
  6233   30B0    FFFF                      NOP                                    
  6234   30B2    FFFF                      NOP                                    
  6235   30B4    FFFF                      NOP                                    
  6236   30B6    FFFF                      NOP                                    
  6237   30B8    FFFF                      NOP                                    
  6238   30BA    FFFF                      NOP                                    
  6239   30BC    FFFF                      NOP                                    
  6240   30BE    FFFF                      NOP                                    
  6241   30C0    FFFF                      NOP                                    
  6242   30C2    FFFF                      NOP                                    
  6243   30C4    FFFF                      NOP                                    
  6244   30C6    FFFF                      NOP                                    
  6245   30C8    FFFF                      NOP                                    
  6246   30CA    FFFF                      NOP                                    
  6247   30CC    FFFF                      NOP                                    
  6248   30CE    FFFF                      NOP                                    
  6249   30D0    FFFF                      NOP                                    
  6250   30D2    FFFF                      NOP                                    
  6251   30D4    FFFF                      NOP                                    
  6252   30D6    FFFF                      NOP                                    
  6253   30D8    FFFF                      NOP                                    
  6254   30DA    FFFF                      NOP                                    
  6255   30DC    FFFF                      NOP                                    
  6256   30DE    FFFF                      NOP                                    
  6257   30E0    FFFF                      NOP                                    
  6258   30E2    FFFF                      NOP                                    
  6259   30E4    FFFF                      NOP                                    
  6260   30E6    FFFF                      NOP                                    
  6261   30E8    FFFF                      NOP                                    
  6262   30EA    FFFF                      NOP                                    
  6263   30EC    FFFF                      NOP                                    
  6264   30EE    FFFF                      NOP                                    
  6265   30F0    FFFF                      NOP                                    
  6266   30F2    FFFF                      NOP                                    
  6267   30F4    FFFF                      NOP                                    
  6268   30F6    FFFF                      NOP                                    
  6269   30F8    FFFF                      NOP                                    
  6270   30FA    FFFF                      NOP                                    
  6271   30FC    FFFF                      NOP                                    
  6272   30FE    FFFF                      NOP                                    
  6273   3100    FFFF                      NOP                                    
  6274   3102    FFFF                      NOP                                    
  6275   3104    FFFF                      NOP                                    
  6276   3106    FFFF                      NOP                                    
  6277   3108    FFFF                      NOP                                    
  6278   310A    FFFF                      NOP                                    
  6279   310C    FFFF                      NOP                                    
  6280   310E    FFFF                      NOP                                    
  6281   3110    FFFF                      NOP                                    
  6282   3112    FFFF                      NOP                                    
  6283   3114    FFFF                      NOP                                    
  6284   3116    FFFF                      NOP                                    
  6285   3118    FFFF                      NOP                                    
  6286   311A    FFFF                      NOP                                    
  6287   311C    FFFF                      NOP                                    
  6288   311E    FFFF                      NOP                                    
  6289   3120    FFFF                      NOP                                    
  6290   3122    FFFF                      NOP                                    
  6291   3124    FFFF                      NOP                                    
  6292   3126    FFFF                      NOP                                    
  6293   3128    FFFF                      NOP                                    
  6294   312A    FFFF                      NOP                                    
  6295   312C    FFFF                      NOP                                    
  6296   312E    FFFF                      NOP                                    
  6297   3130    FFFF                      NOP                                    
  6298   3132    FFFF                      NOP                                    
  6299   3134    FFFF                      NOP                                    
  6300   3136    FFFF                      NOP                                    
  6301   3138    FFFF                      NOP                                    
  6302   313A    FFFF                      NOP                                    
  6303   313C    FFFF                      NOP                                    
  6304   313E    FFFF                      NOP                                    
  6305   3140    FFFF                      NOP                                    
  6306   3142    FFFF                      NOP                                    
  6307   3144    FFFF                      NOP                                    
  6308   3146    FFFF                      NOP                                    
  6309   3148    FFFF                      NOP                                    
  6310   314A    FFFF                      NOP                                    
  6311   314C    FFFF                      NOP                                    
  6312   314E    FFFF                      NOP                                    
  6313   3150    FFFF                      NOP                                    
  6314   3152    FFFF                      NOP                                    
  6315   3154    FFFF                      NOP                                    
  6316   3156    FFFF                      NOP                                    
  6317   3158    FFFF                      NOP                                    
  6318   315A    FFFF                      NOP                                    
  6319   315C    FFFF                      NOP                                    
  6320   315E    FFFF                      NOP                                    
  6321   3160    FFFF                      NOP                                    
  6322   3162    FFFF                      NOP                                    
  6323   3164    FFFF                      NOP                                    
  6324   3166    FFFF                      NOP                                    
  6325   3168    FFFF                      NOP                                    
  6326   316A    FFFF                      NOP                                    
  6327   316C    FFFF                      NOP                                    
  6328   316E    FFFF                      NOP                                    
  6329   3170    FFFF                      NOP                                    
  6330   3172    FFFF                      NOP                                    
  6331   3174    FFFF                      NOP                                    
  6332   3176    FFFF                      NOP                                    
  6333   3178    FFFF                      NOP                                    
  6334   317A    FFFF                      NOP                                    
  6335   317C    FFFF                      NOP                                    
  6336   317E    FFFF                      NOP                                    
  6337   3180    FFFF                      NOP                                    
  6338   3182    FFFF                      NOP                                    
  6339   3184    FFFF                      NOP                                    
  6340   3186    FFFF                      NOP                                    
  6341   3188    FFFF                      NOP                                    
  6342   318A    FFFF                      NOP                                    
  6343   318C    FFFF                      NOP                                    
  6344   318E    FFFF                      NOP                                    
  6345   3190    FFFF                      NOP                                    
  6346   3192    FFFF                      NOP                                    
  6347   3194    FFFF                      NOP                                    
  6348   3196    FFFF                      NOP                                    
  6349   3198    FFFF                      NOP                                    
  6350   319A    FFFF                      NOP                                    
  6351   319C    FFFF                      NOP                                    
  6352   319E    FFFF                      NOP                                    
  6353   31A0    FFFF                      NOP                                    
  6354   31A2    FFFF                      NOP                                    
  6355   31A4    FFFF                      NOP                                    
  6356   31A6    FFFF                      NOP                                    
  6357   31A8    FFFF                      NOP                                    
  6358   31AA    FFFF                      NOP                                    
  6359   31AC    FFFF                      NOP                                    
  6360   31AE    FFFF                      NOP                                    
  6361   31B0    FFFF                      NOP                                    
  6362   31B2    FFFF                      NOP                                    
  6363   31B4    FFFF                      NOP                                    
  6364   31B6    FFFF                      NOP                                    
  6365   31B8    FFFF                      NOP                                    
  6366   31BA    FFFF                      NOP                                    
  6367   31BC    FFFF                      NOP                                    
  6368   31BE    FFFF                      NOP                                    
  6369   31C0    FFFF                      NOP                                    
  6370   31C2    FFFF                      NOP                                    
  6371   31C4    FFFF                      NOP                                    
  6372   31C6    FFFF                      NOP                                    
  6373   31C8    FFFF                      NOP                                    
  6374   31CA    FFFF                      NOP                                    
  6375   31CC    FFFF                      NOP                                    
  6376   31CE    FFFF                      NOP                                    
  6377   31D0    FFFF                      NOP                                    
  6378   31D2    FFFF                      NOP                                    
  6379   31D4    FFFF                      NOP                                    
  6380   31D6    FFFF                      NOP                                    
  6381   31D8    FFFF                      NOP                                    
  6382   31DA    FFFF                      NOP                                    
  6383   31DC    FFFF                      NOP                                    
  6384   31DE    FFFF                      NOP                                    
  6385   31E0    FFFF                      NOP                                    
  6386   31E2    FFFF                      NOP                                    
  6387   31E4    FFFF                      NOP                                    
  6388   31E6    FFFF                      NOP                                    
  6389   31E8    FFFF                      NOP                                    
  6390   31EA    FFFF                      NOP                                    
  6391   31EC    FFFF                      NOP                                    
  6392   31EE    FFFF                      NOP                                    
  6393   31F0    FFFF                      NOP                                    
  6394   31F2    FFFF                      NOP                                    
  6395   31F4    FFFF                      NOP                                    
  6396   31F6    FFFF                      NOP                                    
  6397   31F8    FFFF                      NOP                                    
  6398   31FA    FFFF                      NOP                                    
  6399   31FC    FFFF                      NOP                                    
  6400   31FE    FFFF                      NOP                                    
  6401   3200    FFFF                      NOP                                    
  6402   3202    FFFF                      NOP                                    
  6403   3204    FFFF                      NOP                                    
  6404   3206    FFFF                      NOP                                    
  6405   3208    FFFF                      NOP                                    
  6406   320A    FFFF                      NOP                                    
  6407   320C    FFFF                      NOP                                    
  6408   320E    FFFF                      NOP                                    
  6409   3210    FFFF                      NOP                                    
  6410   3212    FFFF                      NOP                                    
  6411   3214    FFFF                      NOP                                    
  6412   3216    FFFF                      NOP                                    
  6413   3218    FFFF                      NOP                                    
  6414   321A    FFFF                      NOP                                    
  6415   321C    FFFF                      NOP                                    
  6416   321E    FFFF                      NOP                                    
  6417   3220    FFFF                      NOP                                    
  6418   3222    FFFF                      NOP                                    
  6419   3224    FFFF                      NOP                                    
  6420   3226    FFFF                      NOP                                    
  6421   3228    FFFF                      NOP                                    
  6422   322A    FFFF                      NOP                                    
  6423   322C    FFFF                      NOP                                    
  6424   322E    FFFF                      NOP                                    
  6425   3230    FFFF                      NOP                                    
  6426   3232    FFFF                      NOP                                    
  6427   3234    FFFF                      NOP                                    
  6428   3236    FFFF                      NOP                                    
  6429   3238    FFFF                      NOP                                    
  6430   323A    FFFF                      NOP                                    
  6431   323C    FFFF                      NOP                                    
  6432   323E    FFFF                      NOP                                    
  6433   3240    FFFF                      NOP                                    
  6434   3242    FFFF                      NOP                                    
  6435   3244    FFFF                      NOP                                    
  6436   3246    FFFF                      NOP                                    
  6437   3248    FFFF                      NOP                                    
  6438   324A    FFFF                      NOP                                    
  6439   324C    FFFF                      NOP                                    
  6440   324E    FFFF                      NOP                                    
  6441   3250    FFFF                      NOP                                    
  6442   3252    FFFF                      NOP                                    
  6443   3254    FFFF                      NOP                                    
  6444   3256    FFFF                      NOP                                    
  6445   3258    FFFF                      NOP                                    
  6446   325A    FFFF                      NOP                                    
  6447   325C    FFFF                      NOP                                    
  6448   325E    FFFF                      NOP                                    
  6449   3260    FFFF                      NOP                                    
  6450   3262    FFFF                      NOP                                    
  6451   3264    FFFF                      NOP                                    
  6452   3266    FFFF                      NOP                                    
  6453   3268    FFFF                      NOP                                    
  6454   326A    FFFF                      NOP                                    
  6455   326C    FFFF                      NOP                                    
  6456   326E    FFFF                      NOP                                    
  6457   3270    FFFF                      NOP                                    
  6458   3272    FFFF                      NOP                                    
  6459   3274    FFFF                      NOP                                    
  6460   3276    FFFF                      NOP                                    
  6461   3278    FFFF                      NOP                                    
  6462   327A    FFFF                      NOP                                    
  6463   327C    FFFF                      NOP                                    
  6464   327E    FFFF                      NOP                                    
  6465   3280    FFFF                      NOP                                    
  6466   3282    FFFF                      NOP                                    
  6467   3284    FFFF                      NOP                                    
  6468   3286    FFFF                      NOP                                    
  6469   3288    FFFF                      NOP                                    
  6470   328A    FFFF                      NOP                                    
  6471   328C    FFFF                      NOP                                    
  6472   328E    FFFF                      NOP                                    
  6473   3290    FFFF                      NOP                                    
  6474   3292    FFFF                      NOP                                    
  6475   3294    FFFF                      NOP                                    
  6476   3296    FFFF                      NOP                                    
  6477   3298    FFFF                      NOP                                    
  6478   329A    FFFF                      NOP                                    
  6479   329C    FFFF                      NOP                                    
  6480   329E    FFFF                      NOP                                    
  6481   32A0    FFFF                      NOP                                    
  6482   32A2    FFFF                      NOP                                    
  6483   32A4    FFFF                      NOP                                    
  6484   32A6    FFFF                      NOP                                    
  6485   32A8    FFFF                      NOP                                    
  6486   32AA    FFFF                      NOP                                    
  6487   32AC    FFFF                      NOP                                    
  6488   32AE    FFFF                      NOP                                    
  6489   32B0    FFFF                      NOP                                    
  6490   32B2    FFFF                      NOP                                    
  6491   32B4    FFFF                      NOP                                    
  6492   32B6    FFFF                      NOP                                    
  6493   32B8    FFFF                      NOP                                    
  6494   32BA    FFFF                      NOP                                    
  6495   32BC    FFFF                      NOP                                    
  6496   32BE    FFFF                      NOP                                    
  6497   32C0    FFFF                      NOP                                    
  6498   32C2    FFFF                      NOP                                    
  6499   32C4    FFFF                      NOP                                    
  6500   32C6    FFFF                      NOP                                    
  6501   32C8    FFFF                      NOP                                    
  6502   32CA    FFFF                      NOP                                    
  6503   32CC    FFFF                      NOP                                    
  6504   32CE    FFFF                      NOP                                    
  6505   32D0    FFFF                      NOP                                    
  6506   32D2    FFFF                      NOP                                    
  6507   32D4    FFFF                      NOP                                    
  6508   32D6    FFFF                      NOP                                    
  6509   32D8    FFFF                      NOP                                    
  6510   32DA    FFFF                      NOP                                    
  6511   32DC    FFFF                      NOP                                    
  6512   32DE    FFFF                      NOP                                    
  6513   32E0    FFFF                      NOP                                    
  6514   32E2    FFFF                      NOP                                    
  6515   32E4    FFFF                      NOP                                    
  6516   32E6    FFFF                      NOP                                    
  6517   32E8    FFFF                      NOP                                    
  6518   32EA    FFFF                      NOP                                    
  6519   32EC    FFFF                      NOP                                    
  6520   32EE    FFFF                      NOP                                    
  6521   32F0    FFFF                      NOP                                    
  6522   32F2    FFFF                      NOP                                    
  6523   32F4    FFFF                      NOP                                    
  6524   32F6    FFFF                      NOP                                    
  6525   32F8    FFFF                      NOP                                    
  6526   32FA    FFFF                      NOP                                    
  6527   32FC    FFFF                      NOP                                    
  6528   32FE    FFFF                      NOP                                    
  6529   3300    FFFF                      NOP                                    
  6530   3302    FFFF                      NOP                                    
  6531   3304    FFFF                      NOP                                    
  6532   3306    FFFF                      NOP                                    
  6533   3308    FFFF                      NOP                                    
  6534   330A    FFFF                      NOP                                    
  6535   330C    FFFF                      NOP                                    
  6536   330E    FFFF                      NOP                                    
  6537   3310    FFFF                      NOP                                    
  6538   3312    FFFF                      NOP                                    
  6539   3314    FFFF                      NOP                                    
  6540   3316    FFFF                      NOP                                    
  6541   3318    FFFF                      NOP                                    
  6542   331A    FFFF                      NOP                                    
  6543   331C    FFFF                      NOP                                    
  6544   331E    FFFF                      NOP                                    
  6545   3320    FFFF                      NOP                                    
  6546   3322    FFFF                      NOP                                    
  6547   3324    FFFF                      NOP                                    
  6548   3326    FFFF                      NOP                                    
  6549   3328    FFFF                      NOP                                    
  6550   332A    FFFF                      NOP                                    
  6551   332C    FFFF                      NOP                                    
  6552   332E    FFFF                      NOP                                    
  6553   3330    FFFF                      NOP                                    
  6554   3332    FFFF                      NOP                                    
  6555   3334    FFFF                      NOP                                    
  6556   3336    FFFF                      NOP                                    
  6557   3338    FFFF                      NOP                                    
  6558   333A    FFFF                      NOP                                    
  6559   333C    FFFF                      NOP                                    
  6560   333E    FFFF                      NOP                                    
  6561   3340    FFFF                      NOP                                    
  6562   3342    FFFF                      NOP                                    
  6563   3344    FFFF                      NOP                                    
  6564   3346    FFFF                      NOP                                    
  6565   3348    FFFF                      NOP                                    
  6566   334A    FFFF                      NOP                                    
  6567   334C    FFFF                      NOP                                    
  6568   334E    FFFF                      NOP                                    
  6569   3350    FFFF                      NOP                                    
  6570   3352    FFFF                      NOP                                    
  6571   3354    FFFF                      NOP                                    
  6572   3356    FFFF                      NOP                                    
  6573   3358    FFFF                      NOP                                    
  6574   335A    FFFF                      NOP                                    
  6575   335C    FFFF                      NOP                                    
  6576   335E    FFFF                      NOP                                    
  6577   3360    FFFF                      NOP                                    
  6578   3362    FFFF                      NOP                                    
  6579   3364    FFFF                      NOP                                    
  6580   3366    FFFF                      NOP                                    
  6581   3368    FFFF                      NOP                                    
  6582   336A    FFFF                      NOP                                    
  6583   336C    FFFF                      NOP                                    
  6584   336E    FFFF                      NOP                                    
  6585   3370    FFFF                      NOP                                    
  6586   3372    FFFF                      NOP                                    
  6587   3374    FFFF                      NOP                                    
  6588   3376    FFFF                      NOP                                    
  6589   3378    FFFF                      NOP                                    
  6590   337A    FFFF                      NOP                                    
  6591   337C    FFFF                      NOP                                    
  6592   337E    FFFF                      NOP                                    
  6593   3380    FFFF                      NOP                                    
  6594   3382    FFFF                      NOP                                    
  6595   3384    FFFF                      NOP                                    
  6596   3386    FFFF                      NOP                                    
  6597   3388    FFFF                      NOP                                    
  6598   338A    FFFF                      NOP                                    
  6599   338C    FFFF                      NOP                                    
  6600   338E    FFFF                      NOP                                    
  6601   3390    FFFF                      NOP                                    
  6602   3392    FFFF                      NOP                                    
  6603   3394    FFFF                      NOP                                    
  6604   3396    FFFF                      NOP                                    
  6605   3398    FFFF                      NOP                                    
  6606   339A    FFFF                      NOP                                    
  6607   339C    FFFF                      NOP                                    
  6608   339E    FFFF                      NOP                                    
  6609   33A0    FFFF                      NOP                                    
  6610   33A2    FFFF                      NOP                                    
  6611   33A4    FFFF                      NOP                                    
  6612   33A6    FFFF                      NOP                                    
  6613   33A8    FFFF                      NOP                                    
  6614   33AA    FFFF                      NOP                                    
  6615   33AC    FFFF                      NOP                                    
  6616   33AE    FFFF                      NOP                                    
  6617   33B0    FFFF                      NOP                                    
  6618   33B2    FFFF                      NOP                                    
  6619   33B4    FFFF                      NOP                                    
  6620   33B6    FFFF                      NOP                                    
  6621   33B8    FFFF                      NOP                                    
  6622   33BA    FFFF                      NOP                                    
  6623   33BC    FFFF                      NOP                                    
  6624   33BE    FFFF                      NOP                                    
  6625   33C0    FFFF                      NOP                                    
  6626   33C2    FFFF                      NOP                                    
  6627   33C4    FFFF                      NOP                                    
  6628   33C6    FFFF                      NOP                                    
  6629   33C8    FFFF                      NOP                                    
  6630   33CA    FFFF                      NOP                                    
  6631   33CC    FFFF                      NOP                                    
  6632   33CE    FFFF                      NOP                                    
  6633   33D0    FFFF                      NOP                                    
  6634   33D2    FFFF                      NOP                                    
  6635   33D4    FFFF                      NOP                                    
  6636   33D6    FFFF                      NOP                                    
  6637   33D8    FFFF                      NOP                                    
  6638   33DA    FFFF                      NOP                                    
  6639   33DC    FFFF                      NOP                                    
  6640   33DE    FFFF                      NOP                                    
  6641   33E0    FFFF                      NOP                                    
  6642   33E2    FFFF                      NOP                                    
  6643   33E4    FFFF                      NOP                                    
  6644   33E6    FFFF                      NOP                                    
  6645   33E8    FFFF                      NOP                                    
  6646   33EA    FFFF                      NOP                                    
  6647   33EC    FFFF                      NOP                                    
  6648   33EE    FFFF                      NOP                                    
  6649   33F0    FFFF                      NOP                                    
  6650   33F2    FFFF                      NOP                                    
  6651   33F4    FFFF                      NOP                                    
  6652   33F6    FFFF                      NOP                                    
  6653   33F8    FFFF                      NOP                                    
  6654   33FA    FFFF                      NOP                                    
  6655   33FC    FFFF                      NOP                                    
  6656   33FE    FFFF                      NOP                                    
  6657   3400    FFFF                      NOP                                    
  6658   3402    FFFF                      NOP                                    
  6659   3404    FFFF                      NOP                                    
  6660   3406    FFFF                      NOP                                    
  6661   3408    FFFF                      NOP                                    
  6662   340A    FFFF                      NOP                                    
  6663   340C    FFFF                      NOP                                    
  6664   340E    FFFF                      NOP                                    
  6665   3410    FFFF                      NOP                                    
  6666   3412    FFFF                      NOP                                    
  6667   3414    FFFF                      NOP                                    
  6668   3416    FFFF                      NOP                                    
  6669   3418    FFFF                      NOP                                    
  6670   341A    FFFF                      NOP                                    
  6671   341C    FFFF                      NOP                                    
  6672   341E    FFFF                      NOP                                    
  6673   3420    FFFF                      NOP                                    
  6674   3422    FFFF                      NOP                                    
  6675   3424    FFFF                      NOP                                    
  6676   3426    FFFF                      NOP                                    
  6677   3428    FFFF                      NOP                                    
  6678   342A    FFFF                      NOP                                    
  6679   342C    FFFF                      NOP                                    
  6680   342E    FFFF                      NOP                                    
  6681   3430    FFFF                      NOP                                    
  6682   3432    FFFF                      NOP                                    
  6683   3434    FFFF                      NOP                                    
  6684   3436    FFFF                      NOP                                    
  6685   3438    FFFF                      NOP                                    
  6686   343A    FFFF                      NOP                                    
  6687   343C    FFFF                      NOP                                    
  6688   343E    FFFF                      NOP                                    
  6689   3440    FFFF                      NOP                                    
  6690   3442    FFFF                      NOP                                    
  6691   3444    FFFF                      NOP                                    
  6692   3446    FFFF                      NOP                                    
  6693   3448    FFFF                      NOP                                    
  6694   344A    FFFF                      NOP                                    
  6695   344C    FFFF                      NOP                                    
  6696   344E    FFFF                      NOP                                    
  6697   3450    FFFF                      NOP                                    
  6698   3452    FFFF                      NOP                                    
  6699   3454    FFFF                      NOP                                    
  6700   3456    FFFF                      NOP                                    
  6701   3458    FFFF                      NOP                                    
  6702   345A    FFFF                      NOP                                    
  6703   345C    FFFF                      NOP                                    
  6704   345E    FFFF                      NOP                                    
  6705   3460    FFFF                      NOP                                    
  6706   3462    FFFF                      NOP                                    
  6707   3464    FFFF                      NOP                                    
  6708   3466    FFFF                      NOP                                    
  6709   3468    FFFF                      NOP                                    
  6710   346A    FFFF                      NOP                                    
  6711   346C    FFFF                      NOP                                    
  6712   346E    FFFF                      NOP                                    
  6713   3470    FFFF                      NOP                                    
  6714   3472    FFFF                      NOP                                    
  6715   3474    FFFF                      NOP                                    
  6716   3476    FFFF                      NOP                                    
  6717   3478    FFFF                      NOP                                    
  6718   347A    FFFF                      NOP                                    
  6719   347C    FFFF                      NOP                                    
  6720   347E    FFFF                      NOP                                    
  6721   3480    FFFF                      NOP                                    
  6722   3482    FFFF                      NOP                                    
  6723   3484    FFFF                      NOP                                    
  6724   3486    FFFF                      NOP                                    
  6725   3488    FFFF                      NOP                                    
  6726   348A    FFFF                      NOP                                    
  6727   348C    FFFF                      NOP                                    
  6728   348E    FFFF                      NOP                                    
  6729   3490    FFFF                      NOP                                    
  6730   3492    FFFF                      NOP                                    
  6731   3494    FFFF                      NOP                                    
  6732   3496    FFFF                      NOP                                    
  6733   3498    FFFF                      NOP                                    
  6734   349A    FFFF                      NOP                                    
  6735   349C    FFFF                      NOP                                    
  6736   349E    FFFF                      NOP                                    
  6737   34A0    FFFF                      NOP                                    
  6738   34A2    FFFF                      NOP                                    
  6739   34A4    FFFF                      NOP                                    
  6740   34A6    FFFF                      NOP                                    
  6741   34A8    FFFF                      NOP                                    
  6742   34AA    FFFF                      NOP                                    
  6743   34AC    FFFF                      NOP                                    
  6744   34AE    FFFF                      NOP                                    
  6745   34B0    FFFF                      NOP                                    
  6746   34B2    FFFF                      NOP                                    
  6747   34B4    FFFF                      NOP                                    
  6748   34B6    FFFF                      NOP                                    
  6749   34B8    FFFF                      NOP                                    
  6750   34BA    FFFF                      NOP                                    
  6751   34BC    FFFF                      NOP                                    
  6752   34BE    FFFF                      NOP                                    
  6753   34C0    FFFF                      NOP                                    
  6754   34C2    FFFF                      NOP                                    
  6755   34C4    FFFF                      NOP                                    
  6756   34C6    FFFF                      NOP                                    
  6757   34C8    FFFF                      NOP                                    
  6758   34CA    FFFF                      NOP                                    
  6759   34CC    FFFF                      NOP                                    
  6760   34CE    FFFF                      NOP                                    
  6761   34D0    FFFF                      NOP                                    
  6762   34D2    FFFF                      NOP                                    
  6763   34D4    FFFF                      NOP                                    
  6764   34D6    FFFF                      NOP                                    
  6765   34D8    FFFF                      NOP                                    
  6766   34DA    FFFF                      NOP                                    
  6767   34DC    FFFF                      NOP                                    
  6768   34DE    FFFF                      NOP                                    
  6769   34E0    FFFF                      NOP                                    
  6770   34E2    FFFF                      NOP                                    
  6771   34E4    FFFF                      NOP                                    
  6772   34E6    FFFF                      NOP                                    
  6773   34E8    FFFF                      NOP                                    
  6774   34EA    FFFF                      NOP                                    
  6775   34EC    FFFF                      NOP                                    
  6776   34EE    FFFF                      NOP                                    
  6777   34F0    FFFF                      NOP                                    
  6778   34F2    FFFF                      NOP                                    
  6779   34F4    FFFF                      NOP                                    
  6780   34F6    FFFF                      NOP                                    
  6781   34F8    FFFF                      NOP                                    
  6782   34FA    FFFF                      NOP                                    
  6783   34FC    FFFF                      NOP                                    
  6784   34FE    FFFF                      NOP                                    
  6785   3500    FFFF                      NOP                                    
  6786   3502    FFFF                      NOP                                    
  6787   3504    FFFF                      NOP                                    
  6788   3506    FFFF                      NOP                                    
  6789   3508    FFFF                      NOP                                    
  6790   350A    FFFF                      NOP                                    
  6791   350C    FFFF                      NOP                                    
  6792   350E    FFFF                      NOP                                    
  6793   3510    FFFF                      NOP                                    
  6794   3512    FFFF                      NOP                                    
  6795   3514    FFFF                      NOP                                    
  6796   3516    FFFF                      NOP                                    
  6797   3518    FFFF                      NOP                                    
  6798   351A    FFFF                      NOP                                    
  6799   351C    FFFF                      NOP                                    
  6800   351E    FFFF                      NOP                                    
  6801   3520    FFFF                      NOP                                    
  6802   3522    FFFF                      NOP                                    
  6803   3524    FFFF                      NOP                                    
  6804   3526    FFFF                      NOP                                    
  6805   3528    FFFF                      NOP                                    
  6806   352A    FFFF                      NOP                                    
  6807   352C    FFFF                      NOP                                    
  6808   352E    FFFF                      NOP                                    
  6809   3530    FFFF                      NOP                                    
  6810   3532    FFFF                      NOP                                    
  6811   3534    FFFF                      NOP                                    
  6812   3536    FFFF                      NOP                                    
  6813   3538    FFFF                      NOP                                    
  6814   353A    FFFF                      NOP                                    
  6815   353C    FFFF                      NOP                                    
  6816   353E    FFFF                      NOP                                    
  6817   3540    FFFF                      NOP                                    
  6818   3542    FFFF                      NOP                                    
  6819   3544    FFFF                      NOP                                    
  6820   3546    FFFF                      NOP                                    
  6821   3548    FFFF                      NOP                                    
  6822   354A    FFFF                      NOP                                    
  6823   354C    FFFF                      NOP                                    
  6824   354E    FFFF                      NOP                                    
  6825   3550    FFFF                      NOP                                    
  6826   3552    FFFF                      NOP                                    
  6827   3554    FFFF                      NOP                                    
  6828   3556    FFFF                      NOP                                    
  6829   3558    FFFF                      NOP                                    
  6830   355A    FFFF                      NOP                                    
  6831   355C    FFFF                      NOP                                    
  6832   355E    FFFF                      NOP                                    
  6833   3560    FFFF                      NOP                                    
  6834   3562    FFFF                      NOP                                    
  6835   3564    FFFF                      NOP                                    
  6836   3566    FFFF                      NOP                                    
  6837   3568    FFFF                      NOP                                    
  6838   356A    FFFF                      NOP                                    
  6839   356C    FFFF                      NOP                                    
  6840   356E    FFFF                      NOP                                    
  6841   3570    FFFF                      NOP                                    
  6842   3572    FFFF                      NOP                                    
  6843   3574    FFFF                      NOP                                    
  6844   3576    FFFF                      NOP                                    
  6845   3578    FFFF                      NOP                                    
  6846   357A    FFFF                      NOP                                    
  6847   357C    FFFF                      NOP                                    
  6848   357E    FFFF                      NOP                                    
  6849   3580    FFFF                      NOP                                    
  6850   3582    FFFF                      NOP                                    
  6851   3584    FFFF                      NOP                                    
  6852   3586    FFFF                      NOP                                    
  6853   3588    FFFF                      NOP                                    
  6854   358A    FFFF                      NOP                                    
  6855   358C    FFFF                      NOP                                    
  6856   358E    FFFF                      NOP                                    
  6857   3590    FFFF                      NOP                                    
  6858   3592    FFFF                      NOP                                    
  6859   3594    FFFF                      NOP                                    
  6860   3596    FFFF                      NOP                                    
  6861   3598    FFFF                      NOP                                    
  6862   359A    FFFF                      NOP                                    
  6863   359C    FFFF                      NOP                                    
  6864   359E    FFFF                      NOP                                    
  6865   35A0    FFFF                      NOP                                    
  6866   35A2    FFFF                      NOP                                    
  6867   35A4    FFFF                      NOP                                    
  6868   35A6    FFFF                      NOP                                    
  6869   35A8    FFFF                      NOP                                    
  6870   35AA    FFFF                      NOP                                    
  6871   35AC    FFFF                      NOP                                    
  6872   35AE    FFFF                      NOP                                    
  6873   35B0    FFFF                      NOP                                    
  6874   35B2    FFFF                      NOP                                    
  6875   35B4    FFFF                      NOP                                    
  6876   35B6    FFFF                      NOP                                    
  6877   35B8    FFFF                      NOP                                    
  6878   35BA    FFFF                      NOP                                    
  6879   35BC    FFFF                      NOP                                    
  6880   35BE    FFFF                      NOP                                    
  6881   35C0    FFFF                      NOP                                    
  6882   35C2    FFFF                      NOP                                    
  6883   35C4    FFFF                      NOP                                    
  6884   35C6    FFFF                      NOP                                    
  6885   35C8    FFFF                      NOP                                    
  6886   35CA    FFFF                      NOP                                    
  6887   35CC    FFFF                      NOP                                    
  6888   35CE    FFFF                      NOP                                    
  6889   35D0    FFFF                      NOP                                    
  6890   35D2    FFFF                      NOP                                    
  6891   35D4    FFFF                      NOP                                    
  6892   35D6    FFFF                      NOP                                    
  6893   35D8    FFFF                      NOP                                    
  6894   35DA    FFFF                      NOP                                    
  6895   35DC    FFFF                      NOP                                    
  6896   35DE    FFFF                      NOP                                    
  6897   35E0    FFFF                      NOP                                    
  6898   35E2    FFFF                      NOP                                    
  6899   35E4    FFFF                      NOP                                    
  6900   35E6    FFFF                      NOP                                    
  6901   35E8    FFFF                      NOP                                    
  6902   35EA    FFFF                      NOP                                    
  6903   35EC    FFFF                      NOP                                    
  6904   35EE    FFFF                      NOP                                    
  6905   35F0    FFFF                      NOP                                    
  6906   35F2    FFFF                      NOP                                    
  6907   35F4    FFFF                      NOP                                    
  6908   35F6    FFFF                      NOP                                    
  6909   35F8    FFFF                      NOP                                    
  6910   35FA    FFFF                      NOP                                    
  6911   35FC    FFFF                      NOP                                    
  6912   35FE    FFFF                      NOP                                    
  6913   3600    FFFF                      NOP                                    
  6914   3602    FFFF                      NOP                                    
  6915   3604    FFFF                      NOP                                    
  6916   3606    FFFF                      NOP                                    
  6917   3608    FFFF                      NOP                                    
  6918   360A    FFFF                      NOP                                    
  6919   360C    FFFF                      NOP                                    
  6920   360E    FFFF                      NOP                                    
  6921   3610    FFFF                      NOP                                    
  6922   3612    FFFF                      NOP                                    
  6923   3614    FFFF                      NOP                                    
  6924   3616    FFFF                      NOP                                    
  6925   3618    FFFF                      NOP                                    
  6926   361A    FFFF                      NOP                                    
  6927   361C    FFFF                      NOP                                    
  6928   361E    FFFF                      NOP                                    
  6929   3620    FFFF                      NOP                                    
  6930   3622    FFFF                      NOP                                    
  6931   3624    FFFF                      NOP                                    
  6932   3626    FFFF                      NOP                                    
  6933   3628    FFFF                      NOP                                    
  6934   362A    FFFF                      NOP                                    
  6935   362C    FFFF                      NOP                                    
  6936   362E    FFFF                      NOP                                    
  6937   3630    FFFF                      NOP                                    
  6938   3632    FFFF                      NOP                                    
  6939   3634    FFFF                      NOP                                    
  6940   3636    FFFF                      NOP                                    
  6941   3638    FFFF                      NOP                                    
  6942   363A    FFFF                      NOP                                    
  6943   363C    FFFF                      NOP                                    
  6944   363E    FFFF                      NOP                                    
  6945   3640    FFFF                      NOP                                    
  6946   3642    FFFF                      NOP                                    
  6947   3644    FFFF                      NOP                                    
  6948   3646    FFFF                      NOP                                    
  6949   3648    FFFF                      NOP                                    
  6950   364A    FFFF                      NOP                                    
  6951   364C    FFFF                      NOP                                    
  6952   364E    FFFF                      NOP                                    
  6953   3650    FFFF                      NOP                                    
  6954   3652    FFFF                      NOP                                    
  6955   3654    FFFF                      NOP                                    
  6956   3656    FFFF                      NOP                                    
  6957   3658    FFFF                      NOP                                    
  6958   365A    FFFF                      NOP                                    
  6959   365C    FFFF                      NOP                                    
  6960   365E    FFFF                      NOP                                    
  6961   3660    FFFF                      NOP                                    
  6962   3662    FFFF                      NOP                                    
  6963   3664    FFFF                      NOP                                    
  6964   3666    FFFF                      NOP                                    
  6965   3668    FFFF                      NOP                                    
  6966   366A    FFFF                      NOP                                    
  6967   366C    FFFF                      NOP                                    
  6968   366E    FFFF                      NOP                                    
  6969   3670    FFFF                      NOP                                    
  6970   3672    FFFF                      NOP                                    
  6971   3674    FFFF                      NOP                                    
  6972   3676    FFFF                      NOP                                    
  6973   3678    FFFF                      NOP                                    
  6974   367A    FFFF                      NOP                                    
  6975   367C    FFFF                      NOP                                    
  6976   367E    FFFF                      NOP                                    
  6977   3680    FFFF                      NOP                                    
  6978   3682    FFFF                      NOP                                    
  6979   3684    FFFF                      NOP                                    
  6980   3686    FFFF                      NOP                                    
  6981   3688    FFFF                      NOP                                    
  6982   368A    FFFF                      NOP                                    
  6983   368C    FFFF                      NOP                                    
  6984   368E    FFFF                      NOP                                    
  6985   3690    FFFF                      NOP                                    
  6986   3692    FFFF                      NOP                                    
  6987   3694    FFFF                      NOP                                    
  6988   3696    FFFF                      NOP                                    
  6989   3698    FFFF                      NOP                                    
  6990   369A    FFFF                      NOP                                    
  6991   369C    FFFF                      NOP                                    
  6992   369E    FFFF                      NOP                                    
  6993   36A0    FFFF                      NOP                                    
  6994   36A2    FFFF                      NOP                                    
  6995   36A4    FFFF                      NOP                                    
  6996   36A6    FFFF                      NOP                                    
  6997   36A8    FFFF                      NOP                                    
  6998   36AA    FFFF                      NOP                                    
  6999   36AC    FFFF                      NOP                                    
  7000   36AE    FFFF                      NOP                                    
  7001   36B0    FFFF                      NOP                                    
  7002   36B2    FFFF                      NOP                                    
  7003   36B4    FFFF                      NOP                                    
  7004   36B6    FFFF                      NOP                                    
  7005   36B8    FFFF                      NOP                                    
  7006   36BA    FFFF                      NOP                                    
  7007   36BC    FFFF                      NOP                                    
  7008   36BE    FFFF                      NOP                                    
  7009   36C0    FFFF                      NOP                                    
  7010   36C2    FFFF                      NOP                                    
  7011   36C4    FFFF                      NOP                                    
  7012   36C6    FFFF                      NOP                                    
  7013   36C8    FFFF                      NOP                                    
  7014   36CA    FFFF                      NOP                                    
  7015   36CC    FFFF                      NOP                                    
  7016   36CE    FFFF                      NOP                                    
  7017   36D0    FFFF                      NOP                                    
  7018   36D2    FFFF                      NOP                                    
  7019   36D4    FFFF                      NOP                                    
  7020   36D6    FFFF                      NOP                                    
  7021   36D8    FFFF                      NOP                                    
  7022   36DA    FFFF                      NOP                                    
  7023   36DC    FFFF                      NOP                                    
  7024   36DE    FFFF                      NOP                                    
  7025   36E0    FFFF                      NOP                                    
  7026   36E2    FFFF                      NOP                                    
  7027   36E4    FFFF                      NOP                                    
  7028   36E6    FFFF                      NOP                                    
  7029   36E8    FFFF                      NOP                                    
  7030   36EA    FFFF                      NOP                                    
  7031   36EC    FFFF                      NOP                                    
  7032   36EE    FFFF                      NOP                                    
  7033   36F0    FFFF                      NOP                                    
  7034   36F2    FFFF                      NOP                                    
  7035   36F4    FFFF                      NOP                                    
  7036   36F6    FFFF                      NOP                                    
  7037   36F8    FFFF                      NOP                                    
  7038   36FA    FFFF                      NOP                                    
  7039   36FC    FFFF                      NOP                                    
  7040   36FE    FFFF                      NOP                                    
  7041   3700    FFFF                      NOP                                    
  7042   3702    FFFF                      NOP                                    
  7043   3704    FFFF                      NOP                                    
  7044   3706    FFFF                      NOP                                    
  7045   3708    FFFF                      NOP                                    
  7046   370A    FFFF                      NOP                                    
  7047   370C    FFFF                      NOP                                    
  7048   370E    FFFF                      NOP                                    
  7049   3710    FFFF                      NOP                                    
  7050   3712    FFFF                      NOP                                    
  7051   3714    FFFF                      NOP                                    
  7052   3716    FFFF                      NOP                                    
  7053   3718    FFFF                      NOP                                    
  7054   371A    FFFF                      NOP                                    
  7055   371C    FFFF                      NOP                                    
  7056   371E    FFFF                      NOP                                    
  7057   3720    FFFF                      NOP                                    
  7058   3722    FFFF                      NOP                                    
  7059   3724    FFFF                      NOP                                    
  7060   3726    FFFF                      NOP                                    
  7061   3728    FFFF                      NOP                                    
  7062   372A    FFFF                      NOP                                    
  7063   372C    FFFF                      NOP                                    
  7064   372E    FFFF                      NOP                                    
  7065   3730    FFFF                      NOP                                    
  7066   3732    FFFF                      NOP                                    
  7067   3734    FFFF                      NOP                                    
  7068   3736    FFFF                      NOP                                    
  7069   3738    FFFF                      NOP                                    
  7070   373A    FFFF                      NOP                                    
  7071   373C    FFFF                      NOP                                    
  7072   373E    FFFF                      NOP                                    
  7073   3740    FFFF                      NOP                                    
  7074   3742    FFFF                      NOP                                    
  7075   3744    FFFF                      NOP                                    
  7076   3746    FFFF                      NOP                                    
  7077   3748    FFFF                      NOP                                    
  7078   374A    FFFF                      NOP                                    
  7079   374C    FFFF                      NOP                                    
  7080   374E    FFFF                      NOP                                    
  7081   3750    FFFF                      NOP                                    
  7082   3752    FFFF                      NOP                                    
  7083   3754    FFFF                      NOP                                    
  7084   3756    FFFF                      NOP                                    
  7085   3758    FFFF                      NOP                                    
  7086   375A    FFFF                      NOP                                    
  7087   375C    FFFF                      NOP                                    
  7088   375E    FFFF                      NOP                                    
  7089   3760    FFFF                      NOP                                    
  7090   3762    FFFF                      NOP                                    
  7091   3764    FFFF                      NOP                                    
  7092   3766    FFFF                      NOP                                    
  7093   3768    FFFF                      NOP                                    
  7094   376A    FFFF                      NOP                                    
  7095   376C    FFFF                      NOP                                    
  7096   376E    FFFF                      NOP                                    
  7097   3770    FFFF                      NOP                                    
  7098   3772    FFFF                      NOP                                    
  7099   3774    FFFF                      NOP                                    
  7100   3776    FFFF                      NOP                                    
  7101   3778    FFFF                      NOP                                    
  7102   377A    FFFF                      NOP                                    
  7103   377C    FFFF                      NOP                                    
  7104   377E    FFFF                      NOP                                    
  7105   3780    FFFF                      NOP                                    
  7106   3782    FFFF                      NOP                                    
  7107   3784    FFFF                      NOP                                    
  7108   3786    FFFF                      NOP                                    
  7109   3788    FFFF                      NOP                                    
  7110   378A    FFFF                      NOP                                    
  7111   378C    FFFF                      NOP                                    
  7112   378E    FFFF                      NOP                                    
  7113   3790    FFFF                      NOP                                    
  7114   3792    FFFF                      NOP                                    
  7115   3794    FFFF                      NOP                                    
  7116   3796    FFFF                      NOP                                    
  7117   3798    FFFF                      NOP                                    
  7118   379A    FFFF                      NOP                                    
  7119   379C    FFFF                      NOP                                    
  7120   379E    FFFF                      NOP                                    
  7121   37A0    FFFF                      NOP                                    
  7122   37A2    FFFF                      NOP                                    
  7123   37A4    FFFF                      NOP                                    
  7124   37A6    FFFF                      NOP                                    
  7125   37A8    FFFF                      NOP                                    
  7126   37AA    FFFF                      NOP                                    
  7127   37AC    FFFF                      NOP                                    
  7128   37AE    FFFF                      NOP                                    
  7129   37B0    FFFF                      NOP                                    
  7130   37B2    FFFF                      NOP                                    
  7131   37B4    FFFF                      NOP                                    
  7132   37B6    FFFF                      NOP                                    
  7133   37B8    FFFF                      NOP                                    
  7134   37BA    FFFF                      NOP                                    
  7135   37BC    FFFF                      NOP                                    
  7136   37BE    FFFF                      NOP                                    
  7137   37C0    FFFF                      NOP                                    
  7138   37C2    FFFF                      NOP                                    
  7139   37C4    FFFF                      NOP                                    
  7140   37C6    FFFF                      NOP                                    
  7141   37C8    FFFF                      NOP                                    
  7142   37CA    FFFF                      NOP                                    
  7143   37CC    FFFF                      NOP                                    
  7144   37CE    FFFF                      NOP                                    
  7145   37D0    FFFF                      NOP                                    
  7146   37D2    FFFF                      NOP                                    
  7147   37D4    FFFF                      NOP                                    
  7148   37D6    FFFF                      NOP                                    
  7149   37D8    FFFF                      NOP                                    
  7150   37DA    FFFF                      NOP                                    
  7151   37DC    FFFF                      NOP                                    
  7152   37DE    FFFF                      NOP                                    
  7153   37E0    FFFF                      NOP                                    
  7154   37E2    FFFF                      NOP                                    
  7155   37E4    FFFF                      NOP                                    
  7156   37E6    FFFF                      NOP                                    
  7157   37E8    FFFF                      NOP                                    
  7158   37EA    FFFF                      NOP                                    
  7159   37EC    FFFF                      NOP                                    
  7160   37EE    FFFF                      NOP                                    
  7161   37F0    FFFF                      NOP                                    
  7162   37F2    FFFF                      NOP                                    
  7163   37F4    FFFF                      NOP                                    
  7164   37F6    FFFF                      NOP                                    
  7165   37F8    FFFF                      NOP                                    
  7166   37FA    FFFF                      NOP                                    
  7167   37FC    FFFF                      NOP                                    
  7168   37FE    FFFF                      NOP                                    
  7169   3800    FFFF                      NOP                                    
  7170   3802    FFFF                      NOP                                    
  7171   3804    FFFF                      NOP                                    
  7172   3806    FFFF                      NOP                                    
  7173   3808    FFFF                      NOP                                    
  7174   380A    FFFF                      NOP                                    
  7175   380C    FFFF                      NOP                                    
  7176   380E    FFFF                      NOP                                    
  7177   3810    FFFF                      NOP                                    
  7178   3812    FFFF                      NOP                                    
  7179   3814    FFFF                      NOP                                    
  7180   3816    FFFF                      NOP                                    
  7181   3818    FFFF                      NOP                                    
  7182   381A    FFFF                      NOP                                    
  7183   381C    FFFF                      NOP                                    
  7184   381E    FFFF                      NOP                                    
  7185   3820    FFFF                      NOP                                    
  7186   3822    FFFF                      NOP                                    
  7187   3824    FFFF                      NOP                                    
  7188   3826    FFFF                      NOP                                    
  7189   3828    FFFF                      NOP                                    
  7190   382A    FFFF                      NOP                                    
  7191   382C    FFFF                      NOP                                    
  7192   382E    FFFF                      NOP                                    
  7193   3830    FFFF                      NOP                                    
  7194   3832    FFFF                      NOP                                    
  7195   3834    FFFF                      NOP                                    
  7196   3836    FFFF                      NOP                                    
  7197   3838    FFFF                      NOP                                    
  7198   383A    FFFF                      NOP                                    
  7199   383C    FFFF                      NOP                                    
  7200   383E    FFFF                      NOP                                    
  7201   3840    FFFF                      NOP                                    
  7202   3842    FFFF                      NOP                                    
  7203   3844    FFFF                      NOP                                    
  7204   3846    FFFF                      NOP                                    
  7205   3848    FFFF                      NOP                                    
  7206   384A    FFFF                      NOP                                    
  7207   384C    FFFF                      NOP                                    
  7208   384E    FFFF                      NOP                                    
  7209   3850    FFFF                      NOP                                    
  7210   3852    FFFF                      NOP                                    
  7211   3854    FFFF                      NOP                                    
  7212   3856    FFFF                      NOP                                    
  7213   3858    FFFF                      NOP                                    
  7214   385A    FFFF                      NOP                                    
  7215   385C    FFFF                      NOP                                    
  7216   385E    FFFF                      NOP                                    
  7217   3860    FFFF                      NOP                                    
  7218   3862    FFFF                      NOP                                    
  7219   3864    FFFF                      NOP                                    
  7220   3866    FFFF                      NOP                                    
  7221   3868    FFFF                      NOP                                    
  7222   386A    FFFF                      NOP                                    
  7223   386C    FFFF                      NOP                                    
  7224   386E    FFFF                      NOP                                    
  7225   3870    FFFF                      NOP                                    
  7226   3872    FFFF                      NOP                                    
  7227   3874    FFFF                      NOP                                    
  7228   3876    FFFF                      NOP                                    
  7229   3878    FFFF                      NOP                                    
  7230   387A    FFFF                      NOP                                    
  7231   387C    FFFF                      NOP                                    
  7232   387E    FFFF                      NOP                                    
  7233   3880    FFFF                      NOP                                    
  7234   3882    FFFF                      NOP                                    
  7235   3884    FFFF                      NOP                                    
  7236   3886    FFFF                      NOP                                    
  7237   3888    FFFF                      NOP                                    
  7238   388A    FFFF                      NOP                                    
  7239   388C    FFFF                      NOP                                    
  7240   388E    FFFF                      NOP                                    
  7241   3890    FFFF                      NOP                                    
  7242   3892    FFFF                      NOP                                    
  7243   3894    FFFF                      NOP                                    
  7244   3896    FFFF                      NOP                                    
  7245   3898    FFFF                      NOP                                    
  7246   389A    FFFF                      NOP                                    
  7247   389C    FFFF                      NOP                                    
  7248   389E    FFFF                      NOP                                    
  7249   38A0    FFFF                      NOP                                    
  7250   38A2    FFFF                      NOP                                    
  7251   38A4    FFFF                      NOP                                    
  7252   38A6    FFFF                      NOP                                    
  7253   38A8    FFFF                      NOP                                    
  7254   38AA    FFFF                      NOP                                    
  7255   38AC    FFFF                      NOP                                    
  7256   38AE    FFFF                      NOP                                    
  7257   38B0    FFFF                      NOP                                    
  7258   38B2    FFFF                      NOP                                    
  7259   38B4    FFFF                      NOP                                    
  7260   38B6    FFFF                      NOP                                    
  7261   38B8    FFFF                      NOP                                    
  7262   38BA    FFFF                      NOP                                    
  7263   38BC    FFFF                      NOP                                    
  7264   38BE    FFFF                      NOP                                    
  7265   38C0    FFFF                      NOP                                    
  7266   38C2    FFFF                      NOP                                    
  7267   38C4    FFFF                      NOP                                    
  7268   38C6    FFFF                      NOP                                    
  7269   38C8    FFFF                      NOP                                    
  7270   38CA    FFFF                      NOP                                    
  7271   38CC    FFFF                      NOP                                    
  7272   38CE    FFFF                      NOP                                    
  7273   38D0    FFFF                      NOP                                    
  7274   38D2    FFFF                      NOP                                    
  7275   38D4    FFFF                      NOP                                    
  7276   38D6    FFFF                      NOP                                    
  7277   38D8    FFFF                      NOP                                    
  7278   38DA    FFFF                      NOP                                    
  7279   38DC    FFFF                      NOP                                    
  7280   38DE    FFFF                      NOP                                    
  7281   38E0    FFFF                      NOP                                    
  7282   38E2    FFFF                      NOP                                    
  7283   38E4    FFFF                      NOP                                    
  7284   38E6    FFFF                      NOP                                    
  7285   38E8    FFFF                      NOP                                    
  7286   38EA    FFFF                      NOP                                    
  7287   38EC    FFFF                      NOP                                    
  7288   38EE    FFFF                      NOP                                    
  7289   38F0    FFFF                      NOP                                    
  7290   38F2    FFFF                      NOP                                    
  7291   38F4    FFFF                      NOP                                    
  7292   38F6    FFFF                      NOP                                    
  7293   38F8    FFFF                      NOP                                    
  7294   38FA    FFFF                      NOP                                    
  7295   38FC    FFFF                      NOP                                    
  7296   38FE    FFFF                      NOP                                    
  7297   3900    FFFF                      NOP                                    
  7298   3902    FFFF                      NOP                                    
  7299   3904    FFFF                      NOP                                    
  7300   3906    FFFF                      NOP                                    
  7301   3908    FFFF                      NOP                                    
  7302   390A    FFFF                      NOP                                    
  7303   390C    FFFF                      NOP                                    
  7304   390E    FFFF                      NOP                                    
  7305   3910    FFFF                      NOP                                    
  7306   3912    FFFF                      NOP                                    
  7307   3914    FFFF                      NOP                                    
  7308   3916    FFFF                      NOP                                    
  7309   3918    FFFF                      NOP                                    
  7310   391A    FFFF                      NOP                                    
  7311   391C    FFFF                      NOP                                    
  7312   391E    FFFF                      NOP                                    
  7313   3920    FFFF                      NOP                                    
  7314   3922    FFFF                      NOP                                    
  7315   3924    FFFF                      NOP                                    
  7316   3926    FFFF                      NOP                                    
  7317   3928    FFFF                      NOP                                    
  7318   392A    FFFF                      NOP                                    
  7319   392C    FFFF                      NOP                                    
  7320   392E    FFFF                      NOP                                    
  7321   3930    FFFF                      NOP                                    
  7322   3932    FFFF                      NOP                                    
  7323   3934    FFFF                      NOP                                    
  7324   3936    FFFF                      NOP                                    
  7325   3938    FFFF                      NOP                                    
  7326   393A    FFFF                      NOP                                    
  7327   393C    FFFF                      NOP                                    
  7328   393E    FFFF                      NOP                                    
  7329   3940    FFFF                      NOP                                    
  7330   3942    FFFF                      NOP                                    
  7331   3944    FFFF                      NOP                                    
  7332   3946    FFFF                      NOP                                    
  7333   3948    FFFF                      NOP                                    
  7334   394A    FFFF                      NOP                                    
  7335   394C    FFFF                      NOP                                    
  7336   394E    FFFF                      NOP                                    
  7337   3950    FFFF                      NOP                                    
  7338   3952    FFFF                      NOP                                    
  7339   3954    FFFF                      NOP                                    
  7340   3956    FFFF                      NOP                                    
  7341   3958    FFFF                      NOP                                    
  7342   395A    FFFF                      NOP                                    
  7343   395C    FFFF                      NOP                                    
  7344   395E    FFFF                      NOP                                    
  7345   3960    FFFF                      NOP                                    
  7346   3962    FFFF                      NOP                                    
  7347   3964    FFFF                      NOP                                    
  7348   3966    FFFF                      NOP                                    
  7349   3968    FFFF                      NOP                                    
  7350   396A    FFFF                      NOP                                    
  7351   396C    FFFF                      NOP                                    
  7352   396E    FFFF                      NOP                                    
  7353   3970    FFFF                      NOP                                    
  7354   3972    FFFF                      NOP                                    
  7355   3974    FFFF                      NOP                                    
  7356   3976    FFFF                      NOP                                    
  7357   3978    FFFF                      NOP                                    
  7358   397A    FFFF                      NOP                                    
  7359   397C    FFFF                      NOP                                    
  7360   397E    FFFF                      NOP                                    
  7361   3980    FFFF                      NOP                                    
  7362   3982    FFFF                      NOP                                    
  7363   3984    FFFF                      NOP                                    
  7364   3986    FFFF                      NOP                                    
  7365   3988    FFFF                      NOP                                    
  7366   398A    FFFF                      NOP                                    
  7367   398C    FFFF                      NOP                                    
  7368   398E    FFFF                      NOP                                    
  7369   3990    FFFF                      NOP                                    
  7370   3992    FFFF                      NOP                                    
  7371   3994    FFFF                      NOP                                    
  7372   3996    FFFF                      NOP                                    
  7373   3998    FFFF                      NOP                                    
  7374   399A    FFFF                      NOP                                    
  7375   399C    FFFF                      NOP                                    
  7376   399E    FFFF                      NOP                                    
  7377   39A0    FFFF                      NOP                                    
  7378   39A2    FFFF                      NOP                                    
  7379   39A4    FFFF                      NOP                                    
  7380   39A6    FFFF                      NOP                                    
  7381   39A8    FFFF                      NOP                                    
  7382   39AA    FFFF                      NOP                                    
  7383   39AC    FFFF                      NOP                                    
  7384   39AE    FFFF                      NOP                                    
  7385   39B0    FFFF                      NOP                                    
  7386   39B2    FFFF                      NOP                                    
  7387   39B4    FFFF                      NOP                                    
  7388   39B6    FFFF                      NOP                                    
  7389   39B8    FFFF                      NOP                                    
  7390   39BA    FFFF                      NOP                                    
  7391   39BC    FFFF                      NOP                                    
  7392   39BE    FFFF                      NOP                                    
  7393   39C0    FFFF                      NOP                                    
  7394   39C2    FFFF                      NOP                                    
  7395   39C4    FFFF                      NOP                                    
  7396   39C6    FFFF                      NOP                                    
  7397   39C8    FFFF                      NOP                                    
  7398   39CA    FFFF                      NOP                                    
  7399   39CC    FFFF                      NOP                                    
  7400   39CE    FFFF                      NOP                                    
  7401   39D0    FFFF                      NOP                                    
  7402   39D2    FFFF                      NOP                                    
  7403   39D4    FFFF                      NOP                                    
  7404   39D6    FFFF                      NOP                                    
  7405   39D8    FFFF                      NOP                                    
  7406   39DA    FFFF                      NOP                                    
  7407   39DC    FFFF                      NOP                                    
  7408   39DE    FFFF                      NOP                                    
  7409   39E0    FFFF                      NOP                                    
  7410   39E2    FFFF                      NOP                                    
  7411   39E4    FFFF                      NOP                                    
  7412   39E6    FFFF                      NOP                                    
  7413   39E8    FFFF                      NOP                                    
  7414   39EA    FFFF                      NOP                                    
  7415   39EC    FFFF                      NOP                                    
  7416   39EE    FFFF                      NOP                                    
  7417   39F0    FFFF                      NOP                                    
  7418   39F2    FFFF                      NOP                                    
  7419   39F4    FFFF                      NOP                                    
  7420   39F6    FFFF                      NOP                                    
  7421   39F8    FFFF                      NOP                                    
  7422   39FA    FFFF                      NOP                                    
  7423   39FC    FFFF                      NOP                                    
  7424   39FE    FFFF                      NOP                                    
  7425   3A00    FFFF                      NOP                                    
  7426   3A02    FFFF                      NOP                                    
  7427   3A04    FFFF                      NOP                                    
  7428   3A06    FFFF                      NOP                                    
  7429   3A08    FFFF                      NOP                                    
  7430   3A0A    FFFF                      NOP                                    
  7431   3A0C    FFFF                      NOP                                    
  7432   3A0E    FFFF                      NOP                                    
  7433   3A10    FFFF                      NOP                                    
  7434   3A12    FFFF                      NOP                                    
  7435   3A14    FFFF                      NOP                                    
  7436   3A16    FFFF                      NOP                                    
  7437   3A18    FFFF                      NOP                                    
  7438   3A1A    FFFF                      NOP                                    
  7439   3A1C    FFFF                      NOP                                    
  7440   3A1E    FFFF                      NOP                                    
  7441   3A20    FFFF                      NOP                                    
  7442   3A22    FFFF                      NOP                                    
  7443   3A24    FFFF                      NOP                                    
  7444   3A26    FFFF                      NOP                                    
  7445   3A28    FFFF                      NOP                                    
  7446   3A2A    FFFF                      NOP                                    
  7447   3A2C    FFFF                      NOP                                    
  7448   3A2E    FFFF                      NOP                                    
  7449   3A30    FFFF                      NOP                                    
  7450   3A32    FFFF                      NOP                                    
  7451   3A34    FFFF                      NOP                                    
  7452   3A36    FFFF                      NOP                                    
  7453   3A38    FFFF                      NOP                                    
  7454   3A3A    FFFF                      NOP                                    
  7455   3A3C    FFFF                      NOP                                    
  7456   3A3E    FFFF                      NOP                                    
  7457   3A40    FFFF                      NOP                                    
  7458   3A42    FFFF                      NOP                                    
  7459   3A44    FFFF                      NOP                                    
  7460   3A46    FFFF                      NOP                                    
  7461   3A48    FFFF                      NOP                                    
  7462   3A4A    FFFF                      NOP                                    
  7463   3A4C    FFFF                      NOP                                    
  7464   3A4E    FFFF                      NOP                                    
  7465   3A50    FFFF                      NOP                                    
  7466   3A52    FFFF                      NOP                                    
  7467   3A54    FFFF                      NOP                                    
  7468   3A56    FFFF                      NOP                                    
  7469   3A58    FFFF                      NOP                                    
  7470   3A5A    FFFF                      NOP                                    
  7471   3A5C    FFFF                      NOP                                    
  7472   3A5E    FFFF                      NOP                                    
  7473   3A60    FFFF                      NOP                                    
  7474   3A62    FFFF                      NOP                                    
  7475   3A64    FFFF                      NOP                                    
  7476   3A66    FFFF                      NOP                                    
  7477   3A68    FFFF                      NOP                                    
  7478   3A6A    FFFF                      NOP                                    
  7479   3A6C    FFFF                      NOP                                    
  7480   3A6E    FFFF                      NOP                                    
  7481   3A70    FFFF                      NOP                                    
  7482   3A72    FFFF                      NOP                                    
  7483   3A74    FFFF                      NOP                                    
  7484   3A76    FFFF                      NOP                                    
  7485   3A78    FFFF                      NOP                                    
  7486   3A7A    FFFF                      NOP                                    
  7487   3A7C    FFFF                      NOP                                    
  7488   3A7E    FFFF                      NOP                                    
  7489   3A80    FFFF                      NOP                                    
  7490   3A82    FFFF                      NOP                                    
  7491   3A84    FFFF                      NOP                                    
  7492   3A86    FFFF                      NOP                                    
  7493   3A88    FFFF                      NOP                                    
  7494   3A8A    FFFF                      NOP                                    
  7495   3A8C    FFFF                      NOP                                    
  7496   3A8E    FFFF                      NOP                                    
  7497   3A90    FFFF                      NOP                                    
  7498   3A92    FFFF                      NOP                                    
  7499   3A94    FFFF                      NOP                                    
  7500   3A96    FFFF                      NOP                                    
  7501   3A98    FFFF                      NOP                                    
  7502   3A9A    FFFF                      NOP                                    
  7503   3A9C    FFFF                      NOP                                    
  7504   3A9E    FFFF                      NOP                                    
  7505   3AA0    FFFF                      NOP                                    
  7506   3AA2    FFFF                      NOP                                    
  7507   3AA4    FFFF                      NOP                                    
  7508   3AA6    FFFF                      NOP                                    
  7509   3AA8    FFFF                      NOP                                    
  7510   3AAA    FFFF                      NOP                                    
  7511   3AAC    FFFF                      NOP                                    
  7512   3AAE    FFFF                      NOP                                    
  7513   3AB0    FFFF                      NOP                                    
  7514   3AB2    FFFF                      NOP                                    
  7515   3AB4    FFFF                      NOP                                    
  7516   3AB6    FFFF                      NOP                                    
  7517   3AB8    FFFF                      NOP                                    
  7518   3ABA    FFFF                      NOP                                    
  7519   3ABC    FFFF                      NOP                                    
  7520   3ABE    FFFF                      NOP                                    
  7521   3AC0    FFFF                      NOP                                    
  7522   3AC2    FFFF                      NOP                                    
  7523   3AC4    FFFF                      NOP                                    
  7524   3AC6    FFFF                      NOP                                    
  7525   3AC8    FFFF                      NOP                                    
  7526   3ACA    FFFF                      NOP                                    
  7527   3ACC    FFFF                      NOP                                    
  7528   3ACE    FFFF                      NOP                                    
  7529   3AD0    FFFF                      NOP                                    
  7530   3AD2    FFFF                      NOP                                    
  7531   3AD4    FFFF                      NOP                                    
  7532   3AD6    FFFF                      NOP                                    
  7533   3AD8    FFFF                      NOP                                    
  7534   3ADA    FFFF                      NOP                                    
  7535   3ADC    FFFF                      NOP                                    
  7536   3ADE    FFFF                      NOP                                    
  7537   3AE0    FFFF                      NOP                                    
  7538   3AE2    FFFF                      NOP                                    
  7539   3AE4    FFFF                      NOP                                    
  7540   3AE6    FFFF                      NOP                                    
  7541   3AE8    FFFF                      NOP                                    
  7542   3AEA    FFFF                      NOP                                    
  7543   3AEC    FFFF                      NOP                                    
  7544   3AEE    FFFF                      NOP                                    
  7545   3AF0    FFFF                      NOP                                    
  7546   3AF2    FFFF                      NOP                                    
  7547   3AF4    FFFF                      NOP                                    
  7548   3AF6    FFFF                      NOP                                    
  7549   3AF8    FFFF                      NOP                                    
  7550   3AFA    FFFF                      NOP                                    
  7551   3AFC    FFFF                      NOP                                    
  7552   3AFE    FFFF                      NOP                                    
  7553   3B00    FFFF                      NOP                                    
  7554   3B02    FFFF                      NOP                                    
  7555   3B04    FFFF                      NOP                                    
  7556   3B06    FFFF                      NOP                                    
  7557   3B08    FFFF                      NOP                                    
  7558   3B0A    FFFF                      NOP                                    
  7559   3B0C    FFFF                      NOP                                    
  7560   3B0E    FFFF                      NOP                                    
  7561   3B10    FFFF                      NOP                                    
  7562   3B12    FFFF                      NOP                                    
  7563   3B14    FFFF                      NOP                                    
  7564   3B16    FFFF                      NOP                                    
  7565   3B18    FFFF                      NOP                                    
  7566   3B1A    FFFF                      NOP                                    
  7567   3B1C    FFFF                      NOP                                    
  7568   3B1E    FFFF                      NOP                                    
  7569   3B20    FFFF                      NOP                                    
  7570   3B22    FFFF                      NOP                                    
  7571   3B24    FFFF                      NOP                                    
  7572   3B26    FFFF                      NOP                                    
  7573   3B28    FFFF                      NOP                                    
  7574   3B2A    FFFF                      NOP                                    
  7575   3B2C    FFFF                      NOP                                    
  7576   3B2E    FFFF                      NOP                                    
  7577   3B30    FFFF                      NOP                                    
  7578   3B32    FFFF                      NOP                                    
  7579   3B34    FFFF                      NOP                                    
  7580   3B36    FFFF                      NOP                                    
  7581   3B38    FFFF                      NOP                                    
  7582   3B3A    FFFF                      NOP                                    
  7583   3B3C    FFFF                      NOP                                    
  7584   3B3E    FFFF                      NOP                                    
  7585   3B40    FFFF                      NOP                                    
  7586   3B42    FFFF                      NOP                                    
  7587   3B44    FFFF                      NOP                                    
  7588   3B46    FFFF                      NOP                                    
  7589   3B48    FFFF                      NOP                                    
  7590   3B4A    FFFF                      NOP                                    
  7591   3B4C    FFFF                      NOP                                    
  7592   3B4E    FFFF                      NOP                                    
  7593   3B50    FFFF                      NOP                                    
  7594   3B52    FFFF                      NOP                                    
  7595   3B54    FFFF                      NOP                                    
  7596   3B56    FFFF                      NOP                                    
  7597   3B58    FFFF                      NOP                                    
  7598   3B5A    FFFF                      NOP                                    
  7599   3B5C    FFFF                      NOP                                    
  7600   3B5E    FFFF                      NOP                                    
  7601   3B60    FFFF                      NOP                                    
  7602   3B62    FFFF                      NOP                                    
  7603   3B64    FFFF                      NOP                                    
  7604   3B66    FFFF                      NOP                                    
  7605   3B68    FFFF                      NOP                                    
  7606   3B6A    FFFF                      NOP                                    
  7607   3B6C    FFFF                      NOP                                    
  7608   3B6E    FFFF                      NOP                                    
  7609   3B70    FFFF                      NOP                                    
  7610   3B72    FFFF                      NOP                                    
  7611   3B74    FFFF                      NOP                                    
  7612   3B76    FFFF                      NOP                                    
  7613   3B78    FFFF                      NOP                                    
  7614   3B7A    FFFF                      NOP                                    
  7615   3B7C    FFFF                      NOP                                    
  7616   3B7E    FFFF                      NOP                                    
  7617   3B80    FFFF                      NOP                                    
  7618   3B82    FFFF                      NOP                                    
  7619   3B84    FFFF                      NOP                                    
  7620   3B86    FFFF                      NOP                                    
  7621   3B88    FFFF                      NOP                                    
  7622   3B8A    FFFF                      NOP                                    
  7623   3B8C    FFFF                      NOP                                    
  7624   3B8E    FFFF                      NOP                                    
  7625   3B90    FFFF                      NOP                                    
  7626   3B92    FFFF                      NOP                                    
  7627   3B94    FFFF                      NOP                                    
  7628   3B96    FFFF                      NOP                                    
  7629   3B98    FFFF                      NOP                                    
  7630   3B9A    FFFF                      NOP                                    
  7631   3B9C    FFFF                      NOP                                    
  7632   3B9E    FFFF                      NOP                                    
  7633   3BA0    FFFF                      NOP                                    
  7634   3BA2    FFFF                      NOP                                    
  7635   3BA4    FFFF                      NOP                                    
  7636   3BA6    FFFF                      NOP                                    
  7637   3BA8    FFFF                      NOP                                    
  7638   3BAA    FFFF                      NOP                                    
  7639   3BAC    FFFF                      NOP                                    
  7640   3BAE    FFFF                      NOP                                    
  7641   3BB0    FFFF                      NOP                                    
  7642   3BB2    FFFF                      NOP                                    
  7643   3BB4    FFFF                      NOP                                    
  7644   3BB6    FFFF                      NOP                                    
  7645   3BB8    FFFF                      NOP                                    
  7646   3BBA    FFFF                      NOP                                    
  7647   3BBC    FFFF                      NOP                                    
  7648   3BBE    FFFF                      NOP                                    
  7649   3BC0    FFFF                      NOP                                    
  7650   3BC2    FFFF                      NOP                                    
  7651   3BC4    FFFF                      NOP                                    
  7652   3BC6    FFFF                      NOP                                    
  7653   3BC8    FFFF                      NOP                                    
  7654   3BCA    FFFF                      NOP                                    
  7655   3BCC    FFFF                      NOP                                    
  7656   3BCE    FFFF                      NOP                                    
  7657   3BD0    FFFF                      NOP                                    
  7658   3BD2    FFFF                      NOP                                    
  7659   3BD4    FFFF                      NOP                                    
  7660   3BD6    FFFF                      NOP                                    
  7661   3BD8    FFFF                      NOP                                    
  7662   3BDA    FFFF                      NOP                                    
  7663   3BDC    FFFF                      NOP                                    
  7664   3BDE    FFFF                      NOP                                    
  7665   3BE0    FFFF                      NOP                                    
  7666   3BE2    FFFF                      NOP                                    
  7667   3BE4    FFFF                      NOP                                    
  7668   3BE6    FFFF                      NOP                                    
  7669   3BE8    FFFF                      NOP                                    
  7670   3BEA    FFFF                      NOP                                    
  7671   3BEC    FFFF                      NOP                                    
  7672   3BEE    FFFF                      NOP                                    
  7673   3BF0    FFFF                      NOP                                    
  7674   3BF2    FFFF                      NOP                                    
  7675   3BF4    FFFF                      NOP                                    
  7676   3BF6    FFFF                      NOP                                    
  7677   3BF8    FFFF                      NOP                                    
  7678   3BFA    FFFF                      NOP                                    
  7679   3BFC    FFFF                      NOP                                    
  7680   3BFE    FFFF                      NOP                                    
  7681   3C00    FFFF                      NOP                                    
  7682   3C02    FFFF                      NOP                                    
  7683   3C04    FFFF                      NOP                                    
  7684   3C06    FFFF                      NOP                                    
  7685   3C08    FFFF                      NOP                                    
  7686   3C0A    FFFF                      NOP                                    
  7687   3C0C    FFFF                      NOP                                    
  7688   3C0E    FFFF                      NOP                                    
  7689   3C10    FFFF                      NOP                                    
  7690   3C12    FFFF                      NOP                                    
  7691   3C14    FFFF                      NOP                                    
  7692   3C16    FFFF                      NOP                                    
  7693   3C18    FFFF                      NOP                                    
  7694   3C1A    FFFF                      NOP                                    
  7695   3C1C    FFFF                      NOP                                    
  7696   3C1E    FFFF                      NOP                                    
  7697   3C20    FFFF                      NOP                                    
  7698   3C22    FFFF                      NOP                                    
  7699   3C24    FFFF                      NOP                                    
  7700   3C26    FFFF                      NOP                                    
  7701   3C28    FFFF                      NOP                                    
  7702   3C2A    FFFF                      NOP                                    
  7703   3C2C    FFFF                      NOP                                    
  7704   3C2E    FFFF                      NOP                                    
  7705   3C30    FFFF                      NOP                                    
  7706   3C32    FFFF                      NOP                                    
  7707   3C34    FFFF                      NOP                                    
  7708   3C36    FFFF                      NOP                                    
  7709   3C38    FFFF                      NOP                                    
  7710   3C3A    FFFF                      NOP                                    
  7711   3C3C    FFFF                      NOP                                    
  7712   3C3E    FFFF                      NOP                                    
  7713   3C40    FFFF                      NOP                                    
  7714   3C42    FFFF                      NOP                                    
  7715   3C44    FFFF                      NOP                                    
  7716   3C46    FFFF                      NOP                                    
  7717   3C48    FFFF                      NOP                                    
  7718   3C4A    FFFF                      NOP                                    
  7719   3C4C    FFFF                      NOP                                    
  7720   3C4E    FFFF                      NOP                                    
  7721   3C50    FFFF                      NOP                                    
  7722   3C52    FFFF                      NOP                                    
  7723   3C54    FFFF                      NOP                                    
  7724   3C56    FFFF                      NOP                                    
  7725   3C58    FFFF                      NOP                                    
  7726   3C5A    FFFF                      NOP                                    
  7727   3C5C    FFFF                      NOP                                    
  7728   3C5E    FFFF                      NOP                                    
  7729   3C60    FFFF                      NOP                                    
  7730   3C62    FFFF                      NOP                                    
  7731   3C64    FFFF                      NOP                                    
  7732   3C66    FFFF                      NOP                                    
  7733   3C68    FFFF                      NOP                                    
  7734   3C6A    FFFF                      NOP                                    
  7735   3C6C    FFFF                      NOP                                    
  7736   3C6E    FFFF                      NOP                                    
  7737   3C70    FFFF                      NOP                                    
  7738   3C72    FFFF                      NOP                                    
  7739   3C74    FFFF                      NOP                                    
  7740   3C76    FFFF                      NOP                                    
  7741   3C78    FFFF                      NOP                                    
  7742   3C7A    FFFF                      NOP                                    
  7743   3C7C    FFFF                      NOP                                    
  7744   3C7E    FFFF                      NOP                                    
  7745   3C80    FFFF                      NOP                                    
  7746   3C82    FFFF                      NOP                                    
  7747   3C84    FFFF                      NOP                                    
  7748   3C86    FFFF                      NOP                                    
  7749   3C88    FFFF                      NOP                                    
  7750   3C8A    FFFF                      NOP                                    
  7751   3C8C    FFFF                      NOP                                    
  7752   3C8E    FFFF                      NOP                                    
  7753   3C90    FFFF                      NOP                                    
  7754   3C92    FFFF                      NOP                                    
  7755   3C94    FFFF                      NOP                                    
  7756   3C96    FFFF                      NOP                                    
  7757   3C98    FFFF                      NOP                                    
  7758   3C9A    FFFF                      NOP                                    
  7759   3C9C    FFFF                      NOP                                    
  7760   3C9E    FFFF                      NOP                                    
  7761   3CA0    FFFF                      NOP                                    
  7762   3CA2    FFFF                      NOP                                    
  7763   3CA4    FFFF                      NOP                                    
  7764   3CA6    FFFF                      NOP                                    
  7765   3CA8    FFFF                      NOP                                    
  7766   3CAA    FFFF                      NOP                                    
  7767   3CAC    FFFF                      NOP                                    
  7768   3CAE    FFFF                      NOP                                    
  7769   3CB0    FFFF                      NOP                                    
  7770   3CB2    FFFF                      NOP                                    
  7771   3CB4    FFFF                      NOP                                    
  7772   3CB6    FFFF                      NOP                                    
  7773   3CB8    FFFF                      NOP                                    
  7774   3CBA    FFFF                      NOP                                    
  7775   3CBC    FFFF                      NOP                                    
  7776   3CBE    FFFF                      NOP                                    
  7777   3CC0    FFFF                      NOP                                    
  7778   3CC2    FFFF                      NOP                                    
  7779   3CC4    FFFF                      NOP                                    
  7780   3CC6    FFFF                      NOP                                    
  7781   3CC8    FFFF                      NOP                                    
  7782   3CCA    FFFF                      NOP                                    
  7783   3CCC    FFFF                      NOP                                    
  7784   3CCE    FFFF                      NOP                                    
  7785   3CD0    FFFF                      NOP                                    
  7786   3CD2    FFFF                      NOP                                    
  7787   3CD4    FFFF                      NOP                                    
  7788   3CD6    FFFF                      NOP                                    
  7789   3CD8    FFFF                      NOP                                    
  7790   3CDA    FFFF                      NOP                                    
  7791   3CDC    FFFF                      NOP                                    
  7792   3CDE    FFFF                      NOP                                    
  7793   3CE0    FFFF                      NOP                                    
  7794   3CE2    FFFF                      NOP                                    
  7795   3CE4    FFFF                      NOP                                    
  7796   3CE6    FFFF                      NOP                                    
  7797   3CE8    FFFF                      NOP                                    
  7798   3CEA    FFFF                      NOP                                    
  7799   3CEC    FFFF                      NOP                                    
  7800   3CEE    FFFF                      NOP                                    
  7801   3CF0    FFFF                      NOP                                    
  7802   3CF2    FFFF                      NOP                                    
  7803   3CF4    FFFF                      NOP                                    
  7804   3CF6    FFFF                      NOP                                    
  7805   3CF8    FFFF                      NOP                                    
  7806   3CFA    FFFF                      NOP                                    
  7807   3CFC    FFFF                      NOP                                    
  7808   3CFE    FFFF                      NOP                                    
  7809   3D00    FFFF                      NOP                                    
  7810   3D02    FFFF                      NOP                                    
  7811   3D04    FFFF                      NOP                                    
  7812   3D06    FFFF                      NOP                                    
  7813   3D08    FFFF                      NOP                                    
  7814   3D0A    FFFF                      NOP                                    
  7815   3D0C    FFFF                      NOP                                    
  7816   3D0E    FFFF                      NOP                                    
  7817   3D10    FFFF                      NOP                                    
  7818   3D12    FFFF                      NOP                                    
  7819   3D14    FFFF                      NOP                                    
  7820   3D16    FFFF                      NOP                                    
  7821   3D18    FFFF                      NOP                                    
  7822   3D1A    FFFF                      NOP                                    
  7823   3D1C    FFFF                      NOP                                    
  7824   3D1E    FFFF                      NOP                                    
  7825   3D20    FFFF                      NOP                                    
  7826   3D22    FFFF                      NOP                                    
  7827   3D24    FFFF                      NOP                                    
  7828   3D26    FFFF                      NOP                                    
  7829   3D28    FFFF                      NOP                                    
  7830   3D2A    FFFF                      NOP                                    
  7831   3D2C    FFFF                      NOP                                    
  7832   3D2E    FFFF                      NOP                                    
  7833   3D30    FFFF                      NOP                                    
  7834   3D32    FFFF                      NOP                                    
  7835   3D34    FFFF                      NOP                                    
  7836   3D36    FFFF                      NOP                                    
  7837   3D38    FFFF                      NOP                                    
  7838   3D3A    FFFF                      NOP                                    
  7839   3D3C    FFFF                      NOP                                    
  7840   3D3E    FFFF                      NOP                                    
  7841   3D40    FFFF                      NOP                                    
  7842   3D42    FFFF                      NOP                                    
  7843   3D44    FFFF                      NOP                                    
  7844   3D46    FFFF                      NOP                                    
  7845   3D48    FFFF                      NOP                                    
  7846   3D4A    FFFF                      NOP                                    
  7847   3D4C    FFFF                      NOP                                    
  7848   3D4E    FFFF                      NOP                                    
  7849   3D50    FFFF                      NOP                                    
  7850   3D52    FFFF                      NOP                                    
  7851   3D54    FFFF                      NOP                                    
  7852   3D56    FFFF                      NOP                                    
  7853   3D58    FFFF                      NOP                                    
  7854   3D5A    FFFF                      NOP                                    
  7855   3D5C    FFFF                      NOP                                    
  7856   3D5E    FFFF                      NOP                                    
  7857   3D60    FFFF                      NOP                                    
  7858   3D62    FFFF                      NOP                                    
  7859   3D64    FFFF                      NOP                                    
  7860   3D66    FFFF                      NOP                                    
  7861   3D68    FFFF                      NOP                                    
  7862   3D6A    FFFF                      NOP                                    
  7863   3D6C    FFFF                      NOP                                    
  7864   3D6E    FFFF                      NOP                                    
  7865   3D70    FFFF                      NOP                                    
  7866   3D72    FFFF                      NOP                                    
  7867   3D74    FFFF                      NOP                                    
  7868   3D76    FFFF                      NOP                                    
  7869   3D78    FFFF                      NOP                                    
  7870   3D7A    FFFF                      NOP                                    
  7871   3D7C    FFFF                      NOP                                    
  7872   3D7E    FFFF                      NOP                                    
  7873   3D80    FFFF                      NOP                                    
  7874   3D82    FFFF                      NOP                                    
  7875   3D84    FFFF                      NOP                                    
  7876   3D86    FFFF                      NOP                                    
  7877   3D88    FFFF                      NOP                                    
  7878   3D8A    FFFF                      NOP                                    
  7879   3D8C    FFFF                      NOP                                    
  7880   3D8E    FFFF                      NOP                                    
  7881   3D90    FFFF                      NOP                                    
  7882   3D92    FFFF                      NOP                                    
  7883   3D94    FFFF                      NOP                                    
  7884   3D96    FFFF                      NOP                                    
  7885   3D98    FFFF                      NOP                                    
  7886   3D9A    FFFF                      NOP                                    
  7887   3D9C    FFFF                      NOP                                    
  7888   3D9E    FFFF                      NOP                                    
  7889   3DA0    FFFF                      NOP                                    
  7890   3DA2    FFFF                      NOP                                    
  7891   3DA4    FFFF                      NOP                                    
  7892   3DA6    FFFF                      NOP                                    
  7893   3DA8    FFFF                      NOP                                    
  7894   3DAA    FFFF                      NOP                                    
  7895   3DAC    FFFF                      NOP                                    
  7896   3DAE    FFFF                      NOP                                    
  7897   3DB0    FFFF                      NOP                                    
  7898   3DB2    FFFF                      NOP                                    
  7899   3DB4    FFFF                      NOP                                    
  7900   3DB6    FFFF                      NOP                                    
  7901   3DB8    FFFF                      NOP                                    
  7902   3DBA    FFFF                      NOP                                    
  7903   3DBC    FFFF                      NOP                                    
  7904   3DBE    FFFF                      NOP                                    
  7905   3DC0    FFFF                      NOP                                    
  7906   3DC2    FFFF                      NOP                                    
  7907   3DC4    FFFF                      NOP                                    
  7908   3DC6    FFFF                      NOP                                    
  7909   3DC8    FFFF                      NOP                                    
  7910   3DCA    FFFF                      NOP                                    
  7911   3DCC    FFFF                      NOP                                    
  7912   3DCE    FFFF                      NOP                                    
  7913   3DD0    FFFF                      NOP                                    
  7914   3DD2    FFFF                      NOP                                    
  7915   3DD4    FFFF                      NOP                                    
  7916   3DD6    FFFF                      NOP                                    
  7917   3DD8    FFFF                      NOP                                    
  7918   3DDA    FFFF                      NOP                                    
  7919   3DDC    FFFF                      NOP                                    
  7920   3DDE    FFFF                      NOP                                    
  7921   3DE0    FFFF                      NOP                                    
  7922   3DE2    FFFF                      NOP                                    
  7923   3DE4    FFFF                      NOP                                    
  7924   3DE6    FFFF                      NOP                                    
  7925   3DE8    FFFF                      NOP                                    
  7926   3DEA    FFFF                      NOP                                    
  7927   3DEC    FFFF                      NOP                                    
  7928   3DEE    FFFF                      NOP                                    
  7929   3DF0    FFFF                      NOP                                    
  7930   3DF2    FFFF                      NOP                                    
  7931   3DF4    FFFF                      NOP                                    
  7932   3DF6    FFFF                      NOP                                    
  7933   3DF8    FFFF                      NOP                                    
  7934   3DFA    FFFF                      NOP                                    
  7935   3DFC    FFFF                      NOP                                    
  7936   3DFE    FFFF                      NOP                                    
  7937   3E00    FFFF                      NOP                                    
  7938   3E02    FFFF                      NOP                                    
  7939   3E04    FFFF                      NOP                                    
  7940   3E06    FFFF                      NOP                                    
  7941   3E08    FFFF                      NOP                                    
  7942   3E0A    FFFF                      NOP                                    
  7943   3E0C    FFFF                      NOP                                    
  7944   3E0E    FFFF                      NOP                                    
  7945   3E10    FFFF                      NOP                                    
  7946   3E12    FFFF                      NOP                                    
  7947   3E14    FFFF                      NOP                                    
  7948   3E16    FFFF                      NOP                                    
  7949   3E18    FFFF                      NOP                                    
  7950   3E1A    FFFF                      NOP                                    
  7951   3E1C    FFFF                      NOP                                    
  7952   3E1E    FFFF                      NOP                                    
  7953   3E20    FFFF                      NOP                                    
  7954   3E22    FFFF                      NOP                                    
  7955   3E24    FFFF                      NOP                                    
  7956   3E26    FFFF                      NOP                                    
  7957   3E28    FFFF                      NOP                                    
  7958   3E2A    FFFF                      NOP                                    
  7959   3E2C    FFFF                      NOP                                    
  7960   3E2E    FFFF                      NOP                                    
  7961   3E30    FFFF                      NOP                                    
  7962   3E32    FFFF                      NOP                                    
  7963   3E34    FFFF                      NOP                                    
  7964   3E36    FFFF                      NOP                                    
  7965   3E38    FFFF                      NOP                                    
  7966   3E3A    FFFF                      NOP                                    
  7967   3E3C    FFFF                      NOP                                    
  7968   3E3E    FFFF                      NOP                                    
  7969   3E40    FFFF                      NOP                                    
  7970   3E42    FFFF                      NOP                                    
  7971   3E44    FFFF                      NOP                                    
  7972   3E46    FFFF                      NOP                                    
  7973   3E48    FFFF                      NOP                                    
  7974   3E4A    FFFF                      NOP                                    
  7975   3E4C    FFFF                      NOP                                    
  7976   3E4E    FFFF                      NOP                                    
  7977   3E50    FFFF                      NOP                                    
  7978   3E52    FFFF                      NOP                                    
  7979   3E54    FFFF                      NOP                                    
  7980   3E56    FFFF                      NOP                                    
  7981   3E58    FFFF                      NOP                                    
  7982   3E5A    FFFF                      NOP                                    
  7983   3E5C    FFFF                      NOP                                    
  7984   3E5E    FFFF                      NOP                                    
  7985   3E60    FFFF                      NOP                                    
  7986   3E62    FFFF                      NOP                                    
  7987   3E64    FFFF                      NOP                                    
  7988   3E66    FFFF                      NOP                                    
  7989   3E68    FFFF                      NOP                                    
  7990   3E6A    FFFF                      NOP                                    
  7991   3E6C    FFFF                      NOP                                    
  7992   3E6E    FFFF                      NOP                                    
  7993   3E70    FFFF                      NOP                                    
  7994   3E72    FFFF                      NOP                                    
  7995   3E74    FFFF                      NOP                                    
  7996   3E76    FFFF                      NOP                                    
  7997   3E78    FFFF                      NOP                                    
  7998   3E7A    FFFF                      NOP                                    
  7999   3E7C    FFFF                      NOP                                    
  8000   3E7E    FFFF                      NOP                                    
  8001   3E80    FFFF                      NOP                                    
  8002   3E82    FFFF                      NOP                                    
  8003   3E84    FFFF                      NOP                                    
  8004   3E86    FFFF                      NOP                                    
  8005   3E88    FFFF                      NOP                                    
  8006   3E8A    FFFF                      NOP                                    
  8007   3E8C    FFFF                      NOP                                    
  8008   3E8E    FFFF                      NOP                                    
  8009   3E90    FFFF                      NOP                                    
  8010   3E92    FFFF                      NOP                                    
  8011   3E94    FFFF                      NOP                                    
  8012   3E96    FFFF                      NOP                                    
  8013   3E98    FFFF                      NOP                                    
  8014   3E9A    FFFF                      NOP                                    
  8015   3E9C    FFFF                      NOP                                    
  8016   3E9E    FFFF                      NOP                                    
  8017   3EA0    FFFF                      NOP                                    
  8018   3EA2    FFFF                      NOP                                    
  8019   3EA4    FFFF                      NOP                                    
  8020   3EA6    FFFF                      NOP                                    
  8021   3EA8    FFFF                      NOP                                    
  8022   3EAA    FFFF                      NOP                                    
  8023   3EAC    FFFF                      NOP                                    
  8024   3EAE    FFFF                      NOP                                    
  8025   3EB0    FFFF                      NOP                                    
  8026   3EB2    FFFF                      NOP                                    
  8027   3EB4    FFFF                      NOP                                    
  8028   3EB6    FFFF                      NOP                                    
  8029   3EB8    FFFF                      NOP                                    
  8030   3EBA    FFFF                      NOP                                    
  8031   3EBC    FFFF                      NOP                                    
  8032   3EBE    FFFF                      NOP                                    
  8033   3EC0    FFFF                      NOP                                    
  8034   3EC2    FFFF                      NOP                                    
  8035   3EC4    FFFF                      NOP                                    
  8036   3EC6    FFFF                      NOP                                    
  8037   3EC8    FFFF                      NOP                                    
  8038   3ECA    FFFF                      NOP                                    
  8039   3ECC    FFFF                      NOP                                    
  8040   3ECE    FFFF                      NOP                                    
  8041   3ED0    FFFF                      NOP                                    
  8042   3ED2    FFFF                      NOP                                    
  8043   3ED4    FFFF                      NOP                                    
  8044   3ED6    FFFF                      NOP                                    
  8045   3ED8    FFFF                      NOP                                    
  8046   3EDA    FFFF                      NOP                                    
  8047   3EDC    FFFF                      NOP                                    
  8048   3EDE    FFFF                      NOP                                    
  8049   3EE0    FFFF                      NOP                                    
  8050   3EE2    FFFF                      NOP                                    
  8051   3EE4    FFFF                      NOP                                    
  8052   3EE6    FFFF                      NOP                                    
  8053   3EE8    FFFF                      NOP                                    
  8054   3EEA    FFFF                      NOP                                    
  8055   3EEC    FFFF                      NOP                                    
  8056   3EEE    FFFF                      NOP                                    
  8057   3EF0    FFFF                      NOP                                    
  8058   3EF2    FFFF                      NOP                                    
  8059   3EF4    FFFF                      NOP                                    
  8060   3EF6    FFFF                      NOP                                    
  8061   3EF8    FFFF                      NOP                                    
  8062   3EFA    FFFF                      NOP                                    
  8063   3EFC    FFFF                      NOP                                    
  8064   3EFE    FFFF                      NOP                                    
  8065   3F00    FFFF                      NOP                                    
  8066   3F02    FFFF                      NOP                                    
  8067   3F04    FFFF                      NOP                                    
  8068   3F06    FFFF                      NOP                                    
  8069   3F08    FFFF                      NOP                                    
  8070   3F0A    FFFF                      NOP                                    
  8071   3F0C    FFFF                      NOP                                    
  8072   3F0E    FFFF                      NOP                                    
  8073   3F10    FFFF                      NOP                                    
  8074   3F12    FFFF                      NOP                                    
  8075   3F14    FFFF                      NOP                                    
  8076   3F16    FFFF                      NOP                                    
  8077   3F18    FFFF                      NOP                                    
  8078   3F1A    FFFF                      NOP                                    
  8079   3F1C    FFFF                      NOP                                    
  8080   3F1E    FFFF                      NOP                                    
  8081   3F20    FFFF                      NOP                                    
  8082   3F22    FFFF                      NOP                                    
  8083   3F24    FFFF                      NOP                                    
  8084   3F26    FFFF                      NOP                                    
  8085   3F28    FFFF                      NOP                                    
  8086   3F2A    FFFF                      NOP                                    
  8087   3F2C    FFFF                      NOP                                    
  8088   3F2E    FFFF                      NOP                                    
  8089   3F30    FFFF                      NOP                                    
  8090   3F32    FFFF                      NOP                                    
  8091   3F34    FFFF                      NOP                                    
  8092   3F36    FFFF                      NOP                                    
  8093   3F38    FFFF                      NOP                                    
  8094   3F3A    FFFF                      NOP                                    
  8095   3F3C    FFFF                      NOP                                    
  8096   3F3E    FFFF                      NOP                                    
  8097   3F40    FFFF                      NOP                                    
  8098   3F42    FFFF                      NOP                                    
  8099   3F44    FFFF                      NOP                                    
  8100   3F46    FFFF                      NOP                                    
  8101   3F48    FFFF                      NOP                                    
  8102   3F4A    FFFF                      NOP                                    
  8103   3F4C    FFFF                      NOP                                    
  8104   3F4E    FFFF                      NOP                                    
  8105   3F50    FFFF                      NOP                                    
  8106   3F52    FFFF                      NOP                                    
  8107   3F54    FFFF                      NOP                                    
  8108   3F56    FFFF                      NOP                                    
  8109   3F58    FFFF                      NOP                                    
  8110   3F5A    FFFF                      NOP                                    
  8111   3F5C    FFFF                      NOP                                    
  8112   3F5E    FFFF                      NOP                                    
  8113   3F60    FFFF                      NOP                                    
  8114   3F62    FFFF                      NOP                                    
  8115   3F64    FFFF                      NOP                                    
  8116   3F66    FFFF                      NOP                                    
  8117   3F68    FFFF                      NOP                                    
  8118   3F6A    FFFF                      NOP                                    
  8119   3F6C    FFFF                      NOP                                    
  8120   3F6E    FFFF                      NOP                                    
  8121   3F70    FFFF                      NOP                                    
  8122   3F72    FFFF                      NOP                                    
  8123   3F74    FFFF                      NOP                                    
  8124   3F76    FFFF                      NOP                                    
  8125   3F78    FFFF                      NOP                                    
  8126   3F7A    FFFF                      NOP                                    
  8127   3F7C    FFFF                      NOP                                    
  8128   3F7E    FFFF                      NOP                                    
  8129   3F80    FFFF                      NOP                                    
  8130   3F82    FFFF                      NOP                                    
  8131   3F84    FFFF                      NOP                                    
  8132   3F86    FFFF                      NOP                                    
  8133   3F88    FFFF                      NOP                                    
  8134   3F8A    FFFF                      NOP                                    
  8135   3F8C    FFFF                      NOP                                    
  8136   3F8E    FFFF                      NOP                                    
  8137   3F90    FFFF                      NOP                                    
  8138   3F92    FFFF                      NOP                                    
  8139   3F94    FFFF                      NOP                                    
  8140   3F96    FFFF                      NOP                                    
  8141   3F98    FFFF                      NOP                                    
  8142   3F9A    FFFF                      NOP                                    
  8143   3F9C    FFFF                      NOP                                    
  8144   3F9E    FFFF                      NOP                                    
  8145   3FA0    FFFF                      NOP                                    
  8146   3FA2    FFFF                      NOP                                    
  8147   3FA4    FFFF                      NOP                                    
  8148   3FA6    FFFF                      NOP                                    
  8149   3FA8    FFFF                      NOP                                    
  8150   3FAA    FFFF                      NOP                                    
  8151   3FAC    FFFF                      NOP                                    
  8152   3FAE    FFFF                      NOP                                    
  8153   3FB0    FFFF                      NOP                                    
  8154   3FB2    FFFF                      NOP                                    
  8155   3FB4    FFFF                      NOP                                    
  8156   3FB6    FFFF                      NOP                                    
  8157   3FB8    FFFF                      NOP                                    
  8158   3FBA    FFFF                      NOP                                    
  8159   3FBC    FFFF                      NOP                                    
  8160   3FBE    FFFF                      NOP                                    
  8161   3FC0    FFFF                      NOP                                    
  8162   3FC2    FFFF                      NOP                                    
  8163   3FC4    FFFF                      NOP                                    
  8164   3FC6    FFFF                      NOP                                    
  8165   3FC8    FFFF                      NOP                                    
  8166   3FCA    FFFF                      NOP                                    
  8167   3FCC    FFFF                      NOP                                    
  8168   3FCE    FFFF                      NOP                                    
  8169   3FD0    FFFF                      NOP                                    
  8170   3FD2    FFFF                      NOP                                    
  8171   3FD4    FFFF                      NOP                                    
  8172   3FD6    FFFF                      NOP                                    
  8173   3FD8    FFFF                      NOP                                    
  8174   3FDA    FFFF                      NOP                                    
  8175   3FDC    FFFF                      NOP                                    
  8176   3FDE    FFFF                      NOP                                    
  8177   3FE0    FFFF                      NOP                                    
  8178   3FE2    FFFF                      NOP                                    
  8179   3FE4    FFFF                      NOP                                    
  8180   3FE6    FFFF                      NOP                                    
  8181   3FE8    FFFF                      NOP                                    
  8182   3FEA    FFFF                      NOP                                    
  8183   3FEC    FFFF                      NOP                                    
  8184   3FEE    FFFF                      NOP                                    
  8185   3FF0    FFFF                      NOP                                    
  8186   3FF2    FFFF                      NOP                                    
  8187   3FF4    FFFF                      NOP                                    
  8188   3FF6    FFFF                      NOP                                    
  8189   3FF8    FFFF                      NOP                                    
  8190   3FFA    FFFF                      NOP                                    
  8191   3FFC    FFFF                      NOP                                    
  8192   3FFE    FFFF                      NOP                                    
