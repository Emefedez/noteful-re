// 100ae197c FUN_100ae197c

/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

void FUN_100ae197c(undefined4 *param_1,long param_2)

{
  ulong *puVar1;
  undefined8 *puVar2;
  undefined *puVar3;
  ulong uVar4;
  ulong uVar5;
  code *pcVar6;
  long lVar7;
  undefined *puVar8;
  float *pfVar9;
  undefined *puVar10;
  undefined *puVar11;
  float *pfVar12;
  ulong uVar13;
  undefined1 *puVar14;
  ulong uVar15;
  undefined *puVar16;
  undefined *puVar17;
  undefined8 uVar18;
  ulong uVar19;
  ulong uVar20;
  long lVar21;
  long unaff_x21;
  ulong *puVar22;
  ulong uVar23;
  undefined8 uVar24;
  undefined *local_c0;
  undefined *local_b8;
  undefined *local_b0;
  undefined *local_a0;
  undefined8 uStack_98;
  undefined8 uStack_90;
  undefined8 uStack_88;
  undefined1 auStack_80 [32];
  float local_58;
  undefined4 uStack_54;
  
  puVar14 = auStack_80;
  _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
  lVar21 = *(long *)(param_2 + 0x20);
  if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae19e8:
    uStack_98 = 0;
    local_a0 = (undefined *)0x0;
    uStack_88 = 0;
    uStack_90 = 0;
  }
  else {
    lVar7 = 1;
    FUN_10099b820(1);
    if (((ulong)puVar14 & 1) == 0) goto LAB_100ae19e8;
    FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
  }
  _swift_endAccess(auStack_80);
  puVar8 = &DAT_100f3c610;
  FUN_100005490(&DAT_100f3c610,&DAT_100b81540);
  pfVar9 = &local_58;
  _swift_dynamicCast(pfVar9,&local_a0,puVar8,PTR_type_metadata_for_Swift_Float_100ddd948,6);
  puVar3 = PTR___swiftEmptyArrayStorage_100dde690;
  if (((ulong)pfVar9 & 1) != 0) {
    if (1.21 < local_58) {
      FUN_1007ebfa8();
      _swift_allocError(&DAT_100e4a268,pfVar9,0,0);
      uVar18 = _DAT_100b8f880;
      *(undefined8 *)(pfVar9 + 2) = _UNK_100b8f888;
      *(undefined8 *)pfVar9 = uVar18;
      *(undefined2 *)(pfVar9 + 4) = 0;
      *(undefined1 *)((long)pfVar9 + 0x12) = 2;
      goto LAB_100ae2040;
    }
    FUN_100991eb8(PTR___swiftEmptyArrayStorage_100dde690);
    _swift_bridgeObjectRelease();
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1adc:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 2;
      FUN_10099b820(2);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1adc;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    puVar10 = &DAT_100f3c380;
    FUN_100005490(&DAT_100f3c380,&DAT_100b907c0);
    pfVar9 = &local_58;
    _swift_dynamicCast(pfVar9,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar9 & 1) == 0) ||
       (puVar16 = (undefined *)CONCAT44(uStack_54,local_58),
       (undefined *)CONCAT44(uStack_54,local_58) == (undefined *)0x0)) {
      puVar16 = PTR___swiftEmptyArrayStorage_100dde690;
    }
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1b74:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 3;
      FUN_10099b820(3);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1b74;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    pfVar9 = &local_58;
    _swift_dynamicCast(pfVar9,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar9 & 1) == 0) ||
       (puVar17 = (undefined *)CONCAT44(uStack_54,local_58),
       (undefined *)CONCAT44(uStack_54,local_58) == (undefined *)0x0)) {
      puVar17 = PTR___swiftEmptyArrayStorage_100dde690;
    }
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1bf4:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 4;
      FUN_10099b820(4);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1bf4;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    pfVar9 = &local_58;
    _swift_dynamicCast(pfVar9,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar9 & 1) == 0) ||
       (pfVar9 = (float *)CONCAT44(uStack_54,local_58),
       (float *)CONCAT44(uStack_54,local_58) == (float *)0x0)) {
      pfVar9 = (float *)PTR___swiftEmptyArrayStorage_100dde690;
    }
    puVar11 = (undefined *)0x14;
    FUN_1009daf90();
    if (unaff_x21 != 0) {
      _swift_bridgeObjectRelease(pfVar9);
      _swift_bridgeObjectRelease(puVar17);
      _swift_bridgeObjectRelease(puVar16);
      return;
    }
    if (puVar11 != (undefined *)0x0) {
      puVar3 = puVar11;
    }
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1cb4:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 10;
      FUN_10099b820(10);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1cb4;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    pfVar12 = &local_58;
    _swift_dynamicCast(pfVar12,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar12 & 1) == 0) ||
       (local_b0 = (undefined *)CONCAT44(uStack_54,local_58), local_b0 == (undefined *)0x0)) {
      local_b0 = PTR___swiftEmptyArrayStorage_100dde690;
    }
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1d38:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 0xb;
      FUN_10099b820(0xb);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1d38;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    puVar10 = &DAT_100f54298;
    FUN_100005490(&DAT_100f54298,&DAT_100bc1130);
    pfVar12 = &local_58;
    _swift_dynamicCast(pfVar12,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar12 & 1) == 0) ||
       (local_b8 = (undefined *)CONCAT44(uStack_54,local_58), local_b8 == (undefined *)0x0)) {
      local_b8 = PTR___swiftEmptyArrayStorage_100dde690;
    }
    puVar14 = auStack_80;
    _swift_beginAccess(param_2 + 0x20,puVar14,0x20,0);
    lVar21 = *(long *)(param_2 + 0x20);
    if (*(long *)(lVar21 + 0x10) == 0) {
LAB_100ae1dd4:
      uStack_98 = 0;
      local_a0 = (undefined *)0x0;
      uStack_88 = 0;
      uStack_90 = 0;
    }
    else {
      lVar7 = 0xc;
      FUN_10099b820(0xc);
      if (((ulong)puVar14 & 1) == 0) goto LAB_100ae1dd4;
      FUN_10000b33c(*(long *)(lVar21 + 0x38) + lVar7 * 0x20,&local_a0);
    }
    _swift_endAccess(auStack_80);
    pfVar12 = &local_58;
    _swift_dynamicCast(pfVar12,&local_a0,puVar8,puVar10,6);
    if ((((ulong)pfVar12 & 1) == 0) ||
       (local_c0 = (undefined *)CONCAT44(uStack_54,local_58), local_c0 == (undefined *)0x0)) {
      local_c0 = PTR___swiftEmptyArrayStorage_100dde690;
    }
    uVar19 = *(ulong *)(local_b0 + 0x10);
    if ((uVar19 == *(ulong *)(local_b8 + 0x10)) && (uVar19 == *(ulong *)(local_c0 + 0x10))) {
      puVar8 = PTR___swiftEmptyDictionarySingleton_100dde698;
      if (uVar19 != 0) {
        uVar23 = 0;
        puVar22 = (ulong *)(local_b0 + 0x28);
        do {
          if (*(ulong *)(local_b0 + 0x10) <= uVar23) {
                    /* WARNING: Does not return */
            pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20bc);
            (*pcVar6)();
          }
          if (*(ulong *)(local_b8 + 0x10) <= uVar23) {
                    /* WARNING: Does not return */
            pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20c0);
            (*pcVar6)();
          }
          if (*(ulong *)(local_c0 + 0x10) <= uVar23) {
                    /* WARNING: Does not return */
            pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20c4);
            (*pcVar6)();
          }
          uVar4 = puVar22[-1];
          uVar5 = *puVar22;
          uVar24 = *(undefined8 *)(local_b8 + uVar23 * 8 + 0x20);
          uVar18 = *(undefined8 *)(local_c0 + uVar23 * 8 + 0x20);
          _swift_bridgeObjectRetain(uVar5);
          puVar10 = puVar8;
          _swift_isUniquelyReferenced_nonNull_native();
          uVar13 = uVar4;
          uVar15 = uVar5;
          local_a0 = puVar8;
          FUN_1002f58b8();
          uVar20 = (ulong)~(uint)uVar15 & 1;
          lVar21 = *(long *)(puVar8 + 0x10) + uVar20;
          if (SCARRY8(*(long *)(puVar8 + 0x10),uVar20)) {
                    /* WARNING: Does not return */
            pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20c8);
            (*pcVar6)();
          }
          if (*(long *)(puVar8 + 0x18) < lVar21) {
            FUN_1009f2628(lVar21,puVar10);
            uVar13 = uVar4;
            uVar20 = uVar5;
            FUN_1002f58b8();
            if (((uint)uVar15 & 1) != ((uint)uVar20 & 1)) {
              Swift::_KEY_TYPE_OF_DICTIONARY_VIOLATES_HASHABLE_REQUIREMENTS();
                    /* WARNING: Does not return */
              pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20dc);
              (*pcVar6)();
            }
