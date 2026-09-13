// 100a49e04 FUN_100a49e04

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_opt_self replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Heritage AFTER dead removal. Example location: d1 : 0x000100a4abc8 */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */
/* WARNING: Restarted to delay deadcode elimination for space: register */

ID FUN_100a49e04(void)

{
  double *pdVar1;
  uint uVar2;
  byte bVar3;
  byte bVar4;
  undefined8 uVar5;
  byte bVar6;
  code *pcVar7;
  bool bVar8;
  undefined *puVar9;
  ID self;
  ID IVar10;
  undefined *puVar11;
  NSString *pNVar12;
  ID IVar13;
  ID IVar14;
  undefined8 uVar15;
  undefined *puVar16;
  undefined *puVar17;
  NSDictionary *pNVar18;
  ID IVar19;
  ID IVar20;
  NSNumber *pNVar21;
  class_t *pcVar22;
  class_t *pcVar23;
  ulong uVar24;
  long lVar25;
  long lVar26;
  ulong uVar27;
  long lVar28;
  undefined8 uVar29;
  undefined8 uVar30;
  undefined8 uVar31;
  undefined8 uVar32;
  undefined8 uVar33;
  undefined8 uVar34;
  undefined8 uVar35;
  undefined8 uVar36;
  ulong uVar37;
  ulong uVar38;
  ulong uVar39;
  long unaff_x20;
  ulong uVar40;
  ulong uVar41;
  ulong uVar42;
  undefined1 *puVar43;
  long lVar44;
  long lVar45;
  ulong uVar46;
  undefined2 uVar47;
  ushort uVar48;
  undefined2 uVar49;
  undefined2 uVar50;
  undefined2 uVar51;
  undefined2 uVar52;
  undefined2 uVar53;
  undefined2 uVar54;
  undefined2 uVar55;
  undefined1 uVar56;
  undefined1 uVar57;
  undefined1 uVar58;
  undefined1 uVar59;
  undefined1 uVar60;
  undefined1 uVar61;
  undefined1 uVar62;
  undefined1 uVar63;
  undefined1 uVar64;
  undefined1 uVar65;
  undefined1 uVar66;
  undefined1 uVar67;
  undefined1 uVar68;
  undefined1 uVar69;
  undefined1 uVar70;
  undefined1 uVar71;
  undefined8 uVar72;
  undefined8 uVar73;
  undefined8 uVar74;
  ID local_2a8;
  undefined8 local_2a0;
  long local_298;
  long local_290;
  ulong local_288;
  ulong local_280;
  undefined8 local_250;
  undefined *local_248;
  undefined8 local_240;
  undefined8 local_238;
  undefined8 local_230;
  long local_228;
  ID local_218;
  ulong local_208;
  ulong local_200;
  long local_1f8;
  ulong local_1f0;
  ulong local_1e8;
  double local_1e0;
  double dStack_1d8;
  double dStack_1d0;
  double dStack_1c8;
  double local_1c0;
  double dStack_1b8;
  double dStack_1b0;
  double dStack_1a8;
  undefined *local_198;
  undefined8 uStack_190;
  undefined8 local_188;
  long lStack_180;
  undefined1 local_178;
  undefined1 local_177;
  undefined4 local_176;
  undefined2 local_172;
  long local_170;
  long lStack_168;
  undefined8 local_160;
  undefined8 uStack_158;
  undefined8 local_150;
  undefined8 uStack_148;
  double local_140;
  double dStack_138;
  double local_130;
  double dStack_128;
  undefined8 local_120;
  ID local_118;
  undefined8 local_110;
  undefined8 local_108;
  undefined8 local_100;
  undefined8 local_f8;
  objc_super local_a8;
  objc_super local_98;
  
  local_240 = 0xe900000000000061;
  puVar9 = PTR__OBJC_CLASS___NSMutableAttributedString_100efb510;
  _objc_allocWithZone();
  self = _objc_msgSend((ID)puVar9,PTR_s_init_100ef1148);
  IVar10 = 0;
  FUN_100a55dd4();
  _objc_allocWithZone();
  local_218 = _objc_msgSend(IVar10,PTR_s_init_100ef1148);
  puVar9 = PTR__OBJC_CLASS___NSMutableParagraphStyle_100efb778;
  _objc_allocWithZone();
  IVar10 = _objc_msgSend((ID)puVar9,PTR_s_init_100ef1148);
  _objc_msgSend(IVar10,PTR_s_setAlignment__100eeb158,0);
  _objc_msgSend(IVar10,PTR_s_setLineHeightMultiple__100eedd00,0);
  uVar72 = 0x4020000000000000;
  _objc_msgSend(IVar10,PTR_s_setLineSpacing__100eedcd8,0);
  puVar9 = PTR__OBJC_CLASS___UIFont_100efb240;
  uVar73 = 0x402e000000000000;
  local_2a8 = _objc_msgSend((ID)PTR__OBJC_CLASS___UIFont_100efb240,PTR_s_systemFontOfSize__100eea750
                            ,0);
  lVar28 = *(long *)(unaff_x20 + 8);
  uVar37 = *(ulong *)(lVar28 + 0x10);
  uVar47 = (undefined2)_DAT_100b92e60;
  uVar49 = (undefined2)((ulong)_DAT_100b92e60 >> 0x10);
  uVar50 = (undefined2)((ulong)_DAT_100b92e60 >> 0x20);
  uVar51 = (undefined2)((ulong)_DAT_100b92e60 >> 0x30);
  uVar52 = (undefined2)_UNK_100b92e68;
  uVar53 = (undefined2)((ulong)_UNK_100b92e68 >> 0x10);
  uVar54 = (undefined2)((ulong)_UNK_100b92e68 >> 0x20);
  uVar55 = (undefined2)((ulong)_UNK_100b92e68 >> 0x30);
  if (uVar37 == 0) {
    local_250 = 0;
    local_1f8 = 0;
    local_290 = 0;
    local_288 = 0;
    local_2a0 = 0;
    local_298 = 0;
    uVar56 = 0;
    uVar57 = 0;
    uVar58 = 0;
    uVar59 = 0;
    uVar60 = 0;
    uVar61 = 0;
    uVar62 = 0;
    uVar63 = 0;
    uVar64 = 0;
    uVar65 = 0;
    uVar66 = 0;
    uVar67 = 0;
    uVar68 = 0;
    uVar69 = 0;
    uVar70 = 0;
    uVar71 = 0;
    uVar74 = 0;
    local_248 = (undefined *)0x63697465766c6548;
    dStack_1d0 = 0.0;
    dStack_1c8 = 0.0;
    local_1e0 = 0.0;
    dStack_1d8 = 0.0;
LAB_100a4af04:
    _objc_msgSend(self,PTR_s_length_100ef23f8);
    if (DAT_100f80f50 != -1) {
      _swift_once(&DAT_100f80f50,FUN_100a54954);
    }
    uVar29 = DAT_100f859f0;
    puVar9 = PTR___swiftEmptyArrayStorage_100dde690;
    FUN_100991fc0();
    local_f8 = 0;
    local_198 = puVar9;
    IVar10 = _objc_msgSend(self,PTR_s_mutableString_100eedc90);
    IVar13 = _objc_msgSend(self,PTR_s_length_100ef23f8);
    _swift_retain(uVar29);
    FUN_100a479e0(0,IVar13,IVar10,self,uVar29,&local_f8,&local_198);
    _swift_release(uVar29);
    _swift_bridgeObjectRelease(local_198);
    local_198 = local_248;
    uStack_190 = local_240;
    local_188 = local_250;
    local_178 = (undefined1)(local_288 >> 0x20);
    local_177 = (undefined1)local_288;
    local_176 = (undefined4)local_f8;
    local_172 = local_f8._4_2_;
    local_170 = local_290;
    lStack_168 = local_298;
    local_120 = local_2a0;
    lStack_180 = local_1f8;
    local_160 = CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13(uVar59,
                                                  CONCAT12(uVar58,CONCAT11(uVar57,uVar56)))))));
    uStack_158 = CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,CONCAT13(uVar67,
                                                  CONCAT12(uVar66,CONCAT11(uVar65,uVar64)))))));
    local_150 = CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
    uStack_148 = CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
    local_140 = dStack_1d0;
    dStack_138 = dStack_1c8;
    local_130 = local_1e0;
    dStack_128 = dStack_1d8;
    local_118 = local_218;
    local_110 = uVar73;
    local_108 = uVar74;
    local_100 = uVar72;
    FUN_100a4c4e4(&local_198);
    return self;
  }
  local_1f8 = 0;
  local_228 = 0;
  local_250 = 0;
  local_1f0 = 0;
  uVar41 = 0;
  local_208 = 0;
  uVar46 = 0;
  local_1e8 = 0;
  local_288 = 0;
  local_280 = 0;
  uVar38 = 0;
  uVar42 = 0;
  local_2a0 = 0;
  local_298 = 0;
  bVar4 = 0;
  local_200 = 0;
  local_290 = 0;
  uVar29 = *(undefined8 *)PTR__NSParagraphStyleAttributeName_100ddae28;
  uVar30 = *(undefined8 *)PTR__NSFontAttributeName_100ddae18;
  uVar31 = *(undefined8 *)PTR__UIFontDescriptorNameAttribute_100ddaef8;
  uVar32 = *(undefined8 *)PTR__UIFontDescriptorFamilyAttribute_100ddaef0;
  uVar33 = *(undefined8 *)PTR__NSUnderlineStyleAttributeName_100ddae48;
  uVar34 = *(undefined8 *)PTR__NSStrikethroughStyleAttributeName_100ddae40;
  uVar35 = *(undefined8 *)PTR__NSForegroundColorAttributeName_100ddae20;
  uVar36 = *(undefined8 *)PTR__NSBackgroundColorAttributeName_100ddae08;
  uVar56 = 0;
  uVar57 = 0;
  uVar58 = 0;
  uVar59 = 0;
  uVar60 = 0;
  uVar61 = 0;
  uVar62 = 0;
  uVar63 = 0;
  uVar64 = 0;
  uVar65 = 0;
  uVar66 = 0;
  uVar67 = 0;
  uVar68 = 0;
  uVar69 = 0;
  uVar70 = 0;
  uVar71 = 0;
  uVar74 = 0;
  dStack_1d0 = 0.0;
  dStack_1c8 = 0.0;
  local_1e0 = 0.0;
  dStack_1d8 = 0.0;
  lVar25 = *(long *)(unaff_x20 + 0x10);
  local_248 = (undefined *)0x63697465766c6548;
  local_238 = 0xe900000000000061;
  local_230 = 0xe900000000000061;
