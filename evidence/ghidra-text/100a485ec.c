// 100a485ec FUN_100a485ec

/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

undefined8
FUN_100a485ec(undefined8 param_1,long param_2,undefined8 param_3,undefined8 param_4,
             undefined8 param_5,ID param_6,String *param_7,long param_8)

{
  undefined1 *puVar1;
  undefined *puVar2;
  undefined1 uVar3;
  String SVar4;
  code *pcVar5;
  bool bVar6;
  ID self;
  undefined8 uVar7;
  NSObject **ppNVar8;
  ulong uVar9;
  undefined *puVar10;
  _StringGuts _Var11;
  NSObject *pNVar12;
  long lVar13;
  ulong uVar14;
  NSObject *pNVar15;
  long lVar16;
  ulong uVar17;
  void *pvVar18;
  char *pcVar19;
  ulong uVar20;
  undefined2 uVar21;
  ushort uVar22;
  undefined2 uVar23;
  undefined2 uVar24;
  undefined2 uVar25;
  short sVar26;
  short sVar27;
  short sVar28;
  void *pvVar29;
  char *pcVar30;
  String SVar31;
  String SVar32;
  NSObject *local_98;
  undefined1 auStack_90 [32];
  
  uVar25 = (undefined2)((ulong)param_1 >> 0x30);
  uVar24 = (undefined2)((ulong)param_1 >> 0x20);
  uVar23 = (undefined2)((ulong)param_1 >> 0x10);
  uVar21 = (undefined2)param_1;
  self = _objc_msgSend(param_6,PTR_s_string_100ef60c8);
  if (self == 0) {
                    /* WARNING: Does not return */
    pcVar5 = (code *)SoftwareBreakpoint(1,0x100a49e04);
    (*pcVar5)();
  }
  _objc_msgSend(self,PTR_s_substringWithRange__100ef6218,param_3,param_4);
  SVar31 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
  puVar10 = SVar31.bridgeObject;
  if (*(long *)(param_2 + 0x10) == 0) {
LAB_100a48768:
    uVar20 = 0;
  }
  else {
    lVar16 = *(long *)PTR__NSFontAttributeName_100ddae18;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48768;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    uVar7 = 0;
    FUN_1000199c0(0,&DAT_100f42478,&PTR__OBJC_CLASS___UIFont_100efb240);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,uVar7,6);
    pNVar12 = local_98;
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48768;
    _objc_msgSend((ID)local_98,PTR_s_fontName_100eebad8);
    SVar32 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
    _Var11.unknown = SVar32.bridgeObject;
    if (param_7[1].bridgeObject == (void *)0x0) {
      _swift_bridgeObjectRelease(_Var11.unknown);
LAB_100a49308:
      _objc_msgSend((ID)pNVar12,PTR_s_fontName_100eebad8);
      SVar32 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
      pvVar18 = param_7[1].bridgeObject;
      param_7[1] = SVar32;
      _swift_bridgeObjectRelease(pvVar18);
      uVar14 = *(ulong *)(param_8 + 0x18);
      uVar20 = uVar14;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x18) = uVar14;
      uVar9 = uVar14;
      if ((uVar20 & 1) == 0) {
        uVar9 = 0;
        FUN_1009f65bc(0,*(long *)(uVar14 + 0x10) + 1,1,uVar14);
        *(ulong *)(param_8 + 0x18) = uVar9;
      }
      uVar20 = *(ulong *)(uVar9 + 0x10);
      uVar14 = uVar9;
      if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar20) {
        uVar14 = (ulong)(1 < *(ulong *)(uVar9 + 0x18));
        FUN_1009f65bc(uVar14,uVar20 + 1,1,uVar9);
        *(ulong *)(param_8 + 0x18) = uVar14;
      }
      *(ulong *)(uVar14 + 0x10) = uVar20 + 1;
      *(undefined1 *)(uVar14 + uVar20 + 0x20) = 0xd;
      _objc_msgSend((ID)pNVar12,PTR_s_fontName_100eebad8);
      SVar32 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
      uVar14 = *(ulong *)(param_8 + 0x20);
      uVar20 = uVar14;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x20) = uVar14;
      uVar9 = uVar14;
      if ((uVar20 & 1) == 0) {
        uVar9 = 0;
        FUN_1002b45c4(0,*(long *)(uVar14 + 0x10) + 1,1,uVar14);
        *(ulong *)(param_8 + 0x20) = uVar9;
      }
      uVar20 = *(ulong *)(uVar9 + 0x10);
      uVar14 = uVar9;
      if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar20) {
        uVar14 = (ulong)(1 < *(ulong *)(uVar9 + 0x18));
        FUN_1002b45c4(uVar14,uVar20 + 1,1,uVar9);
        *(ulong *)(param_8 + 0x20) = uVar14;
      }
      *(ulong *)(uVar14 + 0x10) = uVar20 + 1;
      *(String *)(uVar14 + uVar20 * 0x10 + 0x20) = SVar32;
      _objc_msgSend((ID)pNVar12,PTR_s_familyName_100eebb08);
      SVar32 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
      *param_7 = SVar32;
      _swift_bridgeObjectRelease(param_7->bridgeObject);
      uVar14 = *(ulong *)(param_8 + 0x18);
      uVar20 = uVar14;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x18) = uVar14;
      uVar9 = uVar14;
      if ((uVar20 & 1) == 0) {
        uVar9 = 0;
        FUN_1009f65bc(0,*(long *)(uVar14 + 0x10) + 1,1,uVar14);
        *(ulong *)(param_8 + 0x18) = uVar9;
      }
      uVar20 = *(ulong *)(uVar9 + 0x10);
      uVar14 = uVar9;
      if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar20) {
        uVar14 = (ulong)(1 < *(ulong *)(uVar9 + 0x18));
        FUN_1009f65bc(uVar14,uVar20 + 1,1,uVar9);
        *(ulong *)(param_8 + 0x18) = uVar14;
      }
      *(ulong *)(uVar14 + 0x10) = uVar20 + 1;
      *(undefined1 *)(uVar14 + uVar20 + 0x20) = 0xc;
      _objc_msgSend((ID)pNVar12,PTR_s_familyName_100eebb08);
      SVar32 = (extension_Foundation)::Swift::String::__unconditionallyBridgeFromObjectiveC();
      uVar14 = *(ulong *)(param_8 + 0x20);
      uVar20 = uVar14;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x20) = uVar14;
      uVar9 = uVar14;
      if ((uVar20 & 1) == 0) {
        uVar9 = 0;
        FUN_1002b45c4(0,*(long *)(uVar14 + 0x10) + 1,1,uVar14);
        *(ulong *)(param_8 + 0x20) = uVar9;
      }
      uVar20 = *(ulong *)(uVar9 + 0x10);
      uVar14 = uVar9;
      if (*(ulong *)(uVar9 + 0x18) >> 1 <= uVar20) {
        uVar14 = (ulong)(1 < *(ulong *)(uVar9 + 0x18));
        FUN_1002b45c4(uVar14,uVar20 + 1,1,uVar9);
        *(ulong *)(param_8 + 0x20) = uVar14;
      }
      *(ulong *)(uVar14 + 0x10) = uVar20 + 1;
      *(String *)(uVar14 + uVar20 * 0x10 + 0x20) = SVar32;
      uVar20 = 2;
    }
    else {
      SVar4.bridgeObject = param_7[1].bridgeObject;
      SVar4.str = param_7[1].str;
      if (SVar32 == SVar4) {
        _swift_bridgeObjectRelease(_Var11.unknown);
        uVar20 = 0;
      }
      else {
        bVar6 = Swift::_stringCompareWithSmolCheck
                          ((_StringGuts)SVar32.str,_Var11,
                           (_StringComparisonResult)(__int8)param_7[1].str);
        _swift_bridgeObjectRelease(_Var11.unknown);
        if (!bVar6) goto LAB_100a49308;
        uVar20 = 0;
      }
    }
    puVar10 = PTR_s_pointSize_100eebb10;
    _objc_msgSend((ID)pNVar12,PTR_s_pointSize_100eebb10);
    if ((double)CONCAT26(uVar25,CONCAT24(uVar24,CONCAT22(uVar23,uVar21))) !=
        (double)param_7[8].bridgeObject) {
      uVar17 = *(ulong *)(param_8 + 0x18);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x18) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        uVar14 = 0;
        FUN_1009f65bc(0,*(long *)(uVar17 + 0x10) + 1,1,uVar17);
        *(ulong *)(param_8 + 0x18) = uVar14;
      }
      uVar9 = *(ulong *)(uVar14 + 0x10);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        FUN_1009f65bc(uVar17,uVar9 + 1,1,uVar14);
        *(ulong *)(param_8 + 0x18) = uVar17;
      }
      *(ulong *)(uVar17 + 0x10) = uVar9 + 1;
      *(undefined1 *)(uVar17 + uVar9 + 0x20) = 9;
      puVar10 = PTR_s_pointSize_100eebb10;
      _objc_msgSend((ID)pNVar12,PTR_s_pointSize_100eebb10);
      uVar17 = *(ulong *)(param_8 + 0x48);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x48) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
        uVar14 = 0;
        FUN_1002b3be0(0,puVar10,1,uVar17);
        *(ulong *)(param_8 + 0x48) = uVar14;
      }
      uVar20 = uVar20 | 1;
      uVar9 = *(ulong *)(uVar14 + 0x10);
      puVar2 = (undefined *)(uVar9 + 1);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        puVar10 = puVar2;
        FUN_1002b3be0(uVar17,puVar2,1,uVar14);
        *(ulong *)(param_8 + 0x48) = uVar17;
      }
      *(undefined **)(uVar17 + 0x10) = puVar2;
      *(ulong *)(uVar17 + uVar9 * 8 + 0x20) =
           CONCAT26(uVar25,CONCAT24(uVar24,CONCAT22(uVar23,uVar21)));
    }
  }
  if (DAT_100f80f08 == -1) {
    if (*(long *)(param_2 + 0x10) == 0) goto LAB_100a48808;
LAB_100a48784:
    lVar16 = DAT_100fc4a38;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48808;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,
                       PTR_type_metadata_for_Swift_Int_100ddd9d8,6);
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48808;
    bVar6 = 0 < (long)local_98;
    if (bVar6 != (bool)*(char *)&param_7[2].str) goto LAB_100a48814;
  }
  else {
    puVar10 = (undefined *)0x0;
    _swift_once(&DAT_100f80f08);
    if (*(long *)(param_2 + 0x10) != 0) goto LAB_100a48784;
LAB_100a48808:
    if (((ulong)param_7[2].str & 1) != 0) {
      bVar6 = false;
LAB_100a48814:
      *(bool *)&param_7[2].str = bVar6;
      uVar17 = *(ulong *)(param_8 + 0x18);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x18) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
        uVar14 = 0;
        FUN_1009f65bc(0,puVar10,1,uVar17);
        *(ulong *)(param_8 + 0x18) = uVar14;
      }
      uVar9 = *(ulong *)(uVar14 + 0x10);
      puVar2 = (undefined *)(uVar9 + 1);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        puVar10 = puVar2;
        FUN_1009f65bc(uVar17,puVar2,1,uVar14);
        *(ulong *)(param_8 + 0x18) = uVar17;
      }
      *(undefined **)(uVar17 + 0x10) = puVar2;
      *(undefined1 *)(uVar17 + uVar9 + 0x20) = 1;
      uVar3 = *(undefined1 *)&param_7[2].str;
      uVar17 = *(ulong *)(param_8 + 0x28);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x28) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
        uVar14 = 0;
        FUN_1009f5ebc(0,puVar10,1,uVar17);
        *(ulong *)(param_8 + 0x28) = uVar14;
      }
      uVar20 = uVar20 + 1;
      uVar9 = *(ulong *)(uVar14 + 0x10);
      puVar2 = (undefined *)(uVar9 + 1);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        puVar10 = puVar2;
        FUN_1009f5ebc(uVar17,puVar2,1,uVar14);
        *(ulong *)(param_8 + 0x28) = uVar17;
      }
      *(undefined **)(uVar17 + 0x10) = puVar2;
      *(undefined1 *)(uVar17 + uVar9 + 0x20) = uVar3;
    }
  }
  if (DAT_100f80f00 == -1) {
    if (*(long *)(param_2 + 0x10) == 0) goto LAB_100a48924;
LAB_100a488a0:
    lVar16 = DAT_100fc4a30;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48924;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,
                       PTR_type_metadata_for_Swift_Int_100ddd9d8,6);
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48924;
    bVar6 = 0 < (long)local_98;
    if (bVar6 != (bool)*(char *)((long)&param_7[2].str + 1)) goto LAB_100a48930;
  }
  else {
    puVar10 = (undefined *)0x0;
    _swift_once(&DAT_100f80f00);
    if (*(long *)(param_2 + 0x10) != 0) goto LAB_100a488a0;
LAB_100a48924:
    if (((ulong)param_7[2].str & 0x100) != 0) {
      bVar6 = false;
LAB_100a48930:
      puVar1 = (undefined1 *)((long)&param_7[2].str + 1);
      *puVar1 = bVar6;
      uVar17 = *(ulong *)(param_8 + 0x18);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x18) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
        uVar14 = 0;
        FUN_1009f65bc(0,puVar10,1,uVar17);
        *(ulong *)(param_8 + 0x18) = uVar14;
      }
      uVar9 = *(ulong *)(uVar14 + 0x10);
      puVar2 = (undefined *)(uVar9 + 1);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        puVar10 = puVar2;
        FUN_1009f65bc(uVar17,puVar2,1,uVar14);
        *(ulong *)(param_8 + 0x18) = uVar17;
      }
      *(undefined **)(uVar17 + 0x10) = puVar2;
      *(undefined1 *)(uVar17 + uVar9 + 0x20) = 2;
      uVar3 = *puVar1;
      uVar17 = *(ulong *)(param_8 + 0x28);
      uVar9 = uVar17;
      _swift_isUniquelyReferenced_nonNull_native();
      *(ulong *)(param_8 + 0x28) = uVar17;
      uVar14 = uVar17;
      if ((uVar9 & 1) == 0) {
        puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
        uVar14 = 0;
        FUN_1009f5ebc(0,puVar10,1,uVar17);
        *(ulong *)(param_8 + 0x28) = uVar14;
      }
      uVar20 = uVar20 + 1;
      uVar9 = *(ulong *)(uVar14 + 0x10);
      puVar2 = (undefined *)(uVar9 + 1);
      uVar17 = uVar14;
      if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
        uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
        puVar10 = puVar2;
        FUN_1009f5ebc(uVar17,puVar2,1,uVar14);
        *(ulong *)(param_8 + 0x28) = uVar17;
      }
      *(undefined **)(uVar17 + 0x10) = puVar2;
      *(undefined1 *)(uVar17 + uVar9 + 0x20) = uVar3;
    }
  }
  pNVar12 = (NSObject *)0x0;
  if (*(long *)(param_2 + 0x10) != 0) {
    lVar16 = *(long *)PTR__NSUnderlineStyleAttributeName_100ddae48;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
    }
    else {
      FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
      _swift_bridgeObjectRelease(param_2);
      ppNVar8 = &local_98;
      puVar10 = auStack_90;
      _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,
                         PTR_type_metadata_for_Swift_Int_100ddd9d8,6);
      pNVar12 = local_98;
      if (((ulong)ppNVar8 & 1) != 0) goto LAB_100a48a20;
    }
    pNVar12 = (NSObject *)0x0;
  }
