#!/usr/bin/env python3
"""Re-import native writer output using the independent Python decoder."""
import base64,json,subprocess,sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]
sys.path.insert(0,str(ROOT/'research/python'))
from noteful import parse,semantic_summary
subprocess.run(['cargo','build','--locked','-p','noteful-cli'],cwd=ROOT,check=True)
binary=ROOT/'target/debug'/('noteful.exe' if sys.platform=='win32' else 'noteful')
rows=[]
for source in sorted((ROOT/'samples').glob('*.noteful')):
 raw=source.read_bytes();original=parse(raw)
 project={'format':'noteful-re-project','version':1,'source_base64':base64.b64encode(raw).decode(),'history':[{'kind':'Add','page':0,'line':{'width':3,'rgba':[0,0,1,1],'points':[[10,10],[20,30],[40,50],[60,20],[80,30]]}}],'cursor':1}
 output=subprocess.check_output([str(binary),'export','-'],input=json.dumps(project).encode())
 parsed=parse(output)
 assert sum(len(b.get('strokes',[])) for b in parsed['blocks'])==sum(len(b.get('strokes',[])) for b in original['blocks'])+1
 by_id={b['id']:b for b in parsed['blocks']}
 for b in original['blocks']:
  if b['kind'] in ('pdf','jpeg','png','m4a','wav','binary'):
   new=by_id[b['id']];assert raw[b['offset']:b['offset']+b['size']]==output[new['offset']:new['offset']+new['size']]
 assert len(semantic_summary(parsed)['pages'])==len(semantic_summary(original)['pages'])
 rows.append({'file':source.name,'independent_parse':True,'added_strokes':1,'media_exact':True})
(ROOT/'research/evidence/native-export-validation.json').write_text(json.dumps(rows,indent=2)+'\n')
print('Independent native export validation:',len(rows),'notes passed')