LAB_100a4a024:
  if (*(ulong *)(lVar25 + 0x10) <= uVar42) {
                    /* WARNING: Does not return */
    pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b124);
    (*pcVar7)();
  }
  lVar44 = *(long *)(lVar25 + 0x20 + uVar42 * 8);
  if (lVar44 < 0) {
                    /* WARNING: Does not return */
    pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b128);
    (*pcVar7)();
  }
  dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,CONCAT13(
                                                  uVar67,CONCAT12(uVar66,CONCAT11(uVar65,uVar64)))))
                                               ));
  local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13(
                                                  uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56)))))
                                              ));
  dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
  dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
  uVar15 = *(undefined8 *)(lVar28 + uVar42 * 0x10 + 0x28);
  uVar40 = local_1f0;
  if (lVar44 != 0) {
    lVar26 = *(long *)(unaff_x20 + 0x18);
    uVar27 = *(ulong *)(lVar26 + 0x10);
    lVar45 = 0;
    if (local_1f0 <= uVar27) {
      lVar45 = uVar27 - local_1f0;
    }
    _swift_bridgeObjectRetain(uVar15);
    bVar8 = false;
    bVar6 = 0;
    puVar43 = (undefined1 *)(lVar26 + local_1f0 + 0x20);
    lVar44 = 1 - lVar44;
    do {
      uVar40 = uVar40 + 1;
      if ((long)local_1f0 < 0) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0a4);
        (*pcVar7)();
      }
      if (lVar45 == 0) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0a8);
        (*pcVar7)();
      }
      uVar27 = uVar46;
      uVar39 = uVar38;
                    /* WARNING (jumptable): Sanity check requires truncation of jumptable */
                    /* WARNING: Could not find normalized switch variable to match jumptable */
      switch(*puVar43) {
      case 0:
        if ((long)uVar41 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0d4);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x20) + 0x10) <= uVar41) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b108);
          (*pcVar7)();
        }
        lVar26 = *(long *)(unaff_x20 + 0x20) + uVar41 * 0x10;
        local_248 = *(undefined **)(lVar26 + 0x20);
        local_240 = *(undefined8 *)(lVar26 + 0x28);
        dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
        local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13
                                                  (uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56))))
                                                  )));
        dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
        dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
        _swift_bridgeObjectRetain(local_240);
        _swift_bridgeObjectRelease(local_238);
        _swift_bridgeObjectRelease(local_1f8);
        uVar41 = uVar41 + 1;
        bVar6 = 1;
        local_1f8 = 0;
        local_228 = 0;
        local_250 = 0;
        local_238 = local_240;
        local_230 = local_240;
        if (lVar44 == 0) {
          bVar6 = 1;
          local_1f8 = 0;
          local_228 = 0;
          goto LAB_100a4a5e8;
        }
        break;
      case 1:
        if ((long)local_208 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0d0);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x28) + 0x10) <= local_208) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0e4);
          (*pcVar7)();
        }
        uVar24 = local_208 + 1;
        bVar4 = *(byte *)(*(long *)(unaff_x20 + 0x28) + local_208 + 0x20);
        bVar6 = 1;
        local_288 = (ulong)CONCAT14(bVar4,(uint)local_288);
        local_208 = uVar24;
        if (lVar44 == 0) {
          bVar6 = 1;
          dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
          local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,
                                                  CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,
                                                  uVar56)))))));
          dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
          dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
          goto LAB_100a4a5e8;
        }
        break;
      case 2:
        if ((long)local_208 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0b4);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x28) + 0x10) <= local_208) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b114);
          (*pcVar7)();
        }
        uVar24 = local_208 + 1;
        bVar3 = *(byte *)(*(long *)(unaff_x20 + 0x28) + local_208 + 0x20);
        local_200 = (ulong)bVar3;
        bVar6 = 1;
        local_288 = CONCAT44(local_288._4_4_,(uint)bVar3);
        local_208 = uVar24;
        if (lVar44 == 0) {
          bVar6 = 1;
          dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
          local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,
                                                  CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,
                                                  uVar56)))))));
          dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
          dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
          local_200 = (ulong)(uint)bVar3;
          goto LAB_100a4a5e8;
        }
        break;
      case 3:
        if ((long)uVar46 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0bc);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x38) + 0x10) <= uVar46) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b10c);
          (*pcVar7)();
        }
        local_290 = *(long *)(*(long *)(unaff_x20 + 0x38) + uVar46 * 8 + 0x20);
        bVar6 = 1;
        uVar27 = uVar46 + 1;
        if (lVar44 != 0) break;
        bVar6 = 1;
        goto LAB_100a4a5cc;
      case 4:
        if ((long)uVar46 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0dc);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x38) + 0x10) <= uVar46) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0ec);
          (*pcVar7)();
        }
        local_298 = *(long *)(*(long *)(unaff_x20 + 0x38) + uVar46 * 8 + 0x20);
        goto joined_r0x000100a4a2f8;
      case 5:
        if ((long)local_1e8 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0e0);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x30) + 0x10) <= local_1e8) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0f8);
          (*pcVar7)();
        }
        lVar26 = *(long *)(unaff_x20 + 0x30) + local_1e8 * 0x20;
        uVar5 = *(undefined8 *)(lVar26 + 0x28);
        uVar64 = (undefined1)uVar5;
        uVar65 = (undefined1)((ulong)uVar5 >> 8);
        uVar66 = (undefined1)((ulong)uVar5 >> 0x10);
        uVar67 = (undefined1)((ulong)uVar5 >> 0x18);
        uVar68 = (undefined1)((ulong)uVar5 >> 0x20);
        uVar69 = (undefined1)((ulong)uVar5 >> 0x28);
        uVar70 = (undefined1)((ulong)uVar5 >> 0x30);
        uVar71 = (undefined1)((ulong)uVar5 >> 0x38);
        uVar5 = *(undefined8 *)(lVar26 + 0x20);
        uVar56 = (undefined1)uVar5;
        uVar57 = (undefined1)((ulong)uVar5 >> 8);
        uVar58 = (undefined1)((ulong)uVar5 >> 0x10);
        uVar59 = (undefined1)((ulong)uVar5 >> 0x18);
        uVar60 = (undefined1)((ulong)uVar5 >> 0x20);
        uVar61 = (undefined1)((ulong)uVar5 >> 0x28);
        uVar62 = (undefined1)((ulong)uVar5 >> 0x30);
        uVar63 = (undefined1)((ulong)uVar5 >> 0x38);
        uVar5 = *(undefined8 *)(lVar26 + 0x38);
        uVar52 = (undefined2)uVar5;
        uVar53 = (undefined2)((ulong)uVar5 >> 0x10);
        uVar54 = (undefined2)((ulong)uVar5 >> 0x20);
        uVar55 = (undefined2)((ulong)uVar5 >> 0x30);
        uVar5 = *(undefined8 *)(lVar26 + 0x30);
        uVar47 = (undefined2)uVar5;
        uVar49 = (undefined2)((ulong)uVar5 >> 0x10);
        uVar50 = (undefined2)((ulong)uVar5 >> 0x20);
        uVar51 = (undefined2)((ulong)uVar5 >> 0x30);
        goto LAB_100a4a0bc;
      case 6:
        if ((long)local_1e8 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0cc);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x30) + 0x10) <= local_1e8) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0fc);
          (*pcVar7)();
        }
        lVar26 = *(long *)(unaff_x20 + 0x30) + local_1e8 * 0x20;
        dStack_1c8 = *(double *)(lVar26 + 0x28);
        dStack_1d0 = *(double *)(lVar26 + 0x20);
        dStack_1d8 = *(double *)(lVar26 + 0x38);
        local_1e0 = *(double *)(lVar26 + 0x30);