joined_r0x000100ae1fcc:
            if ((uVar15 & 1) == 0) goto LAB_100ae1f70;
LAB_100ae1e74:
            _swift_bridgeObjectRelease(uVar5);
            puVar2 = (undefined8 *)(*(long *)(local_a0 + 0x38) + uVar13 * 0x10);
            *puVar2 = uVar24;
            puVar2[1] = uVar18;
          }
          else {
            if (((ulong)puVar10 & 1) == 0) {
              FUN_1009efc90();
              goto joined_r0x000100ae1fcc;
            }
            if ((uVar15 & 1) != 0) goto LAB_100ae1e74;
LAB_100ae1f70:
            *(ulong *)(local_a0 + (uVar13 >> 6) * 8 + 0x40) =
                 *(ulong *)(local_a0 + (uVar13 >> 6) * 8 + 0x40) | 1L << (uVar13 & 0x3f);
            puVar1 = (ulong *)(*(long *)(local_a0 + 0x30) + uVar13 * 0x10);
            *puVar1 = uVar4;
            puVar1[1] = uVar5;
            puVar2 = (undefined8 *)(*(long *)(local_a0 + 0x38) + uVar13 * 0x10);
            *puVar2 = uVar24;
            puVar2[1] = uVar18;
            if (SCARRY8(*(long *)(local_a0 + 0x10),1)) {
                    /* WARNING: Does not return */
              pcVar6 = (code *)SoftwareBreakpoint(1,0x100ae20cc);
              (*pcVar6)();
            }
            *(long *)(local_a0 + 0x10) = *(long *)(local_a0 + 0x10) + 1;
          }
          uVar23 = uVar23 + 1;
          puVar22 = puVar22 + 2;
          puVar8 = local_a0;
        } while (uVar19 != uVar23);
      }
      _swift_bridgeObjectRelease(local_c0);
      _swift_bridgeObjectRelease(local_b8);
      _swift_bridgeObjectRelease(local_b0);
      *param_1 = 0x3f9ae148;
      *(undefined **)(param_1 + 2) = puVar16;
      *(undefined **)(param_1 + 4) = puVar17;
      *(float **)(param_1 + 6) = pfVar9;
      *(undefined **)(param_1 + 8) = puVar3;
      *(undefined **)(param_1 + 10) = puVar8;
      return;
    }
    _swift_bridgeObjectRelease(puVar17);
    _swift_bridgeObjectRelease(puVar16);
    _swift_bridgeObjectRelease(local_c0);
    _swift_bridgeObjectRelease(local_b8);
    _swift_bridgeObjectRelease(local_b0);
    _swift_bridgeObjectRelease(puVar3);
    _swift_bridgeObjectRelease();
  }
  FUN_1007ebfa8();
  _swift_allocError(&DAT_100e4a268,pfVar9,0,0);
  *(undefined **)pfVar9 = &DAT_100e49dd8;
  pfVar9[2] = 0.0;
  pfVar9[3] = 0.0;
  *(undefined2 *)(pfVar9 + 4) = 0;
  *(undefined1 *)((long)pfVar9 + 0x12) = 0;
LAB_100ae2040:
  _swift_willThrow();
  return;
}

