// 100a4f9f0 FUN_100a4f9f0

/* WARNING: Function: _objc_retain replaced with injection: _objc_retain_fixup */
/* WARNING: Function: _objc_release replaced with injection: _objc_release_fixup */
/* WARNING: Function: _objc_retainAutoreleasedReturnValue replaced with injection:
   _objc_retain_fixup */
/* WARNING: Globals starting with '_' overlap smaller symbols at the same address */

ID FUN_100a4f9f0(ulong param_1)

{
  _CocoaArrayWrapper _Var1;
  undefined8 uVar2;
  undefined8 uVar3;
  undefined8 uVar4;
  code *pcVar5;
  ID IVar6;
  undefined *puVar7;
  URL UVar8;
  undefined *puVar9;
  undefined *puVar10;
  undefined8 uVar11;
  undefined *puVar12;
  NSDictionary *pNVar13;
  ID IVar14;
  ID IVar15;
  long extraout_x8;
  undefined8 uVar16;
  undefined8 uVar17;
  undefined1 *puVar18;
  long unaff_x20;
  ID IVar19;
  ID IVar20;
  undefined1 auStack_f8 [152];
  
  puVar7 = &DAT_100f3cb30;
  FUN_100005490(&DAT_100f3cb30,&DAT_100b81ff0);
  (*(code *)PTR____chkstk_darwin_100ddc798)
            (*(long *)(*(long *)(puVar7 + -8) + 0x40) + 0xfU & 0xfffffffffffffff0);
  puVar18 = &stack0xfffffffffffffeb0 + -extraout_x8;
  IVar6 = _objc_msgSend(*(ID *)(unaff_x20 + 0x10),PTR_s_lock_100ef2510);
  if ((param_1 & 1) == 0) {
    FUN_100a4fefc();
    _objc_msgSend(*(ID *)(unaff_x20 + 0x10),PTR_s_unlock_100ef66d8);
    return IVar6;
  }
  IVar6 = *(ID *)(unaff_x20 + 0x20);
  if (IVar6 == 0) {
    FUN_100a4fefc();
    puVar7 = PTR__OBJC_CLASS___NSMutableAttributedString_100efb510;
    _objc_allocWithZone();
    IVar6 = _objc_msgSend((ID)puVar7,PTR_s_initWithAttributedString__100eed4b8,IVar6);
    puVar7 = (undefined *)0x0;
    FUN_100a4ed64();
    if ((ulong)puVar7 >> 0x3e == 0) {
      IVar19 = *(ID *)(((ulong)puVar7 & 0xffffffffffffff8) + 0x10);
      uVar2 = _DAT_100b81200;
      uVar3 = _UNK_100b81208;
    }
    else {
      _Var1.unknown = (undefined *)((ulong)puVar7 & 0xffffffffffffff8);
      if ((long)puVar7 < 0) {
        _Var1.unknown = puVar7;
      }
      IVar19 = Swift::_CocoaArrayWrapper::get_endIndex(_Var1);
      uVar2 = _DAT_100b81200;
      uVar3 = _UNK_100b81208;
    }
    _DAT_100b81200 = uVar2;
    _UNK_100b81208 = uVar3;
    if (IVar19 == 0) {
      _swift_bridgeObjectRelease(puVar7);
    }
    else {
      if ((long)IVar19 < 1) {
                    /* WARNING: Does not return */
        pcVar5 = (code *)SoftwareBreakpoint(1,0x100a4fefc);
        (*pcVar5)();
      }
      IVar20 = 0;
      uVar16 = *(undefined8 *)PTR__NSForegroundColorAttributeName_100ddae20;
      uVar17 = *(undefined8 *)PTR__NSUnderlineStyleAttributeName_100ddae48;
      do {
        if (((ulong)puVar7 & 0xc000000000000001) == 0) {
          IVar15 = *(ID *)(puVar7 + IVar20 * 8 + 0x20);
        }
        else {
          IVar15 = IVar20;
          FUN_10053ca24(IVar20,puVar7);
        }
        UVar8.unknown = (undefined *)_objc_msgSend(IVar15,PTR_s_URL_100eee140);
        if (UVar8.unknown == (undefined *)0x0) {
          UVar8 = Foundation::URL::typeMetadataAccessor();
          (**(code **)(*(long *)(UVar8.unknown + -8) + 0x38))(puVar18,1,1,UVar8.unknown);
          FUN_10000b2c8(puVar18,&DAT_100f3cb30,&DAT_100b81ff0);
        }
        else {
          Foundation::URL::__unconditionallyBridgeFromObjectiveC(UVar8);
          UVar8 = Foundation::URL::typeMetadataAccessor();
          (**(code **)(*(long *)(UVar8.unknown + -8) + 0x38))(puVar18,0,1,UVar8.unknown);
          FUN_10000b2c8(puVar18,&DAT_100f3cb30,&DAT_100b81ff0);
          puVar9 = &DAT_100f43420;
          FUN_100005490(&DAT_100f43420,&DAT_100b87d20);
          puVar10 = puVar9;
          _swift_initStackObject();
          *(undefined8 *)(puVar10 + 0x18) = uVar3;
          *(undefined8 *)(puVar10 + 0x10) = uVar2;
          *(undefined8 *)(puVar10 + 0x20) = uVar16;
          if (DAT_100f80f38 != -1) {
            _swift_once(&DAT_100f80f38,FUN_100a4ecac);
          }
          uVar4 = DAT_100fc4af0;
          uVar11 = 0;
          FUN_1000199c0(0,&DAT_100f3d1a0,&PTR__OBJC_CLASS___UIColor_100efb248);
          *(undefined8 *)(puVar10 + 0x40) = uVar11;
          *(undefined8 *)(puVar10 + 0x28) = uVar4;
          puVar12 = puVar10;
          FUN_1002f7580(puVar10);
          _swift_setDeallocating(puVar10);
          FUN_10000b2c8(puVar10 + 0x20,&DAT_100f43428,&DAT_100b8d6b0);
          FUN_1000059bc(0);
          FUN_100037dc8();
          pNVar13 = (extension_Foundation)::Swift::Dictionary::_bridgeToObjectiveC();
          _swift_bridgeObjectRelease(puVar12);
          puVar10 = PTR_s_range_100ef36f8;
          IVar14 = _objc_msgSend(IVar15,PTR_s_range_100ef36f8);
          _objc_msgSend(IVar6,PTR_s_addAttributes_range__100eedd70,pNVar13,IVar14,puVar10);
          _swift_initStackObject(puVar9,auStack_f8);
          *(undefined8 *)(puVar9 + 0x18) = uVar3;
          *(undefined8 *)(puVar9 + 0x10) = uVar2;
          *(undefined8 *)(puVar9 + 0x20) = uVar17;
          *(undefined **)(puVar9 + 0x40) = PTR_type_metadata_for_Swift_Int_100ddd9d8;
          *(undefined8 *)(puVar9 + 0x28) = 1;
          puVar10 = puVar9;
          FUN_1002f7580(puVar9);
          _swift_setDeallocating(puVar9);
          FUN_10000b2c8(puVar9 + 0x20,&DAT_100f43428,&DAT_100b8d6b0);
          pNVar13 = (extension_Foundation)::Swift::Dictionary::_bridgeToObjectiveC();
          _swift_bridgeObjectRelease(puVar10);
          puVar9 = PTR_s_range_100ef36f8;
          IVar15 = _objc_msgSend(IVar15,PTR_s_range_100ef36f8);
          _objc_msgSend(IVar6,PTR_s_addAttributes_range__100eedd70,pNVar13,IVar15,puVar9);
        }
        IVar20 = IVar20 + 1;
      } while (IVar19 != IVar20);
      _swift_bridgeObjectRelease(puVar7);
    }
    *(ID *)(unaff_x20 + 0x20) = IVar6;
    _objc_msgSend(*(ID *)(unaff_x20 + 0x10),PTR_s_unlock_100ef66d8);
    return IVar6;
  }
  _objc_msgSend(*(ID *)(unaff_x20 + 0x10),PTR_s_unlock_100ef66d8);
  return IVar6;
}