LAB_100a4a0bc:
        local_1e8 = local_1e8 + 1;
        if (lVar44 == 0) {
          dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
          local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,
                                                  CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,
                                                  uVar56)))))));
          dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
          dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
          goto LAB_100a4a5e8;
        }
        break;
      case 7:
        if ((long)uVar46 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0d8);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x38) + 0x10) <= uVar46) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0e8);
          (*pcVar7)();
        }
        local_2a0 = *(undefined8 *)(*(long *)(unaff_x20 + 0x38) + uVar46 * 8 + 0x20);
        bVar8 = true;
joined_r0x000100a4a2f8:
        uVar27 = uVar46 + 1;
        if (lVar44 == 0) {
LAB_100a4a5cc:
          uVar46 = uVar46 + 1;
          dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
          local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,
                                                  CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,
                                                  uVar56)))))));
          dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
          dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
          goto LAB_100a4a5e8;
        }
        break;
      case 8:
        uVar24 = *(ulong *)(unaff_x20 + 0x40);
        dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
        local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13
                                                  (uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56))))
                                                  )));
        dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
        dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
        if ((uVar24 & 0xc000000000000001) == 0) {
          if ((long)local_280 < 0) {
                    /* WARNING: Does not return */
            pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b104);
            (*pcVar7)();
          }
          if (*(ulong *)((uVar24 & 0xffffffffffffff8) + 0x10) <= local_280) {
                    /* WARNING: Does not return */
            pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b120);
            (*pcVar7)();
          }
          local_218 = *(ID *)(uVar24 + local_280 * 8 + 0x20);
        }
        else {
          local_218 = local_280;
          FUN_10099b790();
        }
        bVar8 = SCARRY8(local_280,1);
        local_280 = local_280 + 1;
        if (bVar8) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b11c);
          (*pcVar7)();
        }
        bVar8 = true;
        if (lVar44 == 0) goto LAB_100a4a5e8;
        break;
      case 9:
        if ((long)uVar38 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0c0);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x48) + 0x10) <= uVar38) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0f4);
          (*pcVar7)();
        }
        uVar73 = *(undefined8 *)(*(long *)(unaff_x20 + 0x48) + uVar38 * 8 + 0x20);
        bVar6 = 1;
        uVar39 = uVar38 + 1;
        if (lVar44 != 0) break;
        bVar6 = 1;
        goto LAB_100a4a554;
      case 10:
        if ((long)uVar38 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0c8);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x48) + 0x10) <= uVar38) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b110);
          (*pcVar7)();
        }
        uVar74 = *(undefined8 *)(*(long *)(unaff_x20 + 0x48) + uVar38 * 8 + 0x20);
        goto LAB_100a4a410;
      case 0xb:
        if ((long)uVar38 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0b8);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x48) + 0x10) <= uVar38) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b118);
          (*pcVar7)();
        }
        uVar72 = *(undefined8 *)(*(long *)(unaff_x20 + 0x48) + uVar38 * 8 + 0x20);