LAB_100a48a20:
  if (pNVar12 != param_7[2].bridgeObject) {
    param_7[2].bridgeObject = pNVar12;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 3;
    pvVar18 = param_7[2].bridgeObject;
    uVar17 = *(ulong *)(param_8 + 0x38);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x38) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b3eb0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x38) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b3eb0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x38) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(void **)(uVar17 + uVar9 * 8 + 0x20) = pvVar18;
  }
  pNVar12 = (NSObject *)0x0;
  if (*(long *)(param_2 + 0x10) != 0) {
    lVar16 = *(long *)PTR__NSStrikethroughStyleAttributeName_100ddae40;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
    }
    else {
      FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
      _swift_bridgeObjectRelease(param_2);
      ppNVar8 = &local_98;
      puVar10 = auStack_90;
      _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,
                         PTR_type_metadata_for_Swift_Int_100ddd9d8,6);
      pNVar12 = local_98;
      if (((ulong)ppNVar8 & 1) != 0) goto LAB_100a48b18;
    }
    pNVar12 = (NSObject *)0x0;
  }
LAB_100a48b18:
  if (pNVar12 != (NSObject *)param_7[3].str) {
    param_7[3].str = (char *)pNVar12;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 4;
    pcVar19 = param_7[3].str;
    uVar17 = *(ulong *)(param_8 + 0x38);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x38) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b3eb0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x38) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b3eb0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x38) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(char **)(uVar17 + uVar9 * 8 + 0x20) = pcVar19;
  }
  if (DAT_100f80ef0 != -1) {
    puVar10 = (undefined *)0x0;
    _swift_once(&DAT_100f80ef0);
  }
  lVar16 = DAT_100fc4a20;
  if (*(long *)(param_2 + 0x10) == 0) {
LAB_100a48c44:
    pvVar18 = _DAT_100fc4a88;
    pcVar19 = _DAT_100fc4a90;
    pvVar29 = _DAT_100fc4a98;
    pcVar30 = DAT_100fc4aa0;
    if (DAT_100f80f20 != -1) {
      puVar10 = (undefined *)0x0;
      _swift_once(&DAT_100f80f20);
      pvVar18 = _DAT_100fc4a88;
      pcVar19 = _DAT_100fc4a90;
      pvVar29 = _DAT_100fc4a98;
      pcVar30 = DAT_100fc4aa0;
    }
  }
  else {
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48c44;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    uVar7 = 0;
    FUN_100a55a64(0);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,uVar7,6);
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48c44;
    pNVar12 = local_98 + _TtC10NotesStore9TextColor::color;
    pvVar18 = *(void **)pNVar12;
    pcVar19 = *(char **)(pNVar12 + 8);
    pvVar29 = *(void **)(pNVar12 + 0x10);
    pcVar30 = *(char **)(pNVar12 + 0x18);
  }
  uVar22 = NEON_uminv(CONCAT26(-(ushort)((double)pcVar30 == (double)param_7[5].str),
                               CONCAT24(-(ushort)((double)pvVar29 == (double)param_7[4].bridgeObject
                                                 ),
                                        CONCAT22(-(ushort)((double)pcVar19 == (double)param_7[4].str
                                                          ),
                                                 -(ushort)((double)pvVar18 ==
                                                          (double)param_7[3].bridgeObject)))),2);
  if ((uVar22 & 1) == 0) {
    param_7[4].str = pcVar19;
    param_7[3].bridgeObject = pvVar18;
    param_7[5].str = pcVar30;
    param_7[4].bridgeObject = pvVar29;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 5;
    pcVar30 = param_7[5].str;
    pvVar29 = param_7[4].bridgeObject;
    pcVar19 = param_7[4].str;
    pvVar18 = param_7[3].bridgeObject;
    uVar17 = *(ulong *)(param_8 + 0x30);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x30) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b43a0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x30) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b43a0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x30) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    lVar16 = uVar17 + uVar9 * 0x20;
    *(char **)(lVar16 + 0x28) = pcVar19;
    *(void **)(lVar16 + 0x20) = pvVar18;
    *(char **)(lVar16 + 0x38) = pcVar30;
    *(void **)(lVar16 + 0x30) = pvVar29;
  }
  if (DAT_100f80ef8 == -1) {
    if (*(long *)(param_2 + 0x10) == 0) goto LAB_100a48dac;
LAB_100a48d18:
    lVar16 = DAT_100fc4a28;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48dac;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    uVar7 = 0;
    FUN_100a55a64(0);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,uVar7,6);
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48dac;
    pNVar12 = local_98 + _TtC10NotesStore9TextColor::color;
    pvVar18 = *(void **)pNVar12;
    pcVar19 = *(char **)(pNVar12 + 8);
    pvVar29 = *(void **)(pNVar12 + 0x10);
    pcVar30 = *(char **)(pNVar12 + 0x18);
  }
  else {
    puVar10 = (undefined *)0x0;
    _swift_once(&DAT_100f80ef8);
    if (*(long *)(param_2 + 0x10) != 0) goto LAB_100a48d18;
LAB_100a48dac:
    pvVar18 = _DAT_100fc4aa8;
    pcVar19 = pcRam0000000100fc4ab0;
    pvVar29 = _DAT_100fc4ab8;
    pcVar30 = pcRam0000000100fc4ac0;
    if (DAT_100f80f20 != -1) {
      puVar10 = (undefined *)0x0;
      _swift_once(&DAT_100f80f20);
      pvVar18 = _DAT_100fc4aa8;
      pcVar19 = pcRam0000000100fc4ab0;
      pvVar29 = _DAT_100fc4ab8;
      pcVar30 = pcRam0000000100fc4ac0;
    }
  }
  sVar26 = -(ushort)((double)pvVar29 == (double)param_7[6].bridgeObject);
  sVar28 = -(ushort)((double)pcVar30 == (double)param_7[7].str);
  sVar27 = -(ushort)((double)pcVar19 == (double)param_7[6].str);
  uVar22 = NEON_uminv(CONCAT26(sVar28,CONCAT24(sVar26,CONCAT22(sVar27,-(ushort)((double)pvVar18 ==
                                                                               (double)param_7[5].
                                                                                       bridgeObject)
                                                              ))),2);
  if ((uVar22 & 1) == 0) {
    param_7[6].str = pcVar19;
    param_7[5].bridgeObject = pvVar18;
    param_7[7].str = pcVar30;
    param_7[6].bridgeObject = pvVar29;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 6;
    pcVar30 = param_7[7].str;
    pvVar29 = param_7[6].bridgeObject;
    pcVar19 = param_7[6].str;
    pvVar18 = param_7[5].bridgeObject;
    uVar17 = *(ulong *)(param_8 + 0x30);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x30) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b43a0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x30) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b43a0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x30) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    lVar16 = uVar17 + uVar9 * 0x20;
    uVar22 = (ushort)pvVar18;
    sVar27 = (short)((ulong)pvVar18 >> 0x10);
    sVar26 = (short)((ulong)pvVar18 >> 0x20);
    sVar28 = (short)((ulong)pvVar18 >> 0x30);
    *(char **)(lVar16 + 0x28) = pcVar19;
    *(void **)(lVar16 + 0x20) = pvVar18;
    *(char **)(lVar16 + 0x38) = pcVar30;
    *(void **)(lVar16 + 0x30) = pvVar29;
  }
  if (*(long *)(param_2 + 0x10) == 0) {
LAB_100a48f30:
    pvVar18 = DAT_100fc4ac8;
    pvVar29 = DAT_100fc4ae8;
    pcVar19 = DAT_100fc4ae0;
    if (DAT_100f80f20 != -1) {
      puVar10 = (undefined *)0x0;
      _swift_once(&DAT_100f80f20);
      pvVar18 = DAT_100fc4ac8;
      pvVar29 = DAT_100fc4ae8;
      pcVar19 = DAT_100fc4ae0;
    }
  }
  else {
    lVar16 = *(long *)PTR__NSParagraphStyleAttributeName_100ddae28;
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
      goto LAB_100a48f30;
    }
    FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
    _swift_bridgeObjectRelease(param_2);
    uVar7 = 0;
    FUN_1000199c0(0,&DAT_100f857f0,&PTR__OBJC_CLASS___NSParagraphStyle_100efc908);
    ppNVar8 = &local_98;
    puVar10 = auStack_90;
    _swift_dynamicCast(ppNVar8,puVar10,PTR_type_metadata_for_Any_100dde678 + 8,uVar7,6);
    pNVar12 = local_98;
    if (((ulong)ppNVar8 & 1) == 0) goto LAB_100a48f30;
    pvVar18 = (void *)_objc_msgSend((ID)local_98,PTR_s_alignment_100eedc98);
    _objc_msgSend((ID)pNVar12,PTR_s_maximumLineHeight_100eedcc8);
    pcVar19 = (char *)CONCAT26(sVar28,CONCAT24(sVar26,CONCAT22(sVar27,uVar22)));
    puVar10 = PTR_s_lineSpacing_100eedcf8;
    _objc_msgSend((ID)pNVar12,PTR_s_lineSpacing_100eedcf8);
    pvVar29 = (void *)CONCAT26(sVar28,CONCAT24(sVar26,CONCAT22(sVar27,uVar22)));
  }
  if (pvVar18 != param_7[7].bridgeObject) {
    param_7[7].bridgeObject = pvVar18;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 7;
    pvVar18 = param_7[7].bridgeObject;
    uVar17 = *(ulong *)(param_8 + 0x38);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x38) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b3eb0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x38) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b3eb0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x38) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(void **)(uVar17 + uVar9 * 8 + 0x20) = pvVar18;
  }
  if ((double)pcVar19 != (double)param_7[9].str) {
    param_7[9].str = pcVar19;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 10;
    pcVar19 = param_7[9].str;
    uVar17 = *(ulong *)(param_8 + 0x48);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x48) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b3be0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x48) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b3be0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x48) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(char **)(uVar17 + uVar9 * 8 + 0x20) = pcVar19;
  }
  if ((double)pvVar29 != (double)param_7[9].bridgeObject) {
    param_7[9].bridgeObject = pvVar29;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1009f65bc(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1009f65bc(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 0xb;
    pvVar18 = param_7[9].bridgeObject;
    uVar17 = *(ulong *)(param_8 + 0x48);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x48) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      puVar10 = (undefined *)(*(long *)(uVar17 + 0x10) + 1);
      uVar14 = 0;
      FUN_1002b3be0(0,puVar10,1,uVar17);
      *(ulong *)(param_8 + 0x48) = uVar14;
    }
    uVar20 = uVar20 + 1;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    puVar2 = (undefined *)(uVar9 + 1);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      puVar10 = puVar2;
      FUN_1002b3be0(uVar17,puVar2,1,uVar14);
      *(ulong *)(param_8 + 0x48) = uVar17;
    }
    *(undefined **)(uVar17 + 0x10) = puVar2;
    *(void **)(uVar17 + uVar9 * 8 + 0x20) = pvVar18;
  }
  if (DAT_100f80ee8 == -1) {
    lVar13 = *(long *)(param_2 + 0x10);
    lVar16 = DAT_100fc4a18;
  }
  else {
    puVar10 = (undefined *)0x0;
    _swift_once(&DAT_100f80ee8);
    lVar13 = *(long *)(param_2 + 0x10);
    lVar16 = DAT_100fc4a18;
  }
  DAT_100fc4a18 = lVar16;
  if (lVar13 != 0) {
    _swift_bridgeObjectRetain(param_2);
    FUN_1003efb0c(lVar16);
    if (((ulong)puVar10 & 1) == 0) {
      _swift_bridgeObjectRelease(param_2);
    }
    else {
      FUN_10000b33c(*(long *)(param_2 + 0x38) + lVar16 * 0x20,auStack_90);
      _swift_bridgeObjectRelease(param_2);
      uVar7 = 0;
      FUN_100a55dd4(0);
      ppNVar8 = &local_98;
      _swift_dynamicCast(ppNVar8,auStack_90,PTR_type_metadata_for_Any_100dde678 + 8,uVar7,6);
      pNVar12 = local_98;
      if (((ulong)ppNVar8 & 1) != 0) goto LAB_100a49178;
    }
  }
  pNVar12 = DAT_100fc4ad0;
  if (DAT_100f80f20 != -1) {
    _swift_once(&DAT_100f80f20,FUN_100a48540);
    pNVar12 = DAT_100fc4ad0;
  }
