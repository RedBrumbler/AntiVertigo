import os, re

for root, dirs, files in os.walk('extern/includes/codegen/include'):
  for infile in files:
    with open(os.path.join(root, infile)) as in_text:
      contents = in_text.read()
    with open(os.path.join(root, infile), 'w') as out:
      out.write(re.sub('#include "extern/beatsaber-hook/', '#include "beatsaber-hook/', contents))