LAB_100a4a410:
        bVar8 = true;
        uVar39 = uVar38 + 1;
        if (lVar44 == 0) {
LAB_100a4a554:
          uVar38 = uVar38 + 1;
          dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
          local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,
                                                  CONCAT13(uVar59,CONCAT12(uVar58,CONCAT11(uVar57,
                                                  uVar56)))))));
          dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
          dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
          goto LAB_100a4a5e8;
        }
        break;
      case 0xc:
        if ((long)uVar41 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0b0);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x20) + 0x10) <= uVar41) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b100);
          (*pcVar7)();
        }
        lVar26 = *(long *)(unaff_x20 + 0x20) + uVar41 * 0x10;
        local_248 = *(undefined **)(lVar26 + 0x20);
        local_240 = *(undefined8 *)(lVar26 + 0x28);
        dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
        local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13
                                                  (uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56))))
                                                  )));
        dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
        dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
        _swift_bridgeObjectRetain(local_240);
        _swift_bridgeObjectRelease(local_230);
        uVar41 = uVar41 + 1;
        bVar6 = 1;
        local_238 = local_240;
        local_230 = local_240;
        if (lVar44 == 0) {
          bVar6 = 1;
          goto LAB_100a4a5e8;
        }
        break;
      case 0xd:
        if ((long)uVar41 < 0) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0c4);
          (*pcVar7)();
        }
        if (*(ulong *)(*(long *)(unaff_x20 + 0x20) + 0x10) <= uVar41) {
                    /* WARNING: Does not return */
          pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0f0);
          (*pcVar7)();
        }
        lVar26 = *(long *)(unaff_x20 + 0x20) + uVar41 * 0x10;
        local_250 = *(undefined8 *)(lVar26 + 0x20);
        local_1f8 = *(long *)(lVar26 + 0x28);
        dStack_1b8 = (double)CONCAT17(uVar71,CONCAT16(uVar70,CONCAT15(uVar69,CONCAT14(uVar68,
                                                  CONCAT13(uVar67,CONCAT12(uVar66,CONCAT11(uVar65,
                                                  uVar64)))))));
        local_1c0 = (double)CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13
                                                  (uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56))))
                                                  )));
        dStack_1a8 = (double)CONCAT26(uVar55,CONCAT24(uVar54,CONCAT22(uVar53,uVar52)));
        dStack_1b0 = (double)CONCAT26(uVar51,CONCAT24(uVar50,CONCAT22(uVar49,uVar47)));
        _swift_bridgeObjectRetain(local_1f8);
        _swift_bridgeObjectRelease(local_228);
        uVar41 = uVar41 + 1;
        bVar6 = 1;
        local_228 = local_1f8;
        if (lVar44 == 0) goto LAB_100a4a568;
      }
      puVar43 = puVar43 + 1;
      lVar45 = lVar45 + -1;
      lVar44 = lVar44 + 1;
      uVar38 = uVar39;
      uVar46 = uVar27;
      if (lVar44 == 1) {
                    /* WARNING: Does not return */
        pcVar7 = (code *)SoftwareBreakpoint(1,0x100a4b0ac);
        (*pcVar7)();
      }
    } while( true );
  }
  _swift_bridgeObjectRetain(uVar15);
  bVar6 = 0;
  bVar8 = false;
  goto LAB_100a4a5e8;