LAB_100a49178:
  pNVar15 = (NSObject *)param_7[8].str;
  FUN_100a55dd4(0);
  bVar6 = (extension_ObjectiveC)::__C::NSObject::___infix(pNVar12,pNVar15);
  if (!bVar6) {
    param_7[8].str = (char *)pNVar12;
    uVar17 = *(ulong *)(param_8 + 0x18);
    uVar9 = uVar17;
    _swift_isUniquelyReferenced_nonNull_native();
    *(ulong *)(param_8 + 0x18) = uVar17;
    uVar14 = uVar17;
    if ((uVar9 & 1) == 0) {
      uVar14 = 0;
      FUN_1009f65bc(0,*(long *)(uVar17 + 0x10) + 1,1,uVar17);
      *(ulong *)(param_8 + 0x18) = uVar14;
    }
    uVar9 = *(ulong *)(uVar14 + 0x10);
    uVar17 = uVar14;
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      FUN_1009f65bc(uVar17,uVar9 + 1,1,uVar14);
      *(ulong *)(param_8 + 0x18) = uVar17;
    }
    uVar20 = uVar20 + 1;
    *(ulong *)(uVar17 + 0x10) = uVar9 + 1;
    *(undefined1 *)(uVar17 + uVar9 + 0x20) = 8;
    pcVar19 = param_7[8].str;
    FUN_1009f5b54();
    uVar14 = *(ulong *)(param_8 + 0x40) & 0xffffffffffffff8;
    uVar9 = *(ulong *)(uVar14 + 0x10);
    if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
      uVar14 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
      FUN_1009f5fac(uVar14,uVar9 + 1,1);
      *(ulong *)(param_8 + 0x40) = uVar14;
      uVar14 = uVar14 & 0xffffffffffffff8;
    }
    *(ulong *)(uVar14 + 0x10) = uVar9 + 1;
    *(char **)(uVar14 + uVar9 * 8 + 0x20) = pcVar19;
  }
  uVar17 = *(ulong *)(param_8 + 8);
  uVar9 = uVar17;
  _swift_isUniquelyReferenced_nonNull_native();
  *(ulong *)(param_8 + 8) = uVar17;
  uVar14 = uVar17;
  if ((uVar9 & 1) == 0) {
    uVar14 = 0;
    FUN_1002b45c4(0,*(long *)(uVar17 + 0x10) + 1,1,uVar17);
    *(ulong *)(param_8 + 8) = uVar14;
  }
  uVar9 = *(ulong *)(uVar14 + 0x10);
  uVar17 = uVar14;
  if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
    uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
    FUN_1002b45c4(uVar17,uVar9 + 1,1,uVar14);
    *(ulong *)(param_8 + 8) = uVar17;
  }
  *(ulong *)(uVar17 + 0x10) = uVar9 + 1;
  *(String *)(uVar17 + uVar9 * 0x10 + 0x20) = SVar31;
  uVar17 = *(ulong *)(param_8 + 0x10);
  uVar9 = uVar17;
  _swift_isUniquelyReferenced_nonNull_native();
  *(ulong *)(param_8 + 0x10) = uVar17;
  uVar14 = uVar17;
  if ((uVar9 & 1) == 0) {
    uVar14 = 0;
    FUN_1002b3eb0(0,*(long *)(uVar17 + 0x10) + 1,1,uVar17);
    *(ulong *)(param_8 + 0x10) = uVar14;
  }
  uVar9 = *(ulong *)(uVar14 + 0x10);
  uVar17 = uVar14;
  if (*(ulong *)(uVar14 + 0x18) >> 1 <= uVar9) {
    uVar17 = (ulong)(1 < *(ulong *)(uVar14 + 0x18));
    FUN_1002b3eb0(uVar17,uVar9 + 1,1,uVar14);
    *(ulong *)(param_8 + 0x10) = uVar17;
  }
  *(ulong *)(uVar17 + 0x10) = uVar9 + 1;
  *(ulong *)(uVar17 + uVar9 * 8 + 0x20) = uVar20;
  return 0;
}