LAB_100a4a568:
  bVar6 = 1;
LAB_100a4a5e8:
  local_1f0 = uVar40;
  puVar11 = PTR__OBJC_CLASS___NSMutableAttributedString_100efb510;
  _objc_allocWithZone();
  pNVar12 = (extension_Foundation)::Swift::String::_bridgeToObjectiveC();
  _swift_bridgeObjectRelease(uVar15);
  IVar13 = _objc_msgSend((ID)puVar11,PTR_s_initWithString__100ef18b8,pNVar12);
  IVar14 = _objc_msgSend(IVar13,PTR_s_length_100ef23f8);
  if (bVar8) {
    IVar10 = _objc_msgSend(IVar10,PTR_s_mutableCopy_100ef2b40);
    Swift::__bridgeAnyObjectToAny();
    _swift_unknownObjectRelease(IVar10);
    uVar15 = 0;
    FUN_1000199c0(0,&DAT_100f56c88,&PTR__OBJC_CLASS___NSMutableParagraphStyle_100efb778);
    _swift_dynamicCast(&local_f8,&local_198,PTR_type_metadata_for_Any_100dde678 + 8,uVar15,7);
    IVar10 = local_f8;
    _objc_msgSend(local_f8,PTR_s_setAlignment__100eeb158,local_2a0);
    _objc_msgSend(IVar10,PTR_s_setMaximumLineHeight__100eedce0,(short)uVar74);
    _objc_msgSend(IVar10,PTR_s_setMinimumLineHeight__100eedce8,(short)uVar74);
    _objc_msgSend(IVar10,PTR_s_setLineSpacing__100eedcd8,(short)uVar72);
  }
  _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar29,IVar10,0,IVar14);
  if ((bool)(uVar42 != 0 & (bVar6 ^ 1))) {
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar30,local_2a8,0,IVar14);
    uVar40 = local_200;
    if ((bVar4 & 1) != 0) goto LAB_100a4a860;
LAB_100a4aa78:
    bVar4 = 0;
    local_200 = 0;
    if ((uVar40 & 1) == 0) goto LAB_100a4aae0;
  }
  else {
    if (local_1f8 == 0) {
      puVar11 = &DAT_100f85800;
      FUN_100005490(&DAT_100f85800,&DAT_100bc36c0);
      _swift_initStackObject();
      uVar15 = _DAT_100b81200;
      *(undefined8 *)(puVar11 + 0x18) = _UNK_100b81208;
      *(undefined8 *)(puVar11 + 0x10) = uVar15;
      *(undefined8 *)(puVar11 + 0x20) = uVar32;
      *(undefined **)(puVar11 + 0x40) = PTR_type_metadata_for_Swift_String_100ddd6f8;
      *(undefined **)(puVar11 + 0x28) = local_248;
      *(undefined8 *)(puVar11 + 0x30) = local_240;
      _swift_bridgeObjectRetain(local_240);
      puVar17 = puVar11;
      FUN_100992098(puVar11);
      _swift_setDeallocating(puVar11);
      FUN_100a4c458(puVar11 + 0x20);
    }
    else {
      puVar11 = &DAT_100f85800;
      FUN_100005490(&DAT_100f85800,&DAT_100bc36c0);
      _swift_allocObject();
      uVar15 = _DAT_100b829c0;
      *(undefined8 *)(puVar11 + 0x18) = _UNK_100b829c8;
      *(undefined8 *)(puVar11 + 0x10) = uVar15;
      *(undefined8 *)(puVar11 + 0x20) = uVar31;
      *(undefined8 *)(puVar11 + 0x28) = local_250;
      *(long *)(puVar11 + 0x30) = local_1f8;
      puVar17 = PTR_type_metadata_for_Swift_String_100ddd6f8;
      *(undefined **)(puVar11 + 0x40) = PTR_type_metadata_for_Swift_String_100ddd6f8;
      *(undefined8 *)(puVar11 + 0x48) = uVar32;
      *(undefined **)(puVar11 + 0x68) = puVar17;
      *(undefined **)(puVar11 + 0x50) = local_248;
      *(undefined8 *)(puVar11 + 0x58) = local_240;
      _swift_bridgeObjectRetain(local_1f8);
      _swift_bridgeObjectRetain(local_240);
      puVar17 = puVar11;
      FUN_100992098(puVar11);
      _swift_setDeallocating(puVar11);
      puVar16 = &DAT_100f81a88;
      FUN_100005490(&DAT_100f81a88,&DAT_100bbf7f8);
      _swift_arrayDestroy(puVar11 + 0x20,2,puVar16);
      _swift_deallocClassInstance(puVar11,0x20,7);
    }
    puVar11 = PTR__OBJC_CLASS___UIFontDescriptor_100efc910;
    _objc_allocWithZone();
    FUN_100993270(0);
    FUN_100a4c4a0();
    pNVar18 = (extension_Foundation)::Swift::Dictionary::_bridgeToObjectiveC();
    _swift_bridgeObjectRelease(puVar17);
    IVar19 = _objc_msgSend((ID)puVar11,PTR_s_initWithFontAttributes__100eedcf0,pNVar18);
    IVar20 = _objc_msgSend(IVar19,PTR_s_symbolicTraits_100eebb20);
    uVar2 = (uint)IVar20 | 2;
    if ((local_288 & 0x100000000) == 0) {
      uVar2 = (uint)IVar20;
    }
    IVar20 = _objc_msgSend(IVar19,PTR_s_fontDescriptorWithSymbolicTraits_100eeda08,
                           (ulong)(uVar2 | (uint)local_288 & (uVar2 & 1) == 0));
    if (IVar20 != 0) {
      IVar19 = IVar20;
    }
    local_2a8 = _objc_msgSend((ID)puVar9,PTR_s_fontWithDescriptor_size__100eebad0,(short)uVar73,
                              IVar19);
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar30,local_2a8,0,IVar14);
    local_200 = local_288 & 0xffffffff;
    uVar40 = local_200;
    if ((local_288 & 0x100000000) == 0) goto LAB_100a4aa78;
LAB_100a4a860:
    if (DAT_100f80f08 != -1) {
      _swift_once(&DAT_100f80f08,FUN_100a42ad4);
    }
    uVar15 = DAT_100fc4a38;
    bVar4 = 1;
    pNVar21 = (extension_Foundation)::__int64::_bridgeToObjectiveC();
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar15,pNVar21,0,IVar14);
    if ((local_200 & 1) == 0) {
      local_200 = 0;
      goto LAB_100a4aae0;
    }
  }
  if (DAT_100f80f00 != -1) {
    _swift_once(&DAT_100f80f00,FUN_100a42a48);
  }
  uVar15 = DAT_100fc4a30;
  local_200 = 1;
  pNVar21 = (extension_Foundation)::__int64::_bridgeToObjectiveC();
  _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar15,pNVar21,0,IVar14);
LAB_100a4aae0:
  if (0 < local_290) {
    pNVar21 = (extension_Foundation)::__int64::_bridgeToObjectiveC();
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar33,pNVar21,0,IVar14);
  }
  if (0 < local_298) {
    pNVar21 = (extension_Foundation)::__int64::_bridgeToObjectiveC();
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar34,pNVar21,0,IVar14);
  }
  if (DAT_100f80f20 != -1) {
    _swift_once(&DAT_100f80f20,FUN_100a48540);
  }
  uVar48 = NEON_uminv(CONCAT26((short)(CONCAT19((char)(-(ulong)(dStack_1a8 == DAT_100fc4aa0) >> 8),
                                                CONCAT18((char)-(ulong)(dStack_1a8 == DAT_100fc4aa0)
                                                         ,-(ulong)(dStack_1b0 == _DAT_100fc4a98)))
                                      >> 0x40),
                               CONCAT24((short)-(ulong)(dStack_1b0 == _DAT_100fc4a98),
                                        CONCAT22(-(ushort)(dStack_1b8 == _DAT_100fc4a90),
                                                 -(ushort)(local_1c0 == _DAT_100fc4a88)))),2);
  if ((uVar48 & 1) == 0) {
    _objc_msgSend(IVar13,PTR_s_beginEditing_100eedca0);
    puVar11 = PTR__OBJC_CLASS___UIColor_100efb248;
    _objc_allocWithZone();
    IVar19 = _objc_msgSend((ID)puVar11,PTR_s_initWithRed_green_blue_alpha__100eeb6f0,
                           SUB82(local_1c0,0),
                           CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13(
                                                  uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56)))))
                                                  )),dStack_1b0,dStack_1a8);
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar35,IVar19,0,IVar14);
    if (DAT_100f80ef0 != -1) {
      _swift_once(&DAT_100f80ef0,FUN_100a42928);
    }
    uVar15 = DAT_100fc4a20;
    pcVar22 = (class_t *)0x0;
    FUN_100a55a64();
    pcVar23 = pcVar22;
    _objc_allocWithZone();
    pdVar1 = (double *)((long)&pcVar23->isa + _TtC10NotesStore9TextColor::color);
    pdVar1[1] = dStack_1b8;
    *pdVar1 = local_1c0;
    pdVar1[3] = dStack_1a8;
    pdVar1[2] = dStack_1b0;
    local_98.receiver = (ID)pcVar23;
    local_98.super_class = pcVar22;
    IVar19 = _objc_msgSendSuper2(&local_98,PTR_s_init_100ef1148);
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar15,IVar19,0,IVar14);
    _objc_msgSend(IVar13,PTR_s_endEditing_100eedca8);
  }
  uVar48 = NEON_uminv(CONCAT26((short)(CONCAT19((char)(-(ulong)(dStack_1d8 == dRam0000000100fc4ac0)
                                                      >> 8),
                                                CONCAT18((char)-(ulong)(dStack_1d8 ==
                                                                       dRam0000000100fc4ac0),
                                                         -(ulong)(local_1e0 == _DAT_100fc4ab8))) >>
                                      0x40),
                               CONCAT24((short)-(ulong)(local_1e0 == _DAT_100fc4ab8),
                                        CONCAT22(-(ushort)(dStack_1c8 == dRam0000000100fc4ab0),
                                                 -(ushort)(dStack_1d0 == _DAT_100fc4aa8)))),2);
  if ((uVar48 & 1) == 0) {
    _objc_msgSend(IVar13,PTR_s_beginEditing_100eedca0);
    puVar11 = PTR__OBJC_CLASS___UIColor_100efb248;
    _objc_allocWithZone();
    IVar19 = _objc_msgSend((ID)puVar11,PTR_s_initWithRed_green_blue_alpha__100eeb6f0,
                           SUB82(dStack_1d0,0),
                           CONCAT17(uVar63,CONCAT16(uVar62,CONCAT15(uVar61,CONCAT14(uVar60,CONCAT13(
                                                  uVar59,CONCAT12(uVar58,CONCAT11(uVar57,uVar56)))))
                                                  )),local_1e0,dStack_1d8);
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar36,IVar19,0,IVar14);
    if (DAT_100f80ef8 != -1) {
      _swift_once(&DAT_100f80ef8,FUN_100a429b8);
    }
    uVar15 = DAT_100fc4a28;
    pcVar22 = (class_t *)0x0;
    FUN_100a55a64();
    pcVar23 = pcVar22;
    _objc_allocWithZone();
    pdVar1 = (double *)((long)&pcVar23->isa + _TtC10NotesStore9TextColor::color);
    pdVar1[1] = dStack_1c8;
    *pdVar1 = dStack_1d0;
    pdVar1[3] = dStack_1d8;
    pdVar1[2] = local_1e0;
    local_a8.receiver = (ID)pcVar23;
    local_a8.super_class = pcVar22;
    IVar19 = _objc_msgSendSuper2(&local_a8,PTR_s_init_100ef1148);
    _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,uVar15,IVar19,0,IVar14);
    _objc_msgSend(IVar13,PTR_s_endEditing_100eedca8);
  }
  if (DAT_100f80ee8 != -1) {
    _swift_once(&DAT_100f80ee8,FUN_100a42890);
  }
  uVar42 = uVar42 + 1;
  _objc_msgSend(IVar13,PTR_s_addAttribute_value_range__100eebb58,DAT_100fc4a18,local_218,0,IVar14);
  _objc_msgSend(self,PTR_s_appendAttributedString__100eebc28,IVar13);
  uVar64 = SUB81(dStack_1b8,0);
  uVar65 = (undefined1)((ulong)dStack_1b8 >> 8);
  uVar66 = (undefined1)((ulong)dStack_1b8 >> 0x10);
  uVar67 = (undefined1)((ulong)dStack_1b8 >> 0x18);
  uVar68 = (undefined1)((ulong)dStack_1b8 >> 0x20);
  uVar69 = (undefined1)((ulong)dStack_1b8 >> 0x28);
  uVar70 = (undefined1)((ulong)dStack_1b8 >> 0x30);
  uVar71 = (undefined1)((ulong)dStack_1b8 >> 0x38);
  uVar56 = SUB81(local_1c0,0);
  uVar57 = (undefined1)((ulong)local_1c0 >> 8);
  uVar58 = (undefined1)((ulong)local_1c0 >> 0x10);
  uVar59 = (undefined1)((ulong)local_1c0 >> 0x18);
  uVar60 = (undefined1)((ulong)local_1c0 >> 0x20);
  uVar61 = (undefined1)((ulong)local_1c0 >> 0x28);
  uVar62 = (undefined1)((ulong)local_1c0 >> 0x30);
  uVar63 = (undefined1)((ulong)local_1c0 >> 0x38);
  uVar52 = SUB82(dStack_1a8,0);
  uVar53 = (undefined2)((ulong)dStack_1a8 >> 0x10);
  uVar54 = (undefined2)((ulong)dStack_1a8 >> 0x20);
  uVar55 = (undefined2)((ulong)dStack_1a8 >> 0x30);
  uVar47 = SUB82(dStack_1b0,0);
  uVar49 = (undefined2)((ulong)dStack_1b0 >> 0x10);
  uVar50 = (undefined2)((ulong)dStack_1b0 >> 0x20);
  uVar51 = (undefined2)((ulong)dStack_1b0 >> 0x30);
  if (uVar42 == uVar37) goto LAB_100a4af04;
  goto LAB_100a4a024;
}

